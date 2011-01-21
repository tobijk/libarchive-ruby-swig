#include <archive.h>
#include <archive_entry.h>
#include <ruby.h>
#include "entry.h"

Entry::Entry(struct archive_entry *entry)
{
    _entry = entry;
}

Entry::~Entry()
{
    if(_entry) {
        archive_entry_free(_entry);
        _entry = 0;
    }
}

const char *Entry::pathname()
{
    return archive_entry_pathname(_entry);
}

const char *Entry::symlink()
{
    return archive_entry_symlink(_entry);
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

int Entry::devmajor()
{
    return archive_entry_devmajor(_entry);
}

int Entry::devminor()
{
    return archive_entry_devminor(_entry);
}

int Entry::mode()
{
    return archive_entry_mode(_entry);
}

