J_HOME?=$(shell /usr/libexec/java_home)
INCLUDES = -I. -I../.. -I$(J_HOME)/include -I$(J_HOME)/include/linux -I$(J_HOME)/include/darwin

all: shared

shared:
	cc $(INCLUDES) -fPIC -c -g -Wall  LanguageStringUtils.c
	libtool -dynamic -lSystem LanguageStringUtils.o -o libLanguage.dylib
	
clean:
	rm -f *.o *.so *.class 