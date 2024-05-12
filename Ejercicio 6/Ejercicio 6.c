#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

/*
6) 	Realizar un programa que realice las siguientes acciones
	a. Guarde el registro del nombre y el puntaje de un jugador (solicitando el ingreso
		de los datos del usuario)
	b. Muestre el resultado de los 10 mejores jugadores ordenados por mayor
		puntaje.
	c. Realice y muestre una búsqueda de un Nombre y devuelva sus resultados
	
	NOTA: el registro debe permanecer aunque se apague la PC.
*/

char menu();
void ingresoRegistro();
void buscarPorNameSurname();
void mostrarRegistrosOrdenados();
void replace(char cadena[]);
void pause();

int main(){
	
	char operacion;
	
	do{
		printf("\n\n\t\t --- Programa para el regitro de Personas --- ");	
		
		operacion = menu();
		
		switch(operacion){
			case '1':
				ingresoRegistro();
				break;

			case '2':
				buscarPorNameSurname();
				break;
				
			case '3':
				mostrarRegistrosOrdenados();
				break;
				
			case '4':
				printf("\n\n\t Espero que el programa le haya sido util, Saludos por parte de Ian Vila \n\n");
				return 0;
				break;
					
			default:
				printf("\n\n\n\t Error: Ingrese una opcion valida porfavor ");
				break;
		}
		
		pause();
		
	}while(operacion!='5');
	
	return 0;
}

void pause(){
	printf("\n\n\n\t\t");
	system("pause");
	system("cls");
}

char menu(){
	
	char operacion;
	
	printf("\n\n\t 1- Ingresar un registro de una persona     \n\t 2- Buscar el registro por nombre   \n\t 3- Mostrar top 10 de personas con mejor puntaje \n\t 4- Salir");
	printf("\n\n\t\t Ingrese la operacion que quiera realizar: ");
	operacion = getch();
	printf("%c \n",operacion);
	
	return operacion;
}

void mostrarRegistrosOrdenados() {
    char linea[500];
    int x, orden[500], cantRegistros = 0, aux, puntaje, y;

	printf("\n\n\t Asi quedaria el top 10 de los participantes con mayor puntaje: ");

    FILE *apl;
    apl = fopen("Top.txt", "r");

    while (fgets(linea, sizeof(linea), apl) != NULL) {
        sscanf(linea, "%d ,", &orden[cantRegistros]);
        cantRegistros++;
    }

    fclose(apl);

    for (x=0;x<cantRegistros;x++) {
        for (y=x;y<cantRegistros-1;y++) {
            if (orden[x] < orden[y+1]) {
                aux = orden[y+1];
                orden[y + 1] = orden[x];
                orden[x] = aux;
            }
        }
    }

    apl = fopen("Top.txt", "r");
    
    x=0;
    y=0;
    char nombre[50];
    
    while (fgets(linea, sizeof(linea), apl) != NULL && x < cantRegistros) {
        sscanf(linea, "%d , %s", &puntaje, nombre);
        
		if(puntaje == orden[x] && x<10) {
        	replace(nombre);
            printf("\n\tEn el Top %d: %d   %s", y+1, puntaje, nombre);
            x++;
            y++;
            rewind(apl);
        }
    }

    fclose(apl);
}



void replace(char cadena[]){
	int dim = strlen(cadena),x;
	for(x=0;x<dim;x++){
		if(cadena[x]=='_'){
			cadena[x] = ' ';
		} else if(cadena[x] == ' '){
			cadena[x] = '_';
		}
	}
}

void ingresoRegistro(){
	
	int puntaje;
	char nombre[40];
	int flag;
	
	do{
		printf("\n\t Ingrese el puntaje: ");
		scanf("%d", &puntaje);
		fflush(stdin);
		if(puntaje<=0||puntaje>=99999){
			printf("\n\t\tIngrese un punraje valido porfavor \n");
		}
	}while(puntaje<=0||puntaje>=99999);
	printf("\n\t Ingrese el Nombre: ");
	fflush(stdin);
	gets(nombre);
	fflush(stdin);
	
	replace(nombre);
		
	FILE* apa;
	
		apa = fopen("Top.txt","a");
		
		fprintf(apa,"\n\t%d ,  %s ",puntaje,nombre);
		
	fclose(apa);
}


void buscarRegistro(){
	
	int count=0;
	char puntaje[40];
	char puntajeEncontrado[40], nombre[40], apellido[40];
	char linea[40];
	
	printf("\n\t Ingrese el nombre de la persona de la cual quiere saber informacion: ");
	scanf("%s",&puntaje);
	
	FILE* apl;
	apl = fopen("Top.txt","r");
		
		while(fgets(linea,sizeof(linea),apl)!=NULL){
			fscanf(apl,"%s ,  %s",puntajeEncontrado, nombre);
			if(strcmp(puntaje,puntajeEncontrado)==0){
				replace(nombre);
				printf("\n\n\t\t Se encontro la persona con el puntaje: %s, con nombre: %s ",puntaje,nombre);
				count++;
			}
		}
		if(count==0){
			printf("\n\n\t\t No se ha encontrado ningun usuario con ese nombre... ");
		}
		
	fclose(apl);
	return;
}

void buscarPorNameSurname(){
		
	int count=0;
	int puntaje;
	char Nombre[40], nombreEncontrado[40];
	char linea[40];
	
	printf("\n\t Ingrese el nombre de la persona de la cual quiere saber informacion: ");
	fflush(stdin);
	gets(Nombre);
	fflush(stdin);
	
	FILE* apl;
	apl = fopen("Top.txt","r");
		
		while(fgets(linea, sizeof(linea), apl)!=NULL){
			fscanf(apl,"%d ,  %s ", &puntaje, nombreEncontrado);
			
			replace(nombreEncontrado);

			if(strcmp(Nombre, nombreEncontrado)==0 && count<1){
				replace(Nombre);
				printf("\n\n\t\t Se encontro la persona con el puntaje: %d y su nombre es: %s", puntaje, nombreEncontrado);
				count++;
			}
		}
		fflush(stdin);
		if(count==0){
			printf("\n\n\t\t No se ha encontrado ningun usuario con ese nombre... ");
		}
	fclose(apl);
	
	return;
}

