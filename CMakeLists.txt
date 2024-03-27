cmake_minimum_required(VERSION 3.21)
project(Task2)

set(CMAKE_CXX_STANDARD 14)

add_executable(Task2 src/FileSystemObject.cpp headers/FileSystemObject.h src/Directory.cpp headers/Directory.h src/File.cpp headers/File.h src/Link.cpp headers/Link.h src/SymbolicLink.cpp headers/SymbolicLink.h src/HardLink.cpp headers/HardLink.h app.cpp src/FileSystem.cpp headers/FileSystem.h console-app/UserControlSystem.cpp console-app/UserControlSystem.h console-app/Logger.cpp console-app/Logger.h test/DirectoryTest.cpp test/DirectoryTest.h test/FileTest.cpp test/FileTest.h test/LinkTest.cpp test/LinkTest.h)
