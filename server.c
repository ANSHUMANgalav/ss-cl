#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(){
struct sockaddr_in server , client;
int  size_client ,socket_desc , newsockfd;
char buff[512];
socket_desc = socket(AF_INET, SOCK_STREAM , 0);
server.sin_family = AF_INET; 
server.sin_addr.s_addr = INADDR_ANY; 
server.sin_port = htons( 52698);
bind(socket_desc , (void *)(&server), sizeof(server));
listen(socket_desc,3);

while(1){
size_client = sizeof(client);
newsockfd = accept (socket_desc , (void *)(&client), &size_client);
 if(fork()==0){
       
       
   ///////
   int n;
   char uname[100];
   char d_uname[100];
   char password[100];
   int acc_no,d_acc_no;
   bool type=0;
   int option;
   int status=0;
   int acc_no_fd;
   int acc_fd;
   int c_fd;
   int tran_fd;
   char ack;
   bool exist=0;
   double amount;
   time_t t;
   char a_no_str[5];
   char msg[150];

   struct{
    char opr[10];
    char time[30];
    double r_bal;
    double amt;
   }transaction;

   struct customer{
   char c_name[100];
   char password[100];
   bool type;
   int account_no;
   bool status;
    };
   
   struct account{
    int account_no;
    double balance;

    };
   struct account account1;
   struct account account2;
   struct customer customer1;
   struct customer customer2;

   struct flock fl = {F_UNLCK, SEEK_SET ,0 , 0, getpid()};
   struct flock fl2 ={F_UNLCK, SEEK_SET ,0 , 0, getpid()};

   A:
   n = write(newsockfd,"Enter user id : ",strlen("Enter user id : "));         //Ask username    
   if (n < 0) error("ERROR writing to socket");
   read(newsockfd , uname , sizeof(uname));
  // printf("usernme is %s\n",uname);

   n = write(newsockfd,"Enter your password : ",strlen("Enter your password : "));         //Ask password    
   if (n < 0) error("ERROR writing to socket");
   read(newsockfd , password , sizeof(password));
   //printf("password is %s\n", password);
   

    c_fd = open("customer_db.txt",O_RDONLY,0666);
    //fl = {F_RDLCK , SEEK_SET , 0 , 0 ,getpid() };
    fl.l_type=F_RDLCK;
    fcntl(c_fd,F_SETLKW , &fl);
   
   while(read(c_fd, &customer1 , sizeof(customer1)))
   {    if((strcmp(uname ,customer1.c_name)==0) && (strcmp(password,customer1.password)==0))
            {   //if(customer.status == false) {
                //break;}
                printf("abcabc\n");
                acc_no= customer1.account_no;
                type = customer1.type;
                status=customer1.status;
                break;
            }
    }
    //fl = {F_UNLCK , SEEK_SET , 0 , 0 ,getpid() };
    fl.l_type=F_UNLCK;
    fcntl(c_fd,F_SETLK , &fl);

    close(c_fd);
   // printf("%d\n",status);
 
   if(status)
   {       // printf("im inside status\n");
            n = write(newsockfd,"msg: welcome back\n",strlen("msg: welcome back\n"));         //welcoming valid user    
            if (n < 0) error("ERROR writing to socket");
            read(newsockfd , &ack  , sizeof(ack));
            //printf("%c\n",ack);
         
     }
    else{
            //printf("else part of status");
            n = write(newsockfd,"msg: Warning :: wrong user id or password\n",strlen("msg: Warning :: wrong user id or password\n"));         //welcoming valid user    
            if (n < 0){ 
            error("ERROR writing to socket");}
            read(newsockfd , &ack  , sizeof(ack));
            //printf("%c\n",ack);
            goto A;
    }
   
    C:
    if(type == true)
    {
     n = write(newsockfd,"select option\n Add new user(admin power)  :1\nAdd new user(normal):2\nTo add new user to an existing account  :3\n To delete an account press :4\nTo modify username and password of an account press :5\nTo view details press :6\nTo exit press :7\n",strlen("select option\n Add new user(admin power)  :1\nAdd new user(normal):2\nTo add new user to an existing account  :3\n To delete an account press :4\nTo modify username and password of an account press :5\nTo view details press :6\nTo exit press :7\n"));         //Ask option    
     if (n < 0) error("ERROR writing to socket");
     read(newsockfd , &option , sizeof(option));
     //printf("%d\n",option);

     switch(option)
        {
            case 1:
                D:
                n = write(newsockfd,"Enter name for new acc : ",strlen("Enter name for new acc : "));         //Ask username    
                if (n < 0) error("ERROR writing to socket");
                read(newsockfd , customer2.c_name , sizeof(customer2.c_name));

                exist=0;
                c_fd = open("customer_db.txt",O_RDWR,0666);

                //fl = {F_RDLCK , SEEK_SET , 0 , 0 ,getpid() };
                fl.l_type=F_WRLCK;
                fcntl(c_fd,F_SETLKW , &fl);

                while(read(c_fd, &customer1 , sizeof(customer1))){
                    if(strcmp(customer1.c_name,customer2.c_name)==0 && (customer1.status==1))
                    {   exist=1;
                        break;
                    }
                }
                if(exist==1){
                n = write(newsockfd,"msg:username already exist\n",strlen("msg:username already exist\n"));         //Ask username    
                if (n < 0) error("ERROR writing to socket");
                read(newsockfd , &ack  , sizeof(ack));
                goto D;

                }

                n = write(newsockfd,"Enter password for new acc",strlen("Enter password for new acc"));         //Ask username    
                if (n < 0) error("ERROR writing to socket");
                read(newsockfd , customer2.password , sizeof(customer2.password));

                customer2.account_no=1000;
                customer2.status=1;
                customer2.type=1;
                lseek(c_fd , 0 , SEEK_END);
                write(c_fd,&customer2,sizeof(customer2));


                //fl = {F_UNLCK , SEEK_CUR , 0 , 0 ,getpid() };
                fl.l_type=F_UNLCK;
                fcntl(c_fd,F_SETLK , &fl);
                close(c_fd);
            
                n = write(newsockfd,"msg: new user added successfully\n",strlen("msg: new user added successfully\n"));         //Ask username    
                if (n < 0) error("ERROR writing to socket");
                read(newsockfd , &ack  , sizeof(ack));
                
                break;
            
            
            case 2:
                E:
                n = write(newsockfd,"Enter name for new acc : ",strlen("Enter name for new acc : "));         //Ask username    
                if (n < 0) error("ERROR writing to socket");
                read(newsockfd , customer2.c_name , sizeof(customer2.c_name));
                
                exist=0;
                c_fd = open("customer_db.txt",O_RDWR,0666);

                //fl = {F_WRLCK , SEEK_SET , 0 , 0 ,getpid() };
                fl.l_type=F_WRLCK;
                fcntl(c_fd,F_SETLKW , &fl);

                while(read(c_fd, &customer1 , sizeof(customer1))){
                    if((strcmp(customer1.c_name,customer2.c_name)==0) && (customer1.status==1))
                    {   exist=1;
                        break;
                    }
                }
                if(exist==1){
                n = write(newsockfd,"msg:username already exist\n",strlen("msg:username already exist\n"));         //Ask username    
                if (n < 0) error("ERROR writing to socket");
                read(newsockfd , &ack  , sizeof(ack));
                goto E;

                }

                n = write(newsockfd,"Enter password for new acc",strlen("Enter password for new acc"));         //Ask username    
                if (n < 0) error("ERROR writing to socket");
                read(newsockfd , customer2.password , sizeof(customer2.password));

                acc_no_fd=open("acc_no.txt",O_RDWR,0666);
                //fl2 = {F_WRLCK , SEEK_SET , 0 , 0 ,getpid() };
                fl2.l_type=F_WRLCK;
                fcntl(acc_fd,F_SETLKW , &fl2);


                read(acc_no_fd , &acc_no , sizeof(int));
                acc_no++;
                lseek(acc_no_fd,0,SEEK_SET);
                write(acc_no_fd , &acc_no , sizeof(int));
                
                //fl2 = {F_UNLCK , SEEK_SET , 0 , 0 ,getpid() };
                fl2.l_type=F_UNLCK;
                fcntl(acc_fd,F_SETLK , &fl2);
                close(acc_no_fd);

                customer2.account_no=acc_no;
                customer2.status=1;
                customer2.type=0;
            
                //c_fd = open("customer_db.txt",O_RDWR,0666);
                lseek(c_fd , 0 , SEEK_END);
                write(c_fd,&customer2,sizeof(customer2));

                //fl = {F_UNLCK , SEEK_CUR , 0 , 0 ,getpid() };
                fl.l_type=F_UNLCK;
                fcntl(c_fd,F_SETLK , &fl);
                close(c_fd);

                account2.account_no=acc_no;
                account2.balance=101;
                acc_fd = open("account_db.txt",O_RDWR,0666);
                lseek(acc_fd , 0 , SEEK_END);
                write(acc_fd,&account2,sizeof(account2));
                close(acc_fd);
                
                char a_no_str[5];
                sprintf(a_no_str,"%d.txt",acc_no);
                creat(a_no_str,0666);

                n = write(newsockfd,"msg:new user added successfully\n",strlen("msg:new user added successfully\n"));         //Ask username    
                if (n < 0) error("ERROR writing to socket");
                read(newsockfd , &ack  , sizeof(ack));

                break;
           
            case 3:
               F:
               n = write(newsockfd,"Enter user id who wants to share account: \n",strlen("Enter user id who wants to share account: \n"));         //Ask username    
               if (n < 0) error("ERROR writing to socket");
               read(newsockfd , d_uname , sizeof(d_uname));
               exist=0;

               c_fd = open("customer_db.txt",O_RDWR,0666);
               fl.l_type=F_WRLCK;
               fcntl(c_fd,F_SETLKW, &fl);

               while(read(c_fd, &customer1 , sizeof(customer1))){
                    if(strcmp(customer1.c_name,d_uname)==0 && (customer1.status==1))
                    {   exist=1;
                        break;
                    }
                }
                if(exist==0){
                n = write(newsockfd,"msg:username does not exists\n",strlen("msg:username does not exists\n"));         //Ask username    
                if (n < 0) error("ERROR writing to socket");
                read(newsockfd , &ack  , sizeof(ack));
                goto F;

                }

               n = write(newsockfd,"msg:joint user will be added\n",strlen("msg:joint user will be added\n"));         //Ask username    
                if (n < 0) error("ERROR writing to socket");
                read(newsockfd , &ack  , sizeof(ack));

               

               
               customer2=customer1;
              G:
               n = write(newsockfd,"Enter user id for joint account: \n",strlen("Enter user id for joint account: \n"));         //Ask username    
               if (n < 0) error("ERROR writing to socket");
               read(newsockfd , customer2.c_name , sizeof(customer2.c_name));

               exist=0;
                while(read(c_fd, &customer1 , sizeof(customer1))){
                if((strcmp(customer1.c_name,customer2.c_name)==0) && (customer1.status==1))
                    {   exist=1;
                        break;
                    }
                }
                if(exist==1){
                n = write(newsockfd,"msg:username already exist\n",strlen("msg:username already exist\n"));         //Ask username    
                if (n < 0) error("ERROR writing to socket");
                read(newsockfd , &ack  , sizeof(ack));
                goto G;
                }

                n = write(newsockfd,"Enter password \n",strlen("Enter password \n"));         //Ask username    
               if (n < 0) error("ERROR writing to socket");
               read(newsockfd , customer2.password , sizeof(customer2.password));

               lseek(c_fd,0,SEEK_END);
               write(c_fd, &customer2 , sizeof(customer2));
               
               fl.l_type=F_UNLCK;
               fcntl(c_fd,F_SETLK, &fl);
               close(c_fd);
                
                n = write(newsockfd,"msg:new joint user added successfully\n",strlen("msg:new joint user added successfully\n"));         //Ask username    
                if (n < 0) error("ERROR writing to socket");
                read(newsockfd , &ack  , sizeof(ack));

                break;

            case 4:
                H:
               n = write(newsockfd,"Enter user id you want to delete: \n",strlen("Enter user id you want to delete: \n"));         //Ask username    
               if (n < 0) error("ERROR writing to socket");
               read(newsockfd , d_uname , sizeof(d_uname));
               //printf("usernme %s will be removed\n",d_uname);

                c_fd = open("customer_db.txt",O_RDWR,0666);
                fl.l_type=F_WRLCK;
                fcntl(c_fd,F_SETLKW, &fl);

                exist=0;
                while(read(c_fd, &customer1 , sizeof(customer1))){
                    if((strcmp(d_uname,customer1.c_name)==0) && (customer1.status==1)){
                        d_acc_no=customer1.account_no;
                        exist=1;
                        break;
                    }
                }
                if(exist==0){
                n = write(newsockfd,"msg:username does not exists\n",strlen("msg:username does not exists\n"));         //Ask username    
                if (n < 0) error("ERROR writing to socket");
                read(newsockfd , &ack  , sizeof(ack));
                goto H;

                }

                n = write(newsockfd,"msg:given user will be deleted\n",strlen("msg:given user will be deleted\n"));         //Ask username    
                if (n < 0) error("ERROR writing to socket");
                read(newsockfd , &ack  , sizeof(ack));

                
                
                customer1.status=0;
                lseek(c_fd,-(sizeof(customer1)),SEEK_CUR);
                write(c_fd,&customer1, sizeof(customer1));
                
                fl.l_type=F_UNLCK;
                fcntl(c_fd,F_SETLK, &fl);
                close(c_fd);
                
                // acc_fd = open("account_db.txt",O_RDWR,0666);
                // while (read(acc_fd,&account1,sizeof(account1)))
                // {
                //     if(d_acc_no==account1.account_no)
                //     {
                //         break;
                //     }
                // }
                // account1.balance=0;
                // lseek(acc_fd,-(sizeof(account1)),SEEK_CUR );
                // write(acc_fd,&account1,sizeof(account1));
                // close(acc_fd);
                

                n = write(newsockfd,"msg:account deleted successfully\n",strlen("msg:account deleted successfully\n"));         //Ask username    
                if (n < 0) error("ERROR writing to socket");
                read(newsockfd , &ack  , sizeof(ack));

                break;

             case 5:
             I:
             n = write(newsockfd,"Enter user id whose details to be modified: \n",strlen("Enter user id whose details to be modified: \n"));         //Ask username    
               if (n < 0) error("ERROR writing to socket");
               read(newsockfd , d_uname , sizeof(d_uname));
               c_fd = open("customer_db.txt",O_RDWR,0666);
               fl.l_type=F_WRLCK;
               fcntl(c_fd,F_SETLKW, &fl);

               exist=0;
               while(read(c_fd, &customer1 , sizeof(customer1))){
                    if((strcmp(customer1.c_name,d_uname)==0) && (customer1.status==1))
                    {   exist=1;
                        break;
                    }
                }
                if(exist==0){
                n = write(newsockfd,"msg:username does not exists\n",strlen("msg:username does not exists\n"));         //Ask username    
                if (n < 0) error("ERROR writing to socket");
                read(newsockfd , &ack  , sizeof(ack));
                goto I;

                }

                n = write(newsockfd,"msg:details of given acc will be modified\n",strlen("msg:details of given acc will be modified\n"));         //Ask username    
                if (n < 0) error("ERROR writing to socket");
                read(newsockfd , &ack  , sizeof(ack));

               
               
              J:
               n = write(newsockfd,"Enter new user id : \n",strlen("Enter new user id : \n"));         //Ask username    
               if (n < 0) error("ERROR writing to socket");
               read(newsockfd , customer1.c_name , sizeof(customer1.c_name));
               exist=0;
               while(read(c_fd, &customer2 , sizeof(customer2))){
                    if((strcmp(customer1.c_name,customer2.c_name)==0) && (customer2.status==1))
                    {   exist=1;
                        break;
                    }
                }

                if(exist==1){
                n = write(newsockfd,"msg:username already exists\n",strlen("msg:username already exists\n"));         //Ask username    
                if (n < 0) error("ERROR writing to socket");
                read(newsockfd , &ack  , sizeof(ack));
                goto J;

                }

               n = write(newsockfd,"Enter new password \n",strlen("Enter new password \n"));         //Ask username    
               if (n < 0) error("ERROR writing to socket");
               read(newsockfd , customer1.password , sizeof(customer1.password));
            
               lseek(c_fd,-(sizeof(customer1)),SEEK_CUR);
               write(c_fd, &customer1 , sizeof(customer1));
               
               fl.l_type=F_UNLCK;
               fcntl(c_fd,F_SETLK, &fl);
               close(c_fd);
                
                
                break;
             case 6:
                K:
                n = write(newsockfd,"Enter user id to show details \n",strlen("Enter user id to show details \n"));         //Ask username    
               if (n < 0) error("ERROR writing to socket");
               read(newsockfd , d_uname , sizeof(d_uname));
               c_fd = open("customer_db.txt",O_RDWR,0666);
               fl.l_type=F_RDLCK;
               fcntl(c_fd,F_SETLKW, &fl);
               
               exist=0;
               while(read(c_fd, &customer1 , sizeof(customer1))){
                    if((strcmp(customer1.c_name,d_uname)==0) && (customer1.status==1))
                    {   exist=1;
                        break;
                    }
                }
                if(exist==0){
                n = write(newsockfd,"msg:username does not exists\n",strlen("msg:username does not exists\n"));         //Ask username    
                if (n < 0) error("ERROR writing to socket");
                read(newsockfd , &ack  , sizeof(ack));
                goto K;

                }
                
                fl.l_type=F_UNLCK;
                fcntl(c_fd,F_SETLK, &fl);
                close(c_fd);
                acc_fd=open("account_db.txt",O_RDONLY,0666);
                while(read(acc_fd, &account1 , sizeof(account1))){
                    if(account1.account_no==customer1.account_no){
                        break;
                    }
                }
                char str[100];
                sprintf(str,"msg\nAccount holder name :%s\nAccount Number :%d\nRemaining Balance :%lf\n",customer1.c_name,account1.account_no,account1.balance);
                n = write(newsockfd,str,strlen(str));         //Ask username    
                if (n < 0) error("ERROR writing to socket");
                read(newsockfd , &ack  , sizeof(ack));
                

                break;
             case 7:
                n = write(newsockfd,"bye bye !! see you soon\n",strlen("bye bye !! see you soon\n"));         //welcoming valid user    
                if (n < 0){ 
                error("ERROR writing to socket");}
                read(newsockfd , &ack  , sizeof(ack));
                break;
          
            default:
                n = write(newsockfd,"msg:Enter valid choice\n",strlen("msg:Enter valid choice\n"));         //welcoming valid user    
                if (n < 0){ 
                error("ERROR writing to socket");}
                read(newsockfd , &ack  , sizeof(ack));
            
            break;
        }

      goto C;  

    }
    
    else{
        c:
     n = write(newsockfd,"select option\nTo deposit press :1\nTo withdraw press:2\nFor balance enquiry  :3\n To change password press :4\nTo print Transiction statement press :5\nTo Exit press :6\n",strlen("select option\nTo deposit press :1\nTo withdraw press:2\nFor balance enquiry  :3\n To change password press :4\nTo print Transiction statement press :5\nTo Exit press :6\n"));         //Ask option    
     if (n < 0) error("ERROR writing to socket");
     read(newsockfd , &option , sizeof(option));

      switch (option)
      {
      case 1:
         acc_fd=open("account_db.txt",O_RDWR,0666);
        // fl.l_type=F_RDLCK;//F_WRLCK;
        // fl.l_whence=SEEK_SET;
        // fl.l_start=0;
        // fl.l_len=0;
        // fcntl(acc_fd,F_SETLKW,&fl);
        

        while(read(acc_fd, &account1 , sizeof(account1))){
            if(account1.account_no==acc_no){
                    break;
                }
        } 
        
        
	
        // fl.l_type=F_WRLCK;
        // fl.l_whence=SEEK_CUR;
        // fl.l_start=-(sizeof(account1));
        // fl.l_len=(sizeof(account1));
        // fcntl(acc_fd,F_SETLKW,&fl);
        
       /* while(read(acc_fd, &account2 , sizeof(account2))){
            if(account2.account_no==acc_no){
                    break;
                }*/
        //}
        account2=account1;
        n = write(newsockfd,"Enter amount to Deposit",strlen("Enter amount to Deposit"));         //Ask option    
        if (n < 0) error("ERROR writing to socket");
        read(newsockfd , &amount , sizeof(amount));
        account2.balance+=amount;
        lseek(acc_fd,-(sizeof(account1)),SEEK_CUR );
        write(acc_fd, &account2 , sizeof(account2)); 
        
        // fl.l_type=F_UNLCK; 
        // fcntl(acc_fd,F_SETLK,&fl);
        close(acc_fd);

        time(&t);
        sprintf(a_no_str,"%d.txt",acc_no);
        
        tran_fd=open(a_no_str,O_RDWR,0666);
        // fl.l_type=F_WRLCK;
        // fl.l_whence=SEEK_END;
        // fl.l_start=0;
        // fl.l_len=(sizeof(transaction));
       // fcntl(tran_fd,F_SETLKW,&fl);
        
        strcpy(transaction.opr,"Credited");
        strcpy(transaction.time , ctime(&t));
        transaction.r_bal=account2.balance;
        transaction.amt=amount;
        lseek(tran_fd,0,SEEK_END); 
        write(tran_fd,&transaction,sizeof(transaction));
        
        // fl.l_type=F_UNLCK; 
        // fcntl(tran_fd,F_SETLK,&fl);
        close(tran_fd);

        n = write(newsockfd,"msg:amount added successfully\n",strlen("msg:amount added successfully\n"));         //Ask username    
        if (n < 0) error("ERROR writing to socket");
        read(newsockfd , &ack  , sizeof(ack));
        

        break;

      case 2:
        e:
        acc_fd=open("account_db.txt",O_RDWR,0666);
        // fl.l_type=F_RDLCK;//F_WRLCK;
        // fl.l_whence=SEEK_SET;
        // fl.l_start=0;
        // fl.l_len=0;
        // fcntl(acc_fd,F_SETLK,&fl);
        while(read(acc_fd, &account1 , sizeof(account1))){
            if(account1.account_no==acc_no){
                break;
            }
        }
        // fl.l_type=F_WRLCK;
        // fl.l_whence=SEEK_CUR;
        // fl.l_start=-(sizeof(account1));
        // fl.l_len=(sizeof(account1));
        // fcntl(acc_fd,F_SETLKW,&fl);
         
        account2=account1; 
        n = write(newsockfd,"Enter amount to Withdraw",strlen("Enter amount to Withdraw"));         //Ask option    
        if (n < 0) error("ERROR writing to socket");
        read(newsockfd , &amount , sizeof(amount));

        if(amount > account1.balance){
        n = write(newsockfd,"msg:amount exceeds current balance , enter again with lower amount\n",strlen("msg:amount exceeds current balance , enter again with lower amount\n"));         //Ask username    
          if (n < 0) error("ERROR writing to socket");
          read(newsockfd , &ack  , sizeof(ack));
            goto e;
        }

        account2.balance-=amount;
        lseek(acc_fd,-(sizeof(account1)),SEEK_CUR );
        write(acc_fd, &account2 , sizeof(account2));  
        
        // fl.l_type=F_UNLCK; 
        // fcntl(acc_fd,F_SETLK,&fl);
        close(acc_fd);

        time(&t);
        sprintf(a_no_str,"%d.txt",acc_no);
        tran_fd=open(a_no_str,O_RDWR,0666);
        // fl.l_type=F_WRLCK;
        // fl.l_whence=SEEK_END;
        // fl.l_start=0;
        // fl.l_len=(sizeof(transaction));
        // fcntl(acc_fd,F_SETLKW,&fl);
        
        strcpy(transaction.opr,"Debited");
        strcpy(transaction.time , ctime(&t));
        transaction.r_bal=account2.balance;
        transaction.amt=amount; 
        lseek(tran_fd,0,SEEK_END);
        write(tran_fd,&transaction,sizeof(transaction));
        
        // fl.l_type=F_UNLCK; 
        // fcntl(tran_fd,F_SETLK,&fl);
        close(tran_fd);

        n = write(newsockfd,"msg:amount debited successfully\n",strlen("msg:amount debited successfully\n"));         //Ask username    
        if (n < 0) error("ERROR writing to socket");
        read(newsockfd , &ack  , sizeof(ack));
          break;

      case 3:
        acc_fd=open("account_db.txt",O_RDONLY,0666);
        while(read(acc_fd, &account1 , sizeof(account1))){
            if(account1.account_no==acc_no){
                    break;
                }
            }


        close (acc_fd);
        char str[100];
        sprintf(str, "msg:Account No. :%d\nBalance %lf\n",account1.account_no,account1.balance);
        n = write(newsockfd,str,strlen(str));         //Ask username    
        if (n < 0) error("ERROR writing to socket");
        read(newsockfd , &ack  , sizeof(ack));
            
          break;
      case 4:
        c_fd = open("customer_db.txt",O_RDWR,0666);
        while(read(c_fd, &customer1 , sizeof(customer1))){
            if((strcmp(customer1.c_name,uname)==0))
             {  
                break;
              }
        }
        fl.l_type=F_WRLCK;
        fl.l_whence=SEEK_CUR;
        fl.l_start=-(sizeof(customer1));
        fl.l_len=(sizeof(customer1));
        fcntl(acc_fd,F_SETLKW,&fl);
        
        n = write(newsockfd,"Enter new password \n",strlen("Enter new password \n"));         //Ask username    
        if (n < 0) error("ERROR writing to socket");
        read(newsockfd , customer1.password , sizeof(customer1.password));
            
        lseek(c_fd,-(sizeof(customer1)),SEEK_CUR);
        write(c_fd, &customer1 , sizeof(customer1));
        
        fl.l_type=F_UNLCK; 
        fcntl(c_fd,F_SETLK,&fl);
        close(c_fd); 

        n = write(newsockfd,"msg: password changed successfully\n",strlen("msg: password changed successfully\n"));         //Ask username    
        if (n < 0) error("ERROR writing to socket");
        read(newsockfd , &ack  , sizeof(ack));
         
          break;
      case 5:
        
        sprintf(a_no_str,"%d.txt",acc_no);
        tran_fd=open(a_no_str,O_RDONLY,0666);
        while(read(tran_fd,&transaction,sizeof(transaction))){
        sprintf(msg ,"msg:::%s\nRs.- %lf\nRemaining balance::%lf\nat ::%s\n\n",transaction.opr,transaction.amt,transaction.r_bal,transaction.time );
        n = write(newsockfd,msg,strlen(msg));         //Ask username    
        if (n < 0) error("ERROR writing to socket");
        read(newsockfd , &ack  , sizeof(ack));

        }
        
        
        close(tran_fd);

        break;
      
      case 6:
          n = write(newsockfd,"bye bye !! see you soon\n",strlen("bye bye !! see you soon\n"));         //welcoming valid user    
                if (n < 0){ 
                error("ERROR writing to socket");}
                read(newsockfd , &ack  , sizeof(ack));
                break;
          break;
      
      default:
           n = write(newsockfd,"msg:Enter valid choice\n",strlen("msg:Enter valid choice\n"));         //welcoming valid user    
                if (n < 0){ 
                error("ERROR writing to socket");}
                read(newsockfd , &ack  , sizeof(ack));
          break;
      }

        goto c;




    }
    
    }else{
close(newsockfd);
}

}



return 0;
}
