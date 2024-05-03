#include <stdio.h>
#include <stdlib.h>

void fifo(int *pages, int numberOfPages, int frames);
void lru(int *pages, int numberOfPages, int frames);
void optimal(int *pages, int numberOfPages, int frames);
int inFrame(int page, int *frame, int frames);
int findOptimalIndex(int *pages, int *frame, int start, int numberOfPages, int frames);
int maxIndex(int *map, int frames);
void printFrames(int *frame, int frames);

int main() {
    int choice;
    while (1) {
        printf("Choose the Page Replacement Algorithm:\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. Optimal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        
        scanf("%d", &choice);

        if (choice == 4) {
            printf("Exiting...\n");
            break;
        }

        int frames, numberOfPages;
        printf("Enter number of frames: ");
        scanf("%d", &frames);

        printf("Enter the number of pages: ");
        scanf("%d", &numberOfPages);

        int *pages = (int*)malloc(numberOfPages * sizeof(int));
        printf("Enter the page reference string:\n");
        for (int i = 0; i < numberOfPages; i++) {
            scanf("%d", &pages[i]);
        }

        switch (choice) {
            case 1:
                fifo(pages, numberOfPages, frames);
                break;
            case 2:
                lru(pages, numberOfPages, frames);
                break;
            case 3:
                optimal(pages, numberOfPages, frames);
                break;
            default:
                printf("Invalid choice. Please select again.\n");
        }
        free(pages);
    }
    return 0;
}

void fifo(int *pages, int numberOfPages, int frames) {
    int pageFaults = 0;
    int *frame = (int*)malloc(frames * sizeof(int));
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
    }
    int j = 0;
    printf("Page Reference\tFrames\n");
    for (int i = 0; i < numberOfPages; i++) {
        int page = pages[i];
        int flag = 1;
        for (int k = 0; k < frames; k++) {
            if (frame[k] == page) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            frame[j] = page;
            j = (j + 1) % frames;
            pageFaults++;
            printFrames(frame, frames);
        }
    }
    printf("Total Page Faults: %d\n", pageFaults);
    free(frame);
}

void lru(int *pages, int numberOfPages, int frames) {
    int pageFaults = 0;
    int *frame = (int*)malloc(frames * sizeof(int));
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
    }
    printf("Page Reference\tFrames\n");
    int *stack = (int*)malloc(frames * sizeof(int));
    int stackSize = 0;
    for (int i = 0; i < numberOfPages; i++) {
        int page = pages[i];
        int flag = 1;
        for (int j = 0; j < stackSize; j++) {
            if (stack[j] == page) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            if (stackSize < frames) {
                stack[stackSize++] = page;
            } else {
                int leastRecentlyUsed = stack[0];
                int index = 0;
                for (int k = 0; k < frames; k++) {
                    if (frame[k] == leastRecentlyUsed) {
                        index = k;
                        break;
                    }
                }
                stack[0] = page;
                frame[index] = page;
            }
            pageFaults++;
        } else {
            for (int j = 0; j < stackSize; j++) {
                if (stack[j] == page) {
                    for (int k = j; k < stackSize - 1; k++) {
                        stack[k] = stack[k + 1];
                    }
                    stack[stackSize - 1] = page;
                    break;
                }
            }
        }
        for (int j = 0; j < stackSize; j++) {
            frame[j] = stack[j];
        }
        printFrames(frame, frames);
    }
    printf("Total Page Faults: %d\n", pageFaults);
    free(frame);
    free(stack);
}

void optimal(int *pages, int numberOfPages, int frames) {
    int pageFaults = 0;
    int *frame = (int*)malloc(frames * sizeof(int));
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
    }
    printf("Page Reference\tFrames\n");
    for (int i = 0; i < numberOfPages; i++) {
        int page = pages[i];
        int flag = inFrame(page, frame, frames);
        if (!flag) {
            int index = (i == numberOfPages - 1) ? 0 : findOptimalIndex(pages, frame, i + 1, numberOfPages, frames);
            frame[index] = page;
            pageFaults++;
            printFrames(frame, frames);
        }
    }
    printf("Total Page Faults: %d\n", pageFaults);
    free(frame);
}

int inFrame(int page, int *frame, int frames) {
    for (int i = 0; i < frames; i++) {
        if (frame[i] == page) {
            return 1;
        }
    }
    return 0;
}

int findOptimalIndex(int *pages, int *frame, int start, int numberOfPages, int frames) {
    int index = -1;
    int farthest = start;
    for (int i = 0; i < frames; i++) {
        int found = 0;
        for (int j = start; j < numberOfPages; j++) {
            if (frame[i] == pages[j]) {
                found = 1;
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        if (!found) {
            return i;
        }
    }
    return (index == -1) ? 0 : index;
}


int maxIndex(int *map, int frames) {
    int maxIndex = 0;
    for (int i = 1; i < frames; i++) {
        if (map[i] > map[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

void printFrames(int *frame, int frames) {
    for (int i = 0; i < frames; i++) {
        if (frame[i] != -1) {
            printf("%d\t", frame[i]);
        } else {
            printf("-\t");
        }
    }
    printf("\n");
}
