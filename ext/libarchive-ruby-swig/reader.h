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

        #ifdef SWIG
        %feature("autodoc", "Releases all resources associated with the Reader object") close;
        #endif
        void close();

#ifdef SWIG
%exception {
    try {
        $action
    } catch(Error &err) {
        Error::ruby_raise(err);
        SWIG_fail;
    }
}
#endif

#ifdef SWIG
%feature("autodoc", "Use <code>Archive::read_open_filename</code> instead") read_open_filename;
%newobject read_open_filename(const char *filename, const char *cmd = 0, bool raw = false);
%feature("autodoc", "Use <code>Archive::read_open_memory</code> instead") read_open_memory;
%newobject read_open_memory(const char *string, size_t length, const char *cmd = 0, bool raw = false);
%feature("autodoc", "Returns the next Entry meta data object in the Archive") next_header;
%newobject next_header();
#endif

        static Reader *read_open_filename(const char *filename,
            const char *cmd = 0, bool raw = false);
        static Reader *read_open_memory(const char *string, size_t length,
            const char *cmd = 0, bool raw = false);

        Entry *next_header();
        VALUE read_data_helper(size_t len);

#ifdef SWIG
%exception;
#endif

    private:
        struct archive *_ar;
        char *_buf;
        size_t _buf_size;
        char *_archive_content;
};

#endif
