//
// Created by ayesdie on 01/05/20.
//

#include "disk.hpp"

namespace fs
{
    // constructor of disk, allocate root directory
    disk::disk()
    {
        freeSpaceList[0] = false;
        sector[0] = new directory(0, "root");
        for (int i = 1; i < DISK_SIZE; i++) {
            freeSpaceList[i] = true;
            sector[i] = nullptr;
        }
        close();
    }

// destructor of disk
    disk::~disk()
    {std::cout << "disk is now deleted." << std::endl; }

// return the index of first available sector in the disk
    int disk::index()
    {
        int index;
        index = -1;

        for (int i = 0; i < DISK_SIZE; i++) {
            if (freeSpaceList[i] == true) {
                index = i;
                break;
            }
        }
        return index;
    }

// check the open status;
    bool disk::isOpen()
    {
        bool flag;
        flag = true;
        if (openBlock == -1 && openMode == -1 && cursor == -1) {
            flag = false;
        }
        return flag;
    }

// display the hierarchy structure of the disk
    void disk::display()
    {
        std::cout << "*********** File System Display ************" << std::endl;
        ((directory*)sector[0])->setFree(index());
        ((directory*)sector[0])->display("");
        count();

        std::cout << "Mode: ";
        if (openMode == 0) {
            std::cout << "Input\t";
        }
        else if (openMode==1) {
            std::cout << "Output\t";
        }
        else if (openMode==2) {
            std::cout << "Update\t";
        }
        else {
            std::cout << "NA\t";
        }

        std::cout << "block: ";
        if (openBlock == -1) {
            std::cout << "NA\t";
        }
        else {
            std::cout << sector[openBlock]->getName() << "\t";
        }

        std::cout << "Cursor: ";
        if (cursor == -1) {
            std::cout << "NA\t";
        }
        else {
            std::cout << cursor << "\t";
        }

        std::cout << "\n********************************************\n" ;
    }

// count the type of file in the disk
    void disk::count()
    {
        int free, dir, file;
        free = 0;
        dir = 0;
        file = 0;
        for (int i = 0; i < DISK_SIZE; i++) {
            if (freeSpaceList[i] == 1) {
                free++;
            }
            else {
                if (sector[i]->isDir() == true)
                    dir++;
                else
                    file++;
            }
        }
        std::cout << "# of free blocks: " << free << std::endl;
        std::cout << "# of directory blocks: " << dir << std::endl;
        std::cout << "# of data file blocks: " << file << std::endl;
    }

// create a new block
    void disk::create(char type, std::string name)
    {
        std::string original;
        original = name;

        if (type != 'U' && type != 'D') {
            std::cout << "Error: Create " << name << " failed. Please enter a vaild file type such as U or D" << std::endl;
        }
        else if (isOpen() == true && type == 'U') {
            std::cout << "Error: Create " << name << " failed because " << sector[openBlock]->getName() << " is opened. Please close it first before creating another file" << std::endl;
        }
        else {
            directory* parent;
            // get the parent directory for the coming block
            parent = helpFind((directory*)sector[0], name);

            if (parent == nullptr && index() != -1) {
                std::cout << "Error: Create " << name << " failed. File name " << name << " is not valid." << std::endl;
            }
            else if (parent == nullptr && index() == -1) {
                std::cout << "Error: Create " << name << " failed. ALL the sectors are used." << std::endl;
            }
            else {
                while (name.find('/') != name.npos) {
                    name = name.substr(name.find('/')+1);
                }

                block* newblock;
                newblock = helpCreate(type, name);
                if (newblock != nullptr) {
                    parent->addEntry(newblock);
                    std::cout << "Finished create " << name << std::endl;

                    if (type == 'U') {
                        open('O', original);
                    }
                }
                else {
                    std::cout << "Error: Create " << name << " failed. ALL the sectors are used." << std::endl;
                }
            }
        }
    }

// open a block
    void disk::open(char mode, std::string name)
    {
        if (isOpen() == true) {
            std::cout << "Error: Open " << name << " failed because " << sector[openBlock]->getName() << " is opened. Please close it first before opening another file" << std::endl;
        }
        else if (mode != 'I' && mode != 'U' && mode != 'O')
        {
            std::cout << "Error: Open " << name << " failed. Please enter the correct open mode. (eg: I or U or O)." << std::endl;
        }
        else {
            block* b1;
            b1 = findBlock(name);

            if (b1 == nullptr) {
                std::cout << "Error: Open " << name << " failed because file name is not valid. Please try again." << std::endl;
            }
            else {
                openBlock = b1->getNumber();
                cursor = 0;
                if (mode == 'I') {
                    openMode = 0;
                    seek(-1, 0);
                }
                else if (mode == 'O') {
                    openMode = 1;
                    cursor = ((file*)sector[openBlock])->getEnd();
                }
                else {
                    openMode = 2;
                    seek(-1, 0);
                }
            }
        }

    }

// closed the last open block (reset)
    void disk::close()
    {
        openBlock = -1;
        openMode = -1;
        cursor = -1;
    }

// delete the name block
    void disk::deleteNew(std::string name)
    {
        block* toBeDelete;
        directory* parent;
        int blockNum;

        blockNum = -1;
        toBeDelete = findBlock(name);
        parent = findParent((directory*)sector[0],name);

        // delete a file block
        if (toBeDelete != nullptr && parent != nullptr && toBeDelete->isDir() == false) {
            blockNum = toBeDelete->getNumber();
            deleteBlock(parent, toBeDelete);
        }
            // delete a directory block
        else if (toBeDelete!= nullptr && parent != nullptr && toBeDelete->isDir() == true) {
            blockNum = toBeDelete->getNumber();
            deleteBlock(parent, (directory*)toBeDelete);
        }
        else {
            std::cout << "Error: Delete " << name << " failed. Please enter a valid file name." << std::endl;
        }

        if (blockNum == openBlock) {
            close();
        }
    }

// write into a file    **********
    void disk::write(int count, std::string input)
    {
        if (isOpen() == true && openMode == 0) {
            std::cout << "Error: Write failed because " << sector[openBlock]->getName() << " is in Input mode." << std::endl;
        }
        else if (isOpen() == false) {
            std::cout << "Error: Write failed because no file is opened." << std::endl;
        }
        else {
            int current, blockNum;
            file* next;

            current = cursor;
            blockNum = openBlock;
            next = (file*)(sector[openBlock]->getFrwd());

            // get to the end of the link list and reach the last file block
            while (current >= FILE_SIZE && next != nullptr) {
                openBlock = next->getNumber();
                current -= FILE_SIZE;
                next = (file*)(sector[openBlock]->getFrwd());
            }

            if (current >= FILE_SIZE) {
                std::cout << "Error: Write failed because the cursor is getting beyond the size of " << sector[openBlock]->getName() << std::endl;
            }
            else {
                // start writing in the last file
                helpWrite(count, input, current);
            }
            openBlock = blockNum;   // get back from the linked list
        }
    }

// help write into file
    void disk::helpWrite(int& count, std::string& input, int& current)
    {
        block* newFile;
        int totalToWrite, wrote;

        newFile = sector[openBlock];
        totalToWrite = current + count;
        wrote = 0;

        while (totalToWrite >= FILE_SIZE) {
            // count the total # of wrote
            current = current % FILE_SIZE;
            if (FILE_SIZE > count) {
                wrote = count - current;
            }
            else {
                wrote = FILE_SIZE - current;
            }

            ((file*)sector[openBlock])->writeFile(count, input, current);
            totalToWrite -= wrote;

            // allocate new block
            newFile = helpCreate('U', sector[openBlock]->getName());

            if (newFile != nullptr) {
                sector[openBlock]->setFrwd(newFile);
                newFile->setBack(sector[openBlock]);
                openBlock = newFile->getNumber();
            }
            else {
                break;
            }
        }

        if (totalToWrite < FILE_SIZE && newFile != nullptr) {
            current = current % FILE_SIZE;
            ((file*)sector[openBlock])->writeFile(count, input, current);
            if (count > 0) {
                std::cout << "Error: Write is unfinished because ALL the sectors are used and the disk can't allocate more." << std::endl;
            }
        }
        else {
            std::cout << "Error: Write is unfinished because ALL the sectors are used and the disk can't allocate more." << std::endl;
        }

    }


// read out the file
    void disk::read(int count)
    {
        if (isOpen() == true && openMode == 1) {
            std::cout << "Error: Read failed because " << sector[openBlock]->getName() << " is in Output mode." << std::endl;
        }
        else if (isOpen() == false) {
            std::cout << "Error: Read failed because no file is opened." << std::endl;
        }
        else {
            int current, blockNum;
            block* next;

            current = cursor;
            blockNum = openBlock;
            next = sector[openBlock];

            // get to the desire block
            while (current >= FILE_SIZE && next->getFrwd() != nullptr) {
                next = next->getFrwd();
                openBlock = next->getNumber();
                current -= FILE_SIZE;
            }

            if (current >= FILE_SIZE) {
                std::cout << "Error: Read failed because the cursor is getting beyond the size of " << sector[openBlock]->getName() << std::endl;
            }
            else {
                int totalRead, readed;
                totalRead = current + count;
                next = sector[openBlock];
                readed = 0;

                while (totalRead >= FILE_SIZE) {
                    current = current % FILE_SIZE;
                    if (FILE_SIZE > count) {
                        readed = count - current;
                    }
                    else {
                        readed = FILE_SIZE - current;
                    }

                    ((file*)sector[openBlock])->readFile(count, current);
                    totalRead -= readed;

                    next = sector[openBlock]->getFrwd();
                    if (next != nullptr) {
                        openBlock = next->getNumber();
                    }
                    else {
                        break;
                    }
                }

                if (totalRead < FILE_SIZE && next != nullptr) {
                    current = current % FILE_SIZE;
                    ((file*)sector[openBlock])->readFile(count, current);
                    std::cout << "(EOF)" << std::endl;
                    if (count > 0) {
                        std::cout << "\nEnd of file is reached." << std::endl;
                    }
                }
                else {
                    std::cout << "(EOF)" << std::endl;
                    std::cout << "\nEnd of file is reached." << std::endl;
                }
            }
            openBlock = blockNum;
        }
    }

// seek for cursor
    void disk::seek(int base, int offset)
    {
        if (isOpen() == true && openMode == 1) {
            std::cout << "Error: Seek failed because " << sector[openBlock]->getName() << " is in Output mode." << std::endl;
        }
        else if (isOpen() == false) {
            std::cout << "Error: Seek failed because no file is opened." << std::endl;
        }
        else {
            // the begining of file
            if (base == -1 && offset >= 0) {
                cursor = 0;
                cursor += offset;
            }
            else if (base == -1 && offset < 0) {
                std::cout << "Error: Seek failed. Can't go backward when reach the beginning of the file." << std::endl;
            }
                // the current position in the file
            else if (base == 0) {
                if (cursor + offset < 0) {
                    std::cout << "Error: Seek failed. Can't go backward when reach the beginning of the file." << std::endl;
                }
                else {
                    cursor += offset;
                }
            }
                // the end of file
            else if (base == 1) {
                if (((file*)sector[openBlock])->getEnd() + offset < 0) {
                    std::cout << "Error: Seek failed. Can't go backward when reach the beginning of the file." << std::endl;
                }
                else {
                    cursor = ((file*)sector[openBlock])->getEnd() + offset;
                }
            }
        }
    }

// return the block* of name block
    block* disk::findBlock(std::string name)
    {
        std::string original, name1;
        original = name;
        name1 = name.substr(name.find('/')+1);

        while (name1.find('/') != name1.npos) {
            name1 = name1.substr(name1.find('/')+1);
        }

        if (name1.find('/') && name1.length() <= 9) {
            block* temp;
            temp = nullptr;

            for (int i = 0; i < DISK_SIZE; i++) {
                if (sector[i]!= nullptr && sector[i]->getName() == name1) {
                    temp = sector[i];
                    break;
                }
            }
            return temp;
        }
        else {
            return nullptr;
        }
    }

// return the block* of the parent directory
    directory* disk::findParent(directory* super, std::string name)
    {
        if (name.find('/') != name.npos) {
            std::string name1, name2;
            name1 = name.substr(0, name.find('/'));
            name2 = name.substr(name.find('/')+1);

            directory* sub;
            sub = super->getDirEntry(name1);

            // if directory name exist in parent directory super
            if(sub != super){
                return findParent(sub, name2);
            }
                // if directory name NOT in parent directory super
            else {
                return nullptr;
            }
        }
        else if (name.find('/') && name.length() <= 9) {
            block* file;
            directory* sub;
            sub = super->getDirEntry(name);
            file = super->getFileEntry(name);



            // sub exist as a directory in parent directory super
            if (sub != super && file == nullptr) {
                return super;
            }
                // file exist as a file in parent directory super
            else if (sub == super && file != nullptr) {
                return super;
            }
                // NEITHER sub or file exist in parent directory super
            else {
                return nullptr;
            }
        }
        else
            return nullptr;
    }

// (for create) return the block* of newly allocated block
    block* disk::helpCreate(char type, std::string name)
    {
        block* newblock;
        int sectorNum;

        // initial
        sectorNum = index();
        newblock = nullptr;

        if (index() != -1) {
            if (type == 'U') {
                sector[sectorNum] =  new file (sectorNum, name);
            }
            else {
                sector[sectorNum] = new directory (sectorNum, name);
            }
            freeSpaceList[sectorNum] = false;
            newblock = sector[sectorNum];
            std::cout << "Allocate a new block " << sectorNum << std::endl;
        }

        return newblock;
    }

// (for create) return the block* of the parent directory (if exist, delete and recreate)
    directory* disk::helpFind(directory* super, std::string name)
    {
        if (name.find('/') != name.npos) {
            std::string name1, name2;
            name1 = name.substr(0, name.find('/'));
            name2 = name.substr(name.find('/')+1);

            directory* sub;
            sub = super->getDirEntry(name1);

            // if directory name exist in parent directory super
            if(sub != super){
                return helpFind(sub, name2);
            }

            else {
                block* newEntry;
                newEntry = helpCreate('D', name1);
                if (newEntry != nullptr) {
                    super->addEntry(newEntry);
                    return helpFind((directory*)newEntry, name2);
                }
                else {
                    return nullptr;
                }
            }
        }
        else if (name.find('/') && name.length() <= 9) {
            block* file;
            directory* sub;
            sub = super->getDirEntry(name);
            file = super->getFileEntry(name);

            // sub doesn't exist as a directory in parent directory super
            if (sub == super && file == nullptr) {
                return super;
            }
                // sub exist as a directory in parent directory super
            else if (sub != super) {
                deleteBlock(super, sub);
                return super;
            }
                // file exist as a file in parent directory super
            else {
                deleteBlock(super, file);
                return super;
            }
        }
        else
            return nullptr;
    }

// delete a allocated dir block dir from directory super
    void disk::deleteBlock(directory* super, directory* dir)
    {
        int deleteNum;

        // empty directory
        if (dir->isEmpty() == true) {
            deleteNum = super->deleteNumber(dir);

            if (deleteNum == -1) {
                std::cout << "Error: " << dir->getName() << " delete failed because it is not located in directory " << super->getName() << std::endl;
            }
            else {
                delete sector[deleteNum];
                sector[deleteNum]=nullptr;
                freeSpaceList[deleteNum] = true;
            }
        }
            // directory not empty
        else {
            // empty dir
            block** entry;
            entry = dir->getEntryHead();

            for (int i = 0; i < DIR_SIZE; i++) {
                if (entry[i] != nullptr) {
                    if (entry[i]->isDir() == true) {
                        deleteBlock(dir, (directory*)entry[i]);
                    }
                    else {
                        deleteBlock(dir, entry[i]);
                    }
                }
            }

            // delete the empty dir from super
            deleteNum = super->deleteNumber(dir);

            if (deleteNum == -1) {
                std::cout << "Error: " << dir->getName() << " delete failed because it is not located in directory " << super->getName() << std::endl;
            }
            else {
                delete sector[deleteNum];
                sector[deleteNum]=nullptr;
                freeSpaceList[deleteNum] = true;
            }
        }
    }

// delete a allocated block file from directory super
    void disk::deleteBlock(directory* super, block* file)
    {
        int deleteNum;

        // no linker
        if (file->getBack() == nullptr && file->getFrwd() == nullptr) {
            deleteNum = super->deleteNumber(file);

            if (deleteNum == -1) {
                std::cout << "Error: " << file->getName() << " delete failed because it is not located in directory " << super->getName() << std::endl;
            }
            else {
                delete sector[deleteNum];
                sector[deleteNum]=nullptr;
                freeSpaceList[deleteNum] = true;
            }
        }
            // first/middle/last node in the link list
        else
        {
            block* front;
            block* back;
            front = file;
            back = nullptr;

            // get to the last node
            while (front->getFrwd() != nullptr) {
                front = front->getFrwd();
                back = front->getBack();
            }

            // delete the last node and traverse back
            while (back != nullptr) {
                deleteNum = front->getNumber();
                front->setBack((block*)nullptr);
                back->setFrwd((block*)nullptr);

                delete sector[deleteNum];
                sector[deleteNum]=nullptr;
                freeSpaceList[deleteNum] = true;

                front = back;
                back = front->getBack();
            }

            // delete the first node
            deleteNum = super->deleteNumber(file);
            delete sector[deleteNum];
            sector[deleteNum]=nullptr;
            freeSpaceList[deleteNum] = true;
        }

    }
}
