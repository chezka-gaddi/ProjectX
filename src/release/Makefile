CXX = g++
CXXFLAGS = -g -std=c++11 -fPIC
INCS = -Isrc/
LIBS += -Llibraries -lCTF
SOFLAGS = -DDYNAMIC -Wl,-R libraries

SRC_PATH= src/
TANK_PATH= tanks/
LIB_PATH= libraries/

TANKS = SimpleAI.so
TANKS += PongAI.so

TANKS_LINK = src/actors/Actor.o #need to link in the base class for the .so to have everything.

tanks/%.so: %.cpp
	$(CXX) $(CXXFLAGS) -shared $< $(TANKS_LINK) -o $@ $(SOFLAGS) $(LIBS) $(INCS)

%.ini:
	cp config.sample config.ini
	
config:	config.ini tanks

tanks:	tanksdir $(TANKS:%.so=tanks/%.so)

tanksdir:
	@mkdir -p $(TANK_PATH)

clean:
	rm -rf $(TANK_PATH)
