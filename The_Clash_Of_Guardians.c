#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//estructura para leer Cartas.txt
typedef struct cartas
{
    char Nombre[10];
    char Clase;
    int Vida;
    int Ataque;
    int Defensa;

} Cartas_Juego;

void Crear_Carta(Cartas_Juego * carta_creada)
{
    printf("***********************************************\n");
    printf("* Bienvenido al apartado para crear una carta *\n");
    printf("*     ¿Que nombre desea darle al guardian?     *\n");
    scanf("%c", &carta_creada->Nombre);

    printf("¿De que clase sera el guardian? \n");
    printf("Recuerda que debes ingresar una de las siguientes");
    printf("Mago, Vikingo, Nigromante, Bestia");
    scanf("%c", &carta_creada->Clase);

    printf("¿Cuanta vida posee el guardian? \n"); 
    do
    {
        printf("La vida debe ser un valor entre 1 y 200\n");
        scanf("%d", &carta_creada->Vida);
        if (carta_creada->Vida <1 || carta_creada->Vida > 200)
        {
            printf("Por favor ingrese un valor para vida valido\n");
        }
        
    } while (carta_creada->Vida < 1 || carta_creada->Vida > 200);

    printf("¿Cuanto ataque tiene el guardian?");

    do
    {   
        printf("El ataque debe ser un valor entre 1 y 200\n");

        scanf("%d", &carta_creada->Ataque);

    } while (carta_creada->Ataque <1 || carta_creada->Ataque >200);
    
    printf("¿Cuanta defensa tiene el guardian?");
    do
    {   
        printf("La defensa debe ser un valor entre 1 y 200\n");

        scanf("%d", &carta_creada->Defensa);

    } while (carta_creada->Defensa <1 || carta_creada->Defensa >200);
}
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
    _sleep(5);
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
        _sleep(5);
        exit(1);
        break;
    }


    return 0;
}