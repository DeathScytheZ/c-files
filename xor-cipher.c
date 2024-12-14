#include <stdio.h>



void printBinary(int num){
	for(int i = 8; i >= 0; i--){
		int bit = (num >> i) & 1;
		printf("%d", bit);
	}
}

char* xor(const char* s, int a){
	int i = 0;
	static char result[100] = "";
	while(s[i] != '\0'){
		result[i] = s[i] ^ a;
		i++;
	}
	result[i] = '\0';
	return result;
}


int main(){
	int a = 0b00000001;
	char s[100] = "hello";
	printf("%s",xor(s, a));
}
