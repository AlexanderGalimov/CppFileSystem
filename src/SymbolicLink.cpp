//
// Created by Александр on 20.03.2024.
//

#include "../headers/SymbolicLink.h"
#include <iostream>
using namespace std;

SymbolicLink::SymbolicLink(const string &objectName, Directory *parentObject, FileSystemObject *target,
                           const string &extension, size_t size) : Link(objectName, parentObject, target, extension,
                                                                        size) {}

void SymbolicLink::toString() {
    cout << "Type: Symbolic Link" << endl;
    Link::toString();
}

