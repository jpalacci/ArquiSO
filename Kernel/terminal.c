
#include <terminal.h>
#include <systemCalls.h>
#include <stdint.h>
#include <stdio.h>
#include <video.h>
#include <lib.h>

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
	if(bufferPosition == bufferStart + bufferSize){
			bufferPosition = bufferStart;
		}
	//bufferConsume nunca alcanza a bufferPosition por las implementaciones
	//del Kernel asi que si es al revez es Por que hay OverFLow e ignoro las que
	//vienen
	if(bufferConsume == bufferPosition+1){
		return ; //el buffer esta lleno
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
	sti();
	
}

int getTerminalBuffer(char * buffer, uint32_t length){
	cli();
	int charsConsume = 0;
	while(length != 0){
			if(bufferConsume == bufferPosition){
				return charsConsume;
			}
			*buffer = *bufferConsume;
			buffer++;
			charsConsume++;
			bufferConsume++;
			length--;	
			if(bufferConsume == bufferStart + bufferSize){
				bufferConsume = bufferStart;
			}
		}
	sti();
	return charsConsume;
}

