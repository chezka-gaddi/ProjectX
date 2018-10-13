CXX = g++
CXXFLAGS = -g -std=c++11
LIBS = -lglut -lGL -lGLU -lpthread -lSOIL
<<<<<<< HEAD
INCS = -I./  

FILES = main.o
FILES += GameField.o
=======
INCS = -I./ -I./demo/

FILES = GameField.o
FILES += demo/TankDrawable.o
FILES += demo/main.o
FILES += AsciiGameMisc.o
>>>>>>> fd8b01cc37a9a560b5f6cdbd9b3444c64d8e81df
FILES += Actor.o
FILES += AsciiTankActor.o
FILES += MapData.o
FILES += ProjectileActor.o
FILES += ActorInfo.o
<<<<<<< HEAD
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
=======
FILES += demo/callbacks.o
FILES += demo/event.o
FILES += demo/game.o
FILES += demo/GameFieldDrawable.o
FILES += demo/Texture.o
FILES += demo/util.o
FILES += demo/Projectile.o
FILES += demo/Menu.o
FILES += demo/Obstacles.o
>>>>>>> fd8b01cc37a9a560b5f6cdbd9b3444c64d8e81df

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

platform: $(FILES) $(TEST_FILES)
<<<<<<< HEAD
	$(CXX) $(CXXFLAGS) $(INCS) -o platform $(FILES) $(TEST_FILES) $(LIBS)
=======
	$(CXX) $(CXXFLAGS) $(INCS) -o platform  $(FILES) $(TEST_FILES) $(LIBS)
>>>>>>> fd8b01cc37a9a560b5f6cdbd9b3444c64d8e81df

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INCS)

clean:
	rm -rf platform *.o
