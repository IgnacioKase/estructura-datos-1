MAIN = main
MAIN_SOURCE = main.c
MAIN2 = main2
MAIN2_SOURCE = main2.c
MAIN_INCLUDE = tablahash.o
MAIN2_INCLUDE = tablahash.o
TABLAHASH = tablahash.c
CFLAGS = -Wall -Wextra -Werror -std=c99 -g

OSFLAG 				:=
ifeq ($(OS),Windows_NT)
	OSFLAG +=WIN32
else
	UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	OSFLAG +=LINUX
endif
ifeq ($(UNAME_S),Darwin)
	OSFLAG +=OSX
endif
endif

OSFLAG := $(firstword $(subst :, ,$(OSFLAG)))

ifeq ($(OSFLAG), WIN32)
PYTHON = $(PYTHON_INTERPRETE)
endif
ifeq ($(OSFLAG), LINUX)
PYTHON = $(PYTHON_INTERPRETE_LINUX)
endif
ifeq ($(OSFLAG), OSX)
PYTHON = $(PYTHON_INTERPRETE_DARWIN)
endif

all: main2 clean

main: $(MAIN_SOURCE) $(MAIN_INCLUDE)
	gcc $(CFLAGS) -o $(MAIN) $(MAIN_SOURCE) $(MAIN_INCLUDE)

main2: $(MAIN2_SOURCE) $(MAIN2_INCLUDE)
	gcc $(CFLAGS) -o $(MAIN2) $(MAIN2_SOURCE) $(MAIN2_INCLUDE)

tablahash.o: $(TABLAHASH)
	gcc $(CFLAGS) -c $(TABLAHASH)

clean:
ifeq ($(OSFLAG), WIN32)
	del *.o
endif
ifeq ($(OSFLAG), LINUX)
	rm *.o
endif
ifeq ($(OSFLAG), OSX)
	rm *.o
endif
