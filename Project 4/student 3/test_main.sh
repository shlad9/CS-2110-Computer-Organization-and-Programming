#!/bin/bash

# $1 is the in.txt file
# $2 is the expected output file
# $3 is the optional expected export file

# Build project
gcc -fno-asm -std=c99 -Wall -pedantic -Wextra -Werror -O0 -Wstrict-prototypes -Wold-style-definition -g project4.c main.c helper.c -o project4

# Clean up files
rm -f my_main_out.txt
rm -f case2_export.txt
rm -f diff.txt

# Run script
if [ $# == 3 ] || [ $# == 2 ] ; then
    ./project4 < $1 > my_main_out.txt
else
    echo "Incorrect number of args passed to test script"
    exit 1
fi
error=$?

function mydiff() { echo -e " [Actual]\t\t\t\t\t\t\t\t\t[Expected]"; diff -tyZwB --strip-trailing-cr $1 $2; }

# Check stdout output
mydiff my_main_out.txt $2 > diff.txt
error_stdin=$?
error_export=0

if [ ! $error_stdin -eq 0 ] ; then
    echo "There is a difference between the expected and actual stdouts"
    echo "If you're seeing weird characters, it may be caused by you outbounding arrays or something"
    echo ""
    cat diff.txt
    echo ""
    echo "These were the supplied inputs."
    echo "Note that the inputs (including newlines) do not appear in the diff output above!"
    echo "stdin:"
    cat $1
fi

# If there is an export file, check export output
if [ $# == 3 ] ; then
    mydiff case2_export.txt $3 > diff.txt
    error_export=$?

    if [ ! $error_export -eq 0 ] ; then
        echo "There is a difference between the expected and actual export files"
        echo "If you're seeing weird characters, it may be caused by you outbounding arrays or something"
        echo ""
        cat diff.txt
        echo ""
        echo "These were the supplied inputs."
        echo "Note that the inputs (including newlines) do not appear in the diff output above!"
        echo ""
        echo "stdin:"
        cat $1
    fi
fi

if [ $error_stdin -eq 0 ] && [ $error_export -eq 0 ]; then
    echo "Test passed"
    exit 0
fi

exit 1