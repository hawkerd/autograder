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

        for (int p = 0; p < params; p++) {
            fprintf(outputFile, "%i", os.pi[i][p]);

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
        for (int p = 0; p < params; p++) {
            os.pi[i][p] = atoi(argv[p + 2]);
        }
    }

    // Write the file paths/ names from the "solutions" directory into the struct
    write_filepath_to_struct("solutions");


    int done_executables;
    int executable_count;
    //TODO: For each parameter, run all executables in batch size chunks
    for (int p = 0; p < params; p++) {
        //printf("\nNEXT PARAMATER\n");
        done_executables = 0;
        pid_t children[batch_size];
        executable_count = os.executable_count;
        while (done_executables < executable_count) {
            for (int b = 0; b < batch_size; b++) {
                // Determine current executable based on done executables and index within the batch
                int current_executable = done_executables + b;
                if (current_executable >= executable_count) {
                    
                    //printf("breaking out because %i >= %i\n", current_executable, executable_count);
                    //print_struct(4);

                    break;
                }

                // Fork
               // printf("creating child\n");
                children[b] = fork();
                if (children[b] == -1) {
                    perror("Failed to fork");
                    exit(EXIT_FAILURE); 
                } else if (children[b] == 0) {
                    char input[128];
                    // printf("pi to be printed to the file %i\n", os.pi[current_executable][p]);
                    // printf("currentexecutabel: %i\n", current_executable);
                    snprintf(input, sizeof(input), "%i", os.pi[current_executable][p]);
                    char* args[] = {os.paths[current_executable], input, NULL};
                    if (execve(os.paths[current_executable], args, NULL) == -1) {
                        perror("Failed to exec with error"); //todo: check errno
                        exit(EXIT_FAILURE);
                    }
                }
            }

            int finished = 0;
            while (finished < batch_size) {
                for (int b = 0; b < batch_size; b++) {
                    int current_executable = done_executables + b;

                    // Variable to hold child exit status
                    int exit_status;
                    pid_t wait_return_value;

                
                    wait_return_value = waitpid(children[b], &exit_status, WNOHANG) ; // todo: use WNOHANG once implementing blocks
                    while (wait_return_value == 0) {
                        //printf("Child still running, sleeping for 1 mili second\n");
                        sleep(1);
                        wait_return_value = waitpid(children[b], &exit_status, WNOHANG) ; // todo: use WNOHANG once implementing blocks
                    }
                    if(wait_return_value == -1){
                        if (errno == 10){
                            printf("Wait failed. child doesnt exist\n");
                        } else {
                            printf("Wait failed with code%i\n", errno);
                        }
                    }else{
                    
                        if (!(WIFEXITED(exit_status))) {
                            os.status[current_executable][p] = CRASH;
                        } else if (exit_status == 0) {
                            os.status[current_executable][p] = CORRECT;
                        } else {
                            os.status[current_executable][p] = INCORRECT;
                        }
                    }
                    finished = finished + 1;
                }
            }
            done_executables += batch_size;
        }

    }
    //print_struct(4);
    // Write the status of each executable into autograder.out
    print_status(params);    

    return 0;
}     



