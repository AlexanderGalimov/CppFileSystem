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

public:
    Link(const string &objectName, Directory *parentObject, FileSystemObject *target);

    ~Link();

    void remove() override;

    void move(Directory *oldDirectory, Directory *newDirectory);

    virtual void toString() override;

    void setTarget(FileSystemObject *newTarget);

    FileSystemObject *getTarget() const;
};


#endif //TASK2_LINK_H