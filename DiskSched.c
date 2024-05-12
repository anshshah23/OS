#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_REQUESTS 100

void LOOK(int requests[], int n, int head);
void CLOOK(int requests[], int n, int head);
void SSTF(int requests[], int n, int head);
void SCAN(int requests[], int n, int head, bool direction);
void CSCAN(int requests[], int n, int head);
void FCFS(int requests[], int n, int head);
int main() {
    int requests[MAX_REQUESTS];
    int n, head;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    if (n > MAX_REQUESTS) {
        printf("Number of requests exceeds maximum limit.\n");
        return 1;
    }

    printf("Enter the request queue: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the current head position: ");
    scanf("%d", &head);

    LOOK(requests, n, head);
    CLOOK(requests, n, head);
    SSTF(requests, n, head);
    FCFS(requests, n, head);
    SCAN(requests, n, head, true); // true for left direction
    SCAN(requests, n, head, false); // false for right direction
    CSCAN(requests, n, head);

    return 0;
}

void LOOK(int requests[], int n, int head) {
    printf("\nLOOK Algorithm:\n");

    int total_movement = 0;
    int prev_head = head;

    // Traverse right
    for (int i = head; i < MAX_REQUESTS; i++) {
        for (int j = 0; j < n; j++) {
            if (requests[j] == i) {
                printf("Servicing request %d\n", requests[j]);
                total_movement += abs(i - prev_head);
                prev_head = i;
            }
        }
    }

    // Traverse left
    for (int i = head - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            if (requests[j] == i) {
                printf("Servicing request %d\n", requests[j]);
                total_movement += abs(i - prev_head);
                prev_head = i;
            }
        }
    }
    printf("Total head movement: %d\n", total_movement);
}

void CLOOK(int requests[], int n, int head) {
    printf("\nCLOOK Algorithm:\n");

    int total_movement = 0;
    int prev_head = head;

    // Traverse right
    for (int i = head; i < MAX_REQUESTS; i++) {
        for (int j = 0; j < n; j++) {
            if (requests[j] == i) {
                printf("Servicing request %d\n", requests[j]);
                total_movement += abs(i - prev_head);
                prev_head = i;
            }
        }
    }

    // Traverse left from the beginning
    for (int i = 0; i < head; i++) {
        for (int j = 0; j < n; j++) {
            if (requests[j] == i) {
                printf("Servicing request %d\n", requests[j]);
                total_movement += abs(i - prev_head);
                prev_head = i;
            }
        }
    }

    printf("Total head movement: %d\n", total_movement);
}

void SSTF(int requests[], int n, int head) {
    printf("\nSSTF Algorithm:\n");

    int total_movement = 0;
    int serviced_requests[MAX_REQUESTS] = {0};

    for (int i = 0; i < n; i++) {
        int closest_request = -1;
        int min_distance = MAX_REQUESTS;

        for (int j = 0; j < n; j++) {
            if (!serviced_requests[j]) {
                int distance = abs(requests[j] - head);
                if (distance < min_distance) {
                    min_distance = distance;
                    closest_request = j;
                }
            }
        }

        serviced_requests[closest_request] = 1;
        total_movement += min_distance;
        head = requests[closest_request];
        printf("Servicing request %d\n", requests[closest_request]);
    }

    printf("Total head movement: %d\n", total_movement);
}

void FCFS(int requests[], int n, int head) {
    printf("\nFCFS Algorithm:\n");

    int total_movement = 0;
    int prev_head = head;

    // Service requests in the order they appear
    for (int i = 0; i < n; i++) {
        printf("Servicing request %d\n", requests[i]);
        total_movement += abs(requests[i] - prev_head);
        prev_head = requests[i];
    }

    printf("Total head movement: %d\n", total_movement);
}

void SCAN(int requests[], int n, int head, bool direction) {
    printf("\nSCAN Algorithm (");
    if (direction)
        printf("Left):\n");
    else
        printf("Right):\n");

    int total_movement = 0;

    if (direction) {
        // Traverse left
        for (int i = head; i >= 0; i--) {
            for (int j = 0; j < n; j++) {
                if (requests[j] == i) {
                    printf("Servicing request %d\n", requests[j]);
                    total_movement += abs(i - head);
                    head = i;
                }
            }
        }
    } else {
        // Traverse right
        for (int i = head; i < MAX_REQUESTS; i++) {
            for (int j = 0; j < n; j++) {
                if (requests[j] == i) {
                    printf("Servicing request %d\n", requests[j]);
                    total_movement += abs(i - head);
                    head = i;
                }
            }
        }
    }

    printf("Total head movement: %d\n", total_movement);
}

void CSCAN(int requests[], int n, int head) {
    printf("\nCSCAN Algorithm:\n");

    int total_movement = 0;

    // Traverse right
    for (int i = head; i < MAX_REQUESTS; i++) {
        for (int j = 0; j < n; j++) {
            if (requests[j] == i) {
                printf("Servicing request %d\n", requests[j]);
                total_movement += abs(i - head);
                head = i;
            }
        }
    }

    // Traverse from the beginning
    for (int i = 0; i < head; i++) {
        for (int j = 0; j < n; j++) {
            if (requests[j] == i) {
                printf("Servicing request %d\n", requests[j]);
                total_movement += abs(i - head);
                head = i;
            }
        }
    }

    printf("Total head movement: %d\n", total_movement);
}
