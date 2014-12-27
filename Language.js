var bindings = require('./build/Release/Language.node');

// Export the high level objects associated with
// the Language package
module.exports.StringUtils = bindings.StringUtils;
module.exports.CharUtils = bindings.CharUtils;