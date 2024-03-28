//
// Created by Александр on 27.03.2024.
//

#include <sstream>
#include "UserControlSystem.h"
#include "Logger.h"

UserControlSystem::UserControlSystem(FileSystem* home) : home(home) {}

UserControlSystem::~UserControlSystem() {}

void UserControlSystem::mkdir(const string& dirName) {
    Directory* newDir = new Directory(dirName, home->getCurrentDirectory());
    Directory* currDir = home->getCurrentDirectory();
    currDir->addObject(newDir);
}

void UserControlSystem::ls() {
    home->getCurrentDirectory()->printInner();
}

FileSystemObject* UserControlSystem::findInCurrent(const string& name) {
    FileSystemObject* target = nullptr;
    for (auto& obj : home->getCurrentDirectory()->getObjects()) {
        if (obj->getName() == name) {
            target = obj;
            break;
        }
    }
    return target;
}

void UserControlSystem::rm(const string& path) {
    FileSystemObject* target = findObjectInPath(path);
    if (target == nullptr) {
        Logger::logObjectNotFound(path);
    } else {
        Link* link = dynamic_cast<Link*>(target);
        if (link->getTarget()->getName() == "root" || link->getTarget()->getDestination() == "/") {
            Logger::logRoot();
            return;
        }
        target->remove();
    }
}

void UserControlSystem::move(const string& name, const string& destination) {
    FileSystemObject* object = findInCurrent(name);

    if (object == nullptr) {
        Logger::logIncorrectFileName();
        return;
    }
    if (destination[0] == '/') {
        Directory* directory = findDirectory(destination);
        if (directory == nullptr) {
            Logger::logObjectNotFound(destination);
            return;
        } else {
            object->move(home->getCurrentDirectory(), directory);
        }
    } else {
        FileSystemObject* target = findInCurrent(destination);
        if (target != nullptr) {
            Logger::logAlreadyExist(destination);
        } else {
            object->rename(destination);
        }
    }
}

void UserControlSystem::touchLink(const string& name, const string& type, const string& path, const string& ext, size_t size) {
    FileSystemObject* targetObject = findObjectInPath(path);
    if (targetObject != nullptr) {
        if (type == "-s") {
            SymbolicLink* newLink = new SymbolicLink(name, home->getCurrentDirectory(), targetObject, ext, size);
            home->getCurrentDirectory()->addObject(newLink);
        } else {
            HardLink* newLink = new HardLink(name, home->getCurrentDirectory(), targetObject, ext, size);
            home->getCurrentDirectory()->addObject(newLink);
        }
    } else {
        Logger::logObjectNotFound(name);
    }
}

void UserControlSystem::touchFile(const string& name, const string& ext, size_t size) {
    File* newFile = new File(name, home->getCurrentDirectory(), ext, size);
    home->getCurrentDirectory()->addObject(newFile);
}

FileSystemObject* UserControlSystem::findObjectInPath(const string& path) {
    if (path == "/") {
        return home->getRootDirectory();
    }

    Directory* current = home->getRootDirectory();

    if (path == "..") {
        return current->getParent();
    }

    vector<string> components;
    stringstream ss(path);
    string component;
    while (getline(ss, component, '/')) {
        if (!component.empty() && component != ".") {
            components.push_back(component);
        }
    }

    FileSystemObject* foundObject = nullptr;
    for (const string& comp : components) {
        foundObject = nullptr;
        for (FileSystemObject* object : current->getObjects()) {
            if (object->getName() == comp) {
                foundObject = object;
                break;
            }
        }
        if (foundObject == nullptr) {
            return nullptr;
        }

        if (dynamic_cast<Directory*>(foundObject)) {
            current = static_cast<Directory*>(foundObject);
        }
    }
    return foundObject;
}


Directory* UserControlSystem::findDirectory(const string& path) {
    if (path == "/") {
        return home->getRootDirectory();
    }

    if (path == "..") {
        Directory* current = home->getCurrentDirectory();
        return current->getParent();
    }

    vector<string> components;
    stringstream ss(path);
    string component;
    while (getline(ss, component, '/')) {
        if (!component.empty() && component != ".") {
            components.push_back(component);
        }
    }

    Directory* current = home->getRootDirectory();

    for (const string& comp : components) {
        bool found = false;
        for (FileSystemObject* object : current->getObjects()) {
            Directory* dir = dynamic_cast<Directory*>(object);
            if (dir && dir->getName() == comp) {
                current = dir;
                found = true;
                break;
            }

            SymbolicLink* symbolicLink = dynamic_cast<SymbolicLink*>(object);
            if (symbolicLink && symbolicLink->getName() == comp) {
                FileSystemObject* target = symbolicLink->getTarget();
                Directory* targetDir = dynamic_cast<Directory*>(target);
                if (targetDir) {
                    current = targetDir;
                    found = true;
                    break;
                }
            }

            HardLink* hardLink = dynamic_cast<HardLink*>(object);
            if (hardLink && hardLink->getName() == comp) {
                FileSystemObject* target = hardLink->getTarget();
                Directory* targetDir = dynamic_cast<Directory*>(target);
                if (targetDir) {
                    current = targetDir;
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            return nullptr;
        }
    }

    return current;
}


void UserControlSystem::cd(const string& path) {
    Directory* directory = findDirectory(path);
    if (directory == nullptr) {
        Logger::logObjectNotFound(path);
    } else {
        home->setCurrentDirectory(directory);
        Logger::logDest();
        home->getCurrentDirectory()->toString();
    }
}

