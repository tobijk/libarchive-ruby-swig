%module libarchive_swig

%{
#include <archive.h>
#include <archive_entry.h>
#include <ruby.h>
#include "reader.h"
#include "entry.h"
#include "error.h"
%}

%include "reader.h"
%include "entry.h"

