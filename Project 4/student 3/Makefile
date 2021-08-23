# Project4 (Intro to C) - CS2110: Fall 2020
# GCC flags from the syllabus (each flag described for the curious minds!)
# Flag info credit: https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html

CFLAGS = -std=c99					# Using the C99 standard
CFLAGS += -Wall						# This enables all the warnings about constructions that some users consider questionable, and that are easy to avoid (or modify to prevent the warning), even in conjunction with macros
CFLAGS += -pedantic					# Issue all the warnings demanded by strict ISO C and ISO C++; reject all programs that use forbidden extensions, and some other programs that do not follow ISO C and ISO C++
CFLAGS += -Wextra					# This enables some extra warning flags that are not enabled by -Wall
CFLAGS += -Werror					# Make all warnings into errors
CFLAGS += -O0						# Optimize even more. GCC performs nearly all supported optimizations that do not involve a space-speed tradeoff.
CFLAGS += -Wstrict-prototypes		# Warn if a function is declared or defined without specifying the argument types
CFLAGS += -Wold-style-definition	# Warn if an old-style function definition is used. A warning is given even if there is a previous prototype
CFLAGS += -g						# Generate debugging information

# Source files to be compiled together (for local command line testing)
CFILES = main.c project4.c helper.c

# Executable name
OBJNAME = project4

# Note: '@' added to disable echo on the command
project4:
	@ # Compile all source files with the given flags into the specified executable object!
	@ gcc -fno-asm $(CFLAGS) $(CFILES) -o $(OBJNAME)


clean:
	@ # Removing all sort of object files and executables
	@ rm -f $(OBJNAME) tests *.o *.out

.PHONY: project4 clean tests build_grader

##########################################################################################
# NOTE: AUTOGRADING BELOW

# Uses pkg-config to retrieve package information about check -- Unit Testing Framework
CHECK_LIBS = $(shell pkg-config --cflags --libs check)

# Source files for the autograder
GRADER_O_FILES = remove_doc_suite.o\
									append_suite.o\
									change_mode_suite.o\
									list_suite.o\
									macro_suite.o\
									new_doc_suite.o\
									import_suite.o\
									find_doc_suite.o\
									export_suite.o\
									test_entry.o\
									test_utils.o\
									test_helper.o # DO NOT LINK "helper.c"
STUDENT_FILES = project4.c

GRADER = $(patsubst %, grader/%,$(GRADER_O_FILES))

MAIN_GRADER = ./test_main.sh

# Build Autograder
tests:
	gcc -fno-asm -static $(CFLAGS) $(GRADER) $(STUDENT_FILES) $(CHECK_LIBS) -o tests

# To run a specific test case (or all similar to tests)
run-case: tests
	./tests $(TEST)

# To run test suite on main tests
run-main-tests:
	$(MAIN_GRADER) ./my_main_Tests/case1/case1_in.txt ./my_main_Tests/case1/case1_console_expected_out.txt
	$(MAIN_GRADER) ./my_main_Tests/case2/case2_in.txt ./my_main_Tests/case2/case2_console_expected_out.txt ./my_main_Tests/case2/case2_export_expected_out.txt

# To run gdb on testcase(s)
run-gdb: tests
	@ CK_FORK=no gdb --args ./tests $(TEST)
