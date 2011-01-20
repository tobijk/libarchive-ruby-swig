#include <archive.h>
#include <archive_entry.h>
#include <ruby.h>
#include "carchiveentry.h"

ArchiveEntry::ArchiveEntry(struct archive_entry *entry)
{
    _entry = entry;
}

ArchiveEntry::~ArchiveEntry()
{
    if(_entry) {
        archive_entry_free(_entry);
        _entry = 0;
    }
}

const char *ArchiveEntry::pathname()
{
    return archive_entry_pathname(_entry);
}

const char *ArchiveEntry::symlink()
{
    return archive_entry_symlink(_entry);
}

bool ArchiveEntry::is_directory()
{
    return S_ISDIR(archive_entry_filetype(_entry));
}

bool ArchiveEntry::is_symbolic_link()
{
    return S_ISLNK(archive_entry_filetype(_entry));
}

bool ArchiveEntry::is_block_special()
{
    return S_ISBLK(archive_entry_filetype(_entry));
}

bool ArchiveEntry::is_character_special()
{
    return S_ISCHR(archive_entry_filetype(_entry));
}

bool ArchiveEntry::is_fifo()
{
    return S_ISFIFO(archive_entry_filetype(_entry));
}

bool ArchiveEntry::is_socket()
{
    return S_ISSOCK(archive_entry_filetype(_entry));
}

int ArchiveEntry::devmajor()
{
    return archive_entry_devmajor(_entry);
}

int ArchiveEntry::devminor()
{
    return archive_entry_devminor(_entry);
}

int ArchiveEntry::mode()
{
    return archive_entry_mode(_entry);
}

