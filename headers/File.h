//
// Created by Александр on 20.03.2024.
//

#ifndef TASK2_FILE_H
#define TASK2_FILE_H

#include "FileSystemObject.h"
#include "Directory.h"
#include <iostream>

using namespace std;

class File : public FileSystemObject {
protected:
    string extension;
    size_t size;

public:
    File(const string &objectName, Directory *parentObject, const string &extension, size_t size);

    ~File();

    void setExtension(const string &newExtension);

    void move(Directory *oldDirectory, Directory *newDirectory) override;

    void remove() override;

    void toString() override;

    const string &getExtension() const;

    size_t getSize() const;

    void setSize(size_t size);
};

#endif //TASK2_FILE_H
