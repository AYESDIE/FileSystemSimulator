#ifndef FSX_FILE_HPP
#define FSX_FILE_HPP

#include "block.hpp"
#include "core.hpp"

namespace fsx
{
/**
 * A class representation for a file block.
 */
class file : public block
{
  public:
    /**
     * Parameterized constructor for the file block.
     * @param number - Block Number
     * @param name - Block Name
     */
    file(int number, std::string name);

    /**
     * Destructor for file block.
     */
    ~file();

    /**
     * Write the given input to the file.
     * @param count - the length of file.
     * @param input - string input to be written.
     * @param current - current location for cursor.
     */
    void writeFile(int &count, std::string &input, int &current);

    /**
     * Reads and displays the data in the file.
     * @param count - the count to which to read.
     * @param current - current location of cursor.
     */
    void readFile(int &count, int &current);

    /**
     * Display the contents of the file.
     */
    void display(std::string indent);

    /**
     * @return - EOF index of data.
     */
    int getEnd();

    /**
     * @return - size of the file block
     */
    int getSize();

  private:
    // Data in the file.
    char data[FILE_SIZE];
};
} // namespace fsx

#endif // FSX_FILE_HPP
