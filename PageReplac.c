#include <stdio.h>
#include <stdbool.h>

#define MAX_PAGES 100

// FIFO Page Replacement Algorithm
void FIFO(int pages[], int n, int capacity) {
    int pageFaults = 0;
    int rear = -1;
    int memory[capacity];

    for (int i = 0; i < n; i++) {
        int currentPage = pages[i];
        bool pageHit = false;

        for (int j = 0; j < capacity; j++) {
            if (memory[j] == currentPage) {
                pageHit = true;
                break;
            }
        }

        if (!pageHit) {
            ++pageFaults;
            ++rear;
            rear %= capacity;
            memory[rear] = currentPage;
        }
    }

    printf("FIFO Page Faults: %d\n", pageFaults);
}

// Function to find the index of the page to be replaced (for LRU)
int findPageToReplaceLRU(int memory[], int capacity) {
    int minIndex = 0;
    int minCounter = memory[0];
    for (int i = 1; i < capacity; ++i) {
        if (memory[i] < minCounter) {
            minIndex = i;
            minCounter = memory[i];
        }
    }
    return minIndex;
}

// LRU Page Replacement Algorithm
void LRU(int pages[], int n, int capacity) {
    int pageFaults = 0;
    int memory[capacity];
    int counter = 0;
  
    for (int i = 0; i < n; ++i) {
        int currentPage = pages[i];
        bool pageHit = false;

        for (int j = 0; j < capacity; ++j) {
            if (memory[j] == currentPage) {
                pageHit = true;
                break;
            }
        }

        if (!pageHit) {
            ++pageFaults;
            if (counter < capacity) {
                memory[counter] = currentPage;
                ++counter;
            } else {
                int index = findPageToReplaceLRU(memory, capacity);
                memory[index] = currentPage;
            }
        }
    }
    printf("LRU Page Faults: %d\n", pageFaults);
}

// Optimal Page Replacement Algorithm
void Optimal(int pages[], int n, int capacity) {
    int pageFaults = 0;
    int memory[capacity];

    for (int i = 0; i < capacity; ++i) {
        memory[i] = -1;
    }

    for (int i = 0; i < n; ++i) {
        int currentPage = pages[i];
        bool pageHit = false;

        for (int j = 0; j < capacity; ++j) {
            if (memory[j] == currentPage) {
                pageHit = true;
                break;
            }
        }

        if (!pageHit) {
            ++pageFaults;
            int index = findPageToReplaceOptimal(pages, n, memory, capacity, i);
            memory[index] = currentPage;
        }
    }

    printf("Optimal Page Faults: %d\n", pageFaults);
}

// LFU Page Replacement Algorithm
void LFU(int pages[], int n, int capacity) {
    int pageFaults = 0;
    int memory[capacity];
    int freq[capacity];

    for (int i = 0; i < capacity; ++i) {
        memory[i] = -1;
        freq[i] = 0;
    }

    for (int i = 0; i < n; ++i) 
    {
        int currentPage = pages[i];
        bool pageHit = false;

        for (int j = 0; j < capacity; ++j) {
            if (memory[j] == currentPage) {
                pageHit = true;
                ++freq[j];
                break;
            }
        }

        if (!pageHit) {
            ++pageFaults;
            int minFreqIndex = 0;
            for (int j = 1; j < capacity; ++j) {
                if (freq[j] < freq[minFreqIndex]) {
                    minFreqIndex = j;
                }
            }
            memory[minFreqIndex] = currentPage;
            freq[minFreqIndex] = 1;
        }
    }

    printf("LFU Page Faults: %d\n", pageFaults);
}

// Function to find the index of the page to be replaced (for Optimal)
int findPageToReplaceOptimal(int pages[], int n, int memory[], int capacity, int currentIndex) {
    int farthest = currentIndex;
    int index = -1;

    for (int i = 0; i < capacity; ++i) {
        int j;
        for (j = currentIndex + 1; j < n; ++j) {
            if (memory[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        if (j == n) {
            return i;
        }
    }

    if (index == -1) {
        return 0;
    }

    return index;
}

int main() {
    int pages[] = {2, 3, 2, 1, 5, 2, 4, 5, 3, 2, 5};
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = 3;

    FIFO(pages, n, capacity);
    LRU(pages, n, capacity);
    Optimal(pages, n, capacity);
    LFU(pages, n, capacity);

    return 0;
}
