CXX = g++
CXXFLAGS = -Wall -fmax-errors=5 -g -std=c++11 -fPIC
INCS = -I./ -Isrc/
LIBS = -ldl
LIBS += -lglut -lGL -lGLU -lpthread
LIBS += -lSOIL -Llibraries -lCTF
SOFLAGS = -DDYNAMIC
PROFILE ?=

SRC_PATH= src/
TANK_PATH= tanks/
LIB_PATH= libraries/

MAIN = $(SRC_PATH)main.cpp

FILES = $(MAIN)
#Actors
FILES += $(SRC_PATH)actors/Actor.cpp
FILES += $(SRC_PATH)actors/ActorInfo.cpp
FILES += $(SRC_PATH)actors/ProjectileActor.cpp
#Game
FILES += $(SRC_PATH)game/GameField.cpp
FILES += $(SRC_PATH)game/game.cpp
FILES += $(SRC_PATH)game/gameover.cpp
FILES += $(SRC_PATH)game/configParser.cpp
FILES += $(SRC_PATH)game/Tournament.cpp
#Map
FILES += $(SRC_PATH)map/MapData.cpp
FILES += $(SRC_PATH)map/Tile.cpp
#Settings
FILES += $(SRC_PATH)settings/Settings.cpp
#UI
FILES += $(SRC_PATH)ui/callbacks.cpp
FILES += $(SRC_PATH)ui/Crate.cpp
FILES += $(SRC_PATH)ui/Drawable.cpp
FILES += $(SRC_PATH)ui/event.cpp
FILES += $(SRC_PATH)ui/GameFieldDrawable.cpp
FILES += $(SRC_PATH)ui/Menu.cpp
FILES += $(SRC_PATH)ui/Projectile.cpp
FILES += $(SRC_PATH)ui/Obstacles.cpp
FILES += $(SRC_PATH)ui/sfxDrawable.cpp
FILES += $(SRC_PATH)ui/util.cpp
FILES += $(SRC_PATH)ui/TankDrawable.cpp
#Utilities
FILES += $(SRC_PATH)utilities/textureLoader.cpp
FILES += $(SRC_PATH)utilities/tankLoader.cpp
FILES += $(SRC_PATH)utilities/gameTracker.cpp
FILES += $(SRC_PATH)utilities/mapLoader.cpp
#Tanks
TANKS = $(SRC_PATH)tanks/SimpleAI.cpp
TANKS += $(SRC_PATH)tanks/PongAI.cpp
TANKS += $(SRC_PATH)tanks/CamperAI.cpp
TANKS += $(SRC_PATH)tanks/StationaryAI.cpp
TANKS += $(SRC_PATH)tanks/AttackDownAI.cpp

TANKS_LINK = $(SRC_PATH)actors/Actor.o #need to link in the base class for the .so to have everything.

platform: $(FILES:.cpp=.o)
	+make tanks
	$(CXX) $(CXXFLAGS) $(INCS) -o platform $(FILES:.cpp=.o) $(LIBS)

coverage: set-coverage $(FILES:.cpp=.o) $(TANKS:%.cpp=%.so)
	$(CXX) $(CXXFLAGS) $(INCS) $(PROFILE) -o platform $(FILES:.cpp=.o) $(LIBS)

set-coverage:
	$(eval PROFILE:=-pg -fprofile-arcs -ftest-coverage -lgcov --coverage)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(PROFILE) -c $? -o $@ $(INCS)

%.h.gch: %.h
	$(CXX) -x c++-header -c $< -o $@ $(INCS) $(LIBS)

src/tanks/%.so: src/tanks/%.cpp
	@mkdir -p tanks
	$(CXX) $(CXXFLAGS) $(INCS) $(PROFILE) -shared $? $(TANKS_LINK) -o $(TANK_PATH)$(@F) $(SOFLAGS) $(LIBS)

tanks: src/actors/Actor.o $(TANKS:%.cpp=%.so)

clean:
	@find . -name \*.o -type f -exec rm -f {} +
	@find . -name \*.gc* -type f -exec rm -f {} +
	@rm -rf gprofresults.txt
	@rm -rf gmon.out
	@rm -rf platform

clean-lib: clean
	@rm -rf buildsrc
	@rm -rf libraries/libCTF.so

clean-all: clean-lib clean-tests
	@rm -rf $(TANK_PATH)*
	@rm -rf coverage

clean-tests: clean
	@rm -rf testUnitAll
	@rm -rf testFunctionalAll
	@make clean -C tests/src
	@make cleanTanks -C tests/src
	@make clean -C tests/functional_tests

dev: clean-lib
	make gen-library -j8

gen-library: $(FILES:.cpp=.o) $(TANKS:%.cpp=%.so)
	@mkdir -p buildsrc/$(LIB_PATH)
	@mkdir -p buildsrc/$(SRC_PATH)
	@mkdir -p buildsrc/$(TANK_PATH)
	@mkdir -p buildsrc/images	
	#echo "Building object library"
	g++ -o buildsrc/$(LIB_PATH)libCTF.a -shared $(CXXFLAGS) $(FILES:.cpp=.o) $(SOFLAGS)
	cp buildsrc/$(LIB_PATH)libCTF.a $(LIB_PATH)
	#echo "Building platform"
	$(CXX) $(CXXFLAGS) $(INCS) -o buildsrc/platform $(FILES:.cpp=.o) $(LIBS)
	#echo "Copying support files"
	cp -R src/buildsrc/ .
	cp README.md buildsrc/README.md
	cp -R images/ buildsrc/
	cp -R maps/ buildsrc/
	cp src/actors/Actor.h buildsrc/src/
	cp src/structures/MoveData.h buildsrc/src/
	cp src/structures/attributes.h buildsrc/src/
	cp src/map/MapData.h buildsrc/src/
	cp src/structures/direction.h buildsrc/src/
	cp src/structures/PositionData.h buildsrc/src/
	cp $(TANKS) buildsrc/
	cp $(TANKS:.cpp=.h) buildsrc/
	#	cp -R $(SRC_PATH)*.o build/$(SRC_PATH)
	# Change tanks src to point to new directory
	# sed -i 's#include "#include "src/#g' buildsrc/SimpleAI.h
	# sed -i 's#include "#include "src/#g' buildsrc/PongAI.h

push-to-git: clean-lib
	mkdir -p buildsrc
	git clone git@gitlab.com:jamckee/projectx.git buildsrc/
	make gen-library -j8
	git --git-dir=buildsrc/.git --work-tree=buildsrc checkout -b pre-release
	git --git-dir=buildsrc/.git --work-tree=buildsrc add .
	#git --git-dir=buildsrc/.git --work-tree=buildsrc commit -m "Automated push of new version. 4.00"
	#git --git-dir=buildsrc/.git --work-tree=buildsrc status
	#git --git-dir=buildsrc/.git --work-tree=buildsrc push -fu origin pre-release

tests: set-coverage src/actors/Actor.o $(TANKS:%.cpp=%.so) testUnitAll testFunctionalAll

testUnitAll:
	+make PROFILE="$(PROFILE)" -C tests/src
	mv tests/src/testUnitAll .

testFunctionalAll: src/tanks/SimpleActor.so src/tanks/SimpleAI.so
	+make PROFILE="$(PROFILE)" -C tests/functional_tests
	mv tests/functional_tests/testFunctionalAll .
