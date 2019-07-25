CXX = g++
CXXFLAGS = -Wall -fmax-errors=5 -g -std=c++11 -fPIC
INCS = -I./ -Isrc/
LIBS = -ldl
LIBS += -lglut -lGL -lGLU -lpthread
LIBS += -lSOIL -Llibraries -lCTF 
#LIBS += -lprofiler #Google Profiler
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
TANKS += $(SRC_PATH)tanks/NotSimpleAI.cpp

TANKS_LINK = $(SRC_PATH)actors/Actor.o #need to link in the base class for the .so to have everything.

platform: $(FILES:.cpp=.o)
	+make tanks
	$(CXX) $(CXXFLAGS) $(INCS) -o platform $(FILES:.cpp=.o) $(LIBS)

#-include ./src/.depend

coverage: set-coverage $(FILES:.cpp=.o)
	+make tanks
	$(CXX) $(CXXFLAGS) $(INCS) $(PROFILE) -o platform $(FILES:.cpp=.o) $(LIBS)

set-coverage:
	$(eval PROFILE:=-pg -fprofile-arcs -ftest-coverage -lgcov --coverage)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(PROFILE) -c $? -o $@ $(INCS)

%.h.gch: %.h
	$(CXX) -x c++-header -c $< -o $@ $(INCS) $(LIBS)

tanks/%.so: src/tanks/%.cpp
	@mkdir -p tanks
	$(CXX) $(CXXFLAGS) $(INCS) $(PROFILE) -shared $? $(TANKS_LINK) -o $(TANK_PATH)$(@F) $(SOFLAGS) $(LIBS)

tanks: src/actors/Actor.o $(TANKS:$(SRC_PATH)tanks/%.cpp=$(TANK_PATH)%.so)

depend: .depend

.depend: $(FILES) $(TANKS)
	rm -f ./src/.depend
	$(CXX) $(CXXFLAGS) $(INCS) -MM $^>>./src/.depend;

clean:
	@find . -name \*.o -type f -exec rm -f {} +
	@find . -name \*.gc* -type f -exec rm -f {} +
	@rm -rf gprofresults.txt
	@rm -rf gmon.out
	@rm -rf platform

clean-lib: clean
	@rm -rf release
	@rm -rf libraries/libCTF.so

clean-all: clean-lib clean-tests
	@rm -rf $(TANK_PATH)*
	@rm -rf coverage
	@rm -rf results.txt
	@rm -rf gameMoves.txt

clean-tests: clean
	@rm -rf testUnitAll
	@rm -rf testFunctionalAll
	@make clean -C tests/src
	@make cleanTanks -C tests/src
	@make clean -C tests/functional_tests

dev: clean-lib
	make gen-library -j8

gen-library: $(FILES:.cpp=.o)
	#@echo "Make the tanks"
	+make tanks
	#@echo "Make directories for release folder"
	@mkdir -p release/$(LIB_PATH) release/$(TANK_PATH) release/images release/sample_tanks
	@mkdir -p release/$(SRC_PATH)/actors release/$(SRC_PATH)/map release/$(SRC_PATH)/structures
	#@echo "Building object library"
	$(CXX) $(CXXFLAGS) $(INCS) -o release/$(LIB_PATH)libCTF.a -shared $(FILES:.cpp=.o) $(SOFLAGS)
	cp release/$(LIB_PATH)libCTF.a $(LIB_PATH)
	#@echo "Building platform"
	$(CXX) $(CXXFLAGS) $(INCS) -o release/platform $(FILES:.cpp=.o) $(LIBS)
	#@echo "Copying support files"
	cp -R src/release/ .
	cp README.md release/README.md
	cp changelog.md release/changelog.md
	cp -R images/ release/
	cp -R maps/ release/
	cp src/actors/Actor.h release/src/actors/
	cp src/actors/Actor.o release/src/actors/
	cp src/structures/MoveData.h release/src/structures/
	cp src/structures/attributes.h release/src/structures/
	cp src/structures/direction.h release/src/structures/
	cp src/structures/PositionData.h release/src/structures/
	cp src/map/MapData.h release/src/map/
	cp src/map/Tile.h release/src/map/
	#Copy sample tanks
	cp $(TANKS) release/sample_tanks/
	cp $(TANKS:.cpp=.h) release/sample_tanks/
	# Change tanks src to point to new directory
	#sed -i 's#include <actors#include <src#g' release/SimpleAI.h
	#sed -i 's#include <actors#include <src#g' release/PongAI.h
	#sed -i 's#include <actors#include <src#g' release/CamperAI.h
	#sed -i 's#include <actors#include <src#g' release/PongAI.h

push-to-git: clean-lib
	#Create directories
	mkdir -p release
	#Pull down current release
	git clone git@gitlab.com:jamckee/projectx.git release/
	#Build new files and copy current support files
	make gen-library -j8
	#Switch git branches and add files
	git --git-dir=release/.git --work-tree=release checkout -b pre-release
	git --git-dir=release/.git --work-tree=release add .
	##Automated commit lines #Disabled for manual checking
	#git --git-dir=buildsrc/.git --work-tree=buildsrc commit -m "Automated push of new version. 4.00"
	#git --git-dir=buildsrc/.git --work-tree=buildsrc status
	#git --git-dir=buildsrc/.git --work-tree=buildsrc push -fu origin pre-release

tests: set-coverage src/actors/Actor.o testUnitAll testFunctionalAll

testUnitAll:
	+make PROFILE="$(PROFILE)" -C tests/src
	mv tests/src/testUnitAll .

testFunctionalAll: tanks/SimpleActor.so tanks/SimpleAI.so
	+make PROFILE="$(PROFILE)" -C tests/functional_tests
	mv tests/functional_tests/testFunctionalAll .
