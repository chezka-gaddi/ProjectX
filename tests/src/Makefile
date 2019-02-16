CXX = g++
CXXFLAGS = -g -std=c++11 -DTESTING -fPIC
INCS = -I./ -I../../src/ -I../src 
LIBS += -ldl -lglut -lGL -lGLU -lpthread
LIBS += -L../../libraries -lSOIL
SOFLAGS = -DDYNAMIC

PROFILE ?=

#TEST_FILES = catch.hpp
TEST_FILES = main.cpp
TEST_FILES += GameFieldTests.cpp
TEST_FILES += SimpleActorTests.cpp
TEST_FILES += SimpleAITests.cpp
TEST_FILES += DynamicLoaderTests.cpp

SRC_PATH=../../src/

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
FILES += $(SRC_PATH)SimpleAI.cpp
FILES += $(SRC_PATH)SimpleActor.cpp
FILES += $(SRC_PATH)Settings.cpp


TANK_PATH= ./tanks/
TANKS = SimpleAI.so
TANKS += SimpleActor.so

TANKS_LINK = ../../src/Actor.o #need to link in the base class for the .so to have everything.

%.so: ../../src/%.cpp
	$(CXX) $(CXXFLAGS) $(PROFILE) -shared $? $(TANKS_LINK) -o $@ $(SOFLAGS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(PROFILE) -c $? -o $@ $(INCS)

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
