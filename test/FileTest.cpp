//
// Created by Александр on 27.03.2024.
//

#include "FileTest.h"

#include <iostream>
#include <cassert>

using namespace std;

void FileTest::runTests(File* testingFile) {
    cout << "-----------------------------" << endl;
    cout << "File tests" << endl;
    cout << "-----------------------------" << endl;
    testingFile->setDestination("/Directory");

    // getName(), getDateOfCreation(), getModificationDate()
    assert(testingFile->getName() == "File");
    cout << "getName() Test Passed" << endl;

    assert(!testingFile->getDateOfCreation().empty());
    cout << "getDateOfCreation() Test Passed" << endl;

    assert(!testingFile->getModificationDate().empty());
    cout << "getModificationDate() Test Passed" << endl;

    // getExtension()
    testingFile->setExtension("txt");
    assert(testingFile->getExtension() == "txt");
    cout << "setExtension(), getExtension() Test Passed" << endl;

    // rename()
    testingFile->rename("NewFile");
    assert(testingFile->getName() == "NewFile");
    cout << "rename() Test Passed" << endl;

    // move()
    Directory* oldDirectory = new Directory("OldDirectory", nullptr);
    Directory* newDirectory = new Directory("NewDirectory", nullptr);
    oldDirectory->setDestination("/OldDirectory");
    newDirectory->setDestination("/NewDirectory");
    testingFile->move(oldDirectory, newDirectory);
    assert(testingFile->getDestination() == "/NewDirectory/NewFile");
    cout << "move() Test Passed" << endl;

    // remove()
    testingFile->remove();
    cout << "remove() Test Passed" << endl;
}
