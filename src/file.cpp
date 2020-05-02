//
// Created by ayesdie on 01/05/20.
//

#include "file.hpp"

namespace fs
{
    // constructor for file block
    file::file(int number, std::string name): block(number, false, name)
    {
        for (int i = 0; i < FILE_SIZE; i++) {
            data[i] = '\0';
        }
    }

// destructor of file
    file::~file()
    {   std::cout << "data file " << this->getName() << " is deleted."<< std::endl;   }

// write input into file
    void file::writeFile(int& count, std::string& input, int& current)
    {
        for (; current < FILE_SIZE && 0 < count; count--) {
            if (input != "") {
                data[current] = input[0];
                input = input.substr(input.find(input[0])+1);
                current++;
                cursor++;
            }
            else {
                data[current] = ' ';
                cursor++;
                current++;
            }
        }
    }

// read and display file data
    void file::readFile(int& count, int& current)
    {
        for (; current < FILE_SIZE && 0 < count; count--) {
            if (data[current] != '\0') {
                std::cout << data[current];
                cursor++;
                current++;
            }
            else {
                break;
            }
        }
    }

// display file content
    void file::display(std::string indent)
    {
        // display file name
        std::cout << indent << this->getName() << "\tU\t";
        std::cout << "#: " << this->getNumber();

        // display file linkers
        block* temp;
        block* size;
        temp = this->getFrwd();
        size = this;

        while (temp != nullptr) {
            std::cout << "<=>" << temp->getNumber();
            size = temp;
            temp = temp->getFrwd();
        }

        // display file size
        std::cout << "\tSIZE: " << ((file*)size)->getSize() << std::endl;
    }

// return end of file index of data[]
    int file::getEnd()
    {
        int current;
        bool flag;
        current = 0;
        flag = false;

        for (int i = 0; i < FILE_SIZE; i++) {
            if (data[i] == '\0') {
                current = i;
                flag = true;
                break;
            }
        }

        file* next;
        next = (file*)this->getFrwd();

        if (flag == false && next != nullptr) {
            return next->getEnd()+504;
        }
        else {
            return current;
        }
    }

// return the size of the directory block
    int file::getSize()
    {
        int size;
        size = 0;

        for (int i = 0; i < FILE_SIZE; i++) {
            if (data[i] != '\0') {
                size++;
            }
        }
        return size;
    }
}