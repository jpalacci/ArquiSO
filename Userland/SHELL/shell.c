

#include "stdio.h"
#include "shell.h"

void helpShell(){
	char ** s = 600000;
	char * help = "Help\n the commands are clear, help, echo, ls and man\n write man \"comand\" for more information";
	s[0]= help;
	printFF("%s",s, NULL);
	putchar('\n');
	
}
void ls(){
	char ** s = 600000;
	char * ls = "Modules: dummy, editor, shell, fortune";
	s[0]= ls;
	printFF("%s",s, NULL);
	putchar('\n');
}
void man(char * buffer){
	char ** s = 600000;
	char * man;
	if(!strcmp("help", buffer)){
		man = "HELP\n use this comand to see all the comands";
	}
	else if(!strcmp("clear", buffer)){
		man = "CLEAR\n clear the video use by the shell";
	}
	else if(!strcmp("echo", buffer)){
		man = "ECHO\n Use \"echo on\" to turn on the echo and \"echo off\" to turn it off  ";
	}
	else if(!strcmp("ls", buffer)){
		man = "LS\n display all modules";
	}
	else{
		man = "invalid command for man";
	}
	s[0] = man;
	printFF("%s",s, NULL);
	putchar('\n');

}

void run(char * c){
	if(!strcmp("dummy", c)){
		sys_call(7,0,1);
	}
	else if(!strcmp("editor")){
		sys_call(7,0,2);
	}
	return;
}

void echoShellON(){
	sys_call(6,0,1);
}
void echoShellOFF(){
	sys_call(6,0,0);
}

void error(char * buffer){
	char ** s = 600000;
	s[0] = buffer;
	printFF("%s", s, NULL);
	putchar(':');
	putchar(' ');
	char * error = "command not found";
	s[0]= error;
	printFF("%s",s, NULL);
	putchar('\n');
}

void clearShell(){
	sys_call(5,0,0);
}

void errorParser(int error){
	char ** s = 5000000;
	char * str;
	if(error == 1){
	str = "General Protection";
	s[0] = str;
	printFF("%s",s,NULL);
	return;
	}
	if(error == 2){
	s[0] = str;
	printFF("%s",s,NULL);
	return;
	}
}


//shell

void printShellComand(){
	char ** s = 5000000;
	char * str = "shell>";
	s[0] = str;
	printFF("%s",s,NULL);
}
int main(int error){
	char ** ss = 6500000;
	char * sos = 7000000;
	ss[0] = sos;
	putNumber(error);
	while(1){
		putchar('\n');
		errorParser(error);
		printShellComand();
		if(scanFF("%s",ss, NULL)==0){
			parser(sos);
		}else {
			char ** s = 600000;
			char * help = "ScanFF Buffer OverFlow";
			s[0]= help;
			putchar('\n');
			printFF("%s",s, NULL);
		}

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
	if(!strcmpN("echo", buffer,4)){
		if(!strcmp("on", buffer+5)){
			echoShellON();
			return;
		}
		echoShellOFF();
		return;
	}
	if(*buffer == '.' && *(buffer+1) == '\\'){
		run((buffer+2));
		return;
	}
	if(!strcmpN("man", buffer,3)){
			man(buffer+4);
			return;
	}
	if(!strcmp("ls", buffer)){
		ls();
		return;
	}
	if(*buffer == '\n'){
		return;
	}
	error(buffer);
	
	}
