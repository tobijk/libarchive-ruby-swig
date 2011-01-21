#ifndef CLASS_ARCHIVE_H_INCLUDED
#define CLASS_ARCHIVE_H_INCLUDED

struct archive;
class Entry;

#ifndef SWIG
#include <ruby.h>
#endif

class Reader
{
    public:
        Reader(struct archive *ar);
        virtual ~Reader();
        void close();

#ifdef SWIG
%exception {
    try {
        $action
    } catch(Error &err) {
        static VALUE c_archive = rb_define_module("Archive");
        static VALUE e_archive = rb_define_class_under(c_archive, "Error", rb_eStandardError);
        rb_raise(e_archive, err.what());
    }
}
#endif

#ifdef SWIG
%newobject read_open_filename(const char *filename);
%newobject next_header();
#endif

        static Reader *read_open_filename(const char *filename);
        Entry *next_header();
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
