#
# This file is part of "libarchive-ruby-swig", a simple SWIG wrapper around
# libarchive.
#
# Copyright 2011, Tobias Koch <tobias.koch@gmail.com>
# 
# libarchive-ruby-swig is licensed under a simplified BSD License. A copy of the
# license text can be found in the file LICENSE.txt distributed with the source.
#

require 'archive'

module Archive

  ENTRY_FILE = Stat.type_file
  ENTRY_DIRECTORY = Stat.type_directory
  ENTRY_SYMBOLIC_LINK = Stat.type_symbolic_link
  ENTRY_FIFO = Stat.type_fifo
  ENTRY_SOCKET = Stat.type_socket
  ENTRY_BLOCK_SPECIAL = Stat.type_block_special
  ENTRY_CHARACTER_SPECIAL = Stat.type_character_special

  class Error < StandardError
  end

  class Entry
    alias :file? :is_file
    alias :directory? :is_directory
    alias :symbolic_link? :is_symbolic_link
    alias :block_special? :is_block_special
    alias :character_special? :is_character_special
    alias :fifo? :is_fifo
    alias :socket? :is_socket

    alias :filetype= :set_filetype
    alias :devmajor= :set_devmajor
    alias :devminor= :set_devminor
    alias :atime= :set_atime
    alias :dev= :set_dev
    alias :gid= :set_gid
    alias :gname= :set_gname
    alias :hardlink= :set_hardlink
    alias :ino= :set_ino
    alias :mode= :set_mode
    alias :mtime= :set_mtime
    alias :nlink= :set_nlink
    alias :pathname= :set_pathname
    alias :rdevmajor= :set_rdevmajor
    alias :rdevminor= :set_rdevminor
    alias :size= :set_size
    alias :symlink= :set_symlink
    alias :uid= :set_uid
    alias :uname= :set_uname

    def copy_stat(path)
      copy_stat_helper(path)
      self.set_symlink(File.readlink(path)) if self.symbolic_link?
    end

    private_class_method :new
  end

  class Reader
 
    def read_data(size)
      if block_given?
        while result = self.read_data_helper(size)
          yield result
        end
      else
        return self.read_data_helper(size)
      end
    end
 
    private_class_method :new
  end

  class Writer

    def new_entry()
      entry = self.new_entry_helper
      if block_given?
        yield entry
      else
        return entry
      end
    end

    def write_data(data = nil)
      if block_given?
        while result = yield
          self.write_data_helper(result)
        end
      else
        self.write_data_helper(data)
      end
    end

    private_class_method :new
  end

  def self.read_open_filename(filename, cmd = nil)
    unless cmd.nil?
      cmd = locate_cmd(cmd)
    end

    ar = Reader.read_open_filename(filename, cmd)
 
    if block_given?
      yield ar
      ar.close()
    else
      return ar
    end
  end

  def self.read_open_memory(string, cmd = nil)
    unless cmd.nil?
      cmd = locate_cmd(cmd)
    end

    ar = Reader.read_open_memory(string, cmd)

    if block_given?
      yield ar
      ar.close()
    else
      return ar
    end
  end

  def self.write_open_filename(filename, compression, format)
    if compression.is_a? String
      compresion = locate_cmd(compression)
    end

    ar = Writer.write_open_filename(filename, compression, format)

    if block_given?
      yield ar
      ar.close()
    else
      return ar
    end
  end

  private

  def self.locate_cmd(cmd)
    unless cmd.is_a? String
      raise Error, "exepected String but found #{cmd.class}"
    end

    if cmd.index('/').nil?
      ENV['PATH'].split(File::PATH_SEPARATOR).each do |path|
        if File.executable?(path + '/' + cmd)
          cmd = path + '/' + cmd
          break
        end
      end
    end

    unless File.executable? cmd
      raise Error, "executable '#{cmd}' not found"
    end

    return cmd
  end

end

