#ifndef FSX_BLOCK_HPP
#define FSX_BLOCK_HPP

#include "core.hpp"

namespace fsx
{
/**
 * A class representation of a block.
 */
class block
{
  public:
    /**
     * Default constructor for a block.
     */
    block();

    /**
     * Parameterized constructor for a file or directory block.
     * @param blockNumber - Number of the block.
     * @param isDir - Flag: True: The block is a directory.
     * @param blockName - name of the block.
     */
    block(int blockNumber, bool isDir, const std::string &blockName);

    /**
     * Virtual destructor for block.
     */
    virtual ~block();

    /**
     * @return - block number
     */
    int getBlockNumber();

    /**
     * @return - frwd block pointer.
     */
    block *getFrwd();

    /**
     * @return - back block pointer.
     */
    block *getBack();

    /**
     * @return - name of the block.
     */
    std::string getName();

    /**
     * Return the type of block.
     * @return - True: Block is directory; else false.
     */
    bool isDir();

    /**
     * Set the frwd block pointer.
     * @param frwd - frwd block pointer.
     */
    void setFrwd(block *frwd);

    /**
     * Set the back block pointer.
     * @param back - back block pointer.
     */
    void setBack(block *back);

    /**
     * Resets the block pointer to null pointer.
     */
    void reset();

  private:
    // Block Number
    int number;

    // frwd Block Pointer
    block *frwd;

    // back Block Pointer
    block *back;

    // Block Name
    std::string name;

    // Block Type
    bool dir;
};
} // namespace fsx

#endif // FSX_BLOCK_HPP
