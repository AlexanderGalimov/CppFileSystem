//#include <iostream>
//#include "string"
//#include "ctime"
//#include "vector"

//4.	Файловая система.
// Необходимо смоделировать файловую систему ОС Unix (без прав доступа).
// Файловая система состоит из папок, фалов и ссылок.
// Ссылки бывают 2-х видов жесткие и символьные
// (при удалении жесткой ссылки удаляется заодно и сам файл/папка, на который эта ссылка ссылается, точнее оба имени являются абсолютно равноправными).
// Файлы имеют размер, расширение, кроме того файлы и папки имеют атрибуты: время создания, время изменения и т.п.
// Файловая система имеет только один корень, представляющий собой папку, которую нельзя удалить.
// Для каждого элемента файловой системы предусмотреть операции создания, переименования, перемещения, изменения (меняется дата изменения) и удаления.

//using namespace std;
//
//class FileSystemObject {
//protected:
//    string name;
//    string dateOfCreation;
//    string modificationDate;
//    string destination;
//    FileSystemObject *parent;
//
//public:
//    FileSystemObject(const string &objectName, FileSystemObject *parentObject) {
//        this->name = objectName;
//        time_t currDate = time(0);
//        this->dateOfCreation = ctime(&currDate);
//        this->modificationDate = ctime(&currDate);
//        this->destination = objectName;
//        this->parent = parentObject;
//    }
//
//    virtual ~FileSystemObject() {
//    }
//
//    virtual void remove() {
//        setParent(nullptr);
//        delete this;
//    }
//
//    void modifyDate() {
//        time_t currDate = time(0);
//        this->modificationDate = ctime(&currDate);
//        cout << "Date modified" << endl;
//    }
//
//    const string &getName() const {
//        return name;
//    }
//
//    const string &getModificationDate() const {
//        return modificationDate;
//    }
//
//    const string &getDateOfCreation() const {
//        return dateOfCreation;
//    }
//
//    const string &getDestination() const {
//        return destination;
//    }
//
//    void setDestination(const string &newDestination) {
//        destination = newDestination;
//    }
//
//    void setParent(FileSystemObject *newParent) {
//        FileSystemObject::parent = newParent;
//    }
//
//    virtual void rename(const string &newName) {
//        name = newName;
//        size_t slashIndex = newName.find_last_of('/');
//        destination = newName.substr(0, slashIndex + 1);
//        modifyDate();
//        cout << "Name changed to: " << newName << endl;
//    }
//
//    virtual void toString() {
//        cout << "Name: " << name << endl;
//        cout << "Destination: " << destination << endl;
//        cout << "Date of creation: " << dateOfCreation;
//        cout << "Modification date: " << modificationDate;
//    }
//};
//
//class Directory : public FileSystemObject {
//private:
//    vector<FileSystemObject *> objects;
//public:
//    Directory(const string &objectName, FileSystemObject *parentObject) : FileSystemObject(objectName, parentObject) {}
//
//    ~Directory() {
//        objects.clear();
//        cout << "Directory " << name << " Deleted" << endl;
//    }
//
//    void remove() override {
//        if (name == "root") {
//            return;
//        } else {
//            objects.clear();
//            FileSystemObject::remove();
//        }
//    }
//
//    void rename(const string &newName) override {
//        if (name == "root") {
//            cout << "Can't rename root directory";
//        } else {
//            FileSystemObject::rename(newName);
//        }
//    }
//
//    void move(Directory *oldFolder, Directory *newFolder) {
//        if (name == "root") {
//            cout << "Can't move root directory" << endl;
//        } else {
//            destination = newFolder->getDestination() + "/" + name;
//            newFolder->addObject(this);
//            oldFolder->removeElement(name);
//            setParent(newFolder);
//            modifyDate();
//        }
//    }
//
//    void removeElement(string &elementName) {
//        for (int i = 0; i < objects.size(); ++i) {
//            if (objects[i]->getName() == elementName) {
//                objects[i]->setParent(nullptr);
//                delete objects[i];
//                objects.erase(objects.begin() + i);
//                break;
//            }
//        }
//        modifyDate();
//        cout << "Element successfully removed" << endl;
//    }
//
//    void addObject(FileSystemObject *object) {
//        objects.push_back(object);
//        object->setDestination(destination + "/" + object->getName());
//        object->setParent(this);
//        modifyDate();
//        cout << "Successfully added" << endl;
//    }
//
//    void toString() override {
//        cout << "Type: Directory" << endl;
//        FileSystemObject::toString();
//    }
//
//    void printInner() {
//        cout << "Objects in: " << endl;
//        toString();
//        for (int i = 0; i < objects.size(); i++) {
//            objects[i]->toString();
//        }
//    }
//};
//
//class File : public FileSystemObject {
//private:
//    string extension;
//    size_t size;
//
//public:
//    File(const string &objectName, FileSystemObject *parentObject, const string &extension, size_t size)
//            : FileSystemObject(objectName, parentObject), extension(extension), size(size) {}
//
//    ~File() {
//        cout << "File " << name << " Deleted" << endl;
//    }
//
//    void setExtension(const string &newExtension) {
//        extension = newExtension;
//        modifyDate();
//        cout << "Extension changed to" << extension << endl;
//    }
//
//    void move(Directory *oldFolder, Directory *newFolder) {
//        destination = newFolder->getDestination() + "/" + name;
//        newFolder->addObject(this);
//        oldFolder->removeElement(name);
//        setParent(newFolder);
//        modifyDate();
//    }
//
//    void toString() override {
//        cout << "Type: File" << endl;
//        FileSystemObject::toString();
//        cout << "extension: " << extension << endl;
//        cout << "size: " << size << endl;
//    }
//
//    const string &getExtension() const {
//        return extension;
//    }
//
//    size_t getSize() const {
//        return size;
//    }
//};
//
//class Link : public FileSystemObject {
//protected:
//    FileSystemObject *target;
//
//public:
//    Link(const string &objectName, FileSystemObject *parentObject, FileSystemObject *target) : FileSystemObject(
//            objectName, parentObject), target(target) {}
//
//    ~Link() {
//        cout << "Link " << name << " Deleted" << endl;
//    }
//
//    void move(Directory *oldFolder, Directory *newFolder) {
//        destination = newFolder->getDestination() + "/" + name;
//        newFolder->addObject(this);
//        oldFolder->removeElement(name);
//        setParent(newFolder);
//        modifyDate();
//    }
//
//    virtual void toString() override {
//        FileSystemObject::toString();
//        cout << "Points to: " << endl;
//        target->toString();
//    }
//
//    void setTarget(FileSystemObject *newTarget) {
//        Link::target = newTarget;
//        modifyDate();
//    }
//
//    FileSystemObject *getTarget() const {
//        return target;
//    }
//};
//
//class HardLink : public Link {
//public:
//    HardLink(const string &objectName, FileSystemObject *parentObject, FileSystemObject *target) : Link(objectName,
//                                                                                                        parentObject,
//                                                                                                        target) {}
//
//    void remove() {
//        delete target;
//        FileSystemObject::remove();
//    }
//
//    void toString() {
//        cout << "Type: " << "Hard " << "Link" << endl;
//        Link::toString();
//    }
//};
//
//class SymbolicLink : public Link {
//public:
//    SymbolicLink(const string &objectName, FileSystemObject *parentObject, FileSystemObject *target) : Link(objectName,
//                                                                                                            parentObject,
//                                                                                                            target) {}
//
//    void toString() {
//        cout << "Type: " << "Symbolic " << "Link" << endl;
//        Link::toString();
//    }
//};
//
//class FileSystem {
//private:
//    Directory root;
//
//public:
//    FileSystem() : root("root", &root) {
//    }
//
//    Directory *getRootDirectory() {
//        return &root;
//    }
//};
//
//
//int main() {
//    FileSystem home;
//
//    cout << "--------------------------------------" << endl;
//    Directory *root = home.getRootDirectory();
//
//    string dirName = "dirName";
//    Directory inner_directory(dirName, root);
//    root->toString();
//    cout << "--------------------------------------" << endl;
//    root->addObject(&inner_directory);
//    cout << "--------------------------------------" << endl;
//    root->printInner();
//    cout << "--------------------------------------" << endl;
//    string newName = "new Name dir";
//    inner_directory.rename(newName);
//
//    string fName = "fName";
//    string ext = "png";
//    size_t size = 10;
//    File file(fName, root, ext, size);
//    cout << "--------------------------------------" << endl;
//    root->addObject(&file);
//    cout << "--------------------------------------" << endl;
//    file.move(root, &inner_directory);
//
//    inner_directory.printInner();
//
//
//    return 0;
//}
