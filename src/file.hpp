//
// Created by ayesdie on 01/05/20.
//

#ifndef FILESYSTEMSIMULATOR_FILE_HPP
#define FILESYSTEMSIMULATOR_FILE_HPP

#include "block.hpp"
#include "core.hpp"

namespace fs {
class file : public block {
private:
  char data[FILE_SIZE];

public:
  file(int number, std::string name); // constructor for file block
  ~file();                            // destructor
  void writeFile(int &count, std::string &input,
                 int &current);            // write input into file
  void readFile(int &count, int &current); // read and display file data
  void display(std::string indent);        // display file content
  int getEnd();                            // return end of file index of data[]
  int getSize();                           // return the size of the file block
};
} // namespace fs

#endif // FILESYSTEMSIMULATOR_FILE_HPP
