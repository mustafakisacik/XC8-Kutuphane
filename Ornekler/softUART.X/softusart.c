/**********************************************************
*  Yazar 	: sigmoid
*  Web 		: http://www.gencmucitler.com
*  ?lk		: Eyl�l 2017
*  D�zenleme: Yok 
*  Versiyon : 0.1
*  A��klama : Yaz�l�msal olarak ger�ekle�tirilmi� RS232
*    8 bit data no parity
***********************************************************/

#include <xc.h>
#include "softusart.h"

void softusart_baslat(void)
{
	softtxpin=1;	//bo�tayken 1.
	softrxpintris=1;
	softtxpintris=0;
}

void softusart_yaz(char veri)
{
	char i;
	softtxpin=0;	//start biti
	_delay(usartdelaycyc-sucyc1);
	for(i=8;i>0;i--)
	{
		veri=veri>>1;
		softtxpin=CARRY;
		_delay(usartdelaycyc-sucyc2);
	}	
	softtxpin=1;	//stop biti
	_delay(usartdelaycyc);
}

char softusart_oku(void)
{
	char i;
	unsigned temp=0;
	while(softrxpin);	//startbitini bekle.
	_delay(usartdelaycyc);
	_delay(usartdelaycycyarim-sucyc1rcv);	
	for(i=8;i>0;i--)
	{
		temp=temp>>1;
		if(softrxpin)
			temp=temp|0x80;
		else
			_delay(7);

		_delay(usartdelaycyc-sucyc2rcv);
	}
	
    //stop biti kadar bekle.
	_delay(usartdelaycycyarim);
	while(!softrxpin);
	return temp;	
}


//printf fonksiyonu i�in
void putch(unsigned char byte)
{
	softusart_yaz(byte);
}


