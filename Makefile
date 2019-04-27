NAME = jpTools
EXTENSION_DIR = $(shell php-config --extension-dir)
CP = cp -f
INI_DIR = /etc/php/conf.d/
EXTENSION = ${NAME}.so
INI = ${NAME}.ini

extension: jpTools.i jpTools.cpp utf8Utils.cpp utf8Utils.hpp
	swig -c++ -php7 -outdir out -o out/jpTools_wrap.cxx jpTools.i
	g++ -std=c++1z `php-config --includes` -lmecab -fpic -c out/jpTools_wrap.cxx utf8Utils.cpp jpTools.cpp
	g++ -lmecab -shared jpTools_wrap.o jpTools.o utf8Utils.o -o jpTools.so

install:		
	${CP} ${EXTENSION} ${EXTENSION_DIR}
	${CP} ${INI} ${INI_DIR}

clean:
	$(RM) -r out
	$(RM) *.o
	$(RM) *.so
	mkdir out

.PHONY: clean install