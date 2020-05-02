#ifndef FSX_DIRECTORY_HPP
#define FSX_DIRECTORY_HPP

#include "block.hpp"
#include "core.hpp"
#include "file.hpp"

namespace fsx
{
/**
 * Class representation for a directory.
 */
class directory : public block
{
  public:
    /**
     * Constructor for a directory block.
     *
     * @param number - Block Number
     * @param name - Block Name
     */
    directory(int number, std::string name);

    /**
     * Destructor for directory block.
     */
    ~directory();

    /**
     * Get the block pointer for the given directory name
     * @param name - name of the directory
     * @return - block pointer for the directory.
     */
    directory *getDirEntry(std::string name);

    /**
     * Get the block pointer for the given file name.
     * @param name - name of the file
     * @return - black pointer for the file.
     */
    block *getFileEntry(std::string name);

    /**
     * Get the block pointer of entry.
     * @return - block pointer of entry.
     */
    block **getEntryHead();

    /**
     * Delete block pointer, returns block number associated to it.
     * @param file - filer block pointer to be deleted.
     * @return - block number associated to the file
     */
    int deleteNumber(block *file);

    /**
     * @return - size of the directory block.
     */
    int getSize();

    /**
     * Add a newly allocated entry.
     * @param newEntry - new allocated entry.
     */
    void addEntry(block *newEntry);

    /**
     * Set free for root.
     * @param index - index
     */
    void setFree(int index);

    /**
     * Displayes the content of the directory.
     */
    void display(std::string indent);

    /**
     * @return - True if the directory is empty.
     */
    bool isEmpty();

  private:
    block *entry[DIR_SIZE];

    int free;
};
} // namespace fsx

#endif // FSX_DIRECTORY_HPP
