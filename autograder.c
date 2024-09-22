#include "include/utility.h"

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

    /* Read executable filenames and execute them */

    // Open submissions.txt
    FILE* submissionsFile = fopen("submissions.txt", "r");
    if (!submissionsFile) {
        perror("Failed to open submissions file");
        exit(EXIT_FAILURE);
    }

    FILE* outputFile = fopen("autograder.out", "w");
    if (!outputFile) {
        perror("Failed to open/create output file");
        exit(EXIT_FAILURE);
    }
    
    // Variable to store executable filename
    char submission[128];

    // Loop through submissions
    while (fgets(submission, sizeof(submission), submissionsFile)) {
        // Remove newline character
        char* nl = strchr(submission, '\n');
        if (nl) {
            *nl = '\0';
        }

        // Variable to hold exit status
        int exit_status;

        // Execute the submission
        pid_t pid = fork();
        if (pid == -1) {
            perror("Failed to fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            char param = '1';
            char* args[] = {submission, &param, NULL};
            if (execve(submission, args, NULL) == -1) {
                perror("Failed to exec with error"); //todo: check errno
                exit(EXIT_FAILURE);
            }
        } else {
            waitpid(pid, &exit_status, 0);
        }
    }

    // Close submissions.txt;
    fclose(submissionsFile);

    //TODO: For each parameter, run all executables in batch size chunks

    
    //TODO: Write the status of each executable file from "submissions.txt" to autograder.out. For testing purposes, you can compare the results with the provided expected.out file
    print_status();    


    return 0;
}     
