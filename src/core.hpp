//
// Created by ayesdie on 02/05/20.
//

#ifndef FILESYSTEMSIMULATOR_CORE_HPP
#define FILESYSTEMSIMULATOR_CORE_HPP

#include <iostream>
#include <string>
const int DISK_SIZE = 100;
const int FILE_SIZE = 504;
const int DIR_SIZE = 31;
static int openBlock = -1;
static int openMode = -1; // 0 = input, 1 = output, 2 = update
static int cursor = -1;

#endif // FILESYSTEMSIMULATOR_CORE_HPP
