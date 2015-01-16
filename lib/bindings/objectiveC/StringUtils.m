#import "stringUtils.h"
#import "CharUtils.h"

@implementation CharUtils

+(BOOL) length:(NSString*)str encoding:(NSUInteger)encoding{
  const char * buffer = [str UTF8String];
  return len(str, encoding);
}

+(BOOL) lengthEscaped:(NSString*)str encoding:(NSUInteger)encoding
    escaped:(NSString*)escaped escapedEncoding:(NSUInteger)escapedEncoding
    endString:(NSString*)endString{
  const char * buffer = [str UTF8String];
  const char * escaped = [str UTF8String];
  const char * end = [str UTF8String];

}

+(BOOL) isNaturalNumber:(NSString*)str encoding:(NSUInteger)encoding{
  const char * buffer = [str UTF8String];
  return isNaturalNumberSequence(buffer, encoding);
}

+(BOOL) isValidChar:(NSString*)str encoding:(NSUInteger)encoding{
  const char * buffer = [str UTF8String];
  int isHex = isValidCharacter(buffer, enecoding);
  if(isHex == 1){
    return YES;
  }else{
    return NO;
  }
}

+(BOOL) isInAlphabetChar:(NSString*)str encoding:(NSUInteger)encoding language:(NSUInteger)language{
  const char * buffer = [str UTF8String];
  int isHex = isInAlphabet(buffer, enecoding, language);
  if(isHex == 1){
    return YES;
  }else{
    return NO;
  }
}

@end
