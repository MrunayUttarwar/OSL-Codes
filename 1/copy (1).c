#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
	if(argc < 3) {
		printf("Wrong command\n");
		printf("Exiting program\n");
		return 0;
	}
	
	char *src_file = argv[1];
	char *des_file = argv[2];
	
	char buffer[1000];
	char data_to_read[100];
	
	FILE *src = fopen(src_file, "r");
	FILE *des = fopen(des_file, "w");
	
	if(src == NULL || des==NULL) {
		printf("NO FILE, NOT OPENED");
		printf("Exiting program");
		return 0;
	}
	
	while(fgets(data_to_read, 100, src)) {
		//printf("%s", data_to_read);
		fputs(data_to_read, des);
	}
	
	printf("Data copied from source file to destination file");
	printf("\nClosing both the files\n");
	fclose(src);
	fclose(des);
		
	return 0;
	
}
