Gem::Specification.new do |s|
  s.name = "libarchive-ruby-swig"
  s.version = "0.0.1"
  s.date = "2011-01-22"
  s.authors = ["Tobias Koch"]
  s.email = "tobias.koch@gmail.com"
  s.summary = "A SWIG wrapper around libarchive"
  s.description = "A SWIG wrapper providing access to the most-commonly used functionality in libarchive"
  s.homepage = "http://fixme.rubyforge.org"
  s.rubyforge_project = "libarchive-ruby-swig"
  s.extensions = [ "ext/libarchive-ruby-swig/extconf.rb" ]
  s.files = [ "lib/libarchive.rb",
    "ext/libarchive-ruby-swig/entry.cpp",
    "ext/libarchive-ruby-swig/entry.h",
    "ext/libarchive-ruby-swig/error.h",
    "ext/libarchive-ruby-swig/libarchive_swig.i",
    "ext/libarchive-ruby-swig/reader.cpp",
    "ext/libarchive-ruby-swig/reader.h" ]
end
