#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	
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

			FILE *file;
			if((file=fopen(argv[1], "r")) == NULL){
				printf("Error");
				return 0;
			}
			if(file){
				while((c = getc(file)) != EOF){
					putchar(c);
				}
			}

			return 0;
	}
	return 0;
}