#import "stringUtils.h"
#import "CharUtils.h"

@implementation CharUtils

+(BOOL) isHexNumberChar:(NSString*)str encoding:(NSUInteger)encoding{
  const char * buffer = [str UTF8String];
  int isHex = isHex(buffer, enecoding);
  if(isHex == 1){
    return YES;
  }else{
    return NO;
  }
}

+(BOOL) isNaturalNumberChar:(NSString*)str encoding:(NSUInteger)encoding{
  const char * buffer = [str UTF8String];
  int isHex = isNumber(buffer, enecoding);
  if(isHex == 1){
    return YES;
  }else{
    return NO;
  }
}

+(BOOL) isInRomanceAlphabetChar:(NSString*)str encoding:(NSUInteger)encoding{
  const char * buffer = [str UTF8String];
  int isHex = isHex(buffer, enecoding);
  if(isHex == 1){
    return YES;
  }else{
    return NO;
  }
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
