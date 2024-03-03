#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cont_bancar{
    char *id;
    char nume[100];
    char parola[100];
    char *nr_conturi;
};

struct cont_valuta{
    char *id;
    char nume[100];
    char valuta[5];
    char *numerar;
};

void parse_clienti(struct cont_bancar rows[], int i){
    char buffer[1024];
    FILE *file = fopen("conturi.txt", "r");
    if (!file) {
        perror("Unable to open file");
        return;
    }
    i = 0;
    while(fgets(buffer, 1024, file)) {
        strcpy(rows[i].id, strtok(buffer, ","));
        strcpy(rows[i].nume, strtok(buffer, ","));
        strcpy(rows[i].parola, strtok(buffer, ","));
        strcpy(rows[i].nr_conturi, strtok(buffer, ","));
        i++;
    }
}

void parse_conturi_clienti(struct cont_valuta rows[], int i){
    char buffer[1024];
    FILE *file = fopen("date_conturi.txt", "r");
    if (!file) {
        perror("Unable to open file");
        return;
    }
    i = 0;
    while(fgets(buffer, 1024, file)) {
        strcpy(rows[i].id, strtok(buffer, ","));
        strcpy(rows[i].nume, strtok(buffer, ","));
        strcpy(rows[i].valuta, strtok(buffer, ","));
        strcpy(rows[i].numerar, strtok(buffer, ","));
        i++;
    }
}

int exista_cont(char *nume){
    char buffer[1024];
    FILE *file = fopen("conturi.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    while (fgets(buffer, 1024, file)) {
        if (strstr(buffer, nume)) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int parola_corecta(char *nume, char *parola){
    char buffer[1024];
    FILE *file = fopen("conturi.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    while (fgets(buffer, 1024, file)) {
        if (strstr(buffer, nume) && strstr(buffer, parola)) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}


void adaugare_cont(char *nume, char *parola){
    char buffer[1024];
    FILE *file = fopen("conturi.txt", "r");
    int i = 1;
    while(fgets(buffer, 1024, file)){
        i++;
    }
    fclose(file);
    FILE *file_w = fopen("conturi.txt", "a");
    sprintf(buffer, "%d,%s,%s,%d", i, nume, parola, 1);
    fprintf(file_w, "%s", "\n");
    fprintf(file_w, "%s", buffer);
    fclose(file_w);
    FILE *date_cont = fopen("date_conturi.txt", "a");

    printf("Cont adaugat cu succes!");
}

void parse_csv(const char *file_path) {
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];

    FILE *file = fopen(file_path, "r");
    if (!file) {
        perror("Unable to open file");
        return;
    }

    while (fgets(buffer, BUFFER_SIZE, file)) {
        buffer[strcspn(buffer, "\n")] = 0;

        char *token = strtok(buffer, ",");
        while (token) {
            printf("%s ", token);
            token = strtok(NULL, ",");
        }
    }

    fclose(file);
}
