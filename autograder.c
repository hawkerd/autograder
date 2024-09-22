#include "include/utility.h"

void print_status(int params) {
    // Open autograder.out
    FILE* outputFile = fopen("autograder.out", "w");
    if (!outputFile) {
        perror("Failed to open/create output file");
        exit(EXIT_FAILURE);
    }

    // Write output to autograder.out
    for (int i = 0; i < MAX_EXE; i++) {
        // Break
        if (!(os.paths[i])) {
            break;
        }

        // Print executable name, parameter, and result
        fprintf(outputFile, "%s ", os.name[i]);

        for (int j = 0; j < params; j++) {
            fprintf(outputFile, "%i", os.pi[i][j]);

            switch (os.status[i][j]) {
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
    // Ensure proper program usage
    if (argc < 2) {
        printf("Usage: %s <batch> <p1> <p2> ... <pn>\n", argv[0]);
        return 1;
    }

    // Convert the first command-line argument to an integer to determine the batch size
    int batch_size = atoi(argv[1]);

    // Ensure proper program usage
    const int params = argc - 2;
    if (params > MAX_PI) {
        printf("Maximum number of params: %i\n", MAX_PI);
        return 1;
    }

    // Initialize struct with contents of argv
    for (int i = 0; i < MAX_EXE; i++) {
        for (int j = 0; j < params; j++) {
            os.pi[i][j] = atoi(argv[j + 2]);
        }
    }

    // Write the file paths/ names from the "solutions" directory into the struct
    write_filepath_to_struct("solutions");

    //TODO: For each parameter, run all executables in batch size chunks
    for (int j = 0; j < params; j++) {
        for (int i = 0; i < MAX_EXE; i++) {
            // Break
            if (!(os.paths[i])) {
                break;
            }

            // Execute the submission
            pid_t pid = fork();
            if (pid == -1) {
                perror("Failed to fork");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                char input[128];
                snprintf(input, sizeof(input), "%d", os.pi[i][j]);
                char* args[] = {os.paths[i], input, NULL};
                if (execve(os.paths[i], args, NULL) == -1) {
                    perror("Failed to exec with error"); //todo: check errno
                    exit(EXIT_FAILURE);
                }
            } else {
                // Variable to hold child exit status
                int exit_status;

                // Wait for the process, and store the result
                waitpid(pid, &exit_status, 0); // todo: use WNOHANG once implementing blocks

                if (!(WIFEXITED(exit_status))) {
                    os.status[i][j] = CRASH;
                } else if (exit_status == 0) {
                    os.status[i][j] = CORRECT;
                } else {
                    os.status[i][j] = INCORRECT;
                }
            }
        }
    }

    // Write the status of each executable into autograder.out
    print_status(params);    

    return 0;
}     
