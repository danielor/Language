{
  	'targets': [
    	{
     	    'target_name': 'Language',
			"sources":[
				"bindings/javascript/Language.cc",
				"bindings/javascript/objects/StringUtils.cc",
				"bindings/javascript/objects/CharUtils.cc"
			],
			"include_dirs":[
			    "lib/",
			    "bindings/javascript/objects/"
			]
		},
	],

}