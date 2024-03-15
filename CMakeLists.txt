cmake_minimum_required(VERSION 3.27)
project(RPG_Game)

set(CMAKE_CXX_STANDARD 17)

add_executable(RPG_Game main.cpp
        Character/Character.h
        Character/Character.cpp
        Combat/Action.h
        Enemy/Enemy.cpp
        Enemy/Enemy.h
        Player/Player.cpp
        Player/Player.h
        Utils.h
        Combat/Combat.cpp
        Combat/Combat.h)
