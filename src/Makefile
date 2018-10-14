CXX = g++
CXXFLAGS = -g -std=c++11 -fPIC
INCS = -I./
LIBS = -ldl
LIBS += -lglut -lGL -lGLU -lpthread -lSOIL
SOFLAGS = -DDYNAMIC

FILES = main.o
FILES += GameField.o
FILES += AsciiGameMisc.o
FILES += Actor.o
FILES += AsciiTankActor.o
FILES += MapData.o
FILES += ProjectileActor.o
FILES += ActorInfo.o
FILES += Texture.o
FILES += event.o
FILES += util.o
FILES += TankDrawable.o
FILES += GameFieldDrawable.o
FILES += Projectile.o
FILES += Obstacles.o
FILES += game.o
FILES += callbacks.o
FILES += DynamicLoader.o
FILES += SimpleAI.o
FILES += Menu.o

TANK_PATH= ./tanks/
TANKS = SimpleAI.so
TANKS += AsciiTankActor.so

TANKS_LINK = Actor.o #need to link in the base class for the .so to have everything.

%.so: %.cpp
	$(CXX) $(CXXFLAGS) -shared $< $(TANKS_LINK) -o $@ $(SOFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

platform: $(FILES) $(TEST_FILES)
	make tanks
	$(CXX) $(CXXFLAGS) $(INCS) -o platform $(FILES) $(TEST_FILES) $(LIBS)

tanks:	$(TANKS)
	mkdir -p $(TANK_PATH)
	mv $^ $(TANK_PATH)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

clean:
	rm -rf platform *.o

cleanTanks:
	rm -rf $(TANK_PATH)
