#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct header
{
  char riff[4];
  int fsize;
  char file_type[4];
  char format_chunk[4];
  int chunk_size;
  int format_type;
  int channel_number;
  int samples_per_second;
  int bits_per_second;
  int audio_type;
  int bits_per_sample;
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
				printf("Error");
				return 0;
			}
			fread(&fheader, fheader_size, 1, file);
			int file_length=sizeof(file);
			fclose(file);

			printf("RIFF: %c%c%c%c\n", fheader.riff[0], fheader.riff[1], fheader.riff[2], fheader.riff[3]);
			
		        
	}
	
	return 0;
}
