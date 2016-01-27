# Created by Russell Bentley
# Copyright (c) 2016 Russell Wilhelm Bentley
# Distributed under the MIT License

# Directories
TEMPDIRS = build bin build/generator build/utility build/testsuite build/knapsack

# Source File Names
GENFILES = main genFunctions
UTILFILES = utilities 
KNAPFILES = main shared branchbound recurrence dynamic

# Compiler Stuff
CC = g++
CFLAGS = -std=c++11 -stdlib=libc++ -Wall

# Derived File Lists
GENOBJ = $(GENFILES:%=build/generator/%.obj)
UTILOBJ = $(UTILFILES:%=build/utility/%.obj)
KNAPOBJ = $(KNAPFILES:%=build/knapsack/%.obj)

# Targets
all: dirFile bin/knapsack bin/generator bin/polycase

dirFile:
	for dir in $(TEMPDIRS); do \
		mkdir -p $$dir ; \
	done
	@touch dirFile

bin/generator: $(GENOBJ) $(UTILOBJ)
	$(CC) $^ -o bin/generator

bin/knapsack: $(KNAPOBJ) $(UTILOBJ)
	$(CC) $^ -o bin/knapsack

bin/polycase: build/testsuite/polycase.obj $(UTILOBJ)
	$(CC) $^ -o bin/polycase

build/%.obj : src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Phony Commands
.PHONY: style
style:
	astyle -A2 -s4 -xd -k1 -j $$(find src -type f -name *cpp) $$(find src -type f -name *h)

.PHONY: install
install: bin/knapsack bin/generator bin/polycase
	cp bin/branchbound Tests/knapsack
	cp bin/generator Tests/generator
	cp bin/polycase Tests/polycase

.PHONY: clean
clean:
	rm -f -r build bin dirFile *.dSYM $$(find src -type f -name *orig) Tests/generator Tests/knapsack Tests/polycase
