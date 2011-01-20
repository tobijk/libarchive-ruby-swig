#ifndef CLASS_ARCHIVE_ERROR_H_INCLUDED
#define CLASS_ARCHIVE_ERROR_H_INCLUDED

#include <exception>

class ArchiveError: public std::exception
{
    public:

        ArchiveError(const std::string &error_msg)
            : error_msg(error_msg) {};

        virtual ~ArchiveError() throw()
            {};

        virtual const char *what() const throw() {
            return error_msg.c_str();
        }

    private:

        std::string error_msg;
};

#endif
