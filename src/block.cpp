//
// Created by ayesdie on 01/05/20.
//

#include "block.hpp"

namespace fs {
    // default constructor for block
    block::block()
    {
        number = -1;
        dir = false;
        frwd = nullptr;
        back = nullptr;
        name = "";
    }

// constructor for directory or file block
    block::block(int number, bool isDir, std::string name)
    {
        this->dir = isDir;
        this->name = name;
        this->number = number;

        if (number == 0) {
            frwd = this;
            back = this;
        }
        else    {
            frwd = nullptr;
            back = nullptr;
        }
    }

// destructor of block
    block::~block()
    {
        std::cout << "block " << this->getNumber() << " is now empty."<< std::endl;
        reset();
    }

// return block number
    int block::getNumber()
    {   return number;  }

// return the type of block
    bool block::isDir()
    {   return dir;     }

// set frwd block pointer
    void block::setFrwd(block* frwd)
    {   this->frwd = frwd;  }

// set back block pointer
    void block::setBack(block* back)
    {   this->back = back;  }

// reset a block* to nullptr
    void block::reset()
    {
        number = -1;
        dir = false;
        frwd = nullptr;
        back = nullptr;
        name = "";
    }

// return frwd block pointer
    block* block::getFrwd()
    {   return frwd;    }

// return back block pointer
    block* block::getBack()
    {   return back;    }

// return block name
    std::string block::getName()
    {   return name;    }
}