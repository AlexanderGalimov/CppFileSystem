//
// Created by Александр on 20.03.2024.
//

#include "../headers/HardLink.h"
#include <iostream>

void HardLink::remove() {
    if(target->getDestination() != "/"){
        target->remove();
    }
    Link::remove();
}

void HardLink::toString() {
    cout << "Type: Hard Link" << endl;
    Link::toString();
}

HardLink::HardLink(const string &objectName, Directory *parentObject, FileSystemObject *target, const string &extension,
                   size_t size) : Link(objectName, parentObject, target, extension, size) {}
