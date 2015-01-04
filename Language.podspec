Pod::Spec.new do |s|
	s.name = 'Language'
	s.version = '0.01'
	s.summary = 'A common interface to common problems'
	s.homepage = 'https://github.com/danielor/Language'
	s.author = 'Daniel Ortiz'
	s.license = 'Apache'
	s.source = { :git => 'https://github.com/danielor/Language.git', :tag => 'v3.1.0' }
	s.source_files = 'lib/*.h', 'lib/bindings/objectiveC/.{h,m}'