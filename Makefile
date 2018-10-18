CXX = g++
CXXFLAGS = -g -std=c++11 -fPIC
INCS = -I./
LIBS = -ldl
LIBS += -lglut -lGL -lGLU -lpthread
LIBS += -lSOIL -Llibraries
SOFLAGS = -DDYNAMIC

FILES = src/main.cpp
FILES += src/GameField.cpp
FILES += src/Actor.cpp
FILES += src/MapData.cpp
FILES += src/ProjectileActor.cpp
FILES += src/ActorInfo.cpp
FILES += src/Texture.cpp
FILES += src/event.cpp
FILES += src/util.cpp
FILES += src/TankDrawable.cpp
FILES += src/GameFieldDrawable.cpp
FILES += src/Projectile.cpp
FILES += src/Obstacles.cpp
FILES += src/game.cpp
FILES += src/callbacks.cpp
FILES += src/DynamicLoader.cpp
FILES += src/Menu.cpp

TANK_PATH= ./tanks/
TANKS = src/SimpleAI.so
TANKS += src/AsciiTankActor.so

TANKS_LINK = src/Actor.o #need to link in the base class for the .so to have everything.

platform: $(FILES:.cpp=.o)
	make tanks
	$(CXX) $(CXXFLAGS) $(INCS) -o platform $(FILES) $(LIBS)

%.so: %.cpp
	$(CXX) $(CXXFLAGS) -shared $< $(TANKS_LINK) -o $@ $(SOFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

tanks:	$(TANKS)
	mkdir -p $(TANK_PATH)
	mv $^ $(TANK_PATH)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

clean:
	rm -rf platform src/*.o

cleanTanks:
	rm -rf $(TANK_PATH)
