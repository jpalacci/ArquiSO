#include <video.h>

#define SCREEN 0xB8000
#define BLACK 0x00
#define SPACE 0x20
#define DEFAULT 0x0F
#define WIDTH 80
#define HEIGHT 25

static char video[HEIGHT][WIDTH];
static char attributes[HEIGHT][WIDTH];
static int i=0; //posicion del cursor horizontal
static int j=3;  // posicion del cursor vertical

void putChar(char a ) { // se define color estandar
		printChar(j,i, a ,DEFAULT );
		forwardCursor();
}
void setCursor(int f, int c){
	if(!validPosition(f,c)) return;
	i=c;
	j=f;
}
void updateScreen(){
	char * screen = (char*) SCREEN;
	for(int c=0; c<WIDTH; c++){
		for(int f=0; f<HEIGHT;f++){
			*(screen + f*WIDTH*2 + c*2)= video[f][c];
			*(screen + f*WIDTH*2 + c*2 +1)= attributes[f][c];
		}
	}
}
int getScreen(int f, int c){
	if(!validPosition(f,c)){
		return -1;
	}
	return (char)video[f][c];
}

void selection(int finit, int cinit, int ffin, int cfin){
 
	int auxi=i;
	int auxj=j;	
	setCursor(finit, cinit);
	while(validPosition(j,i) && (j<ffin || ((j==ffin) && (i<=cfin)) ) ){
		
		drawMouse(j,i);
		forwardCursorB();
	}
	setCursor(auxj, auxi);

}

void changeColor(int f, int c, char color){

		char * screen = (char*)SCREEN;

	*(screen + f*WIDTH*2 + c*2 + 1 )=(char)color;
		

}

void undoSelection(int finit, int cinit, int ffin, int cfin){
	int auxi=i;
	int auxj=j;	
	setCursor(finit, cinit);
	while(j<ffin || ((j==ffin) && (i<=cfin)) ){
		udrawMouse(j,i);
		forwardCursor();
	}
	setCursor(auxj, auxi);

}

void forwardCursor(){

	if(i==WIDTH-1){
		if(j==HEIGHT-1){
			 scroll();
			updateScreen();
		}else{
			j++;
			i=0;
		}
	}else{
		i++;
	}

}

void forwardCursorB(){

	if(i==WIDTH-1){
		if(j==HEIGHT-1){
			 return;
		}else{
			j++;
			i=0;
		}
	}else{
		i++;
	}

}

void lineJump(){
	int aux= j +1;
	while(j!=aux){
		forwardCursor();
	}
}

void scroll(){
	int auxf;
	for(auxf=1; auxf<HEIGHT;auxf++){
		copyRow(auxf,auxf-1);
	}
	clearRow(HEIGHT-1);
	j=HEIGHT-1;
	i=0;
}
void copyRow(int from, int to){
	for(int k=0; k<WIDTH;k++){
		video[to][k]=video[from][k];
		attributes[to][k]=attributes[from][k];
		clearPosition(from,k);
	}
}
void clearRow(int f){
	int k;
	for(k=0;k<WIDTH;k++){
		clearPosition(f,k);
	}
}
void clearPosition(int f, int c){
	if(!validPosition(f,c)) return;
	video[f][c]=' ';
}
void backwardCursor(){
	if(i==0){
		if(j!=0){
			j--;
			i=WIDTH-1;
		}
		//Llegamos a principio pantalla, nada que borrar
	}else{
		i--;

	}
}		


void printChar(int f, int c,  char a,  char color)
{
	if(!validPosition(f,c)) return;
	video[f][c] = a;
	updateScreen();

}


void drawMouse(int f, int c){
	if(!validPosition(f,c)) return;
	attributes[f][c]=(char) 0x30;
}
void udrawMouse(int f, int c){
	if(!validPosition(f,c)) return;
	 attributes[f][c]=(char)DEFAULT; // fondo negro con blanco como texto
}

int validPosition(int f, int c){
	return (f>=HEIGHT || c>=WIDTH)? 0:1;
}

void printMsg(int f, int c,  char*msg, char color)
{	
	if(!validPosition(f,c)) return;
	int previ=i;
	int prevj=j; //recuerdo posiciones del mouse
	i=c;
	j=f;
	while(*msg)
	{
		putChar(*msg);
		msg++;
	}
	i=previ;
	j=prevj;
}
void printMsgCursor( char * msg) // cursor position, default color
{
	while(*msg)
	{
		putChar(*msg);
		msg++;
	}
}


void clear()
{


	
	for(int f=0; f<HEIGHT; f++){
		for(int c=0; c<WIDTH; c ++){
			video[f][c]=' ';
			attributes[f][c] = (char)DEFAULT;
		}
	}

	updateScreen();
}
