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
    // Citim parola avand grija ca daca tasta ESC este apasata sa ne intoarcem la meniul principal
    while (1) {
        if (_kbhit()) {
            ch = _getch();
            if (ch == 27) { // ESC
                system("cls");
                return;
            } else if (ch == '\r') { // ENTER
                break;
            } else {
                if (index < sizeof(nume_utilizator) - 1) {
                    nume_utilizator[index++] = ch;
                    putchar(ch); // Scrie caracter
                }
            }
        }
    }
    nume_utilizator[index] = '\0';

    if (exista_cont(nume_utilizator) == 1) {
        printf("\nIntroduceti parola: ");
        // Reset index for password input
        index = 0;
        // Citim parola avand grija ca daca tasta ESC este apasata sa ne intoarcem la meniul principal
        while (1) {
            if (_kbhit()) {
                ch = _getch();
                if (ch == 27) { // tasta ESC apasata
                    system("cls");
                    return;
                } else if (ch == '\r') { // Tasta ENTER apasata
                    break;
                } else {
                    if (index < sizeof(parola) - 1) {
                        parola[index++] = ch;
                        putchar('*'); // Scrie parola ca asterix-uri
                    }
                }
            }
        }
        parola[index] = '\0';

        if (parola_corecta(nume_utilizator, parola) == 1) {
            accesare_cont(nume_utilizator);
        } else {
            for (int i = 2; i > 0; --i) {
                printf("\nParola incorecta! Mai aveti %d incercari.\n", i);
                // Sterge buffer-ul pentru a putea fi scrisa o noua parola
                memset(parola, 0, sizeof(parola));
                index = 0;
                while (1) {
                    if (_kbhit()) {
                        ch = _getch();
                        if (ch == 27) { // tasta ESC apasata
                            system("cls");
                            return;
                        } else if (ch == '\r') { // Tasta ENTER apasata
                            break;
                        } else {
                            if (index < sizeof(parola) - 1) {
                                parola[index++] = ch;
                                putchar('*'); // Scrie parola ca asterix-uri
                            }
                        }
                    }
                }
                parola[index] = '\0'; // Null-terminate string

                if (parola_corecta(nume_utilizator, parola) == 1) {
                    accesare_cont(nume_utilizator);
                    return;
                }
            }
            printf("\nAti gresit parola de prea multe ori, va rugam reincercati conectarea.\n");
            _getch(); // Asteapta keypress
            system("cls");
            log_in();
        }
    } else {
        printf("\nNumele de utilizator nu exista.\n");
        _getch(); // Asteapta keypress
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
        printf("Choice: ");
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