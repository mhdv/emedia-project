#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct header
{
  char riff[4];
  float fsize;
  char file_type[4];
  char format_chunk[4];
  int chunk_size;
  short int format_type;
  short int channel_number;
  int samples_per_second;
  int bits_per_second;
  short int audio_type;
  short int bits_per_sample;
  char data[4];
  int data_length;
}hdr;


int main(int argc, char *argv[])
{
	int c;
	
	
	if(!argv[1]){
		printf("Error: first argument not found.\n");
		return 0;
	}else if(strstr(argv[1],".") == NULL){
		printf("Error: this app can handle only wav files.\n");
		return 0;
	}else if(strstr(argv[1],".") != NULL){
		if(strcmp(strrchr(argv[1],'.')+1, "wav") != 0){
			printf("Error: this app can handle only wav files.\n");
			return 0;
		}
			// BODY OF APP

			hdr fheader;
			int fheader_size=sizeof(fheader);

			FILE *file;

			if((file=fopen(argv[1], "r")) == NULL){
				printf("Error: file could not be opened.");
				return 0;
			}

			fread(&fheader, fheader_size, 1, file);
			int file_length=sizeof(file);
			fclose(file);


			// FILE INFORMATION DISPLAY

			printf("RIFF: \t\t\t");
			int i=0;
			for(i; i<4; ++i){
				printf("%c", fheader.riff[i]);
			}
			printf("\nFile type: \t\t");

			i=0;
			for(i; i<4; ++i){
				printf("%c", fheader.file_type[i]);
			}
			printf("\nFormat chunk: \t\t");

			i=0;
			for(i; i<4; ++i){
				printf("%c", fheader.format_chunk[i]);
			}
			printf("\nData: \t\t\t");

			i=0;
			for(i; i<4; ++i){
				printf("%c", fheader.data[i]);
			}
			printf("\n");
			
			printf("Frequency: \t\t%i Hz\n", fheader.samples_per_second);
			printf("Bits per second: \t%i\n", fheader.bits_per_second);
			printf("Number of channels: \t%i\n", fheader.channel_number);
			printf("Chunk size: \t\t%i\n", fheader.chunk_size);
			printf("Data length: \t\t%i KB\n", fheader.data_length/1024);
		        
	}
	
	return 0;
}
