#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void processLine(char *l, FILE *out)
{
	char *token, *prevword=NULL;
	char proc[1000]="", buf[1000];
	
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
	token= strtok(buf, " \t\n");
	while (token != NULL)
	{
		if (prevword==NULL||strcmp(prevword,token) != 0)
		{
			strcat(proc, token);
			strcat(proc, " ");
		}
		prevword=token;
		token= strtok(NULL, " \t\n");
	}
	
	//remove trailing space
	int len= strlen(proc);
	if (len>0 && proc[len-1] == ' ')
		proc[len-1]='\0';
	fprintf(out, "%s\n", proc);
}

int main()
{
	FILE *inf, *outf;
	char line[1000];
	
	inf= fopen("input.txt","r");
	if (inf==NULL)
	{
		printf("Error: Cannot open input file.\n");
		return 1;
	}
	
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
