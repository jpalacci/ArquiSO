
#include "stdio.h"


void clearEditor(){
	sys_call(5,0,0);
}

void main(){
	clearEditor();
	char ** s = 600000;
	char * editor = "chomp\n";
	s[0]= editor;
	printFF("%s",s, NULL);
	char c;
	int exitFlag = 0;
	while(!exitFlag){
		c = getchar();
		if(c == '%'){
			char ** ss = 6500000;
			char * sos = 7000000;
			ss[0] = sos;
			scanFF("%s",ss, NULL);
			if(strcmp(sos,"exit") == 0){
				exitFlag = 1;
				clearEditor();
			}
		}
	}
}

