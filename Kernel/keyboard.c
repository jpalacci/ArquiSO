#include <lib.h>
#include <video.h>
#include <terminal.h>
#include <stdio.h>
#define LEFT_SHIFT_MAKE   	(char)0x2A
#define RIGHT_SHIFT_MAKE    (char)0x36
#define CAPS_LOCK           (char)0x3A
#define LEFT_SHIFT_BREAK    (char)0xAA
#define RIGHT_SHIFT_BREAK   (char)0xB6
#define CONTROL_MAKE        260
#define CONTROL_R           (char)0x13
#define CONTROL_BREAK       0x9D
#define NOCHAR -1
#define NORMALCOLUMN 1
#define SHIFTEDCOLUMN 2
#define CAPSLOCKEDCOLUMN 3
#define ON 1
#define OFF 0
char kbd_EN[][4] = {
	//USA
	{ 0x00, NOCHAR, NOCHAR, NOCHAR }, //empty,
	{ 0x01, NOCHAR, NOCHAR, NOCHAR }, //esc
	{ 0x02, '1', '!', '1' },
	{ 0x03, '2', '@', '2' },
	{ 0x04, '3', '#', '3' },
	{ 0x05, '4', '$', '4' },
	{ 0x06, '5', '%', '5' },
	{ 0x07, '6', '^', '6' },
	{ 0x08, '7', '&', '7' },
	{ 0x09, '8', '*', '8' },
	{ 0x0A, '9', '(', '9' },
	{ 0x0B, '0', ')', '0' },
	{ 0x0C, '-', '_', '-' },
	{ 0x0D, '=', '+', NOCHAR },
	{ 0x0E, '\b', '\b', '\b' }, //backspace
	{ 0x0F, '\t', '\t', '\t' }, //tab
	{ 0x10, 'q', 'Q', 'Q' },
	{ 0x11, 'w', 'W', 'W' },
	{ 0x12, 'e', 'E', 'E' },
	{ 0x13, 'r', 'R', 'R' },
	{ 0x14, 't', 'T', 'T' },
	{ 0x15, 'y', 'Y', 'Y' },
	{ 0x16, 'u', 'U', 'U' },
	{ 0x17, 'i', 'I', 'I' },
	{ 0x18, 'o', 'O', 'O' },
	{ 0x19, 'p', 'P', 'P' },
	{ 0x1a, '[', '{', '[' },
	{ 0x1b, ']', '}', ']' },
	{ 0x1c, '\n', '\n', '\n' },//enter
	{ 0x1d, NOCHAR, NOCHAR, NOCHAR },//left ctrl
	{ 0x1e, 'a', 'A', 'A' },
	{ 0x1f, 's', 'S', 'S' },
	{ 0x20, 'd', 'D', 'D' },
	{ 0x21, 'f', 'F', 'F' },
	{ 0x22, 'g', 'G', 'G' },
	{ 0x23, 'h', 'H', 'H' },
	{ 0x24, 'j', 'J', 'J' },
	{ 0x25, 'k', 'K', 'K' },
	{ 0x26, 'l', 'L', 'L' },
	{ 0x27, ';', ':', ';' },
	{ 0x28, '\'', '"', '\'' },
	{ 0x29, '`', '~', '`' },
	{ 0x2a, LEFT_SHIFT_MAKE, LEFT_SHIFT_MAKE, LEFT_SHIFT_MAKE },//left shift
	{ 0x2b, '\\', '|', NOCHAR },
	{ 0x2c, 'z', 'Z', 'Z' },
	{ 0x2d, 'x', 'X', 'X' },
	{ 0x2e, 'c', 'C', 'C' },
	{ 0x2f, 'v', 'V', 'V' },
	{ 0x30, 'b', 'B', 'B' },
	{ 0x31, 'n', 'N', 'N' },
	{ 0x32, 'm', 'M', 'M' },
	{ 0x33, ',', '<', ',' },
	{ 0x34, '.', '>', '.' },
	{ 0x35, '/', '?', '/' },
	{ 0x36, RIGHT_SHIFT_MAKE, RIGHT_SHIFT_MAKE, RIGHT_SHIFT_MAKE },//right shift
	{ 0x37, '*', NOCHAR, NOCHAR  },//keypad *
	{ 0x38, NOCHAR, NOCHAR, NOCHAR  },//left alt
	{ 0x39, ' ', ' ', NOCHAR  },
	{ 0x3a, CAPS_LOCK, CAPS_LOCK, CAPS_LOCK  },//caps
	{ 0x3b, NOCHAR, NOCHAR, NOCHAR  },//f1
	{ 0x3c, NOCHAR, NOCHAR, NOCHAR  },//f2
	{ 0x3d, NOCHAR, NOCHAR, NOCHAR  },//f3
	{ 0x3e, NOCHAR, NOCHAR, NOCHAR  },//f4
	{ 0x3f, NOCHAR, NOCHAR, NOCHAR  },//f5
	{ 0x40, NOCHAR, NOCHAR, NOCHAR  },//f6
	{ 0x41, NOCHAR, NOCHAR, NOCHAR  },//f7
	{ 0x42, NOCHAR, NOCHAR, NOCHAR  },//f8
	{ 0x43, NOCHAR, NOCHAR, NOCHAR  },//f9
	{ 0x44, NOCHAR, NOCHAR, NOCHAR  },//f10
	{ 0x45, NOCHAR, NOCHAR, NOCHAR  },//num
	{ 0x46, NOCHAR, NOCHAR, NOCHAR  },//scroll
	{ 0x47, '7', NOCHAR, NOCHAR  },//keypad 7
	{ 0x48, NOCHAR, NOCHAR, NOCHAR  },//keypad 8
	{ 0x49, '9', NOCHAR, NOCHAR  },//keypad 9
	{ 0x4a, '-', NOCHAR, NOCHAR  },//keypad -
	{ 0x4b, NOCHAR, NOCHAR, NOCHAR  },//keypad 4
	{ 0x4c, '5', NOCHAR, NOCHAR  },//keypad 5
	{ 0x4d, NOCHAR, NOCHAR, NOCHAR  },//keypad 6
	{ 0x4e, '+', NOCHAR, NOCHAR  },//keypad +
	{ 0x4f, '1', NOCHAR, NOCHAR  },//keypad 1
	{ 0x50, NOCHAR, NOCHAR, NOCHAR  },//keypad 2
	{ 0x51, '3', NOCHAR, NOCHAR  },//keypad 3
	{ 0x52, '0', NOCHAR, NOCHAR  },//keypad 0
	{ 0x53, '.', NOCHAR, NOCHAR  },//keypad 0
	{ 0x57, NOCHAR, NOCHAR, NOCHAR },//f11
	{ 0x58, NOCHAR, NOCHAR, NOCHAR }//f12
};


static int counter = 0;
static int shift=OFF;
static int caps=OFF;

//lee del teclado, lo codifica en un char 
//se lo entrega a la terminal
void keyboardHandlerC(){
	
	char c=inputb(0x60);
	if(c==CAPS_LOCK){
		caps= (caps==ON)? OFF:ON;
		return;
	}
	if(c== LEFT_SHIFT_MAKE || c== RIGHT_SHIFT_MAKE){
		shift=ON;
		return;
	}
	if(c== LEFT_SHIFT_BREAK || c== RIGHT_SHIFT_BREAK){
		shift=OFF;
		return;
	}	
	if(!(c & 0x80))
	{	
		if(caps==ON){
			putTerminalBuffer(kbd_EN[(int)c][3]);
		}
		else if(shift==ON){
			putTerminalBuffer(kbd_EN[(int)c][2]);
		}
		else{
			putTerminalBuffer(kbd_EN[(int)c][1]);
		}
		return;
	}
}

			
	
