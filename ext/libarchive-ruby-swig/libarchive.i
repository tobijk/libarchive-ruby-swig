/*
 This file is part of "libarchive-ruby-swig", a simple SWIG wrapper around
 libarchive.

 Copyright 2011, Tobias Koch <tobias.koch@gmail.com>
 
 libarchive-ruby-swig is licensed under a simplified BSD License. A copy of the
 license text can be found in the file LICENSE.txt distributed with the source.
*/

%module archive

%{
#include <archive.h>
#include <archive_entry.h>
#include <ruby.h>

#include "stat.h"
#include "reader.h"
#include "writer.h"
#include "entry.h"
#include "error.h"
%}

%init %{
    Error::init();
%}

%wrapper %{
/* --- WRAPPER CODE START --- */
%}

%apply (char *STRING, int LENGTH) { (const char *string, int length) };

%include "stat.h"
%include "reader.h"
%include "writer.h"
%include "entry.h"
