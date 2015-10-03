# libarchive-ruby-swig

Copyright (c) 2011, Tobias Koch <tobias.koch@gmail.com>

## Description

Ruby bindings to libarchive allowing reading and creation of compressed archive files of various formats. This gem uses [SWIG](http://swig.org) to generate the bindings from a C++ wrapper around libarchive. It is mostly interface-compatible with the [Libarchive/Ruby](https://bitbucket.org/winebarrel/libarchive-ruby/) gem by Sugawara Genki.

## Installation

Install the gem 

    gem install libarchive-ruby-swig

or clone the git source repository

    git clone git://github.com/tobijk/libarchive-ruby-swig.git

and then build and install

    gem build libarchive-ruby-swig.gemspec
    gem install libarchive-ruby-swig-<version>.gem

Please mind that you need to install SWIG and the development files for libarchive in order to compile the native extension.

## Usage Examples

### Writing an Archive

The following example shows how to recursively pack everything from the current working directory into a bzip2-compressed tarball:

```ruby
require 'libarchive_rs'

Archive.write_open_filename('../test.tar.bz2', Archive::COMPRESSION_BZIP2, Archive::FORMAT_TAR) do |ar|
  Dir.glob('**/*').each do |fn|
    ar.new_entry do |entry|
      entry.copy_stat(fn)
      entry.pathname = fn
      ar.write_header(entry)

      if entry.file?
        open(fn) do |f|
          ar.write_data { f.read(1024) }
        end
      end

    end
  end
end
```

### Reading from an Archive

The following example shows how to extract all files from the given archive to the current working directory:

```ruby
require 'libarchive_rs'

Archive.read_open_filename(filename) do |archive|
  while entry = archive.next_header
    path = entry.pathname.sub(/^\//, '')
    if entry.directory?
      Dir.mkdir path unless File.directory? path
    elsif entry.symbolic_link?
      File.symlink(entry.symlink, path)
    else
      File.open(path, 'w+') do |fp|
        archive.read_data(1024) {|data| fp.write(data)}
      end
    end
    File.chmod(entry.mode, path) unless entry.symbolic_link?
   end
end
```

Note that this example doesn't treat special entries, such as device nodes, correctly.

