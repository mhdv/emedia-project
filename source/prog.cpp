#include <iostream>
#include <cstdlib>
#include <string.h>
#include <cmath>
#include <sys/stat.h>
#include <gmp.h>
#include <gmpxx.h>

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

int hcf(mpz_t a,mpz_t b, mpz_t &hcf_int) // Highest common factor of a and b
{
  mpz_t t;
  mpz_init(t);
  
  
  while(b != 0)
  {
    mpz_set(t, b);
    mpz_mod(b, a, b);
    mpz_set(a, t);
  };
  mpz_set(hcf_int, a);
}


int modulo(unsigned long long a, unsigned long long b, unsigned long long c) { // Calculate (a^b)%c without calculating a^b
	unsigned long long n, *pows, *indexes, indexCounter = 0, searchBit = 1, partialMul = 1;
	n = floor(log2(b)) + 1;
	pows = new unsigned long long[n];
	indexes = new unsigned long long[n];
	pows[0] = a % c;
	for (int i = 1; i < n; i++) {
		pows[i] = (pows[i - 1] * pows[i - 1]) % c;
	}


	for (int i = 0; i < n; i++) {
		int index = b & searchBit;
		if (index != 0) {
			indexes[indexCounter] = floor(log2(index));
			indexCounter++;
		}
		searchBit = searchBit << 1;
	}

	for (int i = 0; i < indexCounter; i++) {
		partialMul = (partialMul * pows[indexes[i]]) % c;
	}
	delete pows;
	delete indexes;
	return partialMul % c;
}

int main(int argc, char *argv[])
{

  //    Handling arguments  
  
	int read = 0;
	std::string stre = "-encode";
	std::string strd = "-decode";
	std::string output = "-o";
	std::string name;
	
	if(argc != 3 && argc != 5)
	  {
	    std::cout<<"Error: wrong number of input arguments.\nPlease use ./[Prog_name] [file_name.wav] [-encode/-decode] \n(optional)[-o file_name.wav](default: sound2.wav)\n\n";
	    return 0;
	  }
	
	if(strstr(argv[1],".") == NULL)
	  {
	    std::cout<<"Error: please specify a .wav (WAVE) file with full extension.\n\n";
	    return 0;
	  }

	if(strcmp(strrchr(argv[1],'.')+1, "wav") != 0)
	  {
	    std::cout<<"Error: please specify a .wav (WAVE) file with full extension.\n\n";
	    return 0;
	  }
	
	if(argv[2] != stre && argv[2] != strd)
	  {
	    std::cout<<"Error: please specify the type of operation [-encode/-decode]\n\n";
	    return 0;
	  }

	if(argc > 3)
	  {
	    if(argv[3] == output)
	      {
		if(strstr(argv[4],".") == NULL)
			  {
			    std::cout<<"Error: please specify a .wav (WAVE) file with full extension.\n\n";
			    return 0;
			  }

		else if(strcmp(strrchr(argv[4],'.')+1, "wav") != 0)
		  {
		    std::cout<<"Error: please specify a .wav (WAVE) file with full extension.\n\n";
		    return 0;
		  }
        
		std::string name = argv[4];
	      }
	    else
	      {
		  std::cout<<"Error: wrong form of input arguments.\nPlease use ./[Prog_name] [file_name.wav] [-encode/-decode] \n(optional)[-o file_name.wav](default: sound2.wav)\n\n";
		  return 0;
	      }
	  } // if(argc>3)
        
	std::string operation_type = argv[2];
		
	hdr fheader;
	int fheader_size=sizeof(fheader);

	FILE *file;	

	if((file=fopen(argv[1], "rb")) == NULL)
	  {
	    printf("Error: can't open sound file\n\n");
	    return 0;
	  }

	// Header reading
	
	read = fread(&fheader, fheader_size, 1, file);
	int file_length=sizeof(file);


	// Header display

	std::cout<<">>> Header information in file "<<argv[1]<<": <<<\n\n";

	printf("RIFF: %.4s", fheader.riff);
	printf("%.4s", fheader.riff);
	printf("\nFile type: \t\t");
	printf("%.4s", fheader.file_type);
	printf("\nFormat chunk: \t\t");
	printf("%.4s", fheader.format_chunk);
	printf("\nData: \t\t\t");
	printf("%.4s", fheader.data);
	printf("\n");
	printf("Frequency: \t\t%i Hz\n", fheader.samples_per_second);
	printf("Bits per second: \t%i\n", fheader.bits_per_second);
	printf("Number of channels: \t%i\n", fheader.channel_number);
	printf("Chunk size: \t\t%i\n", fheader.chunk_size);
	printf("Data length: \t\t%i KB\n", fheader.data_length/1024);
	
	long sample_size = (fheader.channel_number * fheader.bits_per_sample)/8;
	
	if(fheader.format_type == 1)
	  {
	    long i = 0;
	    char data_buffer[sample_size];
	    int  size_is_correct = 1;
	    long bytes_in_each_channel = (sample_size / fheader.channel_number);
	    long num_samples = (8 * fheader.data_length) / (fheader.channel_number * fheader.bits_per_sample);
	    
	    
	    FILE *ofile;
	    if(argc == 5)
	      ofile = fopen(argv[4], "wb");
	    else
	      ofile = fopen("sound2.wav", "wb");
	    
	    fwrite(&fheader, sizeof(fheader), 1, ofile);
	    
	    if (size_is_correct)
	      { 
		if(operation_type == "-encode")
		  std::cout<<"Operation type: encoding\n";
		else
		  std::cout<<"Operation type: decoding\n";
		
		
	      
		// RSA algorithm: 
		std::cout<<"\n>>> RSA algorithm: <<<\n\n";
		mpz_t p, q;
		mpz_init_set_str(p, "117116115114112111", 10);
	        mpz_init_set_str(q, "161111111111111111", 10);
		std::cout<<"p = "<<p<<"\nq = "<<q<<"\n";
		mpz_t n;
		mpz_init(n);
		mpz_mul (n, p, q);
		 mpz_sub_ui(p, p, 1);
		 mpz_sub_ui(q, q, 1);
		mpz_t euler;
	        mpz_init (euler);
		mpz_mul (euler, p, q);

		 mpz_clear(p);
		 mpz_clear(q);

		 mpz_t n_minus_one;
		 mpz_init(n_minus_one);
		 mpz_sub_ui(n_minus_one, n, 1);
		 
		mpz_t e;
		mpz_init(e);
		mpz_set (e, n_minus_one);

		mpz_t hcf_int;
		mpz_init(hcf_int);

		mpz_t gcd_help;
		mpz_init(gcd_help);
		

        	while (true)
		  {
		    mpz_gcd(gcd_help, euler, e);
		    if(mpz_cmp_d(gcd_help, 1) == 0)
		      {	
			break;
		      }
		    else
		      mpz_sub_ui(e, e, 1);
		   }
		
		mpz_t d;
		mpz_init(d);

		
		mpz_invert(d, e, euler);

		std::cout<<"\nphi = "<<euler<<"\n";

										     
									std::cout<<"\nPublic key (e, n):\n("<<e<<" , "<<n<<")\n";
															   std::cout<<"\nSecret key (d,n):\n("<<d<<" , "<<n<<")\n";
		//  Reading data

	        	       
	        mpz_t op_int;
		mpz_init(op_int);
					
		if(operation_type == stre)
		  {
		    mpz_set(op_int, e);
		    std::cout<<"\nEncoding file...\n";
		  }
		else if(operation_type == strd)
		  {
		    mpz_set(op_int, d);
		    std::cout<<"\nDecoding file...\n";
		  }
		else
		  {
		    std::cout<<"Error: wrong operation type\n\n";
		    return 0;
		  }

	       	    
		int data;
	        mpz_t helper;
	        mpz_init(helper);
		
        		        
		
		if(operation_type == stre)
		  {
		    for (i = 1; i <= num_samples; i++)
		      {

		    
			read = fread(&data, sizeof(data), 1, file);

			if(data<0)
			  {
			    data *= -1;
			    mpz_set_si(helper, data);
			    mpz_powm(helper, helper, op_int, n);
			    mpz_mul_si(helper, helper, -1);
			  }
			else
			  {
			    mpz_set_si(helper, data);
			    mpz_powm(helper, helper, op_int, n);
			  }
		    
		    // Writing data:
		  

			mpz_out_raw(ofile, helper);
			
		      } // for(i = 1...
		  }// if(operation...
		
		else if(operation_type == strd)
		  {
		    for (i = 1; i <= num_samples; i++)
		         {
			   mpz_inp_raw(helper, file);

		      if(mpz_sgn(helper) == -1)
		      {
		        mpz_mul_si(helper, helper, -1);
		        mpz_powm(helper, helper, op_int, n);
			data = mpz_get_ui(helper);
		        data *= -1;
		      }
		    else
		      {
			mpz_powm(helper, helper, op_int, n);
			data = mpz_get_ui(helper);
		      }
		    
		    // Writing data:
		      
		    fwrite(&data, sizeof(data), 1, ofile);
		    
		      } // for(i = 1...
		  } // if(operation...
	      } // if(size_is_correct)
	  } // if(fheader.format_type == 1)
		if(operation_type == "-encode")
		  std::cout<<"\n>>> Successfully encoded <<<\n";
		else
		  std::cout<<"\n>>> Successfully decoded <<<\n";
	return 0;
}