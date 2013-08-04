GXX = g++
LIBS = -losl
SOURCES = tuishogi.cpp
DEST_DIR = bin
DEST_NAME = tuishogi

tuishogi: tuishogi.cpp
	$(GXX) -o $(DEST_DIR)/$(DEST_NAME) $(SOURCES) $(LIBS)

default: tuishogi
