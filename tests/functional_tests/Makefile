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

PROFILE ?=

TEST_FILES = main.cpp
TEST_FILES += movement_tests.cpp
TEST_FILES += projectile_functional_tests.cpp

LIBS += -ldl -lglut -lGL -lGLU -lpthread
LIBS += -L../../libraries -lSOIL
SRC_PATH=../../src/

FILES += $(SRC_PATH)settings/Settings.cpp
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
FILES += $(SRC_PATH)utilities/tankLoader.cpp
FILES += $(SRC_PATH)utilities/textureLoader.cpp
FILES += $(SRC_PATH)utilities/mapLoader.cpp
FILES += $(SRC_PATH)utilities/gameTracker.cpp
FILES += $(SRC_PATH)ui/Menu.cpp
FILES += $(SRC_PATH)ui/sfxDrawable.cpp
FILES += $(SRC_PATH)ui/Crate.cpp
FILES += $(SRC_PATH)tanks/SimpleActor/SimpleActor.cpp

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(PROFILE) -c $< -o $@ $(INCS)

testAll: $(FILES:.cpp=.o) $(TEST_FILES:.cpp=.o)
	$(CXX) $(CXXFLAGS) $(INCS) $(PROFILE) -o testFunctionalAll $(FILES:.cpp=.o) $(TEST_FILES:.cpp=.o) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

clean:
	rm -rf testAll *.o ../../src/*.o
