#include <stdio.h>

//指纹模块的调试 start 
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

int set_opt(int,int,int,char,int);

void main_uart(char *uart3)
{
	int fd,nByte,flag=1;
	//char *uart3 = "/dev/ttyS0"; //"/dev/ttySAC3"
	//char *uart3 = "/dev/ttyS1"; //"/dev/ttySAC3"
	char buffer[512];
       
        unsigned char send_buffer[512];
        send_buffer[0] = 0xF5; 
        send_buffer[1] = 0x30; 
        send_buffer[2] = 0x0; 
        send_buffer[3] = 0x0; 
        send_buffer[4] = 0x0; 
        send_buffer[5] = 0x0; 
        send_buffer[6] = 0x30; 
        send_buffer[7] = 0xF5; 
	memset(buffer, 0, sizeof(buffer));
	//if((fd = open(uart3, O_RDWR|O_NOCTTY))<0)//默认为阻塞读方式
        if((fd = open(uart3, O_RDWR|O_NONBLOCK))<0)//非阻塞读方式
        {
		printf("open %s is failed",uart3);
        }
	else{
		set_opt(fd, 115200, 8, 'N', 1);
		//write(fd,uart_demo, strlen(uart_demo));
		write(fd, send_buffer, 8);
                //write(fd,uart_out, strlen(uart_out));
		while(1) {
                        sleep(1);
                        printf("send write 8!\n");
		        write(fd, send_buffer, 8);
			while( (nByte = read(fd, buffer, 8)) > 0 ) {
				//buffer[nByte+1] = '\0';			
                                printf("read while = %d\n", nByte);
                                //printf buffer
                                printf("start:");
                                for(int i = 0; i < nByte; i++) {
                                   printf("%x ", buffer[i]);
                                   buffer[i] = 0;
                                }
                                printf("end\n");
				//write(fd,buffer,strlen(buffer));
				//memset(buffer, 0, strlen(buffer));
			//	nByte = 0;
			}
		}
	}
}
 
int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio,oldtio;
	if  ( tcgetattr( fd,&oldtio)  !=  0) { 
		perror("SetupSerial 1");
		return -1;
	}
	bzero( &newtio, sizeof( newtio ) );
	newtio.c_cflag  |=  CLOCAL | CREAD;
	newtio.c_cflag &= ~CSIZE;
 
	switch( nBits )
	{
		case 7:
			newtio.c_cflag |= CS7;
			break;
		case 8:
			newtio.c_cflag |= CS8;
			break;
	}
 
	switch( nEvent )
	{
	case 'O':
		newtio.c_cflag |= PARENB;
		newtio.c_cflag |= PARODD;
		newtio.c_iflag |= (INPCK | ISTRIP);
		break;
	case 'E': 
		newtio.c_iflag |= (INPCK | ISTRIP);
		newtio.c_cflag |= PARENB;
		newtio.c_cflag &= ~PARODD;
		break;
	case 'N':  
		newtio.c_cflag &= ~PARENB;
		break;
	}
 
	switch( nSpeed )
	{
		case 2400:
			cfsetispeed(&newtio, B2400);
			cfsetospeed(&newtio, B2400);
			break;
		case 4800:
			cfsetispeed(&newtio, B4800);
			cfsetospeed(&newtio, B4800);
			break;
		case 9600:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
			break;
		case 115200:
			cfsetispeed(&newtio, B115200);
			cfsetospeed(&newtio, B115200);
			break;
		case 460800:
			cfsetispeed(&newtio, B460800);
			cfsetospeed(&newtio, B460800);
			break;
		default:
			cfsetispeed(&newtio, B9600);
			cfsetospeed(&newtio, B9600);
			break;
	}
	if( nStop == 1 )
		newtio.c_cflag &=  ~CSTOPB;
	else if ( nStop == 2 )
		newtio.c_cflag |=  CSTOPB;
		newtio.c_cc[VTIME]  = 100;///* 设置超时10 seconds*/
		newtio.c_cc[VMIN] = 0;
		tcflush(fd,TCIFLUSH);
	if((tcsetattr(fd,TCSANOW,&newtio))!=0)
	{
		perror("com set error");
		return -1;
	}
	
	printf("set done!\n\r");
	return 0;
}

//指纹模块的调试 end

//GPS模块的调试 start 


//GPS模块的调试 end

//普通IO模块

//MAC地址作为sn start
//cat /sys/class/net/eth0/address
int main_sn()
{
//32:D6:39:25:CD:4F
//cat /sys/class/net/eth0/address
}
//MAC地址作为sn end


//rtc时钟模块调试  start
main_rtc(){
   while(1) {
       sleep(1);
       int sys_time = time();
       printf("syst_time=%d\n", sys_time);
   }
}
//rtc时钟模块调试  end

int main()
{
   printf("carry case good!\n");
   main_uart("/dev/ttyS1");
   //main_rtc();
   //double  b = 3029.31033;
   //double  a = 11424.05285;
   //printf("%f %f", b, a);
}
