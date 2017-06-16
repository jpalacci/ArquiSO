
#include <stdint.h>
#include <terminal.h>
#include <video.h>

#define DUMMY  1
static void * const dummyAddress = (void*)0xA00000;
static void * const shellAddress = (void*)0xC00000;
static void * const currentAddress = (void*)0x800000;
typedef int (*EntryPoint)();

void mapModulesLogical(uint64_t  physical );
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
	putChar('c');
	if(on){
		putChar('f');
		echoON();
		return;
	}
	echoOF();
	return;

}

void sys_call_runC(int program){
	char * moduleAdress;
	switch(program){

		case DUMMY:
			moduleAdress = dummyAddress;
			break;
	}
	mapModulesLogical(moduleAdress);
	updateCR3();
	((EntryPoint)currentAddress)();
	mapModulesLogical(shellAddress);
	updateCR3();
	((EntryPoint)currentAddress)();

}