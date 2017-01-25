// Sample code to read in test cases:
#include <stdio.h>

#define BUFFER_SIZE 1024
#define CASE_OFFSET 32

int main(int argc, const char * argv[]) {
    FILE *file = fopen(argv[1], "r");
    char line[BUFFER_SIZE];
    while (fgets(line, BUFFER_SIZE, file)) {
        char *current_char = line;
        do {
            if (*current_char >= 'a' && *current_char <= 'z') {
                (*current_char) -= CASE_OFFSET;
            }
            else if (*current_char >= 'A' && *current_char <= 'Z') {
                (*current_char) += CASE_OFFSET;
            }
        } while (*(++current_char) != NULL);
        printf("%s\n", line);
    }
    return 0;
}
