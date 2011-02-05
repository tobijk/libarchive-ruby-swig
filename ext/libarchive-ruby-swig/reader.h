/*
 This file is part of "libarchive-ruby-swig", a simple SWIG wrapper around
 libarchive.

 Copyright 2011, Tobias Koch <tobias.koch@gmail.com>
 
 libarchive-ruby-swig is licensed under a simplified BSD License. A copy of the
 license text can be found in the file LICENSE.txt distributed with the source.
*/

#ifndef CLASS_ARCHIVE_READER_H_INCLUDED
#define CLASS_ARCHIVE_READER_H_INCLUDED

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
        static VALUE e_archive =
            rb_define_class_under(c_archive, "Error", rb_eStandardError);
        rb_raise(e_archive, err.what());
    }
}
#endif

#ifdef SWIG
%newobject read_open_filename(const char *filename);
%newobject read_open_memory(const char *string, int length);
%newobject next_header();
#endif

        static Reader *read_open_filename(const char *filename);
        static Reader *read_open_memory(const char *string, int length);

        Entry *next_header();
        VALUE read_data_helper(int len);

#ifdef SWIG
%exception;
#endif

    private:
        struct archive *_ar;
        char *_buf;
        char *_archive_content;
        int _buf_size;
};

#endif
