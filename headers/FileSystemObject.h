//
// Created by Александр on 20.03.2024.
//

#ifndef TASK2_FILESYSTEMOBJECT_H
#define TASK2_FILESYSTEMOBJECT_H


#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Directory;

class FileSystemObject {
protected:
    string name;
    string dateOfCreation;
    string modificationDate;
    string destination;
    Directory *parent;

public:
    FileSystemObject(const string &objectName, Directory *parentObject);

    virtual ~FileSystemObject();

    virtual void remove() = 0;

    void modifyDate();

    const string &getName() const;

    const string &getModificationDate() const;

    const string &getDateOfCreation() const;

    const string &getDestination() const;

    virtual void move(Directory *oldDirectory, Directory *newDirectory) = 0;

    void setDestination(const string &newDestination);

    void setParent(Directory *newParent);

    virtual void rename(const string &newName);

    virtual void toString();

    Directory *getParent() const;
};

#endif //TASK2_FILESYSTEMOBJECT_H
