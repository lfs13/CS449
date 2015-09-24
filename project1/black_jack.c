/*
 * This program was written in its entirety
 * by Louis Seefeld with no intent of plagarism.
 *
*/

/*----------------------------------Library Inclusions-----------------------*/
#include<stdio.h>
#include<string.h>

/*~---------------------------------Pr0t0types------------------------------~*/

int get_total(int[],int); //prototype of get_total: returns total hand value

/**---------------------------------Program Body----------------------------------------**/
int main()
{
	/*-----------------------Variable Declarations-----------------------*/
	srand((unsigned int)time(NULL));	/*seed the random number generator*/
	int deck[13]={2,3,4,5,6,7,8,9,10,10,10,10,11}; 	/*Create array for the deck*/
	int dealer_total=0;	/*Variable for dealer's hand count*/
	int player_total=0;	/*Variable for player's hand count*/
	int dealer_hand[8];	/*Array to hold dealer's values*/
	int player_hand[8];	/*Aray to hold player's values (both hands declared with [8], as that is the maximum number of cards that can be dealt in one hand)*/
	int dealer_aces=0;
	int player_aces=0;
	
	int dc=0;
	int pc=0;
	
	/*----------------------Deal 2 cards to dealer----------------------*/
	
	dealer_hand[0] = deck[ rand() % 13 ];
	dc++;
	dealer_hand[1] = deck[ rand() % 13 ];
	dc++;
	printf("Dealer:\n");
	printf("%d",dealer_hand[0]);
	printf(" + ?\n\n");
	dealer_total=get_total(dealer_hand,dc);

	/*-----------------------Deal 2 cards to player--------------------*/
        
	player_hand[0] = deck[ rand() % 13 ];
	pc++;
        player_hand[1] = deck[ rand() % 13 ];
	pc++;
        printf("You:\n");
        printf("%d",player_hand[0]);
        printf(" + ");
	printf("%d",player_hand[1]);
	player_total=get_total(player_hand,pc);
	printf(" = ");
	printf("%d\n\n",player_total);

	/*------------------------Player Loop-----------------------------*/
	
	do
	{	
		if(player_total==21)
		break;

		char choice[5];
		printf("Would you like to \"hit\" or \"stay\"?");
		scanf("%s",choice);
		printf("\n");
		if(strncmp(choice,"hit",5)==0)
		{
			/* Reprint Dealer Stats */
			printf("Dealer:\n");
        		printf("%d",dealer_hand[0]);
        		printf(" + ?\n\n");

			/* Get New Card and Reprint Player Stats */
			player_hand[pc]=deck[rand()%13];
			pc++;
			printf("You:\n");
			printf("%d",player_total);
			printf(" + ");
			printf("%d",player_hand[pc-1]);
			printf(" = ");
			player_total=get_total(player_hand,pc);
			printf("%d\n\n",player_total);
		}
		else
		{
			printf("You stay at %d\n\n",player_total);
			break;
		}
	}while(player_total<=21);
	
	/*--------------------------Break-if-Bust-------------------------*/
	
	if(player_total > 21)
	{
		printf("You bust, dealer wins.");
		return 0;

	}
	
	/*--------------------------Dealer Loop------------------------- */
	
	do
	{
		dealer_hand[dc]=deck[rand()%13];
		dc++;
		dealer_total=get_total(dealer_hand,dc);
	}while(dealer_total<17);
	
	printf("Dealer: ");
	printf("%d\n\n",dealer_total);
	printf("Player: ");
	printf("%d\n\n",player_total);
	
	if(player_total <= dealer_total && dealer_total<22)
	{
		printf("You lose.");
	}
	else
	{
		printf("You win.");
	}

	return 0;
}

int get_total(int a[], int num) /*Receives specified hand array, and number of cards in that array*/
{	
	int total=0;
	int i;
	for(i=0;i<num;i++)
	{
		if(a[i]==11 && total+11>21)
		{
			total+=1;
		}
		else
		{
			total+=a[i];
		}
	}
	return total;
}
			
		
