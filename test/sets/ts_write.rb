require 'libarchive_rs'
require 'tmpdir'
require 'test/unit'

class TS_WriteArchive < Test::Unit::TestCase

  CONTENT_SPEC = [
    ['test/', 'directory', 0755, nil ],
    ['test/b/', 'directory', 0755, nil ],
    ['test/b/c/', 'directory', 0755, nil ],
    ['test/b/c/c.dat', 'file', 0600, "\266\262\v_\266\243\305\3601\204\277\351\354\265\003\036\036\365f\377\210\205\032\222\346\370b\360u\032Y\301" ],
    ['test/b/c/d/', 'directory', 0711, nil ],
    ['test/b/c/d/d.dat', 'symbolic_link', 0777, "../c.dat" ],
    ['test/b/b.dat', 'file', 0640, "s&\245\354(M\331=\270\000!s\355\240\252\355'N\304\343\bY\317\t\274\210\3128\321\347\234!" ],
    ['test/a.dat', 'file', 0777, "\021\216\231Y\354\236\271\372\336\213\224R\211{D{\277\262\304\211xu\330\\\275@~\035\vSRM" ]
  ]

  def test_end_to_end_write_read_tar_gz
    Dir.mktmpdir do |dir| 
      Archive.write_open_filename(dir + '/test.tar.gz',
        Archive::COMPRESSION_GZIP, Archive::FORMAT_TAR) do |ar|
        write_content(ar)
      end

      verify_content(dir + '/test.tar.gz')
    end 
  end

  def test_end_to_end_write_read_tar_gz_with_external_gzip
    Dir.mktmpdir do |dir| 
      Archive.write_open_filename(dir + '/test.tar.gz', 'gzip',
        Archive::FORMAT_TAR) do |ar|
        write_content(ar)
      end

      verify_content(dir + '/test.tar.gz')
    end 
  end

  def test_implicit_hardlink_handling
    Dir.mktmpdir do |dir|
      Dir.mkdir(dir + '/test')
      File.open(dir + '/test/a.dat', 'wb+') { |f| f.write("This is a test.\n") }
      File.link(dir + '/test/a.dat', dir + '/test/b.dat')

      ar = Archive.write_open_filename(dir + '/test.tar.gz',
          Archive::COMPRESSION_GZIP, Archive::FORMAT_TAR)

      Dir.glob(dir + '/test/**/*').sort.each do |fn|
        entry = ar.new_entry
        entry.copy_stat(fn)
        entry.pathname = fn
        ar.write_header(entry)

        if entry.file?
          open(fn) do |f|
            ar.write_data { f.read(1024) }
          end
        end

        # check that b.dat is turned into link to a.dat
        if File.basename(fn) == "b.dat"
          assert entry.hardlink?
          assert_equal dir + '/test/a.dat', entry.hardlink
        end
      end

      ar.close()
    end
  end

  private

  def write_content(ar)
    content_spec_idx = 0

    while content_spec_idx < CONTENT_SPEC.size()
      entry_path, entry_type, entry_mode, entry_content = \
        CONTENT_SPEC[content_spec_idx]

      ar.new_entry do |entry|
        entry.pathname = entry_path
        entry.mode = entry_mode
        entry.filetype = eval "Archive::ENTRY_#{entry_type.upcase}"
        entry.size = entry_content.size if entry_content
        entry.symlink = entry_content if entry_type == 'symbolic_link'
        entry.atime = Time.now.to_i
        entry.mtime = Time.now.to_i
        ar.write_header(entry)

        if entry_type == 'file'
          ar.write_data(entry_content)
        end
      end

      content_spec_idx += 1
    end
  end

  def verify_content(filename)
    Archive.read_open_filename(filename) do |ar|
      content_spec_idx = 0

      while entry = ar.next_header
        expect_pathname, expect_type, expect_mode, expect_content =\
          CONTENT_SPEC[content_spec_idx]

        assert_equal expect_pathname, entry.pathname
        assert_equal entry.send("#{expect_type}?"), true
        assert_equal expect_mode, (entry.mode & 07777)

        if entry.symbolic_link?
          assert_equal expect_content, entry.symlink
        elsif entry.file?
          content = ar.read_data(1024)
          assert_equal expect_content, content
        end

        content_spec_idx += 1
      end
    end
  end

end
