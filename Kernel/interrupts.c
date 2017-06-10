#include<video.h>
#include<lib.h>
#include <interrupts.h>
#include <rtc.h>
#include <keyboard.h>
#include <mouse.h>
#include <naiveConsole.h>

void io_wait();

#pragma pack(push)
#pragma pack(1)
typedef struct IDT_Entry {
  	uint16_t offset_l; //bit 0..15
	uint16_t selector;
	uint8_t zero_l;
	uint8_t attrs;
	uint16_t offset_m; //16..31
	uint32_t offset_h; //32..63
	uint32_t zero_h;
}IDT_Entry;

#pragma pack(pop)

static IDT_Entry * IDT = (IDT_Entry*) 0x00;

void setIDTEntry(uint64_t offset, int entry)
{
	IDT[entry].offset_l = (uint16_t)offset & 0xFFFF;
	IDT[entry].offset_m = (uint16_t)(offset >> 16) & 0xFFFF;
	IDT[entry].offset_h = (uint16_t)(offset >> 32) & 0xFFFFFFFF;
	IDT[entry].zero_l = 0;
	IDT[entry].zero_h = 0;
	IDT[entry].attrs = 0x8E;
	IDT[entry].selector = 0x08;

}



void loadIDT()
{
	
	setIDTEntry((uint64_t) timerTickHandler,0x20);
	setIDTEntry((uint64_t) master,0x23); 
	setIDTEntry((uint64_t) master,0x24); 
	setIDTEntry((uint64_t) master,0x25); 
	setIDTEntry((uint64_t) master,0x26); 
	setIDTEntry((uint64_t) master,0x27); 
	setIDTEntry((uint64_t) slave,0x28); 
	setIDTEntry((uint64_t) slave,0x29); 
	setIDTEntry((uint64_t) master,0x2A); 
	setIDTEntry((uint64_t) master,0x2B);
	setIDTEntry((uint64_t) master,0x2D); 
	setIDTEntry((uint64_t) master,0x2E);
	
	
	setIDTEntry((uint64_t) sys_callHandler,0x80); 
	setIDTEntry((uint64_t) keyboardHandler,0x21);
	setIDTEntry((uint64_t) mouse_handler,0x2C); 
	
	//sti();
	

}




void enablePIC()
{

	outputb(0x21,0xF8);
	outputb(0xA1,0xEF);
	
}

void io_wait()
{

	int time = 100000;
	while(time--);

}

void spure(){
	printMsg(10,10,"xxxxxxxxxx",0x20);
}


void timerTickHandlerC()
{
	char time[9];
	getTime(time);	
	printMsg(2,0,time,0x20);
}









