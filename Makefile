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
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

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
	rm -rf build

cleanTanks:
	rm -rf $(TANK_PATH)

gen-library: $(FILES)
	@mkdir -p build/$(LIB_PATH)
	@mkdir -p build/$(SRC_PATH)
	@mkdir -p build/images
	#echo "Building object files"
	$(CXX) $(CXXFLAGS) $(INCS) -o build/$@ -c $< $(LIBS)
	g++ -o build/$(LIB_PATH)libCTF.so -shared $(CXXFLAGS) $?
	#echo :Building pre-compiled header"
	$(CXX) -x c++-header $(CXXFLAGS) $(INCS) -o build/src/Actor.h.gch -c src/Actor.h $(LIBS)
	#echo "Building platform"
	$(CXX) $(CXXFLAGS) $(INCS) -o $(SRC_PATH)main.o -c $(SRC_PATH)main.cpp $(LIBS)
	$(CXX) $(CXXFLAGS) $(INCS) -o build/platform $(MAIN) $(FILES) $(LIBS)
	#echo "Copying support files"
	cp src/Makefile build/
	cp config.txt	build/config.txt
	cp -R images/ build/images/
	cp src/Actor.* build/src/
	cp src/MoveData.h build/src/
	cp src/attributes.h build/src/
	cp src/MapData.h build/src/
	cp src/direction.h build/src/
	cp src/PositionData.h build/src/
	cp $(TANKS:.so=.cpp) build/
	cp $(TANKS:.so=.h) build/
	#	cp -R $(SRC_PATH)*.o build/$(SRC_PATH)
	sed -i 's#include "#include "src/#g' build/SimpleAI.h
