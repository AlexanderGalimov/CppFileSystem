//
// Created by Александр on 20.03.2024.
//

#include "../headers/FileSystem.h"

FileSystem::FileSystem() : root("root", &root) {
    currentDirectory = &root;
    currentDirectory->setDestination("/");
}

FileSystem::~FileSystem() {
    cout << "File system deleted" << endl;
}

Directory *FileSystem::getRootDirectory() {
    return &root;
}

Directory *FileSystem::getCurrentDirectory() const {
    return currentDirectory;
}


void FileSystem::setCurrentDirectory(Directory *newCurrentDirectory) {
    FileSystem::currentDirectory = newCurrentDirectory;
}
