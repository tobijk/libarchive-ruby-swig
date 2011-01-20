#ifndef CLASS_ARCHIVE_ENTRY_H_INCLUDED
#define CLASS_ARCHIVE_ENTRY_H_INCLUDED

struct archive_entry;

class ArchiveEntry
{
    public:
        ArchiveEntry(struct archive_entry *entry);
        virtual ~ArchiveEntry();
        const char *pathname();
        const char *symlink();
        bool is_directory();
        bool is_symbolic_link();
        bool is_block_special();
        bool is_character_special();
        bool is_fifo();
        bool is_socket();
        int devmajor();
        int devminor();
        int mode();

    private:
        struct archive_entry *_entry;
};

#endif
