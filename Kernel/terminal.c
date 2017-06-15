
#include <terminal.h>
#include <systemCalls.h>
#include <stdint.h>
#include <stdio.h>
#include <video.h>
#include <lib.h>
#include <naiveConsole.h>

static char * bufferConsume;
static char * bufferPosition;
static char * bufferStart;
static int bufferSize;
static int isEcho;

void echoON(){
	isEcho = 1;
}

void echoOF(){
	isEcho = 0;
}

//funcion para inicializar la terminal
//esta tiene que ir antes de que lleguen las interrupciones
void terminalInitializeC(char * Buffer, int size){
	bufferConsume = Buffer;
	bufferStart = Buffer;
	bufferPosition = Buffer;
	bufferSize = size;
	isEcho = 1;
}

//pone el char que le pasan en el buffer, si este
//esta lleno lo ignora
void putTerminalBuffer(char c){
	cli();
	
	//bufferConsume nunca alcanza a bufferPosition por las implementaciones
	//del Kernel asi que si es al revez es Por que hay OverFLow e ignoro las que
	//vienen
	if(bufferConsume == (bufferPosition+1) ){
		putChar('B');
		return ; //el buffer esta lleno
	}
	if(bufferConsume == (bufferStart+bufferSize) && bufferPosition == bufferStart){
		return;
	} 
	*bufferPosition = c;
	if(c == '\b'){
		backwardCursor();
		putChar(' ');
		backwardCursor();
	}
	else if(c == '\n'){
		lineJump();
		
	}
	else if(isEcho){
		putChar(*bufferPosition);
		
	}
	bufferPosition++;
	if(bufferPosition == (bufferStart + bufferSize)){
			bufferPosition = bufferStart;
		}
	ncPrintHex(bufferPosition);
	ncPrintHex(bufferConsume);
	sti();
	
}

int getTerminalBuffer(char * buffer, uint32_t length){
	cli();
	int charsConsume = 0;
	while(length != 0){
			if(bufferConsume == bufferPosition){
				return charsConsume;
			}
			if(bufferConsume == bufferStart + bufferSize){
				bufferConsume = bufferStart;
			}
			putChar('c');
			*buffer = *bufferConsume;
			buffer++;
			charsConsume++;
			bufferConsume++;
			length--;	
		}
	sti();
	return charsConsume;
}


