
/* This program is written in its entirety by Louis Seefeld without the intent of plagiarism. */
#include <stdlib.h>
#include<stdio.h>


struct header
{
	char start[2];
	char app1[2];
	char length[2];
	char exif[4];
	char zero[2];
	char ii[2];
	char version[2];
	char offset[4];
};

struct tiff
{
	unsigned char id[2];
	unsigned char type[2];
	unsigned char num[4];
	unsigned char val[4];
};
	
//PROTOTYPES
void exif_sub(FILE*);

//MAIN
int main(int argc, char **argv)
{
	//Create File
	FILE *input = fopen(argv[1],"r");
	
	//Check File
	if(input==NULL)
	{
		printf("ERROR:File Not Valid");
		exit(0);
	}

	//Create and File Header
        struct header h;
        fread(&h,1,sizeof(h),input);
	
	//Check for APP1
	if(!((*(unsigned short*)(h.app1)) == 0xE1FF))
	{
		printf("ERROR:Cannot Verify App1\n");
		return 0;
	}

	//Check Endianness
	if((short)h.ii[0]==49)
	{
	printf("ERROR:Image Endianness Not Supported\n");
	return 0;
	}
	
	//Get Count Variable
	unsigned short count;
	fread(&count,1,sizeof(count),input);
	
	//Loop Check Variable	
	int i;  
	
	//Tag Struct Instance
	struct tiff tag;
	
	//Loop and Check for Exif Tags
	for(i=0;i<count;i++)
	{	
		//Read 12 Bytes of Tag
		fread(&tag,1,sizeof(tag),input);
		
		if((*(unsigned short*)(tag.id)) == 0x010f)
		{
			char man[100];
			long int curr = ftell(input);
			fseek(input,tag.val[0]+12,SEEK_SET);
			fread(&man,1,*tag.num,input);
			fseek(input,curr,SEEK_SET);
			printf("Manufacturer:            ");
			printf("%s\n",man);
		}
		if((*(unsigned short*)(tag.id)) == 0x110)
		{
			char model[100];
                        long int curr = ftell(input);
                        fseek(input,tag.val[0]+12,SEEK_SET);                                
			fread(&model,1,*tag.num,input);
                        fseek(input,curr,SEEK_SET);
			printf("Model:                   ");
                        printf("%s\n",model);
                }
		if((*(unsigned short*)(tag.id)) == 0x8769)
                {
			
			//Get Exif Sub Offset
			int offset = *(int*)tag.val;
			
			//Seek To Exif Sub
			fseek(input,12+offset,SEEK_SET);
			
			//Check Sub Tags
			exif_sub(input);
			
			//Break on Return
			break;			
           	}	
        }
	
	//Close File and Exit Program
	fclose(input);
	return 0; 		
}

//Loop Through Sub Tags
void exif_sub(FILE* input)
{	
	struct tiff tag;
	int width;
	int height;
	unsigned short count;
	
	//Read In Count
	fread(&count,1,sizeof(short),input);
	int j;
	for(j=0;j<count;j++)
	{
        	//Read Next Tag
		fread(&tag,1,sizeof(tag),input);
					
		if((*(unsigned short*)(tag.id)) == 0xA002)
		{	
			printf("%s","Width:                   ");
			printf("%d",(*(int*)(tag.val)));
			printf(" pixels\n");
		}
		if((*(unsigned short*)(tag.id)) == 0xA003)
		{
			printf("%s","Height:                  ");
			printf("%d", (*(int*)(tag.val)));
			printf(" pixels\n");
        	}                        
		if((*(unsigned short*)(tag.id)) == 0x8827)                                       
		{
                        printf("%s","ISO:                     ");
                        printf("ISO %d",(*(int*)(tag.val)));
                        printf("\n");
        	}
		if((*(unsigned short*)(tag.id))== 0x829a)
        	{
			unsigned int r1;
                        unsigned int r2;
                        float ratio;
                        int offset = *(int*)tag.val;
                        long int curr = ftell(input);
                        fseek(input,offset+12,SEEK_SET);
                        fread(&r1,1,sizeof(r1),input);
                        fread(&r2,1,sizeof(r2),input);
                        fseek(input,curr,SEEK_SET);
                        printf("Exposure Time:           ");
                        printf("%d/%d second(s)\n",r1,r2);
        	}                       
		if((*(unsigned short*)(tag.id)) == 0x829d)
        	{       // Get Ratio 
			unsigned int r1;
			unsigned int r2;
			float ratio;                 
			int offset = *(int*)tag.val;	
			long int curr = ftell(input);
                        fseek(input,offset+12,SEEK_SET);
			fread(&r1,1,sizeof(r1),input);
			fread(&r2,1,sizeof(r2),input);
			fseek(input,curr,SEEK_SET);
			ratio=(float)r1/(float)r2;
			printf("F-Stop:                  ");
			printf("f/%.1f\n",ratio);
        	}                       
		if((*(unsigned short*)(tag.id)) == 0x920A)
        	{                        
			unsigned int r1;
                        unsigned int r2;
                        float ratio;
                        int offset = *(int*)tag.val;
                        long int curr = ftell(input);
                        fseek(input,offset+12,SEEK_SET);
                        fread(&r1,1,sizeof(r1),input);
                        fread(&r2,1,sizeof(r2),input);
                        fseek(input,curr,SEEK_SET);
                        ratio=(float)r1/(float)r2;
                        printf("Focal Length:            ");
                        printf("%.1f mm\n",ratio);
        	}
		if((*(unsigned short*)(tag.id)) == 0x9003)
        	{                        
			int offset = *(int*)tag.val;
			char date[20];
			long int curr = ftell(input);
                        fseek(input,offset+12,SEEK_SET);
                        fread(&date,1,*tag.num,input);
                        fseek(input,curr,SEEK_SET);
			printf("Date:                    ");
                        printf("%s\n",date);
        	}
	}                       

}
	
	
