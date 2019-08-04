CXX = g++
CXXFLAGS = -g -std=c++11 -DTESTING -fPIC
INCS = -I./ -I../../src/ -I../src
INCS += -I../../src/game
INCS += -I../../src/map
INCS += -I../../src/settings
INCS += -I../../src/structures
INCS += -I../../src/tanks
INCS += -I../../src/ui
INCS += -I../../src/utilities
INCS += -I../../src/actors
LIBS += -ldl -lglut -lGL -lGLU -lpthread
LIBS += -L../../libraries -lSOIL
SOFLAGS = -DDYNAMIC

PROFILE ?=

#TEST_FILES = catch.hpp
TEST_FILES = main.cpp
TEST_FILES += GameFieldTests.cpp
TEST_FILES += SimpleActorTests.cpp
TEST_FILES += SimpleAITests.cpp
TEST_FILES += TankLoaderTests.cpp

SRC_PATH=../../src/

FILES += $(SRC_PATH)game/GameField.cpp
FILES += $(SRC_PATH)actors/Actor.cpp
FILES += $(SRC_PATH)map/MapData.cpp
FILES += $(SRC_PATH)map/Tile.cpp
FILES += $(SRC_PATH)actors/ProjectileActor.cpp
FILES += $(SRC_PATH)actors/ActorInfo.cpp
FILES += $(SRC_PATH)ui/event.cpp
FILES += $(SRC_PATH)ui/util.cpp
FILES += $(SRC_PATH)ui/TankDrawable.cpp
FILES += $(SRC_PATH)ui/GameFieldDrawable.cpp
FILES += $(SRC_PATH)ui/Projectile.cpp
FILES += $(SRC_PATH)ui/Obstacles.cpp
FILES += $(SRC_PATH)ui/Drawable.cpp
FILES += $(SRC_PATH)game/game.cpp
FILES += $(SRC_PATH)game/gameover.cpp
FILES += $(SRC_PATH)game/configParser.cpp
FILES += $(SRC_PATH)ui/callbacks.cpp
FILES += $(SRC_PATH)utilities/textureLoader.cpp
FILES += $(SRC_PATH)utilities/tankLoader.cpp
FILES += $(SRC_PATH)utilities/gameTracker.cpp
FILES += $(SRC_PATH)utilities/mapLoader.cpp
FILES += $(SRC_PATH)ui/Menu.cpp
FILES += $(SRC_PATH)ui/sfxDrawable.cpp
FILES += $(SRC_PATH)ui/Crate.cpp
FILES += $(SRC_PATH)tanks/SimpleAI/SimpleAI.cpp
FILES += $(SRC_PATH)tanks/SimpleActor/SimpleActor.cpp
FILES += $(SRC_PATH)settings/Settings.cpp

TANK_PATH = ./tanks/
TANKS = SimpleAI.so
TANKS += SimpleActor.so

TANKS_LINK = ../../src/actors/Actor.o #need to link in the base class for the .so to have everything.

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(PROFILE) -c $? -o $@ $(INCS)

%.so: ../../src/tanks/*/%.cpp
	$(CXX) $(CXXFLAGS) $(PROFILE) -shared $? $(TANKS_LINK) -o $@ $(SOFLAGS) $(INCS)

testAll: $(FILES:.cpp=.o) $(TEST_FILES:.cpp=.o)
	+make tanks
	$(CXX) $(CXXFLAGS) $(INCS) $(PROFILE) -o testUnitAll $(FILES:.cpp=.o) $(TEST_FILES:.cpp=.o) $(LIBS)

tanks:	$(TANKS)
	mkdir -p $(TANK_PATH)
	mv $? $(TANK_PATH)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS) 

clean:
	rm -rf testAll *.o ../../src/*.o

cleanTanks:
	rm -rf $(TANK_PATH)
