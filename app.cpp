//
// Created by Александр on 20.03.2024.
//

#include "headers/FileSystem.h"
#include "headers/File.h"
#include "console-app/UserControlSystem.h"
#include "console-app/Logger.h"
#include "test/DirectoryTest.h"
#include "test/FileTest.h"
#include "test/LinkTest.h"

#include <sstream>

//4.	Файловая система.
// Необходимо смоделировать файловую систему ОС Unix (без прав доступа).
// Файловая система состоит из папок, фалов и ссылок.
// Ссылки бывают 2-х видов жесткие и символьные
// (при удалении жесткой ссылки удаляется заодно и сам файл/папка, на который эта ссылка ссылается, точнее оба имени являются абсолютно равноправными).
// Файлы имеют размер, расширение, кроме того файлы и папки имеют атрибуты: время создания, время изменения и т.п.
// Файловая система имеет только один корень, представляющий собой папку, которую нельзя удалить.
// Для каждого элемента файловой системы предусмотреть операции создания, переименования, перемещения, изменения (меняется дата изменения) и удаления.

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
            size_t size = -1;
            ss >> filename >> extension >> size;
            if(filename == "" || extension == "" || size == -1){
                Logger::logIncorrectFileName();
                continue;
            }
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
            string path;
            ss >> path;
            if (path == "/") {
                Logger::logIncorrectFileName();
            } else {
                userControlSystem->rm(path);
            }
        } else if (command == "ls") {
            userControlSystem->ls();
        } else if (command == "cd") {
            string path;
            ss >> path;
            if (path.empty()) {
                Logger::logIncorrectFileName();
                continue;
            }

            userControlSystem->cd(path);
        } else if (command == "mv") {
            string name, destination;
            ss >> name >> destination;
            if (name == "" || destination == "" || name == "root") {
                Logger::logIncorrectFileName();
                continue;
            } else {
                userControlSystem->move(name, destination);
            }
        } else if (command == "man") {
            cout << "User manual" << endl;
            cout << "1) mkdir directoryName (in current dir)" << endl;
            cout << "2) touch filename extension size (in current dir)" << endl;
            cout << "3) ln type(-s/-h) linkName targetPath extension size (in current dir)" << endl;
            cout << "4) ls" << endl;
            cout << "5) cd path" << endl;
            cout << "6) mv filename path" << endl;
            cout << "7) rm path" << endl;
        } else if (command == "exit") {
            break;
        } else {
            cout << "Unknown command" << endl;
        }
    }

    Directory *testingDirectory = new Directory("Directory", nullptr);
    DirectoryTest::runTests(testingDirectory);

    File *testingFile = new File("File", nullptr, "txt", 10);
    FileTest::runTests(testingFile);

    Link *testingLink = new Link("Link", nullptr, nullptr, "txt", 10);
    LinkTest::runTests(testingLink);

    return 0;
}

