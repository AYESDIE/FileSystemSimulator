#include "file.hpp"

namespace fs
{
file::file(int number, std::string name) : block(number, false, name)
{
    for (int i = 0; i < FILE_SIZE; i++)
    {
        data[i] = '\0';
    }
}

file::~file()
{
    log(std::cout, "data file ", this->getName(), " is deleted.\n");
}

void file::writeFile(int &count, std::string &input, int &current)
{
    for (; current < FILE_SIZE && 0 < count; count--)
    {
        if (input != "")
        {
            data[current] = input[0];
            input = input.substr(input.find(input[0]) + 1);
            current++;
            cursor++;
        }
        else
        {
            data[current] = ' ';
            cursor++;
            current++;
        }
    }
}

void file::readFile(int &count, int &current)
{
    for (; current < FILE_SIZE && 0 < count; count--)
    {
        if (data[current] != '\0')
        {
            log(std::cout, data[current]);
            cursor++;
            current++;
        }
        else
        {
            break;
        }
    }
}

void file::display(std::string indent)
{
    log(std::cout, indent, this->getName(), "\tU\t");
    log(std::cout, "#: ", this->getBlockNumber());

    block *temp;
    block *size;
    temp = this->getFrwd();
    size = this;

    while (temp != nullptr)
    {
        log(std::cout, "<=>", temp->getBlockNumber());
        size = temp;
        temp = temp->getFrwd();
    }

    log(std::cout, "\tSIZE: ", ((file *)size)->getSize(), "\n");
}

int file::getEnd()
{
    int current;
    bool flag;
    current = 0;
    flag = false;

    for (int i = 0; i < FILE_SIZE; i++)
    {
        if (data[i] == '\0')
        {
            current = i;
            flag = true;
            break;
        }
    }

    file *next;
    next = (file *)this->getFrwd();

    if (flag == false && next != nullptr)
    {
        return next->getEnd() + 504;
    }
    else
    {
        return current;
    }
}

int file::getSize()
{
    int size;
    size = 0;

    for (int i = 0; i < FILE_SIZE; i++)
    {
        if (data[i] != '\0')
        {
            size++;
        }
    }
    return size;
}
} // namespace fs