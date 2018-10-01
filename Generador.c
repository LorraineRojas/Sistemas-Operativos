#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

//Crea la estructura dogType
struct dogType {
	char nombre[32];
	char tipo[32];
	int edad;
	char raza[16];
	int estatura;
	float peso;
	char sexo[1];
};

//Genera un aleatorio de tipo entero entre a y b
int aleatorioEntero(int a, int b)
{
	int x=(a + (rand() % (int)(b - a + 1)));
	if(x != 10 && x != 13){
		return x;
	}else{
		return aleatorioEntero(a,b);
	}
}

//Genera un aleatorio de tipo real entre a y b
float aleatorioReal(int a, int b)
{
    	int x = ((float)aleatorioEntero(a, b) + ((float) rand() / (RAND_MAX)) + 1);
	if(x != 63.760475){
		return x;
	}else{
		return aleatorioReal(a,b);
	}
}


int main(){

	//Crea el archivo donde se guardan las mascotas
    
	FILE *ap = fopen("dataDogs.dat", "w");
	fwrite("",0,0,ap);

	//Abre los archivos donde están almacenados los nombres y las razas
	FILE *nombres = fopen("nombresMascotas.txt","r");
	FILE *razas = fopen("razas.txt","r");
	
	//Variable del iterador
	int i;
	int j;
	int c1=0;
	int c2=0;
	
	fclose(ap);

	for(i=0;i<1716;i++){
		
		struct dogType *data = malloc(sizeof(struct dogType));


		//Se lee siguiente nombre y raza
		c1=fscanf(nombres," %[^\n]",data -> nombre);
		for(j=0;j<5828;j++){//5828
			c2=fscanf(razas," %[^\n]",data -> raza);

			//Genera datos aleatorios para edad, estatura y peso
			data -> edad = aleatorioEntero(1,20);
			data -> estatura = aleatorioEntero(5,100);
			data -> peso = aleatorioReal(3,100);
		
			//Si el iterador es divisible entre 3, será macho. De lo contrario, será hembra
			if(j%3 == 0){
				strcpy(data -> sexo, "M");
        	}else{
				strcpy(data -> sexo, "H");
        	}
			//Si el iterador es divisible en 2 es perro, de lo contrario es gato.
			if(j%2 == 0){
				strcpy(data -> tipo, "Perro");
	        }else{
				strcpy(data -> tipo, "Gato");
	        }
			
		    //Si se llega al final del archivo con los nombres, manda el apuntador al principio del mismo
	        if(c1==EOF){
	        	rewind(nombres);
	        }if(c2==EOF){
    	    	rewind(razas);
    	    }
			
			ap = fopen("dataDogs.dat", "ab");//Abre el archivo
			fwrite(data, sizeof(struct dogType), 1, ap);//Copia la estructura al archivo
			fwrite("\n",1,1,ap);//Pone un salto de línea
			fclose(ap);//Cierra el archivo
		}
	}			
}
