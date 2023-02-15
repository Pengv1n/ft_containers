cmake_minimum_required(VERSION 3.24)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

include_directories(include vector iterator)

add_subdirectory(Google_tests)

add_executable(ft_containers
        vector/vector.cpp
        vector/vector.hpp
        main.cpp
        include/defs.hpp
        iterator/iterator.cpp iterator/iterator.hpp
        iterator/normal_iterator.cpp iterator/normal_iterator.hpp
        include/type_traits.hpp
        include/utils.hpp
        )
