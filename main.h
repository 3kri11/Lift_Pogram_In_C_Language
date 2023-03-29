struct  admin
{
    char email[50];
    char password[20];
};
struct user
{
    char email[50];
    char password[20];
};
struct lift
{
    char name[20];
    int brojAktivacija=0;
    int pragPrijeServisa;
    int brojMaxKoristenja;
    int trenBrojKoristenje=0;
};
void logIn(char *email, char *password){

}
void registration(char *email, char *password){

}
void adminControls(){

}
void userControls(){

}
void liftGraphics(){}