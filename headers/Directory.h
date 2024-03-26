//
// Created by Александр on 20.03.2024.
//

#ifndef TASK2_DIRECTORY_H
#define TASK2_DIRECTORY_H

#include "FileSystemObject.h"
#include <vector>

using namespace std;

class Directory : public FileSystemObject {
protected:
    vector<FileSystemObject *> objects;

public:
    Directory(const string &objectName, Directory *parentObject);

    ~Directory();

    void remove() override;

    void clearVector();

    void rename(const string &newName) override;

    int getElementIndex(const string& name);

    void removeElement(const string &elementName);

    void unlinkElement(const string& elementName);

    void addObject(FileSystemObject *object);

    void toString() override;

    void printInner();

    bool isRoot();

    const vector<FileSystemObject *> &getObjects() const;

    void move(Directory *oldDirectory, Directory *newDirectory) override;
};

#endif //TASK2_DIRECTORY_H
