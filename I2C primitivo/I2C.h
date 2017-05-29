//Biblioteca I2C para a disciplina de microcontroladores
//Autora: Mariana Cabral

#include <AT89X51.H>
#include <stdio.h>

sbit SCL =  P1^0;
sbit SDA =  P1^1;

void write(unsigned char);
void start(void);
void stop(void);
unsigned char read();
void ack();
void nack();
void i2c_init();