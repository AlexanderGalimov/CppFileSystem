//
// Created by Александр on 27.03.2024.
//

#include <iostream>
#include <cassert>
#include "DirectoryTest.h"

using namespace std;

void DirectoryTest::runTests(Directory* testingDirectory) {
    cout << "-----------------------------" << endl;
    cout << "Directory tests" << endl;
    cout << "-----------------------------" << endl;
    testingDirectory->setDestination("/Directory");

    // getName(), getDateOfCreation(), getModificationDate()
    assert(testingDirectory->getName() == "Directory");
    cout << "getName() Test Passed" << endl;

    assert(!testingDirectory->getDateOfCreation().empty());
    cout << "getDateOfCreation() Test Passed" << endl;

    assert(!testingDirectory->getModificationDate().empty());
    cout << "getModificationDate() Test Passed" << endl;

    // getDestination()
    assert(testingDirectory->getDestination() == "/Directory");
    cout << "setDestination(), getDestination() Test Passed" << endl;

    // rename()
    testingDirectory->rename("newName");
    assert(testingDirectory->getName() == "newName");
    assert(testingDirectory->getDestination() == "/newName");
    cout << "rename() Test Passed" << endl;

    // addObject(), getObjects()
    Directory* directory = new Directory("dirName", nullptr);
    testingDirectory->addObject(directory);
    const vector<FileSystemObject*>& objects = testingDirectory->getObjects();
    assert(objects.size() == 1);
    assert(objects[0] == directory);
    cout << "addObject(), getObjects() Test Passed" << endl;

    // removeElement()
    testingDirectory->removeElement("dirName");
    assert(objects.size() == 0);
    cout << "removeElement() Test Passed" << endl;

    // move()
    Directory* oldDirectory = new Directory("OldDirectory", nullptr);
    oldDirectory->setDestination("/OldDirectory");
    Directory* newDirectory = new Directory("NewDirectory", nullptr);
    newDirectory->setDestination("/NewDirectory");
    testingDirectory->move(oldDirectory, newDirectory);
    assert(testingDirectory->getDestination() == "/NewDirectory/newName");
    cout << "move() Test Passed" << endl;

    testingDirectory->removeElement(oldDirectory->getName());
    testingDirectory->removeElement(newDirectory->getName());
    testingDirectory->remove();
}

