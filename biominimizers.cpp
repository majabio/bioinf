#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void Minimizers(char*, int, int);


int main(int argc, char *argv[]) //kao argumente saljemo ime datoteke, w i k
{
	
	FILE *f;
	char* file_name=argv[1];
	char *buffer = 0; //buffer u koji ce se spremiti sadrzaj datoteke kao niz
	int length; //duljina buffera
	int w=atoi(argv[2]); //sirina prozora
	int k=atoi(argv[3]); //broj znakova k-mera

	f = fopen(file_name, "r");
	
	if(!f)
		printf("\n Datoteka se nije uspjesno otvorila");
	else
	{
	//trazimo kraj datoteke pa tako i njenu duljinu,a onda se vracamo na pocetak datoteke
		fseek (f, 0, SEEK_END);
		length = ftell (f);
		fseek (f, 0, SEEK_SET);
		buffer = (char*)malloc(length); 
	
	//spremamo sadrzaj datoteke u buffer kao niz
	
		if (buffer)
		{
			fread(buffer, 1, length, f);
			buffer[length]= '\0';
			printf("\nbuffer je %s\n", buffer);
		}
	}

	fclose(f);

	Minimizers(buffer, w, k); //funnkcija koja trazi minimizere

	return 0;
}

void Minimizers(char* buffer, int w, int k)
{
 
	char* squ_substring = 0; //podsekvenca niza(buffera)
	char* k_substring = 0; //svaki susjedni k-mer
	char* min_k_substring = 0; //minimizer-minimalni podstring
	int squ_number = 0; //broj sekvenci unutar niza
	int squ_length = 0; //duljina sekvence
	int min_index = 0; //indeks minimalnog podstringa u podsekvenci
	char* end_minimizer = 0; //svaki susjedni end k-mer
	char* min_end_minimizer = 0; //minimialni end podstring
	
	
	//izracunajemo duljinu podsekvence i broj podsekvenci u nizu
	squ_length = (w + k - 1); 
	squ_number = strlen(buffer) - squ_length + 1; 


	if(squ_length > strlen(buffer))
		printf("Unijeli ste nemoguce vrijednosti");//l=w+k-1, tako da w+k-1 ne moze biti veci od sekvence

	//alociramo potrebni memorijski prostor za velicine
	squ_substring = (char*)malloc(squ_length);
	k_substring = (char*)malloc(k);
	min_k_substring = (char*)malloc(k);
	end_minimizer = (char*)malloc(k);
	min_end_minimizer = (char*)malloc(k);

	//trazimo minimizere

	for(int i=0;i<squ_number;i++) //uzimaju se susjedne sekvence dok i!=squ_number
	{
		strncpy(squ_substring,buffer+i,squ_length); //nalazimo posekvencu
		squ_substring[squ_length]= '\0';
		printf("\n\nsubstring je %s", squ_substring);

		strncpy(min_k_substring,squ_substring,k); //postavljamo prvi k-mer na minimalni
		min_k_substring[k]='\0';
		printf("\npocetni je %s", min_k_substring);

		//uzimamo susjedne k-mere i ako je susjedni manji od prethodnog on postaje minimalni
		for(int j=0;j<w;j++)
		{
			strncpy(k_substring,squ_substring+j,k);
			k_substring[k]='\0';
			printf("\nk_substring je %s", k_substring);
			
			if(strcmp(k_substring,min_k_substring) < 0)
			{
				strncpy(min_k_substring,k_substring,k);
				min_index=j; //spremamo indeks minimalnog
			}
		}
		
		if(i==0) //provjera za lijeve end minimizere
		{
			strncpy(min_end_minimizer,squ_substring,k);
			min_end_minimizer[k]='\0';

			printf("\nend minimizer je %s", min_end_minimizer);//ispisuje prvi k-mer, posto je on svakako lijevi end minimizer

			for(int j=0;j<min_index;j++) //ako je susjedni k-mer manji, postaje i on minimizer
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

		if (i == squ_number - 1) //trazimo za desni kraj sekvence, slicno kao za lijevi, samo obrnuto
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
