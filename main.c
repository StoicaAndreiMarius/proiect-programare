#include <stdio.h>

void sign_up(){
    char nume_utilizator;
    char parola;
    printf("Introduceti un nume de utilizator: ");
    scanf("%s", nume_utilizator);

}

void log_in(){
    char nume_utilizator;
    char parola;
    printf("Nume utilizator:");
    scanf("%s", &nume_utilizator);
    if(exista_cont(nume_utilizator)){
        printf("Introduceti parola:");
        scanf("%s", &parola);
        if(parola_corecta(nume_utilizator, parola)){
            accesare_cont(nume_utilizator, parola);
        }
        else{
            int i = 3;
            while(parola_corecta(nume_utilizator, parola) != 1 || i == 0){
                if(i == 3)
                    printf("Parola incorecta! Incercati din nou.");
                else{
                    printf("Parola incorecta! Mai aveti %d incercari.", i);
                }
                scanf("%s", &parola);
                i--;
            }
        }
    }
    else{
        printf("Numele de utilizator nu exista.\n");
        log_in();
    }
}




int main(){
    int n;
    while(1){
        scanf("%d", &n);
        printf("1. Log in\n");
        printf("2. Sign up\n");
        printf("Choice: ");
        switch (n) {
            case 1:
                log_in();
                break;
            case 2:
                sign_up();
                break;
        }
    }
    return 0;
}