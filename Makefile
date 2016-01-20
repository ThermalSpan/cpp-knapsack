# Created by Russell Bentley
# Copyright (c) 2016 Russell Wilhelm Bentley
# Distributed under the MIT License

# Directories
TEMPDIRS = build bin build/generator build/branchbound build/utility

# File Lists
GENFILES = main
BRBOFILES = main
UTILFILES = utilities

# Compiler Stuff
CC = g++
CFLAGS = -std=c++11 -stdlib=libc++ -Wall

# Derived File Lists
GENSRC = $(GENFILES:%=src/generator/%.cpp)
GENOBJ = $(GENFILES:%=build/generator/%.obj)

BRBOSRC = $(BRBOFILES:%=src/branchbound/%.cpp)
BRBOOBJ = $(BRBOFILES:%=build/branchbound/%.obj)

UTILSRC = $(UTILFILES:%=src/utility/%.cpp)
UTILOBJ = $(UTILFILES:%=build/utility/%.obj)

# Targets
all: dirFile bin/generator bin/branchbound 

dirFile:
	for dir in $(TEMPDIRS); do \
		mkdir -p $$dir ; \
	done
	@touch dirFile

bin/generator: $(GENOBJ) $(UTILOBJ)
	$(CC) $^ -o bin/generator

bin/branchbound: $(BRBOOBJ) $(UTILOBJ)
	$(CC) $^ -o bin/branchbound

build/%.o: src/%.cpp
	$(CC) $(CFLAGS) $< -o $@

build/generator/main.obj: src/generator/%.cpp
	$(CC) $(CFLAGS) $< -o $@

# Phony Commands
.PHONY: style
style:
	astyle -A2 -s4 -xd -k1 -j $(GENSRC) $(BRBOSRC) $(UTILSRC) $(UTILSRC:%=src/utility/%.h)

.PHONY: clean
clean:
	rm -f -r build bin dirFile *.dSYM *.orig


