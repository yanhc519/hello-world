#include "usart1.h"
#include "led.h"
#include "beep.h"
#include "lcd.h"
#include "key.h"
#include "stdarg.h"

#define  putc	uart1SendChar
#define  puts	uart1SendChars

/*********************************************************************************
**********************MCUÆôÃ÷ STM32F407Ó¦ÓÃ¿ª·¢°å(¸ßÅä°æ)*************************
**********************************************************************************
* ÎÄ¼þÃû³Æ: Àý³Ì5 USART1ÃüÁî¿ØÖÆÖ÷º¯Êýmain.c                                     *
* ÎÄ¼þ¼òÊö£ºUSART1ÃüÁî¿ØÖÆÊ¹ÓÃ                                                   *
* ´´½¨ÈÕÆÚ£º2015.03.06                                                           *
* °æ    ±¾£ºV1.0                                                                 *
* ×÷    Õß£ºClever                                                               *
* Ëµ    Ã÷£ºÀûÓÃ´®¿Úµ÷ÊÔÖúÊÖ¾­¹ýUSART1¿ØÖÆLEDÁÁÃðÓë·äÃùÆ÷Ïì±Õ£¬°´KEY0´®¿Ú·¢ËÍÊý  *
            ¾Ýµ½´®¿Úµ÷ÊÔÖúÊÖ                                                     * 
* ÌÔ±¦µêÆÌ£ºhttps://shop125046348.taobao.com                                     *
**********************************************************************************
*********************************************************************************/

/*
There are 7 format specifiers:
%c - Character
%s - String
%i - signed Integer (16 bit)
%u - Unsigned integer (16 bit)
%l - signed Long (32 bit)
%n - uNsigned loNg (32 bit)
%x - heXadecimal (16 bit)
Field width, floating point and other standard printf() features are not supported.
*/

static const unsigned long dv[] = {
	//  4294967296      // 32 bit unsigned max
	1000000000,     // +0
	100000000,     // +1
	10000000,     // +2
	1000000,     // +3
	100000,     // +4
				//       65535      // 16 bit unsigned max     
	10000,     // +5
	1000,     // +6
	100,     // +7
	10,     // +8
	1,     // +9
};

static void xtoa(unsigned long x, const unsigned long *dp)
{
	char c;
	unsigned long d;
	if (x) {
		while (x < *dp) ++dp;
		do {
			d = *dp++;
			c = '0';
			while (x >= d) ++c, x -= d;
			putc(c);
		} while (!(d & 1));
	}
	else
		putc('0');
}

static void puth(unsigned n)
{
	static const char hex[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	putc(hex[n & 15]);
}

void printf(char *format, ...)
{
	char c;
	short i;
	int n;

	va_list a;
	va_start(a, format);
	c = *format++;
	while(c) 
	{
		if (c == '%') {
			switch (c = *format++) {
			case 's':                       // String
				puts(va_arg(a, char*));
				break;
			case 'c':                       // Char
				putc(va_arg(a, int));
				break;
			case 'i':                       // 16 bit Integer
			case 'u':                       // 16 bit Unsigned
				i = va_arg(a, int);
				if (c == 'i' && i < 0) i = -i, putc('-');
				xtoa((unsigned short)i, dv + 5);
				break;
			case 'l':                       // 32 bit Long
			case 'n':                       // 32 bit uNsigned loNg
				n = va_arg(a, int);
				if (c == 'l' &&  n < 0) n = -n, putc('-');
				xtoa((unsigned int)n, dv);
				break;
			case 'x':                       // 16 bit heXadecimal
				i = va_arg(a, int);
				puth(i >> 12);
				puth(i >> 8);
				puth(i >> 4);
				puth(i);
				break;
			case 0: return;
			default: putc(c);
			}
		}
		else
		{
			putc(c);
		}
		c = *format++;
	}
	va_end(a);
}

int main(void)
{   
	char *s;
   char c;
   int i;
   unsigned u;
   long int l;
   long unsigned n;
   unsigned x;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //ÉèÖÃÏµÍ³ÖÐ¶ÏÓÅÏÈ¼¶·Ö×é2
	delay_init();		      //ÑÓÊ±³õÊ¼»¯ 
	uart1_init(9600);	    //´®¿Ú³õÊ¼»¯²¨ÌØÂÊÎª9600
	KEY_Init();
	LED_Init();		  		  //³õÊ¼»¯ÓëLED 
	BEEP_Init();          //·äÃùÆ÷³õÊ¼»¯
  LCD_Init();           //³õÊ¼»¯LCD FSMC½Ó¿ÚºÍÏÔÊ¾Çý¶¯
	BRUSH_COLOR=RED;      //ÉèÖÃ»­±ÊÑÕÉ«ÎªºìÉ«
	
	LCD_DisplayString(10,10,24,"Illuminati STM32F4");	
  LCD_DisplayString(20,40,16,"Author:Clever");
	LCD_DisplayString(30,80,24,"5.USART1 TEST");
	LCD_DisplayString(50,110,16,"Please send control cmd");

	while(1)
	{
//		key_scan(0);
//		
//		if(keyup_data==KEY0_DATA)
//		  {
//		   uart1SendChars("U",1);
//		  }
			
		s = "test";
   c = 'X';
   i = -12345;
   u =  12345;
   l = -1234567890;
   n =  1234567890;
   x = 0xABCD;

   printf("String        %s\r\n", s);
   printf("Char          %c\r\n", c);
   printf("Integer       %i\r\n", i);
   printf("Unsigned      %u\r\n", u);
   printf("Long          %l\r\n", l);
   printf("uNsigned loNg %n\r\n", n);
   printf("heX           %x\r\n", x);

   printf("multiple args %s %c %i %u %l %n %x\r\n", s, c, i, u, l, n, x);

   printf("\r\n*** Done ***\r\n");
   
		delay_ms(500);
		printf("%s", "\r\n*** printf() test ***\r\n");
//		uart1SendChars("0",1);
			
	}
}

