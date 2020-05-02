////
//// Created by ayesdie on 01/05/20.
////
//
//#ifndef FILESYSTEMSIMULATOR_FS_HPP
//#define FILESYSTEMSIMULATOR_FS_HPP
//
//
//#include <stdio.h>
//#include <string>
//#include <iostream>
//using namespace std;
//const int DISK_SIZE = 100;
//const int FILE_SIZE = 504;
//const int DIR_SIZE = 31;
//static int openBlock = -1;
//static int openMode = -1;   // 0 = input, 1 = output, 2 = update
//static int cursor = -1;
//
//
//
//
//class Block
//{
//private:
//    int number;
//    Block* frwd;
//    Block* back;
//    string name;
//    bool dir;
//public:
//    Block();                                    // default constructor for block
//    Block(int number, bool isDir, string name); // constructor for directory or file block
//    virtual~Block();                            // virtual destructor
//    int getNumber();                            // return block number
//    bool isDir();                               // return the type of block
//    void setFrwd(Block* frwd);                  // set frwd block pointer
//    void setBack(Block* back);                  // set back block pointer
//    void reset();                               // reset a Block* to nullptr
//    Block* getFrwd();                           // return frwd block pointer
//    Block* getBack();                           // return back block pointer
//    string getName();                           // return block name
//};
//
//
//
//
//
//
//class Directory: public Block
//{
//private:
//    Block* entry[DIR_SIZE];
//    int free;       // ROOT: block number of first unused block
//public:
//    Directory(int number, string name);         // constructor for directory block
//    ~Directory();                               // destructor
//    Directory* getDirEntry(string name);        // get the directory block* for name
//    Block* getFileEntry(string name);           // get the file block* for name
//    Block** getEntryHead();                     // return the Block* of entry;
//    int deleteNumber(Block* file);              // return the block number of the to be deleted Block*
//    int getSize();                              // return the size of the directory block
//    void addEntry(Block* newEntry);             // add an newly allocated entry
//    void setFree(int index);                    // set free for root block
//    void display(string indent);                // display directory content
//    bool isEmpty();                             // check whether the directory is empty
//};
//
//
//
//
//
//
//class File: public Block
//{
//private:
//    char data[FILE_SIZE];
//public:
//    File(int number, string name);              // constructor for file block
//    ~File();                                    // destructor
//    void writeFile(int& count, string& input, int& current);    // write input into file
//    void readFile(int& count, int& current);                    // read and display file data
//    void display(string indent);                // display file content
//    int getEnd();                               // return end of file index of data[]
//    int getSize();                              // return the size of the file block
//};
//
//
//
//
//
//
//class Disk: public Block
//{
//private:
//    Block* sector[DISK_SIZE];
//    bool freeSpaceList[DISK_SIZE];  // true = F, false = D or U
//public:
//    Disk();                         // constructor of disk, allocate root directory
//    ~Disk();                        // destructor
//    int index();                    // return the index of first available sector in the disk
//    bool isOpen();                  // check the open status;
//    void display();                 // display the hierarchy structure of the disk
//    void count();                   // count the type of file in the disk
//    void create(char type, string name);                // create a new block
//    void open(char mode, string name);                  // open a block
//    void close();                                       // closed the last open block (reset)
//    void deleteNew(string name);                        // delete the name block
//    void write(int count, string input);                // write into a file
//    void helpWrite(int&count,string&input,int&current); // help write into file
//    void read(int count);                               // read out the file
//    void seek(int base, int offset);                    // seek for cursor
//    Block* findBlock(string name);                      // return the Block* of name file block
//    Directory*findParent(Directory* super,string name); // return the Block* of the parent directory
//    Block* helpCreate(char type, string name);          // return the Block* of newly allocated block
//    Directory* helpFind(Directory* super, string name); // return the Block* of the parent directory (overwrite)
//    void deleteBlock(Directory* super, Directory* dir); // delete a allocated block dir from directory super
//    void deleteBlock(Directory* super, Block* file);    // delete a allocated block file from directory super
//
//};
//
//
//#endif //FILESYSTEMSIMULATOR_FS_HPP
