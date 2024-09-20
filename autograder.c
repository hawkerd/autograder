#include "include/utility.h"
//TEST FOR CORRECT BRANCH
void print_status(){

     //TODO: write the status of each executable file to autograder.out. Your output should align with expected.out 
}


int main(int argc, char *argv[]) {


    if (argc < 2) {
        printf("Usage: %s <batch> <p1> <p2> ... <pn>\n", argv[0]);
        return 1;
    }

    // Convert the first command-line argument to an integer to determine the batch size
    int batch_size = atoi(argv[1]);


    // write the file paths from the "solutions" directory into the submissions.txt file
    write_filepath_to_submissions("solutions", "submissions.txt");


    //TODO: read the executable filename from submissions.txt


    //TODO: For each parameter, run all executables in batch size chunks

    
    //TODO: Write the status of each executable file from "submissions.txt" to autograder.out. For testing purposes, you can compare the results with the provided expected.out file
    print_status();    


    return 0;
}     
