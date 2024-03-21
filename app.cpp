//
// Created by Александр on 20.03.2024.
//

#include "headers/FileSystemObject.h"
#include "headers/FileSystem.h"
#include "headers/Directory.h"
#include "headers/File.h"
#include "headers/Link.h"
#include "headers/SymbolicLink.h"
#include "headers/HardLink.h"

#include <sstream>

void cd(const string &path, FileSystem *fileSystem, Directory *root) {
    if (path.empty()) {
        cout << "Invalid path." << endl;
        return;
    }

    Directory *targetDirectory = root;
    size_t start = 0;
    size_t end = path.find('/');

    while (end != string::npos) {
        string directory = path.substr(start, end - start);
        if (directory == "..") {
            if (targetDirectory->getParent() != nullptr) {
                targetDirectory = targetDirectory->getParent();
            }
        } else {
            bool found = false;
            for (auto &obj: targetDirectory->getObjects()) {
                if (obj->getName() == directory && dynamic_cast<Directory *>(obj) != nullptr) {
                    targetDirectory = dynamic_cast<Directory *>(obj);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Directory not found: " << directory << endl;
                return;
            }
        }
        start = end + 1;
        end = path.find('/', start);
    }

    string directory = path.substr(start);
    if (directory == "..") {
        if (targetDirectory->getParent() != nullptr) {
            targetDirectory = targetDirectory->getParent();
        }
    } else {
        bool found = false;
        for (auto &obj: targetDirectory->getObjects()) {
            if (obj->getName() == directory && dynamic_cast<Directory *>(obj) != nullptr) {
                targetDirectory = dynamic_cast<Directory *>(obj);
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Directory not found: " << directory << endl;
            return;
        }
    }
    fileSystem->setCurrentDirectory(targetDirectory);
    cout << "You are in: " << endl;
    fileSystem->getCurrentDirectory()->toString();
}

int main() {

    FileSystem home;
    Directory *root = home.getRootDirectory();

    string input;
    while (true) {
        cout << "Enter a command (mkdir, touch, move, rm, ls, cd, exit): ";
        getline(cin, input);

        stringstream ss(input);
        string command;
        ss >> command;

        if (command == "mkdir") {
            string dirname;
            ss >> dirname;
            if (dirname == "") {
                cout << "Incorrect filename" << endl;
                continue;
            }
            Directory *newDir = new Directory(dirname, home.getCurrentDirectory());
            root->addObject(newDir);
        } else if (command == "touch") {
            string filename, extension;
            size_t size;
            ss >> filename >> extension >> size;
            File *newFile = new File(filename, home.getCurrentDirectory(), extension, size);
            root->addObject(newFile);
        } else if (command == "rm") {
            string name;
            ss >> name;
            FileSystemObject *target = nullptr;
            for (auto &obj: home.getCurrentDirectory()->getObjects()) {
                if (obj->getName() == name) {
                    target = obj;
                    break;
                }
            }
            if (target == nullptr) {
                cout << "Object not found: " << name << endl;
            } else {
                target->remove();
            }
        } else if (command == "ls") {
            home.getCurrentDirectory()->printInner();
        } else if (command == "cd") {
            string path;
            ss >> path;
            cd(path, &home, root);
        } else if (command == "exit") {
            break;
        } else {
            cout << "Unknown command" << endl;
        }
    }


    return 0;
}

