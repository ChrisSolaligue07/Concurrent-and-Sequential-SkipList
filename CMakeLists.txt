cmake_minimum_required(VERSION 3.24)
project(Sequential_Concurrent_SkipList)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sequential_Concurrent_SkipList main.cpp src/dataGenerator.h src/ConcurrentSkipList/cnode.h src/ConcurrentSkipList/cSkipList.h src/SequentialSkipList/snode.h src/SequentialSkipList/sSkipList.h src/ConcurrentSkipList/cnode.cpp src/ConcurrentSkipList/cSkipList.cpp src/SequentialSkipList/snode.cpp src/SequentialSkipList/sSkipList.cpp src/testStruct.h src/argsMain.h)
