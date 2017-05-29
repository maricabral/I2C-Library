//Biblioteca I2C para a disciplina de microcontroladores
//Autora: Mariana Cabral


#include <I2C_advanced.h>

void init(void)
{
	SDA = 1;
	SCL = 1;
}

void start(void)
{
	SDA = 1;
	SCL = 1;
	SDA = 0;
	SCL = 0;
}

void stop(void)
{
	SCL=0;
	SDA=0;
	SCL=1;
	SDA=1;
}

void ack(void)
{
	SDA = 0;
	SCL=0;
	SDA=1;
	SCL=1;
}

void nack(void)
{
	SDA = 1;
	SCL = 1;
	SCL = 0;
	SDA = 1;
}

void write(unsigned char Data)
{
	 unsigned char i;
	 for (i = 0; i < 8; i++) {
		if ((Data & 0x80) == 0)
			SDA = 0;
		else
			SDA = 1;
		SCL = 1;
	 	SCL = 0;
		Data<<=1;
	 }
	 
	 SDA = 1;
	 SCL = 1;
	 SCL = 0;
}

unsigned char read()
{
	unsigned char i, Data=0;
	for (i = 0; i < 8; i++) {
		SCL = 1;
		if(SDA)
			Data |=1;
		if(i<7)
			Data<<=1;
		SCL = 0;
	}
	return Data;
}

void i2c_device_write(unsigned char slave ,unsigned char reg_add ,unsigned char dado)
{
	start();
	write(slave); //endereço do escravo
	ack();
	write(reg_add); //endereço desejado à escrita
	ack();
	write(dado); //dado para ser escrito
	ack();
	stop();
}

unsigned char i2c_device_read(unsigned char slave, unsigned char reg_add)
{
	unsigned char dado=0;
	start();
	write(slave);//endereço do escravo
	ack();
	write(reg_add);   //endereço desejado à ser lido
	ack();
	start();
	write(slave|1); //chamar o escravo com o bit de leitura acionado
	dado=read();
	nack();
	stop();
	return dado;
}

//EXEMPLO SUPONDO QUE ENDEREÇO DO ESCRAVO É 0XD0
void main()
{
	unsigned char resposta1, resposta2;
	init();//iniciando dispositivo 12c
	
	//escrevendo 10 no endereço 0x30
	i2c_device_write(0xD0 ,0X30 ,10);
	
	//lendo os dados do endereço 0x30
	resposta1 = i2c_device_read(0xD0, 0X30);
	
	//lendo os dados do endereço 0x31
	resposta2 = i2c_device_read(0xD0, 0X31);
}