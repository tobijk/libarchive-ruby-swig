require 'mkmf'

unless have_header('archive.h') && \
  have_library('archive', 'archive_read_open_filename')
  $stderr.write "Libarchive development files not found.\n"
  exit 1
end

if find_executable('g++')
  $libs = append_library($libs, "stdc++")
end

if swig = find_executable('swig')
  `#{swig} -c++ -ruby libarchive_swig.i`
  $distcleanfiles << 'libarchive_swig_wrap.cxx'
else
  $stderr.write "You need SWIG to compile this extension.\n"
  exit 1
end

create_makefile('libarchive_swig') 
