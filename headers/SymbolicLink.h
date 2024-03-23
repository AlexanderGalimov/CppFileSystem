
//
// Created by Александр on 20.03.2024.
//

#ifndef TASK2_SYMBOLICLINK_H
#define TASK2_SYMBOLICLINK_H

#include "Link.h"
#include <iostream>

using namespace std;

class SymbolicLink : public Link {
public:
    SymbolicLink(const string &objectName, Directory *parentObject, FileSystemObject *target, const string &extension,
                 size_t size);

    void toString() override;
};


#endif //TASK2_SYMBOLICLINK_H
