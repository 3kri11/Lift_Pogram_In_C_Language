#include "lift.h"
#include <stdbool.h>
#define ADMIN 0
#define USER 1
typedef struct{
    char email[50];
    char password[20];
}user;
bool logIn(user *,short int);
void createUser();
void adminMenu();
void userMenu();
void cls();
bool logIn(user *u,short int tip){
    FILE *fp = fopen(tip == ADMIN ? "admin.dat" : "user.dat","rb");
    if(fp == NULL){
        printf("{error404}");
    }
    user a;
    while (!feof(fp))
    {
        fscanf(fp,"%s %s ", a.email,a.password);
        if (strcmp(u->email,a.email) == 0 && strcmp(u->email,a.email) == 0)
        {
            fclose(fp);
            return true;
        }
        
    }
    fclose(fp);
    return false;
    
}
void createUser(){
    user u;
    printf("Kreiranje novog korisnika");
    printf("\nEmail: ");
    scanf("%s",&u.email);
    printf("\nPassword: ");
    scanf("%s",&u.password);
    FILE *fp = fopen("user.dat","rb+");
    if(fp != NULL){
        user ax;//Ax znaci aready exists
        while (!feof(fp))
        {
            fscanf(fp,"%s %s",ax.email,ax.password);
            if (strcmp(ax.email,u.email) == 0)
            {
                printf("Korisnik vec postoji s tim emailomm");
                fclose(fp);
                return;
            }
            
        }
        
    }
    fp=fopen("user.dat","ab+");
    fprintf(fp,"%s %s\n",u.email,u.password);
    printf("\nKorisnik je uspjesno kreiran!\n");
    fclose(fp);
}
void adminMenu(){
    cls();
    printf("\nHello Admin!!!:)\n");
    while (1)
    {
        int opcija;
        printf("\n\nMenu");
        printf("\n1.Kreiranje novog Korisnika\n2.Kreiranje novog Nosila\n3.Ispis jednog Nosila\n4.Prikaz nosila za servisranje\n5.Blokirana nosila\n6.Exit ");
        printf("\nIzaberite jednu od opcija: ");
        scanf("%d",&opcija);
        switch (opcija)
        {
        case 1:
            createUser();
            break;
        case 2:
            createLift();
            break;
        case 3:
            showLift();
            break;
        case 4:
            listOfLifts(Servis);
            break;
        case 5:
            listOfLifts(Block);
            break;
        case 6:
            return;
            break;
        
        default:

            printf("Ne postoji opcija");
        }
    }
    
}
void userMenu(){
    cls();
    printf("\nHello Korisnice!!!:)\n");
    while (1)
    {
        lift ak;
        int opcija;
        FILE *fp = fopen("lift.dat","rb+");
        printf("\n\nMenu");
        printf("\n1.Aktivacija lifta\n2.Poziv lifta\n3.Exit");
        printf("\nIzaberite jednu od opcija: ");
        scanf("%d",&opcija);
        cls();
        switch (opcija)
        {
        case 1:
            activateLift(&ak,fp);
            break;
        case 2:
                if (strcmp(ak.naziv,"") == 0){
                    printf("\n Nijedno nosilo nije aktivirano");
                    break;
                }
                if(!moveLift(&ak,0,fp))
                break;
                int br_sprat;
                if (ak.br_spratova >2)
                {
                    printf("\nBroj zeljenog sprata:");
                    do
                    {
                        printf("(1-%d): ",ak.br_spratova-1);
                        scanf("%d",&br_sprat);
                    } while (br_sprat < 1 || br_sprat > ak.br_spratova - 1);
                    
                }else{
                    br_sprat = 1;
                    if(moveLift(&ak,br_sprat,fp))
                    break;
                    cls();
                }
                
            break;
        case 3:
            fclose(fp);
            return;
            break;
        
        
        default:

            printf("Ne postoji opcija");
        }
    }

}
void cls(){
    system("cls");

}
