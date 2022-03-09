#include<stdio.h>

char *GronsfeldCipherEncryption(char *, int *, int, int);
char *GronsfeldCipherDecryption(char *, int *, int, int);

int main(){
    int str_size = 0, key_size = 0, select = 0;
    char str[50] = {0,};
    char key[50] = {0,};
    int shift[50] = {0,};

    printf("Input PlainText or CipherText: ");
    gets(str);

    printf("Input Key Value: ");
    gets(key);

    printf("Select menu(Input 1 or 2):1 Encryption, 2 Decryption: ");
    scanf("%d", &select);

    for(int i=0; str[i]!='\0'; i++)
        str_size++;
    for(int i=0; key[i]!='\0'; i++)
        key_size++;
    for(int i=0; i<key_size; i++){
        key[i] -= '0';
        shift[i] = key[i];
    }

    if(select == 1) GronsfeldCipherEncryption(str, shift, str_size, key_size);
    if(select == 2) GronsfeldCipherDecryption(str, shift, str_size, key_size);

    printf("Print Result: ");
    puts(str);

    return 0;
}
char *GronsfeldCipherEncryption(char *str, int *shift, int str_size, int key_size){
    int j = 0;

    for(int i=0; i<str_size; i++){
        if(str[i]>='A' && str[i]<='Z'){
            str[i] -='A';

            str[i] = (str[i]+shift[j]) % 26;
            str[i] += 'A';
            j++;
            if(j >= key_size)
                j = 0;
        }
        else if(str[i]>='a' && str[i]<='z'){
            str[i] -= 'a';

            str[i] = (str[i]+shift[j]) % 26;
            str[i] += 'a';
            j++;
            if(j >= key_size)
                j = 0;
        }
        else    ;
    }
}

char *GronsfeldCipherDecryption(char *str, int *shift, int str_size, int key_size){
    int j = 0;

    for(int i=0; i<str_size; i++){
        if(str[i]>='A' && str[i]<='Z'){
            str[i] -='A';

            if((str[i]-shift[j]) < 0)   str[i] += 26;
            str[i] = (str[i]-shift[j]) % 26;
            str[i] += 'A';
            j++;
            if(j >= key_size)
                j = 0;
        }
        else if(str[i]>='a' && str[i]<='z'){
            str[i] -= 'a';

            if((str[i]-shift[j]) < 0)   str[i] += 26;
            str[i] = (str[i]-shift[j]) % 26;
            str[i] += 'a';
            j++;
            if(j >= key_size)
                j = 0;
        }
        else    ;
    }
}
