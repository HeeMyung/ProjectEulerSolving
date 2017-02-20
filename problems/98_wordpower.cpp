#include<stdio.h>
#include"bigint.h"
#include <set>

void charsort(char* sort)
{
	int k;
 	int countbuf[26] = {0,};
	char *temp = sort;
	while(*temp != '\0')
	{
		countbuf[*temp-'A']++;
		temp++;
	}

	for(k =0; k < 26; k++)
	{
		while(countbuf[k] > 0)
		{
			*sort = k+'A';
			sort++;
			countbuf[k]--;
		}
	}
	//*sort = '\0'; 
}

int main()
{
	FILE *inp;
	inp = fopen("words.txt","r");
	char buffer[100000];
	fgets(buffer,100000,inp);
	char *word;
	word = strtok(buffer,"\",\n");
	
	char wordlist[2000][30];


	std::set<std::string> realstr,sorted;

	std::string src;
	std::list<std::string> li;
	char *buff = (char*)calloc(30,sizeof(char));

	int count = 0;

	do{
		//printf("%s\n",word);
		src = (ELEMENT)word;
		realstr.insert(src);
		strcpy(buff,word);
		charsort(buff);
		if( stringIsIn(sorted,buff) == 1 )
		{
			strcpy(wordlist[count],word);
			src = stringLoad(sorted,buff);
			li = (LISTptr)src.ptr;
			listPushEnd(li,(ELEMENT)wordlist[count]);
			listIter(li,temp)
			{
				printf("%s ",*temp);
			}
			printf("\n");
			//getchar();
			count++;
		}
		else
		{
			li = newList();
			listPushEnd(li,(ELEMENT)word);
			stringStore(sorted,buff,(ELEMENT)(void*)li);
		}
		word = strtok(NULL,"\",\n");
	}while(word != NULL);



	printf("%d\n",count);


	free(buff);
}
