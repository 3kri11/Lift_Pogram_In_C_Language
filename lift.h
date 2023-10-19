#define MAX_NAZIV 10
#define Servis 0
#define Block 1
typedef struct
{
    char naziv[MAX_NAZIV];
    int br_spratova,br_koristenja,limit_servis,limit_block;
}lift;
void createLift();
void showLift();
void listOfLifts(short int);
bool moveLift(lift *,int,FILE *);
void activateLift(lift *,FILE *);
bool unos();


void createLift(){
    lift li;
    printf("\nUneste ime nosila: ");
    scanf("%s",&li.naziv);
    printf("\nBroj spratova: ");
    do{
        printf("\nMinimalno 2 sprata: ");
        scanf("%d",&(li.br_spratova));
    } while (li.br_spratova < 2);
    printf("\nUnseite broj mogucih koristeja prije servisiranja: ");
    do{
        printf("\nMinimalno 1 koristenje: ");
        scanf("%d",&(li.br_koristenja));
    } while (li.br_koristenja < 1);
    printf("\nUnseite broj mogucih dodatnih koristeja prije servisiranja: ");
    do{
        printf("\nMinimalno 1 sprata: ");
        scanf("%d",&(li.limit_block));
    } while (li.br_spratova < 2);
    li.br_koristenja = 0;

    FILE *fp;
    fp = fopen("lift.dat","ab+");
    if(fp != NULL){
        fwrite(&li,sizeof(lift),1,fp);

    }else{
        printf("{error404}");
    }
    fclose(fp);


}
void showLift(){
    char s[MAX_NAZIV];
    printf("\nUnesite naziv lifta: ");
    scanf("%s",&s);

    lift li;
    FILE *fp=fopen("lift.dat","rb");
    while (fread(&li,sizeof(lift),1,fp) == 1)
    {
        if(strcmp(li.naziv,s) == 0){
            printf("\nNosilo:  %s",li.naziv);
            printf("\nBroj koristenja - %d",li.br_koristenja);
            int x = li.limit_servis - li.br_koristenja;
            printf(x > 0 ? "%d do servisa" : "\tNosilu potreban servis",x);
            printf("\n");
            x = li.limit_servis + li.limit_block - li.br_koristenja;
            printf(x > 0 ? "%d do blokade" : "\tNosilo blokirano",x);
            printf("\n");
            fclose(fp);
            return;
        }
    }
    printf("\nNosilo koje treazite ne postoji");
    fclose(fp);
}
void listOfLifts(short int tip){
    FILE *fp = fopen("lift.dat","rb+");
    if (fp == NULL){
        printf("{error404}");
        fclose(fp);
    }
    lift li;
    bool pot = false;
    while (fread(&li,sizeof(lift),1,fp) == 1)
    {
        int razlika = tip == Servis ? li.limit_servis - li.br_koristenja : li.limit_block + li.limit_servis - li.br_koristenja;
        if(razlika <=0){
        if (!pot){
            printf(tip == Servis ? "Sljedecim nosilima je potreban servis:\n\n" : "Sljedeca nosila su blokirana:\n\n");
            pot = true;
        }
        printf("%s",li.naziv);
        }
    }
    printf("\n");
    if (!pot){
            printf(tip == Servis ? "Nijednomnosilu nije potreban servis.\n\n" : "Nijedno nosilo nije blokirano.\n\n");
            fclose(fp);
        }
        printf("Zelite li servisirati nosila");
        if (unos()){
            fseek(fp,0,SEEK_SET);
            while(fread(&li,sizeof(lift),1,fp)==1){
                int razlika = tip == Servis ? li.limit_servis - li.br_koristenja : li.limit_block + li.limit_servis - li.br_koristenja;
                if (razlika <= 0){
                    li.br_koristenja = 0;
                    fseek(fp, -sizeof(lift),1);
                    fwrite(&li,sizeof(lift),1,fp);
                    fflush(fp);
                }
            }
            printf("\nNosila uspjesno servisirana");
        }
        fclose(fp);
}
void activateLift(lift *ak,FILE *fp){
    printf("\nNaziv zeljenog nosila:");
    char s[MAX_NAZIV];
    scanf("%s",&s);
    if (strcmp(ak->naziv,s) == 0){
        printf("\nNosilo '%s' je vec aktivirano",s);
        return;
    }
    strcpy(ak->naziv,"");
    fflush(fp);
    fseek(fp,0,SEEK_SET);
    lift li;
    while (fread(&li,sizeof(lift),1,fp) == 1)
    {
        if (strcmp(li.naziv,s) == 0)
        {
            printf("\nNosilo uspjesno aktivirano!\n");
            *ak=li;
            return;
        }
        
    }
    if(strcmp(ak->naziv,"") == 0) printf("\nNosilo s tim nazivom ne postoji\n");

}
bool moveLift(lift *li,int sprat,FILE *fp){
    if (li->br_koristenja == li->limit_servis + li->limit_block){
        printf("\nAktivirano nosilo '%s' je trenutno blokirano\n",li->naziv);
        return false;
    }
    bool d = sprat !=0;
    int brojPomijeranja = d ? sprat+1 : li->br_spratova;
        for (int i = 0; i<brojPomijeranja; i++){
            if (i>0)
            for (int j = 0; j< li->br_spratova; j++)
            {
                if((!d && i ==j) || (d && li->br_spratova-i-1 ==j)) printf("|||");
                else printf("|");
                printf("\n\n");
            }
            printf(i==brojPomijeranja -1 ? "\aNosilo je stiglo" : d ? "Nosilo se dize..." : "Nosilo se spusta...");


        }
        li->br_koristenja++;
        fseek(fp,-sizeof(lift),SEEK_CUR);
        fwrite(li,sizeof(lift),1,fp);
        return true;
}
bool unos(){
    char c;
        do
        {
            printf("[y/n]:");
            scanf("%c",&c);
            c=tolower(c);
        } while (c !='y' && c !='n');
        return c =='y';
}