#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include "csv_parser.c"
#include "actiuni_conturi.c"

void sign_up() {
    char nume_utilizator[100] = {0};
    char parola[100] = {0};
    int i = 0;
    char ch;

    printf("Introduceti un nume de utilizator: ");
    while(1) {
        if (_kbhit()) {
            ch = _getch();
            if (ch == 27) { // ESC
                system("cls");
                return;
            } else if (ch == '\r') { // ENTER
                break;
            } else {
                nume_utilizator[i++] = ch;
                putchar(ch);
            }
        }
    }
    nume_utilizator[i] = '\0';

    if(!exista_cont(nume_utilizator)){
        printf("\nIntroduceti parola pentru cont: ");
        i = 0;
        while(1) {
            if (_kbhit()) {
                ch = _getch();
                if (ch == 27) { // ESC
                    system("cls");
                    return;
                } else if (ch == '\r') { // ENTER
                    break;
                } else {
                    parola[i++] = ch;
                    putchar('*');
                }
            }
        }
        parola[i] = '\0';
        adaugare_cont(nume_utilizator, parola);
        system("cls");
    }
    else{
        printf("\nNumele contului exista deja.\nApasa ENTER pentru a te intoarce la meniul principal.");
        while(_getch() != '\r'); // Asteptam ENTER
        system("cls");
    }
}

void log_in() {
    char nume_utilizator[100] = {0};
    char parola[100] = {0};
    int ch, index = 0;

    printf("Nume utilizator: ");
    while (1) {
        if (_kbhit()) {
            ch = _getch();
            if (ch == 27) { // ESC
                system("cls");
                return;
            } else if (ch == '\r') { // ENTER
                nume_utilizator[index] = '\0';
                break;
            } else if (ch == '\b' && index > 0) { // BACKSPACE
                putchar('\b');
                putchar(' ');
                putchar('\b');
                nume_utilizator[--index] = '\0';
            } else if (isalnum(ch) || ispunct(ch) || isspace(ch)) { // Accepta litere, cifre si semne de punctuatie
                if (index < sizeof(nume_utilizator) - 1) {
                    nume_utilizator[index++] = ch;
                    putchar(ch);
                }
            }
        }
    }

    if (exista_cont(nume_utilizator) == 1) {
        printf("\nIntroduceti parola: ");
        index = 0;
        while (1) {
            if (_kbhit()) {
                ch = _getch();
                if (ch == 27) { // ESC
                    system("cls");
                    return;
                } else if (ch == '\r') { // ENTER
                    parola[index] = '\0';
                    break;
                } else if (ch == '\b' && index > 0) { // BACKSPACE
                    putchar('\b');
                    putchar(' ');
                    putchar('\b');
                    parola[--index] = '\0';
                } else if (isalnum(ch) || ispunct(ch) || isspace(ch)) { // Accepta litere, cifre si semne de punctuatie
                    if (index < sizeof(parola) - 1) {
                        parola[index++] = ch;
                        putchar('*');
                    }
                }
            }
        }

        // Verificare si restul logicii de autentificare
        if (parola_corecta(nume_utilizator, parola) == 1) {
            accesare_cont(nume_utilizator);
        } else {
            printf("\nParola incorecta. Incercati din nou.\n");
            // Aici poate urma restul codului pentru gestionarea incercarilor de login nereusite
        }
    } else {
        printf("\nNumele de utilizator nu exista.\n");
        _getch();
        system("cls");
        log_in();
    }
}



void setConsoleColor(WORD color) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, color);
}

int main() {
    char ch;
    while(1){
        printf("1. Log in\n");
        printf("2. Sign up\n");
        ch = _getch();

        switch(ch) {
            case '1':
                system("cls");
                log_in();
                break;
            case '2':
                system("cls");
                sign_up();
                break;
            default:
                setConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY); // Face culoarea de ECHO rosu
                system("cls");
                printf("Input invalid, va rugam apasati tasta 1 sau 2\n");
                setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reseteaza culoarea de ECHO
                break;
        }
    }
    return 0;
}