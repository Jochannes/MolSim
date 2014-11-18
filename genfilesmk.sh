#!/bin/sh
#
# Generate a file called files.mk containing all the names of the source files.
# This is neccessary for the Makefile to work correctly.
# 
#
# Best way: Run automatically in Eclipse via Project->Properties->Builders->New->Program

#echo "starting generation of files.mk... "


find src -name *.cpp -printf '%p\\\n' > files.mk.tmp
echo "SOURCES=\\" > files.mk
cat files.mk.tmp >> files.mk
rm files.mk.tmp


#echo "finished."


