#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void Minimizers(char*, int, int);


int main(int argc, char *argv[]) //as arguments we send name od the file, w and k
{
	
	FILE *f;
	char* file_name=argv[1];
	char *buffer = 0; //buffer that we will save content of file into
	int length; //buffer length
	int w=atoi(argv[2]); //window width
	int k=atoi(argv[3]); //k-mer number of chars

	f = fopen(file_name, "r");
	
	if (!f)
		printf("\n Datoteka se nije uspjesno otvorila");
	else
	{
		//we search the end of file and its length and after that go back to start
		fseek (f, 0, SEEK_END);
		length = ftell (f);
		fseek (f, 0, SEEK_SET);
		buffer = (char*)malloc(length); 
	
		//saving file content in buffer as a string of characters
		if (buffer)
		{
			fread(buffer, 1, length, f);
			buffer[length]= '\0';
			printf("\nbuffer je %s\n", buffer);
		}
	}

	fclose(f);

	Minimizers(buffer, w, k); //function that searches for minimizers

	return 0;
}

void Minimizers(char* buffer, int w, int k)
{
 
	char* squ_substring = 0; //subsequence of buffer
	char* k_substring = 0; //neighbour k-mers
	char* min_k_substring = 0; //minimizer
	int squ_number = 0; //number of sequences in buffer
	int squ_length = 0; //sequence length
	int min_index = 0; //index of minimizer in subsequence
	char* end_minimizer = 0; //neighbour end k-mers
	char* min_end_minimizer = 0; //end minimizer
	
	
	//counting sequence lentgh and number of sequences  in buffer
	squ_length = (w + k - 1); 
	squ_number = strlen(buffer) - squ_length + 1; 


	if(squ_length > strlen(buffer))
		printf("Unijeli ste nemoguce vrijednosti");//l=w+k-1,  w+k-1 cant be larger than length of sequence

	//allocating memory
	squ_substring = (char*)malloc(squ_length);
	k_substring = (char*)malloc(k);
	min_k_substring = (char*)malloc(k);
	end_minimizer = (char*)malloc(k);
	min_end_minimizer = (char*)malloc(k);

	//looking for minimizers

	for(int i=0;i<squ_number;i++) //we are taking neighbour sequences until squ-number is not equal to i
	{
		strncpy(squ_substring,buffer+i,squ_length); //setting subsequences
		squ_substring[squ_length]= '\0';
		printf("\n\nsubstring je %s", squ_substring);

		strncpy(min_k_substring,squ_substring,k); //setting first k-mer to minimum one
		min_k_substring[k]='\0';
		printf("\npocetni je %s", min_k_substring);

		//if neighbour k-mer is smaller than current minimum one, than it becomes minimum one - minimizer
		for(int j=0;j<w;j++)
		{
			strncpy(k_substring,squ_substring+j,k);
			k_substring[k]='\0';
			printf("\nk_substring je %s", k_substring);
			
			if(strcmp(k_substring,min_k_substring) < 0)
			{
				strncpy(min_k_substring,k_substring,k);
				min_index=j; //saving index of minimizer
			}
		}
		
		if(i==0) //looking for left end minimizers
		{
			strncpy(min_end_minimizer,squ_substring,k);
			min_end_minimizer[k]='\0';

			printf("\nend minimizer je %s", min_end_minimizer);//printfs the first k-mer because it is 100% end-minimizer

			for(int j=0;j<min_index;j++) //if neighbour minimizer is smaller than current one than it too becomes minimizer
			{
				strncpy(end_minimizer,squ_substring+j,k);
				end_minimizer[k]='\0';
				if(strcmp(end_minimizer,min_end_minimizer) < 0)
				{
					strncpy(min_end_minimizer,end_minimizer,k);
					printf("\nend minimizer je %s", min_end_minimizer);
				}
			}
		}

		if (i == squ_number - 1) //looking for right end minimizers, similar to looking for left ones, just vice versa
		{
			strncpy(min_end_minimizer, (squ_substring + squ_length - k), k); 
			min_end_minimizer[k] = '\0';
			printf("\nend minimizer je %s", min_end_minimizer);

			for(int j = (squ_length - k - min_index) ; j > 0; j--) 
			{
				strncpy(end_minimizer, (squ_substring + j + min_index), k);
				end_minimizer[k] = '\0';

				if (strcmp(end_minimizer, min_end_minimizer) < 0)
				{
					strncpy(min_end_minimizer, end_minimizer, k);
					printf("\nend minimizer je %s", min_end_minimizer);
				}
			}
		}
			
		printf("\nindex minimalnog substringa (minimizera) je %d", min_index);
		printf("\nminimalni substring je %s", min_k_substring);
	}
}
