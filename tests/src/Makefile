CXX = g++
CXXFLAGS = -g -std=c++11 -DTESTING -fPIC
INCS = -I../../src/ 
LIBS = -ldl
SOFLAGS = -DDYNAMIC

#TEST_FILES = catch.hpp
TEST_FILES = main.o
TEST_FILES += GameFeildTests.o
TEST_FILES += ../../src/GameField.o
TEST_FILES += ../../src/MapData.o
FILES = ../../src/Actor.o
FILES += ../../src/SimpleAI.o
FILES += ../../src/DynamicLoader.o
TEST_FILES += ../../src/ActorInfo.o
TEST_FILES += ../../src/ProjectileActor.o
TEST_FILES += ../../src/SimpleActor.o
TEST_FILES += SimpleActorTests.o
TEST_FILES += SimpleAITests.o

TEST_FILES += DynamicLoaderTests.o

TANK_PATH= ./tanks/
TANKS = ../../src/SimpleAI.so
TANKS += ../../src/SimpleActor.so

TANKS_LINK = ../../src/Actor.o #need to link in the base class for the .so to have everything.

%.so: %.cpp
	$(CXX) $(CXXFLAGS) -shared $? $(TANKS_LINK) -o $@ $(SOFLAGS)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $? -o $@ $(INCS)

testAll: $(FILES) $(TEST_FILES)
	make tanks
	$(CXX) $(CXXFLAGS) $(INCS) -o testAll $(FILES) $(TEST_FILES) $(LIBS)

tanks:	$(TANKS)
	mkdir -p $(TANK_PATH)
	mv $? $(TANK_PATH)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS) 

clean:
	rm -rf testAll *.o ../../src/*.o

cleanTanks:
	rm -rf $(TANK_PATH)
