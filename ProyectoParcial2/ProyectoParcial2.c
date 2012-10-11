/*
* Archivo: ProyectoParcial2.c
* Autor: D.Schuldt
* Fecha de creación: 2011-23-08
* Descripción: Proyecto Final
* -------------------------------------------------
* Modificaciones: 
* 2011-27-08: Implementación de la secuencia de escape "S" (D.Schuldt)
* 2011-28-08: Arreglos de dos dimensiones en el tablero de juego (D.Schuldt)
* 2011-02-09: Reforma para el ordenamieno burbuja (D.Schuldt)
*/

#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
//#include "MuestraLib.h" //Despliega el mensaje "LUDO" en la opción 3 del menú.


typedef enum {false,true} bool;
typedef struct {
	int vecesGanadas;
	char jugador[50];
	}jugadorT;

#define SALIR 4
#define MAX 200

/*Prototipos de funciones*/
void menuPrincipal(void);
void dibujaTablero (void);
int lanzarDado(void);
int primerJugador(int a, int b);
bool bloqueo1(int posiciónFicha1, int posiciónFicha2);
bool bloqueo2(int posiciónFicha1, int posiciónFicha2);
bool Ganador(int a, int b, int c, int d);
void informacionFichas(char a[], int b, int c, char d[], int e, int f);
void declararGanador (char *nombre);
int condicionInicial(int jug1, int jug2);
void ganaTurno(void);
void muestra11(int x, int y);
void muestra12(int x, int y);
void muestra21(int x, int y);
void muestra22(int x, int y);
int cargarDatos(FILE *archivo);
void actualizaPosicion1(int posAct, char Ficha[3][8], char inicio1[2][1], char c);
void actualizaPosicion2(int posAct, char Ficha[3][8], char inicio2[2][1], char c);
void dibujarTablero(char inicio1[2][1],char Ficha11[3][8],char Ficha12[3][8],char inicio2[2][1],char Ficha21[3][8],char Ficha22[3][8]);
void GuardarPartida(FILE *archivo, int turno, char *nombre1, int ficha11, int ficha12, char *nombre2, int ficha21, int ficha22);
void GuardarLanzamientos(FILE *archivo, int cont11, int cont12, int cont21, int cont22);
int cargarJugadores(FILE *top, jugadorT palabras[], char jugador[30]);
void guardarJugadores(FILE *top, jugadorT palabras[], int tamanio);

															/*Desarrollo*/
void main()
{
	FILE *in;
	FILE *out;
	FILE *inTop;
	FILE *outTop;
	FILE *inLnz;
	FILE *Lee;
	jugadorT Lista[50];
	char nombre1[500];
	char nombre2[500];
	int op, i=0,opcionEscape=0,guardaImput=0,tmp=0,guardaTam=0;
	int jugador1, posAct11=0, posAct12=0, jugador2, posAct21=0, posAct22=0, tmp11=0, tmp12=0, tmp21=0, tmp22=0;
	int Ficha=0, turno1=0, turno2=0, cont11=0, cont12=0, cont21=0, cont22=0;
	int turno=0, cambia=0;
		char caracter=0;
	char inicio1[2][1];
		char Ficha11[3][8];
		char Ficha12[3][8];
	char inicio2[2][1];
		char Ficha21[3][8];
		char Ficha22[3][8];

do{ //Do....While proncipal

	do{
	menuPrincipal();
	printf(" Elija una opci%cn: ",162);
	scanf("%d",&op);
	}while((op<0)||(op>SALIR));

switch(op)
{
case 1: /*Opción 1 del menú......................................................................................................... 
....................................................................................................................................*/
	flushall();
	system("cls");
	for(i=1;i<=80;i++)
		printf("-");
	printf("   Ludo v2.0 - Inicia el juego!\n");
	for(i=1;i<=80;i++)
		printf("-");
	printf("\n\n\t* Jugador 1, ingrese su nombre: ");
		gets(nombre1);
	printf("\n\t* Jugador 2, ingrese su nombre: ");
		gets(nombre2);
	if(strcmp(nombre1,nombre2)>0)
	{
		if(strstr(nombre2,nombre1))
			printf("\n\n\t*Coincidencia*\n\n   A partir del primer nombre, el resto del segundo es: %s.\n\n",strstr(nombre2,nombre1));
		/*else
			printf("\n\n\tNo hay coincidencias en los nombres.\n\n");*/
	}
	if(strcmp(nombre1,nombre2)<0)
	{
		if(strstr(nombre1,nombre2))
			printf("\n\n\t*Coincidencia*\n\n   A partir del segundo nombre, el resto del primero es: %s.\n\n",strstr(nombre1,nombre2));
		/*else
			printf("\n\n\tNo hay coincidencias en los nombres.\n\n");*/
	}
	printf("\n\n\tEste es su tablero de juego: ---------------------------------");
		dibujaTablero();
	printf("\n\n * Presione una tecla para iniciar el sorteo:");
		
	do{ 
		srand(time(NULL));
		printf("\n\n\t%s ha sacado: ",nombre1);
		if(getch()==32);
		{
			jugador1=LanzarDado();
			printf("%d",jugador1);
		}
		printf("\n\t%s ha sacado: ",nombre2);	
		if(getch()==32);
		{
			jugador2=LanzarDado();
			printf("%d",jugador2);
		}
		if(jugador1==jugador2)
		printf("\n\t\tEmpate, se sortea nuevamente.");
	}while(jugador1==jugador2);

	if(primerJugador(jugador1,jugador2)==1)
		printf("\n\n\t\tEl primer jugador es: %s",nombre1);
	if(primerJugador(jugador1,jugador2)==2)
		printf("\n\n\t\tEl primer jugador es: %s",nombre2);


	//--------------------------------------------------------
	printf("\n\n      ");
	for(i=0;i<68;i++)
		printf("_");
	printf("\n\n      ---[Recuerde presionar la barra espaciadora para lanzar el dado]---\n      ");
	for(i=0;i<68;i++)
		printf("_");
	printf("\n\n");
	turno=primerJugador(jugador1,jugador2);
	do{
	if(posAct11==0) //Para ficha11
	{
		caracter=65;
		actualizaPosicion1(posAct11,Ficha11,inicio1,caracter);
		inicio1[0][0]='A';
	}
	else
	{
		inicio1[0][0]=255;
		caracter=65;
		actualizaPosicion1(posAct11,Ficha11,inicio1,caracter);
	}
	if(posAct12==0) //Para ficha12
	{
		caracter=66;
		actualizaPosicion1(posAct12,Ficha12,inicio1,caracter);
		inicio1[1][0]='B';
	}
	else
	{
		inicio1[1][0]=255;
		caracter=66;
		actualizaPosicion1(posAct12,Ficha12,inicio1,caracter);
	}
	if(posAct21==0) //Para ficha21
	{
		caracter=67;
		actualizaPosicion2(posAct21,Ficha21,inicio2,caracter);
		inicio2[0][0]='C';
	}
	else
	{
		inicio2[0][0]=255;
		caracter=67;
		actualizaPosicion2(posAct21,Ficha21,inicio2,caracter);
	}
	if(posAct22==0) //Para ficha22
	{
		caracter=68;
		actualizaPosicion2(posAct22,Ficha22,inicio2,caracter);
		inicio2[1][0]='D';
	}
	else
	{
		inicio2[1][0]=255;
		caracter=68;
		actualizaPosicion2(posAct22,Ficha22,inicio2,caracter);
	}
	dibujarTablero(inicio1,Ficha11,Ficha12,inicio2,Ficha21,Ficha22);
	printf("\n\n");
		for(i=0;i<80;i++)
		printf("_");
	switch(turno) //De esta manera se logra intercalar los turnos de los jugadores y sus fichas.
	{
	case 1: //if(primerJugador(jugador1,jugador2)==1)......................................
	do{
		printf("\n\n\n\tTurno de %s: ",nombre1);
		guardaImput=getch();
		if(guardaImput==32) //Entra si se presiona la barra espaciadora.
		{				
			if(posAct12==24)
				turno1=0; //Si la ficha 2 ya llegó al la casilla 24, solo se juega con la ficha 1.
			if(posAct11==24)
				turno1=1; //Si la ficha 1 ya llegó al la casilla 24, solo se juega con la ficha 2.
			if(turno1==0) //--------------------------------------------------------------------------------------JUGADOR 1 --> FICHA 1
			{
				do{
				Ficha=LanzarDado();
				posAct11=posAct11+Ficha;

				if(bloqueo1(posAct11,posAct12)==true)
					printf("\n\t Se ha producido un bloqueo");

				if((posAct11<6)&&(tmp11==0))  /*tmp11 luego cambia de valor para así no volver a entrar 
												aquí y no tener conflictos con el 6 para poder salir al tablero cuando
												una ficha sea desplazada por el oponente.*/
				{ //Muestra en pantalla que aun no puede sacar la ficha porque no ha sacado seis.
				printf("\n\t  Ficha: A\n\t   Dado muestra: %d",Ficha);
				posAct11=0;
				condicionInicial(Ficha,Ficha);
				turno1=1;
				}		
				if((posAct11>=6)||(tmp11!=0))
				{ //tambien entra cuando posAct11 sea menor a 6 (Cuando una ficha parte desde el inicio otra vez).
					if(posAct11==24)
					{ //Indica que la ficha ya llego a la casilla 24.
						posAct11=24;
						printf("\n\t  Ficha: A\n\t   Dado muestra: %d",Ficha);
						printf("\n\tLa ficha A est%c en el TRIANGULO GANADOR",160);
						turno1=1;
					}
					else
					{
						if(posAct11>24)
						{ //Indica que la ficha no puede pasar más allá de la casilla 24.
							posAct11=posAct11-Ficha;
							printf("\n\tLa ficha A no puede pasar mas all%c de 24",160);
							turno1=1;
						}
						if(((posAct11>posAct21)&&(posAct11>posAct22))&&(bloqueo2(posAct21,posAct22)==true))
						{ //Impide que la ficha 1 se mueva ante la presencia de un bloqueo por parte del oponente.
							posAct11=posAct11-Ficha;
							printf("\n\t No puede pasar por el bloqueo");
							turno1=1;
						}
						if(((posAct11==6)&&(posAct21==8))||((posAct11==7)&&(posAct21==7))||((posAct11==8)&&(posAct21==6)))
						{
							posAct21=0;
							printf("\n\t  La ficha del otro jugador a sido dezplazada a 0");
							tmp21=1;
							turno1=1;
						}
						if(((posAct11==6)&&(posAct22==8))||((posAct11==7)&&(posAct22==7))||((posAct11==8)&&(posAct22==6)))
						{
							posAct22=0;
							printf("\n\t  La ficha del otro jugador a sido dezplazada a 0");
							tmp22=1;
							turno1=1;
						}
						if(((Ficha<6)&&(tmp11!=0))&&(posAct11<6))
						{ //Imprime posicion luego de que ha salido pero sin la condicion inicial.
							muestra11(Ficha,posAct11);
							turno1=1;
						}
						if(((Ficha==6)&&(posAct11>6))&&(posAct11<24))
						{ 
							muestra11(Ficha,posAct11);		
							actualizaPosicion1(posAct11,Ficha11,inicio1,65);
							dibujarTablero(inicio1,Ficha11,Ficha12,inicio2,Ficha21,Ficha22);
							ganaTurno();
							getch();
							turno1=0; //Turno1=0 para que así vuelva a entrar a la ficha 1, pues se ha ganado un turno.
						}
						if(((Ficha!=6)&&(posAct11>6))&&(posAct11<24))
						{ //Imprime la posicion en cualquier casilla mayor a 6 y menor a 24.
							muestra11(Ficha,posAct11);
							turno1=1;
						}
						if((Ficha==6)&&(posAct11==6))
						{ //Imprime la primera posicion en el primer movimiento de la ficha (condicion inicial).
							muestra11(Ficha,posAct11);
							turno1=1;
						}
						if((Ficha!=6)&&(posAct11==6))
						{ //Imprime la posicion en la casilla 6, pero no es necesaria la condición inicial.
							muestra11(Ficha,posAct11);
							turno1=1;
						}
					}
				}
				cont11++;
				}while((turno1==0)&&(posAct11!=24));
			}		
			else //--------------------------------------------------------------------------------------JUGADOR 1 --> FICHA 2
			{
				do{
				Ficha=LanzarDado();
				posAct12=posAct12+Ficha;

				if(bloqueo1(posAct11,posAct12)==true)
					printf("\n\t Se ha producido un bloqueo");

				if((posAct12<6)&&(tmp12==0))  /*tmp12 luego cambia de valor para así no volver a entrar 
												aquí y no tener conflictos con el 6 para poder salir al tablero cuando
												una ficha sea desplazada por el oponente.*/
				{ //Muestra en pantalla que aun no puede sacar la ficha porque no ha sacado seis.
					printf("\n\t  Ficha: B\n\t   Dado muestra: %d",Ficha);
					posAct12=0;
					condicionInicial(Ficha,Ficha);
					turno1=0;
				}		
				if((posAct12>=6)||(tmp12!=0))
				{ //tambien entra cuando posAct12 sea menor a 6 (Cuando una ficha parte desde el inicio otra vez).
					if(posAct12==24)
					{ //Indica que la ficha ya llego a la casilla 24.
						posAct12=24;
						printf("\n\t  Ficha: B\n\t   Dado muestra: %d",Ficha);
						printf("\n\tLa ficha B est%c en el TRIANGULO GANADOR",160);
						turno1=0;
					}
					else
					{
						if(posAct12>24)
						{ //Indica que la ficha no puede pasar más allá de la casilla 24.
							posAct12=posAct12-Ficha;
							printf("\n\tLa ficha B no puede pasar mas all%c de 24",160);
							turno1=0;
						}
						if(((posAct12>posAct21)&&(posAct12>posAct22))&&(bloqueo2(posAct21,posAct22)==true))
						{ //Impide que la ficha 2 se mueva ante la presencia de un bloqueo por parte del oponente.
							posAct12=posAct12-Ficha;
							printf("\n\t No puede pasar por el bloqueo");
							turno1=0;
						}
						if(((posAct12==6)&&(posAct21==8))||((posAct12==7)&&(posAct21==7))||((posAct12==8)&&(posAct21==6)))
						{
							posAct21=0;
							printf("\n\t  La ficha del otro jugador a sido dezplazada a 0");
							tmp21=1;
							turno1=0;
						}
						if(((posAct12==6)&&(posAct22==8))||((posAct12==7)&&(posAct22==7))||((posAct12==8)&&(posAct22==6)))
						{
							posAct22=0;
							printf("\n\t  La ficha del otro jugador a sido dezplazada a 0");
							tmp22=1;
							turno1=0;
						}
						if(((Ficha<6)&&(tmp12!=0))&&(posAct12<6))
						{ //Imprime posicion luego de que ha salido pero sin la condicion inicial.
							muestra12(Ficha,posAct12);
							turno1=0;
						}
						if(((Ficha==6)&&(posAct12>6))&&(posAct12<24))
						{
							muestra12(Ficha,posAct12);		
							actualizaPosicion1(posAct12,Ficha12,inicio1,66);
							dibujarTablero(inicio1,Ficha11,Ficha12,inicio2,Ficha21,Ficha22);
							ganaTurno();
							getch();
							turno1=1; //Turno1=1 para que así vuelva a entrar a la ficha 1, pues se ha ganado un turno.
						}
						if(((Ficha!=6)&&(posAct12>6))&&(posAct12<24))
						{ //Imprime la posicion en cualquier casilla mayor a 6 y menor a 24.
							muestra12(Ficha,posAct12);
							turno1=0;
						}
						if((Ficha==6)&&(posAct12==6))
						{ //Imprime la primera posicion en el primer movimiento de la ficha (condicion inicial).
							muestra12(Ficha,posAct12);
							turno1=0;
						}
						if((Ficha!=6)&&(posAct12==6))
						{ //Imprime la posicion en la casilla 6, pero no es necesaria la condición inicial.
							muestra12(Ficha,posAct12);
							turno1=0;
						}
					}				
				}
				cont12++;
				}while((turno1==1)&&(posAct12!=24));
			}
			turno=2;
		}
		if(guardaImput==115) //Entra si se ha presionado la "S".
		{
			printf("\n");
			for(i=1;i<=80;i++)
				printf("-");
			printf("\n	* Usted ha elegido el modo de escape S.            %c%c%c%c",201,205,205,187);
			printf("\n                                                           %c%c%c%c",186,201,187,186);
			printf("\n\t\t 1 - Salir y guardar partida.              %c%c%c%c",186,200,188,186);
			printf("\n\t\t 2 - Cancelar y continuar jugando.         %c%c%c%c",200,205,205,188);
			printf("\n\n   Elija: ");
				scanf("%d",&opcionEscape);
			if(opcionEscape==1) //Opción de salir y guardar.
			{
				in=fopen("ludo.ptd","w");
				GuardarPartida(in,turno,nombre1,posAct11,posAct12,nombre2,posAct21,posAct22);
				fclose(in);
				inLnz=fopen("lanzamientos.ptd","w");
				GuardarLanzamientos(inLnz,cont11,cont12,cont21,cont22);
				fclose(inLnz);
				printf("\n\n\t\tTodos los datos han sido guardados. Hasta la proxima!\n");
				getch();
				exit(1);
			}
			else //Opción de continuar
				turno=1; //turno=1, para que le toque al mismo jugador y a la misma ficha, pues ha decidido seguir jugando.
			printf("\n");
			for(i=1;i<=80;i++)
			printf("-");
		}
	}while(guardaImput!=32);
	break;
	case 2: //if(primerJugador(jugador1,jugador2)==2)......................................
	do{
		printf("\n\n\n\t\t\t\t\t\tTurno de %s: ",nombre2);
		guardaImput=getch();
		if(guardaImput==32)
		{
			if(posAct22==24)
				turno2=0; //Si la ficha 2 ya llegó al la casilla 24, solo se juega con la ficha 1.
			if(posAct21==24)
				turno2=1; //Si la ficha 1 ya llegó al la casilla 24, solo se juega con la ficha 2.
			if(turno2==0) //--------------------------------------------------------------------------------------JUGADOR 2 --> FICHA 1
			{ 
				do{
				Ficha=LanzarDado();
				posAct21=posAct21+Ficha;
				if(bloqueo2(posAct21,posAct22)==true)
					printf("\n\t\t\t\t\t\tSe ha producido un bloqueo");
				if((posAct21<6)&&(tmp21==0))  /*tmp21 luego cambia de valor para así no volver a entrar 
												aquí y no tener conflictos con el 6 para poder salir al tablero cuando
												una ficha sea desplazada por el oponente.*/
				{ //Muestra en pantalla que aun no puede sacar la ficha porque no ha sacado seis.
					printf("\n\t\t\t\t\t\t  Ficha: C\n\t\t\t\t\t\t   Dado muestra: %d",Ficha);
					posAct21=0;
					condicionInicial(Ficha,Ficha);
					turno2=1;
				}		
				if((posAct21>=6)||(tmp21!=0))
				{ //tambien entra cuando posAct21 sea menor a 6 (Cuando una ficha parte desde el inicio otra vez).
					if(posAct21==24)
					{ //Indica que la ficha ya llegó a la casilla 24.
						posAct21=24;
						printf("\n\t\t\t\t\t\t  Ficha: C\n\t\t\t\t\t\t   Dado muestra: %d",Ficha);
						printf("\n\t\t\t\t\tLa ficha C est%c en el TRIANGULO GANADOR",160);
						turno2=1;
					}
					else
					{
						if(posAct21>24)
						{ //Indica que la ficha no puede pasar más allá de la casilla 24.
							posAct21=posAct21-Ficha;
							printf("\n\t\t\t\t  La ficha C no puede pasar mas all%c de 24",160);
							turno2=1;
						}
						if(((posAct21>posAct11)&&(posAct21>posAct12))&&(bloqueo1(posAct11,posAct12)==true))
						{ //Impide que la ficha 2 se mueva ante la presencia de un bloqueo por parte del oponente.
							posAct21=posAct21-Ficha;
							printf("\n\t\t\t\t\t       No puede pasar por el bloqueo");
							turno2=1;
						}
						if(((posAct21==6)&&(posAct11==8))||((posAct21==7)&&(posAct11==7))||((posAct21==8)&&(posAct11==6)))
						{
							posAct11=0;
							printf("\n\t\t\t* La ficha del otro jugador a sido dezplazada a 0");
							tmp11=1;
							turno2=1;
						}
						if(((posAct21==6)&&(posAct12==8))||((posAct21==7)&&(posAct12==7))||((posAct21==8)&&(posAct12==6)))
						{
							posAct12=0;
							printf("\n\t\t\t* La ficha del otro jugador a sido dezplazada a 0");
							tmp12=1;
							turno2=1;
						}			
						if(((Ficha<6)&&(tmp21!=0))&&(posAct21<6))
						{ //Imprime la posición luego de que ha salido pero sin la condición inicial.
							muestra21(Ficha,posAct21);
							turno2=1;
						}
						if(((Ficha==6)&&(posAct21>6))&&(posAct21<24))
						{
							muestra21(Ficha,posAct21);							
							actualizaPosicion2(posAct21,Ficha21,inicio2,67);
							dibujarTablero(inicio1,Ficha11,Ficha12,inicio2,Ficha21,Ficha22);
							ganaTurno();
							getch();
							turno2=0; //Turno2=0 para que así vuelva a entrar a la ficha 1, pues se ha ganado un turno.
						}
						if(((Ficha!=6)&&(posAct21>6))&&(posAct21<24))
						{ //Imprime la posicion en cualquier casilla mayor a 6 y menor a 24.
							muestra21(Ficha,posAct21);
							turno2=1;
						}
						if((Ficha==6)&&(posAct21==6))
						{ //Imprime la primera posicion en el primer movimiento de la ficha (condicion inicial).
							muestra21(Ficha,posAct21);
							turno2=1;
						}
						if((Ficha!=6)&&(posAct21==6))
						{ //Imprime la posicion en la casilla 6, pero no es necesaria la condición inicial.
							muestra21(Ficha,posAct21);
							turno2=1;
						}
					}				
				}
				cont21++;
				}while((turno2==0)&&(posAct21!=24));
			}	
			else //--------------------------------------------------------------------------------------JUGADOR 2 --> FICHA 2
			{	
				do{
				Ficha=LanzarDado();
				posAct22=posAct22+Ficha;
				if(bloqueo2(posAct21,posAct22)==true)
					printf("\n\t\t\t\t\t\tSe ha producido un bloqueo");
				if((posAct22<6)&&(tmp22==0))  /*tmp22 luego cambia de valor para así no volver a entrar 
												aquí y no tener conflictos con el 6 para poder salir al tablero cuando
												una ficha sea desplazada por el oponente.*/
				{ //Muestra en pantalla que aun no puede sacar la ficha porque no ha sacado seis.
					printf("\n\t\t\t\t\t\t  Ficha: D\n\t\t\t\t\t\t   Dado muestra: %d",Ficha);
					posAct22=0;
					condicionInicial(Ficha,Ficha);
					turno2=0;
					turno=1;
				}		
				if((posAct22>=6)||(tmp22!=0))
				{ //tambien entra cuando posAct22 sea menor a 6 (Cuando una ficha parte desde el inicio otra vez)
					if(posAct22==24)
					{ //Indica que la ficha ya llegó a la casilla 24.
						posAct22=24;
						printf("\n\t\t\t\t\t\t  Ficha: D\n\t\t\t\t\t\t   Dado muestra: %d",Ficha);
						printf("\n\t\t\t\t\tLa ficha D est%c en el TRIANGULO GANADOR",160);
						turno2=0;
					}
					else
					{
						if(posAct22>24)
						{ //Indica que la ficha no puede pasar más allá de la casilla 24.
							posAct22=posAct22-Ficha;
							printf("\n\t\t\t\t    La ficha D no puede pasar mas all%c de 24",160);
							turno2=0;
						}
						if(((posAct22>posAct11)&&(posAct22>posAct12))&&(bloqueo1(posAct11,posAct12)==true))
						{ //Impide que la ficha 2 se mueva ante la presencia de un bloqueo por parte del oponente.
							posAct22=posAct22-Ficha;
							printf("\n\t\t\t\t\t       No puede pasar por el bloqueo");
							turno2=0;
						}
						if(((posAct22==6)&&(posAct11==8))||((posAct22==7)&&(posAct11==7))||((posAct22==8)&&(posAct11==6)))
						{
							posAct11=0;
							printf("\n\t\t\t* La ficha del otro jugador a sido dezplazada a 0");
							tmp11=1;
							turno2=0;
						}
						if(((posAct22==6)&&(posAct12==8))||((posAct22==7)&&(posAct12==7))||((posAct22==8)&&(posAct12==6)))
						{
							posAct12=0;
							printf("\n\t\t\t* La ficha del otro jugador a sido dezplazada a 0");
							tmp12=1;
							turno2=0;
						}
						if(((Ficha<6)&&(tmp22!=0))&&(posAct22<6))
						{ //Imprime la posición luego de que ha salido pero sin la condición inicial.
							muestra22(Ficha,posAct22);
							turno2=0;
						}
						if(((Ficha==6)&&(posAct22>6))&&(posAct22<24))
						{
							muestra22(Ficha,posAct22);
							actualizaPosicion2(posAct22,Ficha22,inicio2,68);
							dibujarTablero(inicio1,Ficha11,Ficha12,inicio2,Ficha21,Ficha22);
							ganaTurno();
							getch();
							turno2=1; //Turno2=1 para que así vuelva a entrar a la ficha 1, pues se ha ganado un turno.
						} 
						if(((Ficha!=6)&&(posAct22>6))&&(posAct22<24))
						{ //Imprime la posicion en cualquier casilla mayor a 6 y menor a 24.
							muestra22(Ficha,posAct22);
							turno2=0;
						}
						if((Ficha==6)&&(posAct22==6))
						{ //Imprime la primera posicion en el primer movimiento de la ficha (condicion inicial).
							muestra22(Ficha,posAct22);
							turno2=0;
						}
						if((Ficha!=6)&&(posAct22==6))
						{ //Imprime la posicion en la casilla 6, pero no es necesaria la condición inicial.
							muestra22(Ficha,posAct22);
							turno2=0;
						}
					}	
				}
				cont22++;
				}while((turno2==1)&&(posAct22!=24));
			}
			turno=1;
		}
		if(guardaImput==115) //Entra si se ha presionado la "S".
		{
			printf("\n");
			for(i=1;i<=80;i++)
				printf("-");
			printf("\n	* Usted ha elegido el modo de escape S.            %c%c%c%c",201,205,205,187);
			printf("\n                                                           %c%c%c%c",186,201,187,186);
			printf("\n\t\t 1 - Salir y guardar partida.              %c%c%c%c",186,200,188,186);
			printf("\n\t\t 2 - Cancelar y continuar jugando.         %c%c%c%c",200,205,205,188);
			printf("\n\n   Elija: ");
				scanf("%d",&opcionEscape);
			if(opcionEscape==1) //Opción de salir y guardar.
			{
				in=fopen("ludo.ptd","w");
				GuardarPartida(in,turno,nombre1,posAct11,posAct12,nombre2,posAct21,posAct22);
				fclose(in);
				inLnz=fopen("lanzamientos.ptd","w");
				GuardarLanzamientos(inLnz,cont11,cont12,cont21,cont22);
				fclose(inLnz);
				printf("\n\n\t\tTodos los datos han sido guardados. Hasta la proxima!\n");
				getch();
				exit(1);
			}
			else //Opción de continuar.
				turno=2; //turno=2, para que le toque al mismo jugador y a la misma ficha, pues ha decidido seguir jugando.
			printf("\n");
			for(i=1;i<=80;i++)
				printf("-");
		}
	}while(guardaImput!=32);
	break;
	} //switch(turno)
	//declararGanador(posAct11,posAct12,posAct21,posAct22,cont11,cont12,cont21,cont22);

	if((posAct11==24)&&(posAct12==24)) //Si ambas fichas del jugador 1 están en la casilla 24.
	{
		actualizaPosicion1(posAct11,Ficha11,inicio1,65);
		actualizaPosicion1(posAct12,Ficha12,inicio1,66);
		dibujarTablero(inicio1,Ficha11,Ficha12,inicio2,Ficha21,Ficha22);
		declararGanador(nombre1);
		informacionFichas(nombre1,cont11,cont12,nombre2,cont21,cont22);
		out=fopen("ludo.ptd","w");
		fputs("-1",out);
		fclose(out);
		inTop=fopen("top.txt","r");
		if(inTop==NULL)
			printf("\nERROR al abrir el archivo. Verificar ubicaci%cn del archivo.",162);
		guardaTam=cargarJugadores(inTop,Lista,nombre1);
		fclose(inTop);
		outTop=fopen("top.txt","w");
		guardarJugadores(outTop,Lista,guardaTam);
		fclose(outTop);
	}
	if((posAct21==24)&&(posAct22==24)) //Si ambas fichas del jugador 2 están en la casilla 24.
	{
		actualizaPosicion2(posAct21,Ficha21,inicio2,67);
		actualizaPosicion2(posAct22,Ficha22,inicio2,68);
		dibujarTablero(inicio1,Ficha11,Ficha12,inicio2,Ficha21,Ficha22);
		declararGanador(nombre2);
		informacionFichas(nombre1,cont11,cont12,nombre2,cont21,cont22);
		out=fopen("ludo.ptd","w");
		fputs("-1",out);
		fclose(out);
		inTop=fopen("top.txt","r");
		if(inTop==NULL)
			printf("\nERROR al abrir el archivo. Verificar ubicaci%cn del archivo.",162);
		guardaTam=cargarJugadores(inTop,Lista,nombre2);
		fclose(inTop);
		outTop=fopen("top.txt","w");
		guardarJugadores(outTop,Lista,guardaTam);
		fclose(outTop);
	}
	}while((Ganador(posAct11,posAct12,posAct21,posAct22))!=true); //Mientras no se declare un ganador.
	getch();
	break; // Cierra el case de la opción 1 del menú.

case 2: /*Opción 2 del menú.........................................................................................................
....................................................................................................................................*/
	system("cls");
	Lee=fopen("ludo.ptd","r");
	inLnz=fopen("Lanzamientos.ptd","r");
	if(cargarDatos(Lee)==-1)
	{
		for(i=1;i<=80;i++)
			printf("-");
			printf("   Vac%co...\n",161);
		for(i=1;i<=80;i++)
			printf("-");
			printf("\n\n\ * Opci%cn no disponible, juego previo finalizado.\n\n\t%c Presione una tecla para volver al men%c...",162,175,163);
		fclose(Lee);
		fclose(inLnz);
		getch();
	}
	else //Carga la partida si es que se guardo un juego con anterioridad.
	{
		rewind(Lee); //Volver al inicio del archivo.
		fscanf(Lee,"%d\n",&turno);
		fscanf(Lee,"%[^,]s",nombre1);
		fscanf(Lee,",%d,%d\n",&posAct11,&posAct12);
		fscanf(Lee,"%[^,]s",nombre2);
		fscanf(Lee,",%d,%d",&posAct21,&posAct22);
		fscanf(inLnz,"%d,%d,%d,%d",&cont11,&cont12,&cont21,&cont22);
		for(i=1;i<=80;i++)
			printf("-");
		printf("   Ludo v2.0 - Contin%ca el juego!\n",163);
		for(i=1;i<=80;i++)
			printf("-");
		printf("\n\n      ");
		for(i=0;i<68;i++)
			printf("_");
		printf("\n\n      ---[Recuerde presionar la barra espaciadora para lanzar el dado]---\n      ");
		for(i=0;i<68;i++)
			printf("_");
	do{
	if(posAct11==0) //Para ficha11
	{
		caracter=65;
		actualizaPosicion1(posAct11,Ficha11,inicio1,caracter);
		inicio1[0][0]='A';
	}
	else
	{
		inicio1[0][0]=255;
		caracter=65;
		actualizaPosicion1(posAct11,Ficha11,inicio1,caracter);
	}
	if(posAct12==0) //Para ficha12
	{
		caracter=66;
		actualizaPosicion1(posAct12,Ficha12,inicio1,caracter);
		inicio1[1][0]='B';
	}
	else
	{
		inicio1[1][0]=255;
		caracter=66;
		actualizaPosicion1(posAct12,Ficha12,inicio1,caracter);
	}
	if(posAct21==0) //Para ficha21
	{
		caracter=67;
		actualizaPosicion2(posAct21,Ficha21,inicio2,caracter);
		inicio2[0][0]='C';
	}
	else
	{
		inicio2[0][0]=255;
		caracter=67;
		actualizaPosicion2(posAct21,Ficha21,inicio2,caracter);
	}
	if(posAct22==0) //Para ficha22
	{
		caracter=68;
		actualizaPosicion2(posAct22,Ficha22,inicio2,caracter);
		inicio2[1][0]='D';
	}
	else
	{
		inicio2[1][0]=255;
		caracter=68;
		actualizaPosicion2(posAct22,Ficha22,inicio2,caracter);
	}
	dibujarTablero(inicio1,Ficha11,Ficha12,inicio2,Ficha21,Ficha22);
	printf("\n\n");
		for(i=0;i<80;i++)
		printf("_");
	switch(turno) //De esta manera se logra intercalar los turnos de los jugadores y sus fichas.
	{
	case 1: //if(primerJugador(jugador1,jugador2)==1)......................................
	do{
		printf("\n\n\n\tTurno de %s: ",nombre1);
		guardaImput=getch();
		if(guardaImput==32) //Entra si se presiona la barra espaciadora.
		{				
			if(posAct12==24)
				turno1=0; //Si la ficha 2 ya llegó al la casilla 24, solo se juega con la ficha 1.
			if(posAct11==24)
				turno1=1; //Si la ficha 1 ya llegó al la casilla 24, solo se juega con la ficha 2.
			if(turno1==0) //--------------------------------------------------------------------------------------JUGADOR 1 --> FICHA 1
			{
				do{
				Ficha=LanzarDado();
				posAct11=posAct11+Ficha;

				if(bloqueo1(posAct11,posAct12)==true)
					printf("\n\t Se ha producido un bloqueo");

				if((posAct11<6)&&(tmp11==0))  /*tmp11 luego cambia de valor para así no volver a entrar 
												aquí y no tener conflictos con el 6 para poder salir al tablero cuando
												una ficha sea desplazada por el oponente.*/
				{ //Muestra en pantalla que aun no puede sacar la ficha porque no ha sacado seis.
				printf("\n\t  Ficha: A\n\t   Dado muestra: %d",Ficha);
				posAct11=0;
				condicionInicial(Ficha,Ficha);
				turno1=1;
				}		
				if((posAct11>=6)||(tmp11!=0))
				{ //tambien entra cuando posAct11 sea menor a 6 (Cuando una ficha parte desde el inicio otra vez).
					if(posAct11==24)
					{ //Indica que la ficha ya llego a la casilla 24.
						posAct11=24;
						printf("\n\t  Ficha: A\n\t   Dado muestra: %d",Ficha);
						printf("\n\tLa ficha A est%c en el TRIANGULO GANADOR",160);
						turno1=1;
					}
					else
					{
						if(posAct11>24)
						{ //Indica que la ficha no puede pasar más allá de la casilla 24.
							posAct11=posAct11-Ficha;
							printf("\n\tLa ficha A no puede pasar mas all%c de 24",160);
							turno1=1;
						}
						if(((posAct11>posAct21)&&(posAct11>posAct22))&&(bloqueo2(posAct21,posAct22)==true))
						{ //Impide que la ficha 1 se mueva ante la presencia de un bloqueo por parte del oponente.
							posAct11=posAct11-Ficha;
							printf("\n\t No puede pasar por el bloqueo");
							turno1=1;
						}
						if(((posAct11==6)&&(posAct21==8))||((posAct11==7)&&(posAct21==7))||((posAct11==8)&&(posAct21==6)))
						{
							posAct21=0;
							printf("\n\t  La ficha del otro jugador a sido dezplazada a 0");
							tmp21=1;
							turno1=1;
						}
						if(((posAct11==6)&&(posAct22==8))||((posAct11==7)&&(posAct22==7))||((posAct11==8)&&(posAct22==6)))
						{
							posAct22=0;
							printf("\n\t  La ficha del otro jugador a sido dezplazada a 0");
							tmp22=1;
							turno1=1;
						}
						if(((Ficha<6)&&(tmp11!=0))&&(posAct11<6))
						{ //Imprime posicion luego de que ha salido pero sin la condicion inicial.
							muestra11(Ficha,posAct11);
							turno1=1;
						}
						if(((Ficha==6)&&(posAct11>6))&&(posAct11<24))
						{ 
							muestra11(Ficha,posAct11);		
							actualizaPosicion1(posAct11,Ficha11,inicio1,65);
							dibujarTablero(inicio1,Ficha11,Ficha12,inicio2,Ficha21,Ficha22);
							ganaTurno();
							getch();
							turno1=0; //Turno1=0 para que así vuelva a entrar a la ficha 1, pues se ha ganado un turno.
						}
						if(((Ficha!=6)&&(posAct11>6))&&(posAct11<24))
						{ //Imprime la posicion en cualquier casilla mayor a 6 y menor a 24.
							muestra11(Ficha,posAct11);
							turno1=1;
						}
						if((Ficha==6)&&(posAct11==6))
						{ //Imprime la primera posicion en el primer movimiento de la ficha (condicion inicial).
							muestra11(Ficha,posAct11);
							turno1=1;
						}
						if((Ficha!=6)&&(posAct11==6))
						{ //Imprime la posicion en la casilla 6, pero no es necesaria la condición inicial.
							muestra11(Ficha,posAct11);
							turno1=1;
						}
					}
				}
				cont11++;
				}while((turno1==0)&&(posAct11!=24));
			}		
			else //--------------------------------------------------------------------------------------JUGADOR 1 --> FICHA 2
			{
				do{
				Ficha=LanzarDado();
				posAct12=posAct12+Ficha;

				if(bloqueo1(posAct11,posAct12)==true)
					printf("\n\t Se ha producido un bloqueo");

				if((posAct12<6)&&(tmp12==0))  /*tmp12 luego cambia de valor para así no volver a entrar 
												aquí y no tener conflictos con el 6 para poder salir al tablero cuando
												una ficha sea desplazada por el oponente.*/
				{ //Muestra en pantalla que aun no puede sacar la ficha porque no ha sacado seis.
					printf("\n\t  Ficha: B\n\t   Dado muestra: %d",Ficha);
					posAct12=0;
					condicionInicial(Ficha,Ficha);
					turno1=0;
				}		
				if((posAct12>=6)||(tmp12!=0))
				{ //tambien entra cuando posAct12 sea menor a 6 (Cuando una ficha parte desde el inicio otra vez).
					if(posAct12==24)
					{ //Indica que la ficha ya llego a la casilla 24.
						posAct12=24;
						printf("\n\t  Ficha: B\n\t   Dado muestra: %d",Ficha);
						printf("\n\tLa ficha B est%c en el TRIANGULO GANADOR",160);
						turno1=0;
					}
					else
					{
						if(posAct12>24)
						{ //Indica que la ficha no puede pasar más allá de la casilla 24.
							posAct12=posAct12-Ficha;
							printf("\n\tLa ficha B no puede pasar mas all%c de 24",160);
							turno1=0;
						}
						if(((posAct12>posAct21)&&(posAct12>posAct22))&&(bloqueo2(posAct21,posAct22)==true))
						{ //Impide que la ficha 2 se mueva ante la presencia de un bloqueo por parte del oponente.
							posAct12=posAct12-Ficha;
							printf("\n\t No puede pasar por el bloqueo");
							turno1=0;
						}
						if(((posAct12==6)&&(posAct21==8))||((posAct12==7)&&(posAct21==7))||((posAct12==8)&&(posAct21==6)))
						{
							posAct21=0;
							printf("\n\t  La ficha del otro jugador a sido dezplazada a 0");
							tmp21=1;
							turno1=0;
						}
						if(((posAct12==6)&&(posAct22==8))||((posAct12==7)&&(posAct22==7))||((posAct12==8)&&(posAct22==6)))
						{
							posAct22=0;
							printf("\n\t  La ficha del otro jugador a sido dezplazada a 0");
							tmp22=1;
							turno1=0;
						}
						if(((Ficha<6)&&(tmp12!=0))&&(posAct12<6))
						{ //Imprime posicion luego de que ha salido pero sin la condicion inicial.
							muestra12(Ficha,posAct12);
							turno1=0;
						}
						if(((Ficha==6)&&(posAct12>6))&&(posAct12<24))
						{
							muestra12(Ficha,posAct12);		
							actualizaPosicion1(posAct12,Ficha12,inicio1,66);
							dibujarTablero(inicio1,Ficha11,Ficha12,inicio2,Ficha21,Ficha22);
							ganaTurno();
							getch();
							turno1=1; //Turno1=1 para que así vuelva a entrar a la ficha 1, pues se ha ganado un turno.
						}
						if(((Ficha!=6)&&(posAct12>6))&&(posAct12<24))
						{ //Imprime la posicion en cualquier casilla mayor a 6 y menor a 24.
							muestra12(Ficha,posAct12);
							turno1=0;
						}
						if((Ficha==6)&&(posAct12==6))
						{ //Imprime la primera posicion en el primer movimiento de la ficha (condicion inicial).
							muestra12(Ficha,posAct12);
							turno1=0;
						}
						if((Ficha!=6)&&(posAct12==6))
						{ //Imprime la posicion en la casilla 6, pero no es necesaria la condición inicial.
							muestra12(Ficha,posAct12);
							turno1=0;
						}
					}
				}
				cont12++;
				}while((turno1==1)&&(posAct12!=24));
			}
			turno=2;
		}
		if(guardaImput==115) //Entra si se ha presionado la "S".
		{
			printf("\n");
			for(i=1;i<=80;i++)
				printf("-");
			printf("\n	* Usted ha elegido el modo de escape S.            %c%c%c%c",201,205,205,187);
			printf("\n                                                           %c%c%c%c",186,201,187,186);
			printf("\n\t\t 1 - Salir y guardar partida.              %c%c%c%c",186,200,188,186);
			printf("\n\t\t 2 - Cancelar y continuar jugando.         %c%c%c%c",200,205,205,188);
			printf("\n\n   Elija: ");
				scanf("%d",&opcionEscape);
			if(opcionEscape==1) //Opción de salir y guardar.
			{
				in=fopen("ludo.ptd","w");
				GuardarPartida(in,turno,nombre1,posAct11,posAct12,nombre2,posAct21,posAct22);
				fclose(in);
				in=fopen("lanzamientos.ptd","w");
				GuardarLanzamientos(in,cont11,cont12,cont21,cont22);
				fclose(in);
				printf("\n\n\t\tTodos los datos han sido guardados. Hasta la proxima!\n");
				getch();
				exit(1);
			}
			else //Opción de continuar
				turno=1; //turno=1, para que le toque al mismo jugador y a la misma ficha, pues ha decidido seguir jugando.
			printf("\n");
			for(i=1;i<=80;i++)
			printf("-");
		}
	}while(guardaImput!=32);
	break;
	case 2: //if(primerJugador(jugador1,jugador2)==2)......................................
	do{
		printf("\n\n\n\t\t\t\t\t\tTurno de %s: ",nombre2);
		guardaImput=getch();
		if(guardaImput==32)
		{
			if(posAct22==24)
				turno2=0; //Si la ficha 2 ya llegó al la casilla 24, solo se juega con la ficha 1.
			if(posAct21==24)
				turno2=1; //Si la ficha 1 ya llegó al la casilla 24, solo se juega con la ficha 2.
			if(turno2==0) //--------------------------------------------------------------------------------------JUGADOR 2 --> FICHA 1
			{ 
				do{
				Ficha=LanzarDado();
				posAct21=posAct21+Ficha;
				if(bloqueo2(posAct21,posAct22)==true)
					printf("\n\t\t\t\t\t\tSe ha producido un bloqueo");
				if((posAct21<6)&&(tmp21==0))  /*tmp21 luego cambia de valor para así no volver a entrar 
												aquí y no tener conflictos con el 6 para poder salir al tablero cuando
												una ficha sea desplazada por el oponente.*/
				{ //Muestra en pantalla que aun no puede sacar la ficha porque no ha sacado seis.
					printf("\n\t\t\t\t\t\t  Ficha: C\n\t\t\t\t\t\t   Dado muestra: %d",Ficha);
					posAct21=0;
					condicionInicial(Ficha,Ficha);
					turno2=1;
				}		
				if((posAct21>=6)||(tmp21!=0))
				{ //tambien entra cuando posAct21 sea menor a 6 (Cuando una ficha parte desde el inicio otra vez).
					if(posAct21==24)
					{ //Indica que la ficha ya llegó a la casilla 24.
						posAct21=24;
						printf("\n\t\t\t\t\t\t  Ficha: C\n\t\t\t\t\t\t   Dado muestra: %d",Ficha);
						printf("\n\t\t\t\t\tLa ficha C est%c en el TRIANGULO GANADOR",160);
						turno2=1;
					}
					else
					{
						if(posAct21>24)
						{ //Indica que la ficha no puede pasar más allá de la casilla 24.
							posAct21=posAct21-Ficha;
							printf("\n\t\t\t\t  La ficha C no puede pasar mas all%c de 24",160);
							turno2=1;
						}
						if(((posAct21>posAct11)&&(posAct21>posAct12))&&(bloqueo1(posAct11,posAct12)==true))
						{ //Impide que la ficha 2 se mueva ante la presencia de un bloqueo por parte del oponente.
							posAct21=posAct21-Ficha;
							printf("\n\t\t\t\t\t       No puede pasar por el bloqueo");
							turno2=1;
						}
						if(((posAct21==6)&&(posAct11==8))||((posAct21==7)&&(posAct11==7))||((posAct21==8)&&(posAct11==6)))
						{
							posAct11=0;
							printf("\n\t\t\t* La ficha del otro jugador a sido dezplazada a 0");
							tmp11=1;
							turno2=1;
						}
						if(((posAct21==6)&&(posAct12==8))||((posAct21==7)&&(posAct12==7))||((posAct21==8)&&(posAct12==6)))
						{
							posAct12=0;
							printf("\n\t\t\t* La ficha del otro jugador a sido dezplazada a 0");
							tmp12=1;
							turno2=1;
						}			
						if(((Ficha<6)&&(tmp21!=0))&&(posAct21<6))
						{ //Imprime la posición luego de que ha salido pero sin la condición inicial.
							muestra21(Ficha,posAct21);
							turno2=1;
						}
						if(((Ficha==6)&&(posAct21>6))&&(posAct21<24))
						{
							muestra21(Ficha,posAct21);							
							actualizaPosicion2(posAct21,Ficha21,inicio2,67);
							dibujarTablero(inicio1,Ficha11,Ficha12,inicio2,Ficha21,Ficha22);
							ganaTurno();
							getch();
							turno2=0; //Turno2=0 para que así vuelva a entrar a la ficha 1, pues se ha ganado un turno.
						}
						if(((Ficha!=6)&&(posAct21>6))&&(posAct21<24))
						{ //Imprime la posicion en cualquier casilla mayor a 6 y menor a 24.
							muestra21(Ficha,posAct21);
							turno2=1;
						}
						if((Ficha==6)&&(posAct21==6))
						{ //Imprime la primera posicion en el primer movimiento de la ficha (condicion inicial).
							muestra21(Ficha,posAct21);
							turno2=1;
						}
						if((Ficha!=6)&&(posAct21==6))
						{ //Imprime la posicion en la casilla 6, pero no es necesaria la condición inicial.
							muestra21(Ficha,posAct21);
							turno2=1;
						}
					}
				}
				cont21++;
				}while((turno2==0)&&(posAct21!=24));
			}	
			else //--------------------------------------------------------------------------------------JUGADOR 2 --> FICHA 2
			{	
				do{
				Ficha=LanzarDado();
				posAct22=posAct22+Ficha;
				if(bloqueo2(posAct21,posAct22)==true)
					printf("\n\t\t\t\t\t\tSe ha producido un bloqueo");
				if((posAct22<6)&&(tmp22==0))  /*tmp22 luego cambia de valor para así no volver a entrar 
												aquí y no tener conflictos con el 6 para poder salir al tablero cuando
												una ficha sea desplazada por el oponente.*/
				{ //Muestra en pantalla que aun no puede sacar la ficha porque no ha sacado seis.
					printf("\n\t\t\t\t\t\t  Ficha: D\n\t\t\t\t\t\t   Dado muestra: %d",Ficha);
					posAct22=0;
					condicionInicial(Ficha,Ficha);
					turno2=0;
					turno=1;
				}		
				if((posAct22>=6)||(tmp22!=0))
				{ //tambien entra cuando posAct22 sea menor a 6 (Cuando una ficha parte desde el inicio otra vez)
					if(posAct22==24)
					{ //Indica que la ficha ya llegó a la casilla 24.
						posAct22=24;
						printf("\n\t\t\t\t\t\t  Ficha: D\n\t\t\t\t\t\t   Dado muestra: %d",Ficha);
						printf("\n\t\t\t\t\tLa ficha D est%c en el TRIANGULO GANADOR",160);
						turno2=0;
					}
					else
					{
						if(posAct22>24)
						{ //Indica que la ficha no puede pasar más allá de la casilla 24.
							posAct22=posAct22-Ficha;
							printf("\n\t\t\t\t    La ficha D no puede pasar mas all%c de 24",160);
							turno2=0;
						}
						if(((posAct22>posAct11)&&(posAct22>posAct12))&&(bloqueo1(posAct11,posAct12)==true))
						{ //Impide que la ficha 2 se mueva ante la presencia de un bloqueo por parte del oponente.
							posAct22=posAct22-Ficha;
							printf("\n\t\t\t\t\t       No puede pasar por el bloqueo");
							turno2=0;
						}
						if(((posAct22==6)&&(posAct11==8))||((posAct22==7)&&(posAct11==7))||((posAct22==8)&&(posAct11==6)))
						{
							posAct11=0;
							printf("\n\t\t\t* La ficha del otro jugador a sido dezplazada a 0");
							tmp11=1;
							turno2=0;
						}
						if(((posAct22==6)&&(posAct12==8))||((posAct22==7)&&(posAct12==7))||((posAct22==8)&&(posAct12==6)))
						{
							posAct12=0;
							printf("\n\t\t\t* La ficha del otro jugador a sido dezplazada a 0");
							tmp12=1;
							turno2=0;
						}
						if(((Ficha<6)&&(tmp22!=0))&&(posAct22<6))
						{ //Imprime la posición luego de que ha salido pero sin la condición inicial.
							muestra22(Ficha,posAct22);
							turno2=0;
						}
						if(((Ficha==6)&&(posAct22>6))&&(posAct22<24))
						{
							muestra22(Ficha,posAct22);
							actualizaPosicion2(posAct22,Ficha22,inicio2,68);
							dibujarTablero(inicio1,Ficha11,Ficha12,inicio2,Ficha21,Ficha22);
							ganaTurno();
							getch();
							turno2=1; //Turno2=1 para que así vuelva a entrar a la ficha 1, pues se ha ganado un turno.
						} 
						if(((Ficha!=6)&&(posAct22>6))&&(posAct22<24))
						{ //Imprime la posicion en cualquier casilla mayor a 6 y menor a 24.
							muestra22(Ficha,posAct22);
							turno2=0;
						}
						if((Ficha==6)&&(posAct22==6))
						{ //Imprime la primera posicion en el primer movimiento de la ficha (condicion inicial).
							muestra22(Ficha,posAct22);
							turno2=0;
						}
						if((Ficha!=6)&&(posAct22==6))
						{ //Imprime la posicion en la casilla 6, pero no es necesaria la condición inicial.
							muestra22(Ficha,posAct22);
							turno2=0;
						}
					}	
				}
				cont22++;
				}while((turno2==1)&&(posAct22!=24));
			}
			turno=1;
		}
		if(guardaImput==115) //Entra si se ha presionado la "S".
		{
			printf("\n");
			for(i=1;i<=80;i++)
				printf("-");
			printf("\n	* Usted ha elegido el modo de escape S.            %c%c%c%c",201,205,205,187);
			printf("\n                                                           %c%c%c%c",186,201,187,186);
			printf("\n\t\t 1 - Salir y guardar partida.              %c%c%c%c",186,200,188,186);
			printf("\n\t\t 2 - Cancelar y continuar jugando.         %c%c%c%c",200,205,205,188);
			printf("\n\n   Elija: ");
				scanf("%d",&opcionEscape);
			if(opcionEscape==1) //Opción de salir y guardar.
			{
				in=fopen("ludo.ptd","w");
				GuardarPartida(in,turno,nombre1,posAct11,posAct12,nombre2,posAct21,posAct22);
				fclose(in);
				in=fopen("lanzamientos.ptd","w");
				GuardarLanzamientos(in,cont11,cont12,cont21,cont22);
				fclose(in);
				printf("\n\n\t\tTodos los datos han sido guardados. Hasta la proxima!\n");
				getch();
				exit(1);
			}
			else //Opción de continuar.
				turno=2; //turno=2, para que le toque al mismo jugador y a la misma ficha, pues ha decidido seguir jugando.
			printf("\n");
			for(i=1;i<=80;i++)
				printf("-");
		}
	}while(guardaImput!=32);
	break;
	} //switch(turno)
	//declararGanador(posAct11,posAct12,posAct21,posAct22,cont11,cont12,cont21,cont22);

	if((posAct11==24)&&(posAct12==24)) //Si ambas fichas del jugador 1 están en la casilla 24.
	{
		actualizaPosicion1(posAct11,Ficha11,inicio1,65);
		actualizaPosicion1(posAct12,Ficha12,inicio1,66);
		dibujarTablero(inicio1,Ficha11,Ficha12,inicio2,Ficha21,Ficha22);
		declararGanador(nombre1);
		informacionFichas(nombre1,cont11,cont12,nombre2,cont21,cont22);
		out=fopen("ludo.ptd","w");
		fputs("-1",out);
		fclose(out);
		inTop=fopen("top.txt","r");
		if(inTop==NULL)
			printf("\nERROR al abrir el archivo. Verificar ubicaci%cn del archivo.",162);
		guardaTam=cargarJugadores(inTop,Lista,nombre1);
		fclose(inTop);
		outTop=fopen("top.txt","w");
		guardarJugadores(outTop,Lista,guardaTam);
		fclose(outTop);
	}
	if((posAct21==24)&&(posAct22==24)) //Si ambas fichas del jugador 2 están en la casilla 24.
	{
		actualizaPosicion2(posAct21,Ficha21,inicio2,67);
		actualizaPosicion2(posAct22,Ficha22,inicio2,68);
		dibujarTablero(inicio1,Ficha11,Ficha12,inicio2,Ficha21,Ficha22);
		declararGanador(nombre2);
		informacionFichas(nombre1,cont11,cont12,nombre2,cont21,cont22);
		out=fopen("ludo.ptd","w");
		fputs("-1",out);
		fclose(out);
		inTop=fopen("top.txt","r");
		if(inTop==NULL)
			printf("\nERROR al abrir el archivo. Verificar ubicaci%cn del archivo.",162);
		guardaTam=cargarJugadores(inTop,Lista,nombre2);
		fclose(inTop);
		outTop=fopen("top.txt","w");
		guardarJugadores(outTop,Lista,guardaTam);
		fclose(outTop);
	}
	}while((Ganador(posAct11,posAct12,posAct21,posAct22))!=true); //Mientras no se declare un ganador.
	getch();
	fclose(Lee);
	fclose(inLnz);
}
break;

case 3: /*Opción 3 del menú......................................................................................................... 
....................................................................................................................................*/
	system("cls");
	for(i=1;i<=80;i++)
		printf("-");
	printf("   Acerca de...\n");
	for(i=1;i<=80;i++)
		printf("-");
	printf("\nAutor: D.Schuldt\n\nFecha: Agosto 27/2011\nVersion: 2.0");
	printf("\n\n\tReglas del juego:\n\nPara avanzar, un jugador lanza un dado sobre la mesa de juego, el valor que se obtiene es el numero de casillas que debe avanzar. Cada jugador escoge un cuadrado inicial, el primer jugador lanza el dado y avanza su primera ficha, después lanza el segundo jugador y avanza su primera ficha. De nuevo el primer jugador lanza el dado y avanza su segunda ficha, después lanza el segundo jugador y avanza su segunda ficha.\n\nPero hay varias reglas para poder avanzar en el tablero:\n\n");
		dibujaTablero();
	printf("\n\n\n\t%c Al empezar para poder sacar una ficha por primera vez, se debe lanzar \ty sacar seis.\n\n\t%c Durante el juego, cada vez que se obtenga un seis, se gana un turno y \tel jugador debe lanzar de nuevo los dados y avanzar su ficha.\n\n\t%c Si la ficha cae en una casilla ocupada por una ficha del contrincante,\tla ficha del oponente se regresa a su cuadrado inicial.\n\n\t%c Si la ficha cae en una casilla ocupada por una ficha propia esto forma\tun bloqueo. El bloqueo no puede ser pasado por alguna de las fichas del \toponente.\n\n\t%c Cuando una ficha recorre todo el tablero, puede entrar a la columna de\tsu color para caer en el TRIANGULO GANADOR, pero se debe lanzar el numer\to exacto.\n\n\t%c Se declara ganador al primer jugador que lleve todas sus fichas al TRI\tANGULO GANADOR.\n\n\t%c Cada ficha tiene un recorrido distinto por el tablero.\n\n\n\n\t\t\t   **Mejoras en la versi%cn 2**",175,175,175,175,175,175,175,162);
	printf("\n\n\n\n\t%c PERSONALIZACI%CN DEL JUEGO, al iniciar el juego se solicitar%c a los \n\tusuarios ingresar su nombre. El nombre ser%c utilizado para indicarle a \n\tun jugador que es su turno y felicitar al jugador cuando gane el juego.",175,224,160,160);
	printf("\n\n\t%c LISTA DE JUGADORES TOP, la cual consiste en la creaci%cn de archivo de \tnombre top.txt. Este archivo contiene 1 listado que incluye los nombres \ty las veces que 1 jugador ha ganado el juego ordenados de mayor a menor.",175,162);
	printf("\n\t%c CONTINUAR PARTIDA, permite cargar datos provenientes del archivo ludo.\tptd para dar continuidad a una partida iniciada previamente. Si la \n\t%cltima vez que se jug%c Ludo se finaliz%c la partida, esta opci%cn no \n\testar%c disponible y en lugar de %csta aparecer%c la opci%cn Nueva Partida.",175,163,162,162,162,160,130,160,162);
	printf("\n\n\t%c GUARDAR PARTIDA, permite grabar autom%cticamente en un archivo llamado \tludo.ptd los datos que permitir%cn dar continuidad a una partida iniciada \ten el caso de no haber sido terminada.",175,160,160);
	//muestra();
	printf("\n\n\n   Presione una tecla para retornar al men%c.",163);
	getch();
	break;

case SALIR: /*Opción 4 del menú......................................................................................................... 
........................................................................................................................................*/
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\tFinal del programa.\n\tUn proyecto desarrollado por D. Schuldt. y B.Olmedo");
	getch();
	break;

}
//Actualizaciones de valor para la siguiente partida.
posAct11=0, posAct12=0, jugador2, posAct21=0, posAct22=0, tmp11=0, tmp12=0, tmp21=0, tmp22=0;
Ficha=0, turno1=0, turno2=0, cont11=0, cont12=0, cont21=0, cont22=0, turno=0,guardaTam=0;
flushall();
}while(op!=SALIR);
}//fin de main.


															/*Declaración de funciones*/

/* 
*  Procedimiento: menuPrincipal 
*  Uso: menuPrincipal(); 
*          ---------------------------------------------------------- 
*  Descripcion: Muestra en pantalla el menú del juego.
*/ 
void menuPrincipal(void)
{
	int i;
	system("cls");
	for(i=1;i<=80;i++)
		printf("-");
	printf("\t\t\t\t    Ludo v2.0\n\t\t    -An original desing for a common project-\n");
	for(i=1;i<=80;i++)
		printf("-");
	printf("\n -Se recomienda maximizar la consola para un mejor panorama del juego.");
	printf("\n\n\t* Men%c:\n\n\t\t1 %c Nueva partida\n\t\t2 %c Continuar partida\n\t\t3 %c Acerca de...\n\t\t4 %c Salir\n\n",163,175,175,175,175);
}

/* 
*  Procedimiento: dibujaTablero 
*  Uso: dibujaTablero();
*          ---------------------------------------------------------- 
*  Descripcion: Este procedimiento muestra un detallado y muy elaborado tablero de juego... (:
*/ 
void dibujaTablero(void)
{
	printf("\n\n\t%c%c%c%c%c%c%c%c%c%c%c%c%cFicha 1: A\n\t%cJugador%c1%c\n\t%c%c%c%c%c%c%c%c%c%c%c%c%cFicha 2: B",201,205,205,205,205,205,205,205,205,205,187,32,32,186,32,186,200,205,205,205,205,205,205,205,205,205,188,32,32);
	printf("\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,187,201,187,201,187,201,187,201,187,255,255,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,200,188,200,188,200,188,200,188,200,188,255,255,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188);
	printf("\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,187,49,55,255,255,49,56,201,187,49,255,255,255,50,255,255,255,51,255,255,255,52,255,255,255,53,255,255,255,54,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,201,187,200,188,255,255,255,255,255,255,200,188,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,200,188);
	printf("\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,187,255,255,201,187,255,255,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,255,255,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,255,255,201,187,200,188,255,255,200,188,255,255,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,255,255,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,255,255,200,188);
	printf("\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,187,49,54,201,187,49,57,255,255,50,48,255,255,50,49,255,255,50,50,255,255,50,51,255,255,50,52,201,187,55,255,201,187,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,201,187,255,255,201,187,200,188,255,255,200,188,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,200,188,255,255,200,188,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,200,188,255,255,200,188);
	printf("\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,187,255,255,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,255,255,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,255,255,201,187,255,255,201,187,200,188,255,255,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,255,255,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,255,255,200,188,255,255,200,188);
	printf("\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,187,49,53,255,255,49,52,255,255,49,51,255,255,49,50,255,255,49,49,255,255,49,48,255,255,57,255,255,255,56,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,201,187,255,255,255,255,255,255,201,187,200,188,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,200,188,255,255,255,255,255,255,200,188);
	printf("\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,255,255,201,187,201,187,201,187,201,187,201,187,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,255,255,200,188,200,188,200,188,200,188,200,188);
	printf("\t\t\t\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%cFicha 1: C\n\t\t\t\t\t\t%cJugador%c2%c\n\t\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%cFicha 2: D",201,205,205,205,205,205,205,205,205,205,187,32,32,186,32,186,200,205,205,205,205,205,205,205,205,205,188,32,32);
}

/* 
*  Función: LanzarDado  
*  Uso: a=LanzarDado();  
*          ---------------------------------------------------------- 
*  Descripción: Esta función retorna un número que simula el número obtenido con un dado.    
*/ 
int LanzarDado(void)
{
return 1+rand()%6;
}

/* 
*  Función: primerJugador  
*  Uso: primerJugador(a,b);  
*          ---------------------------------------------------------- 
*  Descripción: Función que compara el resultado de los números conseguidos por los jugadores
*				para saber quien es el primer jugador.
*/ 
int primerJugador(int a, int b)
{
	if(a>b)
		return 1;
	if(a<b)
		return 2;
	if(a==b) 
		return 0;
}

/* 
*  Funciones: bloqueo1 // bloqueo2  
*  Uso: bloqueo1(posiciónFicha1,posiciónFicha2); // bloqueo2(posiciónFicha1,posiciónFicha2)
*          ---------------------------------------------------------- 
*  Descripción (cada una): Esta función compara las posiciones de las dos fichas de un jugador, con cada una de las fichas del oponente. Si las dos fichas
*				de un jugador coinciden en una misma casilla, el oponente no podrá moverse hacia esa casilla o más allá hasta que el jugador no
*				tenga una de sus fichas fuera de la misma.
*/ 
bool bloqueo1(int posiciónFicha1, int posiciónFicha2)
{
	if((posiciónFicha1==6)&&(posiciónFicha2==6))
		return true;
	if((posiciónFicha1==7)&&(posiciónFicha2==7))
		return true;
	if((posiciónFicha1==8)&&(posiciónFicha2==8))
		return true;
	if(posiciónFicha1!=posiciónFicha2)
		return false;
}
bool bloqueo2(int posiciónFicha1, int posiciónFicha2)
{
	if((posiciónFicha1==6)&&(posiciónFicha2==6))
		return true;
	if((posiciónFicha1==7)&&(posiciónFicha2==7))
		return true;
	if((posiciónFicha1==8)&&(posiciónFicha2==8))
		return true;
		if(posiciónFicha1!=posiciónFicha2)
		return false;
}

/* 
*  Procedimiento: declararGanador 
*  Uso: declararGanador(nombre1);
*          ---------------------------------------------------------- 
*  Descripcion: Este procedimiento imprime en pantalla una felicitación al ganador del juego.
*/ 
void declararGanador (char *nombre)
{
	int i;
	printf("\n\n\n\n");
	for(i=1;i<=80;i++)
		printf("-");
	printf("\t\t\t       --------------------\n");
	printf("\t\t\t        %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",174,179,205,205,205,205,205,205,205,205,205,205,205,205,205,205,179,175);
	printf("\t\t\t       --------------------\n");
	printf("\t\t\t                %c%c\n",192,217);
	printf("\t\t\t       El ganador es %s!\n\t\t\t          FELICIDADES! :D",nombre);
	printf("\n\t\t\t                %c%c\n",218,191);
	printf("\t\t\t       --------------------\n");
	printf("\t\t\t        %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",174,179,205,205,205,205,205,205,205,205,205,205,205,205,205,205,179,175);
	printf("\t\t\t       --------------------\n");
	for(i=1;i<=80;i++)
		printf("-");
}

/* 
*  Procedimiento: informacionFichas.
*  Uso: informacionFichas(nombre1,cont11,cont12,nombre2,cont21,cont22);
*          ---------------------------------------------------------- 
*  Descripción: Muestra las veces que fueron movidas las fichas de cada jugador.
*/ 
void informacionFichas(char a[], int b, int c, char d[], int e, int f)
{
	printf("\n\n\t* Datos de %s:",a);
	printf("\n   -Ficha 1: %d lanzamientos.\n   -Ficha 2: %d lanzamientos.",b,c);
	printf("\n\n\t* Datos de %s:",d);
	printf("\n   -Ficha 1: %d lanzamientos.\n   -Ficha 2: %d lanzamientos.",e,f);
	printf("\n\n\t * Presione una tecla para regresar al men%c.\n",163);
}

/* 
*  Función: Ganador.
*  Uso: Ganador(posAct11,posAct12,posAct21,posAct22);
*          ---------------------------------------------------------- 
*  Descripción: Función booleana que retorna true si hay un ganador. Caso contrario retorna false.
*/ 
bool Ganador(int a, int b, int c, int d)
{
	if(((a==24)&&(b==24))||((c==24)&&(d==24)))
		return true;
	return false;
}

/* 
*  Función: condicionInicial  
*  Uso: condicionInicial(a,b); 
*          ---------------------------------------------------------- 
*  Descripción: Función que determina si un jugador puede mover una de sus fichas para empezar el recorrido por el tablero, o no.  
*/ 
int condicionInicial(int jug1, int jug2)
{
	if(jug1!=6)
		printf("\n\t* Debe sacar seis para poder mover la ficha por primera vez.\n");
	return jug2;
}

/* 
*  Procedimiento: ganaTurno 
*  Uso: ganaTurno();
*          ---------------------------------------------------------- 
*  Descripcion: Muestra un cuadro en pantalla, indicando que el jugador ha ganado un turno. 
*/ 
void ganaTurno(void)
{
	printf("\n\n\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",255,255,255,201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
	printf("\t\t\t%c%c%c%c%c%c%c%c%cGan%c un turno!%c%c%c%c%c%c\n",255,255,255,186,255,255,255,255,255,162,255,255,255,255,255,186);
	printf("\t\t\t%c%c%c%c%cLance el dado otra vez%c%c\n",255,255,255,186,255,255,186);
	printf("\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",255,255,255,200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
}

/* 
*  Procedimientos: muestra11 // muestra12 // muestra21 // muestra22
*  Uso: muestra11(a,b); // muestra12(a,b); // muestra21(a,b); // muestra22(a,b);
*          ---------------------------------------------------------- 
*  Descripcion (cada uno): Este procedimiento muestra en pantalla que ficha es la que se debe mover de cada jugador, el resultado
*				del dado y en que posición está dicha ficha.
*/ 
void muestra11(int x, int y) // muestra11(Ficha,posAct11);
{
	printf("\n\t  Ficha: A\n\t   Dado muestra: %d",x);
	printf("\n\t   Posicion actual: %d",y);
}
void muestra12(int x, int y) // muestra12(Ficha,posAct12);
{
	printf("\n\t  Ficha: B\n\t   Dado muestra: %d",x);
	printf("\n\t   Posicion actual: %d",y);
}
void muestra21(int x, int y) // muestra21(Ficha,posAct21);
{
	printf("\n\t\t\t\t\t\t  Ficha: C\n\t\t\t\t\t\t   Dado muestra: %d",x);
	printf("\n\t\t\t\t\t\t   Posicion actual: %d",y);
}
void muestra22(int x, int y) // muestra22(Ficha,posAct22);
{
	printf("\n\t\t\t\t\t\t  Ficha: D\n\t\t\t\t\t\t   Dado muestra: %d",x);
	printf("\n\t\t\t\t\t\t   Posicion actual: %d",y);
}

/* 
*  Función: cargarDatos.
*  Uso: Ganador(in);
*          ---------------------------------------------------------- 
*  Descripción: Esta función lee un archivo y retorna un entero: -1 si no hay un juego grabado con anterioridad, ó 1 si es que si lo hay.
*/ 
int cargarDatos(FILE *archivo)
{
	char tmp[MAX];
	fscanf(archivo,"%s",tmp);
	if(strcmp(tmp,"-1")==0)
		return -1;
	else
		return 1;
}

/* 
*  Procedimiento: GuardarPartida.
*  Uso: GuardarPartida(out,turno,nombre1,posAct11,posAct12,nombre2,posAct21,posAct22);
*          ---------------------------------------------------------- 
*  Descripcion: Graba en un archivo llamado ludo.ptd los datos que permitan dar continuidad a una partida iniciada.
*/ 
void GuardarPartida(FILE *archivo, int turno, char  *nombre1, int ficha11, int ficha12, char *nombre2, int ficha21, int ficha22)
{
	fprintf(archivo,"%d\n",turno);
	fprintf(archivo,"%s,%d,%d\n",nombre1,ficha11,ficha12);
	fprintf(archivo,"%s,%d,%d",nombre2,ficha21,ficha22);
}

/* 
*  Procedimiento: GuardarLanzamientos.
*  Uso: GuardarLanzamientos(out,cont11,cont12,cont21,cont22);
*          ---------------------------------------------------------- 
*  Descripcion: Graba en un archivo llamado lanzamientos.ptd los datos que permitan dar continuidad al numero de lanzamientos que llevaba cada ficha.
*/ 
void GuardarLanzamientos(FILE *archivo, int cont11, int cont12, int cont21, int cont22)
{
	fprintf(archivo,"%d,%d,%d,%d",cont11,cont12,cont21,cont22);
}

/* 
*  Función: cargarJugadores.
*  Uso: cargarJugadores(in,variable,nombre1)
*          ---------------------------------------------------------- 
*  Descripción: Agrega un nuevo jugador al archivo "top.txt", ordena los jugadores por veces ganadas de mayor a menor.
*				Devuelve el numero de jugadores en el archivo top.
*/ 
int cargarJugadores(FILE *top, jugadorT palabras[], char jugador[30])
{
	char guardaTmp[100];
	int tmp;
	int cont=0,i=0,j=0,cont2=0;
	while(!feof(top))
	{
		fscanf(top,"%d %s\n",&palabras[cont].vecesGanadas,palabras[cont].jugador);
		cont++;
	}
	for(i=0;i<cont;i++)
	{
		if(strcmp(palabras[i].jugador,jugador)==0)
		{
			palabras[i].vecesGanadas++;
			cont2++;
		}
	}
	if(cont2==0)
	{
		strcpy(palabras[cont].jugador,jugador);
		palabras[cont].vecesGanadas=1;
		cont++;
	}
	for(i=1;i<=cont;i++)
	{
		if(palabras[i-1].vecesGanadas<palabras[i].vecesGanadas)
		{
			tmp=palabras[i-1].vecesGanadas;
			palabras[i-1].vecesGanadas=palabras[i].vecesGanadas;
			palabras[i].vecesGanadas=tmp;
			strcpy(guardaTmp,palabras[i-1].jugador);
			strcpy(palabras[i-1].jugador,palabras[i].jugador);
			strcpy(palabras[i].jugador,guardaTmp);
		}
	}
	return cont;
}

/* 
*  Procedimientos: guardarJugadores.
*  Uso: guardarJugadores(out,variable,tam);
*          ---------------------------------------------------------- 
*  Descripcion: Procedimiento que guarda el archivo "top.txt".
*/ 
void guardarJugadores(FILE *top, jugadorT palabras[], int tamanio)
{
	int i=0;
	for(i=0;i<tamanio;i++)
	{
		fprintf(top,"%d %s\n",palabras[i].vecesGanadas,palabras[i].jugador);
	}
}

/* 
*  Procedimiento: dibujarTablero 
*  Uso: dibujarTablero();
*          ---------------------------------------------------------- 
*  Descripcion: Este procedimiento muestra un detallado y muy elaborado tablero de juego vacio, en el cual se mostrarán las pisiciones de las fichas.
*/ 
void dibujarTablero(char inicio1[2][1],char Ficha11[3][8],char Ficha12[3][8],char inicio2[2][1],char Ficha21[3][8],char Ficha22[3][8])
{
	printf("\n\n\t%c%c%c%c%c%c%c%c%c%c%c%c%cFicha 1: %c",201,205,205,205,205,205,205,205,205,205,187,32,32,inicio1[0][0]);
	printf("\n\t%cJugador%c1%c\n\t%c%c%c%c%c%c%c%c%c%c%c%c%cFicha 2: %c",186,32,186,200,205,205,205,205,205,205,205,205,205,188,32,32,inicio1[1][0]);
	printf("\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,187,201,187,201,187,201,187,201,187,255,255,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,200,188,200,188,200,188,200,188,200,188,255,255,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188);
	printf("\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,187,Ficha11[0][0],255,255,255,Ficha11[0][1],255,201,187,Ficha11[0][2],255,255,255,Ficha11[0][3],255,255,255,Ficha11[0][4],255,255,255,Ficha11[0][5],255,255,255,Ficha11[0][6],255,255,255,Ficha11[0][7],Ficha22[0][0],255,255,255,Ficha22[0][1],255,255,255,Ficha22[0][2],255,255,255,Ficha22[0][3],255,255,255,Ficha22[0][4],255,255,255,Ficha22[0][5],255,255,255,Ficha22[0][6],255,255,255,Ficha22[0][7],201,187,200,188,255,Ficha12[0][0],255,255,255,Ficha12[0][1],200,188,255,Ficha12[0][2],255,255,255,Ficha12[0][3],255,255,255,Ficha12[0][4],255,255,255,Ficha12[0][5],255,255,255,Ficha12[0][6],255,255,Ficha21[0][0],Ficha12[0][7],255,255,Ficha21[0][1],255,255,255,Ficha21[0][2],255,255,255,Ficha21[0][3],255,255,255,Ficha21[0][4],255,255,255,Ficha21[0][5],255,255,255,Ficha21[0][6],255,255,255,Ficha21[0][7],255,200,188);
	printf("\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,187,255,255,201,187,255,255,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,255,255,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,255,255,201,187,200,188,255,255,200,188,255,255,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,255,255,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,255,255,200,188);
	printf("\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,187,Ficha11[1][0],255,201,187,Ficha11[1][1],255,255,255,Ficha11[1][2],255,255,255,Ficha11[1][3],255,255,255,Ficha11[1][4],255,255,255,Ficha11[1][5],255,255,255,Ficha11[1][6],255,201,187,Ficha11[1][7],Ficha22[1][0],201,187,Ficha21[1][1],255,255,255,Ficha21[1][2],255,255,255,Ficha21[1][3],255,255,255,Ficha21[1][4],255,255,255,Ficha21[1][5],255,255,255,Ficha21[1][6],255,201,187,255,Ficha22[1][7],201,187,200,188,255,Ficha12[1][0],200,188,255,Ficha12[1][1],255,255,255,Ficha12[1][2],255,255,255,Ficha12[1][3],255,255,255,Ficha12[1][4],255,255,255,Ficha12[1][5],255,255,255,Ficha12[1][6],200,188,Ficha21[1][0],Ficha12[1][7],200,188,255,Ficha22[1][1],255,255,255,Ficha22[1][2],255,255,255,Ficha22[1][3],255,255,255,Ficha22[1][4],255,255,255,Ficha22[1][5],255,255,255,Ficha22[1][6],200,188,Ficha21[1][7],255,200,188);
	printf("\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,187,255,255,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,255,255,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,255,255,201,187,255,255,201,187,200,188,255,255,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,255,255,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,255,255,200,188,255,255,200,188);
	printf("\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,187,Ficha11[2][0],255,255,255,Ficha11[2][1],255,255,255,Ficha11[2][2],255,255,255,Ficha11[2][3],255,255,255,Ficha11[2][4],255,255,255,Ficha11[2][5],255,255,255,Ficha11[2][6],255,255,255,Ficha21[2][0],Ficha11[2][7],255,255,Ficha21[2][1],255,255,255,Ficha21[2][2],255,255,255,Ficha21[2][3],255,255,255,Ficha21[2][4],255,255,255,Ficha21[2][5],255,201,187,Ficha21[2][6],255,255,255,Ficha21[2][7],255,201,187,200,188,255,Ficha12[2][0],255,255,255,Ficha12[2][1],255,255,255,Ficha12[2][2],255,255,255,Ficha12[2][3],255,255,255,Ficha12[2][4],255,255,255,Ficha12[2][5],255,255,255,Ficha12[2][6],255,255,Ficha12[2][7],Ficha22[2][0],255,255,255,Ficha22[2][1],255,255,255,Ficha22[2][2],255,255,255,Ficha22[2][3],255,255,255,Ficha22[2][4],255,255,255,Ficha22[2][5],200,188,255,Ficha22[2][6],255,255,255,Ficha22[2][7],200,188);
	printf("\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,201,187,255,255,201,187,201,187,201,187,201,187,201,187,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,200,188,255,255,200,188,200,188,200,188,200,188,200,188);
	printf("\t\t\t\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%cFicha 1: %c\n\t\t\t\t\t\t%cJugador%c2%c\n\t\t\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%cFicha 2: %c",201,205,205,205,205,205,205,205,205,205,187,32,32,inicio2[0][0],186,32,186,200,205,205,205,205,205,205,205,205,205,188,32,32,inicio2[1][0]);
}

/* 
*  Procedimiento: actualizaPosicion1
*  Uso: actualizaPosicion1(posAct,Ficha,inicio1,caracter);
*          ---------------------------------------------------------- 
*  Descripcion: Este procedimiento actualiza la posicion en tablero de Ficha11 o Ficha12, de acuerdo a como se use la función.
*/ 
void actualizaPosicion1(int posAct, char Ficha[3][8], char inicio1[2][1], char c)
{
	int i=0,j=0,k=0;
		for(i=0;i<3;i++)
		{
			for(j=0;j<8;j++)
				Ficha[i][j]=255;
		}
	if(posAct!=0)
	{
		for(k=1;k<7;k++)
		{
			if(posAct==k)
				Ficha[0][k+1]=c;
		}
		if(posAct==7)
			Ficha[1][7]=c;
		if(posAct==8)
			Ficha[2][7]=c;
		if(posAct==9)
			Ficha[2][6]=c;
		if(posAct==10)
			Ficha[2][5]=c;
		if(posAct==11)
			Ficha[2][4]=c;
		if(posAct==12)
			Ficha[2][3]=c;
		if(posAct==13)
			Ficha[2][2]=c;
		if(posAct==14)
			Ficha[2][1]=c;
		if(posAct==15)
			Ficha[2][0]=c;
		if(posAct==16)
			Ficha[1][0]=c;
		if(posAct==17)
			Ficha[0][0]=c;
		if(posAct==18)
			Ficha[0][1]=c;
		for(k=19;k<25;k++)
		{
			if(posAct==k)
				Ficha[1][k-18]=c;
		}
	}
}

/* 
*  Procedimiento: actualizaPosicion2
*  Uso: actualizaPosicion2(posAct,Ficha,inicio2,caracter);
*          ---------------------------------------------------------- 
*  Descripcion: Este procedimiento actualiza la posicion en tablero de Ficha21 o Ficha22, de acuerdo a como se use la función.
*/ 
void actualizaPosicion2(int posAct, char Ficha[3][8], char inicio2[2][1], char c)
{
	int i=0,j=0,k=0,cont=6;
		for(i=0;i<3;i++)
		{
			for(j=0;j<8;j++)
				Ficha[i][j]=255;
		}
	if(posAct!=0)
	{
		if(posAct==1)
			Ficha[2][5]=c;
		if(posAct==2)
			Ficha[2][4]=c;
		if(posAct==3)
			Ficha[2][3]=c;
		if(posAct==4)
			Ficha[2][2]=c;
		if(posAct==5)
			Ficha[2][1]=c;
		if(posAct==6)
			Ficha[2][0]=c;
		if(posAct==7)
			Ficha[1][0]=c;
		if(posAct==8)
			Ficha[0][0]=c;
		for(k=9;k<16;k++)
		{
			if(posAct==k)
				Ficha[0][k-8]=c;
		}
		if(posAct==16)
			Ficha[1][7]=c;
		if(posAct==17)
			Ficha[2][7]=c;
		if(posAct==18)
			Ficha[2][6]=c;
		if(posAct==19)
			Ficha[1][6]=c;
		if(posAct==20)
			Ficha[1][5]=c;
		if(posAct==21)
			Ficha[1][4]=c;
		if(posAct==22)
			Ficha[1][3]=c;
		if(posAct==23)
			Ficha[1][2]=c;
		if(posAct==24)
			Ficha[1][1]=c;
	}
}
