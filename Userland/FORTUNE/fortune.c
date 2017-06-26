#include <stdio.h>
#include <fortune.h>

int main(void){

	char ** ss = malloc(sizeof(char *));
	char * string = malloc(2500);
	ss[0] = string;
	char * name = "Ingrese su nombre:";
	printFF("%s",&name, NULL);

	if(scanFF("%s",ss, NULL)==0){
			char * yourFortune
			if(strcmp(name,"Augusto")==0 ||strcmp(name,"augusto")==0 ){
					yourFortune="mmmmmm...Interesante... veo a un tal Augusto, pero
					veo mala suerte, oscuridad. Pero tambien veo luz que solo  obtendra 
					si realiza una accion: 'Aprobar a este grupo' ";
			}else if(strcmp(name,"Santiago")==0 ||strcmp(name,"santiago")==0 ){
					yourFortune="Veo poder, veo a un director, veo felicidad , veo ganas de aprobar a sus alumnos";
			}else{		

			int longitud=0;

			while(string[longitud]!=0){
				longitud++;
			}
			yourFortune= magic(longitud);
			}


			printFF("%s",&yourFortune, NULL);
		}else {
			char ** s = malloc(sizeof(char*));
			char * help = "ScanFF Buffer OverFlow";
			s[0]= help;
			putchar('\n');
			printFF("%s",s, NULL);
		}


return 0;


}

char * magic(int n){
	int mod= n%3;

	char* fortune;

	switch(mod){
		case 0:
				fortune="TENDRAS MALA SUERTE TODA TU VIDA";
				break;

		case 1:
				fortune="TE SACARAS UN 10 EN EL TP DE ARQUI";
				break;

		case 2:
				fortune="NUNCA TE VAS A RECIBIR";
				break;

	}

	return fortune;
}