#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int exista_cont(char *nume){
    char buffer[1024]; // Buffer to hold each line from the file
    FILE *file = fopen("conturi.txt", "r"); // Open the file for reading

    if (file == NULL) {
        perror("Error opening file");
        return -1; // Return -1 to indicate file opening error
    }

    while (fgets(buffer, 1024, file)) { // Read lines into buffer
        if (strstr(buffer, nume)) { // Check if search_string is in line
            fclose(file); // Close the file
            return 1; // Return 1 if string is found
        }
    }
    fclose(file); // Close the file
    return 0; // Return 0 if string is not found
}

int parola_corecta(char *nume, char *parola){
    char buffer[1024]; // Buffer to hold each line from the file
    FILE *file = fopen("conturi.txt", "r"); // Open the file for reading

    if (file == NULL) {
        perror("Error opening file");
        return -1; // Return -1 to indicate file opening error
    }

    while (fgets(buffer, 1024, file)) { // Read lines into buffer
        if (strstr(buffer, nume) && strstr(buffer, parola)) { // Check if search_string is in line
            fclose(file); // Close the file
            return 1; // Return 1 if string is found
        }
    }
    fclose(file); // Close the file
    return 0; // Return 0 if string is not found
}


void parse_csv(const char *file_path) {
    const int BUFFER_SIZE = 1024; // Adjust based on expected line length
    char buffer[BUFFER_SIZE];

    // Open the CSV file for reading
    FILE *file = fopen(file_path, "r");
    if (!file) {
        perror("Unable to open file");
        return;
    }

    // Read each line from the file
    while (fgets(buffer, BUFFER_SIZE, file)) {
        // Remove newline character at the end of the line
        buffer[strcspn(buffer, "\n")] = 0;

        // Use strtok to split the line by commas
        char *token = strtok(buffer, ",");
        while (token) {
            printf("%s ", token); // Print each field (or handle accordingly)
            token = strtok(NULL, ",");
        }
    }

    // Close the file
    fclose(file);
}
