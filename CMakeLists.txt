cmake_minimum_required(VERSION 3.22)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

include_directories(include
                    vector
                    iterator
                    pair
                    map
                    rb_tree
                    set)

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
        stack/stack.cpp stack/stack.hpp
        map/map.cpp map/map.hpp
        pair/pair.cpp pair/pair.hpp
        rb_tree/rb_tree.cpp rb_tree/rb_tree.hpp iterator/rb_iterator.cpp iterator/rb_iterator.hpp set/set.cpp set/set.hpp)
