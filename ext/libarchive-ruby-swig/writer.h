/*
 This file is part of "libarchive-ruby-swig", a simple SWIG wrapper around
 libarchive.

 Copyright 2011, Tobias Koch <tobias.koch@gmail.com>
 
 libarchive-ruby-swig is licensed under a simplified BSD License. A copy of the
 license text can be found in the file LICENSE.txt distributed with the source.
*/

#ifndef CLASS_ARCHIVE_WRITER_H_INCLUDED
#define CLASS_ARCHIVE_WRITER_H_INCLUDED

struct archive;
class Entry;

#ifndef SWIG
#include <ruby.h>
#include <string>
#include <map>
#endif

namespace Archive
{
    enum {
        FORMAT_AR = 1,
        FORMAT_AR_BSD,
        FORMAT_AR_SVR4,
        FORMAT_CPIO,
        FORMAT_CPIO_NEWC,
        FORMAT_MTREE,
        FORMAT_TAR,
        FORMAT_TAR_GNUTAR,
        FORMAT_TAR_PAX_INTERCHANGE,
        FORMAT_TAR_PAX_RESTRICTED,
        FORMAT_TAR_USTAR,
        FORMAT_TAR_OLDTAR,
        FORMAT_ZIP
    };

    enum {
        COMPRESSION_BZIP2 = 1,
        COMPRESSION_COMPRESS,
        COMPRESSION_GZIP,
        COMPRESSION_LZMA,
        COMPRESSION_NONE,
        COMPRESSION_XZ
    };
};


class Writer
{
    public:
        Writer(struct archive *ar);
        virtual ~Writer();

        #ifdef SWIG
        %feature("autodoc", "Releases all resources associated with the Writer object") close;
        #endif
        void close();

#ifdef SWIG
%exception {
    try {
        $action
    } catch(Error &err) {
        static VALUE c_archive = rb_define_module("Archive");
        static VALUE e_archive =
            rb_define_class_under(c_archive, "Error", rb_eStandardError);
        static VALUE o_except = rb_exc_new2(e_archive, err.what());
        rb_exc_raise(o_except);
    }
}
#endif

#ifdef SWIG
%feature("autodoc", "Use Archive::write_open_filename instead") write_open_filename;
%newobject write_open_filename(const char *filename,
    const char *cmd, int format);
%newobject write_open_filename(const char *filename,
    int compression, int format);
#endif

        static Writer *write_open_filename(const char *filename,
            const char *cmd, int format);

        static Writer *write_open_filename(const char *filename,
            int compression, int format);

        #ifdef SWIG
        %feature("autodoc", "Write Entry meta data to Archive") write_header;
        #endif
        void write_header(Entry *entry);

        void write_data_helper(const char *string, int length);

#ifdef SWIG
%exception;
#endif

#ifdef SWIG
%newobject new_entry_helper();
#endif

        Entry *new_entry_helper();

    private:
        static void set_format_helper(struct archive *ar, int format);

        struct archive *_ar;
        char *_buf;
        int _buf_size;

        std::map<unsigned long, std::map<unsigned long, std::string> > _hardlinks;
};

#endif
