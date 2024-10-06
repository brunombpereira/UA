//
// Created by bruno on 05/10/2024.
//


#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(void) {
	char str1[50], str2[50], str3[50];
  	int cnt = 0;

  	printf("Primeira string: ");
  	scanf("%s", str1);
  	printf("Segunda string: ");
  	scanf("%s", str2);

  	for(int i = 0; i < strlen(str1); i++) {
    	if(isalpha(str1[i])) {
      		cnt++;
    	}
  	}

	printf("Número de letras do alfabeto da primeira string: %d\n", cnt);

	cnt = 0;

	for (int i = 0; i < strlen(str2); i++)
	{
		if (isupper(str2[i]))
		{
			cnt++;
		}
	}

	printf("Número de letras maiúsculas da segunda string: %d\n\n", cnt);

	for (int i = 0; i < strlen(str1); i++)
	{
		str1[i] = tolower(str1[i]);
	}
	
	for (int i = 0; i < strlen(str2); i++)
	{
		str2[i] = tolower(str2[i]);
	}

	printf("Primeira string em minúsculas: %s\n", str1);
	printf("Segunda string em minúsculas: %s\n", str2);

	if (strcmp(str1,str2) < 0)
	{
		printf("As strings não são iguais.\nOrdem lexicográfica: %s, %s\n", str1, str2);
	} else if (strcmp(str1,str2) > 0)
	{
		printf("As strings são diferentes.\nOrdem lexicográfica: %s, %s\n", str2, str1);
	} else
	{
		printf("As strings são iguais.\n");
	}

	strcpy(str3,str2);

	printf("Terceira string: %s\n", str3);
	printf("String concatenada: %s", strcat(str2,str3));

	return 0;
}