#include <iostream>
#include <cstring>
#include <fss.hpp>

#define ARGLEN  50500   // token length
#define MAXARGS 3       // cmdline args
using namespace std;

// split a string into tokens
void parse( char* input, char* args[] ) {
    input[std::strlen(input)-1] = '\0';  // fgets reads the \n, so overwrite it
    args[0] = std::strtok(input, " ");
    args[1] = std::strtok(NULL, " ");
    args[2] = std::strtok(NULL, "\0");   // for writing long string
}


int main() {

    char arg [ARGLEN];
    char* arglist[MAXARGS];
    Disk* Disk1;

    Disk1 = new Disk();

    while (strcmp(arg, "exit\n") != 0) {
        printf(" > ");
        if ( fgets(arg, ARGLEN, stdin) == NULL) {
            perror( "read input failed" );
            exit(1);
        }
        else {
            if (strcmp(arg, "exit\n") == 0)     // exit command to finish
                exit(0);

            parse(arg, arglist);
            if ((strcmp(arglist[0], "create") == 0 || strcmp(arglist[0], "CREATE") == 0) && arglist[2]!= nullptr && arglist[1]!= nullptr) {
                Disk1->create(arglist[1][0], arglist[2]);
                Disk1->display();
            }
            else if ((strcmp(arglist[0], "open") == 0 || strcmp(arglist[0], "OPEN") == 0) && arglist[2] != nullptr && arglist[1]!= nullptr) {
                Disk1->open(arglist[1][0], arglist[2]);
                Disk1->display();
            }
            else if (strcmp(arglist[0], "close") == 0 || strcmp(arglist[0], "CLOSE") == 0) {
                Disk1->close();
                Disk1->display();
            }
            else if ((strcmp(arglist[0], "delete") == 0 || strcmp(arglist[0], "DELETE") == 0) && arglist[1]!= nullptr) {
                Disk1->deleteNew(arglist[1]);
                Disk1->display();
            }
            else if ((strcmp(arglist[0], "write") == 0 || strcmp(arglist[0], "WRITE") == 0) && arglist[2]!= nullptr && arglist[1]!= nullptr) {
                if (arglist[2][0] == '\'' && arglist[2][std::strlen(arglist[2])-1] == '\'') {
                    // trim off the single quotes
                    char trim[std::strlen(arglist[2])-2];
                    for (int i = 0; i < std::strlen(arglist[2])-2; i++) {
                        trim[i] = arglist[2][i+1];
                    }
                    Disk1->write(atoi(arglist[1]), trim);
                    Disk1->display();
                }
                else {
                    cout << "Error: Write failed. Please put single quote \' \' outside the writing input" << endl;
                    Disk1->display();
                }
            }
            else if ((strcmp(arglist[0], "read") == 0 || strcmp(arglist[0], "READ") == 0) && arglist[1]!= nullptr) {
                Disk1->read(atoi(arglist[1]));
                Disk1->display();
            }
            else if ((strcmp(arglist[0], "seek") == 0 || strcmp(arglist[0], "SEEK") == 0) && arglist[1]!= nullptr && arglist[2]!= nullptr) {
                Disk1->seek(atoi(arglist[1]), atoi(arglist[2]));
                Disk1->display();
            }
            else {
                cout << "Error: please enter a valid input" << endl;
                Disk1->display();
            }
        }
    }
    return 0;
}
