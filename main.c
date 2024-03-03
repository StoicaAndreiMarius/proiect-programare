#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "csv_parser.c"
#include "actiuni_conturi.c"

void sign_up(){
    char nume_utilizator[100];
    char parola[100];
    printf("Introduceti un nume de utilizator: ");
    getchar();
    fgets(nume_utilizator, 100, stdin);
    nume_utilizator[((strlen(nume_utilizator) - 1))] = '\0';
    if(!exista_cont(nume_utilizator)){
        printf("\nIntroduceti parola pentru cont: ");
        fgets(parola, 100, stdin);
        parola[((strlen(parola) - 1))] = '\0';
        adaugare_cont(nume_utilizator, parola);
        getchar();
        system("cls");
        return;
    }
    else{
        printf("Numele contului exista deja.\n Apasa ENTER pentru a te intoarce la meniul principal.");
        getchar();
        system("cls");
        return;
    }
}

void log_in(){
    char nume_utilizator[100];
    char parola[100];
    printf("Nume utilizator:");
    getchar();
    fgets(nume_utilizator, 100, stdin);
    nume_utilizator[((strlen(nume_utilizator) - 1))] = '\0';
    if(exista_cont(nume_utilizator) == 1){
        printf("Introduceti parola:");
        getchar();
        fgets(parola, 100, stdin);
        parola[((strlen(parola) - 1))] = '\0';
        if(parola_corecta(nume_utilizator, parola) == 1){
            accesare_cont(nume_utilizator);
        }
        else{
            int i = 2;
            while(i > 0){
                printf("Parola incorecta! Mai aveti %d incercari.\n ", i);
                scanf("%s", parola);
                if(parola_corecta(nume_utilizator, parola) == 1){
                    accesare_cont(nume_utilizator);
                    return;
                }
                i--;
            }
            printf("Ati gresit parola de prea multe ori, va rugam reincercati conectarea.\n");
            getchar();
            system("cls");
            log_in();
        }
    }
    else{
        printf("Numele de utilizator nu exista.\n");
        getchar();
        system("cls");
        log_in();
    }
}

int main() {
    int n;
    while(1){
        printf("1. Log in\n");
        printf("2. Sign up\n");
        printf("Choice: ");
        scanf("%d", &n);
        switch(n) {
            case 1:
                system("cls");
                log_in();
                break;
            case 2:
                system("cls");
                sign_up();
                break;
            default:
                printf("Input Invalid.\n");
                getchar();
                return 0;
        }
    }
    return 0;
}
