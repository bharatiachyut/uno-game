/*
              *********        M A B  9.40         ***********
                           THE BATTLE OF CARDS

    Authors: MAYANK AGRAWAL & ASHANK BHARATI

    Dept.  : COMPUTER SCIENCE

    DATE   : 11-11-2016

*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<strings.h>
#include<windows.h>

struct node{
    char cardType[12];
    char color;
    int flag;
    struct node*next;
};

typedef struct node*nodeptr;
 struct Master{
    char cardType[12];
    char color;
};

nodeptr getNode(void){
    nodeptr new_node=(nodeptr)malloc(sizeof(struct node));
    return new_node;
}
void deleteRear(nodeptr*first){
if(*first==NULL||(*first)->next==NULL)
    return;
nodeptr last=(*first)->next;
while(last->next!=NULL)
    last=last->next;

(*first)->next=NULL;
free(last);
}
void push(nodeptr *first,char colr,char*cardTyp){ //insertAtFirst
    nodeptr temp=getNode();
    temp->color=colr;
    temp->flag=0;
    strcpy(temp->cardType,cardTyp);
    temp->next=*first;
    *first=temp;
}
void insertRear(nodeptr* first,char colr,char*cardTyp){
    nodeptr last=*first;
    nodeptr temp=getNode();
    temp->color=colr;
    temp->flag=0;
    strcpy(temp->cardType,cardTyp);
    temp->next=NULL;
    if(*first==NULL){
        *first=temp;
        return;
    }
    while(last->next!=NULL)
        last=last->next;
    last->next=temp;

}
void freeNodes(nodeptr*list){
if(*list==NULL)
    return;
nodeptr temp=*list,prev=NULL;
while(temp!=NULL){
    prev=temp;
    temp=temp->next;
    free(prev);
}
}
void add_card(nodeptr *player,nodeptr *master)
{
    nodeptr temp1 = *player;
    nodeptr temp2 = *master;
    nodeptr newn = getNode();
    newn->color = temp2->color;
    newn->flag=0;
    strcpy(newn->cardType,temp2->cardType);
    while(temp1->next != NULL)
        temp1 = temp1->next;
    temp1->next = newn;
    newn->next=NULL;
    *master = (*master)->next;
    free(temp2);
}
void display(nodeptr first){
    nodeptr temp=first;
    int i=0;
    printf("\t\t\t\t\t");
    while(temp!=NULL){
        printf("%d-%c%s    ",++i,temp->color,temp->cardType);
        temp=temp->next;
    }
    printf("\n");
}
int length(nodeptr first){
    nodeptr temp=first;
    int count =0;
    if(first==NULL)
        return 1;
    while(temp!=NULL){
       count++;
        temp=temp->next;
    }
    return count;
}
nodeptr deleteAtpos(nodeptr *first,int pos){
nodeptr temp=*first;
nodeptr curr=NULL;
int i;

if(pos==1){
    *first=(*first)->next;
    return temp;
}


for(i=1;i<pos;i++){
curr=temp;
temp=temp->next;
}
curr->next=temp->next;
return temp;
}

void initialiseMasterDeck(struct Master*masterDeck)
{
    int i,k=1;
    FILE*fcard;
    char*s=(char*)calloc(12,sizeof(char));



    fcard=fopen("cards.c","r");
    for(i=0;i<52&&fscanf(fcard,"%s",s)!=EOF;i++){
        strcpy(masterDeck[i].cardType,s);
        if(i<13)
            masterDeck[i].color='R';
        else if(i>=13&&i<26)
            masterDeck[i].color='Y';
        else if(i>=26&&i<39)
            masterDeck[i].color='B';
        else
            masterDeck[i].color='G';
    }
     fclose(fcard);

}
void shuffleMasterDeck(struct Master*masterDeck){
srand(time(NULL));
int i;
int rand1,rand2;
struct Master temp;
for(i=0;i<52;i++){
rand1=rand()%52;
rand2=rand()%52;
temp=masterDeck[rand1];
masterDeck[rand1]=masterDeck[rand2];
masterDeck[rand2]=temp;
}

}
int computerChance(nodeptr*compDeck,nodeptr*stackThrown,nodeptr*masterStack){
nodeptr temp1=*compDeck,prev=NULL;
nodeptr temp2=*stackThrown;
int i,count;
if(strcmp((*stackThrown)->cardType,"Wild")==0&&(*stackThrown)->flag==0)

{
    (*stackThrown)->flag=1;
    while(temp1!=NULL){
        if(strcmp(temp1->cardType,"Wild")==0){
            Sleep(1000);
            printf("\n\n\t\t\t*** HAHA !!  EVEN  I  AM   GOING  $ W I L D $  PLAYER  !!! ***\n\n");
            Sleep(1000);
            break;
        }
        prev=temp1;
        temp1=temp1->next;
    }

    if(temp1==NULL)
        goto wildRead;



}
else if(strcmp((*stackThrown)->cardType,"Skip")==0&&(*stackThrown)->flag==0)
        {
            (*stackThrown)->flag=1;
            Sleep(1000);
            printf("\n\n\t\t*** G r r r r ! You SKIPPED My Turn ***\n\n");
            Sleep(1000);
            printf("\t\t*** It's YOUR TURN AGAIN ***\n\n");
            return 1;

        }
else if((strcmp((*stackThrown)->cardType,"Draw2")==0)&& (*stackThrown)->flag==0){
        (*stackThrown)->flag=1;
        temp1=*compDeck;
    while(temp1!=NULL){

    if((strcmp(temp1->cardType,"Draw2")==0))
    {
        Sleep(1000);
        printf(" \n\n\t\tHAHA ! I  know  all  your  tricks \n\n");
        Sleep(500);
        break;
    }
    prev=temp1;
    temp1=temp1->next;
    }
    if(temp1==NULL)
    {
        temp2=*stackThrown;
        printf("\n\n\t\t*** Oh  no!   I   have   to   DRAW   2   cards ***\n");
        Sleep(1000);
        for(i=0;i<2;i++)
        add_card(&(*compDeck),&(*masterStack));
        return 1;
    }
}
else if((strcmp((*stackThrown)->cardType,"Draw4")==0)&& (*stackThrown)->flag==0){
        (*stackThrown)->flag=1;
        temp1=*compDeck;
    while(temp1!=NULL){

    if((strcmp(temp1->cardType,"Draw4")==0))
    {
        Sleep(1000);
        printf(" \n\n\t\tNOT BAD ! BUT I AM  SMARTER ;-) \n\n");
        Sleep(1000);
        break;
    }
    prev=temp1;
    temp1=temp1->next;
    }
    if(temp1==NULL)
    {
        temp2=*stackThrown;
        printf("\n\n\t\t*** Oh  no! :-(   I   have   to   DRAW   4   cards ***\n");
        for(i=0;i<4;i++)
        add_card(&(*compDeck),&(*masterStack));
        return 1;
    }
}
else{
  wildRead:temp1=*compDeck;
  temp2=*stackThrown;
while(temp1!=NULL){
    if((strcmp(temp1->cardType,temp2->cardType)==0)||(temp1->color==temp2->color))
        break;
    prev=temp1;
    temp1=temp1->next;
}
if(temp1==NULL){
    printf("\n\n\t\t Oop's !   It  seems  that  I  don't  have  any  valid  card\n");
    printf("\n\t\tLet's  pick  up  a  card  from  the  master  stack\n");
    add_card(&(*compDeck),&(*masterStack));
    temp1=*compDeck;
    while(temp1->next!=NULL)
    temp1=temp1->next;

    if((strcmp(temp1->cardType,temp2->cardType)!=0)&&(temp1->color!=temp2->color))
            return 1;
    else{
        Sleep(1000);

        push(&(*stackThrown),temp1->color,temp1->cardType);

        insertRear(&(*masterStack),temp1->color,temp1->cardType);
        printf("\n\n\t\tL E T'S   T H R O W\n\n");
                     printf("\n\n\t\t ----------- \n");
                     printf("\t\t|           | \n");
                     printf("\t\t|           | \n");
                     printf("\t\t|           | \n");
                     printf("\t\t    %c%s      \n",temp1->color,temp1->cardType);
                     printf("\t\t|           | \n");
                     printf("\t\t|           | \n");
                      printf("\t\t|           | \n");
                     printf(" \t\t ----------- \n");
        free(temp1);
        return 1;
        }
}
}


    if(temp1==*compDeck){
        *compDeck=temp1->next;
        push(&(*stackThrown),temp1->color,temp1->cardType);

        insertRear(&(*masterStack),temp1->color,temp1->cardType);
        Sleep(1000);
        printf("\n\n\t\tL E T'S   T H R O W\n\n");
                     printf("\n\n\t\t ----------- \n");
                     printf("\t\t|           | \n");
                     printf("\t\t|           | \n");
                     printf("\t\t|           | \n");
                     printf("\t\t    %c%s      \n",temp1->color,temp1->cardType);
                     printf("\t\t|           | \n");
                     printf("\t\t|           | \n");
                      printf("\t\t|           | \n");
                     printf(" \t\t ----------- \n");
        free(temp1);
        return 1;

    }
    prev->next=temp1->next;

    push(&(*stackThrown),temp1->color,temp1->cardType);

    insertRear(&(*masterStack),temp1->color,temp1->cardType);
    printf("\n\n\t\tL E T'S   T H R O W\n\n");
                     printf("\n\n\t\t ----------- \n");
                     printf("\t\t|           | \n");
                     printf("\t\t|           | \n");
                     printf("\t\t|           | \n");
                     printf("\t\t    %c%s      \n",temp1->color,temp1->cardType);
                     printf("\t\t|           | \n");
                     printf("\t\t|           | \n");
                     printf("\t\t|           | \n");
                     printf(" \t\t ----------- \n");
    free(temp1);
    return 1;

}
void initialiseDecks(nodeptr*userDeck,nodeptr*compDeck,nodeptr*masterStack,struct Master*masterDeck){
    int i;
    for(i=0;i<52;i++){

        if(i<10)
            push(&(*userDeck),masterDeck[i].color,masterDeck[i].cardType);
        else if(i>=10&&i<20)
            push(&(*compDeck),masterDeck[i].color,masterDeck[i].cardType);
        else
            push(&(*masterStack),masterDeck[i].color,masterDeck[i].cardType);
    }
}

int main()
{

    int i,k=0,ch,pos,count=1;
    char c;
    struct Master*masterDeck=(struct Master*)calloc(60,sizeof(struct Master));
    nodeptr userDeck=NULL,compDeck=NULL,masterStack=NULL,thrown=NULL,stackThrown=NULL,temp=NULL;
    int j=1;
    for(i=1;i<=5;i++){
    Sleep(200);
    system("cls");
    printf("\n\n\t\t\t\t\t#################################################################################################\n");
    printf("\t\t\t\t\t_________________________________________________________________________________________________\n\n");
    printf("\t\t\t\t\t\t**           **        ***        ********        *********   **    **   *********\n");
    printf("\t\t\t\t\t\t***         ***       ** **       **       *      **     **   **    **   *********\n");
    printf("\t\t\t\t\t\t** *       * **      **   **      **       *      **     **   **    **   **     **\n");
    printf("\t\t\t\t\t\t**  *     *  **     **     **     **********      *********   ********   **     ** \n");
    printf("\t\t\t\t\t\t**   *   *   **    ***********    **       *             **         **   **     **\n");
    printf("\t\t\t\t\t\t**    * *    **   **         **   **       *             **         **   *********\n");
    printf("\t\t\t\t\t\t**     *     **  **           **  ********               **  #      **   *********       \n");
    printf("\t\t\t\t\t_________________________________________________________________________________________________\n\n");
    printf("\t\t\t\t\t#################################################################################################\n");
    printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t L O A D I N G ....... %d %% \n",(j++)*20);
    Beep(800,500);



    Sleep(1000);
    system("cls");
}
    Beep(500,400);
    Beep(750,500);
    Beep(1000,500);

    printf("\n\n\t\t\t\t\t#################################################################################################\n");
    printf("\t\t\t\t\t_________________________________________________________________________________________________\n\n");
    printf("\t\t\t\t\t\t**           **        ***        ********        *********   **    **   *********\n");
    printf("\t\t\t\t\t\t***         ***       ** **       **       *      **     **   **    **   *********\n");
    printf("\t\t\t\t\t\t** *       * **      **   **      **       *      **     **   **    **   **     **\n");
    printf("\t\t\t\t\t\t**  *     *  **     **     **     **********      *********   ********   **     ** \n");
    printf("\t\t\t\t\t\t**   *   *   **    ***********    **       *             **         **   **     **\n");
    printf("\t\t\t\t\t\t**    * *    **   **         **   **       *             **         **   *********\n");
    printf("\t\t\t\t\t\t**     *     **  **           **  ********               **  #      **   *********       \n");
    printf("\t\t\t\t\t_________________________________________________________________________________________________\n\n");
    printf("\t\t\t\t\t#################################################################################################\n");
    printf("\n\n\t\t\t\t\t\t\t   *******  T H E     B A T T L E     O F     C A R D S  *******\n");
    Sleep(500);

    FILE*fp=fopen("rules.c","r");
    while(!feof(fp)){
        c=getc(fp);
        Sleep(40);
        putc(c,stdout);
    }
    fclose(fp);
    printf("\n\n\n\nPress Enter to START MAB 9.40\n\n");
    getch();


    initialiseMasterDeck(masterDeck);

     for(i=1;i<=3;i++){
        Sleep(500);
        system("cls");

        printf("\n\n\n\n\nINITIALISING   THE   M A S T E R   D E C K....\n");

        Sleep(1000);
        system("cls");
     }
     Sleep(500);

    shuffleMasterDeck(masterDeck);
    for(i=1;i<=3;i++){
        Sleep(500);
        system("cls");
        printf("\n\n\n\n\nS H U F F L I N G....\n");
        Sleep(1000);
        system("cls");
     }


    initialiseDecks(&userDeck,&compDeck,&masterStack,masterDeck);
    free(masterDeck);
    Sleep(500);


    enter_ch:printf("\n\n\n\n\t\t\t\t\t\t\t##***\tY O U R   D E C K   O F   C A R D S\t***##\n\n\n\n\n");

        display(userDeck);


        printf("\n\n");
        Sleep(1000);
        printf("\n\n\n****\tY O U R   T U R N\t****\n");
        printf(" _____________________________\n");
        Sleep(1000);
        printf("\n\nEnter your choice:\n\n\n1.Throw the desired card\n\n2.Pick up a card from the master stack \n\n3.HELP\n\n");
        scanf("%d",&ch);
        switch(ch){
        read :    case 1: printf("Enter the position of the card as displayed above\n");
            scanf("%d",&pos);
            if(pos<1||pos>length(userDeck)){
                printf("Invalid position! Card does not exist\n");
                goto read;
            }
            thrown=deleteAtpos(&userDeck,pos);

            if(strcmp(thrown->cardType,"Wild")==0)
                goto printThrown;
             if(stackThrown!=NULL)
            {

                if((strcmp(stackThrown->cardType,thrown->cardType)!=0)&&(stackThrown->color!=thrown->color))
                {
                    printf("Ah!Dare not throw the invalid card!!\n");
                    insertRear(&userDeck,thrown->color,thrown->cardType);
                    free(thrown);
                    goto enter_ch;
                }

             }
             Sleep(1000);
     printThrown :   printf("\n\n\t\t ----------- \n");
                     printf("\t\t|           | \n");
                     printf("\t\t|           | \n");
                     printf("\t\t|           | \n");
                     printf("\t\t    %c%s      \n",thrown->color,thrown->cardType);
                     printf("\t\t|           | \n");
                     printf("\t\t|           | \n");
                      printf("\t\t|           | \n");
                     printf(" \t\t ----------- \n");
                     Sleep(1000);

            push(&stackThrown,thrown->color,thrown->cardType);
            deleteRear(&stackThrown);

            insertRear(&masterStack,thrown->color,thrown->cardType);
            free(thrown);
            if(userDeck==NULL){
                printf("\n\n*************\t\t\tYOU WIN\t\t\t*******************\n\n");
                getchar();
                freeNodes(&stackThrown);
                freeNodes(&userDeck);
                freeNodes(&compDeck);
                freeNodes(&masterStack);
                exit(0);
            }

            break;
        case 2: add_card(&userDeck,&masterStack);
                printf("\n\n\t\t\t\t\t\t\t\t\t##***\tY O U R  D E C K  O F   C A R D S\t***##\n\n\n");

                display(userDeck);

                Sleep(1000);
                printf("Press 1 to throw the desired card\nPress 2 to pass the chance\n");
                scanf("%d",&pos);
                if(pos==1)
                    goto read;
                else
                    break;

                break;
        case 3:fp=fopen("rules.c","r");
                while(!feof(fp)){
                    c=getc(fp);
                    putc(c,stdout);
                }
                fclose(fp);
                goto enter_ch;
                break;
            default : printf("INVALID ENTRY!!\n");
                        goto enter_ch;
    }
             printf("\n\n\t\t\t\t\t\t\t\t\t##***\tY O U R  D E C K  O F   C A R D S\t***##\n\n\n");
             display(userDeck);
             printf("\n\n");
compTurn:    printf("\n\n\n****\tM Y  T U R N     ****\n");
compTurnAgn: printf("__________________________________\n");
Sleep(1000);

    if(computerChance(&compDeck,&stackThrown,&masterStack)){
        printf("\n");
        if(compDeck==NULL){
                Sleep(1000);
                printf("\n\n*************\t\t\t\t I   W O N\t\t\t*******************\n\n");
                Sleep(1000);
                printf("\n\n********\t\t\tB E T T E R   L U C K   N E X T   T I M E\t\t\t***********\n\n");
                getchar();
                freeNodes(&stackThrown);
                freeNodes(&userDeck);
                freeNodes(&compDeck);
                freeNodes(&masterStack);

                exit(0);
                }
        else if((strcmp(stackThrown->cardType,"Draw4")==0)&&stackThrown->flag==0){
                    stackThrown->flag=1;
                    temp=stackThrown;
                    Sleep(1000);
                printf("\t!! H A R D Luck C H A M P SURPRISE :-D !\n\n\t*** DRAW 4 CARDS  ***\n\n");
                printf("\n\n\t\t\t\t\t\t\t##***\tY O U R   D E C K   O F   C A R D S\t***##\n\n\n");

                display(userDeck);


                     Sleep(1000);
           drawRead4:printf("\n\nPress 1 to THROW A DRAW4 CARD");
                    printf("\n\nPress 2 to DRAW 4 CARDS");
                    printf("\n\nPress 3 for HElP\n\n");
                    scanf("%d",&ch);
                    switch(ch){
                        case 1: printf("Enter the position of the card as displayed above\n");
                                scanf("%d",&pos);
                                if(pos<1||pos>length(userDeck)){
                                printf("Invalid position! Card does not exist\n");
                                goto drawRead4;
                                }
                                thrown=deleteAtpos(&userDeck,pos);
                                if(strcmp(thrown->cardType,"Draw4")!=0)
                                {
                                    Sleep(1000);
                                    printf("***  Ah!Dare not throw the invalid card!! ***\n");
                                    Sleep(1000);
                                    printf("***\n\n\n   YOU CAN ONLY THROW A DRAW4 CARD    ***\n");
                                    insertRear(&userDeck,thrown->color,thrown->cardType);
                                    free(thrown);
                                    goto drawRead4;
                                }
                                goto printThrown;
                                break;
                        case 2:for(i=0;i<4;i++)
                                    add_card(&userDeck,&masterStack);
                        printf("\n\nD R A W I N G. . . . .\n\n");
                        Sleep(1000);
                        printf("\n\n*** Successfully Drawn 4 cards ***\n\n");
                                break;
                        case 3:fp=fopen("rules.c","r");
                                while(!feof(fp)){
                                    c=getc(fp);
                                    putc(c,stdout);
                                    }
                                fclose(fp);
                                goto drawRead4;
                                break;
                        default:printf("Invalid choice mate !!\n");
                            goto drawRead4;
                    }
                    goto compTurn;
        }
        else if(strcmp(stackThrown->cardType,"Skip")==0&&stackThrown->flag==0)
        {
            stackThrown->flag=1;
            Sleep(1000);
            printf("\n\n***** S K I P *****\n\n");
            Sleep(1000);
            printf("*** It's MY TURN AGAIN ***\n\n");
            goto compTurnAgn;

        }
        else if(strcmp(stackThrown->cardType,"Wild")==0&&stackThrown->flag==0){
                stackThrown->flag=1;
                Sleep(1000);
                printf("*** THROW A  W I L D  CARD OR ANY CARD OF  W I L D  COLOR ***\n\n");
                Sleep(1000);
                printf("\n\n\t\t\t\t\t\t\t##***\tY O U R   D E C K   O F   C A R D S\t***##\n\n\n");

                display(userDeck);


                Sleep(1000);
                 WRead:printf("\n\nPress 1 to THROW A WILD CARD Or Same color Card ");
                    printf("\n\nPress 2 to pick up a card ");
                    printf("\n\nPress 3 for HELP\n\n");
                    scanf("%d",&ch);
                    switch(ch){
                        case 1: printf("Enter the position of the card as displayed above\n");
                                scanf("%d",&pos);
                                if(pos<1||pos>length(userDeck)){
                                printf("Invalid position! Card does not exist\n");
                                goto WRead;
                                }
                                thrown=deleteAtpos(&userDeck,pos);
                                if((strcmp(thrown->cardType,"Wild")!=0 )&&thrown->color!=stackThrown->color)
                                {
                                    Sleep(1000);
                                    printf("***  A h !  Dare   not   throw   the   invalid   card!! ***\n");
                                    Sleep(1000);
                                    printf("***\n\n THROW A  W I L D  C A R D  OR  A   C A R D   OF SAME COLOR ***\n");
                                    insertRear(&userDeck,thrown->color,thrown->cardType);
                                    free(thrown);
                                    goto WRead;
                                }
                                Sleep(1000);
                                goto printThrown;
                                break;
                        case 2:
                                add_card(&userDeck,&masterStack);
                                printf("\n\nD R A W I N G . . . . . \n");
                                Sleep(1000);

                                printf("\n\n*** Successfully Drawn a card ***\n\n");
                                break;
                        case 3:fp=fopen("rules.c","r");
                                while(!feof(fp)){
                                    c=getc(fp);
                                    putc(c,stdout);
                                }
                                fclose(fp);
                                goto WRead;
                                break;
                        default:printf("Invalid choice mate !!\n");
                            goto WRead;
                    }
                    goto compTurn;
                }



        else if((strcmp(stackThrown->cardType,"Draw2")==0)&&stackThrown->flag==0){
                    stackThrown->flag=1;
                    temp=stackThrown;
                    Sleep(1000);
                printf("\tHaha!! Bad Luck !\n\n\t*** DRAW 2 CARDS  ***\n\n");
                printf("\n\n\t\t\t\t\t\t\t##***\tY O U R   D E C K   O F   C A R D S\t***##\n\n\n");

           display(userDeck);



           drawRead:printf("\n\nPress 1 to THROW A DRAW2 CARD\n");
                    printf("\nPress 2 to DRAW 2 CARDS \n");
                    printf("\nPress 3 for HELP\n\n");
                    scanf("%d",&ch);
                    switch(ch){
                        case 1: printf("Enter the position of the card as displayed above\n");
                                scanf("%d",&pos);
                                if(pos<1||pos>length(userDeck)){
                                printf("Invalid position! Card does not exist\n");
                                goto drawRead;
                                }
                                thrown=deleteAtpos(&userDeck,pos);
                                if(strcmp(thrown->cardType,"Draw2")!=0)
                                {
                                    Sleep(1000);
                                    printf("***  Ah!Dare not throw the invalid card!! ***\n");
                                    Sleep(1000);
                                    printf("***\n\n   YOU CAN ONLY THROW A DRAW2 CARD    ***\n");
                                    insertRear(&userDeck,thrown->color,thrown->cardType);
                                    free(thrown);
                                    goto drawRead;
                                }
                                goto printThrown;
                                break;
                        case 2:for(i=0;i<2;i++)
                                    add_card(&userDeck,&masterStack);
                        printf("\n\nD R A W I N G . . . . \n\n");
                        Sleep(1000);
                        printf("\n\n*** Successfully Drawn 2 cards ***\n\n");
                                break;
                        case 3:fp=fopen("rules.c","r");
                                 while(!feof(fp)){
                                    c=getc(fp);
                                    putc(c,stdout);
                                }
                                fclose(fp);
                                goto drawRead;
                                break;
                        default:printf("Invalid choice mate !!\n");
                            goto drawRead;
                    }
                    goto compTurn;
                }
            else
                goto enter_ch;


    }

return 0;
}



