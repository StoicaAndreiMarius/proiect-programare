#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

#define MAX_NAME 50
#define MAX_CURRENCY 4
#define MAX_LINE 100

// Definirea structurii pentru cont
typedef struct Cont {
    char nume[MAX_NAME];
    char valuta[MAX_CURRENCY];
    int suma;
    struct Cont *urmatorul; // pointer pentru urmatorul cont in lista
} Cont;

// Prototipuri de functii
Cont *incarca_conturi(FILE *fisier);
void adauga_sau_actualizeaza_cont(Cont **cap_lista,const char *nume,const char *valuta, int suma_adaugata);
void actualizeaza_cont_retragere(Cont **cap_lista,const char *nume,const char *valuta, int suma_adaugata);
void scrie_conturi_in_fisier(FILE *fisier, Cont *cap_lista);
void elibereaza_memoria_conturilor(Cont *cap_lista);
void adaugare_bani(const char *nume, const char *valuta, int suma_adaugata);
void retragere_bani(const char *nume, const char *valuta, int suma);

Cont *incarca_conturi(FILE *fisier) {
    Cont *cap_lista = NULL, *ultimul = NULL;

    char linie[MAX_LINE];
    while (fgets(linie, MAX_LINE, fisier)) {
        Cont *nou_cont = (Cont *)malloc(sizeof(Cont));
        if (nou_cont == NULL) {
            elibereaza_memoria_conturilor(cap_lista);
            exit(EXIT_FAILURE);
        }

        sscanf(linie, "%49[^,], %3[^,], %f", nou_cont->nume, nou_cont->valuta, &nou_cont->suma);
        nou_cont->urmatorul = NULL;

        if (cap_lista == NULL) {
            cap_lista = nou_cont; // Lista este goala, deci acesta este primul nod
        } else {
            ultimul->urmatorul = nou_cont; // Adauga la sfarsitul listei
        }
        ultimul = nou_cont; // Actualizeaza ultimul element
    }

    return cap_lista;
}

void adauga_sau_actualizeaza_cont(Cont **cap_lista,const char *nume,const char *valuta, int suma_adaugata) {
    Cont *curent = *cap_lista;
    Cont *anterior = NULL;
    bool cont_gasit = false;

    // Cauta contul in lista
    while (curent != NULL) {
        if (strcmp(curent->nume, nume) == 0 && strcmp(curent->valuta, valuta) == 0) {
            curent->suma += suma_adaugata;
            cont_gasit = true;
            break;
        }
        anterior = curent;
        curent = curent->urmatorul;
    }

    // Daca contul nu a fost gasit, adauga un nou cont
    if (!cont_gasit) {
        Cont *nou_cont = (Cont *)malloc(sizeof(Cont));
        if (nou_cont == NULL) {
            elibereaza_memoria_conturilor(*cap_lista);
            exit(EXIT_FAILURE);
        }
        strcpy(nou_cont->nume, nume);
        strcpy(nou_cont->valuta, valuta);
        nou_cont->suma = suma_adaugata;
        nou_cont->urmatorul = NULL;

        if (anterior != NULL) {
            anterior->urmatorul = nou_cont;
        } else {
            *cap_lista = nou_cont;
        }
    }
}

void actualizeaza_cont_retragere(Cont **cap_lista,const char *nume,const char *valuta, int suma_adaugata) {
    Cont *curent = *cap_lista;
    Cont *anterior = NULL;
    bool cont_gasit = false;

    // Cauta contul in lista
    while (curent != NULL) {
        if (strcmp(curent->nume, nume) == 0 && strcmp(curent->valuta, valuta) == 0) {
            curent->suma += suma_adaugata;
            cont_gasit = true;
            break;
        }
        anterior = curent;
        curent = curent->urmatorul;
    }

    // Daca contul nu a fost gasit, adauga un nou cont
    if (!cont_gasit) {
        Cont *nou_cont = (Cont *)malloc(sizeof(Cont));
        if (nou_cont == NULL) {
            fprintf(stderr, "Eroare la alocarea memoriei pentru un nou cont.\n");
            elibereaza_memoria_conturilor(*cap_lista);
            exit(EXIT_FAILURE);
        }
        strcpy(nou_cont->nume, nume);
        strcpy(nou_cont->valuta, valuta);
        nou_cont->suma = suma_adaugata;
        nou_cont->urmatorul = NULL;

        if (anterior != NULL) {
            anterior->urmatorul = nou_cont;
        } else {
            *cap_lista = nou_cont;
        }
    }
}

void scrie_conturi_in_fisier(FILE *fisier, Cont *cap_lista) {
    Cont *curent = cap_lista;
    while (curent != NULL) {
        fprintf(fisier, "%s, %s, %d\n", curent->nume, curent->valuta, curent->suma);
        curent = curent->urmatorul;
    }
}

void elibereaza_memoria_conturilor(Cont *cap_lista) {
    Cont *curent;
    while (cap_lista != NULL) {
        curent = cap_lista;
        cap_lista = cap_lista->urmatorul;
        free(curent);
    }
}

void log_in_menu(const char *nume) {
    char key;

    do {
        printf("Alege o optiune:\n");
        printf("1. Adauga bani\n");
        printf("2. Retrage bani\n");

        // Așteptăm să se apese o tastă
        key = _getch();
        char valuta;
        switch(key) {
            case '1':
                printf("Te rog tasteaza suma pe care doresti sa o adaugi in cont:");
                int suma_adaugare;
                scanf("%d", &suma_adaugare);
                printf("Alege o optiune:\n");
                printf("1. Pentru RON apasa tasta 1\n");
                printf("2. Pentru EUR apasa tasta 2\n");
                valuta = _getch();
                switch (valuta) {
                    case '1':
                        adaugare_bani(nume, "RON", suma_adaugare);
                        break;
                    case '2':
                        adaugare_bani(nume, "EUR", suma_adaugare);
                        break;
                }
                break;
            case '2':
                printf("Te rog tasteaza suma pe care doresti sa o adaugi in cont:");
                int suma_retragere;
                scanf("%d", &suma_retragere);
                printf("Alege o optiune:\n");
                printf("1. Pentru RON apasa tasta 1\n");
                printf("2. Pentru EUR apasa tasta 2\n");
                valuta = _getch();
                switch (valuta) {
                    case '1':
                        retragere_bani(nume, "RON", suma_retragere);
                        break;
                    case '2':
                        retragere_bani(nume, "EUR", suma_retragere);
                        break;
                }
                break;
            case 27: // Codul ASCII pentru tasta ESC
                system("cls");
                return; // Iesim din funcție
        }

        printf("Apasa orice tasta pentru a reveni la meniu...\n");
        _getch(); // Pauză, așteptăm o nouă apăsare de tastă pentru a reveni la meniu
        system("cls");
    } while(key != 27); // Continuăm până când este apăsată tasta ESC
}

int accesare_cont(char *nume){
    char buffer[1024];
    FILE *file = fopen("date_conturi.txt", "r");

    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }
    while (fgets(buffer, 1024, file)) {
        if (strstr(buffer, nume)) {
            printf("%s\n", buffer);
        }
    }
    fclose(file);

    log_in_menu(nume);

    return 1;
}

void adaugare_cont(char *nume, char *parola){
    char buffer[1024];
    FILE *file = fopen("conturi.txt", "r");
    int i = 1;

    if (file != NULL) {
        while(fgets(buffer, 1024, file)){
            i++;
        }
        fclose(file);
    }

    FILE *file_w = fopen("conturi.txt", "a");
    if (file_w == NULL) {
        perror("Eroare la deschiderea fisierului");
        return;
    }

    if (i > 1) {
        fprintf(file_w, "\n");
    }
    sprintf(buffer, "%d,%s,%s", i, nume, parola);
    fprintf(file_w, "%s", buffer);
    fclose(file_w);

    FILE *fisier = fopen("date_conturi.txt", "r");
    if (!fisier) {
        perror("Nu s-a putut deschide fisierul pentru citire");
        return;
    }

    Cont *conturi = incarca_conturi(fisier);
    fclose(fisier);

    adauga_sau_actualizeaza_cont(&conturi, nume, "RON", 0);
    adauga_sau_actualizeaza_cont(&conturi, nume, "EUR", 0);

    fisier = fopen("date_conturi.txt", "w");
    if (!fisier) {
        perror("Nu s-a putut deschide fisierul pentru scriere");
        elibereaza_memoria_conturilor(conturi);
        return;
    }

    scrie_conturi_in_fisier(fisier, conturi);
    fclose(fisier);

    elibereaza_memoria_conturilor(conturi);

    printf("\nCont adaugat cu succes!");
}

void adaugare_bani(const char *nume, const char *valuta, int suma_adaugata) {
    // Incarca conturile existente din fisier
    FILE *fisier = fopen("date_conturi.txt", "r");
    if (!fisier) {
        perror("Nu s-a putut deschide fisierul pentru citire");
        exit(1);
    }
    Cont *conturi = incarca_conturi(fisier);
    fclose(fisier);

    // Adauga sau actualizeaza conturile cu informatiile primite
    adauga_sau_actualizeaza_cont(&conturi, nume, valuta, suma_adaugata);

    // Deschide fisierul pentru scriere si actualizeaza-l cu noile date ale conturilor
    fisier = fopen("date_conturi.txt", "w");
    if (!fisier) {
        perror("Nu s-a putut deschide fisierul pentru scriere");
        elibereaza_memoria_conturilor(conturi);
        exit(1);
    }
    scrie_conturi_in_fisier(fisier, conturi);
    fclose(fisier);

    // Elibereaza memoria alocata pentru lista de conturi
    elibereaza_memoria_conturilor(conturi);
}



void retragere_bani(const char *nume, const char *valuta, int suma){
    // Incarca conturile existente din fisier
    FILE *fisier = fopen("date_conturi.txt", "r");
    if (!fisier) {
        perror("Nu s-a putut deschide fisierul pentru citire");
        exit(1);
    }
    Cont *conturi = incarca_conturi(fisier);
    fclose(fisier);

    // Adauga sau actualizeaza conturile cu informatiile primite
    actualizeaza_cont_retragere(&conturi, nume, valuta, suma);

    // Deschide fisierul pentru scriere si actualizeaza-l cu noile date ale conturilor
    fisier = fopen("date_conturi.txt", "w");
    if (!fisier) {
        perror("Nu s-a putut deschide fisierul pentru scriere");
        elibereaza_memoria_conturilor(conturi);
        exit(1);
    }
    scrie_conturi_in_fisier(fisier, conturi);
    fclose(fisier);

    // Elibereaza memoria alocata pentru lista de conturi
    elibereaza_memoria_conturilor(conturi);
}