#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

/*
3)  Agregarle validación de datos de manera que no se repitan cuando
	sea necesario.
*/

void pause();
char menu();
void ingresoRegistro();
void buscarRegistro();
void buscarPorNameSurname();

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
	
	printf("\n\n\t 1- Ingresar un registro de una persona     \n\t 2- Buscar el registro de una persona segun su id    \n\t 3- Buscar un registro por nombre y apellido \n\t 4- Salir ");
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

int validacion(char cadena[]){
	
	char linea[500], cadenaEncontrada[50];
	
	FILE* apl;
	apl = fopen("Registros.txt","r");
	
	while(fgets(linea,sizeof(linea),apl)!=NULL){
		fscanf(apl,"%s  ,",&cadenaEncontrada);
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

