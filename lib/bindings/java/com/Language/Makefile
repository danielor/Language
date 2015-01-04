J_HOME?=$(shell /usr/libexec/java_home)
INCLUDES = -I. -I../../../.. -I$(J_HOME)/include -I$(J_HOME)/include/linux -I$(J_HOME)/include/darwin

all: shared

shared:
	cc $(INCLUDES) -fPIC -c  LanguageStringUtils.c
	cc $(INCLUDES) -fPIC -c  LanguageCharUtils.c
	libtool -dynamic -lSystem LanguageStringUtils.o LanguageCharUtils.o -o libLanguage.dylib
	
clean:
	rm -f *.o *.so *.class 