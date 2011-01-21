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
