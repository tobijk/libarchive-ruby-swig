require 'fileutils'

task :default => :build

source_files = Dir['ext/libarchive-ruby-swig/*.{cpp,h}']
file 'ext/libarchive-ruby-swig/archive.so' => source_files do
  Dir.chdir "ext/libarchive-ruby-swig/" do
    sh "ruby extconf.rb"
    sh "make"
  end
end
desc "build extension"
task :build => 'ext/libarchive-ruby-swig/archive.so'


desc "clean source tree"
task :clean do |t|
  Dir.chdir "ext/libarchive-ruby-swig/" do
    sh "make distclean" if File.exist? "Makefile"
  end

  [ 'doc', '*.gem' ].each do |glob|
    filelist = Dir.glob(glob)
    filelist.each do |entry|
      FileUtils.remove_entry_secure(entry) if entry
    end
  end
end


desc "generate a gem bundle"
task :gem do |t|
  sh "gem build libarchive-ruby-swig.gemspec"
end


namespace :doc do
  task :sanitize do |t|
    Dir.chdir "ext/libarchive-ruby-swig/" do
      sh "ruby extconf.rb"
      wrapper_code = IO.read('libarchive_wrap.cxx')
      wrapper_code.slice! /^.*\/\*\s+---\s+WRAPPER CODE START\s+---\s+\*\//m
      File.open('libarchive_wrap_doc.cxx', 'w+') { |f| f.write(wrapper_code) }
    end
  end

  desc "generate sanitized rdoc documentation"
  task :rdoc => :sanitize do |t|
    sh 'rdoc --title="libarchive-ruby-swig" -m README README LICENSE ' +
       'Changelog lib/libarchive_rs.rb lib/libarchive_doc.rb ' +
       'ext/libarchive-ruby-swig/libarchive_wrap_doc.cxx'

    Dir.chdir "ext/libarchive-ruby-swig/" do
      sh "make distclean"
    end
  end

  desc "generate sanitized yard documentation"
  task :yard => :sanitize do |t|
    sh 'yard --title="libarchive-ruby-swig" -r README lib/libarchive_rs.rb ' +
       'lib/libarchive_doc.rb ' +
       ' - LICENSE Changelog'

    Dir.chdir "ext/libarchive-ruby-swig/" do
      sh "make distclean"
    end
  end

end


desc "run the test suite"
task :test => :build do |t|
  Dir.chdir "test" do
    sh "ruby testsuite.rb"
  end
end
