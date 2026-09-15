#include<lpc21xx.h>
#define green_led 1<<5
#define red_led 1<<7
#define flame 1<<8
#define pir 1<<9
int main()
{
int temp=40;
adc_init();
lcd_init();
uart0_init(9600);
	IODIR0|=green_led;
	IODIR0|=red_led;
	IODIR0 &=~(flame|pir);
	//IODIR0&=~pir;
	IOSET0|=green_led;
	IOSET0|=red_led;
while(1)
{
temp=adc_read(1);
temp=(temp*330)/1023;
uart0_string("\r\n temperature:");
	uart0_integer(temp);
	lcd_cmd(0x80);
	lcd_string("temperature:");
	lcd_integer(temp);
//pir=adc_read(3);
uart0_string("\r\n pir sensor:");
if(!(IOPIN0&pir))
	uart0_string("worker detected");
else
	uart0_string(" worker notdetected");
uart0_string("\r\n flame sensor:");
if(!(IOPIN0&flame))
uart0_string("fire detected");
else
uart0_string("fire no detected");
uart0_string("\r\n machine status:");
if(temp<40&&((IOPIN0&pir)==1)&&((IOPIN0&flame)==1))
{
uart0_string(" safe");
	uart0_string("\r\n led :");
uart0_string("green led on");
	lcd_cmd(0xc0);
	lcd_string("status:");
	IOSET0=green_led;
	IOCLR0=red_led;
}
else
{
uart0_string(" no safe");
	uart0_string("\r\n led :");
uart0_string(" red led on");
	IOSET0=red_led;
	IOCLR0=green_led;
}
delay_ms(500);
}
}
