#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dir.h>

#define tam 100 //define el tama๑o del arreglo de estructura

// << ---------- >> Estructuras << ---------- >>

//Estructura que recibe, a travez de la variable linea, la informacion que  introduzca el usuario--

struct almacen{
       char linea[100];
       }N[tam];

//estructura de la pila
struct base_pila
   {
        char *pal;
   }pila[100];
//estructura de la tabla de simbolos
struct p
{       
    char *palabra;
}tabla[31];

// << ---------- >> Banderas y variables  para el acceso y uso de las funciones << ---------- >>

int contarchivo; //contiene el numero de lineas ingresadas
int bandabierto; //si es 1 hay un archivo abierto
int bandnuevo; //si es 1 se creo un archivo nuevo
int bandmod; //si es 1 se modifico el contenido

char otravez[100]; //almacena una copia de la ruta
//arreglo de caracteres para la funcion buscar
//permite realizar tokens cada que se encuentra uno de los caracteres declarados
char s2[7] = " ,.-,\n";
char cadena[1000]; //almacena en un solo arreglo lo contenido en el arreglo de estructuras (Analisis)

int k=0,ban=0,tope=-1;
char aux2[1000]={};
char linea[10]={};

void separar();

// << ---------- >> ARCHIVO << ---------- >>

FILE *f; // variable que apunta al archivo

// << ---------- >> FUNCIONES << ---------- >>

//  creacion de un nuevo archivo
void nuevo()
{
    int i=0;
    int t=0; //almacena el valor del tama๑o de la cadena (se encuentra en diferentes funciones)
    bandnuevo=0;
    contarchivo=0;
    printf("\nA continuacion deberas ingresar el texto para el documento,\n    presiona enter para generar una nueva linea\n\n");
    printf("Para finalizar el proceso de escritura,\n    inserta solamente un punto ( . ) en una linea y despues presiona enter.\n\n");
    for(i=0;i<tam;i++)
    {                         
        printf("[%d]",(i+1));    //proceso mediante el cual se imprime el numero de linea,
        fflush(stdin);           //se lee desde el teclado la informacion y se almacena en la linea correspondiente
        gets(N[i].linea);
        t=strlen(N[i].linea);
        contarchivo++;
        
        if(N[i].linea[t-1]== '.')  //verifica si el caracter insertado es un punto, esto para encontrar el fin del archivo
        {
            printf("\n"); 
            bandnuevo=1;
            break;
        }
    }
}

void abrir()
{
    fclose(f); // por default se cerrara cualquier archivo abierto con anterioridad
    bandabierto=0;
    contarchivo=0;
    int i=0;
    char ruta[100]; // almacena la direccion en memoria del documento
    char nombre[100]; //contiene el nombre del archivo
    printf("\n\n>>Ingrese la ruta donde se encuentre el archivo << Ejemplo: G\n");
    fflush(stdin);
    gets(ruta);
    strcat(ruta,":/");
    if(chdir(ruta)!=0) //verifica si la direccion es valida
    {
         printf("Error en la ruta especificada\n");
         printf("Por favor vuelve a intentarlo\n"); 
    } else{
              printf(">>Ingresa el nombre del archivo y su extension<< Ejemplo: prueba.txt\n");
              scanf("%s",&nombre);
              strcat(ruta,nombre);
              strcpy(otravez,ruta);
              f=fopen(ruta,"r"); //abre el documento en modo lectura,
              if(f) //comprueba si el archivo existe
              {
	              while(!feof(f))    
	              { 
	                      fgets(N[i].linea,1000,f); //lee el contenido del archivo a la estructura
	                      printf("%s",N[i].linea);  //muestra en pantalla la informacion
	                      i++; 
	                      contarchivo++;
	              }
	              bandabierto=1;
		      }else{
		      	   printf("El archivo no existe\n");
		      }
           }  
     contarchivo=contarchivo-1;
}

void volverabrir() //trabaja con la funcion guardar y guardarcomo
{                  //despues de almacenar la informacion, se actualiza, con esta funcion
	int i=0;       //el contenido de la estructura que tiene las lineas
	f= fopen(otravez,"r"); //otravez variable de tipo cadena definida en la funcion de guardar y guardarcomo
       while(!feof(f))
       { 
                   fgets(N[i].linea,1000,f);
                   printf("%s",N[i].linea);
                   i++; 
                   contarchivo++;
       }
}
void guardarcomo() //Realiza copias de un documento, no le importa si se ha modificado o no.
{
    int i=0;
    int t;
    char ruta[100];
    char nombre[100];
    char Aux[100];
    bandabierto=0;
    
    printf("\n\n>>Ingrese la ruta donde se guardara el archivo << Ejemplo: G\n");
    fflush(stdin);
    gets(ruta);
    strcat(ruta,":/");
    
    if(chdir(ruta)!=0)//Chdir identifica si se puede o no grabar en esa hubicaci๓n
    {
         printf("Error en la ruta especificada\n");
         printf("Por favor vuelve a intentar guardar el archivo\n"); 
    } else{
              printf(">>Ingresa el nombre del archivo y la extension que desee<< Ejemplo: prueba.txt\n");
              scanf("%s",&nombre);
              strcat(ruta,nombre);
              strcpy(otravez,ruta); //realiza una copia de la direccion donde se almacena la informacion, esto para cuando se manda a llamar 
              f= fopen(ruta,"r");   //la funcion de volverabrir();
              if( f ) 
              {
                 printf("El archivo %s ya existe. No se guardo la informacion \n", ruta);
              }else{
                         fclose(f);
                         f=fopen(ruta,"w"); //apertura del archivo en modo escrituta
                         printf("\n\n << Archivo: %s\n >>",ruta);
                         for(i=0;i<contarchivo;i++)
                         {
                             if(i==contarchivo-1)
                             {
                                  t=strlen(N[i].linea);
                                  N[i].linea[t-1]=' ';
                                  fprintf(f,"%s\n",N[i].linea);
                             }else{
                                   fprintf(f,"%s\n",N[i].linea);//Escribe el contenido de info2 en archi.
                                   }
                         }
                         fclose(f); //cerrar archivo en modo escritura
                         printf(">>Guardado<<\n");
                         i=0;
                         contarchivo=0;
                         
                        volverabrir(); //volviendo abrir el archivo guardado, en modo lectura
                       contarchivo=contarchivo-2;
                       bandabierto=1;
                         //NO se cierra el archivo
                   }
          }
}


void buscar()
{
          char palabra[50]; //contiene la palabra a buscar
          int posicion[50]; //almacena las posiciones donde se localiza la palabra
          int i=0,j,b=0,c=0,k=0,t,tpal,m=0; //la variable c, es nuestro contador de palabras que coinciden con la busqueda.

          printf ("Ingrese la palabra que quiere buscar\n");
          fflush(stdin);
          gets(palabra);
		  //scanf("%s",&palabra);
          tpal=strlen(palabra); // tama๑o de palabra a buscar
          
          // Busqueda de la palabra por lineas
          for(i=0;i<contarchivo;i++) 
          { 
              t=strlen(N[i].linea); //mide el tama๑o de una linea
              for(j=0;j<t;j++)
              {     
                    if (N[i].linea[j]==palabra[k])  //realiza una comparacion de caracteres entre la linea y la palabra a buscar
                    {
                          b++;  //cada que son iguales b toma incrementa en 1
                          if(b==tpal)   //compara que b sea igual al tama๑o de la palabra a buscar
                          {              // si se cumple C incrementa, es decir hay una palabra identica.
                               c++;     
                               b=0;      //se reinicia el valor de b, para continuar con las comparaciones
                               posicion[m]=i+1; //se almacena, en un arreglo, el numero de linea donde se encontro la palabra a buscar
                               m++;
                          }    
                          k++;     //determina la posicion del caracter para el momento de la comparacion
                    }else{
                               if(b==tpal)
                               {
                                    c++;
                               }
                           k=0; 
                         }
              } 
          }
          printf ("El numero de veces que se repite la palabra ingresada '%s'es %d\n",palabra,c); 
          for(i=0;i<m;i++)
          {
              printf ("Linea donde se encuentra: %d \n",posicion[i]);      
          }
}

void mostrar()    //recorre el arreglo de estructuras, por si se ha realizado algun cambio en la informacion, 
{                 //no necesita que la informacion se encuentre en un archivo
	int i;
	printf("\nContenido:\n");
	for(i=0;i<(contarchivo-1);i++)
	{
		printf("[%d] %s\n", (i+1), N[i].linea);
	}
	printf("\n");
}

void modificar()
{
     int resp;
     int numlin,i,t;
     bandmod=0;
     mostrar();
     printf("Presiona 1 para modificar una linea\n  2 para agregar informaci๓n\n");
     scanf("%d",&resp);
     switch (resp)
     {
            case 1: 
                 printf("Ingresa el numero de linea a modificar\n");
                 scanf("%d",&numlin);  //modifica la informacion que contiene la linea que el usuario a escogido
                 if(numlin<=(contarchivo+1))
                 {
                        printf("\nInformacion Anterior [%d] %s\n", numlin, N[(numlin-1)].linea);
                        printf("Ingresa Nueva Informacion:  ");
                        t=strlen(N[(numlin-1)].linea);
                        
                        for(i=0; i<t; i++) // Limpia la linea para que se ingresen nuevos valores
								N[(numlin-1)].linea[i] = '\0';
								
                        fflush(stdin);   
                        gets(N[(numlin-1)].linea);      //lee el nuevo contenido para la linea seleccionada
                        t=strlen(N[(numlin-1)].linea);
                        N[(numlin-1)].linea[t]='\n';
                        mostrar();
                 }else{
                         printf("Esa linea no existe");
                 }
                 bandmod=1;
            break;
            case 2:
                printf("Ingresa el texto\n");
                contarchivo=contarchivo-2;
                for(i=contarchivo;i<tam;i++) //continua con la escritura, lo hace donde el contador de lineas se quedo
                {
                    printf("[%d]  ",(i+2));
                    fflush(stdin);
                    gets(N[(i+1)].linea); //lee una nueva linea
                    
                    t=strlen(N[(i+1)].linea);
                    contarchivo++;
                    
                    if(N[(i+1)].linea[t-1]== '.') //realiza la comparacion sobre el caracter que determina el fin de archivo
                    {
                        printf("Fin de archivo"); 
                        break;
                    }
                }
                contarchivo++;
                mostrar();
                bandmod=1;
            break;
            default:
                 printf("Opcion no valida\n");
     }
      
}

void eliminar()
{
   int res=0;
   char ruta[30];
   char nombre[30];
   printf("Ingrese la ruta donde se encuentra el archivo Ejemplo: G\n");
   fflush(stdin);
   gets(ruta);
   strcat(ruta,":/");
   if(chdir(ruta)!=0)  //Chdir identifica si se puede o no grabar en esa ubicaci๓n
   {
         printf("Error en la ruta especificada\n");
         printf("Intentalo nuevamente\n");  
   } else{
                printf("Nombre y tipo del archivo\n");
                fflush(stdin);
                gets(nombre);
                strcat(ruta, nombre);
                f = fopen(ruta,"r"); //se realiza la apertura en modo lectura para verificar que el archivo existe
                if( f ) 
                 {
                    printf("El archivo %s si existe \n", ruta);
                    fclose(f);
                    printf("Esta seguro que desea eliminar el archivo \n");
                    printf("1.-Si         2.-No \n");//pregunta si esta seguro de eliminar el archivo
                    scanf("%d",&res);                //1 si eliminar 2 no eliminar
                    if(res==1)
                      {
                        if(remove(ruta)==-1 ) // la funcion remove elimina el archivo indicado, si se esta usando se mostrara un error
                        printf("Error al eliminar archivo \n");
                        else //si el archivo existe y no esta en uso se eliminara
                        printf("Archivo eliminado correctamente \n");
                             
                      }
					  else
                      printf(" El archivo no se ha eliminado\n");
                           
                 }else
                 printf("El archivo %s no existe\n", ruta); 
                      
         
              }
}

void guardar() 
{
     int i,t;
     fclose(f);
      f= fopen(otravez,"w");
      {
           for(i=0;i<=contarchivo;i++)   //realiza la copia, de la informacion que se encuentra en la estructura
  	   	   {                             // a un archivo ya definido.
                t=strlen(N[i].linea);
                if(N[i].linea[t-1]=='.')  //comprueba si aun existe un punto en la linea 
                {
                   	N[i].linea[t-1]='\n';
                   	fprintf(f,"%s",N[i].linea); //si existe un punto, losustituye por un salto de linea
                }else{
                  	    fprintf(f,"%s",N[i].linea); //sino copia tal cual la linea en la estructura al archivo
      		         }
            }	
      }
       fclose(f);
       i=0;
       contarchivo=0;
       volverabrir();
      printf("Cambios guardados\n");
      bandabierto=1;
      bandmod=0;
}

void salir() //salir del editor de texto
{    
     int resp2;
     if(bandabierto==1) //******* revisa si el archivo se encuentra abierto*******//
     {  
        printf("\nEl archivo se encuentra abierto\n");
        printf("\nDeseas cerrar el archivo y salir 1=SI, 2=NO\n"); //si esta abierto se preguntara si se desea cerrar o no el archivo
        scanf("%d",&resp2);
        if(resp2==1)
        {
               if(bandmod==1)
                 {
                     printf("No se han guardado los cambios\n"); //si existen cambios en el archivo, se informara y se consultara si 
                     printf("\nDeseas guardar el archivo antes de salir 1=SI, 2=NO\n");   //el usuario desea guardar o descartas los cambios
                     scanf("%d",&resp2);
                     if(resp2==1)
                     {
                                guardar();  //si se requiere guardar cambios, se manda a traer la funcion guardar y sale uno del programa
                                getch();
                     } else{
                             printf("- Saliendo del programa -\n");
                             getch();
                            } 
                 }else{
                       printf("- Saliendo del programa - \n");
                             getch();
                       }
                            
        }
     }
}

// << ---------- >> FUNCIONES CON ANALISIS << ---------- >>

//Conversion del contenido del arreglo a una sola cadena
void convcadena()
{
	int i,j,cont,t,c;
	c=0;
	cont=0;
	for(i=0;i<contarchivo;i++)
	{
		c=cont;
		t=strlen(N[i].linea);
		for(j=0;j<t;j++)
		{
			cadena[c]=N[i].linea[j];
			c++;
		}
		cont=cont+t;
		cadena[cont]=' ';
		cont++;
	}
	t=strlen(cadena);
	if(cadena[t-2]=='.')
	     cadena[t-2]=' ';
}

// << Analisis sintactico>>
void sintactico(char *ptr)
{
  struct base_pila p;
  int b=0,r,j,n;
  if(ptr[1]=='/')
  {
       if(tope!=-1)
       {   
          for(j=tope;j>=0;j--)
          { 
                	for(r=0;r<(strlen(ptr)-1);r++)
	            	{   
	            		if(ptr[r+2]==pila[j].pal[r+1])	
	            		   
	            			 b=1;
						else{
							 b=0;
							 break;
					     	}
	            	}
	            
	            	if(b==1)
     					break;
     				
		  }
               if(b==1)
               {  
			   	   for(n=j;n<=tope;n++) 
		              pila[j]=pila[j+1];
                   tope--;
				        
               }else if(b==0)
               {
                  tope++;
                  pila[tope].pal=ptr;
                
                 
               }
           
       }else{
             tope++;
  		     pila[tope].pal=ptr;
			            
        }	
  }
  else
  {
  		tope++;
  		pila[tope].pal=ptr;	
  		
  }
  
}
void sintactic()
{
     	 struct p m;
  
  //tabla de simbolos html
  tabla[0].palabra = "<head>";
  tabla[1].palabra = "</head>";
  tabla[2].palabra = "<p>";
  tabla[3].palabra = "</p>";
  tabla[4].palabra = "<title>";
  tabla[5].palabra = "</title>";
  tabla[6].palabra = "<body>";
  tabla[7].palabra = "</body>";
  tabla[8].palabra = "<br>";
  tabla[9].palabra = "</br>";
  tabla[10].palabra = "<h1>";
  tabla[11].palabra = "</h1>";
  tabla[12].palabra = "<div>";
  tabla[13].palabra = "</div>";
  tabla[14].palabra = "<h2>";
  tabla[15].palabra = "</h2>";
  tabla[16].palabra = "<center>";
  tabla[17].palabra = "</center>";
  tabla[18].palabra = "<pre>";
  tabla[19].palabra = "</pre>";
  tabla[20].palabra = "<h3>";
  tabla[21].palabra = "</h3>";
  tabla[22].palabra = "<ul>";
  tabla[23].palabra = "</ul>";
  tabla[24].palabra = "<li>";
  tabla[25].palabra = "</li>";
  tabla[26].palabra = "<tr>";
  tabla[27].palabra = "</tr>";
  tabla[28].palabra = "<table>";
  tabla[29].palabra = "</table>";
  tabla[30].palabra = "<td>";
  tabla[31].palabra = "</td>";
  //termina tabla de simbolos
   char *aux;
   char cadena[1000]="<head> imagen </head> hola<hola> <p>amigos<p> <body>";
   separar(cadena);
  int i=0;
   char *ptr;
    FILE *f;
    ptr = strtok(aux2," ");   
    printf(">>> ANALISIS LEXICO HTML <<<\n\n");
    if((f=fopen("Errorsintactico.txt","w"))!=NULL)
   
   //
    fprintf(f,"\n >>>>ANALISIS LEXICO<<<<");
    for(i=0;i<31;i++)
    {
       k=strcmp(ptr,tabla[i].palabra);//compara que la cadena sea igual a la
                                      //que se tiene en la tabla de simbolo
       if(k>0 || k<0)
       ban==0;
       else   
       ban=1;      //regresa valor de ban=1 si son iguales
    }
   
   if(ban==1) 
   {
   

        sintactico(ptr);
        
  }
        
   ban=0;
   while((ptr = strtok(NULL," "))!= NULL )
   {        
              for(i=0;i<31;i++)
              {
                  k=strcmp(ptr,tabla[i].palabra);//compara que la cadena sea igual a la
                                                 //que se tiene en la tabla de simbolo
                  if(k>0||k<0)
                  ban==0;
                  else 
                  ban=1;      //regresa valor de ban=1 si son iguales
              } 
              
              if(ban==1)
              {
                 
                   sintactico(ptr);//funcion del sintactico
              }
             ban=0;   //vaciando la bandera para volver a hacer el proceso                 
   }
   
   if(tope==-1)
   printf("--Estructura del programa correccto--\n");
   else
   {
   fprintf(f,"\n >>>>ANALISIS SINTACTICO<<<<"); 
   for(i=0;i<=tope;i++)
     {
       if(pila[i].pal[1]=='/')
       {    
	        
          printf(" falta aperturar la etiqueta %s\n",pila[i].pal);
          fprintf(f,"\nlinea %c falta aperturar la etiqueta %s",linea,pila[i].pal);
       }
       else
       {
          printf(" falta cerrar la etiqueta %s\n",pila[i].pal);
          fprintf(f,"\n linea %c falta cerrar la etiqueta %s",linea,pila[i].pal);
       }
   }
       
   }
   fclose(f);
}

// << Analisis lexico>>
void analisis()
{
	 struct p m;
  
  //tabla de simbolos html
  tabla[0].palabra = "<head>";
  tabla[1].palabra = "</head>";
  tabla[2].palabra = "<p>";
  tabla[3].palabra = "</p>";
  tabla[4].palabra = "<title>";
  tabla[5].palabra = "</title>";
  tabla[6].palabra = "<body>";
  tabla[7].palabra = "</body>";
  tabla[8].palabra = "<br>";
  tabla[9].palabra = "</br>";
  tabla[10].palabra = "<h1>";
  tabla[11].palabra = "</h1>";
  tabla[12].palabra = "<div>";
  tabla[13].palabra = "</div>";
  tabla[14].palabra = "<h2>";
  tabla[15].palabra = "</h2>";
  tabla[16].palabra = "<center>";
  tabla[17].palabra = "</center>";
  tabla[18].palabra = "<pre>";
  tabla[19].palabra = "</pre>";
  tabla[20].palabra = "<h3>";
  tabla[21].palabra = "</h3>";
  tabla[22].palabra = "<ul>";
  tabla[23].palabra = "</ul>";
  tabla[24].palabra = "<li>";
  tabla[25].palabra = "</li>";
  tabla[26].palabra = "<tr>";
  tabla[27].palabra = "</tr>";
  tabla[28].palabra = "<table>";
  tabla[29].palabra = "</table>";
  tabla[30].palabra = "<td>";
  tabla[31].palabra = "</td>";
  //termina tabla de simbolos
   char *aux;
   int l=0;
   char cadena[1000]="<head>imagen</head>hola<hola<<p>amigos<p>><body>";
   separar(cadena);
  
   char *ptr;
    FILE *p;
    int i=0;
    ptr = strtok(aux2," ");   
    printf(">>> ANALISIS LEXICO HTML <<<\n\n");
    if((p=fopen("Errorlexico.txt","w"))!=NULL)
     
   //
    fprintf(p,"\n >>>>ANALISIS LEXICO<<<<");
    for(i=0;i<31;i++)
    {
       k=strcmp(ptr,tabla[i].palabra);//compara que la cadena sea igual a la
                                      //que se tiene en la tabla de simbolo
       if(k>0 || k<0)
       ban==0;
       else   
       ban=1;      //regresa valor de ban=1 si son iguales
    }
   
   if(ban==1) 
   {
   
        printf("Etiqueta html: %s\n",ptr);
       
        
  }else{
        l=strlen(ptr);
        if((ptr[0]=='<'&&ptr[l-1]=='>')||(ptr[0]=='<'||ptr[l-1]=='>'))
        {
           printf("Error lexico: %s \n",ptr);
           fprintf(p,"\nlinea %c Error Lexico %s",ptr,linea);
       }
           //crear un fichero llamado errores
        else
           printf("Texto: %s\n",ptr);
        }
        
   ban=0;
   while((ptr = strtok(NULL," "))!= NULL )
   {        
              for(i=0;i<31;i++)
              {
                  k=strcmp(ptr,tabla[i].palabra);//compara que la cadena sea igual a la
                                                 //que se tiene en la tabla de simbolo
                  if(k>0||k<0)
                  ban==0;
                  else 
                  ban=1;      //regresa valor de ban=1 si son iguales
              } 
              
              if(ban==1)
              {
                   printf("Etiqueta html: %s \n",ptr); //imprime caracter especial de html
                  
              }else{
                    l=strlen(ptr);
                    if((ptr[0]=='<'&&ptr[l-1]=='>')||(ptr[0]=='<'||ptr[l-1]=='>'))
                    {
	  				    printf("Error lexico: %s \n",ptr);
                    	fprintf(p,"\n linea %c Error lexico:%s",linea,ptr);
                    }
                    
                    //crear un fichero llamado errores
                     else
                         printf("Texto: %s \n",ptr);//imprime texto normal 
                   }
            
             ban=0;   //vaciando la bandera para volver a hacer el proceso                 
   }
   
  
}

void menu()
{
     printf("\nบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบ\n");
     printf("||           EDITOR DE TEXTO          ||\n");
     printf("บบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบ\n");
     printf("||     1. Nuevo archivo               ||\n");
     printf("||     2. Abrir archivo               ||\n");
     printf("||     3. Modificar contenido         ||\n");
     printf("||     4. Eliminar archivo            ||\n");
     printf("||     5. Buscar dentro del contenido ||\n");
     printf("||     6. Guardar                     ||\n");
     printf("||     7. Guardar como                ||\n");
     printf("||     8. Analisis lexico             ||\n");
     printf("||     9. Analisis sintactico         ||\n");
     printf("||     10. Salir                      ||\n");
     printf("บบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบ\n");
}

int main(int argc, char *argv[])
{  
    int op;
    printf("\nบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบ\n");
    printf("บบ      Este programa solo funciona con letras minusculas     บบ\n");
    printf("บบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบบ\n\n");
    MENU:
   menu();
   printf("Introduce una opcion:  ");
   scanf("%d",&op);
   switch (op)
   {
          case 1:
 	           printf("\nบบ     Creando archivo ... ... ...     บบ\n");
               nuevo();
          goto MENU;
          case 2:
     	       printf("\nบบ     Abriendo archivo ... ... ...     บบ\n");
               abrir();
          goto MENU;
          case 3:
          	   printf("\nบบ   Modificando contenido ... ... ...  บบ\n");
               if(bandabierto==1 ||bandnuevo==1)
               {
                  modificar();
                  if(bandabierto==1)
                  {
                  	   guardar();
                  }
               }else{
                        printf("No puedes usar esta funcion porque no hay contenido disponible.\n");
                    }
          goto MENU;
          case 4:
          	   printf("\nบบ     Eliminando archivo ... ... ...  บบ\n");
               eliminar();
          goto MENU;
          case 5:
          	   printf("\nบบ   Buscando dentro del contenido ... ... บบ\n");
               if(bandabierto==1 || bandnuevo==1)
               {
                   buscar();
               }else{
                        printf("No puedes usar esta funcion porque no hay contenido disponible.\n");
                    }
          goto MENU;
          case 6:
               printf("\nบบ     Guardando informacion ... ... ...  บบ\n");
               //condiciones posibles para usar esta funcion
			   if(bandnuevo==1 || bandmod==1 && bandabierto==0)
               {
                   guardarcomo();
               }
   	           if(bandabierto==1 && bandmod==1 && bandnuevo==0)
   	           {
       	      	    guardar();
               } 
               if(bandabierto==1 && bandmod==0 && bandnuevo==0)
	           {
                    printf("No hay cambios que guardar\n");
               }   
	            if(bandabierto==0 && bandmod==0 && bandnuevo==0)
	            {
	            	printf("No puedes usar esta funcion, intenta crear un archivo o modificar uno\n");
	            } 
          goto MENU;
          case 7:
          	   printf("\nบบ     Guardando informacion como... ... ...  บบ\n");
               if(bandnuevo==1 || bandabierto==1)
               {
                    guardarcomo();
               }else{
                        printf("No puedes usar esta funcion, intenta crear o abrir un archivo\n");
                    }
          goto MENU;
          case 8:
          	   printf("\nบบ   Aplicando analizador lexico al contenido ... ... ...  บบ\n");
          	   if(bandnuevo==1 || bandabierto==1)
          	   {
          	   	     convcadena();
          	   	     analisis();
    	   	   }else{
    	   	   	     printf("No puedes usar esta funcion, intenta crear o abrir un archivo\n");
    	   	   	   }
          goto MENU;
          case 9:
          	   printf("\nบบ   Aplicando analizador sintactico al contenido ... ... ...  บบ\n");
          	    if(bandnuevo==1 || bandabierto==1)
          	   {
          	   	     convcadena();
                     sintactic();
    	   	   }else{
    	   	   	     printf("No puedes usar esta funcion, intenta crear o abrir un archivo\n");
    	   	   	   }
          goto MENU;
          case 10:
          	   printf("\nบบ     Saliendo del editor ... ... ...     บบ\n");
               salir();
          break;
          default:
                  printf("Ingresa una opcion valida\n");
   }
  system("PAUSE");	
  return 0;
}

void separar(char cadena[1000])
{
  	 int i,j;
     char aux1[1000]={};
     j=0;
     for(i=0;i<=1000;i++)
     {  
        if(cadena[i]!='>')
	       aux1[j]=cadena[i];
        else
        {  
           if(cadena[i]=='>')
           {
           	if(cadena[i+1]=='>')
		          aux1[j]=cadena[i];
            else{
       	    	 aux1[j]=cadena[i];
       	    	 aux1[j+1]=' ';
       	    	 j=j+1;
       	   		 }
           }
        }
       j++;
          
     }
    
     j=0;
	 //comienza la segunda separacion antes de <
     for(i=0;i<1000;i++)
     { 
       if(aux1[i-1]=='<')
       {  
         if(aux1[i]=='<')
         {
            aux2[j]= aux1[i];
         }
       }
       if(aux1[i]=='<')
       {  
         if(aux1[i+1]!='<' || aux1[i+1]!=' ' )
         {
         	aux2[j]=' ';
         	j++;
            aux2[j]= aux1[i];
         }
       }
       aux2[j]=aux1[i];
 	   j++;
     }
    
	  for(i=0;i<1000;i++)
	  {
	  	if(aux2[i]=='<'&&aux2[i+1]==' ')
	  	for(j=i+1;j<1000;j++)
	  	{
	  		aux2[j]=aux2[j+1];
	  	}
	  } 
	    printf("[[+%s+]]",aux2);
}
