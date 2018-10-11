CXX = g++
CXXFLAGS = -g -std=c++11
LIBS = -lglut -lGL -lGLU -lpthread -lSOIL
INCS = -I./ -I./demo/

FILES = GameField.o
FILES += demo/TankDrawable.o
FILES += demo/main.o
FILES += AsciiGameMisc.o
FILES += Actor.o
FILES += AsciiTankActor.o
FILES += MapData.o
FILES += ProjectileActor.o
FILES += ActorInfo.o
FILES += demo/callbacks.o
FILES += demo/event.o
FILES += demo/game.o
FILES += demo/GameFieldDrawable.o
FILES += demo/Texture.o
FILES += demo/util.o
FILES += demo/Projectile.o
FILES += demo/Menu.o
FILES += demo/Obstacles.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

platform: $(FILES) $(TEST_FILES)
	$(CXX) $(CXXFLAGS) $(INCS) -o platform  $(FILES) $(TEST_FILES) $(LIBS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

clean:
	rm -rf platform *.o
