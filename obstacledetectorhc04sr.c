#include<reg51.h>
#define port P2
#define dataport P0
int cms;
sbit trig=P3^5;
sbit rs=port^0;
sbit rw=port^1;
sbit e=port^2;
void delay(unsigned int msec)
{
int i,j;
for(i=0;i<msec;i++)
for(j=0;j<1275;j++);
}
void lcd_cmd(unsigned char item)
{
dataport = item;
rs = 0;
rw=0;
e=1;
delay(1);
e=0;
return;
}
void lcd_data(unsigned char item)
{
dataport = item;
rs=1;
rw=0;
e=1;
delay(1);
e=0;
return;
}
void lcd_data_string(unsigned char *str)
{
int i=0;
while(str[i]!='\0')
{
lcd_data(str[i]);
i++;
delay(1);
}
return;
}
void send_pulse(void)
{
TH0=0x00;
TL0=0x00;
trig=1;
delay(5);
trig=0;
}
unsigned int get_range(void)
{
long int timer_val;
send_pulse();
while(!INT0);
while(INT0);
timer_val=(TH0<<8)+TL0;
lcd_cmd(0x81);
lcd_data_string("output");
lcd_cmd(0x80);
if(timer_val<38000)
{
cms=timer_val/59;
if(cms!=0)
{
lcd_data(cms+48);
}
}
else
{
lcd_cmd(0x06);
lcd_data_string("object out of range");
}
return cms;
}
void main()
{
lcd_cmd(0x38);
lcd_cmd(0x0c);
delay(2);
lcd_cmd(0x01);
delay(2);
lcd_cmd(0x81);
delay(2);
lcd_data_string("start");
delay(20);
TMOD=0x09;
TR0=1;
TH0=0x00;
TL0=0x00;
P3|=0x04;
while(1)
{
get_range();
delay(2);
}
}
