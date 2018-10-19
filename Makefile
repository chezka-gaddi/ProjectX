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
TANKS += $(SRC_PATH)AsciiTankActor.so

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
	rm -rf build/$(LIB_PATH)libCTF.so
	rm -rf build/$(SRC_PATH)*.gch
	rm -rf build/platform
	rm -rf build/$(SRC_PATH)*.o
	rm -rf build/$(TANK_PATH)

cleanTanks:
	rm -rf $(TANK_PATH)

gen-library: $(FILES:.cpp=.o)
	@mkdir -p build/$(LIB_PATH)
	@mkdir -p build/$(SRC_PATH)
	@mkdir -p build/images
	#echo "Building object files"
	$(CXX) $(CXXFLAGS) $(INCS) -o build/$@ -c $< $(LIBS)
	g++ -o build/$(LIB_PATH)libCTF.so -shared $(CXXFLAGS) $?
	#echo :Building pre-compiled header"
	$(CXX) -x c++-header $(CXXFLAGS) $(INCS) -o build/$(SRC_PATH)AllHeader.h.gch -c $(SRC_PATH)AllHeader.h $(LIBS)
	#echo "Building platform"
	$(CXX) $(CXXFLAGS) $(INCS) -o build/$(SRC_PATH)/main.o -c $(SRC_PATH)main.cpp $(LIBS)
	$(CXX) $(CXXFLAGS) $(INCS) -o build/platform $(MAIN) $(FILES) $(LIBS)
	#echo "Copying support files"
	cp config.txt	build/config.txt
	cp -R images/ build/images/
	cp -R $(SRC_PATH)*.o build/$(SRC_PATH)
