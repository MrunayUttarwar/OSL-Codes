#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void execute_cp(char *src, char *dest) {
    pid_t pid = fork(); // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("child is executing");
        execlp("./copy", "copy", src, dest, NULL); // Execute the 'cp' command
        exit(1);
    } else {
        // Parent process
        wait(NULL); // Wait for the child process to finish
        printf("File copied from %s to %s\n", src, dest);
    }
}

void execute_grep(char *pattern, char *file) {
    pid_t pid = fork(); // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process
        execlp("./grep_simulation", "grep_simulation", pattern, file, NULL); // Execute the 'grep' command
        perror("exec failed"); // This runs only if exec fails
        exit(1);
    } else {
        // Parent process
        wait(NULL); // Wait for the child process to finish
        printf("Search completed for pattern '%s' in file %s\n", pattern, file);
    }
}

int main() {
    int choice;
    char src[100], dest[100], pattern[100], file[100];

    while (1) {
        printf("\n--- Linux Command Simulation ---\n");
        printf("1. cp (Copy file)\n");
        printf("2. grep (Search for a pattern in a file)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter source file: ");
                scanf("%s", src);
                printf("Enter destination file: ");
                scanf("%s", dest);
                execute_cp(src, dest);
                break;

            case 2:
                printf("Enter pattern to search: ");
                scanf("%s", pattern);
                printf("Enter file to search in: ");
                scanf("%s", file);
                execute_grep(pattern, file);
                break;

            case 3:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

