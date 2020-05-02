#include "block.hpp"

namespace fs
{
block::block()
{
    dir = false;

    name = "";
    number = -1;
    frwd = nullptr;
    back = nullptr;
}

block::block(int blockNumber, bool isDir, const std::string &blockName)
    : dir(isDir), name(blockName), number(blockNumber)
{
    if (number != 0)
    {
        frwd = nullptr;
        back = nullptr;
    }
    else
    {
        frwd = this;
        back = this;
    }
}

block::~block()
{
    log(std::cout, "block ", this->getBlockNumber(), " is now empty.\n");
    reset();
}

int block::getBlockNumber()
{
    return number;
}

bool block::isDir()
{
    return dir;
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
    number = -1;
    dir = false;
    frwd = nullptr;
    back = nullptr;
    name = "";
}

block *block::getFrwd()
{
    return frwd;
}

block *block::getBack()
{
    return back;
}

std::string block::getName()
{
    return name;
}
} // namespace fs