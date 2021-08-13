#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include <unistd.h>
#include<stdbool.h>
#include <string.h>


int main(){

struct{
char c_name[100];
char password[100];
bool type;
int account_no;
bool status;


}customer;

char uname[100];
char password[100];
/*
printf("uname  :");
scanf("%s",uname);

printf("password  :");
scanf("%s",password);
*/
int fd = open("customer_db.txt",O_RDWR,0666);
while(read(fd, &customer , sizeof(customer)))
{
	//if((strcmp(uname ,customer.c_name)==0) && (strcmp(password,customer.password)==0) && customer.status){
			
	printf("name    :%s\n",customer.c_name);
	
	printf("acc no. :%d\n",customer.account_no);
	
	printf("password :%s\n",customer.password);

	if(customer.type==true){
		printf("type----admin\n");		
		}	
	else{
		printf("type----normal user\n");	
		}
	if(customer.status){
		printf("active\n");		
		}	
	else{
		printf("closed acc\n");	
		}
	//}	
}


return 0;
}
