//all code written by Louis Seefeld for cs449 without the intention of plagarism
//---------------CAVEATS---------------------//
//This program is not going to be runnable most likely.
//The bank of headers is treated like actual nodes at this point which is wrong.
//This is prety much the worst project attempt I have ever submitted and I apologize that you have to witness such coding.
//-Cheers



#include<stdio.h>
#include<stdlib.h>
#include <sys/mman.h>


#define MAX_MEM 1<<30

struct node
{
	int free;			//is node free(0 yes, 1 no)
	int size;			//2^size of space
	struct node *next_node;		//pointer to next node
	struct node *previous_node;	//pointer to previous node
};

struct node headers[25];

struct node * curr;

int called=0;

void * base;



* my_buddy_malloc(int size)
{	
	if(called==0)
	{	
		called++;
		base = mmap(NULL,MAX_MEM,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANON,0,0);
		int i=0;
		for(i=0;i<24;i++)
		{
			headers[i].free=0;
			headers[i].size=i+5;
			headers[i].next_node=NULL;
			headers[i].previous_node=NULL;
		}
		headers[24].free=0;
		headers[24].size=29;
		headers[24].next_node=base;
		headers[24].previous_node=NULL;
		struct node init;
		init.free=0;
		init.size=30;
		init.next_node=NULL;
		init.previous_node=&headers[24];
	}	

	int new_size=size+sizeof(struct node);
	int power = getPower(new_size);
	int index= power-5;
	int free =0;

	if(headers[index].next_node==NULL)
		free=0;
	else
	{
		curr=headers[index].next_node;
		while(((struct node)*curr).next_node!=NULL)
		{
			if (((struct node)*curr).free==1)
				curr=((struct node)*curr).next_node;
			else
			{
				free=1;	
			}
		}
	}
	
	if(free==1)
	{
		((struct node)*curr).free=1;
		((struct node)*curr).size=power;
		return curr;
	}
	else
	{
		int split_count=0;
		while(headers[index].next_node==NULL)
		{
			split_count++;
			index++;
		}
		curr=(struct node *)headers[index].next_node;
		while(((struct node)*curr).next_node!=NULL)
		{
			if (((struct node)*curr).free==1)
                                curr=((struct node)*curr).next_node;
                        else
                        {
				//should return pointer to final split node
                                //return split(index,split_count);
				
				//return case for compilation purposes
				return curr;
                        }
		}
	}
	
	return NULL;			
}



my_free(void * ptr)
{
	curr=(struct node *)ptr;
	
	if(curr->next_node->free==1 && curr->previous_node->free==1)
	{
		curr->free=0;
	}
	else if(curr->next_node->free==0 && curr->previous_node->free==1)	//if next node is free and previous is not
	{
		curr->size+=curr->next_node->size;		//size of curr+= size of next
		curr->free=0;					//curr set to free
		curr->next_node=curr->next_node->next_node;	//set curr.next_node to 2 away
	}
	else if(curr->next_node->free==1 && curr->previous_node->free==0) //if previous node is free and next is not
	{
		curr->previous_node->next_node=curr->next_node;
		curr->previous_node->size+=curr->size;
		curr->free=0;
	}
	else
	{
		curr->previous_node->next_node=curr->next_node->next_node;
		curr->previous_node->size+=curr->next_node->size;
		curr->previous_node->size+=curr->size;
		curr->free=0;
	}
}


void * split(int index, int count)
{
	for(count;count>=0;count--)
	{
		index--;
		curr->free=0;
		curr->size=index;
		//realized here that my header bank implementation rendered split impossible: not enough time to fix
	}
	return curr;
	//should split nodes count times based on deviation from base power index
	//return pointer to first lowerst power node
	//if not possible return null
}


int getPower(int size)
{	
	
	int n=size;		//Get Power of 2 assuming 32-bit integer
        n--;
	n |= n >> 1;
        n |= n >> 2;
        n |= n >> 4;
        n |= n >> 8;
        n |= n >> 16;
        n++;
	
	if(n<5)		//return 5 if request is less than min, fragmentation but oh well
	return 5;

	return n;	//return closest power of 2(ceiling)
}

	

					
