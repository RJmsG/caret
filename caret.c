#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define getchar() getc(stdin)
#define putchar() putc((c),stdout)

char * xorBuffer(char *buffer, long bufferSize, char* key, int keyLen){

    int i;
    for(i = 0;i <= bufferSize;i++){
        buffer[i] ^= key[i % keyLen];
    }
    return buffer;
}

int xorFile(char *fileIn, char * fileOut, char* key){

    FILE *fpi, *fpo;
    char *fileBuffer = NULL;

    fpi = fopen(fileIn,"rb");
    fpo = fopen(fileOut,"wb");

    if(NULL == fpi){
        printf("Error opening input file %s: %s\n", fileIn, strerror(errno));
        return 1;
    }
    if(NULL == fpo){
        printf("Error opening output file %s: %s\n", fileOut, strerror(errno));
        return 2;
    }

    fseek(fpi,0L,SEEK_END);
    long fileSize = ftell(fpi); 
    fileBuffer = malloc(sizeof(char)* (fileSize + 1));  
    fseek(fpi,0L,SEEK_SET);     
    size_t length = fread(fileBuffer, sizeof(char), fileSize,fpi);      
    fileBuffer[length];
    int kl = strlen(key);
    fileBuffer = (char *)xorBuffer(fileBuffer,fileSize,key,kl);    
    int c;  
    for(c = 0;c < fileSize;c++){ 
        putc(((fileBuffer[c])),fpo);
    }

    fclose(fpi);
    fclose(fpo);
    free(fileBuffer);
    return 0;
}

int main(int argc, char*argv[]){
    if(argc == 4){
        if(xorFile(argv[1],argv[2],argv[3]) == 0)
            printf("File operation was successful.");

        else
            printf("An error occured.");
        
    }else{
        printf("usage --- ./caret [input file][output file]");
    }
}
