//
// Created by Александр on 27.03.2024.
//

#ifndef TASK2_LOGGER_H
#define TASK2_LOGGER_H

#include "iostream"
using namespace std;

class Logger {
public:
    static void logAddObjectToDirectory();

    static void logIncorrectFileName();

    static void logAlreadyExist(const string& name);

    static void logObjectNotFound(const string& name);

    static void logUnknownCommand();

    static void logIncorrectLinkType(const string& type);

    static void logUnsuccessfullyRename(const string& name);

    static void logSuccessfullyRename(const string& name);

    static void logUnsuccessfullyMove(const string& name);

    static void logSuccessfullyMove(const string& name);

    static void logDelete(const string& name);

    static void logExtensionChange(const string& extension);

    static void logDest();

    static void logRoot();
};


#endif //TASK2_LOGGER_H
