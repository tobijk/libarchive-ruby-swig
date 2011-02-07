/*
 This file is part of "libarchive-ruby-swig", a simple SWIG wrapper around
 libarchive.

 Copyright 2011, Tobias Koch <tobias.koch@gmail.com>
 
 libarchive-ruby-swig is licensed under a simplified BSD License. A copy of the
 license text can be found in the file LICENSE.txt distributed with the source.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "stat.h"

int Stat::type_file()
{
    return S_IFREG;
}

int Stat::type_directory()
{
    return S_IFDIR;
}

int Stat::type_symbolic_link()
{
    return S_IFLNK;
}

int Stat::type_block_special()
{
    return S_IFBLK;
}

int Stat::type_character_special()
{
    return S_IFCHR;
}

int Stat::type_fifo()
{
    return S_IFIFO;
}

int Stat::type_socket()
{
    return S_IFSOCK;
}

