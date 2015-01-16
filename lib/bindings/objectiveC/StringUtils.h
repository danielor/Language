#import <Foundation/Foundation.h>

/**
@interface StringUtils
@brief A collection of char utils
*/
@interface StringUtils : NSObject{

  /**
  @function length
  @brief Return the length of a string
  @param str The string to check if the first character is
  a string
  @param encoding The encoding of the string
  */
  +(NSUInteger) length:(NSString*)str encoding:(NSUInteger)encoding;

  /**
  @function lengthEscaped
  @brief Find the length with escaped string that need to be
  translated into a differente encoding
  @param str The string check if the first character satisfies
  the natural number
  @param encoding The encoding of the string
  @param escaped The identifier of an escaped string
  @param escapedEncoding The escaped encoding of a string
  @param endString The end string of the escaped length
  */
  +(NSUInteger) lengthEscaped:(NSString*)str encoding:(NSUInteger)encoding
        escaped:(NSString*)escaped escapedEncoding:(NSUInteger)escapedEncoding
        endString:(NSString*)endString;

  /**
  @function isNaturalNumber
  @brief Check if the entire string is a natural number
  @param str The string to check if the first character satisifies
  the romance alphabet condition
  */
  +(BOOL) isNaturalNumber:(NSString*)str encoding:(NSUInteger)encoding;

  /**
  @function isHexNumber
  @brief Check if entire string is a hex number
  @param str The string to check if the first character is valid
  @param encoding The encoding of the string
  */
  +(BOOL) isHexNumber:(NSString*)str encoding:(NSUInteger)encoding;


}
