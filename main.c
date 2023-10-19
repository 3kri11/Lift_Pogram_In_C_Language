#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "main.h"




int main(int argc, char const *argv[])
{
    cls();
    while (1)
    {
        user u;
        printf("\n\n<----------Prijava---------->\n\n");
        printf("\nEmail: ");
        scanf("%s",u.email);
        printf("\nPassword: ");
        scanf("%s",u.password);
        bool ex = logIn(&u,ADMIN);
        if(ex){
            adminMenu();

        }else{
            ex = logIn(&u,USER);
            if (ex)
            {
                userMenu();
                break;
            }else{
                cls();
                printf("Ne postoji korisnik.Pogresan unos podataka.\n\n");
            }
            
            
        }
    }
    
    return 0;
}
