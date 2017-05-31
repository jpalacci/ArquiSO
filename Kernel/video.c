void printChar(int f, int c, char a, char color)
{
	
	char * first = (char*)0xB8000;
	char * position = 80*f*2 + c*2 + first;
	*position = a;
	position++;
	*position = color;

}

void drawMouse(int f, int c){
	char * first = (char*)0xB8000;
	char * position = 80*f*2 + c*2 + first;
	position++;
	*position= 0x33;
}
void udrawMouse(int f, int c){
	char * first = (char*)0xB8000;
	char * position = 80*f*2 + c*2 + first;
	position++;
	*position= 0x0F;
}

void printMsg(int f, int c, char*msg, char color)
{
	char * first = (char*)0xB8000 ;
	char * position = 80*f*2 + c*2 + first;

	while(*msg)
	{
		*position = *msg;
		position++;
		*position = color;
		position++;
		msg++;
	}
}


void clear()
{
	char * first = (char*)0xB8000;
	int i;
	for(i = 0; i<80*25*2; i++)
	{
		if(i%2 == 0)
		{
			*(first+i)=0x20;
		}
		else
		{
			*(first+i)=0x00;
		}
	}
}

void matrix()
{
	char * first = (char*)0xB8000;
	int i;
	for(i=0;i<80*25*2; i+=2)
	{
		if(i%8==0)
		{
			*(first+i)='|';
			*(first+i+1)=0x20;
		}
	}
}
