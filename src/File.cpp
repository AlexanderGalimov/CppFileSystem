//
// Created by Александр on 20.03.2024.
//

#include "../headers/File.h"
#include <iostream>

using namespace std;

File::~File() {
    cout << "File " << name << " Deleted" << endl;
}

void File::setExtension(const string &newExtension) {
    extension = newExtension;
    modifyDate();
}

void File::remove() {
    if (parent != nullptr) {
        parent->removeElement(getName());
    }
    else{
        delete this;
    }
}

void File::move(Directory *oldDirectory, Directory *newDirectory) {
    destination = newDirectory->getDestination() + "/" + name;
    newDirectory->addObject(this);
    oldDirectory->unlinkElement(name);
    setParent(newDirectory);
    modifyDate();
}

void File::toString() {
    cout << "Type: File" << endl;
    FileSystemObject::toString();
    cout << "extension: " << extension << endl;
    cout << "size: " << size << endl;
}

const string &File::getExtension() const {
    return extension;
}

size_t File::getSize() const {
    return size;
}

void File::setSize(size_t newSize) {
    File::size = newSize;
}

File::File(const string &objectName, Directory *parentObject, const string &extension, size_t size) : FileSystemObject(
        objectName, parentObject), extension(extension), size(size) {}



