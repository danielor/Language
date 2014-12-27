{
  	'targets': [
    	{
     	    'target_name': 'Language',
			"sources":[
				"lib/bindings/javascript/Language.cc",
				"lib/bindings/javascript/objects/StringUtils.cc",
				"lib/bindings/javascript/objects/CharUtils.cc"
			],
			"include_dirs":[
			    "lib/",
			    "lib/bindings/javascript/objects/"
			]
		},
	],

}