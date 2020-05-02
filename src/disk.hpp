//
// Created by ayesdie on 01/05/20.
//

#ifndef FILESYSTEMSIMULATOR_DISK_HPP
#define FILESYSTEMSIMULATOR_DISK_HPP

#include "block.hpp"
#include "directory.hpp"
#include "fss.hpp"

namespace fs {
class disk : public block {
private:
  block *sector[DISK_SIZE];
  bool freeSpaceList[DISK_SIZE]; // true = F, false = D or U
public:
  disk();         // constructor of disk, allocate root directory
  ~disk();        // destructor
  int index();    // return the index of first available sector in the disk
  bool isOpen();  // check the open status;
  void display(); // display the hierarchy structure of the disk
  void count();   // count the type of file in the disk
  void create(char type, std::string name); // create a new block
  void open(char mode, std::string name);   // open a block
  void close();                     // closed the last open block (reset)
  void deleteNew(std::string name); // delete the name block
  void write(int count, std::string input); // write into a file
  void helpWrite(int &count, std::string &input,
                 int &current);       // help write into file
  void read(int count);               // read out the file
  void seek(int base, int offset);    // seek for cursor
  block *findBlock(std::string name); // return the block* of name file block
  directory *
  findParent(directory *super,
             std::string name); // return the block* of the parent directory
  block *
  helpCreate(char type,
             std::string name); // return the block* of newly allocated block
  directory *helpFind(directory *super,
                      std::string name); // return the block* of the parent
                                         // directory (overwrite)
  void deleteBlock(
      directory *super,
      directory *dir); // delete a allocated block dir from directory super
  void deleteBlock(
      directory *super,
      block *file); // delete a allocated block file from directory super
};
} // namespace fs

#endif // FILESYSTEMSIMULATOR_DISK_HPP
