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
}

void Directory::remove() {
    clearVector();
    if (parent != nullptr) {
        parent->removeElement(name);
    } else{
        delete this;
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

bool Directory::isRoot(){
    if(destination == "/" && name == "root"){
        return true;
    }
    else{
        return false;
    }
}

void Directory::move(Directory *oldDirectory, Directory *newDirectory) {
    if(isRoot()){
        return;
    }
    destination = newDirectory->getDestination() + "/" + name;
    newDirectory->addObject(this);
    oldDirectory->unlinkElement(name);
    setParent(newDirectory);
    modifyDate();
}

void Directory::removeElement(const string &elementName) {
    int index = getElementIndex(elementName);
    if (index != -1){
        delete objects[index];
        objects.erase(objects.begin() + index);
        modifyDate();
    }
}

int Directory::getElementIndex(const string& elementName){
    for (int i = 0; i < objects.size(); ++i) {
        if (objects[i]->getName() == elementName) {
            return i;
        }
    }
    return -1;
}

void Directory::unlinkElement(const string& elementName){
    int index = getElementIndex(elementName);
    objects.erase(objects.begin() + index);
}

void Directory::addObject(FileSystemObject *object) {
    if(isRoot()){
        object->setDestination(destination + object->getName());
    } else{
        object->setDestination(destination + "/" + object->getName());
    }
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

