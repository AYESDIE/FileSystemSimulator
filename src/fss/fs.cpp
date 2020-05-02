////
//// Created by ayesdie on 01/05/20.
////
//
//#include "fs.hpp"
//
////
////  OSFS.cpp
////  OSFS
////
////  Created by Sunny Lin on 10/23/17.
////  Copyright © 2017 Sunny Lin. All rights reserved.
////
//
//#include "fs.hpp"
//
///************** class Block  **************/
//// default constructor for block
//Block::Block()
//{
//    number = -1;
//    dir = false;
//    frwd = nullptr;
//    back = nullptr;
//    name = "";
//}
//
//// constructor for directory or file block
//Block::Block(int number, bool isDir, string name)
//{
//    this->dir = isDir;
//    this->name = name;
//    this->number = number;
//
//    if (number == 0) {
//        frwd = this;
//        back = this;
//    }
//    else    {
//        frwd = nullptr;
//        back = nullptr;
//    }
//}
//
//// destructor of block
//Block::~Block()
//{
//    cout << "block " << this->getNumber() << " is now empty."<< endl;
//    reset();
//}
//
//// return block number
//int Block::getNumber()
//{   return number;  }
//
//// return the type of block
//bool Block::isDir()
//{   return dir;     }
//
//// set frwd block pointer
//void Block::setFrwd(Block* frwd)
//{   this->frwd = frwd;  }
//
//// set back block pointer
//void Block::setBack(Block* back)
//{   this->back = back;  }
//
//// reset a Block* to nullptr
//void Block::reset()
//{
//    number = -1;
//    dir = false;
//    frwd = nullptr;
//    back = nullptr;
//    name = "";
//}
//
//// return frwd block pointer
//Block* Block::getFrwd()
//{   return frwd;    }
//
//// return back block pointer
//Block* Block::getBack()
//{   return back;    }
//
//// return block name
//string Block::getName()
//{   return name;    }
//
//
//
///************** class Directory  **************/
//// constructor for directory block
//Directory::Directory(int number, string name): Block(number, true, name)
//{
//    free = -1;
//    for (int i = 0; i < DIR_SIZE; i++) {
//        entry[i] = nullptr;
//    }
//}
//
//// destructor of directory
//Directory::~Directory()
//{   cout << "directory " << this->getName() << " is deleted."<< endl;   }
//
//// get the entry block* of name
//Directory* Directory::getDirEntry(string name)
//{
//    Directory* temp;
//    temp = this;
//
//    for (int i = 0 ; i < DIR_SIZE; i++) {
//        if (entry[i] != nullptr && entry[i]->getName() == name && entry[i]->isDir() == true) {
//            temp = (Directory*)entry[i];
//            break;
//        }
//    }
//    return temp;
//}
//
//// get the file block* of name
//Block* Directory::getFileEntry(string name)
//{
//    Block* temp;
//    temp = nullptr;
//
//    for (int i = 0 ; i < DIR_SIZE; i++) {
//        if (entry[i] != nullptr && entry[i]->getName() == name && entry[i]->isDir() == false) {
//            temp = entry[i];
//            break;
//        }
//    }
//    return temp;
//}
//
//// return the Block* of entry;
//Block** Directory::getEntryHead()
//{   return entry;   }
//
//// return the block number of the to be deleted Block*
//int Directory::deleteNumber(Block* toDelete)
//{
//    int temp;
//    temp = -1;
//
//    // set entry[i] == file to nullptr
//    for (int i = 0; i < DIR_SIZE; i++) {
//        if (entry[i]->getNumber() == toDelete->getNumber()) {
//            temp = entry[i]->getNumber();
//            entry[i] = nullptr;
//            break;
//        }
//    }
//    return temp;
//}
//
//// return the size of the directory block
//int Directory::getSize()
//{
//    int size;
//    size = 0;
//
//    for (int i = 0; i < DIR_SIZE; i++) {
//        if (entry[i] != nullptr) {
//            size++;
//        }
//    }
//    return size;
//}
//
//// add an newly allocated entry
//void Directory::addEntry(Block* newEntry)
//{
//    for (int i = 0; i < DIR_SIZE; i++) {
//        if (entry[i] == nullptr) {
//            entry[i] = newEntry;
//            break;
//        }
//    }
//}
//
//// set free for root block
//void Directory::setFree(int index)
//{
//    if (this->getNumber() == 0) {
//        free = index;
//    }
//    else
//        free = -1;
//}
//
//// display directory content
//void Directory::display(string indent)
//{
//    // display name, type, block number, and size
//    cout << indent << this->getName() << "\tD\t";
//    cout << "#: " << this->getNumber() << "\tSIZE: " << this->getSize() << endl;
//
//    // display back pointer block #
//    if (this->getBack() == nullptr)
//    {   cout << indent << "-BACK: nullptr" << endl;    }
//    else
//    {   cout << indent << "-BACK: " << this->getBack()->getNumber() << endl;   }
//
//    // display forward pointer block #
//    if (this->getFrwd() == nullptr)
//    {   cout << indent << "-FRWD: nullptr" << endl;    }
//    else
//    {   cout << indent << "-FRWD: " << this->getFrwd()->getNumber() << endl;   }
//
//    if (this->getNumber() == 0)
//    {   cout << indent << "-FREE: " << free << endl; }
//
//    // display unused filler
//    cout << indent << "-FILLER: UNUSED" << endl;
//
//    if (isEmpty() == false) {
//        indent += "\t";
//        for (int i = 0; i < DIR_SIZE; i++) {
//            if (entry[i] != nullptr) {
//                if (entry[i]->isDir() == true) {
//                    ((Directory*)entry[i])->display(indent);
//                }
//                else {
//                    ((File*)entry[i])->display(indent);
//                }
//            }
//        }
//    }
//}
//
//// check whether the directory is empty
//bool Directory::isEmpty()
//{
//    bool flag;
//    flag = true;
//
//    for (int i = 0; i < DIR_SIZE; i++) {
//        if (entry[i] != nullptr) {
//            flag = false;
//            break;
//        }
//    }
//    return flag;
//}
//
///************** class File  **************/
//// constructor for file block
//File::File(int number, string name): Block(number, false, name)
//{
//    for (int i = 0; i < FILE_SIZE; i++) {
//        data[i] = '\0';
//    }
//}
//
//// destructor of file
//File::~File()
//{   cout << "data file " << this->getName() << " is deleted."<< endl;   }
//
//// write input into file
//void File::writeFile(int& count, string& input, int& current)
//{
//    for (; current < FILE_SIZE && 0 < count; count--) {
//        if (input != "") {
//            data[current] = input[0];
//            input = input.substr(input.find(input[0])+1);
//            current++;
//            cursor++;
//        }
//        else {
//            data[current] = ' ';
//            cursor++;
//            current++;
//        }
//    }
//}
//
//// read and display file data
//void File::readFile(int& count, int& current)
//{
//    for (; current < FILE_SIZE && 0 < count; count--) {
//        if (data[current] != '\0') {
//            cout << data[current];
//            cursor++;
//            current++;
//        }
//        else {
//            break;
//        }
//    }
//}
//
//// display file content
//void File::display(string indent)
//{
//    // display file name
//    cout << indent << this->getName() << "\tU\t";
//    cout << "#: " << this->getNumber();
//
//    // display file linkers
//    Block* temp;
//    Block* size;
//    temp = this->getFrwd();
//    size = this;
//
//    while (temp != nullptr) {
//        cout << "<=>" << temp->getNumber();
//        size = temp;
//        temp = temp->getFrwd();
//    }
//
//    // display file size
//    cout << "\tSIZE: " << ((File*)size)->getSize() << endl;
//}
//
//// return end of file index of data[]
//int File::getEnd()
//{
//    int current;
//    bool flag;
//    current = 0;
//    flag = false;
//
//    for (int i = 0; i < FILE_SIZE; i++) {
//        if (data[i] == '\0') {
//            current = i;
//            flag = true;
//            break;
//        }
//    }
//
//    File* next;
//    next = (File*)this->getFrwd();
//
//    if (flag == false && next != nullptr) {
//        return next->getEnd()+504;
//    }
//    else {
//        return current;
//    }
//}
//
//// return the size of the directory block
//int File::getSize()
//{
//    int size;
//    size = 0;
//
//    for (int i = 0; i < FILE_SIZE; i++) {
//        if (data[i] != '\0') {
//            size++;
//        }
//    }
//    return size;
//}
//
///************** class Disk **************/
//// constructor of disk, allocate root directory
//Disk::Disk()
//{
//    freeSpaceList[0] = false;
//    sector[0] = new Directory(0, "root");
//    for (int i = 1; i < DISK_SIZE; i++) {
//        freeSpaceList[i] = true;
//        sector[i] = nullptr;
//    }
//    close();
//}
//
//// destructor of disk
//Disk::~Disk()
//{cout << "Disk is now deleted." << endl; }
//
//// return the index of first available sector in the disk
//int Disk::index()
//{
//    int index;
//    index = -1;
//
//    for (int i = 0; i < DISK_SIZE; i++) {
//        if (freeSpaceList[i] == true) {
//            index = i;
//            break;
//        }
//    }
//    return index;
//}
//
//// check the open status;
//bool Disk::isOpen()
//{
//    bool flag;
//    flag = true;
//    if (openBlock == -1 && openMode == -1 && cursor == -1) {
//        flag = false;
//    }
//    return flag;
//}
//
//// display the hierarchy structure of the disk
//void Disk::display()
//{
//    cout << "*********** File System Display ************" << endl;
//    ((Directory*)sector[0])->setFree(index());
//    ((Directory*)sector[0])->display("");
//    count();
//
//    cout << "Mode: ";
//    if (openMode == 0) {
//        cout << "Input\t";
//    }
//    else if (openMode==1) {
//        cout << "Output\t";
//    }
//    else if (openMode==2) {
//        cout << "Update\t";
//    }
//    else {
//        cout << "NA\t";
//    }
//
//    cout << "Block: ";
//    if (openBlock == -1) {
//        cout << "NA\t";
//    }
//    else {
//        cout << sector[openBlock]->getName() << "\t";
//    }
//
//    cout << "Cursor: ";
//    if (cursor == -1) {
//        cout << "NA\t";
//    }
//    else {
//        cout << cursor << "\t";
//    }
//
//    cout << "\n********************************************\n" ;
//}
//
//// count the type of file in the disk
//void Disk::count()
//{
//    int free, dir, file;
//    free = 0;
//    dir = 0;
//    file = 0;
//    for (int i = 0; i < DISK_SIZE; i++) {
//        if (freeSpaceList[i] == 1) {
//            free++;
//        }
//        else {
//            if (sector[i]->isDir() == true)
//                dir++;
//            else
//                file++;
//        }
//    }
//    cout << "# of free blocks: " << free << endl;
//    cout << "# of directory blocks: " << dir << endl;
//    cout << "# of data file blocks: " << file << endl;
//}
//
//// create a new block
//void Disk::create(char type, string name)
//{
//    string original;
//    original = name;
//
//    if (type != 'U' && type != 'D') {
//        cout << "Error: Create " << name << " failed. Please enter a vaild file type such as U or D" << endl;
//    }
//    else if (isOpen() == true && type == 'U') {
//        cout << "Error: Create " << name << " failed because " << sector[openBlock]->getName() << " is opened. Please close it first before creating another file" << endl;
//    }
//    else {
//        Directory* parent;
//        // get the parent directory for the coming block
//        parent = helpFind((Directory*)sector[0], name);
//
//        if (parent == nullptr && index() != -1) {
//            cout << "Error: Create " << name << " failed. File name " << name << " is not valid." << endl;
//        }
//        else if (parent == nullptr && index() == -1) {
//            cout << "Error: Create " << name << " failed. ALL the sectors are used." << endl;
//        }
//        else {
//            while (name.find('/') != name.npos) {
//                name = name.substr(name.find('/')+1);
//            }
//
//            Block* newBlock;
//            newBlock = helpCreate(type, name);
//            if (newBlock != nullptr) {
//                parent->addEntry(newBlock);
//                cout << "Finished create " << name << endl;
//
//                if (type == 'U') {
//                    open('O', original);
//                }
//            }
//            else {
//                cout << "Error: Create " << name << " failed. ALL the sectors are used." << endl;
//            }
//        }
//    }
//}
//
//// open a block
//void Disk::open(char mode, string name)
//{
//    if (isOpen() == true) {
//        cout << "Error: Open " << name << " failed because " << sector[openBlock]->getName() << " is opened. Please close it first before opening another file" << endl;
//    }
//    else if (mode != 'I' && mode != 'U' && mode != 'O')
//    {
//        cout << "Error: Open " << name << " failed. Please enter the correct open mode. (eg: I or U or O)." << endl;
//    }
//    else {
//        Block* file;
//        file = findBlock(name);
//
//        if (file == nullptr) {
//            cout << "Error: Open " << name << " failed because file name is not valid. Please try again." << endl;
//        }
//        else {
//            openBlock = file->getNumber();
//            cursor = 0;
//            if (mode == 'I') {
//                openMode = 0;
//                seek(-1, 0);
//            }
//            else if (mode == 'O') {
//                openMode = 1;
//                cursor = ((File*)sector[openBlock])->getEnd();
//            }
//            else {
//                openMode = 2;
//                seek(-1, 0);
//            }
//        }
//    }
//
//}
//
//// closed the last open block (reset)
//void Disk::close()
//{
//    openBlock = -1;
//    openMode = -1;
//    cursor = -1;
//}
//
//// delete the name block
//void Disk::deleteNew(string name)
//{
//    Block* toBeDelete;
//    Directory* parent;
//    int blockNum;
//
//    blockNum = -1;
//    toBeDelete = findBlock(name);
//    parent = findParent((Directory*)sector[0],name);
//
//    // delete a file block
//    if (toBeDelete != nullptr && parent != nullptr && toBeDelete->isDir() == false) {
//        blockNum = toBeDelete->getNumber();
//        deleteBlock(parent, toBeDelete);
//    }
//        // delete a directory block
//    else if (toBeDelete!= nullptr && parent != nullptr && toBeDelete->isDir() == true) {
//        blockNum = toBeDelete->getNumber();
//        deleteBlock(parent, (Directory*)toBeDelete);
//    }
//    else {
//        cout << "Error: Delete " << name << " failed. Please enter a valid file name." << endl;
//    }
//
//    if (blockNum == openBlock) {
//        close();
//    }
//}
//
//// write into a file    **********
//void Disk::write(int count, string input)
//{
//    if (isOpen() == true && openMode == 0) {
//        cout << "Error: Write failed because " << sector[openBlock]->getName() << " is in Input mode." << endl;
//    }
//    else if (isOpen() == false) {
//        cout << "Error: Write failed because no file is opened." << endl;
//    }
//    else {
//        int current, blockNum;
//        File* next;
//
//        current = cursor;
//        blockNum = openBlock;
//        next = (File*)(sector[openBlock]->getFrwd());
//
//        // get to the end of the link list and reach the last file block
//        while (current >= FILE_SIZE && next != nullptr) {
//            openBlock = next->getNumber();
//            current -= FILE_SIZE;
//            next = (File*)(sector[openBlock]->getFrwd());
//        }
//
//        if (current >= FILE_SIZE) {
//            cout << "Error: Write failed because the cursor is getting beyond the size of " << sector[openBlock]->getName() << endl;
//        }
//        else {
//            // start writing in the last file
//            helpWrite(count, input, current);
//        }
//        openBlock = blockNum;   // get back from the linked list
//    }
//}
//
//// help write into file
//void Disk::helpWrite(int& count, string& input, int& current)
//{
//    Block* newFile;
//    int totalToWrite, wrote;
//
//    newFile = sector[openBlock];
//    totalToWrite = current + count;
//    wrote = 0;
//
//    while (totalToWrite >= FILE_SIZE) {
//        // count the total # of wrote
//        current = current % FILE_SIZE;
//        if (FILE_SIZE > count) {
//            wrote = count - current;
//        }
//        else {
//            wrote = FILE_SIZE - current;
//        }
//
//        ((File*)sector[openBlock])->writeFile(count, input, current);
//        totalToWrite -= wrote;
//
//        // allocate new block
//        newFile = helpCreate('U', sector[openBlock]->getName());
//
//        if (newFile != nullptr) {
//            sector[openBlock]->setFrwd(newFile);
//            newFile->setBack(sector[openBlock]);
//            openBlock = newFile->getNumber();
//        }
//        else {
//            break;
//        }
//    }
//
//    if (totalToWrite < FILE_SIZE && newFile != nullptr) {
//        current = current % FILE_SIZE;
//        ((File*)sector[openBlock])->writeFile(count, input, current);
//        if (count > 0) {
//            cout << "Error: Write is unfinished because ALL the sectors are used and the disk can't allocate more." << endl;
//        }
//    }
//    else {
//        cout << "Error: Write is unfinished because ALL the sectors are used and the disk can't allocate more." << endl;
//    }
//
//}
//
//
//// read out the file
//void Disk::read(int count)
//{
//    if (isOpen() == true && openMode == 1) {
//        cout << "Error: Read failed because " << sector[openBlock]->getName() << " is in Output mode." << endl;
//    }
//    else if (isOpen() == false) {
//        cout << "Error: Read failed because no file is opened." << endl;
//    }
//    else {
//        int current, blockNum;
//        Block* next;
//
//        current = cursor;
//        blockNum = openBlock;
//        next = sector[openBlock];
//
//        // get to the desire block
//        while (current >= FILE_SIZE && next->getFrwd() != nullptr) {
//            next = next->getFrwd();
//            openBlock = next->getNumber();
//            current -= FILE_SIZE;
//        }
//
//        if (current >= FILE_SIZE) {
//            cout << "Error: Read failed because the cursor is getting beyond the size of " << sector[openBlock]->getName() << endl;
//        }
//        else {
//            int totalRead, readed;
//            totalRead = current + count;
//            next = sector[openBlock];
//            readed = 0;
//
//            while (totalRead >= FILE_SIZE) {
//                current = current % FILE_SIZE;
//                if (FILE_SIZE > count) {
//                    readed = count - current;
//                }
//                else {
//                    readed = FILE_SIZE - current;
//                }
//
//                ((File*)sector[openBlock])->readFile(count, current);
//                totalRead -= readed;
//
//                next = sector[openBlock]->getFrwd();
//                if (next != nullptr) {
//                    openBlock = next->getNumber();
//                }
//                else {
//                    break;
//                }
//            }
//
//            if (totalRead < FILE_SIZE && next != nullptr) {
//                current = current % FILE_SIZE;
//                ((File*)sector[openBlock])->readFile(count, current);
//                cout << "(EOF)" << endl;
//                if (count > 0) {
//                    cout << "\nEnd of file is reached." << endl;
//                }
//            }
//            else {
//                cout << "(EOF)" << endl;
//                cout << "\nEnd of file is reached." << endl;
//            }
//        }
//        openBlock = blockNum;
//    }
//}
//
//// seek for cursor
//void Disk::seek(int base, int offset)
//{
//    if (isOpen() == true && openMode == 1) {
//        cout << "Error: Seek failed because " << sector[openBlock]->getName() << " is in Output mode." << endl;
//    }
//    else if (isOpen() == false) {
//        cout << "Error: Seek failed because no file is opened." << endl;
//    }
//    else {
//        // the begining of file
//        if (base == -1 && offset >= 0) {
//            cursor = 0;
//            cursor += offset;
//        }
//        else if (base == -1 && offset < 0) {
//            cout << "Error: Seek failed. Can't go backward when reach the beginning of the file." << endl;
//        }
//            // the current position in the file
//        else if (base == 0) {
//            if (cursor + offset < 0) {
//                cout << "Error: Seek failed. Can't go backward when reach the beginning of the file." << endl;
//            }
//            else {
//                cursor += offset;
//            }
//        }
//            // the end of file
//        else if (base == 1) {
//            if (((File*)sector[openBlock])->getEnd() + offset < 0) {
//                cout << "Error: Seek failed. Can't go backward when reach the beginning of the file." << endl;
//            }
//            else {
//                cursor = ((File*)sector[openBlock])->getEnd() + offset;
//            }
//        }
//    }
//}
//
//// return the Block* of name block
//Block* Disk::findBlock(string name)
//{
//    string original, name1;
//    original = name;
//    name1 = name.substr(name.find('/')+1);
//
//    while (name1.find('/') != name1.npos) {
//        name1 = name1.substr(name1.find('/')+1);
//    }
//
//    if (name1.find('/') && name1.length() <= 9) {
//        Block* temp;
//        temp = nullptr;
//
//        for (int i = 0; i < DISK_SIZE; i++) {
//            if (sector[i]!= nullptr && sector[i]->getName() == name1) {
//                temp = sector[i];
//                break;
//            }
//        }
//        return temp;
//    }
//    else {
//        return nullptr;
//    }
//}
//
//// return the Block* of the parent directory
//Directory* Disk::findParent(Directory* super, string name)
//{
//    if (name.find('/') != name.npos) {
//        string name1, name2;
//        name1 = name.substr(0, name.find('/'));
//        name2 = name.substr(name.find('/')+1);
//
//        Directory* sub;
//        sub = super->getDirEntry(name1);
//
//        // if directory name exist in parent directory super
//        if(sub != super){
//            return findParent(sub, name2);
//        }
//            // if directory name NOT in parent directory super
//        else {
//            return nullptr;
//        }
//    }
//    else if (name.find('/') && name.length() <= 9) {
//        Block* file;
//        Directory* sub;
//        sub = super->getDirEntry(name);
//        file = super->getFileEntry(name);
//
//
//
//        // sub exist as a directory in parent directory super
//        if (sub != super && file == nullptr) {
//            return super;
//        }
//            // file exist as a file in parent directory super
//        else if (sub == super && file != nullptr) {
//            return super;
//        }
//            // NEITHER sub or file exist in parent directory super
//        else {
//            return nullptr;
//        }
//    }
//    else
//        return nullptr;
//}
//
//// (for create) return the Block* of newly allocated block
//Block* Disk::helpCreate(char type, string name)
//{
//    Block* newBlock;
//    int sectorNum;
//
//    // initial
//    sectorNum = index();
//    newBlock = nullptr;
//
//    if (index() != -1) {
//        if (type == 'U') {
//            sector[sectorNum] =  new File (sectorNum, name);
//        }
//        else {
//            sector[sectorNum] = new Directory (sectorNum, name);
//        }
//        freeSpaceList[sectorNum] = false;
//        newBlock = sector[sectorNum];
//        cout << "Allocate a new block " << sectorNum << endl;
//    }
//
//    return newBlock;
//}
//
//// (for create) return the Block* of the parent directory (if exist, delete and recreate)
//Directory* Disk::helpFind(Directory* super, string name)
//{
//    if (name.find('/') != name.npos) {
//        string name1, name2;
//        name1 = name.substr(0, name.find('/'));
//        name2 = name.substr(name.find('/')+1);
//
//        Directory* sub;
//        sub = super->getDirEntry(name1);
//
//        // if directory name exist in parent directory super
//        if(sub != super){
//            return helpFind(sub, name2);
//        }
//
//        else {
//            Block* newEntry;
//            newEntry = helpCreate('D', name1);
//            if (newEntry != nullptr) {
//                super->addEntry(newEntry);
//                return helpFind((Directory*)newEntry, name2);
//            }
//            else {
//                return nullptr;
//            }
//        }
//    }
//    else if (name.find('/') && name.length() <= 9) {
//        Block* file;
//        Directory* sub;
//        sub = super->getDirEntry(name);
//        file = super->getFileEntry(name);
//
//        // sub doesn't exist as a directory in parent directory super
//        if (sub == super && file == nullptr) {
//            return super;
//        }
//            // sub exist as a directory in parent directory super
//        else if (sub != super) {
//            deleteBlock(super, sub);
//            return super;
//        }
//            // file exist as a file in parent directory super
//        else {
//            deleteBlock(super, file);
//            return super;
//        }
//    }
//    else
//        return nullptr;
//}
//
//// delete a allocated dir block dir from directory super
//void Disk::deleteBlock(Directory* super, Directory* dir)
//{
//    int deleteNum;
//
//    // empty directory
//    if (dir->isEmpty() == true) {
//        deleteNum = super->deleteNumber(dir);
//
//        if (deleteNum == -1) {
//            cout << "Error: " << dir->getName() << " delete failed because it is not located in directory " << super->getName() << endl;
//        }
//        else {
//            delete sector[deleteNum];
//            sector[deleteNum]=nullptr;
//            freeSpaceList[deleteNum] = true;
//        }
//    }
//        // directory not empty
//    else {
//        // empty dir
//        Block** entry;
//        entry = dir->getEntryHead();
//
//        for (int i = 0; i < DIR_SIZE; i++) {
//            if (entry[i] != nullptr) {
//                if (entry[i]->isDir() == true) {
//                    deleteBlock(dir, (Directory*)entry[i]);
//                }
//                else {
//                    deleteBlock(dir, entry[i]);
//                }
//            }
//        }
//
//        // delete the empty dir from super
//        deleteNum = super->deleteNumber(dir);
//
//        if (deleteNum == -1) {
//            cout << "Error: " << dir->getName() << " delete failed because it is not located in directory " << super->getName() << endl;
//        }
//        else {
//            delete sector[deleteNum];
//            sector[deleteNum]=nullptr;
//            freeSpaceList[deleteNum] = true;
//        }
//    }
//}
//
//// delete a allocated block file from directory super
//void Disk::deleteBlock(Directory* super, Block* file)
//{
//    int deleteNum;
//
//    // no linker
//    if (file->getBack() == nullptr && file->getFrwd() == nullptr) {
//        deleteNum = super->deleteNumber(file);
//
//        if (deleteNum == -1) {
//            cout << "Error: " << file->getName() << " delete failed because it is not located in directory " << super->getName() << endl;
//        }
//        else {
//            delete sector[deleteNum];
//            sector[deleteNum]=nullptr;
//            freeSpaceList[deleteNum] = true;
//        }
//    }
//        // first/middle/last node in the link list
//    else
//    {
//        Block* front;
//        Block* back;
//        front = file;
//        back = nullptr;
//
//        // get to the last node
//        while (front->getFrwd() != nullptr) {
//            front = front->getFrwd();
//            back = front->getBack();
//        }
//
//        // delete the last node and traverse back
//        while (back != nullptr) {
//            deleteNum = front->getNumber();
//            front->setBack((Block*)nullptr);
//            back->setFrwd((Block*)nullptr);
//
//            delete sector[deleteNum];
//            sector[deleteNum]=nullptr;
//            freeSpaceList[deleteNum] = true;
//
//            front = back;
//            back = front->getBack();
//        }
//
//        // delete the first node
//        deleteNum = super->deleteNumber(file);
//        delete sector[deleteNum];
//        sector[deleteNum]=nullptr;
//        freeSpaceList[deleteNum] = true;
//    }
//
//}
