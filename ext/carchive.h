#ifndef CLASS_ARCHIVE_H_INCLUDED
#define CLASS_ARCHIVE_H_INCLUDED

struct archive;
class ArchiveEntry;

#ifndef SWIG
#include <ruby.h>
#endif

class Archive
{
    public:
        Archive(struct archive *ar);
        virtual ~Archive();
        void close();

#ifdef SWIG
%exception {
    try {
        $action
    } catch(ArchiveError &err) {
        static VALUE archive_error = rb_define_class("ArchiveError", rb_eStandardError);
        rb_raise(archive_error, err.what());
    }
}
#endif

#ifdef SWIG
%newobject read_open_filename_helper(const char *filename);
%newobject next_header();
#endif

        static Archive *read_open_filename_helper(const char *filename);
        ArchiveEntry *next_header();
        VALUE read_data_helper(int len);

#ifdef SWIG
%exception;
#endif

    private:
        struct archive *_ar;
        char *_buf;
        int _buf_size;
};

#endif
