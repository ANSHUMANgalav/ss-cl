#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include <unistd.h>
#include<stdbool.h>
#include <string.h>

int main(){

struct{

int account_no;
double balance;

}account;

int fd = open("account_db.txt",O_RDWR|O_CREAT|O_EXCL,0666);

account.account_no=1000;
account.balance=0;
write(fd,&account,sizeof(account));

return 0;
}
