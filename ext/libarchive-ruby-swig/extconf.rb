#
# This file is part of "libarchive-ruby-swig", a simple SWIG wrapper around
# libarchive.
#
# Copyright 2011, Tobias Koch <tobias.koch@gmail.com>
# 
# libarchive-ruby-swig is licensed under a simplified BSD License. A copy of the
# license text can be found in the file LICENSE.txt distributed with the source.
#

require 'mkmf'

RbConfig::MAKEFILE_CONFIG['CC']  = ENV['CC']  if ENV['CC']
RbConfig::MAKEFILE_CONFIG['CXX'] = ENV['CXX'] if ENV['CXX']

unless have_header('archive.h') && \
  have_library('archive', 'archive_read_open_filename') &&
  have_library('archive', 'archive_read_support_format_raw')
  $stderr.write "Libarchive development files not found.\n"
  exit 1
end

if find_executable('g++') or find_executable('clang++')
  $libs = append_library($libs, "stdc++")
end

swig = [ 'swig2', 'swig2.0', 'swig' ].select { |swig_name|
  find_executable(swig_name) }.first

if swig
  $stdout.write "Using '#{swig}' to generate wrapper code... "
  `#{swig} -c++ -ruby -features autodoc=0 libarchive.i`
  $stdout.write "done\n"
  $distcleanfiles += [ 'libarchive_wrap.cxx', 'libarchive_wrap_doc.cxx' ]
else
  $stderr.write "You need SWIG to compile this extension.\n"
  exit 1
end

create_makefile('archive') 
