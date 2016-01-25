# Created by Russell Bentley
# Copyright (c) 2016 Russell Wilhelm Bentley
# Distributed under the MIT License

# Directories
TEMPDIRS = build bin build/generator build/branchbound build/utility build/recurrence build/testsuite

# Source File Names
GENFILES = main genFunctions
BRBOFILES = main search
RECUFILES = main search
UTILFILES = utilities knapsack

# Header File Names
GENHEADERS = genFunctions
BRBOHEADERS = search
RECUHEADERS = search

# Compiler Stuff
CC = g++
CFLAGS = -std=c++11 -stdlib=libc++ -Wall

# Derived File Lists
GENSRC = $(GENFILES:%=src/generator/%.cpp)
GENOBJ = $(GENFILES:%=build/generator/%.obj)

BRBOSRC = $(BRBOFILES:%=src/branchbound/%.cpp)
BRBOOBJ = $(BRBOFILES:%=build/branchbound/%.obj)

RECUSRC = $(RECUFILES:%=src/recurrence/%.cpp)
RECUOBJ = $(RECUFILES:%=build/recurrence/%.obj)

UTILSRC = $(UTILFILES:%=src/utility/%.cpp)
UTILOBJ = $(UTILFILES:%=build/utility/%.obj)

# Targets
all: dirFile bin/generator bin/branchbound  bin/recurrence bin/polycase

dirFile:
	for dir in $(TEMPDIRS); do \
		mkdir -p $$dir ; \
	done
	@touch dirFile

bin/generator: $(GENOBJ) $(UTILOBJ)
	$(CC) $^ -o bin/generator

bin/branchbound: $(BRBOOBJ) $(UTILOBJ)
	$(CC) $^ -o bin/branchbound

bin/recurrence: $(RECUOBJ) $(UTILOBJ)
	$(CC) $^ -o bin/recurrence

bin/polycase: build/testsuite/polycase.obj $(UTILOBJ)
	$(CC) $^ -o bin/polycase

build/%.obj : src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Phony Commands
.PHONY: style
style:
	astyle -A2 -s4 -xd -k1 -j $$(find src -type f -name *cpp) $$(find src -type f -name *h)

.PHONY: test
test: all
	/bin/generator
	/bin/branchbound
	/bin/recurrence

.PHONY: install
install: bin/branchbound bin/generator bin/recurrence bin/polycase
	cp bin/branchbound Tests/branchbound
	cp bin/generator Tests/generator
	cp bin/recurrence Tests/recurrence
	cp bin/polycase Tests/polycase

.PHONY: clean
clean:
	rm -f -r build bin dirFile *.dSYM $$(find src -type f -name *orig) Tests/generator Tests/branchbound Tests/recurrence Tests/polycase

