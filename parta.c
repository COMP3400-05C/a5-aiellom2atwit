#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * @brief Reads a file given in args on an 8 bit buffer and tallies char types
 * 
 * @param argc Number of args given, shoud be 1 for valid program usage
 * @param argv First arg is the name of the file to read
 * @return int 0 if success, 1 if invalid args, 2 if file doesn't exist
 */
int main(int argc, char* argv[]) {
    // Declare the buffer to use. Do NOT change!
    enum { BUFSIZE = 8 };
    char buffer[BUFSIZE];

    //if no arguments given or null argument, return 1
    if (argc == 0 || argv[1] == NULL) {
        printf("USAGE: parta FILEIN\n");
        return 1;
    }

    //opens file from args
    int file = open(argv[1], O_RDONLY);

    //if file value less than 0, file doesn't exist, return 2
    if (file < 0) {
        printf("ERROR: %s not found\n", argv[1]);
        return 2;
    }

    //bytes read variable initialization
    int bytesRead = 0;

    //counters for each char type
    int upper = 0, lower = 0, number = 0, space = 0, others = 0;

    //reads by BUFSIZE until end of file
    while ((bytesRead = read(file, buffer, BUFSIZE)) > 0) {
        //iterate over chars in buffer
        for (int i = 0; i < bytesRead; i++) {
            //set c to current char
            char c = buffer[i];

            //add to counters based on char type
            if (isupper(c)) {
                upper++;
            }
            else if (islower(c)) {
                lower++;
            }
            else if (isdigit(c)) {
                number++;
            }
            else if (isspace(c)) {
                space++;
            }
            else {
                others++;
            }
        }
    }

    //print each amount of chars
    printf("Upper,%d\n", upper);
    printf("Lower,%d\n", lower);
    printf("Number,%d\n", number);
    printf("Space,%d\n", space);
    printf("Other,%d\n", others);
    
    //return 0 for success
    return 0;
}
