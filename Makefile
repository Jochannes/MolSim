# This is a makefile template


# Compiler
# --------
CC=g++
#CC=icpc

include files.mk


# Compiler flags
# -------------------------------------------------------------------------
CFLAGS=-g -O3 -fopenmp
#CFLAGS=-g -O3 -ip -ipo -fast -openmp

# Linker flags
# ------------
LDFLAGS= -lxerces-c -llog4cxx -lcppunit -lpapi -fopenmp
#LDFLAGS= -lxerces-c -llog4cxx -lcppunit -lpapi -openmp

INCLUDES= -I./src -I./libxsd

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=MolSim

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@ 

clean:
	rm $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

