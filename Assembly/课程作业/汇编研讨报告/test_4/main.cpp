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

int main()
{
	int valid_flag = 0;
	char password[1024];
	FILE *fp;
	if(!(fp=fopen("password.txt","r")))

	{
		fclose(fp);
		return 0;
	}
	fscanf(fp,"%s",password);
	valid_flag = verify_password(password);
	if(valid_flag)
	{		
		printf("incorrect password!\n");
	}
	else
	{
		printf("Congratulation! You have passed the verification\n\n");
	}
	fclose(fp);
	return 0;
}