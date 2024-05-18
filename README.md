# os-administration

# you fill find in this repositry two projects the first one todo.sh and the second one is p2.C 

######################## P2.C ############################## 

1. Data Storage:
Process Struct: The main data structure used is a struct called Process, which stores all the relevant information about each process:

char id[10]; : Process ID.
int arrival; : Arrival time of the process.
int burst; : Burst time (execution time required).
int first_scheduled; : The first time the process is scheduled.
int completion; : Completion time of the process.
int turnaround; : Turnaround time (completion time - arrival time).
int response; : Response time (first scheduled time - arrival time).
int remaining_time; : Remaining burst time (used for STCF).
Array of Processes: An array of Process structures is used to store all processes read from the file. This allows easy access and manipulation of each process's information.

2. Code Organization:
Header Inclusions: Standard libraries (stdio.h, string.h, stdlib.h, limits.h) are included for file operations, string manipulation, dynamic memory allocation, and defining integer limits.

Function Definitions:

read(): This function handles:
Reading the file path from the user.
Opening and reading the file contents.
Parsing each line to extract process information and storing it in the Process array.
Prompting the user to choose a scheduling algorithm and executing the chosen algorithm.
FIFO Scheduling: Implemented within the read() function, this algorithm processes each task in the order they arrive.
SJF Scheduling: Also implemented within the read() function, this algorithm processes tasks based on the shortest burst time available after arrival.
STCF Scheduling: Implemented within the read() function, this algorithm dynamically selects the process with the shortest remaining time to execute next.
Main Function:

The main() function simply calls the read() function, starting the process of reading input and scheduling processes.





3. how to run the programm :
   gcc -o p2 p2.c
   ./p2

   message will apear : enter the file path : data.csv
   another message will apear : Choose a scheduling algorithm to display:
1. FIFO
2. SJF
3. STCF
Choice: 1
and the result will apear :


################################## todo.sh ##################################





