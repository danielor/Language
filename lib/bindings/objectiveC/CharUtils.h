#import <Foundation/Foundation.h>

/**
@interface CharUtils
@brief A collection of char utils
*/
@interface CharUtils : NSObject{

/**
@function isHexNumberChar
@brief Check if the first character of a string conforms to the
hex range of characters(0-9,a-f,A-F)
@param str The string to check if the first character is
a string
@param encoding The encoding of the string
*/
+(BOOL) isHexNumberChar:(NSString*)str encoding:(NSUInteger)encoding;

/**
@function isNaturalNumberChar
@brief Check if the first character of a string conforms to the
natural numbers(0-9)
@param str The string check if the first character satisfies
the natural number
@param encoding The encoding of the string
*/
+(BOOL) isNaturalNumberChar:(NSString*)str encoding:(NSUInteger)encoding;

/**
@function isInRomanceAlphabetChar
@brief Check if the first character of a string confirms to the
romance alphabet(a-z,A-Z)
@param str The string to check if the first character satisifies
the romance alphabet condition
*/
+(BOOL) isInRomanceAlphabetChar:(NSString*)str encoding:(NSUInteger)encoding;

/**
@function isValidChar
@brief Check if the first character of a string is valid
@param str The string to check if the first character is valid
@param encoding The encoding of the string
*/
+(BOOL) isValidChar:(NSString*)str encoding:(NSUInteger)encoding;

/**
@function isInAlphabetChar
@brief Check if the first character of a string is in an alphabet
@param str The string to check if the first character is valid
@param encoding The encoding of the string
@param language The language of the string
*/
+(BOOL) isInAlphabetChar:(NSString*)str encoding:(NSUInteger)encoding language:(NSUInteger)language;
}
