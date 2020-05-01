//
// Created by ayesdie on 01/05/20.
//

#ifndef FILESYSTEMSIMULATOR_DIRECTORY_HPP
#define FILESYSTEMSIMULATOR_DIRECTORY_HPP

#include "fss.hpp"
#include <string>
#include <iostream>

class directory : public block
{
private:
    block* entry[DIR_SIZE];
    int free;       // ROOT: block number of first unused block
public:
    directory(int number, std::string name);         // constructor for directory block
    ~directory();                               // destructor
    directory* getDirEntry(std::string name);        // get the directory block* for name
    block* getFileEntry(std::string name);           // get the file block* for name
    block** getEntryHead();                     // return the block* of entry;
    int deleteNumber(block* file);              // return the block number of the to be deleted block*
    int getSize();                              // return the size of the directory block
    void addEntry(block* newEntry);             // add an newly allocated entry
    void setFree(int index);                    // set free for root block
    void display(std::string indent);                // display directory content
    bool isEmpty();
};


#endif //FILESYSTEMSIMULATOR_DIRECTORY_HPP
