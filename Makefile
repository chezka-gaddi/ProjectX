CXX = g++
CXXFLAGS = -std=c++11 -fPIC
CXXFLAGS += -g
#PROFILE = -pg
#PROFILE += -fprofile-arcs -ftest-coverage
INCS = -I./ -Isrc/
LIBS = -ldl
LIBS += -lglut -lGL -lGLU -lpthread
LIBS += -lSOIL -Llibraries
SOFLAGS = -DDYNAMIC

SRC_PATH= src/
TANK_PATH= tanks/
LIB_PATH= libraries/

MAIN = $(SRC_PATH)main.cpp

FILES = $(MAIN)
FILES += $(SRC_PATH)GameField.cpp
FILES += $(SRC_PATH)Actor.cpp
FILES += $(SRC_PATH)MapData.cpp
FILES += $(SRC_PATH)ProjectileActor.cpp
FILES += $(SRC_PATH)ActorInfo.cpp
FILES += $(SRC_PATH)Texture.cpp
FILES += $(SRC_PATH)event.cpp
FILES += $(SRC_PATH)util.cpp
FILES += $(SRC_PATH)TankDrawable.cpp
FILES += $(SRC_PATH)GameFieldDrawable.cpp
FILES += $(SRC_PATH)Projectile.cpp
FILES += $(SRC_PATH)Obstacles.cpp
FILES += $(SRC_PATH)game.cpp
FILES += $(SRC_PATH)callbacks.cpp
FILES += $(SRC_PATH)DynamicLoader.cpp
FILES += $(SRC_PATH)Menu.cpp
FILES += $(SRC_PATH)sfxDrawable.cpp
FILES += $(SRC_PATH)Crate.cpp

TANK_PATH= ./tanks/
TANKS = $(SRC_PATH)SimpleAI.cpp
TANKS += $(SRC_PATH)PongAI.cpp
TANKS += $(SRC_PATH)CamperAI.cpp
TANKS += $(SRC_PATH)StationaryAI.cpp
TANKS += $(SRC_PATH)AttackDownAI.cpp

TANKS_LINK = src/Actor.o #need to link in the base class for the .so to have everything.

platform: $(FILES:.cpp=.o) $(TANKS:src/%.cpp=tanks/%.so)
	$(CXX) $(CXXFLAGS) $(INCS) $(PROFILE) -o platform $(FILES:.cpp=.o) $(LIBS)

tanksdir:
	@mkdir -p tanks

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(PROFILE) -c $? -o $@ 

%.h.gch: %.h
	$(CXX) -x c++-header -c $< -o $@ $(INCS) $(LIBS)

tanks/%.so: src/%.cpp ./src/Actor.o
	$(CXX) $(CXXFLAGS) $(INCS) $(PROFILE) -shared $< $(TANKS_LINK) -o $(TANK_PATH)$(@F) $(SOFLAGS) $(LIBS)

tanks: $(TANKS:%.cpp=%.so)

clean:
	@rm -rf platform results.txt src/*.o
	@rm -rf *.gc*
	@rm -rf src/*.gc*
	@rm -rf gprofresults.txt
	@rm -rf gmon.out

clean-lib: clean
	rm -rf buildsrc
	rm -rf libraries/libCTF.so

clean-all: clean-lib
	@rm -rf $(TANK_PATH)*
	@rm -rf coverage

dev: clean-lib
	make gen-library -j8

gen-library: $(FILES:.cpp=.o) $(TANKS:src/%.cpp=tanks/%.so)
	@mkdir -p buildsrc/$(LIB_PATH)
	@mkdir -p buildsrc/$(SRC_PATH)
	@mkdir -p buildsrc/$(TANK_PATH)
	@mkdir -p buildsrc/images	
	#echo "Building object library"
	g++ -o buildsrc/$(LIB_PATH)libCTF.so -shared $(CXXFLAGS) $(FILES:.cpp=.o) $(SOFLAGS)
	#echo "Building platform"
	$(CXX) $(CXXFLAGS) $(INCS) -o buildsrc/platform $(FILES:.cpp=.o) $(LIBS)
	#echo "Copying support files"
	cp -R src/buildsrc/ .
	cp config.txt	buildsrc/config.sample
	cp README.md buildsrc/README.md
	cp -R images/ buildsrc/
	cp -R maps/ buildsrc/
	cp src/Actor.h buildsrc/src/
	cp src/MoveData.h buildsrc/src/
	cp src/attributes.h buildsrc/src/
	cp src/MapData.h buildsrc/src/
	cp src/direction.h buildsrc/src/
	cp src/PositionData.h buildsrc/src/
	cp $(TANKS) buildsrc/
	cp $(TANKS:.cpp=.h) buildsrc/
	#	cp -R $(SRC_PATH)*.o build/$(SRC_PATH)
	# Change tanks src to point to new directory
	sed -i 's#include "#include "src/#g' buildsrc/SimpleAI.h
	sed -i 's#include "#include "src/#g' buildsrc/PongAI.h

push-to-git: clean-lib
	mkdir -p buildsrc
	git clone git@gitlab.com:jamckee/projectx.git buildsrc/
	make gen-library -j8
	git --git-dir=buildsrc/.git --work-tree=buildsrc checkout -b pre-release
	git --git-dir=buildsrc/.git --work-tree=buildsrc add .
	#git --git-dir=buildsrc/.git --work-tree=buildsrc commit -m "Automated push of new version. 4.00"
	#git --git-dir=buildsrc/.git --work-tree=buildsrc status
	#git --git-dir=buildsrc/.git --work-tree=buildsrc push -fu origin pre-release
