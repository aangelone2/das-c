# Ensure bash is used
SHELL := bash
# Ensures 100% stopping if step in recipe fails
.SHELLFLAGS := -eu -o pipefail -c

# If a rule fails, its target file is deleted
.DELETE_ON_ERROR:

# Warning if using undefined make variables
MAKEFLAGS += --warn-undefined-variables
# Disables builtin rules (C...)
MAKEFLAGS += --no-builtin-rules




# Targets which are not supposed to generate
# a file with the same name
.PHONY: docs builds

idir := include
sdir := src
odir := obj
bdir := build
tdir := tests

headers := $(wildcard $(idir)/*.h)
sources := $(wildcard $(sdir)/*.c)
objects := $(patsubst $(sdir)/%.c, $(odir)/%.o, $(sources))

theaders := $(wildcard $(tdir)/*.h)
tsources := $(wildcard $(tdir)/*.c)
tobjects := $(patsubst $(tdir)/%.c, $(bdir)/%, $(tsources))

CC := gcc
CFLAGS := -std=c17 -O3 -Wfatal-errors\
					-Wall -Werror -Wextra -Wshadow -Wparentheses\
					-Wconversion -Wpedantic -pedantic -Wunused-result
INC := -I$(idir)
LIB := -L$(bdir) -ldas-c -lm


test: $(tobjects)
	@echo ''
	@echo 'Beginning testing'
	@echo ''
	cd $(bdir); ./01.test-count_fields
	cd $(bdir); ./02.test-file_info
	cd $(bdir); ./03.test-statistics
	cd $(bdir); ./04.test-parse
	cd $(bdir); ./05.test-clargs
	cd $(bdir); ./06.test-avs
	cd $(bdir); ./07.test-ave

	@echo 'All tests completed successfully'


# Rule to build test object files
$(tobjects): $(bdir)/%: $(tdir)/%.c $(theaders) lib
	$(CC) $(CFLAGS) $(INC) $< -o $@ $(LIB)


# Target, which executes the rule to build the library
build: lib


# Rule to build the library
lib: $(objects)
	@mkdir -p $(bdir)
	rm -fv $(bdir)/*.a
	ar rcs $(bdir)/libdas-c.a $(objects)


# Rule to build library object files
$(objects): $(odir)/%.o: $(sdir)/%.c $(headers)
	@mkdir -p $(odir)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@


docs:
	rm -rf html/
	doxygen doxygen.cnf


clean:
	rm -rf build/ html/ obj/
