#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

void printFrames(int frame[], int frames) {
    for (int i = 0; i < frames; i++) {
        if (frame[i] == -1)
            printf(" - ");
        else
            printf(" %d ", frame[i]);
    }
    printf("\n");
}

void fcfs(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], index = 0, pageFaults = 0;

    for (int i = 0; i < frames; i++)
        frame[i] = -1;

    printf("\nFCFS Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        printf("Page %d -> ", pages[i]);
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            frame[index] = pages[i];
            index = (index + 1) % frames;
            pageFaults++;
        }
        printFrames(frame, frames);
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

void lru(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], recent[MAX_FRAMES], pageFaults = 0;

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
        recent[i] = -1;
    }

    printf("\nLRU Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        printf("Page %d -> ", pages[i]);
        int found = 0;

        // Check if page is already in frame
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                recent[j] = i; // Update recent access index
                break;
            }
        }

        // If not found, replace LRU page
        if (!found) {
            int minIndex = 0;
            for (int j = 1; j < frames; j++) {
                if (recent[j] < recent[minIndex])
                    minIndex = j;
            }
            frame[minIndex] = pages[i];
            recent[minIndex] = i; // Store latest access
            pageFaults++;
        }
        printFrames(frame, frames);
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

void optimal(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], pageFaults = 0;

    for (int i = 0; i < frames; i++)
        frame[i] = -1;

    printf("\nOptimal Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        printf("Page %d -> ", pages[i]);
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            int replaceIndex = -1, farthest = i + 1;
            for (int j = 0; j < frames; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (frame[j] == pages[k])
                        break;
                }
                if (k == n) {
                    replaceIndex = j;
                    break;
                }
                if (k > farthest) {
                    farthest = k;
                    replaceIndex = j;
                }
            }
            frame[replaceIndex == -1 ? 0 : replaceIndex] = pages[i];
            pageFaults++;
        }
        printFrames(frame, frames);
    }
    printf("Total Page Faults: %d\n", pageFaults);
}

int main() {
    int n, frames, choice;
    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[MAX_PAGES];
    printf("Enter page reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("\nChoose a Page Replacement Algorithm:\n");
    printf("1. FCFS\n2. LRU\n3. Optimal\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            fcfs(pages, n, frames);
            break;
        case 2:
            lru(pages, n, frames);
            break;
        case 3:
            optimal(pages, n, frames);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}