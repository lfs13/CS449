#include <stdio.h>
#include <stdlib.h>



int getStringLength(FILE*);


int main(int argc, char **argv)
{
	//create file
	FILE *input = fopen(argv[1],"r");

	//check file
	if(input==NULL)
	{
		printf("ERROR: File does not exist.");
		exit(0);
	}
	
	//file exists, set variable to length of file
	fseek(input,0,SEEK_END);
	int file_length = ftell(input);
	fseek(input,0,SEEK_SET);

	while(ftell(input) < (file_length-3))
	{
		char head=0;				//short to store value of leading byte
		fread(&head,sizeof(head),1,input); 	//read in first byte of potential string

		if( ((unsigned char)(head)) >= 32 && ((unsigned char)(head)) <=126)
		{
			long int curr = ftell(input)-1;
			int string_length = getStringLength(input);

			if(string_length < 4)
			{	
				fseek(input,1,SEEK_CUR);
				continue;
			}
			else
			{
				fseek(input,curr,SEEK_SET);
				char string[string_length];
				fread(&string,sizeof(char),string_length,input);
				printf("%s\n", string);
			}
		}	
	}
	
	return 0;
}


int getStringLength(FILE *input)
{
	int count = 1;
	
	while(1<2)
	{
		char temp = 0;
		
		fread(&temp,sizeof(temp),1,input);
		
		if( ((unsigned char)(temp)) >= 32 && ((unsigned char)(temp)) <=126 )
			count++;
		else
			break;
	} 
	
	return count;
}
