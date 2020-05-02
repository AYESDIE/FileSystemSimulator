//
// Created by ayesdie on 01/05/20.
//

#include "block.hpp"

namespace fs {
block::block() {
  number = -1;
  dir = false;
  frwd = nullptr;
  back = nullptr;
  name = "";
}

block::block(int number, bool isDir, std::string name) {
  this->dir = isDir;
  this->name = name;
  this->number = number;

  if (number == 0) {
    frwd = this;
    back = this;
  } else {
    frwd = nullptr;
    back = nullptr;
  }
}

block::~block() {
  std::cout << "block " << this->getNumber() << " is now empty." << std::endl;
  reset();
}

int block::getNumber() { return number; }

bool block::isDir() { return dir; }

void block::setFrwd(block *frwd) { this->frwd = frwd; }

void block::setBack(block *back) { this->back = back; }

void block::reset() {
  number = -1;
  dir = false;
  frwd = nullptr;
  back = nullptr;
  name = "";
}

block *block::getFrwd() { return frwd; }

block *block::getBack() { return back; }

std::string block::getName() { return name; }
} // namespace fs