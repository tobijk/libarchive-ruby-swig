#include <string>
#include <archive.h>
#include <archive_entry.h>
#include <ruby.h>
#include "carchive.h"
#include "carchiveentry.h"
#include "carchiveerror.h"

Archive::Archive(struct archive *ar)
    : _ar(ar),
    _buf((char*) malloc(1024)),
    _buf_size(1024)
{}


Archive::~Archive()
{
    this->close();
    free(_buf);
    _buf = 0;
    _buf_size = 0;
}


void Archive::close()
{
    if(_ar) {
        archive_read_finish(_ar);
        _ar = 0;
    }
}


Archive *Archive::read_open_filename_helper(const char * filename) 
{
    struct archive *ar = archive_read_new();

    try {
        if(archive_read_support_compression_all(ar) != ARCHIVE_OK)
            throw 0;

        if(archive_read_support_format_all(ar) != ARCHIVE_OK)
            throw 0;

        if(archive_read_open_filename(ar, filename, 1024) != ARCHIVE_OK)
            throw 0;

    } catch(...) {
        std::string error_msg = archive_error_string(ar);
        archive_read_finish(ar);
        throw ArchiveError(error_msg);
    }

    return new Archive(ar);
}


ArchiveEntry *Archive::next_header()
{
    ArchiveEntry * result = 0;
    std::string error_msg = "operation on uninitialized archive";

    if(!_ar)
        throw ArchiveError(error_msg);

    struct archive_entry *entry = archive_entry_new();
    int rval = archive_read_next_header2(_ar, entry);

    switch(rval) {
        case ARCHIVE_EOF:
            archive_entry_free(entry);
            close();
            break;
        case ARCHIVE_OK:
            result = new ArchiveEntry(entry);
            break;
        default:
            archive_entry_free(entry);
            error_msg = archive_error_string(_ar);
            throw ArchiveError(error_msg);
    }

    return result;
}


VALUE Archive::read_data_helper(int len)
{
    std::string error_msg = "error while reading from archive";

    if(len > _buf_size) {
        _buf = (char*) realloc(_buf, len);
        _buf_size = len;
    }

    ssize_t rval = archive_read_data(_ar, (void*) _buf, len);

    switch(rval) {
        case ARCHIVE_FATAL:
        case ARCHIVE_WARN:
        case ARCHIVE_RETRY:
            error_msg = archive_error_string(_ar);
            throw ArchiveError(error_msg);
        case 0:
            return 0;
    }

    return rb_tainted_str_new(_buf, rval);
}
