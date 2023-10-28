cmake_minimum_required(VERSION 3.26)
project(Intersections_of_segments)

set(CMAKE_CXX_STANDARD 23)

add_executable(Intersections_of_segments main.cpp
        Segments.h
        Segments.cpp
        Intersection.cpp
        Intersection.h
        Tree.cpp
        Tree.h
        RandomSegments.cpp
        RandomSegments.h
        Tests.cpp
        Tests.h
)
