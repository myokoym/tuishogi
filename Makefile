GXX = g++
LIBS = -losl
SOURCES = tuishogi.cpp

tuishogi: tuishogi.cpp
	$(GXX) -o tuishogi $(SOURCES) $(LIBS)

default: tuishogi
