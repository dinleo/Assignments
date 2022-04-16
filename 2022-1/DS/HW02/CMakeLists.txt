cmake_minimum_required(VERSION 3.21)
project(HW02)

set(CMAKE_CXX_STANDARD 14)

add_executable(HW02 main.cpp
        doublylinkedlist.h
        doublylinkedlist.txx
        texteditor.cpp
        texteditor.h
        )
