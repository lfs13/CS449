#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int grade;
	struct Node *next;
};

int main()
{	
	int i=0;
	float avg=0;
	int count=0;
	struct Node *last;
	last== NULL;
	struct Node *root=last;
	struct Node *curr;

	printf("Enter integers:");
	while(i!=-1)
	{	
		scanf("%d",&i);
		curr =(struct Node *)malloc(sizeof(curr));
		if(curr == NULL)
		{
			printf("error");
			break;
		}
		if(i== -1)
			break;
		curr->grade=i;
		last->next=curr;
		last=curr;
	}
	
	curr=&root;
	
	while(curr)
	{
		avg+=curr.grade;	
		count++;
	}
	printf("%f\n",avg/count);
return 0;
}
		
