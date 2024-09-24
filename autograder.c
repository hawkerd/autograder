#include "include/utility.h"

void print_status(int params, char *argv[]) {
    // Open autograder.out
    FILE* outputFile = fopen("autograder.out", "w");
    if (!outputFile) {
        perror("Failed to open/create output file");
        exit(EXIT_FAILURE);
    }

    // Write output to autograder.out
    for (int i = 0; i < MAX_EXE; i++) {
        // Print executable name, parameter, and result
        fprintf(outputFile, "%s ", os.name[i]);

        for (int p = 0; p < params; p++) {
            fprintf(outputFile, "%s", argv[p + 2]);

            switch (os.status[i][p]) {
                case INCORRECT:
                    fprintf(outputFile, "(incorrect) ");
                    break;
                case CORRECT:
                    fprintf(outputFile, "(correct) ");
                    break;
                case CRASH:
                    fprintf(outputFile, "(crash) ");
                    break;
            }
        }

        fprintf(outputFile, "\n");
    }

    // Close autograder.out
    fclose(outputFile);
}


int main(int argc, char *argv[]) {
    int batch_size; // Batch size
    int params; // Number of inputted parameters
    int done_executables; // Used to track index of completed executables (previous batches)
    int current_executable; // Used to index executables within each batch
    int exit_status; // Used to hold the exit status of executables
    pid_t wait_return_value; // Wait return value


    // If argument count is less than two, output proper program usage
    if (argc < 2) {
        printf("Usage: %s <batch> <p1> <p2> ... <pn>\n", argv[0]);
        return 1;
    }

    // Convert the second command-line argument to an integer to determine the batch size
    batch_size = atoi(argv[1]);

    // If the number of inputted parameters exceed the max, output max number of params
    params = argc - 2;
    if (params > MAX_PI) {
        printf("Maximum number of params: %i\n", MAX_PI);
        return 1;
    }

    // Write the file paths/ names from the "solutions" directory into the struct
    write_filepath_to_struct("solutions");

    //For each parameter, run all executables in batch size chunks
    for (int p = 0; p < params; p++) {
        // Reset done executable count
        done_executables = 0;

        // Variable to hold the process id of executables
        pid_t children[batch_size];

        // Iterate through all executables
        while (done_executables < os.executable_count) {
            // Iterate through the batch
            for (int b = 0; b < batch_size; b++) {
                // Determine current executable based on done executables and index within the batch
                current_executable = done_executables + b;
                if (current_executable >= os.executable_count) {
                    break;
                }

                // Fork
                children[b] = fork();

                if (children[b] == -1) {
                    // Handle error
                    perror("Failed to fork");
                    exit(EXIT_FAILURE); 
                } else if (children[b] == 0) {
                    // Exec the proper executable
                    execl(os.paths[current_executable], os.name[current_executable], argv[p + 2], NULL);

                    // Handle exec() error
                    perror("Failed to exec with error"); //todo: check errno
                    exit(EXIT_FAILURE);
                }
            }

            // Iterate through the batch
            for (int b = 0; b < batch_size; b++) {
                // Determine current executable based on done executables and index within the batch
                current_executable = done_executables + b;
                if (current_executable >= os.executable_count) {
                    break;
                }
            
                // Wait for the proper child process
                wait_return_value = waitpid(children[b], &exit_status, WNOHANG);
                while (wait_return_value == 0) {
                    // Sleep for 0.05s
                    sleep(0.05);

                    // Continuously check to see if the process returned
                    wait_return_value = waitpid(children[b], &exit_status, WNOHANG);
                }
                if (wait_return_value == -1) {
                    // Handle wait error
                    char error[128];
                    sprintf(error, "Wait failed with code %i\n", errno);
                    perror(error);
                    exit(EXIT_FAILURE);
                } else {
                    // Assign exit status of the current executable to os struct
                    if (!(WIFEXITED(exit_status))) {
                        os.status[current_executable][p] = CRASH;
                    } else if (WEXITSTATUS(exit_status) == 0) {
                        os.status[current_executable][p] = CORRECT;
                    } else {
                        os.status[current_executable][p] = INCORRECT;
                    }
                }
            }
            done_executables += batch_size;
        }

    }

    // Write the status of each executable into autograder.out
    print_status(params, argv);    

    return 0;
}     



