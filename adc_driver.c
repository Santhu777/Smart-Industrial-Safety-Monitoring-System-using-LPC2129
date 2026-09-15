#include<lpc21xx.h>
void adc_init()
{
PINSEL1=0X15400000;
ADCR=0X00200400;
}

#define done ((ADDR>>31)&1)
adc_read(unsigned int ch_num)
{
unsigned int result=0;
ADCR|=(1<<ch_num);
ADCR|=(1<<24);
while(done==0);
ADCR^=(1<<24);
ADCR^(1<<ch_num);
result=(ADDR>>6)&0x3ff;
return result;
}
