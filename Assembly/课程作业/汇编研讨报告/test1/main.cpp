#include<stdio.h>
#define PASSWORD "1234567"
#include<string>
int verify_password(char *password)
{
	int authenticated;
	char buffer[8];
	authenticated = strcmp(password,PASSWORD);
	strcpy(buffer,password);
	return authenticated;
}

void main()
{
	int valid_flag = 0;
	char password[1024];
	char temp[100];
	while(1)
	{
		printf("TEST:    ");
		scanf("%s",temp);
		printf("please input password:    ");
		scanf("%s",password);
		valid_flag = verify_password(password);
		if(valid_flag)
		{
			printf("incorrect password\n");
		}
		else
		{
			printf("Congratulation£¡You have passed the verification£¡\n\n");
		}
	}

}