//Biblioteca I2C para a disciplina de microcontroladores
//Autora: Mariana Cabral


#include <AT89X51.H>
#include <stdio.h>

sbit SDA = P1^0;
sbit SCL = P1^1;

void init(void);
void start(void);
void stop(void);
void ack(void);
void nack(void);
void write(unsigned char dado);
unsigned char read(void);
void i2c_device_write(unsigned char slave ,unsigned char reg_add ,unsigned char dado);
unsigned char i2c_device_read(unsigned char slave, unsigned char reg_add);