CXX = g++
CXXFLAGS = -g -std=c++11 -fPIC
INCS = -I./
LIBS = -ldl
LIBS += -lglut -lGL -lGLU -lpthread
LIBS += -lSOIL -Llibraries
SOFLAGS = -DDYNAMIC

SRC_PATH= src/
TANK_PATH= tanks/
LIB_PATH= libraries/

MAIN = $(SRC_PATH)main.cpp

FILES = $(SRC_PATH)GameField.cpp
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

TANKS = $(SRC_PATH)SimpleAI.so

TANKS_LINK = src/Actor.o #need to link in the base class for the .so to have everything.

platform: $(FILES:.cpp=.o) $(MAIN:.cpp=.o)
	+make tanks
	$(CXX) $(CXXFLAGS) $(INCS) -o platform $(MAIN) $(FILES) $(LIBS)

%.so: %.cpp
	$(CXX) $(CXXFLAGS) -shared $< $(TANKS_LINK) -o $@ $(SOFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS) $(LIBS)

%.h.gch: %.h
	$(CXX) -x c++-header -c $< -o $@ $(INCS) $(LIBS)

tanks:	$(TANKS)
	mkdir -p $(TANK_PATH)
	mv $^ $(TANK_PATH)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

clean:
	rm -rf platform src/*.o

clean-lib: clean
	rm -rf buildsrc
	rm -rf libraries/libCTF.so

cleanTanks:
	rm -rf $(TANK_PATH)

dev: clean-lib
	make gen-library -j8

gen-library: $(FILES:.cpp=.o)
	@mkdir -p buildsrc/$(LIB_PATH)
	@mkdir -p buildsrc/$(SRC_PATH)
	@mkdir -p buildsrc/$(TANK_PATH)
	@mkdir -p buildsrc/images	
	#echo "Building object library"
	g++ -o buildsrc/$(LIB_PATH)libCTF.so -shared $(CXXFLAGS) $? $(SOFLAGS)
	#echo :Building pre-compiled header"
	#$(CXX) -x c++-header $(CXXFLAGS) $(INCS) -o build/src/Actor.h.gch -c src/Actor.h $(LIBS)
	#echo "Building platform"
	$(CXX) $(CXXFLAGS) $(INCS) -o $(SRC_PATH)main.o -c $(SRC_PATH)main.cpp $(LIBS)
	$(CXX) $(CXXFLAGS) $(INCS) -o buildsrc/platform $(MAIN) $? $(LIBS)
	#echo "Building Sample Tank"	
	$(CXX) $(CXXFLAGS) -shared src/SimpleAI.cpp -o buildsrc/$(TANK_PATH)SimpleAI.so $(SOFLAGS)
	#echo "Copying support files"
	cp -R src/buildsrc/ .
	cp config.txt	buildsrc/config.txt
	cp -R images/ buildsrc/
	cp src/Actor.h buildsrc/src/
	cp src/MoveData.h buildsrc/src/
	cp src/attributes.h buildsrc/src/
	cp src/MapData.h buildsrc/src/
	cp src/direction.h buildsrc/src/
	cp src/PositionData.h buildsrc/src/
	cp $(TANKS:.so=.cpp) buildsrc/
	cp $(TANKS:.so=.h) buildsrc/
	#	cp -R $(SRC_PATH)*.o build/$(SRC_PATH)
	# Change tanks src to point to new directory
	sed -i 's#include "#include "src/#g' buildsrc/SimpleAI.h

push-to-git: clean-lib
	mkdir -p buildsrc
	git clone git@gitlab.com:jamckee/projectx.git buildsrc/
	make gen-library -j8
	git --git-dir=buildsrc/.git --work-tree=buildsrc add .
	git --git-dir=buildsrc/.git --work-tree=buildsrc commit -m "Automated push of new version. 1.03"
	git --git-dir=buildsrc/.git --work-tree=buildsrc status
	git --git-dir=buildsrc/.git --work-tree=buildsrc push
