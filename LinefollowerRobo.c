#include<REG51.H>
sbit ls=P0^0;
sbit rs=P0^1;

#define motor P2
#define forward 0x06
#define turn_left 0x82
#define turn_right 0x14
#define stop 0x00
void main()
{
motor=stop;
while(1)
{
if(ls && rs)
	motor=forward;
else if(!ls && rs)
	motor=turn_left;
else if(ls && !rs)
	motor=turn_right;
else if(!ls && !rs)
	motor=stop;
}
}
