NAME = jpTools
INI_DIR = /etc/php.d/
EXTENSION_DIR = $(shell php-config --extension-dir)
EXTENSION = ${NAME}.so
INI = ${NAME}.ini
COMPILER = clang
LINKER = clang
COMPILER_FLAGS = -Wall -c -O3 -std=c++11 -fpic -o
LINKER_FLAGS = -shared
LINKER_DEPENDENCIES = -lphpcpp -lmecab
RM = rm -f
CP = cp -f
MKDIR = mkdir -p
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)

all: ${OBJECTS} ${EXTENSION}

${EXTENSION}:	${OBJECTS}
	${LINKER} ${LINKER_FLAGS} -o $@ ${OBJECTS} ${LINKER_DEPENDENCIES}

${OBJECTS}:
	${COMPILER} ${COMPILER_FLAGS} $@ ${@:%.o=%.cpp}

install:		
	${CP} ${EXTENSION} ${EXTENSION_DIR}
	${CP} ${INI} ${INI_DIR}
				
clean:
	${RM} ${EXTENSION} ${OBJECTS}
