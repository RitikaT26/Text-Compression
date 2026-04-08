#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_WORDS 10000
#define MAX_LEN 1000

void normcmp(const char *src, char *dst)
{
	int len= (int)strlen(src);
	int s=0, e=len-1;
	while (s<=e && !isalnum(src[s])) s++;
	while (e>=s && !isalnum(src[e])) e--;
	int j=0;
	for (int k=s; k<=e;++k) dst[j++]=(char)tolower(src[k]);
	dst[j]='\0';
}

void processLine(char *l, FILE *outf)
{
	char prevword[MAX_LEN]="";
	char proc[MAX_LEN]="", buf[MAX_LEN];
	
	//remove leading/trailing spaces
	int start=0, end=strlen(l)-1;
	while (isspace(l[start])) start++;
	while (end>=start && isspace(l[end])) end--;
	l[end+1] = '\0';
	
	//skip blank lines
	if (strlen(l+start)==0)
		return;
	strcpy(buf, l+start);
	
	//tokenise lines by spaces
	strncpy(buf, l+start, MAX_LEN-1);
	buf[MAX_LEN-1]='\0';
	char prevcmp[MAX_LEN]="";
	char *token= strtok(buf, " \t\n");
	int wa=0;
	
	while (token != NULL)
	{
		char word[MAX_LEN];
		normcmp(token,word);
		
		if (strcmp(prevcmp,word) != 0)
		{
			if (wa)
				fprintf(outf," %s",token);
			else
			{
				fprintf(outf," %s",token);
				wa=1;
			}
			strcpy(prevcmp,word);
		}
		token= strtok(NULL, " \t\n");
	}
	if (wa) fprintf(outf,"");
	//remove trailing space
	int len= strlen(proc);
	if (len>0 && proc[len-1] == ' ')
		proc[len-1]='\0';
	fprintf(outf, "%s\n", proc);
}

int main()
{
	FILE *inf, *outf;
	char line[MAX_LEN];
	
	inf= fopen("input.txt","r");
	if (inf==NULL)
	{
		printf("Error: Cannot open input file.\n");
		return 1;
	}
	printf("File Reading Successful.\n");
	
	outf= fopen("compressed.txt","w");
	if (outf==NULL)
	{
		printf("Error: Cannot create output file.\n");
		fclose(inf);
		return 1;
	}
	
	while (fgets(line, sizeof(line), inf))
		processLine(line, outf);
		
	fclose(inf);
	fclose(outf);
	
	printf("Compression complete! Output saved to compressed.txt.\n");
	return 0;
}
