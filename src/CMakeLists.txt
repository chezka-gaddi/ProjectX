cmake_minimum_required(VERSION 3.9)
project(src)

set(CMAKE_CXX_STANDARD 11)

add_executable(src
        Actor-Alternate.cpp
        Actor-Alternate.h
        Actor.cpp
        Actor.h
        ActorInfo.cpp
        ActorInfo.h
        AttackData.cpp
        AttackData.h
        direction.h
        Drawable.h
        GameField.cpp
        GameField.h
        main.cpp
        MapData.h
        MoveData.cpp
        MoveData.h
        PositionData.h
        ProjectileActor.h
        ProjectileDrawable.h
        SimpleActor.cpp
        SimpleActor.h
        TankActor.h
        TankDrawable.h
        TurnData.cpp
        TurnData.h
        Window.h AsciiGameMisc.h AsciiGameMisc.cpp)
