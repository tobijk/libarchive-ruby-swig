%module libarchive_swig

%{
#include <archive.h>
#include <archive_entry.h>
#include <ruby.h>
#include "carchive.h"
#include "carchiveentry.h"
#include "carchiveerror.h"
%}

#include "carchive.h"
#include "carchiveentry.h"

