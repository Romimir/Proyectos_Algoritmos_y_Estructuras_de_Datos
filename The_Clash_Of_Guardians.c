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
    struct cartas *next;
} Cartas_Juego;

//Funcion para crear carta
void Crear_Carta(Cartas_Juego *carta_creada)
{
    int ClaseGuardian;
    printf("***********************************************\n");
    printf("* Bienvenido al apartado para crear una carta *\n");
    printf("*     ¿Que nombre desea darle al guardian?     *\n");
    scanf("%s", &carta_creada->Nombre);

    printf("¿De que clase sera el guardian? \n");
    printf("Ingresa un numero para asignarle la clase a tu guardian");
    //validacion de clase valida
    do
    {
        printf("(1)Mago, (2)Vikingo, Nigromante(3), Bestia(4)");
        scanf("%s", &carta_creada->Clase);   
        //mensaje de aviso
        if (ClaseGuardian<=0 || ClaseGuardian>=5)
        {
            printf("por favor ingrese una clase valida");
        }
        else
        {
            //Le asigna la clase ingresada a la carta creada
            switch (ClaseGuardian)
            {
                case 1:
                    carta_creada->Clase = "Mago";
                    break;
                case 2:
                    carta_creada->Clase = "Vikingo";
                    break;
                case 3:
                    carta_creada->Clase = "Nigromante";
                    break;
                case 4:
                    carta_creada->Clase = "Bestia";
                    break;        
            }
        }
        
         
    } while (ClaseGuardian >=1 && ClaseGuardian <= 4);

    //Verifica que la vida ingresada sea un valor entre 1 y 200
    printf("¿Cuanta vida posee el guardian? \n"); 
    do
    {
        printf("La vida debe ser un valor entre 1 y 200\n");
        scanf("%d", &carta_creada->Vida);
        if (carta_creada->Vida <1 || carta_creada->Vida > 200)
        {
            printf("Por favor ingrese un valor para vida valido\n");
        }
        
    } while (carta_creada->Vida < 1 && carta_creada->Vida > 200);

    //Verifica que el ataque ingresado sea un valor entre 1 y 200
    printf("¿Cuanto ataque tiene el guardian?");

    do
    {   
        printf("El ataque debe ser un valor entre 1 y 200\n");

        scanf("%d", &carta_creada->Ataque);

    } while (carta_creada->Ataque <1 && carta_creada->Ataque >200);
    
    //Verifica que la defensa ingresada sea un valor entre 1 y 200
    printf("¿Cuanta defensa tiene el guardian?");
    do
    {   
        printf("La defensa debe ser un valor entre 1 y 200\n");

        scanf("%d", &carta_creada->Defensa);

    } while (carta_creada->Defensa <1 && carta_creada->Defensa >200);
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

        if (Opcion <=0 || Opcion >=5)
        {
                printf("Por favor ingrese una opcion valida");
        }
        else
        {
            switch (Opcion)
            {
                case 1:
                    //agregar funcion Crear_Carta para que se guarde en Cartas_Juego.txt las cartas creadas
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
        }
        
    } while (Opcion >= 1 && Opcion <= 4);

    


    return 0;
}