//
// Created by Александр on 20.03.2024.
//

#include "../headers/Directory.h"
#include <iostream>

using namespace std;

Directory::Directory(const string &objectName, Directory *parentObject)
        : FileSystemObject(objectName, parentObject) {}

Directory::~Directory() {
    cout << "Directory " << name << " Deleted" << endl;
    clearVector();
}

void Directory::remove() {
    clearVector();
    if (parent != nullptr) {
        parent->removeElement(getName());
    }
}

void Directory::clearVector() {
    for (auto obj: objects) {
        obj->remove();
    }
    objects.clear();
}

void Directory::rename(const string &newName) {
    FileSystemObject::rename(newName);
}

void Directory::move(Directory *oldDirectory, Directory *newDirectory) {
    destination = newDirectory->getDestination() + "/" + name;
    newDirectory->addObject(this);
    oldDirectory->removeElement(name);
    setParent(newDirectory);
    modifyDate();
}

void Directory::removeElement(const string &elementName) {
    for (int i = 0; i < objects.size(); ++i) {
        if (objects[i]->getName() == elementName) {
            delete objects[i];
            objects.erase(objects.begin() + i);
            return;
        }
    }
    modifyDate();
}

void Directory::addObject(FileSystemObject *object) {
    object->setDestination(destination + "/" + object->getName());
    object->setParent(this);
    objects.push_back(object);
    modifyDate();
}

void Directory::toString() {
    cout << "Type: Directory" << endl;
    FileSystemObject::toString();
}

const vector<FileSystemObject *> &Directory::getObjects() const {
    return objects;
}

void Directory::printInner() {
    cout << "------------------------------" << endl;
    toString();
    cout << "Contents:" << endl;
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->toString();
    }
    cout << "------------------------------" << endl;
}

