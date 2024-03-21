//
// Created by Александр on 20.03.2024.
//

#ifndef TASK2_HARDLINK_H
#define TASK2_HARDLINK_H


#include "Link.h"
#include <iostream>

class HardLink : public Link {
public:
    HardLink(const std::string &objectName, Directory *parentObject, FileSystemObject *target)
            : Link(objectName, parentObject, target) {}

    void remove() override;

    void toString() override;
};


#endif //TASK2_HARDLINK_H
