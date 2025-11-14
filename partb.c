#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

/**
 * @brief Prints character counts from input file to output file
 * 
 * @param argc Number of args provided
 * @param argv Args 1 = input, 2 = output
 * @return int 0 if success, 1 if incorrect params, 2 if input doesn't exist, 3 if dup2 error
 */
int main(int argc, char* argv[]) {

    //if insufficient arguments given or null argument, return 1
    if (argc < 3) {
        printf("USAGE: partb FILEIN FILEOUT\n");
        return 1;
    }

    //define input and ouput froma args
    char *input = argv[1];
    char *output = argv[2];

    int fd = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0770);

    //print error and return if file not found
    if(fd < 0) {
        printf("ERROR: %s not found\n", output);
        return 2;
    }

    //redirect ouput to output file, return error if fails
    if (dup2(fd, STDOUT_FILENO) < 0) {
        printf("Dup2 ERROR\n");
        return 3;
    }

    //write header 'Category,Count' to output file
    write(STDOUT_FILENO, "Category,Count\n", 15);

    //close output file
    close(fd);

    //run parta and end program if success
    execl("./parta", "./parta", input, NULL);
    
    //print error if this line is reached
    printf("Exec error\n");

    //default case return 0 
    return 0;
}
