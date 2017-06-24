#include "stdioASM.h"

int main(){

char * buffer = "soy Dummy";
char *hola = (char*)0x100011;
int length = 3000;
*hola = 40;
writeC(buffer,9);
return 0;

}
