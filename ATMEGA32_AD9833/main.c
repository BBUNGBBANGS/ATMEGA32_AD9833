
#define F_CPU 7372800UL

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <util/delay.h>

static void Uart_Init(void);
static void Uart_Transmit(char data);
static void Uart_Transmit_Array(char *data_ptr, unsigned char length);
static void Clear_Tx_Buffer(char *buf,unsigned int length);
int main(void)
{
    char tx_buf[100] = {0,};
    Uart_Init();
    while (1) 
    {
		sprintf(tx_buf,"<Uart Print Test> \n");
		Uart_Transmit_Array(tx_buf,strlen(tx_buf));
		Clear_Tx_Buffer(tx_buf,100);
        _delay_ms(100);
    }
}

static void Uart_Init(void)
{
	UCSRB= (1<<RXEN) | (1<<TXEN);                  // Enable Receiver and Transmitter
	UCSRC= (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0);   // Asynchronous mode 8-bit data and 1-stop bit
	UCSRA= 0x00;                                   // Clear the UASRT status register
	UBRRL = 3; //115200bps 3(7.3728Mhz)
	UBRRH = 0; //115200bps 3(7.3728Mhz)
}

static void Uart_Transmit_Array(char *data_ptr, unsigned char length)
{
    unsigned char ch;
    for(ch=0;ch<length;ch++)
    {
        Uart_Transmit(*data_ptr++);
    }
}

static void Uart_Transmit(char data)
{
    /* Wait for empty transmit buffer */
    while (!( UCSRA & (1<<UDRE)));
    /* Put data into buffer, sends the data */
    UDR = data;
}
static void Clear_Tx_Buffer(char *buf,unsigned int length)
{
    for(unsigned int i = 0; i < length; i++)
    {
        buf[i] = 0;
    }
}