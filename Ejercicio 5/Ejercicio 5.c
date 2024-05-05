#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

/*
versión sin struct
4)	Modificar dicho programa de manera que me muestre los datos de
	manera ordenada
	Según se desee por nombre y apellido o por DNI
*/

void pause();
char menu();
void ingresoRegistro();
void buscarRegistro();
void buscarPorNameSurname();
void mostrarRegistrosOrdenados();
void replace(char cadena[], char cadena2[]);

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
				buscarRegistro();
				break;

			case '3':
				buscarPorNameSurname();
				break;
				
			case '4':
				mostrarRegistrosOrdenados();
				break;
				
			case '5':
				printf("\n\n\n\t Espero que el programa le haya sido util, Saludos por parte de Ian Vila \n\n");
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
	
	printf("\n\n\t 1- Ingresar un registro de una persona     \n\t 2- Buscar el registro de una persona segun su id    \n\t 3- Buscar un registro por nombre y apellido \n\t 4- Mostrar Registros Ordenados \n\t 5- Salir ");
	printf("\n\n\t\t Ingrese la operacion que quiera realizar: ");
	operacion = getch();
	printf("%c \n",operacion);
	
	return operacion;
}

void mostrarRegistrosOrdenados() {
    char linea[500], nombre[50], apellido[50];
    int x, orden[500], cantRegistros = 0, aux, id, y;

	printf("\n\n\t Asi quedarian todos los registros ordenados por el dni: ");

    FILE *apl;
    apl = fopen("Registros.txt", "r");

    while (fgets(linea, sizeof(linea), apl) != NULL) {
        sscanf(linea, "%d ,", &orden[cantRegistros]);
        cantRegistros++;
    }

    fclose(apl);

    for (x=0;x<cantRegistros;x++) {
        for (y=x;y<cantRegistros-1;y++) {
            if (orden[x] > orden[y+1]) {
                aux = orden[y+1];
                orden[y + 1] = orden[x];
                orden[x] = aux;
            }
        }
    }

    apl = fopen("Registros.txt", "r");

    x=0;
    
    while (fgets(linea, sizeof(linea), apl) != NULL && x < cantRegistros) {
        sscanf(linea, "%d , %s , %s", &id, nombre, apellido);
        if (id == orden[x]) {
        	replace(nombre,apellido);
            printf("\n\t %d   %s   %s", id, nombre, apellido);
            x++;
            rewind(apl);
        }
    }

    fclose(apl);
}



void Reemplazar_sPorEspacios(char cadena[]){
	int dim = strlen(cadena),x;
	for(x=0;x<dim;x++){
		if(cadena[x]=='_'){
			cadena[x] = ' ';
		} else if(cadena[x] == ' '){
			cadena[x] = '_';
		}
	}
}

void replace(char cadena[], char cadena2[]){
	Reemplazar_sPorEspacios(cadena);
	Reemplazar_sPorEspacios(cadena2);
}

int validacion(char cadena[]){
	
	char linea[500], cadenaEncontrada[50];
	
	FILE* apl;
	apl = fopen("Registros.txt","r");
	
	while(fgets(linea,sizeof(linea),apl)!=NULL){
		fscanf(apl,"%s ,",&cadenaEncontrada);
		if(strcmp(cadenaEncontrada,cadena)==0){
			return 1;
		}
	}

	fclose(apl);
	
	return 0;
}

void ingresoRegistro(){
	
	char DNI[40];
	char nombre[40];
	char apellido[40];
	int flag;
	
	do{
		flag=0;
	
		printf("\n\t Ingrese el DNI: ");
		scanf("%s",&DNI);
		
		if(validacion(DNI)==1){
			flag=1;
			printf("\n\n\t\t Error: Este dni ya fue ingresado. ");
		}
		
	}while(flag==1);
	
	printf("\n\t Ingrese el Nombre: ");
	fflush(stdin);
	gets(nombre);
	fflush(stdin);
		
	printf("\n\t Ingrese el Apellido: ");
	fflush(stdin);
	gets(apellido);
	fflush(stdin);
	
	Reemplazar_sPorEspacios(nombre);
	Reemplazar_sPorEspacios(apellido);
		
	FILE* apa;
	
		apa = fopen("Registros.txt","a");
		
		fprintf(apa,"\n\t%s ,  %s ,  %s",DNI,nombre,apellido);
		
	fclose(apa);
	
	apa = fopen("RegistrosReserva.txt","a");
		
		fprintf(apa,"\n\t%s ,  %s ,  %s",DNI,nombre,apellido);
		
	fclose(apa);
}


void buscarRegistro(){
	
	int count=0;
	char DNI[40];
	char dniEncontrado[40], nombre[40], apellido[40];
	char linea[40];
	
	printf("\n\t Ingrese el DNI de la persona de la cual quiere saber informacion: ");
	scanf("%s",&DNI);
	
	FILE* apl;
	apl = fopen("Registros.txt","r");
		
		while(fgets(linea,sizeof(linea),apl)!=NULL){
			fscanf(apl,"%s ,  %s ,  %s",dniEncontrado, nombre, apellido);
			if(strcmp(DNI,dniEncontrado)==0){
				replace(nombre,apellido);
				printf("\n\n\t\t Se encontro la persona con el dni: %s, con nombre: %s y con apellido: %s",DNI,nombre, apellido);
				count++;
			}
		}
		if(count==0){
			printf("\n\n\t\t No se ha encontrado ningun usuario con ese DNI... ");
		}
		
	fclose(apl);
	return;
}

void buscarPorNameSurname(){
		
	int count=0;
	char DNI[40];
	char Nombre[40], Apellido[40], nombreEncontrado[40], apellidoEncontrado[40];
	char linea[40];
	
	printf("\n\t Ingrese el nombre de la persona de la cual quiere saber informacion: ");
	fflush(stdin);
	gets(Nombre);
	fflush(stdin);
	
	printf("\n\t Ahora también ingrese su apellido: ");
	fflush(stdin);
	gets(Apellido);
	fflush(stdin);
	
	FILE* apl;
	apl = fopen("Registros.txt","r");
		
		while(fgets(linea, sizeof(linea), apl)!=NULL){
			fscanf(apl,"%s ,  %s ,  %s", DNI, nombreEncontrado, apellidoEncontrado);
			
			replace(nombreEncontrado,apellidoEncontrado);

			if(strcmp(Nombre, nombreEncontrado)==0 && strcmp(Apellido, apellidoEncontrado)==0){
				replace(Nombre, Apellido);
				printf("\n\n\t\t Se encontro la persona con el dni: %s, con nombre: %s y con apellido: %s", DNI, nombreEncontrado, apellidoEncontrado);
				count++;
			}
		}
		fflush(stdin);
		if(count==0){
			printf("\n\n\t\t No se ha encontrado ningun usuario con ese DNI... ");
		}
	fclose(apl);
	
	return;
}

