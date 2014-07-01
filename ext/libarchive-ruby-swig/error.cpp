/*
 This file is part of "libarchive-ruby-swig", a simple SWIG wrapper around
 libarchive.

 Copyright 2011, Tobias Koch <tobias.koch@gmail.com>
 
 libarchive-ruby-swig is licensed under a simplified BSD License. A copy of the
 license text can be found in the file LICENSE.txt distributed with the source.
*/

#include <ruby.h>
#include "error.h"

namespace {
    VALUE archive_rb_error_class;
}

void Error::init() throw()
{
    VALUE c_archive = rb_define_module("Archive");
    archive_rb_error_class =
        rb_define_class_under(c_archive, "Error", rb_eStandardError);
}

void Error::ruby_raise(const Error &err) throw()
{
    VALUE o_except = rb_exc_new2(archive_rb_error_class, err.what());
    rb_exc_raise(o_except);
}

