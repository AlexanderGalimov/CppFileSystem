//
// Created by Александр on 20.03.2024.
//

#include "../headers/SymbolicLink.h"
#include <iostream>
using namespace std;

void SymbolicLink::toString() {
    cout << "Type: Symbolic Link" << endl;
    Link::toString();
}

