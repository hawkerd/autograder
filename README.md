# Autograder
This project implements a basic autograder that automates the testing of multiple student submissions, each representing the solution to a problem. Each executable will either pass, fail, or crash for any given integer parameter. The autograder will compile these results into autograder.out. The autograder can run executables in batches of any size, allowing for flexibility and the ability to run it more efficiently on different systems. The purpose of the project was to understand the syntax and use of different system calls relating to UNIX file i/o and processes, like the fork/ exec/ wait sequence.

<br/>
## Compilation and Execution
To compile, run the provided makefile. Then, run the executable with batch size and program parameters, which will be passed onto each "submission".
```
	$ make
	$ ./autograder <batch size>, <p1>, <p2>, ... <pn>
```

<br/>
## Assumptions
- Assumes that the submissions are located in the solutions directory.
- Assumes that all provided submissions will exit and return with a valid exit status, or crash.

<br/>
## Contributions
This project was completed for **CSCI 4061 - Introduction to Operating Systems** at the University of Minnesota by the following contributors, from **Group 5**.

**Luke Lopata (lopat018)**:
- Implemented batching functionality for executables, allowing them to run in parallel
- Created the wait logic for handling child processes.
- Assisted in debugging the final project for accuracy.
<br/>

**Dan Hawker (hawke069)**:
- Developed the loop to run all executables sequentially with proper parameter inputs.
- Implemented non-batched functionality for executables, so that they run in sequence.
- Co-developed the output function to summarize the results of all executables.
- Error checked all system calls, ensuring that our program is safe.
- Assisted in debugging the final project for accuracy.
<br/>

**Samuel Thorson (thors648)**:
- Implemented non-batched functionality for up to 4 parameters.
- Co-developed the output function to summarize the results of all executables.
- Wrote the project README to summarize contributions and function.
- Assisted in debugging the final project for accuracy.