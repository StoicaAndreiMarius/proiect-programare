#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
int accesare_cont(char *nume){
    char buffer[1024];
    FILE *file = fopen("date_conturi.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }
    while (fgets(buffer, 1024, file)) {
        if (strstr(buffer, nume)) {
            printf("\n%s\n", buffer);
        }
    }
    fclose(file);

    while (1) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 27) { // ESC key
                break;
            }
        }
    }

    return 0;
}