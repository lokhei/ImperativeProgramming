# Find the OS platform using the uname command.
Linux := $(findstring Linux, $(shell uname -s))
MacOS := $(findstring Darwin, $(shell uname -s))
Windows := $(findstring NT, $(shell uname -s))

# For native Windows only (not supported in our unit), add the .exe extension
ifdef Windows

hello: hello.c
	clang -std=c11 -Wall -pedantic -g hello.c -o hello.exe

# For Linux/MacOS/LinuxSubSystemForWindows10, include the advanced debugging options
else

hello: hello.c
	clang -std=c11 -Wall -pedantic -g hello.c -o hello \
	    -fsanitize=undefined -fsanitize=address
	./hello

square: square.c
	clang -std=c11 -Wall -pedantic -g square.c -o square \
	    -fsanitize=undefined -fsanitize=address
	./square

interest: interest.c
	clang -std=c11 -Wall -pedantic -g interest.c -o interest \
	    -fsanitize=undefined -fsanitize=address
	./interest

max: max.c
	clang -std=c11 -Wall -pedantic -g max.c -o max \
	    -fsanitize=undefined -fsanitize=address
	./max

min: min.c
	clang -std=c11 -Wall -pedantic -g min.c -o min \
	    -fsanitize=undefined -fsanitize=address
	./min

endif
