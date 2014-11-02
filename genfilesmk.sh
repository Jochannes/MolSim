#!/bin/sh
#
# Generate a file called files.mk containing all the names of the source files.
# This is neccessary for the Makefile to work correctly.
# 

echo "starting generation files.mk... "


find src -name *.cpp -printf '%p\\\n' > files.mk.tmp
echo "SOURCES=\\" > files.mk
cat files.mk.tmp >> files.mk
rm files.mk.tmp


echo "finished."


