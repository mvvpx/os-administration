#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
typedef struct {
    char id[10];
    int arrival;
    int burst;
    int first_scheduled;
    int completion;
    int turnaround;
    int response;
    int remaining_time;
} Process;

void read() {
    FILE *file = NULL;
    char path[100];
    printf("Enter the file path: ");
    scanf("%s", path);

    file = fopen(path, "r");
    if (file == NULL) {
        printf("File does not exist\n");
        return;
    }

    char buffer[100];
    char *data;
    int i = 0;
    int nbrLigne = 0;
    Process process[100];

    fgets(buffer, sizeof(buffer), file);
    printf("%s\n", buffer);

    while (fgets(buffer, sizeof(buffer), file)) {
        data = strtok(buffer, ",");
        strcpy(process[i].id, data);

        data = strtok(NULL, ",");
        process[i].arrival = atoi(data);

        data = strtok(NULL, ",");
        process[i].burst = atoi(data);

        process[i].first_scheduled = -1;
        process[i].completion = 0;
        process[i].turnaround = 0;
        process[i].response = 0;
        process[i].remaining_time = process[i].burst;
        i++;
    }

    nbrLigne = i;
    printf("ID, Arrival, Burst\n");
    for (int j = 0; j < nbrLigne; j++) {
        printf("%s, %d, %d\n", process[j].id, process[j].arrival, process[j].burst);
    }

    int algo = 0;
    do {
        printf("\nChoose a scheduling algorithm to display:\n1. FIFO\n2. SJF\n3. STCF\n");
        printf("Choice: ");
        scanf("%d", &algo);
    } while (algo != 1 && algo != 2 && algo != 3);

    if (algo == 1) {
        // FIFO Scheduling
        printf("\nProcess ID, Arrival, Burst, First Scheduled, Completion, Turnaround, Response\n");

        process[0].first_scheduled = process[0].arrival;
        process[0].completion = process[0].arrival + process[0].burst;
        process[0].turnaround = process[0].completion - process[0].arrival;
        process[0].response = process[0].first_scheduled - process[0].arrival;
        printf("%s, %d, %d, %d, %d, %d, %d\n", process[0].id, process[0].arrival, process[0].burst, process[0].first_scheduled, process[0].completion, process[0].turnaround, process[0].response);

        for (int i = 1; i < nbrLigne; i++) {
            process[i].first_scheduled = process[i - 1].completion;
            process[i].completion = process[i].first_scheduled + process[i].burst;
            process[i].turnaround = process[i].completion - process[i].arrival;
            process[i].response = process[i].first_scheduled - process[i].arrival;
            printf("%s, %d, %d, %d, %d, %d, %d\n", process[i].id, process[i].arrival, process[i].burst, process[i].first_scheduled, process[i].completion, process[i].turnaround, process[i].response);
        }
    } else if (algo == 2) {
        // SJF (Shortest Job First) Scheduling
        printf("\nProcess ID, Arrival, Burst, First Scheduled, Completion, Turnaround, Response\n");

        // Sort processes by arrival time, then by burst time
        for (int i = 0; i < nbrLigne - 1; i++) {
            for (int j = i + 1; j < nbrLigne; j++) {
                if (process[i].arrival > process[j].arrival ||
                    (process[i].arrival == process[j].arrival && process[i].burst > process[j].burst)) {
                    Process temp = process[i];
                    process[i] = process[j];
                    process[j] = temp;
                }
            }
        }

        int current_time = 0;
        for (int i = 0; i < nbrLigne; i++) {
            if (current_time < process[i].arrival) {
                current_time = process[i].arrival;
            }
            process[i].first_scheduled = current_time;
            process[i].completion = current_time + process[i].burst;
            process[i].turnaround = process[i].completion - process[i].arrival;
            process[i].response = process[i].first_scheduled - process[i].arrival;
            current_time = process[i].completion;
            printf("%s, %d, %d, %d, %d, %d, %d\n", process[i].id, process[i].arrival, process[i].burst, process[i].first_scheduled, process[i].completion, process[i].turnaround, process[i].response);
        }
    } else if (algo == 3) {
        // STCF (Shortest Time to Completion First) Scheduling
        printf("\nProcess ID, Arrival, Burst, First Scheduled, Completion, Turnaround, Response\n");

        int completed = 0;
        int current_time = 0;
        int shortest = 0;
        int finish_time;
        int min_remaining_time = INT_MAX;
        int check = 0;

        while (completed != nbrLigne) {
            for (int j = 0; j < nbrLigne; j++) {
                if (process[j].arrival <= current_time && process[j].remaining_time < min_remaining_time && process[j].remaining_time > 0) {
                    min_remaining_time = process[j].remaining_time;
                    shortest = j;
                    check = 1;
                }
            }

            if (check == 0) {
                current_time++;
                continue;
            }

            if (process[shortest].first_scheduled == -1) {
                process[shortest].first_scheduled = current_time;
            }

            process[shortest].remaining_time--;
            min_remaining_time = process[shortest].remaining_time;
            if (min_remaining_time == 0) {
                min_remaining_time = INT_MAX;
            }

            if (process[shortest].remaining_time == 0) {
                completed++;
                check = 0;
                finish_time = current_time + 1;
                process[shortest].completion = finish_time;
                process[shortest].turnaround = finish_time - process[shortest].arrival;
                process[shortest].response = process[shortest].first_scheduled - process[shortest].arrival;
            }
            current_time++;
        }

        for (int i = 0; i < nbrLigne; i++) {
            printf("%s, %d, %d, %d, %d, %d, %d\n", process[i].id, process[i].arrival, process[i].burst, process[i].first_scheduled, process[i].completion, process[i].turnaround, process[i].response);
        }
    }

    fclose(file);
}

int main(void) {
    read();
    return 0;
}
