#include <LPC214x.h>

void delay_ms(unsigned int count)
{
  unsigned int j=0,i=0;
  for(j=0;j<count;j++)
  {
    for(i=0;i<3000;i++);
  }
}

int main()
{
	PINSEL0 = 0x00000000; // making pins of 0-15 of P0 as GPIO
	IODIR0 =  0x00000003; // 
	
	 while(1)
    {
       IOSET0 = 0x00000003;     // Make all the Port pins as high  
         delay_ms(1000);

       IOCLR0 = 0x00000003;     // Make all the Port pins as low  
         delay_ms(1000);
    }
}

