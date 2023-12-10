cmake_minimum_required(VERSION 3.26)
project(Intersections_of_segments)

set(CMAKE_CXX_STANDARD 20)

add_executable(Intersections_of_segments main.cpp
        Segments.h
        Segments.cpp
        Tree.cpp
        Tree.h
        Tests.cpp
        Tests.h
        PSeg.cpp
        PSeg.h
        NaiveAlg.cpp
        EffectiveAlg.cpp
)
