#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 5  // Maximum number of jobs in the queue

typedef struct {
    int jobId;
    char jobName[50];
} PrintJob;

PrintJob queue[MAX];
int front = -1, rear = -1;

// Function to check if the queue is empty
int isEmpty() {
    return (front == -1);
}

// Function to check if the queue is full (Circular Queue Condition)
int isFull() {
    return ((rear + 1) % MAX == front);
}

// Function to add a job to the queue
void enqueue(int jobId, char jobName[]) {
    if (isFull()) {
        printf("Queue is full! Cannot add more print jobs.\n");
        return;
    }
    
    if (isEmpty()) {
        front = rear = 0;
    } else {
        rear = (rear + 1) % MAX;
    }
    
    queue[rear].jobId = jobId;
    strcpy(queue[rear].jobName, jobName);
    printf("Print job %d ('%s') added to the queue.\n", jobId, jobName);
}

// Function to process a job from the queue
void dequeue() {
    if (isEmpty()) {
        printf("Queue is empty! No jobs to process.\n");
        return;
    }
    
    printf("Processing print job %d ('%s').\n", queue[front].jobId, queue[front].jobName);
    
    if (front == rear) {
        // Reset queue when last job is processed
        front = rear = -1;
    } else {
        front = (front + 1) % MAX;
    }
}

// Function to display the queue
void displayQueue() {
     int i = front;

    if (isEmpty()) {
        printf("Queue is empty! No pending jobs.\n");
        return;
    }

    printf("Current Print Queue:\n");
    
    do {
        printf("[%d] %s\n", queue[i].jobId, queue[i].jobName);
        i = (i + 1) % MAX;
    } while (i != (rear + 1) % MAX);
}

// Main function
int main() {
    int choice;
    int jobId = 1;  // Start jobId from 1
    char jobName[50];
    clrscr();
    while (1) {
        printf("\n--- Print Queue Menu ---\n");
        printf("1. Add Print Job\n");
        printf("2. Process Print Job\n");
        printf("3. Display Print Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter job name: ");
                getchar();  // Consume newline left in buffer
                fgets(jobName, sizeof(jobName), stdin);
                jobName[strcspn(jobName, "\n")] = 0;  // Remove trailing newline
                enqueue(jobId++, jobName);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                displayQueue();
                break;
            case 4:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}