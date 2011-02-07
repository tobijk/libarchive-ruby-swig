/*
 This file is part of "libarchive-ruby-swig", a simple SWIG wrapper around
 libarchive.

 Copyright 2011, Tobias Koch <tobias.koch@gmail.com>
 
 libarchive-ruby-swig is licensed under a simplified BSD License. A copy of the
 license text can be found in the file LICENSE.txt distributed with the source.
*/

#ifndef CLASS_ARCHIVE_STAT_H_INCLUDED
#define CLASS_ARCHIVE_STAT_H_INCLUDED

class Stat
{
    public:

        static int type_file();
        static int type_directory();
        static int type_symbolic_link();
        static int type_block_special();
        static int type_character_special();
        static int type_fifo();
        static int type_socket();
};

#endif
