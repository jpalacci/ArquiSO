
#include <stdint.h>
#include <terminal.h>
#include <video.h>
//escribe en el file descriptor que le pasen.
//solo tiene implementado para imprimir por salida estandar
void sys_call_writeC(uint32_t stdout, char * msg, uint32_t length){
	if(stdout == 0){
		while(length != 0){
			if(*msg == '\n'){
				lineJump();
			}
			else{
				putChar(*msg);
			}
			msg++;
			length--;	
		}
	}
		
}
//lee del file descriptor que le pasen.
//solo tiene implementado para leer de la entrada estandar
uint32_t sys_call_readC(uint32_t stdin, char * buffer, uint32_t length){

	if(stdin == 0){
		return getTerminalBuffer(buffer, length);
	}
	//no leyo nada
	return 0;
}

void sys_call_clearC(){
	int i;
	for(i=25; i>2;i--){
		clearRow(i);
	}
	setCursor(3,0);
}

void sys_call_echoC(int on){
	if(on){
		echoON();
		return;
	}
	echoOF();
	return;

}