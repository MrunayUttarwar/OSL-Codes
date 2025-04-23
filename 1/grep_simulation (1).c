#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int containsSubstring(const char *line, const char *pattern) {
    return strstr(line, pattern) != NULL;
}

int main(int argc, char *argv[]) {
 
    if (argc != 3) {
        printf("Usage: %s <pattern> <filename>\n", argv[0]);
        return 1;
    }

    const char *pattern = argv[1];  
    const char *filename = argv[2]; 

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int lineNumber = 0;

    printf("Searching for '%s' in %s:\n\n", pattern, filename);

    while (fgets(line, sizeof(line), file) != NULL) {
        lineNumber++;
        if (containsSubstring(line, pattern)) {
            printf("Line %d: %s", lineNumber, line);
        }
    }

    fclose(file);
    return 0;
}
