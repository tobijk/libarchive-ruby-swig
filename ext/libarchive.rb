require 'libarchive_swig'

include Libarchive_swig

class ArchiveEntry

  alias :directory? :is_directory
  alias :symbolic_link? :is_symbolic_link
  alias :block_special? :is_block_special
  alias :character_special? :is_character_special
  alias :fifo? :is_fifo
  alias :socket? :is_socket

end


class Archive

  def self.read_open_filename(filename)
    ar = Archive.read_open_filename_helper(filename)

    if block_given?
      yield ar
    else
      return ar
    end
  end

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
