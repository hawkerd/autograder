#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <mode>\n", argv[0]);
        return 1;
    }

    unsigned int seed = 0;

    for (int i = 0; argv[0][i] != '\0'; i++) {
        seed += (unsigned char)argv[0][i]; 
    }
    
    unsigned int pi = atoi(argv[1]);    
    seed += pi;
    srandom(seed);
  
    int mode = random() % 3 + 1;
    pid_t pid = getpid(); // Get the current process ID

    sleep(1); 

    switch (mode) {
        case 1:
            
            // Simulate a computation for the correct answer
            int correct_result = 0;
            for (int i = 0; i < 100000; i++) {
                correct_result += i;  // Example computation
            }

            printf("Program: %s, PID: %d, Mode: 1 - Exiting with status 0 (Correct answer)\n", argv[0], pid);
            return 0;  // Exit with status 0 (correct answer)
        case 2:
             
            // Simulate a computation for the incorrect answer 
            int incorrect_result = 1;
            for (int i = 1; i <= 100000; i++) {
                incorrect_result *= i;
            }

            printf("Program: %s, PID: %d, Mode: 2 - Exiting with status 1 (Incorrect answer)\n", argv[0], pid);
            return 1;  // Exit with status 1 (incorrect answer)
        case 3:
            
            // Simulate computation before triggering a crash
            int segfault_result = 42;
            for (int i = 0; i < 50000; i++) {
                 segfault_result /= (i + 1);
            }

            printf("Program: %s, PID: %d, Mode: 3 - Triggering a segmentation fault\n", argv[0], pid);
            raise(SIGSEGV);  // Trigger a segmentation fault
            break;
        default:
            break;
    }

    return 0;
}
