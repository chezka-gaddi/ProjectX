CXX = g++
CXXFLAGS = -g -std=c++11 -fPIC
INCS = -Isrc/
LIBS += -Llibraries -lCTF
SOFLAGS = -DDYNAMIC -Wl,-R libraries

SRC_PATH= src/
TANK_PATH= tanks/
LIB_PATH= libraries/

#Add your custom tank to the TANKS variable
#TANKS = SimpleAI.cpp

#Bundled Sample Tanks
STANKS = sample_tanks/SimpleAI.cpp
STANKS += sample_tanks/PongAI.cpp
STANKS += sample_tanks/AttackDownAI.cpp
STANKS += sample_tanks/CamperAI.cpp
STANKS += sample_tanks/StationaryAI.cpp

TANKS_LINK = src/actors/Actor.o #need to link in the base class for the .so to have everything.

tanks/%.so: %.cpp
	$(CXX) $(CXXFLAGS) -shared $< $(TANKS_LINK) -o $@ $(SOFLAGS) $(LIBS) $(INCS)

tanks/%.so: sample_tanks/%.cpp
	$(CXX) $(CXXFLAGS) -shared $< $(TANKS_LINK) -o $@ $(SOFLAGS) $(LIBS) $(INCS)

#Checks for config file, creates copy of sample config if none found
%.ini:
	cp config.sample config.ini

#You can remove sample_tanks and config.ini to prevent checking those sections
config:	config.ini tanks sample_tanks

tanks:	tanksdir $(TANKS:%.cpp=tanks/%.so)

sample_tanks: tanksdir $(STANKS:sample_tanks/%.cpp=tanks/%.so)

tanksdir:
	@mkdir -p $(TANK_PATH)

clean:
	rm -rf $(TANK_PATH)
