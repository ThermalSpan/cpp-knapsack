# Created by Russell Bentley
# Copyright (c) 2016 Russell Wilhelm Bentley
# Distributed under the MIT License

# Directories
TEMPDIRS = build bin build/generator build/branchbound build/utility

# Source File Names
GENFILES = main genFunctions
BRBOFILES = main search
UTILFILES = utilities knapsack

# Header File Names
GENHEADERS = genFunctions
BRBOHEADERS = search

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

build/%.obj : src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Phony Commands
.PHONY: style
style:
	astyle -A2 -s4 -xd -k1 -j $(GENSRC) $(BRBOSRC) $(BRBOHEADERS:%=src/branchbound/%.h) $(UTILSRC) $(UTILFILES:%=src/utility/%.h) $(GENSRC) $(GENHEADERS:%=/src/generator/%.h)

.PHONY: test
test: all
	./bin/generator
	./bin/branchbound

.PHONY: install
install: bin/branchbound
	cp bin/branchbound Tests/branchbound
	cp bin/generator Tests/generator

.PHONY: clean
clean:
	rm -f -r build bin dirFile *.dSYM src/*.orig Tests/generator Tests/branchbound

