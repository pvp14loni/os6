#include <stdio.h>

#define MAX_FRAMES 3
#define MAX_PAGES 20

// Function to find the index of the page with the highest frequency
int getMFU(int frames[], int freq[], int f) {
    int maxFreq = -1;
    int index = -1;
    for (int i = 0; i < f; i++) {
        if (freq[i] > maxFreq) {
            maxFreq = freq[i];
            index = i;
        }
    }
    return index;
}

int main() {
    int pages[MAX_PAGES], frames[MAX_FRAMES];
    int pageFaults = 0, n, f, freq[MAX_FRAMES] = {0};

    // Take input for the reference string (pages)
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Take input for the number of frames
    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initialize frames to -1 (indicating empty frames)
    for (int i = 0; i < f; i++) {
        frames[i] = -1;
    }

    // Start page replacement algorithm
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in one of the frames
        for (int j = 0; j < f; j++) {
            if (frames[j] == page) {
                found = 1;
                freq[j]++;  // Increment frequency if page is found
                break;
            }
        }

        // If the page was not found, it's a page fault
        if (!found) {
            pageFaults++;

            // If there is space in the frames, add the page
            int emptyFrame = -1;
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    emptyFrame = j;
                    break;
                }
            }

            if (emptyFrame != -1) {
                frames[emptyFrame] = page;
                freq[emptyFrame] = 1;  // Initial frequency for new page
            } else {
                // Replace the most frequently used page
                int index = getMFU(frames, freq, f);
                frames[index] = page;
                freq[index] = 1;  // Reset frequency for replaced page
            }
        }

        // Print the current state of frames
        printf("After accessing page %d: ", page);
        for (int j = 0; j < f; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            }
        }
        printf("\n");
    }

    // Output the total page faults
    printf("Total page faults: %d\n", pageFaults);

    return 0;
}
