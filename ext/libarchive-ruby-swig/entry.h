/*
 This file is part of "libarchive-ruby-swig", a simple SWIG wrapper around
 libarchive.

 Copyright 2011, Tobias Koch <tobias.koch@gmail.com>
 
 libarchive-ruby-swig is licensed under a simplified BSD License. A copy of the
 license text can be found in the file LICENSE.txt distributed with the source.
*/

#ifndef CLASS_ARCHIVE_ENTRY_H_INCLUDED
#define CLASS_ARCHIVE_ENTRY_H_INCLUDED

#include "writer.h"

struct archive_entry;

class Entry
{
    friend void Writer::write_header(Entry *entry);

    public:
        Entry(struct archive_entry *entry);
        virtual ~Entry();

        bool is_file();
        bool is_directory();
        bool is_symbolic_link();
        bool is_block_special();
        bool is_character_special();
        bool is_fifo();
        bool is_socket();

        unsigned int filetype();
        void set_filetype(unsigned int filetype);

        unsigned int devmajor();
        void set_devmajor(unsigned int devmajor);

        unsigned int devminor();
        void set_devminor(unsigned int devminor);

        unsigned long atime();
        void set_atime(unsigned long atime);

        void clear();

#ifdef SWIG
%newobject clone(Entry *entry);
#endif

        Entry *clone();

        unsigned long dev();
        void set_dev(unsigned long dev);

        unsigned long gid();
        void set_gid(unsigned long gid);

        const char *gname();
        void set_gname(const char *gname);

        const char *hardlink();
        void set_hardlink(const char *hardlink);

        unsigned long ino();
        void set_ino(unsigned long ino);

        int mode();
        void set_mode(int mode);

        unsigned long mtime();
        void set_mtime(unsigned long mtime);

        unsigned int nlink();
        void set_nlink(unsigned int nlink);

        const char *pathname();
        void set_pathname(const char *pathname);

        unsigned int rdevmajor();
        void set_rdevmajor(unsigned int rdevmajor);

        unsigned int rdevminor();
        void set_rdevminor(unsigned int rdevminor);

        unsigned long size();
        void set_size(unsigned long size);

        const char *symlink();
        void set_symlink(const char *symlink);

        unsigned long uid();
        void set_uid(unsigned long uid);

        const char *uname();
        void set_uname(const char *uname);

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

        void copy_stat_helper(const char *filename);

#ifdef SWIG
%exception;
#endif

    private:
        struct archive_entry *_entry;
};

#endif
