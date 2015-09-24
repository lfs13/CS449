#include <stdio.h>
#include <stdlib.h>
#include <linux/random.h>
#include <time.h>
#include <string.h>

#ifndef HEADER
#define HEADER
void storeUpper(int a, unsigned char *p);
unsigned char get_random_byte();
void roll_all(unsigned char *);
int compare(const void *, const void *);
void three_pair(unsigned char *);
void four_pair(unsigned char *);
void full_house(unsigned char *);
void small(unsigned char *);
void large(unsigned char *);
void yahtzee_check(unsigned char *);
void chance(unsigned char *);
void r(int count, unsigned char * p);
int upperFilled();
#endif

int total_score = 0; //track total score for game, so i dont have to send another pointer as a parameter,or have a return value from each check function
int upper[]={-1,-1,-1,-1,-1,-1};
int lower[]={-1,-1,-1,-1,-1,-1,-1};
FILE * dev_file;

int main()
{
	int i=0; //loop counter
	int j=0;  //loop counter
	unsigned char roll[5]; //keeps track of current roll	
	unsigned char * roll_pointer= roll; //pointer to dice array
	srand (time(NULL)); //initialize random for predriver yahtzee
	dev_file = fopen("/dev/dice", "r");
	
	for(i=0;i<13;i++)
	{
		char reroll[5];//checks which dice to reroll
		int new_rolls = 0;
		int struct_section = 0;
		int section = 0;
		
		//-----------------------------ROLL1------------------------------//	
	
		//roll_all(roll_pointer);
		r(5,roll_pointer);
		
		printf("Your roll:\n");
		int j=0;
		for(j=0;j<5;j++)
		{
			printf("%d ",roll[j]);
		}
		
		printf("\n");
		
		//---------------------------------ROLL2------------------------------//
		
		printf("%s","Which dice to reroll?\n");
		scanf("%s",&reroll);
		new_rolls=strlen(reroll);
		
		if(strcmp(reroll,"0")!=0)
		{
			for(j=0;j<new_rolls;j++)
			{	
				int index = (int)(((reroll[j])-1)-'0');				
				//roll[index]=get_random_byte();
				r(1,roll_pointer+index);
			}		


			printf("Your second roll:\n");
        		for(j=0;j<5;j++)
        		{
        			printf("%d ",roll[j]);
        		}
		}
		else
		{
			printf("Your second roll:\n");
                        for(j=0;j<5;j++)
                        {
                                printf("%d ",roll[j]);
                        }
		}

		printf("\n");
		

		//-----------------------------ROLL3------------------------------//
                
		printf("%s","Which dice to reroll?\n");
                scanf("%s",&reroll);
                new_rolls=strlen(reroll);
		
		if(strcmp(reroll,"0")!=0)
		{
                	for(j=0;j<new_rolls;j++)
                	{	
                        	int index = (int)(((reroll[j])-1)-'0');
                        	//roll[index]=get_random_byte();
				r(1,roll_pointer+index);
                	}


                	printf("Your third roll:\n");
                	for(j=0;j<5;j++)
                	{
                        	printf("%d ",roll[j]);
                	}
		}
		else
                {
                        printf("Your second roll:\n");
                        for(j=0;j<5;j++)
                        {
                                printf("%d ",roll[j]);
                        }
                }

                printf("\n");

		//-----------------------------SORT------------------------------//
		
        	qsort(roll,5,sizeof(char),compare);

	
		//------------------------ASSIGN_POINTS-------------------------//
		
		printf("%s\n","Place dice into:");
		printf("%s\n","1) Upper Section");
		printf("%s\n\n","2) Lower Section");		
	
		printf("%s","Selection?");
		scanf("%d", &struct_section);

		printf("%s","\n");
		
		if(struct_section == 1)
		{
			printf("%s\n","Place dice into:");
                	if(upper[0] == -1)
			printf("%s\n","1) Ones");
                	if(upper[1] == -1)
			printf("%s\n","2) Twos");
			if(upper[2] == -1)
			printf("%s\n","3) Threes");
			if(upper[3] == -1)
			printf("%s\n","4) Fours");
			if(upper[4] == -1)
			printf("%s\n","5) Fives");
			if(upper[5] == -1)
			printf("%s\n\n","6) Sixes");
			
			do
			{
			printf("%s","Selection?");
                	scanf("%d",&section);
			}while(upper[section-1] != -1);
				
            		//wrong argument num
			storeUpper(section,roll_pointer);
			
		}
		if(struct_section == 2)
		{	
			printf("%s\n","Place dice into:");
                        if(lower[0]==-1)
			printf("%s\n","1) Three of a Kind");
                        if(lower[1]==-1)
			printf("%s\n","2) Four of a Kind");
                        if(lower[2]==-1)
			printf("%s\n","3) Full House");
                        if(lower[3]==-1)
			printf("%s\n","4) Small Straight");
                        if(lower[4]==-1)
			printf("%s\n","5) Large Straight");
                        if(lower[5]==-1)
			printf("%s\n","6) Yahtzee");
			if(lower[6]==-1)
			printf("%s\n\n","7) Chance");
			
			do
			{
			printf("%s","Selection?");
                	scanf("%d",&section);
			}while(lower[section-1] != -1);
			
	
                       
                        if(section==1)
			{
				three_pair(roll_pointer);
			}
			else if(section==2)
			{
				four_pair(roll_pointer);
			}
			else if(section==3)
			{
				full_house(roll_pointer);
			}
			else if(section==4)
			{
				small(roll_pointer);
			}
			else if (section==5)
			{
				large(roll_pointer);
			}
			else if(section==6)
			{
				yahtzee_check(roll_pointer);
			}
			else
			{
				chance(roll_pointer);
			}
                        
		}
		
		//-----------------------------TURN_OUTPUT------------------------------//
	
		
		printf("Your score so far is: %d\n", total_score);


	}
	
	i=0;
        int bonus=0;
        for(i=0; i<6; i++)
        {
		bonus+=upper[i];
        }
	if(bonus>=63)
	{
		total_score += 35;
	}
	
	printf("Your final score so is: %d\n", total_score);
		
	return 0;
			
}


void roll_all(unsigned char *p)
{
	int j=0;
        for(j=0;j<5;j++)
        {
        	p[j]= get_random_byte();
        }
}

unsigned char get_random_byte()
{
	int r =(unsigned char) rand() % 6 + 1;
	return r;
}

void r(int count, unsigned char * p)
{
	fread(p,1,count,dev_file);	

}

int compare(const void *a, const void *b) 
{
  return *(char*)a - *(char*)b;
}


void three_pair(unsigned char *p)
{
	int i=0;
	int count=0;
	int pair=0;
	int a=0;
	int total=0;
	for(i=0;i<3;i++)
	{
		int check=(int)p[i];
		if(((int)p[i+1])==check && ((int)p[i+2])==check)
		{
			pair=1;
			a=(int)p[i];
			break;
		}
	}
	if(pair==1)
	{
               	total += 3 * a;
		lower[0]=total;
		total_score += total;
	}
	else
	{
		lower[0]=0;
	}

}

void four_pair(unsigned char *p)
{
	int i = 0;
        int count = 0;
        int pair = 0;
	int a = 0;
        int total = 0;
        for(i=0;i<2;i++)
        {
                int check=(int)p[i];
                if(p[i+1]==check && p[i+2]==check && p[i+3]==check)
                {
                        pair=1;
			a=(int)p[i];
			break;
                }
        }
	if(pair==1)
        {
                total += 4 * a;
                lower[1] = total;
		total_score += total;
        }
	else
	{
		lower[1]=0;
	}
}

void full_house(unsigned char *p)
{
	int two = 0;
	int triple = 0;
	int i = 0;
	if((p[0]==p[1])&&(p[0]==p[2])&&(p[0]==p[3]))
	{
		triple==1;
	}
	else if((p[0]==p[1])&&(p[0]==p[2]))
	{
		two==1;
	}
	else{}

	if(triple==1)
	{
		if((p[3]==p[4])&&(p[3]==p[5]))
		{
			two==1;
		}
	}
	else if(two==1)
	{
		if((p[2]==p[3])&&(p[2]==p[4])&&(p[2]==p[5]))
		{
			triple==1;
		}
	}
	else{}

	if(triple==1 && two==0)
	{
		lower[2]=25;
		total_score += 25;
	}
	else
	{
		lower[2]=0;
	}

}

void small(unsigned char *p)
{
	int i=0;
        int straight=1;
        for(i=0;i<4;i++)
        {
                if((p[i+1]-p[i])!=1)
                {
                        straight=0;
                        break;
                }
        }
        
	if(straight=1)
        {
                lower[3]=30;
		total_score += 30;
        }
	else
	{
		lower[3] = 0;
        }
}

void large(unsigned char *p)
{
	int i=0;
	int straight=1;
	for(i=0;i<5;i++)
	{
		if((p[i+1]-p[i])!=1)
		{
			straight=0;
			break;
		}
	}
	if(straight=1)
	{
		lower[4]=40;
		total_score += 40;
	}
	else
	{
		lower[4]=0;
	}		
}

void yahtzee_check(unsigned char *p)
{
	if((p[0]==p[1])&&(p[0]==p[2])&&(p[0]==p[3])&&(p[0]==p[4]))
	{
		lower[5]=50;
		total_score += 50;
	}
	else
	{
		lower[5]=0;
	}

}

void chance(unsigned char *p)
{
	int i = 0;
	int total = 0;
	for(i=0;i<5;i++)
	{
		total += (((int)p[i]));
		printf("Total: %d\n",total);
	}
	lower[6]=total;
	total_score += total;
}
	
void storeUpper(int a, unsigned char *p)
{
	int i = 0;
	int total = 0;
	for(i=0; i<5; i++)
	{
		if(((int)p[i])==a)
		{
			total+=a;
		}
	}
	upper[a-1] = total;
	total_score += total;
}

int upperFilled()
{
	int i=0;
	int full=1;
	for(i=0; i<6; i++)
	{
		if(upper[i] == -1)
		{
			full = 0;
			break;
		}
	}
	return full;
}
