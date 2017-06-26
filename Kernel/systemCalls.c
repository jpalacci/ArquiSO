#include <stdint.h>
#include <terminal.h>
#include <video.h>
#include <lib.h>
#include <moduleLoader.h>

#define DUMMY  1
#define EDITOR 2
#define FORTUNE 3
static void * const dummyAddress = (void*)0xA00000;
static void * const shellAddress = (void*)0xC00000;
static void * const currentAddress = (void*)0x800000;
static void * const editorAddress = (void*)0xE00000;
static void * const fortuneAddress = (void*)0x600000;
typedef int (*EntryPoint)();

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

void sys_call_runC(int program){
	void * moduleAdress;
	switch(program){

		case DUMMY:
			moduleAdress = dummyAddress;
			break;
		case EDITOR:
			moduleAdress = editorAddress;
			break;

		case FORTUNE:
			moduleAdress=fortuneAddress;
			break;	
	}
	mapModulesLogical(moduleAdress);
	updateCR3();
	((EntryPoint)currentAddress)();

	mapModulesLogical(shellAddress);
	updateCR3();
	((EntryPoint)currentAddress)();

}

void sys_call_changeModuleEnvironmetC(int i, int j){
	changeStartModule(i,j);
	return;
}

void sys_call_undoBackwardsC(int from){
	changeStopBackwards(from);
}