#include "directory.hpp"

namespace fsx
{
directory::directory(int number, std::string name) : block(number, true, name)
{
    this->free = -1;
    for (int i = 0; i < DIR_SIZE; i++)
    {
        this->entry[i] = nullptr;
    }
}

directory::~directory()
{
    log(std::cout, "directory ", this->getName(), " is deleted.\n");
}

directory *directory::getDirEntry(std::string name)
{
    directory *temp;
    temp = this;

    for (int i = 0; i < DIR_SIZE; i++)
    {
        if (this->entry[i] != nullptr && this->entry[i]->getName() == name && this->entry[i]->isDir() == true)
        {
            temp = (directory *)this->entry[i];
            break;
        }
    }
    return temp;
}

block *directory::getFileEntry(std::string name)
{
    block *temp;
    temp = nullptr;

    for (int i = 0; i < DIR_SIZE; i++)
    {
        if (this->entry[i] != nullptr && this->entry[i]->getName() == name && this->entry[i]->isDir() == false)
        {
            temp = this->entry[i];
            break;
        }
    }
    return temp;
}

block **directory::getEntryHead()
{
    return this->entry;
}

int directory::deleteNumber(block *toDelete)
{
    int temp;
    temp = -1;

    for (int i = 0; i < DIR_SIZE; i++)
    {
        if (this->entry[i]->getBlockNumber() == toDelete->getBlockNumber())
        {
            temp = this->entry[i]->getBlockNumber();
            this->entry[i] = nullptr;
            break;
        }
    }
    return temp;
}

int directory::getSize()
{
    int size;
    size = 0;

    for (int i = 0; i < DIR_SIZE; i++)
    {
        if (this->entry[i] != nullptr)
        {
            size++;
        }
    }
    return size;
}

void directory::addEntry(block *newEntry)
{
    for (int i = 0; i < DIR_SIZE; i++)
    {
        if (this->entry[i] == nullptr)
        {
            this->entry[i] = newEntry;
            break;
        }
    }
}

void directory::setFree(int index)
{
    if (this->getBlockNumber() == 0)
    {
        this->free = index;
    }
    else
        this->free = -1;
}

void directory::display(std::string indent)
{
    log(std::cout, indent, this->getName(), "\tD\t");
    log(std::cout, "#: ", this->getBlockNumber(), "\tSIZE: ", this->getSize(), "\n");

    if (this->getBack() == nullptr)
    {
        log(std::cout, indent, "-BACK: nullptr\n");
    }
    else
    {
        log(std::cout, indent, "-BACK: ", this->getBack()->getBlockNumber(), "\n");
    }

    if (this->getFrwd() == nullptr)
    {
        log(std::cout, indent, "-FRWD: nullptr\n");
    }
    else
    {
        log(std::cout, indent, "-FRWD: ", this->getFrwd()->getBlockNumber(), "\n");
    }

    if (this->getBlockNumber() == 0)
    {
        log(std::cout, indent, "-FREE: ", free, "\n");
    }

    log(std::cout, indent, "-FILLER: UNUSED\n");

    if (isEmpty() == false)
    {
        indent += "\t";
        for (int i = 0; i < DIR_SIZE; i++)
        {
            if (this->entry[i] != nullptr)
            {
                if (this->entry[i]->isDir() == true)
                {
                    ((directory *)this->entry[i])->display(indent);
                }
                else
                {
                    ((file *)this->entry[i])->display(indent);
                }
            }
        }
    }
}

bool directory::isEmpty()
{
    bool flag;
    flag = true;

    for (int i = 0; i < DIR_SIZE; i++)
    {
        if (this->entry[i] != nullptr)
        {
            flag = false;
            break;
        }
    }
    return flag;
}
} // namespace fsx