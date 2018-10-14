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
FILES += SimpleAI.o
FILES += Menu.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

platform: $(FILES) $(TEST_FILES)
	$(CXX) $(CXXFLAGS) $(INCS) -o platform $(FILES) $(TEST_FILES) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

clean:
	rm -rf platform *.o
