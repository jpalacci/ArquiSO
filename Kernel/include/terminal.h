
#include <stdint.h> 
void echoON();
void echoOF();
void terminalInitializeC(char * Buffer, int size);
void putTerminalBuffer(char c);
int getTerminalBuffer(char * buffer, uint32_t length);
void terminalInitialize();