#include "block.hpp"

namespace fsx
{
block::block()
{
    this->dir = false;
    this->name = "";
    this->number = -1;
    this->frwd = nullptr;
    this->back = nullptr;
}

block::block(int blockNumber, bool isDir, const std::string &blockName)
    : dir(isDir), name(blockName), number(blockNumber)
{
    if (number != 0)
    {
        this->frwd = nullptr;
        this->back = nullptr;
    }
    else
    {
        this->frwd = this;
        this->back = this;
    }
}

block::~block()
{
    log(std::cout, "block ", this->getBlockNumber(), " is now empty.\n");
    reset();
}

int block::getBlockNumber()
{
    return this->number;
}

bool block::isDir()
{
    return this->dir;
}

void block::setFrwd(block *frwd)
{
    this->frwd = frwd;
}

void block::setBack(block *back)
{
    this->back = back;
}

void block::reset()
{
    this->number = -1;
    this->dir = false;
    this->frwd = nullptr;
    this->back = nullptr;
    this->name = "";
}

block *block::getFrwd()
{
    return this->frwd;
}

block *block::getBack()
{
    return this->back;
}

std::string block::getName()
{
    return this->name;
}
} // namespace fsx