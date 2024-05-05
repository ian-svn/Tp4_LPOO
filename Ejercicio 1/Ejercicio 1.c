#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

/*
1)  Realizar un programa en el cual se ingresen los siguientes datos
	Nombre, Apellido y DNI

	a) Crear un menu donde se ingresen los datos y los guarde en un
	   archivo
	b) Otro ítem donde se pueda realizar una búsqueda por DNI y
	   devuelva los datos de Nombre y apellido
	c) Salir del mismo
*/

void pause();
char menu();
void ingresoRegistro();
void buscarRegistro();


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
				printf("\n\n\n\t Espero que el programa le haya sido util, Saludos por parte de Ian Vila \n\n");
				return 0;
				break;
				
			default:
				printf("\n\n\n\t Error: Ingrese una opcion valida porfavor ");
				break;
		}
		
		pause();
		
	}while(operacion!='3');
	
	return 0;
}

void pause(){
	printf("\n\n\n\t\t");
	system("pause");
	system("cls");
}

char menu(){
	
	char operacion;
	
	printf("\n\n\t 1- Ingresar un registro de una persona     \n\t 2- Buscar el registro de una persona segun su id    \n\t 3- Salir ");
	printf("\n\n\t\t Ingrese la operacion que quiera realizar: ");
	operacion = getch();
	printf("%c \n",operacion);
	
	return operacion;
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

void ingresoRegistro(){
	
	char DNI[40];
	char nombre[40];
	char apellido[40];
	
	
	printf("\n\t Ingrese el DNI: ");
	scanf("%s",&DNI);
	
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
	
}

