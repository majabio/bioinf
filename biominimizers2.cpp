#include<stdio.h>
//#include<conio.h>
#include<stdlib.h>
#include<string.h>


void Minimizers(char*, int, int);
//void EndMinimizers(char*, int);

int main(int argc, char *argv[])
{
	
	FILE* f;
	char* file_name=argv[1];
	char *buffer = 0;
    int length;
	int w=atoi(argv[2]);
	int k=atoi(argv[3]);

	/*printf("\n Upisite ime datoteke iz koje citate: ");
	scanf_s("%s", file_name, 1024);
	printf("\nUpisite zeljenu sirinu prozora (w): ");
	scanf_s("%d", &w, 1);
	printf("\nUpisite zeljeni broj slova substringa (k): ");
	scanf_s("%d", &k, 1);*/

	f = fopen(file_name, "r");
	if(!f) {
		printf("\n Datoteka se nije uspjesno otvorila");
	}
	else {
		fseek (f, 0, SEEK_END);
		length = ftell (f);
		printf("velicina je %d", length); 
		fseek (f, 0, SEEK_SET);

		buffer = (char*)malloc(length);
		printf("\nvelicina buffera ja %d", strlen(buffer)); 
	  
	  	if (buffer){
			fread(buffer, 1, length, f);
			buffer[length]= '\0';
			printf("\nbuffer je %s\n", buffer);
		}
	}
	fclose(f);

	Minimizers(buffer, w, k);
	//EndMinimizers(buffer,k);
}

void Minimizers(char* buffer, int w, int k)
{
   
	char* squ_substring=0;
	char* k_substring=0;
	char* min_k_substring=0;
	int squ_number=0; //broj sekvenci unutar stringa
	int squ_length=0; //duljina sekvence
	int min_index;
	char* end_minimizer=0;
	char* min_end_minimizer=0;
	
	squ_length= (w+k-1);
	squ_number= strlen(buffer)-squ_length+1;

	printf("\nsqu:lentgh je %d", squ_length);
	printf("\nsqunumber je %d\n", squ_number);

	//if(squ_length > strlen(buffer))
		//printf("Unijeli ste nemoguce vrijednosti");//l=w+k-1, tako da w+k-1 ne moze biti veci od sekvence
	squ_substring=(char*)malloc(squ_length);
	k_substring=(char*)malloc(k);
	min_k_substring=(char*)malloc(k);
	end_minimizer=(char*)malloc(k);
	min_end_minimizer=(char*)malloc(k);

	for(int i=0;i<squ_number;i++)
	{
		strncpy(squ_substring,buffer+i,squ_length);
		squ_substring[squ_length]= '\0';
		printf("\nsubstring je %s", squ_substring);
		
		strncpy(min_k_substring,squ_substring,k);
		min_k_substring[k]='\0';
		printf("\nzasada je %s", min_k_substring);

		
		for(int j=0;j<w;j++)
		{
			strncpy(k_substring,squ_substring+j,k);
			k_substring[k]='\0';
			printf("\nk_substring je %s", k_substring);
			   
			if(strcmp(k_substring,min_k_substring) < 0) {
			    strncpy(min_k_substring,k_substring,k);
		        min_index=j;
			}
		}
			
		if(i==0) //provjera za end minimizere
		{
			strncpy(min_end_minimizer,squ_substring,k);
			min_end_minimizer[k]='\0';
				

		    for(int j=0;j<min_index;j++)
			{
				strncpy(end_minimizer,squ_substring+j,k);
			    end_minimizer[k]='\0';
				if(strcmp(end_minimizer,min_end_minimizer) < 0)
				   strncpy(min_end_minimizer,end_minimizer,k);
				printf("\nend minimizer je %s", min_end_minimizer);
			}
			
		}

		if(i==(squ_number-1))
		{
			strncpy(end_minimizer,(squ_substring+squ_length-k),k);
			end_minimizer[k]='\0';
			printf("\nend minimizer je %s", end_minimizer);
		}


			
		printf("\nmini index je %d", min_index);
		printf("\n minimalni substring je %s", min_k_substring);
	}
	
	//printf("\nend minimizer je %s", min_end_minimizer);

}


/*void EndMinimizers(char* buffer, int k)
{
	int u;
	char* squ=0; 
	char* end_minimizer=0;
	char* min_end_minimizer=0;


	min_end_minimizer=(char*)malloc(k);
	end_minimizer=(char*)malloc(k);
	
	for(u=1;u <= (strlen(buffer)-k+1); u++)
	{
	   squ=(char*)malloc(k-1+u);
	   strncpy(squ,buffer,k-1+u);
	   squ[k-1+u]= '\0';
	   strncpy(min_end_minimizer,squ,k);
	   min_end_minimizer[k]='\0';

	   for(int i=0; i<u; i++)
	   {
	      strncpy(end_minimizer,squ+i,k);
		  end_minimizer[k]='\0';
		  if(strcmpi(min_end_minimizer,end_minimizer) > 0)
			  strncpy(min_end_minimizer, end_minimizer, k);
	   }

	   printf("\nmin_end_minimizer je %s", min_end_minimizer);


	
	}


}*/