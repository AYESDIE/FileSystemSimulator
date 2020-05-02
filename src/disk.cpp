#include "disk.hpp"

namespace fsx
{

disk::disk()
{
    this->freeSpaceList[0] = false;
    this->sector[0] = new directory(0, "root");
    for (int i = 1; i < DISK_SIZE; i++)
    {
        this->freeSpaceList[i] = true;
        this->sector[i] = nullptr;
    }
    close();
}

disk::~disk()
{
    log(std::cout, "disk is now deleted.\n");
}

int disk::index()
{
    int index;
    index = -1;

    for (int i = 0; i < DISK_SIZE; i++)
    {
        if (this->freeSpaceList[i] == true)
        {
            index = i;
            break;
        }
    }
    return index;
}

bool disk::isOpen()
{
    bool flag;
    flag = true;
    if (openBlock == -1 && openMode == -1 && cursor == -1)
    {
        flag = false;
    }
    return flag;
}

void disk::display()
{
    log(std::cout, "----------- File System Display ------------\n");
    ((directory *)this->sector[0])->setFree(index());
    ((directory *)this->sector[0])->display("");
    count();

    log(std::cout, "Mode: ");
    if (openMode == 0)
    {
        log(std::cout, "Input\t");
    }
    else if (openMode == 1)
    {
        log(std::cout, "Output\t");
    }
    else if (openMode == 2)
    {
        log(std::cout, "Update\t");
    }
    else
    {
        log(std::cout, "NA\t");
    }

    log(std::cout, "block: ");
    if (openBlock == -1)
    {
        log(std::cout, "NA\t");
    }
    else
    {
        log(std::cout, this->sector[openBlock]->getName(), "\t");
    }

    log(std::cout, "Cursor: ");
    if (cursor == -1)
    {
        log(std::cout, "NA\t");
    }
    else
    {
        log(std::cout, cursor, "\t");
    }

    log(std::cout, "\n--------------------------------------------\n");
}

void disk::count()
{
    int free, dir, file;
    free = 0;
    dir = 0;
    file = 0;
    for (int i = 0; i < DISK_SIZE; i++)
    {
        if (this->freeSpaceList[i] == 1)
        {
            free++;
        }
        else
        {
            if (this->sector[i]->isDir() == true)
                dir++;
            else
                file++;
        }
    }
    log(std::cout, "# of free blocks: ", free, "\n");
    log(std::cout, "# of directory blocks: ", dir, "\n");
    log(std::cout, "# of data file blocks: ", file, "\n");
}

void disk::create(char type, std::string name)
{
    std::string original;
    original = name;

    if (type != 'U' && type != 'D')
    {
        log(std::cout, "Error: Create ", name, " failed. Please enter a vaild file type such as U or D", "\n");
    }
    else if (isOpen() == true && type == 'U')
    {
        log(std::cout, "Error: Create ", name, " failed because ", this->sector[openBlock]->getName(),
            " is opened. Please close it first before creating another file", "\n");
    }
    else
    {
        directory *parent;
        parent = helpFind((directory *)this->sector[0], name);

        if (parent == nullptr && index() != -1)
        {
            log(std::cout, "Error: Create ", name, " failed. File name ", name, " is not valid.\n");
        }
        else if (parent == nullptr && index() == -1)
        {
            log(std::cout, "Error: Create ", name, " failed. ALL the sectors are used.\n");
        }
        else
        {
            while (name.find('/') != name.npos)
            {
                name = name.substr(name.find('/') + 1);
            }

            block *newblock;
            newblock = helpCreate(type, name);
            if (newblock != nullptr)
            {
                parent->addEntry(newblock);
                log(std::cout, "Finished create ", name, "\n");

                if (type == 'U')
                {
                    open('O', original);
                }
            }
            else
            {
                log(std::cout, "Error: Create ", name, " failed. ALL the sectors are used.\n");
            }
        }
    }
}

void disk::open(char mode, std::string name)
{
    if (isOpen() == true)
    {
        log(std::cout, "Error: Open ", name, " failed because ", this->sector[openBlock]->getName(),
            " is opened. Please close it first before opening another file\n");
    }
    else if (mode != 'I' && mode != 'U' && mode != 'O')
    {
        log(std::cout, "Error: Open ", name, " failed. Please enter the correct open mode. (eg: I or U or O).\n");
    }
    else
    {
        block *b1;
        b1 = findBlock(name);

        if (b1 == nullptr)
        {
            log(std::cout, "Error: Open ", name, " failed because file name is not valid. Please try again.\n");
        }
        else
        {
            openBlock = b1->getBlockNumber();
            cursor = 0;
            if (mode == 'I')
            {
                openMode = 0;
                seek(-1, 0);
            }
            else if (mode == 'O')
            {
                openMode = 1;
                cursor = ((file *)this->sector[openBlock])->getEnd();
            }
            else
            {
                openMode = 2;
                seek(-1, 0);
            }
        }
    }
}

void disk::close()
{
    openBlock = -1;
    openMode = -1;
    cursor = -1;
}

void disk::deleteNew(std::string name)
{
    block *toBeDelete;
    directory *parent;
    int blockNum;

    blockNum = -1;
    toBeDelete = findBlock(name);
    parent = findParent((directory *)this->sector[0], name);

    if (toBeDelete != nullptr && parent != nullptr && toBeDelete->isDir() == false)
    {
        blockNum = toBeDelete->getBlockNumber();
        deleteBlock(parent, toBeDelete);
    }
    else if (toBeDelete != nullptr && parent != nullptr && toBeDelete->isDir() == true)
    {
        blockNum = toBeDelete->getBlockNumber();
        deleteBlock(parent, (directory *)toBeDelete);
    }
    else
    {
        log(std::cout, "Error: Delete ", name, " failed. Please enter a valid file name.\n");
    }

    if (blockNum == openBlock)
    {
        close();
    }
}

void disk::write(int count, std::string input)
{
    if (isOpen() == true && openMode == 0)
    {
        log(std::cout, "Error: Write failed because ", this->sector[openBlock]->getName(), " is in Input mode.\n");
    }
    else if (isOpen() == false)
    {
        log(std::cout, "Error: Write failed because no file is opened.\n");
    }
    else
    {
        int current, blockNum;
        file *next;

        current = cursor;
        blockNum = openBlock;
        next = (file *)(this->sector[openBlock]->getFrwd());

        while (current >= FILE_SIZE && next != nullptr)
        {
            openBlock = next->getBlockNumber();
            current -= FILE_SIZE;
            next = (file *)(this->sector[openBlock]->getFrwd());
        }

        if (current >= FILE_SIZE)
        {
            log(std::cout, "Error: Write failed because the cursor is getting beyond the size of ",
                this->sector[openBlock]->getName(), "\n");
        }
        else
        {
            helpWrite(count, input, current);
        }
        openBlock = blockNum;
    }
}

void disk::helpWrite(int &count, std::string &input, int &current)
{
    block *newFile;
    int totalToWrite, wrote;

    newFile = this->sector[openBlock];
    totalToWrite = current + count;
    wrote = 0;

    while (totalToWrite >= FILE_SIZE)
    {
        current = current % FILE_SIZE;
        if (FILE_SIZE > count)
        {
            wrote = count - current;
        }
        else
        {
            wrote = FILE_SIZE - current;
        }

        ((file *)this->sector[openBlock])->writeFile(count, input, current);
        totalToWrite -= wrote;

        newFile = helpCreate('U', this->sector[openBlock]->getName());

        if (newFile != nullptr)
        {
            this->sector[openBlock]->setFrwd(newFile);
            newFile->setBack(this->sector[openBlock]);
            openBlock = newFile->getBlockNumber();
        }
        else
        {
            break;
        }
    }

    if (totalToWrite < FILE_SIZE && newFile != nullptr)
    {
        current = current % FILE_SIZE;
        ((file *)this->sector[openBlock])->writeFile(count, input, current);
        if (count > 0)
        {
            log(std::cout,
                "Error: Write is unfinished because ALL the sectors are used and the disk can't allocate more.\n");
        }
    }
    else
    {
        log(std::cout,
            "Error: Write is unfinished because ALL the sectors are used and the disk can't allocate more.\n");
    }
}

void disk::read(int count)
{
    if (isOpen() == true && openMode == 1)
    {
        log(std::cout, "Error: Read failed because ", this->sector[openBlock]->getName(), " is in Output mode.\n");
    }
    else if (isOpen() == false)
    {
        log(std::cout, "Error: Read failed because no file is opened.\n");
    }
    else
    {
        int current, blockNum;
        block *next;

        current = cursor;
        blockNum = openBlock;
        next = this->sector[openBlock];

        while (current >= FILE_SIZE && next->getFrwd() != nullptr)
        {
            next = next->getFrwd();
            openBlock = next->getBlockNumber();
            current -= FILE_SIZE;
        }

        if (current >= FILE_SIZE)
        {
            log(std::cout, "Error: Read failed because the cursor is getting beyond the size of ",
                this->sector[openBlock]->getName(), "\n");
        }
        else
        {
            int totalRead, readed;
            totalRead = current + count;
            next = this->sector[openBlock];
            readed = 0;

            while (totalRead >= FILE_SIZE)
            {
                current = current % FILE_SIZE;
                if (FILE_SIZE > count)
                {
                    readed = count - current;
                }
                else
                {
                    readed = FILE_SIZE - current;
                }

                ((file *)this->sector[openBlock])->readFile(count, current);
                totalRead -= readed;

                next = this->sector[openBlock]->getFrwd();
                if (next != nullptr)
                {
                    openBlock = next->getBlockNumber();
                }
                else
                {
                    break;
                }
            }

            if (totalRead < FILE_SIZE && next != nullptr)
            {
                current = current % FILE_SIZE;
                ((file *)this->sector[openBlock])->readFile(count, current);
                log(std::cout, "(EOF)\n");
                if (count > 0)
                {
                    log(std::cout, "\nEnd of file is reached.\n");
                }
            }
            else
            {
                log(std::cout, "(EOF)\n");
                log(std::cout, "\nEnd of file is reached.\n");
            }
        }
        openBlock = blockNum;
    }
}

void disk::seek(int base, int offset)
{
    if (isOpen() == true && openMode == 1)
    {
        log(std::cout, "Error: Seek failed because ", this->sector[openBlock]->getName(), " is in Output mode.\n");
    }
    else if (isOpen() == false)
    {
        log(std::cout, "Error: Seek failed because no file is opened.\n");
    }
    else
    {
        if (base == -1 && offset >= 0)
        {
            cursor = 0;
            cursor += offset;
        }
        else if (base == -1 && offset < 0)
        {
            log(std::cout,
                "Error: Seek failed. Can't go backward when reach the "
                "beginning of the file.",
                "\n");
        }
        else if (base == 0)
        {
            if (cursor + offset < 0)
            {
                log(std::cout, "Error: Seek failed. Can't go backward when reach the beginning of the file.\n");
            }
            else
            {
                cursor += offset;
            }
        }
        else if (base == 1)
        {
            if (((file *)this->sector[openBlock])->getEnd() + offset < 0)
            {
                log(std::cout, "Error: Seek failed. Can't go backward when reach the beginning of the file.\n");
            }
            else
            {
                cursor = ((file *)this->sector[openBlock])->getEnd() + offset;
            }
        }
    }
}

block *disk::findBlock(std::string name)
{
    std::string original, name1;
    original = name;
    name1 = name.substr(name.find('/') + 1);

    while (name1.find('/') != name1.npos)
    {
        name1 = name1.substr(name1.find('/') + 1);
    }

    if (name1.find('/') && name1.length() <= 9)
    {
        block *temp;
        temp = nullptr;

        for (int i = 0; i < DISK_SIZE; i++)
        {
            if (this->sector[i] != nullptr && this->sector[i]->getName() == name1)
            {
                temp = this->sector[i];
                break;
            }
        }
        return temp;
    }
    else
    {
        return nullptr;
    }
}

directory *disk::findParent(directory *super, std::string name)
{
    if (name.find('/') != name.npos)
    {
        std::string name1, name2;
        name1 = name.substr(0, name.find('/'));
        name2 = name.substr(name.find('/') + 1);

        directory *sub;
        sub = super->getDirEntry(name1);

        if (sub != super)
        {
            return findParent(sub, name2);
        }

        else
        {
            return nullptr;
        }
    }
    else if (name.find('/') && name.length() <= 9)
    {
        block *file;
        directory *sub;
        sub = super->getDirEntry(name);
        file = super->getFileEntry(name);

        if (sub != super && file == nullptr)
        {
            return super;
        }
        else if (sub == super && file != nullptr)
        {
            return super;
        }

        else
        {
            return nullptr;
        }
    }
    else
        return nullptr;
}

block *disk::helpCreate(char type, std::string name)
{
    block *newblock;
    int sectorNum;

    sectorNum = index();
    newblock = nullptr;

    if (index() != -1)
    {
        if (type == 'U')
        {
            this->sector[sectorNum] = new file(sectorNum, name);
        }
        else
        {
            this->sector[sectorNum] = new directory(sectorNum, name);
        }
        this->freeSpaceList[sectorNum] = false;
        newblock = this->sector[sectorNum];
        log(std::cout, "Allocate a new block ", sectorNum, "\n");
    }

    return newblock;
}

directory *disk::helpFind(directory *super, std::string name)
{
    if (name.find('/') != name.npos)
    {
        std::string name1, name2;
        name1 = name.substr(0, name.find('/'));
        name2 = name.substr(name.find('/') + 1);

        directory *sub;
        sub = super->getDirEntry(name1);

        if (sub != super)
        {
            return helpFind(sub, name2);
        }
        else
        {
            block *newEntry;
            newEntry = helpCreate('D', name1);
            if (newEntry != nullptr)
            {
                super->addEntry(newEntry);
                return helpFind((directory *)newEntry, name2);
            }
            else
            {
                return nullptr;
            }
        }
    }
    else if (name.find('/') && name.length() <= 9)
    {
        block *file;
        directory *sub;
        sub = super->getDirEntry(name);
        file = super->getFileEntry(name);

        if (sub == super && file == nullptr)
        {
            return super;
        }
        else if (sub != super)
        {
            deleteBlock(super, sub);
            return super;
        }
        else
        {
            deleteBlock(super, file);
            return super;
        }
    }
    else
        return nullptr;
}

void disk::deleteBlock(directory *super, directory *dir)
{
    int deleteNum;

    if (dir->isEmpty() == true)
    {
        deleteNum = super->deleteNumber(dir);

        if (deleteNum == -1)
        {
            log(std::cout, "Error: ", dir->getName(), " delete failed because it is not located in directory ",
                super->getName(), "\n");
        }
        else
        {
            delete this->sector[deleteNum];
            this->sector[deleteNum] = nullptr;
            this->freeSpaceList[deleteNum] = true;
        }
    }
    else
    {
        block **entry;
        entry = dir->getEntryHead();

        for (int i = 0; i < DIR_SIZE; i++)
        {
            if (entry[i] != nullptr)
            {
                if (entry[i]->isDir() == true)
                {
                    deleteBlock(dir, (directory *)entry[i]);
                }
                else
                {
                    deleteBlock(dir, entry[i]);
                }
            }
        }

        deleteNum = super->deleteNumber(dir);

        if (deleteNum == -1)
        {
            log(std::cout, "Error: ", dir->getName(), " delete failed because it is not located in directory ",
                super->getName(), "\n");
        }
        else
        {
            delete this->sector[deleteNum];
            this->sector[deleteNum] = nullptr;
            this->freeSpaceList[deleteNum] = true;
        }
    }
}

void disk::deleteBlock(directory *super, block *file)
{
    int deleteNum;

    if (file->getBack() == nullptr && file->getFrwd() == nullptr)
    {
        deleteNum = super->deleteNumber(file);

        if (deleteNum == -1)
        {
            log(std::cout, "Error: ", file->getName(), " delete failed because it is not located in directory ",
                super->getName(), "\n");
        }
        else
        {
            delete this->sector[deleteNum];
            this->sector[deleteNum] = nullptr;
            this->freeSpaceList[deleteNum] = true;
        }
    }

    else
    {
        block *front;
        block *back;
        front = file;
        back = nullptr;

        while (front->getFrwd() != nullptr)
        {
            front = front->getFrwd();
            back = front->getBack();
        }

        while (back != nullptr)
        {
            deleteNum = front->getBlockNumber();
            front->setBack((block *)nullptr);
            back->setFrwd((block *)nullptr);

            delete this->sector[deleteNum];
            this->sector[deleteNum] = nullptr;
            this->freeSpaceList[deleteNum] = true;

            front = back;
            back = front->getBack();
        }

        deleteNum = super->deleteNumber(file);
        delete this->sector[deleteNum];
        this->sector[deleteNum] = nullptr;
        this->freeSpaceList[deleteNum] = true;
    }
}
} // namespace fsx
