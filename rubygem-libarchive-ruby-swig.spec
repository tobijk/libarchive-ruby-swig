%define ruby_sitelib %(ruby -rrbconfig -e "puts Config::CONFIG['sitelibdir']")
%define gemdir %(ruby -rubygems -e 'puts Gem::dir' 2>/dev/null)
%define gemname libarchive-ruby-swig
%define geminstdir %{gemdir}/gems/%{gemname}-%{version}

Summary: Ruby bindings to libarchive
Name: rubygem-%{gemname}
Version: 0.5.7
Release: 1%{?dist}
Group: Development/Languages
License: BSD
URL: http://libarchive-rs.rubyforge.org
Source0: http://rubygems.org/gems/%{gemname}-%{version}.gem
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Requires: rubygems
BuildRequires: rubygems
BuildRequires: libarchive-devel
BuildRequires: ruby-devel
BuildRequires: swig
Provides: rubygem(%{gemname}) = %{version}

%description
libarchive-ruby-swig provides Ruby bindings to libarchive using SWIG. The gem
allows you to read and write compressed archives in a variety of formats.

%prep

%build

%install
rm -rf %{buildroot}
mkdir -p %{buildroot}%{gemdir}
gem install --local --install-dir %{buildroot}%{gemdir} \
            --force --rdoc %{SOURCE0}

%clean
rm -rf %{buildroot}

%files
%defattr(-, root, root, -)
%{gemdir}/gems/%{gemname}-%{version}/
%doc %{gemdir}/doc/%{gemname}-%{version}
%{gemdir}/cache/%{gemname}-%{version}.gem
%{gemdir}/specifications/%{gemname}-%{version}.gemspec

%changelog
* Mon Nov 07 2011 Tobias Koch <tobias@tobijk.de> - 0.5.7-1
- Update to version 0.5.7

* Wed Feb 23 2011 Greg Blomquist <gblomqui@blomquisg.usersys.redhat.com> - 0.5.3-1
- Initial package
