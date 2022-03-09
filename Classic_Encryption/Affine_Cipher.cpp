#include <stdio.h>

char *AffineCipherEncryption(char *, int, int, int);
char *AffineCipherDecryption(char *, int, int, int);

int main(){
    int firstKey = 0, secondKey = 0, str_size = 0, select = 0;
    char str[50] = {0,};

    printf("Input PlainText or CipherText: ");
    gets(str);

    printf("Input First Key Value: ");
    scanf("%d", &firstKey);

    printf("Input Second Key Value: ");
    scanf("%d", &secondKey);

    printf("Select menu(Input 1 or 2):1 Encryption, 2 Decryption: ");
    scanf("%d", &select);

    for(int i=0; str[i] != '\0'; i++)   str_size++; //get str_size

    if(select == 1) AffineCipherEncryption(str, str_size, firstKey, secondKey);
    if(select == 2) AffineCipherDecryption(str, str_size, firstKey, secondKey);

    printf("Print Result: ");
    puts(str);

    return 0;
}

char *AffineCipherEncryption(char *str, int str_size, int firstKey, int secondKey){
    for(int i=0; i<str_size; i++){
        if(str[i]>='A' && str[i]<='Z'){
            str[i] -= 'A';

            if(firstKey*str[i] + secondKey < 0) str[i] += 26;

            str[i] = (firstKey*str[i] + secondKey) % 26;
            str[i] += 'A';
        }
        else if(str[i]>='a' && str[i]<='z'){
            str[i] -= 'a';

            if(firstKey*str[i] + secondKey < 0) str[i] += 26;

            str[i] = (firstKey*str[i] + secondKey) % 26;
            str[i] += 'a';
        }
        else    ;
    }
}

char *AffineCipherDecryption(char *str, int str_size, int firstKey, int secondKey){
    int flag = 0, firstKey_inverse = 0;

    for (int i = 0; i < 26; i++){
        flag = (firstKey * i) % 26;
        if (flag == 1)  firstKey_inverse = i;
    }

    for(int i=0; i<str_size; i++){
        if(str[i]>='A' && str[i]<='Z'){
            str[i] -= 'A';

            str[i] = (firstKey_inverse * (str[i]-secondKey)) % 26;
            str[i] += 'A';
        }
        else if(str[i]>='a' && str[i]<='z'){
            str[i] -= 'a';

            if(str[i]-secondKey < 0) str[i] += 26;

            str[i] = (firstKey_inverse * (str[i]-secondKey)) % 26;
            str[i] += 'a';
        }
        else    ;
    }
}
