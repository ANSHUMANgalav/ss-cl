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

int fd = open("customer_db.txt",O_RDWR|O_CREAT|O_EXCL,0666);

strcpy(customer.c_name,"admin");
strcpy(customer.password,"admin12345");
customer.type=true;
customer.account_no=1000;
customer.status=true;

write(fd,&customer,sizeof(customer));

return 0;
}
