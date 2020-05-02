#ifndef FILESYSTEMSIMULATOR_BLOCK_HPP
#define FILESYSTEMSIMULATOR_BLOCK_HPP

#include "core.hpp"

namespace fs
{
    class block {
    private:
        int number;
        block* frwd;
        block* back;
        std::string name;
        bool dir;
    public:
        block();                                    // default constructor for block
        block(int number, bool isDir, std::string name); // constructor for directory or file block
        virtual~block();                            // virtual destructor
        int getNumber();                            // return block number
        bool isDir();                               // return the type of block
        void setFrwd(block* frwd);                  // set frwd block pointer
        void setBack(block* back);                  // set back block pointer
        void reset();                               // reset a block* to nullptr
        block* getFrwd();                           // return frwd block pointer
        block* getBack();                           // return back block pointer
        std::string getName();                           // return block name
    };
}

#endif //FILESYSTEMSIMULATOR_BLOCK_HPP
