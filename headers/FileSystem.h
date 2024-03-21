//
// Created by Александр on 20.03.2024.
//

#ifndef TASK2_FILESYSTEM_H
#define TASK2_FILESYSTEM_H

#include "Directory.h"

class FileSystem {
private:
    Directory root;
    Directory *currentDirectory;

public:
    FileSystem();

    Directory *getRootDirectory();

    virtual ~FileSystem();

    Directory *getCurrentDirectory() const;

    void setCurrentDirectory(Directory *currentDirectory);

};


#endif //TASK2_FILESYSTEM_H
