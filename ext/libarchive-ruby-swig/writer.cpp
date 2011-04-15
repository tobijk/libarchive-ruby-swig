/*
 This file is part of "libarchive-ruby-swig", a simple SWIG wrapper around
 libarchive.

 Copyright 2011, Tobias Koch <tobias.koch@gmail.com>
 
 libarchive-ruby-swig is licensed under a simplified BSD License. A copy of the
 license text can be found in the file LICENSE.txt distributed with the source.
*/

#include <string>
#include <archive.h>
#include <archive_entry.h>
#include <ruby.h>
#include "writer.h"
#include "entry.h"
#include "error.h"

Writer::Writer(struct archive *ar)
    :_ar(ar),
    _buf(0),
    _buf_size(0)
{}


Writer::~Writer()
{
    this->close();
    free(_buf);
    _buf = 0;
    _buf_size = 0;
}


void Writer::close()
{
    if(_ar) {
        archive_write_finish(_ar);
        _ar = 0;
    }
}


Writer *Writer::write_open_filename(const char *filename,
    const char *cmd, int format)

{
    std::string error_msg;
    struct archive *ar = archive_write_new();

    archive_write_set_compression_program(ar, cmd);
    try {
        set_format_helper(ar, format);

        if(archive_write_open_filename(ar, filename) != ARCHIVE_OK) {
            error_msg = archive_error_string(ar);
            throw Error(error_msg);
        }

    } catch(...) {
        archive_write_finish(ar);
        throw;
    }

    return new Writer(ar);
}


Writer *Writer::write_open_filename(const char *filename,
    int compression, int format)
{
    std::string error_msg;
    struct archive *ar = archive_write_new();

    try {

        switch(compression) {
            case Archive::COMPRESSION_BZIP2:
                archive_write_set_compression_bzip2(ar);
                break;
            case Archive::COMPRESSION_COMPRESS:
                archive_write_set_compression_compress(ar);
                break;
            case Archive::COMPRESSION_GZIP:
                archive_write_set_compression_gzip(ar);
                break;
            case Archive::COMPRESSION_LZMA:
                archive_write_set_compression_lzma(ar);
                break;
            case Archive::COMPRESSION_NONE:
                archive_write_set_compression_none(ar);
                break;
            case Archive::COMPRESSION_XZ:
                archive_write_set_compression_xz(ar);
                break;
            default:
                error_msg = "unknown or unsupported compression scheme";
                throw Error(error_msg);
        }

        set_format_helper(ar, format);

        if(archive_write_open_filename(ar, filename) != ARCHIVE_OK) {
            error_msg = archive_error_string(ar);
            throw Error(error_msg);
        }

    } catch(...) {
        archive_write_finish(ar);
        throw;
    }

    return new Writer(ar);
}


Entry *Writer::new_entry_helper()
{
    return new Entry(archive_entry_new());
}


void Writer::write_header(Entry *entry)
{
    if(entry->nlink() > 1) {
        std::string path = _hardlinks[entry->dev()][entry->ino()];
        if(path.empty()) {
            _hardlinks[entry->dev()][entry->ino()] =
                std::string(entry->pathname());
        } else {
            entry->set_hardlink(path.c_str());
        }
    }

    if(archive_write_header(_ar, entry->_entry) != ARCHIVE_OK) {
        std::string error_msg = archive_error_string(_ar);
        throw Error(error_msg);
    }
}


void Writer::write_data_helper(const char *string, int length)
{
    if(archive_write_data(_ar, (void*) string, length) == -1) {
        std::string error_msg = archive_error_string(_ar);
        throw Error(error_msg);
    }
}


void Writer::set_format_helper(struct archive *ar, int format)
{
    std::string error_msg;

    switch(format) {
        case Archive::FORMAT_AR_BSD:
            archive_write_set_format_ar_bsd(ar);
            break;
        case Archive::FORMAT_AR_SVR4:
            archive_write_set_format_ar_svr4(ar);
            break;
        case Archive::FORMAT_CPIO:
            archive_write_set_format_cpio(ar);
            break;
        case Archive::FORMAT_CPIO_NEWC:
            archive_write_set_format_cpio_newc(ar);
            break;
        case Archive::FORMAT_MTREE:
            archive_write_set_format_mtree(ar);
            break;
        case Archive::FORMAT_TAR:
        case Archive::FORMAT_TAR_PAX_RESTRICTED:
            archive_write_set_format_pax_restricted(ar);
            break;
        case Archive::FORMAT_TAR_PAX_INTERCHANGE:
            archive_write_set_format_pax(ar);
            break;
        case Archive::FORMAT_TAR_USTAR:
            archive_write_set_format_ustar(ar);
            break;
        default:
            error_msg = "unknown or unsupported archive format";
            throw Error(error_msg);
    }
}

