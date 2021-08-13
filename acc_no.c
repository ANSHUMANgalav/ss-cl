#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include <unistd.h>
#include<stdbool.h>
#include <string.h>

int main(){

struct{
int acc_no;

}acc_no;

int fd = open("acc_no.txt",O_RDWR|O_CREAT|O_EXCL,0666);

acc_no.acc_no=1000;

write(fd,&acc_no,sizeof(acc_no));

return 0;
}
