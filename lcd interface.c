#include<reg51.h>
void lcd();
void map();
void toggle();
void data_wr();
void command_wr(unsigned char value);
void delay(unsigned int time);
unsigned int i,j;
sbit Bk=P0^0;
sbit RS=P0^1;
sbit RW=P0^2;
sbit EN=P0^3;
sbit d4=P0^4;
sbit d5=P0^5;
sbit d6=P0^6;
sbit d7=P0^7;
sbit B4=B^4;
sbit B5=B^5;
sbit B6=B^6;
sbit B7=B^7;
void main()
{
Bk=0;
lcd();
B='A';
data_wr();
while(1);
}
void lcd()
{
B=0x03;
command_wr();
delay(5);
B=0x03;
command_wr();
delay(5);
B=0x03;
command_wr();
delay(5);
B=0x02;
command_wr();
delay(5);
B=0x01;
command_wr();
delay(5);
B=0x06;
command_wr();
delay(5);
B=0x0f;
command_wr();
delay(5);
}
void command_wr()
{
RS=0;
RW=0;
map();
toggle();
B=B<<4;
map();
toggle();
}
void map()
{
d4=B4;
d5=B5;
d6=B6;
d7=B7;
}
void toggle()
{
EN=1;
delay(5);
EN=0;
delay(5);
}
void data_wr()
{
RS=1;
RW=0;
map();
toggle();
B=B<<4;
map();
toggle();
}
void delay(unsigned int time)
{
for(i=0;i<time;i++)
for(j=0;j<120;j++);
}
