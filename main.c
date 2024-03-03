#include <stdio.h>
#include "csv_parser.c"
#include "actiuni_conturi.c"
#include <string.h>

void sign_up(){
    char nume_utilizator;
    char parola;
    printf("Introduceti un nume de utilizator: ");
    scanf("%s", &nume_utilizator);

}

void log_in(){
    char nume_utilizator[100]; // Change this to an appropriate size
    char parola[100]; // Change this to an appropriate size
    printf("Nume utilizator:");
    getchar();
    fgets(nume_utilizator, 100, stdin);
    printf("%llu\n", strlen((nume_utilizator)));
    nume_utilizator[((strlen(nume_utilizator) - 1))] = '\0';
    if(exista_cont(nume_utilizator) == 1){
        // Username exists
        printf("Introduceti parola:");
        getchar();
        fgets(parola, 100, stdin);
        parola[((strlen(parola) - 1))] = '\0';
        if(parola_corecta(nume_utilizator, parola) == 1){
            // If the password is correct
            accesare_cont(nume_utilizator);
        }
        else{
            // If the password is incorrect
            int i = 2; // Start with 2 more attempts (total 3 attempts including the first one outside the loop)
            while(i > 0){
                printf("Parola incorecta! Mai aveti %d incercari. ", i);
                scanf("%s", parola);
                if(parola_corecta(nume_utilizator, parola) == 1){
                    accesare_cont(nume_utilizator);
                    return; // Exit the log_in function after successful login
                }
                i--;
            }
            printf("Ati gresit parola de prea multe ori, va rugam reincercati conectarea.\n");
            // The getchar() here might consume the newline character left by scanf
            getchar();
            log_in();
        }
    }
    else{
        printf("Numele de utilizator nu exista.\n");
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
                log_in();
                break;
            case 2:
                // Your sign up code would go here
                break;
            default:
                return 0;
        }
    }
    return 0;
}
