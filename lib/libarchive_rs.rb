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

  ##
  #
  # Thrown on problems with opening or processing an archive.
  #
  class Error < StandardError
  end

  ##
  #
  # This class is not meant to be used directly. It exists for the sole purpose
  # of initializing the <code>Archive::ENTRY_*</code> constants in a
  # platform-independent way.
  #
  class Stat
    private_class_method :new
  end  

  ENTRY_FILE = Stat.type_file
  ENTRY_DIRECTORY = Stat.type_directory
  ENTRY_SYMBOLIC_LINK = Stat.type_symbolic_link
  ENTRY_FIFO = Stat.type_fifo
  ENTRY_SOCKET = Stat.type_socket
  ENTRY_BLOCK_SPECIAL = Stat.type_block_special
  ENTRY_CHARACTER_SPECIAL = Stat.type_character_special

  class Entry
    alias :file? :is_file
    alias :directory? :is_directory
    alias :symbolic_link? :is_symbolic_link
    alias :block_special? :is_block_special
    alias :character_special? :is_character_special
    alias :fifo? :is_fifo
    alias :socket? :is_socket
    alias :hardlink? :is_hardlink

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

    ##
    #
    # Populates an Entry by doing a stat on given path and copying all
    # attributes.
    #
    def copy_stat(path)
      copy_stat_helper(path)
      self.set_symlink(File.readlink(path)) if self.symbolic_link?
    end

    private_class_method :new
  end

  class Reader

    ##
    #
    # Reads size bytes from the Archive. If a block is given, chunks of size
    # bytes are repeatedly passed to the block until the complete data stored
    # for the Entry has been read. If size is not specified, all data stored
    # is returned at once.
    #
    def read_data(size = nil)
      if block_given?
        if size.nil?
          result = []
          while data = self.read_data_helper(1024)
            result << data
          end
          yield result.join('')
        else
          while data = self.read_data_helper(size)
            yield data
          end
        end
      else
        if size.nil?
          result = []
          while data = self.read_data_helper(1024)
            result << data
          end
          return result.join('')
        else
          return self.read_data_helper(size)
        end
      end
    end
 
    private_class_method :new
  end

  class Writer

    ##
    #
    # Creates a new Entry. An Entry holds the meta data for an item stored in
    # an Archive, such as filetype, mode, owner, etc. It is typically populated
    # by a call to <code>copy_stat</code>. It is written before the actual data.
    #
    def new_entry()
      entry = self.new_entry_helper
      if block_given?
        yield entry
      else
        return entry
      end
    end

    ##
    #
    # Write data to Archive. If a block is given, data returned from the block
    # is stored until the block returns nil.
    #
    def write_data(data = nil)
      if block_given?
        while data = yield
          self.write_data_helper(data)
        end
      else
        self.write_data_helper(data)
      end
    end

    private_class_method :new
  end

  ##
  #
  # Open filename for reading. Libarchive automatically determines archive
  # format and compression scheme. Optionally, you can specify an auxiliary
  # command to be used for decompression.
  #
  # Returns a Reader instance.
  #
  def self.read_open_filename(filename, cmd = nil, raw = false)
    unless cmd.nil?
      cmd = locate_cmd(cmd)
    end

    ar = Reader.read_open_filename(filename, cmd, raw)
 
    if block_given?
      yield ar
      ar.close()
    else
      return ar
    end
  end

  ##
  #
  # Read archive from string. Libarchive automatically determines archive
  # format and compression scheme. Optionally, you can specify an auxiliary
  # command to be used for decompression.
  #
  # Returns a Reader instance.
  #
  def self.read_open_memory(string, cmd = nil, raw = false)
    unless cmd.nil?
      cmd = locate_cmd(cmd)
    end

    ar = Reader.read_open_memory(string, cmd, raw)

    if block_given?
      yield ar
      ar.close()
    else
      return ar
    end
  end

  ##
  #
  # Open filename for writing. Specify the compression format by passing one
  # of the <code>Archive::COMPRESSION_*</code> constants or optionally specify
  # an auxiliary program to use for compression. Use one of the
  # <code>Archive::FORMAT_*</code> constants to specify the archive format.
  # 
  # Returns a Writer instance.
  #
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

