/*
 This file is part of "libarchive-ruby-swig", a simple SWIG wrapper around
 libarchive.

 Copyright 2011, Tobias Koch <tobias.koch@gmail.com>
 
 libarchive-ruby-swig is licensed under a simplified BSD License. A copy of the
 license text can be found in the file LICENSE.txt distributed with the source.
*/

#ifndef CLASS_ARCHIVE_ERROR_H_INCLUDED
#define CLASS_ARCHIVE_ERROR_H_INCLUDED

#include <exception>

class Error: public std::exception
{
    public:

        Error(const std::string &error_msg)
            : error_msg(error_msg) {};

        virtual ~Error() throw()
            {};

        virtual const char *what() const throw() {
            return error_msg.c_str();
        }

    private:

        std::string error_msg;
};

#endif
