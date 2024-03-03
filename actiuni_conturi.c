#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int accesare_cont(char *nume){
    char buffer[1024]; // Buffer to hold each line from the file
    FILE *file = fopen("date_conturi.txt", "r"); // Open the file for reading

    if (file == NULL) {
        perror("Error opening file");
        return -1; // Return -1 to indicate file opening error
    }
    while (fgets(buffer, 1024, file)) { // Read lines into buffer
        if (strstr(buffer, nume)) { // Check if search_string is in line
            printf("%s\n", buffer);
        }
    }
    fclose(file); // Close the file
    return 0;
}