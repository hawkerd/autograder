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
    char name[MAX_EXE][PATH_MAX];  // Array of string for each program's name
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
 * Writes the full paths and names of all files within a specified directory to the os struct.
 * @param directoryPath The path to the directory whose file paths/names are to be written.
 */

void write_filepath_to_struct(const char *directoryPath) {
    DIR *dir;
    struct dirent *entry;

    // Open the directory
    dir = opendir(directoryPath);
    if (!dir) {
        perror("Failed to open directory");
        exit(EXIT_FAILURE);
    }

    char fullPath[PATH_MAX];

    int i = 0;
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Save submission name and path into struct
        strcpy(os.name[i], entry->d_name);
        snprintf(os.paths[i], sizeof(fullPath), "%s/%s", directoryPath, entry->d_name);

        // Increment
        i++;
    }

    closedir(dir);
}

#endif // UTILITY_H
