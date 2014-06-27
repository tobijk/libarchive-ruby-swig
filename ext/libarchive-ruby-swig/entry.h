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

        #ifdef SWIG
        %feature("autodoc", "Indicates if Entry is a regular file") is_file;
        #endif
        bool is_file();

        #ifdef SWIG
        %feature("autodoc", "Indicates if Entry is a directory") is_directory;
        #endif
        bool is_directory();

        #ifdef SWIG
        %feature("autodoc", "Indicates if Entry is a symlink") is_symbolic_link;
        #endif
        bool is_symbolic_link();

        #ifdef SWIG
        %feature("autodoc", "Indicates if Entry is a block device node") is_block_special;
        #endif
        bool is_block_special();

        #ifdef SWIG
        %feature("autodoc", "Indicates if Entry is a character device node") is_character_special;
        #endif
        bool is_character_special();

        #ifdef SWIG
        %feature("autodoc", "Indicates if Entry is a fifo") is_fifo;
        #endif
        bool is_fifo();

        #ifdef SWIG
        %feature("autodoc", "Indicates if Entry is a UNIX domain socket") is_socket;
        #endif
        bool is_socket();

        #ifdef SWIG
        %feature("autodoc", "Indicates if Entry is a hardlink") is_hardlink;
        #endif
        bool is_hardlink();

        #ifdef SWIG
        %feature("autodoc", "Returns the filetype bits for Entry") filetype;
        #endif
        unsigned int filetype();

        #ifdef SWIG
        %feature("autodoc", "Use one of the <code>Archive::ENTRY_*</code> to specify the filetype of the Entry.") set_filetype;
        #endif
        void set_filetype(unsigned int filetype);

        #ifdef SWIG
        %feature("autodoc", "Device major number of device on which this Entry resided. "
                            "This field will not be available in most cases and is, in "
                            "any case, platform-specific") devmajor;
        #endif
        unsigned int devmajor();

        #ifdef SWIG
        %feature("autodoc", " Sets the device major number of the device on which "
                            "this Entry resides. This field will not be availabla "
                            "in most cases and is, in any case, platform-specific") set_devmajor;
        #endif
        void set_devmajor(unsigned int devmajor);

        #ifdef SWIG
        %feature("autodoc", "Device minor number of device on which this Entry resided. "
                            "This field will not be available in most cases and is, in "
                            "any case, platform-specific") devminor;
        #endif
        unsigned int devminor();

        #ifdef SWIG
        %feature("autodoc", " Sets the device minor number of the device on which "
                            "this Entry resides. This field will not be availabla "
                            "in most cases and is, in any case, platform-specific") set_devminor;
        #endif
        void set_devminor(unsigned int devminor);

        #ifdef SWIG
        %feature("autodoc", "Returns the atime of the saved Entry as a timestamp since epoch") atime;
        #endif
        unsigned long atime();

        #ifdef SWIG
        %feature("autodoc", "Sets the atime of Entry to the given timestamp since epoch") set_atime;
        #endif
        void set_atime(unsigned long atime);

        #ifdef SWIG
        %feature("autodoc", "Resets the Entry") clear;
        #endif
        void clear();

        #ifdef SWIG
        %feature("autodoc", "Returns an exact clone of Entry") clone;
        #endif
        Entry *clone();

        #ifdef SWIG
        %feature("autodoc", "Device id of the device on which entry resided. "
                            "This is usually unused and, in any case, platform-specific") dev;
        #endif
        unsigned long dev();

        #ifdef SWIG
        %feature("autodoc", "Sets the device id of the device on which "
                            "entry resided. This is usually unused and, "
                            "in any case, platform-specific") set_dev;
        #endif
        void set_dev(unsigned long dev);

        #ifdef SWIG
        %feature("autodoc", "Group id of Entry") gid;
        #endif
        unsigned long gid();

        #ifdef SWIG
        %feature("autodoc", "Sets the group id of Entry") set_gid;
        #endif
        void set_gid(unsigned long gid);

        #ifdef SWIG
        %feature("autodoc", "Group name of Entry") gname;
        #endif
        const char *gname();

        #ifdef SWIG
        %feature("autodoc", "Set group name of Entry") set_gname;
        #endif
        void set_gname(const char *gname);

        #ifdef SWIG
        %feature("autodoc", "Path of file this entry was hardlinked to") hardlink;
        #endif
        const char *hardlink();

        #ifdef SWIG
        %feature("autodoc", "Sets the path to the file this entry is hard-linked to") set_hardlink;
        #endif
        void set_hardlink(const char *hardlink);

        #ifdef SWIG
        %feature("autodoc", "Inode of Entry") ino;
        #endif
        unsigned long ino();

        #ifdef SWIG
        %feature("autodoc", "Sets the inode of Entry") set_ino;
        #endif
        void set_ino(unsigned long ino);

        #ifdef SWIG
        %feature("autodoc", "Permission bits and filetype of entry") mode;
        #endif
        int mode();

        #ifdef SWIG
        %feature("autodoc", "Sets filetype and permission bits of Entry") set_mode;
        #endif
        void set_mode(int mode);

        #ifdef SWIG
        %feature("autodoc", "Returns the mtime of Entry as a timestamp since epoch") mtime;
        #endif
        unsigned long mtime();

        #ifdef SWIG
        %feature("autodoc", "Sets the mtime of Entry to given timestamp since epoch") set_mtime;
        #endif
        void set_mtime(unsigned long mtime);

        #ifdef SWIG
        %feature("autodoc", "Number of hard links to Entry") nlink;
        #endif
        unsigned int nlink();

        #ifdef SWIG
        %feature("autodoc", "Sets the number of hardlinks to Entry") set_nlink;
        #endif
        void set_nlink(unsigned int nlink);

        #ifdef SWIG
        %feature("autodoc", "Returns the pathname of Entry") pathname;
        #endif
        const char *pathname();

        #ifdef SWIG
        %feature("autodoc", "Sets the pathname of Entry") set_pathname;
        #endif
        void set_pathname(const char *pathname);

        #ifdef SWIG
        %feature("autodoc", "The dev major number of the device represented by Entry") rdevmajor;
        #endif
        unsigned int rdevmajor();

        #ifdef SWIG
        %feature("autodoc", "Sets the dev major number of the device represented by Entry") set_rdevmajor;
        #endif
        void set_rdevmajor(unsigned int rdevmajor);

        #ifdef SWIG
        %feature("autodoc", "The dev minor number of the device represented by Entry") rdevminor;
        #endif
        unsigned int rdevminor();

        #ifdef SWIG
        %feature("autodoc", "Sets the dev minor number of the device represented by Entry") set_rdevminor;
        #endif
        void set_rdevminor(unsigned int rdevminor);

        #ifdef SWIG
        %feature("autodoc", "Size of the Entry. In case Entry is a symlink, "
                            "returns the size of the symlink's target name") size;
        #endif
        unsigned long size();

        #ifdef SWIG
        %feature("autodoc", "Sets the size of the Entry. In case Entry is "
                            "a symlink, this should be the length of the string set with <code>symlink=</code>") set_size;
        #endif
        void set_size(unsigned long size);

        #ifdef SWIG
        %feature("autodoc", "Returns the target of a symlink Entry") symlink;
        #endif
        const char *symlink();

        #ifdef SWIG
        %feature("autodoc", "Sets the target of a symlink Entry") set_symlink;
        #endif
        void set_symlink(const char *symlink);

        #ifdef SWIG
        %feature("autodoc", "Returns the numeric user id of Entry") uid;
        #endif
        unsigned long uid();

        #ifdef SWIG
        %feature("autodoc", "Sets the numeric user id of Entry") set_uid;
        #endif
        void set_uid(unsigned long uid);

        #ifdef SWIG
        %feature("autodoc", "Returns the Entry owner's username") uname;
        #endif
        const char *uname();

        #ifdef SWIG
        %feature("autodoc", "Sets the Entry owner's username") set_uname;
        #endif
        void set_uname(const char *uname);

#ifdef SWIG
%exception {
    try {
        $action
    } catch(Error &err) {
        static VALUE c_archive = rb_define_module("Archive");
        static VALUE e_archive =
            rb_define_class_under(c_archive, "Error", rb_eStandardError);
        VALUE o_except = rb_exc_new2(e_archive, err.what());
        rb_exc_raise(o_except);
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
