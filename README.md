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

Data Storage
File-Based Storage: The program uses a plain text file, tasks.txt, to store task data. Each task is stored on a new line in the file with fields separated by a consistent delimiter (spaces in this case). This choice makes the program simple and portable, as it does not rely on external databases.
Fields: Each task entry in the file includes:
ID: A unique identifier for each task.
Title: The name of the task.
Description: A detailed description of the task.
Location: Where the task needs to be performed.
Due Date: When the task is due, in YYYY-MM-DD format.
Completion Status: Whether the task is completed or not, stored as "terminée" or "non terminée".
Code Organization
Modular Functions: Each primary operation (create, update, delete, view task information, list tasks, and search tasks) is encapsulated in its own function. This modular approach improves readability and maintainability.
Main Execution Flow: The main part of the script uses a case statement to determine which function to execute based on the command-line argument provided. This design allows the script to handle various user commands efficiently.
Input Validation: The script includes input validation for critical fields like the task title and due date to ensure data integrity.
User Interaction: Prompts and messages to the user are in French, making the script suitable for French-speaking users.
How to Run the Program
Prerequisites
Bash Shell: Ensure you are using a Unix-like system with a Bash shell available.
Permissions: Make sure the script has executable permissions. You can set this with the following command:
sh
Copy code
chmod +x todo.sh
Usage
Help: Display usage information.

sh
Copy code
./todo.sh --help
Create a Task: Start the process to create a new task.

sh
Copy code
./todo.sh create
Update a Task: Update details of an existing task by its ID.

sh
Copy code
./todo.sh update
Delete a Task: Delete a task by its ID.

sh
Copy code
./todo.sh delete
View Task Information: View the details of a specific task by its ID.

sh
Copy code
./todo.sh info
List Tasks for a Given Day: List tasks for a specific date, showing completed and non-completed tasks.

sh
Copy code
./todo.sh list
Search Task by Title: Search for tasks by their title.

sh
Copy code
./todo.sh search
Example Workflow
Create a Task:

Run ./todo.sh create.
Follow the prompts to enter the task details.
List Today's Tasks:

Simply run ./todo.sh without any arguments to list tasks for the current date.
Update a Task:

Run ./todo.sh update.
Enter the task ID and the field you want to update along with the new value.
Delete a Task:

Run ./todo.sh delete.
Enter the task ID to delete the task.
View Task Information:

Run ./todo.sh info.
Enter the task ID to view its details.
Search for a Task by Title:

Run ./todo.sh search.
Enter the title of the task to find matching tasks.
