desc "show available rake tasks"
task :default do |t|
  puts "The following rake tasks are available\n"
  sh "rake -T"
end


desc "generate a gem bundle"
task :gem do |t|
  sh "gem build libarchive-ruby-swig.gemspec"
end


desc "generate sanitized rdoc documentation"
task :doc do |t|
  Dir.chdir "ext/libarchive-ruby-swig/" do
    sh "ruby extconf.rb"
    wrapper_code = File.open('libarchive_wrap.cxx', 'r').read
    wrapper_code.slice! /^.*\/\*\s+---\s+WRAPPER CODE START\s+---\s+\*\//m
    File.open('libarchive_wrap.cxx', 'w+').write(wrapper_code)
  end

  sh 'rdoc --title="Libarchive/Ruby/SWIG" -m README README LICENSE ' +
     'Changelog lib/libarchive_rs.rb ' +
     'ext/libarchive-ruby-swig/libarchive_wrap.cxx'

  Dir.chdir "ext/libarchive-ruby-swig/" do
    sh "make distclean"
  end
end


desc "run the test suite"
task :test do |t|
  Dir.chdir "test" do
    sh "ruby testsuite.rb"
  end
end
