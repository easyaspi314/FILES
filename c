#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define IDENT 21
#define NOM 21
#define DESC 151
#define FECHA 11
#define NUM 10
#define ART 100

struct articulos{
    char identificador2[IDENT];
    int iden_num;
    char modelo[NOM];
    char marca[NOM];
    char fecha[FECHA];
    int stock_art;
    char tipo_art[NOM];
    float precio_art;
    float precio_transport;
    int activo1;
};


struct componentes{
    char identificador1[IDENT];
    char nombre[NOM];
    char descripcion[DESC];
    int stock_comp;
    int activo;
    struct articulos articulo[ART];
};	

void dar_alta(FILE *componente1, char identificador1[IDENT],char nombre[NOM],char descripcion[DESC],char conversion[NOM]){
	fgets(identificador1,IDENT,componente1);
	fgets(nombre,NOM,componente1);
	fgets(descripcion,DESC,componente1);
	fgets(conversion,NOM,componente1);	
}

struct componentes crear_componente(char identificador1[IDENT],char nombre[NOM],char descripcion[DESC],char conversion[NOM],int stock_comp,int activo){
	struct componentes componente;
	strcpy(componente.identificador1,identificador1);
	strcpy(componente.nombre,nombre);
	strcpy(componente.descripcion,descripcion);
	componente.stock_comp = atoi(conversion);
	componente.activo = 1;
	return componente;
}

void comparacion_componentes(FILE  *componente1, char comparacion[IDENT],char seguir,struct componentes componente,char fichero[NOM]){
	if((componente1 = fopen(fichero,"r")) != NULL){
		fgets(comparacion,IDENT,componente1);
		printf("IDENT: %s \n", componente.identificador1);
		printf("comp activo = %d\n", componente.activo);
		if((strcmp(comparacion,componente.identificador1) == 0) && (componente.activo == 1)){
			printf("Quieres eliminar los articulos asociados a %s (y/n)?\n",comparacion);
			// you don't check scanf's return value, if it doesn't return the number of variables you give it, it leaves the text in stdin
			scanf("%c",&seguir);
			if(seguir == 'y'){
				// you don't change componente here, it makes a copy. pass a pointer or return it if you want to change it.
				componente.activo = 0;
			}
		}
	}
	fclose(componente1);    // componente1 is null, crash
}

void dar_alta_articulo(FILE *componente1,char identificador2[IDENT],char fecha[FECHA],char modelo[NOM],char marca[NOM],char tipo_art[NOM],char precio_art1[NUM],char precio_transport1[NUM],char conversion[NOM]){
	fgets(identificador2,IDENT,componente1);
	fgets(fecha,FECHA,componente1);
	fgets(modelo,NOM,componente1);
	fgets(marca,NOM,componente1);
	fgets(tipo_art,NOM,componente1);
	fgets(precio_art1,NUM,componente1);
	fgets(precio_transport1,NUM,componente1);
	fgets(conversion,NOM,componente1); 
} 

struct articulos crear_articulo(char identificador2[IDENT],char fecha[FECHA],char modelo[NOM],char marca[NOM],char tipo_art[NOM],float precio_art,float precio_transport,char precio_art1[NUM],
char precio_transport1[NUM], char conversion[NOM],int activo1, int stock_art){
	struct articulos articulo;
	strcpy(articulo.identificador2, identificador2);
	strcpy(articulo.fecha, fecha);
	strcpy(articulo.modelo, modelo);
	strcpy(articulo.marca, marca);
	strcpy(articulo.tipo_art, tipo_art);
	articulo.precio_art = atoi(precio_art1);
	articulo.precio_transport = atoi(precio_transport1);
	articulo.stock_art = atoi(conversion);
	articulo.activo1 = 1;
	return articulo;
}

main(){ // int main() is better
	//struct articulos articulo[ART];
	struct componentes componente[NUM];
	char identificador[IDENT], modelo[NOM],marca[NOM],fecha[FECHA],tipo_art[NOM],identificador1[IDENT],nombre[NOM],descripcion[DESC],conversion[NOM],seguir = 'y',comparacion[IDENT],fichero[NOM];
	char precio_art1[NUM],precio_transport1[NUM],identificador2[IDENT];
	float precio_art /* = 0.0f? */,precio_transport /* = 0.0f */;
	int stock_art /* = 0? */,stock_comp /* = 0? */,iden_num,opcion,contador = 0,activo = 0,stock_comp1,activo1 = 0, j, k /* =0? */, i,p;
	FILE *componente1;
	do{
		printf("OPCION 1: ");
		printf("Escribe una opcion: ");
		// scanf return value
		scanf("%d",&opcion);
		// fflush(stdin) is not standard. While sometimes it clears the text left over in stdin, other times it doesn't.
		fflush(stdin);
		switch(opcion){
			case 1:
				do{
				printf("Escribe el nombre del fichero: ");
				fflush(stdin); // fflush(stdin) is not standard
				gets(fichero); // gets is very insecure and if anyone suggested you use it, you have my permission to slap them.
				seguir = 'y'; // you assign seguir to y but then check if it is y right after it.
					if((seguir == 'y') && ((componente1 = fopen(fichero,"r")) != NULL)){
						dar_alta(componente1,identificador1,nombre,descripcion,conversion);
						fclose(componente1);
						componente[contador] = crear_componente(identificador1, nombre, descripcion,conversion,stock_comp, activo);
						contador++;
						printf("Quieres seguir introduciendo componentes(y/n)");	
						scanf("%c",&seguir); // don't check return value
						fflush(stdin);      // fflush(stdin) is not standard
						}
					else{
						printf("Ese fichero no existe.\n");
						seguir = 'n';
					}			
				}
				while(seguir == 'y');
				break;
			case 2:
				printf("Escribe el fichero: ");
				fflush(stdin); // not standard
				gets(fichero); // gets again
				printf("Escribe el identificador: ");
				fflush(stdin); // not standard
				gets(comparacion); // gets again
				printf(" COMP: %s\n",comparacion);
				for(i = 0; i <= contador; i++){
					comparacion_componentes(componente1,comparacion,seguir,componente[i],fichero);
				}
				break;
			case 3:
					for(i = 0; i < contador; i++){
					printf("Ident: %s\n",componente[i].identificador1);
					printf("nombre: %s\n",componente[i].nombre);
					printf("descripcion: %s\n",componente[i].descripcion);
					printf("stock: %d",componente[i].stock_comp);
					printf("\n\n");
					}
					break;
			case 4:	
				do{
					printf("Escribeme el fichero: ");
					fflush(stdin); // not standard
					gets(fichero); // gets again
					printf("Escribeme el tipo de articulo: ");
					fflush(stdin); // not standard
					gets(comparacion);
					for(i = 0; i < contador; i++){
						if(((componente1 = fopen(fichero,"r")) != NULL)  && (componente[i].activo == 1)){
							dar_alta_articulo(componente1,identificador2,fecha,modelo,marca,tipo_art,precio_art1,precio_transport1,conversion);
							for(p = 0; tipo_art[p] == '\0'; p++){ // did you mean != 0?
								if(tipo_art[p] == '\n'){
									tipo_art[p] = '\0';
								} // break?
							}
							for(p = 0; componente[i].nombre[p] == '\0'; p++){ // != 0?
								if(tipo_art[p] == '\n'){ // componente[i].nombre[p]?
									tipo_art[p] = '\0';
								} // break?
							}
							// strcmp returns zero when they are the same, so you are checking if tipo_art is equal to componente[i].nombre.
							// that is because the only way that comparacion can be equal to both tipo_art and componente[i].nombre is if
							// tipo_art and componente[i].nombre are equal
							if((strcmp(comparacion,tipo_art) == 0) && (strcmp(comparacion,componente[i].nombre) == 0)){
								printf("xddd");
								for(j = 0; j < k; j++){
									if(componente[i].articulo[j].activo1 != 1){
										fclose(componente1); // you are only sometimes closing componente1, and it looks like you close it multiple times which is bad.
										componente[i].articulo[j] = crear_articulo(identificador2,fecha,modelo,marca,tipo_art,precio_art,precio_transport,precio_art1,precio_transport1,conversion,activo1,stock_art);
										printf("Ident: %s\n",componente[0].articulo[0].identificador2);
										printf("fecha: %s\n",componente[0].articulo[0].fecha);
										printf("modelo: %s\n",componente[0].articulo[0].modelo);
										printf("marca: %s\n",componente[0].articulo[0].marca);
										printf("tipo_art: %s\n",componente[0].articulo[0].tipo_art);
										
					
								
										printf("El articulo ha sido dado de alta con exito!!\n");
										printf("El identificador asignado al articulo es %s_%d_ %s",componente[i].articulo[j].identificador2,k + 1,componente[i].articulo[j].fecha);
									}
								}
							printf("Quieres seguir introduciendo articulos? ");
							scanf("%c",&seguir); // return value
							fflush(stdin); // not standard
							k++;
							}
						}
						else{
								printf("El nombre del tipo de articulo y del componente no coincide.\n");
								seguir = 'n';
							}
					}
				}
				while(seguir == 'y');
				break;  
			case 5:
				componente1 = fopen ("binario.bin","wb"); // don't check return value
				fwrite(componente,sizeof(struct componentes),NUM,componente1); // don't check return value
				fclose(componente1); // may be null
				break;
			case 6: 
				componente1 = fopen("binario.bin","rb") // missing semicolon, don't check return value
				fread(componente,sizeof(struct componentes),NUM,componente1); // return value
				fclose(componente1); // may be null
				break;
				
			case 6: // assuming you aren't done with it here
			}
		}
	while(opcion != 5);
return 0;
}
