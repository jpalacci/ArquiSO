

#include <stdio.h>
#include <shell.h>
void help(){
	char ** s = 600000;
	char * help = "pusiste Help";
	s[0]= help;
	printFF("%s",s, NULL);
	
}

void run(char * c){

}

void error(){
	char ** s = 600000;
	char * help = "error";
	s[0]= help;
	printFF("%s",s, NULL);
}



//shell


int shell(){
	char ** s = 5000000;
	char * str = "shel>";
	s[0] = str;
	printFF("%s",s,NULL);
	char ** ss = 6500000;
	char * sos = 7000000;
	ss[0] = sos;
	scanFF("%s",ss, NULL);
	sos++;
	execute(parser(sos));

}

int parser(char * buffer){
	char state = *buffer;
	char * help = "help";
	char * clear = "clear";
	switch(state){
		case 'c':
		while(*buffer!= 0){
			if(*buffer != *clear || *clear == 0){
				return -1; //codigo de error
			}
			clear++;
			buffer++;
		}
		return 2; //la funcion clear
		case 'h':
			while(*buffer!= 0){
			if(*buffer != *help || *help == 0){
				return -1; //codigo de error
			}
			help++;
			buffer++;
		}
		return 3; //la funcion help

		default: 
		return -1;		
	}
	}


void execute(int n){
	switch(n){
		case 2: //system call  clear
		break;
		case 3: //system call help
		help();
		break;
		case -1: //system call error in parser 
		error();
		break;
	}
	

}