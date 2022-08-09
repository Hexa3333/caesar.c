#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char* Encrypt(char* exposed, int size, int shiftNumber);
char* Decrypt(char* encoded, int size, int rev_shiftNumber);

int main(int argc, const char* argv[])
{

    if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL)
    {
        printf("\033[1;31mInvalid options for caesar\033[0m\n");
        printf("How to use:\ncaesar (e/d) (shift number) (filename) OPTIONAL: (output filename)\n");
        return 0;
    }

    const char* mode = argv[1];
    int desiredShifts = atoi(argv[2]);
    const char* finpName = argv[3];
    const char* foutName = argv[4];

    if (argv[4] == NULL)
    {
        foutName = "caesar_output";
    }

    bool ed;
    if (*mode == 'E' || *mode == 'e')
    {   ed = true; }
    else if (*mode == 'D' || *mode == 'd')
    {   ed = false; }
    

	FILE* finp = NULL;
    finp = fopen(argv[3], "r+");
    if (finp==NULL)
    {
        printf("Failed to read file.\n");
        return 0;
    }
   
    if (ed)
    {
        printf("Encryption running...\n");
    }
    else 
    {
        printf("Decryption running...\n");
    }

    fseek(finp, 0, SEEK_END);
    int length = ftell(finp);
    fseek(finp, 0, SEEK_SET);

    char* content = (char*)malloc(length+1);
    char c;
    int i=0;
    while((c=fgetc(finp)) != EOF)
    {
        content[i] = c;
        i++;
    }
    content[i] = '\0';
    fclose(finp);


    FILE* fout = NULL;
    fout = fopen(foutName, "w");
    if (fout==NULL)
    {
        printf("Failed to write to file.\n");
        return 0;
    }
    if (ed)
    {   fprintf(fout, Encrypt(content, i, desiredShifts));   }
    else
    {   fprintf(fout, Decrypt(content, i, desiredShifts));    }


	free(content);
    return 0;
}

char* Encrypt(char* exposed, int size, int shiftNumber)
{
    char* endRes = (char*)malloc(size+1);
    
    for (int i=0; i < size; i++)
    {
        if (exposed[i] == '\n') 
        {
            endRes[i] = '\n';
            i++;    
        }
        endRes[i] = exposed[i] + shiftNumber;
    }

    return (char*)endRes;
}

char* Decrypt(char* encoded, int size, int rev_shiftNumber)
{
    char* endRes = (char*)malloc(size+1);

    for (int i=0; i < size; i++)
    {
        if (encoded[i] == '\n')
        {
	    endRes[i] = '\n';
	    i++;
        }
        endRes[i] = encoded[i] - rev_shiftNumber;
    }    
    
    return (char*)endRes;
}
