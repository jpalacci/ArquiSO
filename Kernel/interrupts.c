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
   uint16_t offset_1; // offset bits 0..15
   uint16_t selector; // a code segment selector in GDT or LDT
   uint8_t ist;       // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   uint8_t type_attr; // type and attributes
   uint16_t offset_2; // offset bits 16..31
   uint32_t offset_3; // offset bits 32..63
   uint32_t zero;     // reserved
}IDT_Entry;

#pragma pack(pop)

static IDT_Entry * IDT = (IDT_Entry*) 0x00;

void setIDTEntry(uint64_t offset, uint16_t entry, uint8_t attr)
{
	IDT[entry].offset_1 = (uint16_t)(offset & 0xFFFF);
	IDT[entry].offset_2 = (uint16_t)((offset & 0xFFFF0000) >> 16);
	IDT[entry].offset_3 = (uint16_t)((offset & 0xFFFF00000000) >> 32);
	IDT[entry].zero = 0;
	IDT[entry].ist = 0;
	IDT[entry].type_attr = attr;

}

void loadIDT()
{
	
	setIDTEntry((uint64_t) timerTickHandler,0x20, 0x8E);
	setIDTEntry((uint64_t) keyboardHandler,0x21, 0x8E);
	setIDTEntry((uint64_t) mouse_handler,0x2C, 0x8E); 
	setIDTEntry((uint64_t) syscallHandler,0x80, 0x8E); 
	
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



void timerTickHandlerC()
{
	char time[9];
	getTime(time);	
	printMsg(2,0,time,0x20);
}









