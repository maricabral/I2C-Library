//Biblioteca I2C para a disciplina de microcontroladores
//Autora: Mariana Cabral

#include <I2C.h>

void i2c_init()
{
	SDA = 1;
	SCL = 1;
}
 
void start()
{
	SDA = 1;
	SCL = 1;
	SDA = 0;
	SCL = 0;
}

void stop()
{
	SCL = 0;
	SDA = 0;
	SCL = 1;
	SDA = 1;
}

void ack()
{
	SDA = 0;
	SCL = 1;
	SCL = 0;
	SDA = 1;
}
 
void nack()
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

//EXEMPLO SUPONDO QUE O ENDEREÇO DO ESCRAVO É 0XD0
void main()
{
	unsigned char resposta1, resposta2, resposta3;
	
	i2c_init(); //inicialização do dispositivo i2c
	
	//ESCREVER 10 NO ENDEREÇO 20
	start();
	write(0xD0);//chama o escravo
	write(0x20);//chama o endereço desejado
	write(10);//escreve o dado desejado
	stop();
	
	//LER O ENDEREÇO 30	
	start();
	write(0xD0);//chama o escravo
	write(0x30);//chama o endereço desejado
	start();
	write(0xD0 | 1);//chama o escravo com o bit de leitura acionado
	resposta1 = read(); //leu o endereço 0x30
	ack();//continua a leitura
	resposta2 = read();//leu o endereço 0x31
	ack();//continua a leitura
	resposta3 = read();//leu o endereço 0x32
	nack();//para a leitura
	stop();
	
}