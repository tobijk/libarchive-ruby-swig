#
# This file is part of "libarchive-ruby-swig", a simple SWIG wrapper around
# libarchive.
#
# Copyright 2011, Tobias Koch <tobias.koch@gmail.com>
# 
# libarchive-ruby-swig is licensed under a simplified BSD License. A copy of the
# license text can be found in the file LICENSE.txt distributed with the source.
#

#
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

    private

    def self.new()
    end
  end

  class Entry

    ##
    #
    # Is Entry a regular file?
    #
    def is_file
    end

    ##
    #
    # Is Entry a directory?
    #
    def is_directory
    end

    ##
    #
    # Is Entry a symbolic link?
    #
    def is_symbolic_link
    end

    ##
    #
    # Is Entry a block device?
    #
    def is_block_special
    end

    ##
    #
    # Is Entry a char device?
    #
    def is_character_special
    end

    ##
    #
    # Is Entry a fifo?
    #
    def is_fifo
    end

    ##
    #
    # Is Entry a socket?
    #
    def is_socket
    end

    ##
    #
    # Is Entry a hardlink?
    #
    def is_hardlink
    end

    ##
    #
    # Returns the filetype bits for entry.
    #
    def filetype
    end

    ##
    #
    # Use one of the <code>Archive::ENTRY_*</code> to specify the filetype of
    # the Entry.
    #
    def set_filetype(filetype)
    end

    ##
    #
    # Device major number of device on which this Entry resided. This field
    # will not be available in most cases and is, in any case,
    # platform-specific.
    #
    def devmajor
    end

    ##
    #
    # Sets the device major number of the device on which this Entry resides. This
    # field will not be availabla in most cases and is, in any case,
    # platform-specific.
    #
    def set_devmajor(devmajor)
    end

    ##
    #
    # Device minor number of device on which this Entry resided. This field
    # will not be available in most cases and is, in any case,
    # platform-specific.
    #
    def devminor
      return numeric_result
    end

    ##
    #
    # Sets the device minor number of the device on which this Entry resides. This
    # field will not be availabla in most cases and is, in any case,
    # platform-specific.
    #
    def set_devminor(devminor)
    end

    ##
    #
    # Returns the atime of the saved Entry as a timestamp since epoch.
    #
    def atime
    end

    ##
    #
    # Sets the atime of the saved Entry from a timestamp.
    #
    def atime(atime)
    end

    ##
    #
    # Resets the Entry.
    #
    def clear
    end

    ##
    #
    # Returns an exact clone of Entry.
    #
    Entry *clone();

    ##
    #
    # Device id of the device on which entry resided. This is usually unused
    # and, in any case, platform-specific.
    #
    def dev
    end

    ##
    #
    # Sets the device id of the device on which entry resided. This is usually
    # unused and, in any case, platform-specific.
    #
    def set_dev(dev)
    end

    ##
    #
    # Group id of the Entry.
    #
    def gid
    end

    ##
    #
    # Sets the group id of the Entry.
    #
    def set_gid(gid)
    end

    ##
    #
    # Group name of the Entry.
    #
    def gname
    end

    ##
    #
    # Sets the group name of the Entry.
    #
    def set_gname(gname)
    end

    ##
    #
    # Path of file this entry was hardlinked to.
    #
    def hardlink
    end

    ##
    #
    # Sets the path to the file this entry is hard-linked to.
    #
    def set_hardlink(path)
    end

    ##
    #
    # Inode of Entry.
    #
    def ino
    end

    ##
    #
    # Sets the inode of Entry.
    #
    def set_ino(ino)
    end

    ##
    #
    # Permission bits and filetype of entry
    #
    def mode
    end

    ##
    #
    # Sets the permission bits (and/or filetype) of Entry.
    #
    def set_mode(mode)
    end

    ##
    #
    # Returns the mtime of the saved Entry as a timestamp since epoch.
    #
    def mtime
    end

    ##
    #
    # Sets the mtime of the saved Entry from a timestamp.
    #
    def set_mtime(mtime)
    end

    ##
    #
    # Number of hard links to this Entry.
    #
    def nlink
    end

    ##
    #
    # Sets the number of hard links to this Entry.
    #
    def set_nlink(num_links)
    end

    ##
    #
    # Returns the pathname of this Entry.
    #
    def pathname
    end

    ##
    #
    # Sets the pathname of this Entry.
    #
    def set_pathname(pathname)
    end

    ##
    #
    # The dev major number of the device this Entry represents.
    #
    def rdevmajor
    end

    ##
    #
    # Sets the dev major number of the device this Entry represents.
    #
    def set_rdevmajor(devmajor)
    end

    ##
    #
    # The dev minor number of the device this Entry represents.
    #
    def rdevminor
    end

    ##
    #
    # Sets the dev minor number of the device this Entry represents.
    #
    def set_rdevminor(devminor)
    end

    ##
    #
    # Size of the Entry. In case Entry is a symlink, returns the size of
    # symlink's target name.
    #
    def size
    end

    ##
    #
    # Sets the size of the Entry. In case Entry is a symlink, this should
    # be the length of the string set with <code>symlink=</code>.
    #
    def set_size()
    end

    ##
    #
    # Returns the rarget of a symlink Entry.
    #
    def symlink
    end

    ##
    #
    # Sets the target of a symlink Entry.
    #
    def set_symlink(path)
    end

    ##
    #
    # The user id of this Entry.
    #
    def uid
    end

    ##
    #
    # Sets the user id of this Entry.
    #
    def set_uid(uid)
    end

    ##
    #
    # The owner name of this entry.
    #
    def uname
    end

    ##
    #
    # Sets the owner name of this Entry.
    #
    def set_uname(uname)
    end

    private

    def self.new()
    end
  end

  class Reader

    ##
    #
    # Use <code>Archive::read_open_filename</code> instead.
    #
    def self.read_open_filename(filename, cmd = nil)
    end

    ##
    #
    # Use <code>Archive::read_open_memory</code> instead.
    #
    def self.read_open_memory(string, cmd = nil)
    end

    ##
    #
    # Releases all resources associated with the Reader object.
    #
    def close()
    end

    ##
    #
    # Returns the next Entry meta data object in the Archive.
    #
    def next_header()
    end

    private

    def read_data_helper(len)
    end

    def self.new()
    end

  end

  class Writer

    ##
    #
    # Use Archive::write_open_filename instead.
    #
    #
    def self.write_open_filename(filename, compression, format)
    end

    ##
    #
    # Releases all resources associated with the Writer object.
    #
    def close()
    end

    ##
    #
    # Creates a new Entry. An Entry holds the meta data for an item stored in
    # an Archive, such as filetype, mode, owner, etc. It is typically populated
    # by a call to <code>copy_stat</code>. It is written before the actual data.
    #
    def new_entry()
    end

    ##
    #
    # Write Entry meta data to Archive.
    #
    def write_header(entry)
    end

    private

    def self.new()
    end

    def new_entry_helper()
    end

    def write_data_helper()
    end

  end

end
