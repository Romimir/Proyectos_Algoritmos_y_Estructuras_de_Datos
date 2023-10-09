#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//estructura para leer Cartas.txt
typedef struct cartas
{
    char Nombre[50];
    char Clase;
    int Vida;
    int Ataque;
    int Defensa;
} Cartas;

int main()
{
    int Opcion;

    //Menú y verificacion de opciones validas

    do
    {
    printf("***********************************************\n");
    printf("*     Bienvenido a The Clash Of Guardians     *\n");
    printf("*    Para crear tu propia carta ingrese 1     *\n");
    printf("* Para ver el historial de partidas ingrese 2 *\n");
    printf("*             Para jugar ingrese 3            *\n");
    printf("*    Si desea salir del programa ingrese 4    *\n");
    printf("***********************************************\n");
    scanf("%d", &Opcion);
    } while (Opcion >= 1 && Opcion <= 4);

    switch (Opcion)
    {
    case 1:
        /* code */
        break;
    
    case 2:

        break;

    case 3:

        break;

    case 4:
        printf("¡Gracias por jugar the clash of guardians!\n");
        exit(1);
        break;
    }


    return 0;
}