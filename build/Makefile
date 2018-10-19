CXX = g++
CXXFLAGS = -g -H -std=c++11 -fPIC
INCS = -Isrc
LIBS = -ldl
LIBS += -lglut -lGL -lGLU -lpthread
LIBS += -lSOIL -Llibraries
SOFLAGS = -DDYNAMIC

MAIN = src/main.cpp

TANK_PATH= ./tanks/
TANKS = SimpleAI.so

TANKS_LINK = src/Actor.o#need to link in the base class for the .so to have everything.

tanks:	$(TANKS)
	mkdir -p $(TANK_PATH)
	mv $^ $(TANK_PATH)

%.so: %.cpp
	$(CXX) $(INCS) $(CXXFLAGS) -shared $(TANKS_LINK) $< -o $@ $(SOFLAGS)

cleanTanks:
	rm -rf $(TANK_PATH)

