

#include "stdio.h"
#include "shell.h"

void helpShell(){
	char ** s = 600000;
	char * help = "Help\n the commands are clear and help";
	s[0]= help;
	printFF("%s",s, NULL);
	putchar('\n');
	
}

void run(char * c){
	if(strcmp("editor", c)){
		editor();
	}
}

void echoShellON(){
	sys_call(6,0,1);
}
void echoShellOF(){
	sys_call(6,0,0);
}

void error(){
	char ** s = 600000;
	char * help = "error command not found";
	s[0]= help;
	printFF("%s",s, NULL);
	putchar('\n');
}

void clearShell(){
	sys_call(5,0,0);
}


//shell

void printShellComand(){
	char ** s = 5000000;
	char * str = "shell>";
	s[0] = str;
	printFF("%s",s,NULL);
}
int main(){
	char ** ss = 6500000;
	char * sos = 7000000;
	ss[0] = sos;
	while(1){
		printShellComand();
		scanFF("%s",ss, NULL);
		printFF("%s",ss,NULL);
		parser(sos);
	}
	
}

void parser(char * buffer){
	if(!strcmp("help", buffer)){
		helpShell();
		return;
	}
	if(!strcmp("clear", buffer)){
		clearShell();
		return;
	}
	if(!strcmp("echoON", buffer)){
		echoShellON();
		return;
	}
	if(!strcmp("echoOF", buffer)){
		echoShellOF();
		return;
	}
	if(*buffer == '.' && *(buffer+1) == '\\'){
		run((buffer+2));
		return;
	}
	if(*buffer == '\n'){
		return;
	}
	error();
	
	}
void editor(){
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
				clearShell();
			}
		}
	}
}