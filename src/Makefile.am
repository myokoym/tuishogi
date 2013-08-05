lib_LTLIBRARIES = libtuishogi.la

LDFLAGS = -no-undefined

libtuishogi_la_SOURCES = tuishogi.cpp

GXX = g++
LIBS = -losl
SRCS = tuishogi.cpp
DEST_DIR = ../bin
DEST_NAME = tuishogi

tuishogi: $(SRCS)
	$(GXX) -o $(DEST_DIR)/$(DEST_NAME) $(SRCS) $(LIBS)

default: tuishogi
