//
// Created by ayesdie on 01/05/20.
//

#include "directory.hpp"

namespace fs {
directory::directory(int number, std::string name) : block(number, true, name) {
  free = -1;
  for (int i = 0; i < DIR_SIZE; i++) {
    entry[i] = nullptr;
  }
}

directory::~directory() {
  std::cout << "directory " << this->getName() << " is deleted." << std::endl;
}

directory *directory::getDirEntry(std::string name) {
  directory *temp;
  temp = this;

  for (int i = 0; i < DIR_SIZE; i++) {
    if (entry[i] != nullptr && entry[i]->getName() == name &&
        entry[i]->isDir() == true) {
      temp = (directory *)entry[i];
      break;
    }
  }
  return temp;
}

block *directory::getFileEntry(std::string name) {
  block *temp;
  temp = nullptr;

  for (int i = 0; i < DIR_SIZE; i++) {
    if (entry[i] != nullptr && entry[i]->getName() == name &&
        entry[i]->isDir() == false) {
      temp = entry[i];
      break;
    }
  }
  return temp;
}

block **directory::getEntryHead() { return entry; }

int directory::deleteNumber(block *toDelete) {
  int temp;
  temp = -1;

  for (int i = 0; i < DIR_SIZE; i++) {
    if (entry[i]->getNumber() == toDelete->getNumber()) {
      temp = entry[i]->getNumber();
      entry[i] = nullptr;
      break;
    }
  }
  return temp;
}

int directory::getSize() {
  int size;
  size = 0;

  for (int i = 0; i < DIR_SIZE; i++) {
    if (entry[i] != nullptr) {
      size++;
    }
  }
  return size;
}

void directory::addEntry(block *newEntry) {
  for (int i = 0; i < DIR_SIZE; i++) {
    if (entry[i] == nullptr) {
      entry[i] = newEntry;
      break;
    }
  }
}

void directory::setFree(int index) {
  if (this->getNumber() == 0) {
    free = index;
  } else
    free = -1;
}

void directory::display(std::string indent) {
  // display name, type, block number, and size
  std::cout << indent << this->getName() << "\tD\t";
  std::cout << "#: " << this->getNumber() << "\tSIZE: " << this->getSize()
            << std::endl;

  // display back pointer block #
  if (this->getBack() == nullptr) {
    std::cout << indent << "-BACK: nullptr" << std::endl;
  } else {
    std::cout << indent << "-BACK: " << this->getBack()->getNumber()
              << std::endl;
  }

  // display forward pointer block #
  if (this->getFrwd() == nullptr) {
    std::cout << indent << "-FRWD: nullptr" << std::endl;
  } else {
    std::cout << indent << "-FRWD: " << this->getFrwd()->getNumber()
              << std::endl;
  }

  if (this->getNumber() == 0) {
    std::cout << indent << "-FREE: " << free << std::endl;
  }

  std::cout << indent << "-FILLER: UNUSED" << std::endl;

  if (isEmpty() == false) {
    indent += "\t";
    for (int i = 0; i < DIR_SIZE; i++) {
      if (entry[i] != nullptr) {
        if (entry[i]->isDir() == true) {
          ((directory *)entry[i])->display(indent);
        } else {
          ((file *)entry[i])->display(indent);
        }
      }
    }
  }
}

bool directory::isEmpty() {
  bool flag;
  flag = true;

  for (int i = 0; i < DIR_SIZE; i++) {
    if (entry[i] != nullptr) {
      flag = false;
      break;
    }
  }
  return flag;
}
} // namespace fs