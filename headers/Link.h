//
// Created by Александр on 20.03.2024.
//

#ifndef TASK2_LINK_H
#define TASK2_LINK_H


#include "FileSystemObject.h"
#include "Directory.h"
#include <iostream>

using namespace std;

class Link : public FileSystemObject {
protected:
    FileSystemObject *target;
    string extension;
    size_t size;

public:
    Link(const string &objectName, Directory *parentObject, FileSystemObject *target, const string &extension,
         size_t size);

    ~Link();

    void remove() override;

    void move(Directory *oldDirectory, Directory *newDirectory) override;

    virtual void toString() override;

    void setTarget(FileSystemObject *newTarget);

    FileSystemObject *getTarget() const;

    void setExtension(const string &extension);

    void setSize(size_t size);

    const string &getExtension() const;

    size_t getSize() const;
};


#endif //TASK2_LINK_H
