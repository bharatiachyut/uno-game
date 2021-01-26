 struct Master{
    char cardType[12];
    char color[7];
};
struct Master*masterDeck=(struct Master*)calloc(60,sizeof(struct Master));
void initialiseMasterDeck(struct Master*masterDeck)
{
    int i,k=1;
    FILE*fcard;
    char*s=(char*)calloc(12,sizeof(char));



    fcard=fopen("cards.c","r");
    for(i=0;i<60&&fscanf(fcard,"%s",s)!=EOF;i++){
        strcpy(masterDeck[i].cardType,s);
        if(i<15)
            strcpy(masterDeck[i].color,"RED");
        else if(i>=15&&i<30)
            strcpy(masterDeck[i].color,"YELLOW");
        else if(i>=30&&i<45)
            strcpy(masterDeck[i].color,"BLUE");
        else
            strcpy(masterDeck[i].color,"GREEN");
    }
     fclose(fcard);

}
