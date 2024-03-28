//
// Created by Александр on 27.03.2024.
//

#ifndef TASK2_USERCONTROLSYSTEM_H
#define TASK2_USERCONTROLSYSTEM_H


#include "../headers/FileSystem.h"
#include "../headers/Directory.h"
#include "../headers/File.h"
#include "../headers/SymbolicLink.h"
#include "../headers/HardLink.h"

class UserControlSystem {
private:
    FileSystem* home;

public:
    UserControlSystem(FileSystem* home);

    virtual ~UserControlSystem();

    void mkdir(const string& dirName);

    void ls();

    FileSystemObject* findInCurrent(const string& name);

    void rm(const string& path);

    void move(const string& name, const string& destination);

    void touchLink(const string& name, const string& type, const string& path, const string& ext, size_t size);

    void touchFile(const string& name, const string& ext, size_t size);

    FileSystemObject* findObjectInPath(const string& path);

    Directory* findDirectory(const string& path);

    void cd(const string& path);
};


#endif //TASK2_USERCONTROLSYSTEM_H
