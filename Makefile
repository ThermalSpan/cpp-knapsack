# Created by Russell Bentley
# Copyright (c) 2016 Russell Wilhelm Bentley
# Distributed under the MIT License

# Directories
TEMPDIRS = build bin build/generator build/utility build/testsuite build/knapsack

# Source File Names
GENFILES = main genFunctions
UTILFILES = utilities 
KNAPFILES = main shared branchbound recurrence dynamic #minknap

# Compiler Stuff
CC = g++
CFLAGS = -std=c++11 -stdlib=libc++ -Wall -g

# Derived File Lists
GENOBJ = $(GENFILES:%=build/generator/%.obj)
UTILOBJ = $(UTILFILES:%=build/utility/%.obj)
KNAPOBJ = $(KNAPFILES:%=build/knapsack/%.obj)

# Targets
all: dirFile bin/knapsack bin/generator bin/polycase bin/polytest

dirFile:
	for dir in $(TEMPDIRS); do \
		mkdir -p $$dir ; \
	done
	@touch dirFile

bin/generator: $(GENOBJ) $(UTILOBJ)
	$(CC) $^ -o bin/generator

bin/knapsack: $(KNAPOBJ) $(UTILOBJ)
	$(CC) -g $^ -o bin/knapsack

bin/polycase: build/testsuite/polycase.obj $(UTILOBJ)
	$(CC) $^ -o bin/polycase

bin/polytest: build/testsuite/polytest.obj $(UTILOBJ)
	$(CC) $^ -o bin/polytest

build/%.obj : src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Phony Commands
.PHONY: style
style:
	astyle -A2 -s4 -xd -k3 -j $$(find src -type f -and -name *cpp -or -name *.h) 

.PHONY: install
install: bin/knapsack bin/generator bin/polycase bin/polytest
	cp bin/knapsack Tests/knapsack
	cp bin/generator Tests/generator
	cp bin/polycase Tests/polycase
	cp bin/polytest Tests/polytest

.PHONY: clean
clean:
	rm -f -r build bin dirFile $$(find . -type f -and -name *orig -or -name *aux -or -name *log -or -name *dSYM -or -name *swp -or -name *pdf) Tests/generator Tests/knapsack Tests/polycase Tests/polytest
