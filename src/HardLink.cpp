//
// Created by Александр on 20.03.2024.
//

#include "../headers/HardLink.h"
#include <iostream>

void HardLink::remove() {
    delete target;
    Link::remove();
}

void HardLink::toString() {
    cout << "Type: Hard Link" << endl;
    Link::toString();
}
