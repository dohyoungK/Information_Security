#include <stdio.h>

char *RailFenceCipherEncryption(char *, char [][50], int, int);
char *RailFenceCipherDecryption(char *, char *, int, int);


int main(){
    int rail = 0, str_size = 0, select = 0;
    char str[50] = {0,};
    char descryptionStr[50] = {0,};

    printf("Input PlainText or CipherText: ");
    gets(str);

    printf("Input Rail Value: ");
    scanf("%d", &rail);

    char tmp[rail][50] = {0,};

    printf("Select menu(Input 1 or 2):1 Encryption, 2 Decryption: ");
    scanf("%d", &select);

    for(int i=0; str[i] != '\0'; i++)   str_size++; //get str_size

    if(select == 1) RailFenceCipherEncryption(str, tmp, rail, str_size);
    if(select == 2) RailFenceCipherDecryption(str, descryptionStr, rail, str_size);



    return 0;
}

char *RailFenceCipherEncryption(char *str, char tmp[][50], int rail, int str_size){
    int k = 0, j = 0, row = 0, col = 0;

    for(int i=0; i<str_size; i++){
        if((str[i]>='A' && str[i]<='Z') || (str[i]>='a' && str[i]<='z')){
            tmp[row][col] = str[i];
            row++;

            if(row == rail){
                row = 0;
                col++;
            }
        }
    }

    for(int i=0; i<str_size; i++){
        str[i] = tmp[j][k];
        k++;
        if(tmp[j][k] == '\0'){
            j++;
            k = 0;
        }
    }

    printf("Print Result: ");
    puts(str);
}

char *RailFenceCipherDecryption(char *str, char *descryptionStr, int rail, int str_size){
    int j = 0, k = 0;
    int index_count = str_size / rail; // str_size % rail
    if(str_size%rail != 0)  index_count += 1;

    for(int i=0; i<str_size; i++){
        if((str[i]>='A' && str[i]<='Z') || (str[i]>='a' && str[i]<='z')){
            descryptionStr[i] = str[j+k];
            k += index_count;
            if(k >= str_size){
                j++;
                k = 0;
            }
        }
    }

    printf("Print Result: ");
    puts(descryptionStr);
}
