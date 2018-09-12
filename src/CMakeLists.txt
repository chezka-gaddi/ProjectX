cmake_minimum_required(VERSION 3.9)
project(src)

set(CMAKE_CXX_STANDARD 11)

add_executable(Tanks
        Actor.h
        Drawable.h
        GameField.h
        main.cpp
        PositionData.h
        ProjectileActor.h
        ProjectileDrawable.h
        TankActor.h
        TankDrawable.h
        Window.h TurnData.cpp TurnData.h MoveData.cpp MoveData.h AttackData.cpp AttackData.h)
