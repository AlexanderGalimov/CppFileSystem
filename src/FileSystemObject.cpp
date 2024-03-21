//
// Created by Александр on 20.03.2024.
//

#include "../headers/FileSystemObject.h"
#include <iostream>

using namespace std;

FileSystemObject::FileSystemObject(const string &objectName, Directory *parentObject) {
    this->name = objectName;
    time_t currDate = time(0);
    this->dateOfCreation = ctime(&currDate);
    this->modificationDate = ctime(&currDate);
    this->destination = objectName;
    this->parent = parentObject;
}

FileSystemObject::~FileSystemObject() {
}

void FileSystemObject::remove() {
    delete this;
}

void FileSystemObject::modifyDate() {
    time_t currDate = time(0);
    modificationDate = ctime(&currDate);
}

const string &FileSystemObject::getName() const {
    return name;
}

const string &FileSystemObject::getModificationDate() const {
    return modificationDate;
}

const string &FileSystemObject::getDateOfCreation() const {
    return dateOfCreation;
}

const string &FileSystemObject::getDestination() const {
    return destination;
}

void FileSystemObject::setDestination(const string &newDestination) {
    destination = newDestination;
}

void FileSystemObject::setParent(Directory *newParent) {
    parent = newParent;
}

Directory *FileSystemObject::getParent() const {
    return parent;
}

void FileSystemObject::rename(const string &newName) {
    name = newName;
    size_t slashIndex = newName.find_last_of('/');
    destination = newName.substr(0, slashIndex + 1);
    modifyDate();
    cout << "Name changed to: " << newName << endl;
}

void FileSystemObject::toString() {
    cout << "Name: " << name << endl;
    cout << "Destination: " << destination << endl;
    cout << "Date of creation: " << dateOfCreation;
    cout << "Modification date: " << modificationDate;
}
