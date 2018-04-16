#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
	int read = 0;
	
	
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
		FILE *info = fopen("../tmp/info.dat", "wb+");

		if((file=fopen(argv[1], "rb")) == NULL){
			printf("Error: file could not be opened.");
			return 0;
		}

		read = fread(&fheader, fheader_size, 1, file);
		int file_length=sizeof(file);


		// FILE INFORMATION DISPLAY

		printf("RIFF: \t\t\t");
		fprintf(info, "RIFF: \t\t\t");
		int i=0;
        
		printf("%.4s", fheader.riff);
		fprintf(info ,"%.4s", fheader.riff);
		
		printf("\nFile type: \t\t");
		fprintf(info, "\nFile type: \t\t");

		i=0;
	        
		printf("%.4s", fheader.file_type);
		fprintf(info, "%.4s", fheader.file_type);
		
		printf("\nFormat chunk: \t\t");
		fprintf(info, "\nFormat chunk: \t\t");

		i=0;
        
		printf("%.4s", fheader.format_chunk);
		fprintf(info, "%.4s", fheader.format_chunk);
		printf("\nData: \t\t\t");
		fprintf(info, "\nData: \t\t\t");

		i=0;
		
		printf("%.4s", fheader.data);
		fprintf(info,"%.4s", fheader.data);
		
		printf("\n");
		fprintf(info, "\n");
			
		printf("Frequency: \t\t%i Hz\n", fheader.samples_per_second);
		printf("Bits per second: \t%i\n", fheader.bits_per_second);
		printf("Number of channels: \t%i\n", fheader.channel_number);
		printf("Chunk size: \t\t%i\n", fheader.chunk_size);
		printf("Data length: \t\t%i KB\n", fheader.data_length/1024);
		fprintf(info, "Frequency: \t\t%i Hz\n", fheader.samples_per_second);
		fprintf(info, "Bits per second: \t%i\n", fheader.bits_per_second);
		fprintf(info, "Number of channels: \t%i\n", fheader.channel_number);
		fprintf(info, "Chunk size: \t\t%i\n", fheader.chunk_size);
		fprintf(info, "Data length: \t\t%i KB\n", fheader.data_length/1024);

		long sample_size = (fheader.channel_number * fheader.bits_per_sample)/8;
		fclose(info);

		if(fheader.format_type == 1)
		  {
		   	long i =0;
		char data_buffer[sample_size];
		int  size_is_correct = 1;

		// make sure that the bytes-per-sample is completely divisible by num.of channels
		long bytes_in_each_channel = (sample_size / fheader.channel_number);
		long num_samples = (8 * fheader.data_length) / (fheader.channel_number * fheader.bits_per_sample);


		FILE *ofile;
		ofile = fopen("sound2.wav", "wb");
		fwrite(&fheader, sizeof(fheader), 1, ofile);
		
		if (size_is_correct) { 
					// the valid amplitude range for values based on the bits per sample
			long low_limit = 0l;
			long high_limit = 0l;

			switch (fheader.bits_per_sample) {
				case 8:
					low_limit = -128;
					high_limit = 127;
					break;
				case 16:
					low_limit = -32768;
					high_limit = 32767;
					break;
				case 32:
					low_limit = -2147483648;
					high_limit = 2147483647;
					break;
			}					

			printf("\n\n.Valid range for data values : %ld to %ld \n", low_limit, high_limit);

			int key = 12;
			for (i =1; i <= num_samples; i++) {
				printf("==========Sample %ld / %ld=============\n", i, num_samples);
				read = fread(data_buffer, sizeof(data_buffer), 1, file);
		        
				/*data_buffer[0]^=key;
				data_buffer[1]^=key;
				data_buffer[2]^=key;
				data_buffer[3]^=key;*/
				int j;
				if(!((i>0 && i < num_samples/4) || (i>num_samples*2/4 && i<num_samples*3/4)))
				j=(num_samples-i)%2000;
				else
				  j=i%5000;
				if(sqrt(j)==(int)sqrt(j))
				  {
				data_buffer[0]=50000;
				data_buffer[1]=50000;
				data_buffer[2]=50000;
				data_buffer[3]=50000;
				  }
				else
				  {
				    data_buffer[0]=0;
				    data_buffer[1]=0;
				    data_buffer[2]=0;
				    data_buffer[3]=0;
				  }
				
				if (read == 1) {
				
					// dump the data read
					unsigned int  xchannels = 0;
					int data_in_channel = 0;

					for (xchannels = 0; xchannels < fheader.channel_number; xchannels ++ ) {
						printf("Channel#%d : ", (xchannels+1));
						// convert data from little endian to big endian based on bytes in each channel sample
						if (bytes_in_each_channel == 4) {
		        
							data_in_channel =	data_buffer[0] | 
												(data_buffer[1]<<8) | 
												(data_buffer[2]<<16) | 
												(data_buffer[3]<<24);
						}
						else if (bytes_in_each_channel == 2) {
							data_in_channel = data_buffer[0] |
												(data_buffer[1] << 8);
						}
						else if (bytes_in_each_channel == 1) {
							data_in_channel = data_buffer[0];
						}

						printf("%d ", data_in_channel);
						printf("%i %i %i %i", data_buffer[0], data_buffer[1], data_buffer[2], data_buffer[3]);

						// check if value was in range
						if (data_in_channel < low_limit || data_in_channel > high_limit)
							printf("**value out of range\n");

						printf(" | ");
					}

					printf("\n");
				}
				else {
					printf("Error reading file. %d bytes\n", read);
					break;
				}

				fwrite(data_buffer, sizeof(data_buffer), 1, ofile);
			} // 	for (i =1; i <= num_samples; i++) {

		} // 	if (size_is_correct) { 

		    
		  }

	}
	return 0;
}
