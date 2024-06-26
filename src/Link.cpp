//
// Created by Александр on 20.03.2024.
//

#include "../headers/FileSystemObject.h"
#include "../headers/Directory.h"
#include "../headers/Link.h"
#include <iostream>

using namespace std;

Link::Link(const string &objectName, Directory *parentObject, FileSystemObject *target, const string &extension,
           size_t size) : FileSystemObject(objectName, parentObject), target(target), extension(extension),
                          size(size) {}

Link::~Link() {
    cout << "Link " << name << " Deleted" << endl;
}

void Link::remove() {
    if (parent != nullptr) {
        parent->removeElement(name);
    }
    else{
        delete this;
    }
}

void Link::move(Directory *oldDirectory, Directory *newDirectory) {
    destination = newDirectory->getDestination() + "/" + name;
    newDirectory->addObject(this);
    oldDirectory->unlinkElement(name);
    setParent(newDirectory);
    modifyDate();
}

void Link::toString() {
    FileSystemObject::toString();
    cout << "Points to: " << endl;
    target->toString();
}

void Link::setTarget(FileSystemObject *newTarget) {
    target = newTarget;
    modifyDate();
}

FileSystemObject *Link::getTarget() const {
    return target;
}

void Link::setExtension(const string &newExtension) {
    Link::extension = newExtension;
}

void Link::setSize(size_t newSize) {
    Link::size = newSize;
}

const string &Link::getExtension() const {
    return extension;
}

size_t Link::getSize() const {
    return size;
}
