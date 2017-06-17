#include "stdioASM.h"

int main(){

char * buffer = "soy Dummy";
char *hola = 0x000000;
int length = 3000;
*hola = 40;
writeC(buffer,9);
return 0;

}
