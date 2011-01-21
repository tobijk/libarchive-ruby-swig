require 'libarchive_swig'

module Archive

  include Libarchive_swig

  class Libarchive_swig::Entry
    alias :directory? :is_directory
    alias :symbolic_link? :is_symbolic_link
    alias :block_special? :is_block_special
    alias :character_special? :is_character_special
    alias :fifo? :is_fifo
    alias :socket? :is_socket
  end

  class Libarchive_swig::Reader
 
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

  def self.read_open_filename(filename)
    ar = Reader.read_open_filename(filename)
 
    if block_given?
      yield ar
    else
      return ar
    end
  end

end
