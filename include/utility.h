#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <limits.h> // For PATH_MAX
#include <errno.h>

// Define the maximum number of executable files and the maximum number of pi.

#define MAX_EXE 20
#define MAX_PI 4 



// Structure to store information for each executable file: path, status, and pi.
typedef struct {
    char paths[MAX_EXE][PATH_MAX]; // Array of strings for each program's path
    int status[MAX_EXE][MAX_PI];   // For each program, an array of status codes
    int pi[MAX_EXE][MAX_PI];       // Array of 'pi' values, assuming one 'pi' per program for simplicity
} out_status;

out_status os;


// Define an enum for the program execution outcomes
enum {
    CORRECT = 1,     // Corresponds to case 1: Exit with status 0 (correct answer)
    INCORRECT = 2,       // Corresponds to case 2: Exit with status 1 (incorrect answer)
    CRASH = 3,           // Corresponds to case 3: Triggering a crash
};


/**
 * Writes the full paths of all files within a specified directory to a given output file.
 * This function opens the specified directory, iterates over each entry excluding special
 * entries "." and "..", constructs the full path for each file, and writes these paths to
 * the specified output file.
 * @param directoryPath The path to the directory whose file paths are to be written.
 * @param outputFileName The path to the file where the full paths will be saved.
 * @Hint: This function can create submissions.txt if you wish to use it
 */

void write_filepath_to_submissions(const char *directoryPath, const char *outputFileName) {
    DIR *dir;
    struct dirent *entry;
    FILE *file;

    // Open the directory
    dir = opendir(directoryPath);
    if (!dir) {
        perror("Failed to open directory");
        exit(EXIT_FAILURE);
    }

    // Open or create the output file
    file = fopen(outputFileName, "w");
    if (!file) {
        perror("Failed to open output file");
        closedir(dir);
        exit(EXIT_FAILURE);
    }

    char fullPath[PATH_MAX];
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct the full path
        snprintf(fullPath, sizeof(fullPath), "%s/%s", directoryPath, entry->d_name);

        // Write the full path to the file
        fprintf(file, "%s\n", fullPath);
    }

    fclose(file);
    closedir(dir);
}

#endif // UTILITY_H
