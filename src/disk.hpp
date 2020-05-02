#ifndef FSX_DISK_HPP
#define FSX_DISK_HPP

#include "block.hpp"
#include "directory.hpp"

namespace fsx
{
/**
 * Class representation for a disk block.
 */
class disk : public block
{
  public:
    /**
     * Default constructor for disk, it also allocate root directory.
     */
    disk();

    /**
     * Destructor for disk block.
     */
    ~disk();

    /**
     * @return - Index of first available sector in the disk.
     */
    int index();

    /**
     * @return - True if the status is open.
     */
    bool isOpen();

    /**
     * Display the hierarchy structure of disk.
     */
    void display();

    /**
     * Counts the file in the disk.
     */
    void count();

    /**
     * Creates a new block.
     */
    void create(char type, std::string name);

    /**
     * Opens a block
     *
     * @param mode - Mode of operation.
     * @param name - Name of the block.
     */
    void open(char mode, std::string name);

    /**
     * Closes the last opened block.
     */
    void close();

    /**
     * Deletes the block.
     *
     * @param name - name of the block to be deleted.
     */
    void deleteNew(std::string name);

    /**
     * Writes input to the file.
     *
     * @param count - Length of file.
     * @param input - Input to be written into file.
     */
    void write(int count, std::string input);

    /**
     * Helps write into file.
     *
     * @param count - Length of file.
     * @param input - Input to be written into file.
     * @param current - Current location of cursor.
     */
    void helpWrite(int &count, std::string &input, int &current);

    /**
     * Read the content of file.
     *
     * @param count - Length to be read.
     */
    void read(int count);

    /**
     * Seek for the cursor.
     *
     * @param base - Base
     * @param offset - Offset
     */
    void seek(int base, int offset);

    /**
     * Find and return the file block pointer.
     *
     * @param name - Name of the file.
     * @return - Block pointer of the file.
     */
    block *findBlock(std::string name);

    /**
     * Find and return the block pointer of the parent directory.
     */
    directory *findParent(directory *super, std::string name);

    /**
     * Return block pointer of a newly allocated block.
     */
    block *helpCreate(char type, std::string name);

    /**
     * Help in finding the block pointer of the parent.
     */
    directory *helpFind(directory *super, std::string name);

    /**
     * Delete the allocated block directory from the directory super.
     *
     * @param super - Super Directory
     * @param dir - Directory
     */
    void deleteBlock(directory *super, directory *dir);

    /**
     * Delete the allocated block file from the directory super.
     *
     * @param super - Super Directory
     * @param file - File
     */
    void deleteBlock(directory *super, block *file);

  private:
    block *sector[DISK_SIZE];
    bool freeSpaceList[DISK_SIZE];
};
} // namespace fsx

#endif // FSX_DISK_HPP
