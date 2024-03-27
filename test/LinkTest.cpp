//
// Created by Александр on 27.03.2024.
//

#include <iostream>
#include <cassert>
#include "LinkTest.h"

using namespace std;

void LinkTest::runTests(Link* testingLink) {
    cout << "-----------------------------" << endl;
    cout << "Link tests" << endl;
    cout << "-----------------------------" << endl;
    testingLink->setDestination("/Directory");

    // getName(), getDateOfCreation(), getModificationDate()
    assert(testingLink->getName() == "Link");
    cout << "getName() Test Passed" << endl;

    assert(!testingLink->getDateOfCreation().empty());
    cout << "getDateOfCreation() Test Passed" << endl;

    assert(!testingLink->getModificationDate().empty());
    cout << "getModificationDate() Test Passed" << endl;

    // getExtension(), getSize()
    testingLink->setExtension("txt");
    assert(testingLink->getExtension() == "txt");
    cout << "setExtension(), getExtension() Test Passed" << endl;

    testingLink->setSize(100);
    assert(testingLink->getSize() == 100);
    cout << "setSize(), getSize() Test Passed" << endl;

    // move()
    Directory* oldDirectory = new Directory("OldDirectory", nullptr);
    Directory* newDirectory = new Directory("NewDirectory", nullptr);
    oldDirectory->setDestination("/OldDirectory");
    newDirectory->setDestination("/NewDirectory");
    testingLink->move(oldDirectory, newDirectory);
    assert(testingLink->getDestination() == "/NewDirectory/Link");
    cout << "move() Test Passed" << endl;

    oldDirectory->remove();
    newDirectory->remove();

    // remove()
    testingLink->remove();
    cout << "remove() Test Passed" << endl;
}

