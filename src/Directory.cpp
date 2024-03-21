//
// Created by Александр on 20.03.2024.
//

#include "../headers/Directory.h"
#include <iostream>

Directory::Directory(const std::string &objectName, Directory *parentObject)
        : FileSystemObject(objectName, parentObject) {}

Directory::~Directory() {
    clearVector();
    std::cout << "Directory " << name << " Deleted" << std::endl;
}

void Directory::remove() {
    if (name == "root") {
        return;
    } else {
        clearVector();
        if (parent != nullptr) {
            parent->removeElement(getName());
        }
    }
}

void Directory::clearVector() {
    for (auto obj: objects) {
        obj->remove();
    }
    objects.clear();
}

void Directory::rename(const std::string &newName) {
    if (name == "root") {
        std::cout << "Can't rename root directory";
    } else {
        FileSystemObject::rename(newName);
    }
}

void Directory::move(Directory *oldDirectory, Directory *newDirectory) {
    if (name == "root") {
        std::cout << "Can't move root directory" << std::endl;
    } else {
        destination = newDirectory->getDestination() + "/" + name;
        newDirectory->addObject(this);
        oldDirectory->removeElement(name);
        setParent(newDirectory);
        modifyDate();
    }
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
    cout << "Element successfully removed" << endl;
}

void Directory::addObject(FileSystemObject *object) {
    objects.push_back(object);
    object->setDestination(destination + "/" + object->getName());
    object->setParent(this);
    modifyDate();
    cout << "Successfully added" << endl;
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

