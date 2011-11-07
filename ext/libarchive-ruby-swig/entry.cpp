/*
 This file is part of "libarchive-ruby-swig", a simple SWIG wrapper around
 libarchive.

 Copyright 2011, Tobias Koch <tobias.koch@gmail.com>
 
 libarchive-ruby-swig is licensed under a simplified BSD License. A copy of the
 license text can be found in the file LICENSE.txt distributed with the source.
*/

#include <cstring>
#include <string>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <archive.h>
#include <archive_entry.h>
#include <ruby.h>
#include "entry.h"
#include "error.h"

Entry::Entry(struct archive_entry *entry)
    : _entry(entry)
{}

Entry::~Entry()
{
    if(_entry) {
        archive_entry_free(_entry);
        _entry = 0;
    }
}

bool Entry::is_file()
{
    if(S_ISREG(archive_entry_filetype(_entry)) &&
        !this->is_hardlink()) {
        return true;
    }

    return false;
}

bool Entry::is_directory()
{
    return S_ISDIR(archive_entry_filetype(_entry));
}

bool Entry::is_symbolic_link()
{
    return S_ISLNK(archive_entry_filetype(_entry));
}

bool Entry::is_block_special()
{
    return S_ISBLK(archive_entry_filetype(_entry));
}

bool Entry::is_character_special()
{
    return S_ISCHR(archive_entry_filetype(_entry));
}

bool Entry::is_fifo()
{
    return S_ISFIFO(archive_entry_filetype(_entry));
}

bool Entry::is_socket()
{
    return S_ISSOCK(archive_entry_filetype(_entry));
}

bool Entry::is_hardlink()
{
    if(archive_entry_hardlink(_entry) != 0)
        return true;

    return false;
}

unsigned int Entry::filetype()
{
    return archive_entry_filetype(_entry);
}

void Entry::set_filetype(unsigned int filetype)
{
    archive_entry_set_filetype(_entry, filetype);
}

unsigned int Entry::devmajor()
{
    return archive_entry_devmajor(_entry);
}

void Entry::set_devmajor(unsigned int devmajor)
{
    archive_entry_set_devmajor(_entry, devmajor);
}

unsigned int Entry::devminor()
{
    return archive_entry_devminor(_entry);
}

void Entry::set_devminor(unsigned int devminor)
{
    archive_entry_set_devminor(_entry, devminor);
}

unsigned long Entry::atime()
{
    return archive_entry_atime(_entry);
}

void Entry::set_atime(unsigned long atime)
{
    archive_entry_set_atime(_entry, atime, 0);
}

void Entry::clear()
{
    archive_entry_clear(_entry);
}

Entry *Entry::clone()
{
    return new Entry(archive_entry_clone(_entry));
}

unsigned long Entry::dev()
{
    return archive_entry_dev(_entry);
}

void Entry::set_dev(unsigned long dev)
{
    archive_entry_set_dev(_entry, dev);
}

unsigned long Entry::gid()
{
    return archive_entry_gid(_entry);
}

void Entry::set_gid(unsigned long gid)
{
    archive_entry_set_gid(_entry, gid);
}

const char *Entry::gname()
{
    return archive_entry_gname(_entry);
}

void Entry::set_gname(const char *gname)
{
    archive_entry_copy_gname(_entry, gname);
}

const char *Entry::hardlink()
{
    return archive_entry_hardlink(_entry);
}

void Entry::set_hardlink(const char *hardlink)
{
    archive_entry_copy_hardlink(_entry, hardlink);
}

unsigned long Entry::ino()
{
    return archive_entry_ino(_entry);
}

void Entry::set_ino(unsigned long ino)
{
    archive_entry_set_ino(_entry, ino);
}

int Entry::mode()
{
    return archive_entry_mode(_entry);
}

void Entry::set_mode(int mode)
{
    archive_entry_set_mode(_entry, mode);
}

unsigned long Entry::mtime()
{
    return archive_entry_mtime(_entry);
}

void Entry::set_mtime(unsigned long mtime)
{
    archive_entry_set_mtime(_entry, mtime, 0);
}

unsigned int Entry::nlink()
{
    return archive_entry_nlink(_entry);
}

void Entry::set_nlink(unsigned int nlink)
{
    archive_entry_set_nlink(_entry, nlink);
}

const char *Entry::pathname()
{
    return archive_entry_pathname(_entry);
}

void Entry::set_pathname(const char *pathname)
{
    archive_entry_copy_pathname(_entry, pathname);
}

unsigned int Entry::rdevmajor()
{
    return archive_entry_rdevmajor(_entry);
}

void Entry::set_rdevmajor(unsigned int rdevmajor)
{
    archive_entry_set_rdevmajor(_entry, rdevmajor);
}

unsigned int Entry::rdevminor()
{
    return archive_entry_rdevminor(_entry);
}

void Entry::set_rdevminor(unsigned int rdevminor)
{
    archive_entry_set_rdevminor(_entry, rdevminor);
}

unsigned long Entry::size()
{
    return archive_entry_size(_entry);
}

void Entry::set_size(unsigned long size)
{
    archive_entry_set_size(_entry, size);
}

const char *Entry::symlink()
{
    return archive_entry_symlink(_entry);
}

void Entry::set_symlink(const char *symlink)
{
    archive_entry_copy_symlink(_entry, symlink);
}

unsigned long Entry::uid()
{
    return archive_entry_uid(_entry);
}

void Entry::set_uid(unsigned long uid)
{
    archive_entry_set_uid(_entry, uid);
}

const char *Entry::uname()
{
    return archive_entry_uname(_entry);
}

void Entry::set_uname(const char *uname)
{
    archive_entry_copy_uname(_entry, uname);
}

void Entry::copy_stat_helper(const char *filename)
{
    struct stat sb;
    if(lstat(filename, &sb) == -1) {
        std::string error_msg = strerror(errno);
        throw Error(error_msg);
    }

    archive_entry_copy_stat(_entry, &sb);
}

