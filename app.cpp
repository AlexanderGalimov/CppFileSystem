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

//4.	Файловая система.
// Необходимо смоделировать файловую систему ОС Unix (без прав доступа).
// Файловая система состоит из папок, фалов и ссылок.
// Ссылки бывают 2-х видов жесткие и символьные
// (при удалении жесткой ссылки удаляется заодно и сам файл/папка, на который эта ссылка ссылается, точнее оба имени являются абсолютно равноправными).
// Файлы имеют размер, расширение, кроме того файлы и папки имеют атрибуты: время создания, время изменения и т.п.
// Файловая система имеет только один корень, представляющий собой папку, которую нельзя удалить.
// Для каждого элемента файловой системы предусмотреть операции создания, переименования, перемещения, изменения (меняется дата изменения) и удаления.


class Logger {
public:

    static void logAddObjectToDirectory() {
        cout << "Successfully added to directory" << endl;
    }

    static void logIncorrectFileName() {
        cout << "Incorrect filename" << endl;
    }

    static void logAlreadyExist(const string &name) {
        cout << "Object with name: " << name << " Already exists" << endl;
    }

    static void logObjectNotFound(const string &name) {
        cout << "Object " << name << " " << "not found" << endl;
    }

    static void logUnknownCommand() {
        cout << "Unknown command" << endl;
    }

    static void logIncorrectLinkType(const string &type) {
        cout << "Type: " << type << " " << "isn't correct" << endl;
    }

    static void logUnsuccessfullyRename(const string &name) {
        cout << "Can't rename root directory" << endl;
    }

    static void logSuccessfullyRename(const string &name) {
        cout << "File System Object " << name << " renamed" << endl;
    }

    static void logUnsuccessfullyMove(const string &name) {
        cout << "Can't move root directory" << endl;
    }

    static void logSuccessfullyMove(const string &name) {
        cout << "File System Object " << name << " moved" << endl;
    }

    static void logDelete(const string &name) {
        cout << "File System Object " << name << " Deleted" << endl;
    }

    static void logExtensionChange(const string &extension) {
        cout << "Extension changed to" << extension << endl;
    }

    static void logDest() {
        cout << "You are in: " << endl;
    }

    static void logRoot() {
        cout << "Can't do this action with root" << endl;
    }
};

class UserControlSystem {
private:
    FileSystem *home;
    Directory *root;

public:
    UserControlSystem(FileSystem *home) : home(home) {
        root = home->getRootDirectory();
    }

    virtual ~UserControlSystem() {
    }

    void mkdir(const string &dirName) {
        Directory *newDir = new Directory(dirName, home->getCurrentDirectory());
        Directory *currDir = home->getCurrentDirectory();
        currDir->addObject(newDir);
    }

    void ls() {
        home->getCurrentDirectory()->printInner();
    }

    FileSystemObject *findInCurrent(const string &name) {
        FileSystemObject *target = nullptr;
        for (auto &obj: home->getCurrentDirectory()->getObjects()) {
            if (obj->getName() == name) {
                target = obj;
                break;
            }
        }
        return target;
    }

    void rm(const string &name) {
        FileSystemObject *target = findInCurrent(name);
        if (target == nullptr) {
            Logger::logObjectNotFound(name);
        } else {
            Link *link = dynamic_cast<Link *>(target);
            if (link != nullptr) {
                if (link->getTarget()->getName() == "root" || link->getTarget()->getDestination() == "/") {
                    Logger::logRoot();
                    return;
                }
            }
            target->remove();
        }
    }

    void move(const string &name, const string &destination) {
        FileSystemObject *object = findInCurrent(name);

        if (object == nullptr) {
            Logger::logIncorrectFileName();
            return;
        }
        if (destination[0] == '/') {
            Directory *directory = findDirectory(destination);
            if (directory == nullptr) {
                Logger::logObjectNotFound(destination);
                return;
            } else {
                object->move(home->getCurrentDirectory(), directory);
            }
        } else {
            FileSystemObject *target = findInCurrent(destination);
            if (target != nullptr) {
                Logger::logAlreadyExist(destination);
            } else {
                object->rename(destination);
            }
        }
    }

    void touchLink(const string &name, const string &type, const string &path, const string &ext, size_t size) {
        FileSystemObject *targetObject = findObjectInPath(path);
        if (targetObject != nullptr) {
            if (type == "-s") {
                SymbolicLink *newLink = new SymbolicLink(name, home->getCurrentDirectory(), targetObject, ext, size);
                home->getCurrentDirectory()->addObject(newLink);
            } else {
                HardLink *newLink = new HardLink(name, home->getCurrentDirectory(), targetObject, ext, size);
                home->getCurrentDirectory()->addObject(newLink);
            }
        } else {
            Logger::logObjectNotFound(name);
        }
    }

    void touchFile(const string &name, const string &ext, size_t size) {
        File *newFile = new File(name, home->getCurrentDirectory(), ext, size);
        home->getCurrentDirectory()->addObject(newFile);
    }

    FileSystemObject *findObjectInPath(const string &path) {
        if (path.empty()) {
            Logger::logIncorrectFileName();
            return nullptr;
        }

        if (path == "/") {
            return root;
        }

        Directory *current = home->getRootDirectory();

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

        for (const string &comp: components) {
            for (FileSystemObject *object: current->getObjects()) {
                if (object->getName() == comp) {
                    return object;
                }
            }
        }
        return nullptr;
    }

    Directory *findDirectory(const string &path) {
        if (path.empty()) {
            Logger::logIncorrectFileName();
            return nullptr;
        }

        Directory *oldCurr = home->getCurrentDirectory();

        if (path == "..") {
            return oldCurr->getParent();
        }

        Directory *current;

        if (path == "root" || path == "/") {
            return home->getRootDirectory();
        } else {
            current = home->getCurrentDirectory();
        }

        vector<string> components;
        stringstream ss(path);
        string component;
        while (getline(ss, component, '/')) {
            if (!component.empty() && component != ".") {
                components.push_back(component);
            }
        }
        bool found;
        for (const string &comp: components) {
            found = false;
            for (FileSystemObject *object: current->getObjects()) {
                Directory *dir = dynamic_cast<Directory *>(object);
                if (dir && dir->getName() == comp) {
                    current = dir;
                    found = true;
                    break;
                }

                SymbolicLink *symbolicLink = dynamic_cast<SymbolicLink *>(object);
                if (symbolicLink && symbolicLink->getName() == comp) {
                    FileSystemObject *target = symbolicLink->getTarget();
                    Directory *targetDir = dynamic_cast<Directory *>(target);
                    if (targetDir) {
                        current = targetDir;
                        found = true;
                        break;
                    }
                }

                SymbolicLink *hardLink = dynamic_cast<SymbolicLink *>(object);
                if (hardLink && hardLink->getName() == comp) {
                    FileSystemObject *target = hardLink->getTarget();
                    Directory *targetDir = dynamic_cast<Directory *>(target);
                    if (targetDir) {
                        current = targetDir;
                        found = true;
                        break;
                    }
                }
            }
        }
        if (!found) {
            return nullptr;
        }
        return current;
    }

    void cd(const string &path) {
        Directory *directory = findDirectory(path);
        if (directory == nullptr) {
            Logger::logObjectNotFound(path);
        } else {
            home->setCurrentDirectory(directory);
            Logger::logDest();
            home->getCurrentDirectory()->toString();
        }
    }
};


int main() {

    FileSystem home;
    UserControlSystem *userControlSystem = new UserControlSystem(&home);

    string input;
    while (true) {
        cout << "Enter a command (mkdir, touch, move, rm, ls, cd, man, exit):";
        getline(cin, input);

        stringstream ss(input);
        string command;
        ss >> command;

        if (command == "mkdir") {
            string dirname;
            ss >> dirname;
            if (dirname == "" || dirname == "root") {
                Logger::logIncorrectFileName();
                continue;
            } else {
                userControlSystem->mkdir(dirname);
            }
        } else if (command == "touch") {
            string filename, extension;
            size_t size;
            ss >> filename >> extension >> size;

            userControlSystem->touchFile(filename, extension, size);
        } else if (command == "ln") {
            string filename, extension, targetPath, type;
            size_t size;
            ss >> type >> filename >> targetPath >> extension >> size;
            if (type == "-s" || type == "-h") {
                userControlSystem->touchLink(filename, type, targetPath, extension, size);
            } else {
                Logger::logIncorrectLinkType(type);
            }
        } else if (command == "rm") {
            string name;
            ss >> name;
            if (name == "root") {
                Logger::logIncorrectFileName();
            } else {
                userControlSystem->rm(name);
            }
        } else if (command == "ls") {
            userControlSystem->ls();
        } else if (command == "cd") {
            string path;
            ss >> path;

            userControlSystem->cd(path);
        } else if (command == "mv") {
            string name, destination;
            ss >> name >> destination;
            if (name == "" || destination == "" || name == "root") {
                Logger::logIncorrectFileName();
            } else {
                userControlSystem->move(name, destination);
            }
        } else if (command == "man") {
            cout << "User manual" << endl;
            cout << "1) mkdir directoryName" << endl;
            cout << "2) touch filename extension size" << endl;
            cout << "3) ln type(-s/-h) linkName targetPath extension size" << endl;
            cout << "4) ls" << endl;
            cout << "5) cd path" << endl;
            cout << "6) mv filename path" << endl;
        } else if (command == "exit") {
            break;
        } else {
            cout << "Unknown command" << endl;
        }
    }

    return 0;
}

