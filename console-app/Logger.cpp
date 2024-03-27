//
// Created by Александр on 27.03.2024.
//

#include "Logger.h"
#include <iostream>

using namespace std;

void Logger::logAddObjectToDirectory() {
    cout << "Successfully added to directory" << endl;
}

void Logger::logIncorrectFileName() {
    cout << "Incorrect filename" << endl;
}

void Logger::logAlreadyExist(const string& name) {
    cout << "Object with name: " << name << " Already exists" << endl;
}

void Logger::logObjectNotFound(const string& name) {
    cout << "Object " << name << " not found" << endl;
}

void Logger::logUnknownCommand() {
    cout << "Unknown command" << endl;
}

void Logger::logIncorrectLinkType(const string& type) {
    cout << "Type: " << type << " isn't correct" << endl;
}

void Logger::logUnsuccessfullyRename(const string& name) {
    cout << "Can't rename root directory" << endl;
}

void Logger::logSuccessfullyRename(const string& name) {
    cout << "File System Object " << name << " renamed" << endl;
}

void Logger::logUnsuccessfullyMove(const string& name) {
    cout << "Can't move root directory" << endl;
}

void Logger::logSuccessfullyMove(const string& name) {
    cout << "File System Object " << name << " moved" << endl;
}

void Logger::logDelete(const string& name) {
    cout << "File System Object " << name << " Deleted" << endl;
}

void Logger::logExtensionChange(const string& extension) {
    cout << "Extension changed to " << extension << endl;
}

void Logger::logDest() {
    cout << "You are in: " << endl;
}

void Logger::logRoot() {
    cout << "Can't do this action with root" << endl;
}

