//
// Created by Александр on 20.03.2024.
//

#ifndef TASK2_HARDLINK_H
#define TASK2_HARDLINK_H


#include "Link.h"
#include <iostream>

class HardLink : public Link {
public:

    HardLink(const string &objectName, Directory *parentObject, FileSystemObject *target, const string &extension,
             size_t size);

    void remove() override;

    void toString() override;
};


#endif //TASK2_HARDLINK_H
