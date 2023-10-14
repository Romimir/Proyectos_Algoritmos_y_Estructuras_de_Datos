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


// Función para cargar cartas desde un archivo
Cartas_Juego *cargarCartasDesdeArchivo(const char *nombreArchivo) 
{
    FILE *archivoCartas = fopen(nombreArchivo, "r");
    if (archivoCartas == NULL) 
    {
        printf("Error al abrir el archivo de cartas\n");
        return NULL;
    }

    Cartas_Juego *primerCarta = NULL;
    Cartas_Juego *ultimaCarta = NULL;

    while (!feof(archivoCartas)) 
    {
        Cartas_Juego *nuevaCarta = (Cartas_Juego*)malloc(sizeof(Cartas_Juego));
        if (nuevaCarta == NULL) 
        {
            printf("Ah ocurrido un error al asignar memoria para la nueva carta\n");
            fclose(archivoCartas);
            return NULL;
        }

        int elementosLeidos = fscanf(archivoCartas, "%[^,],%[^,],%d,%d,%d\n", nuevaCarta->Nombre, nuevaCarta->Clase, &nuevaCarta->Vida, &nuevaCarta->Ataque, &nuevaCarta->Defensa);
        if (elementosLeidos == 5) 
        {
            nuevaCarta->next = NULL;

            if (primerCarta == NULL) 
            {
                primerCarta = nuevaCarta;
                ultimaCarta = nuevaCarta;
            }
            else 
            {
                ultimaCarta->next = nuevaCarta;
                ultimaCarta = nuevaCarta;
            }
        }
        else 
        {
            printf("Ah ocurrido un error al leer los datos de la carta desde el archivo\n");
            free(nuevaCarta);
        }
    }
    fclose(archivoCartas);
    return primerCarta;
}


void Agregar_Carta(Cartas_Juego* nuevaCarta, const char* nombreArchivo) 
{
    FILE* archivoCartas = fopen(nombreArchivo, "a");
    if (archivoCartas == NULL) 
    {
        printf("Error al abrir el archivo de cartas\n");
        return;
    }

    fprintf(archivoCartas, "%s,%s,%d,%d,%d\n", nuevaCarta->Nombre, nuevaCarta->Clase, nuevaCarta->Vida, nuevaCarta->Ataque, nuevaCarta->Defensa);

    fclose(archivoCartas);
}


// Función para imprimir cartas
void Imprimir_Cartas(Cartas_Juego* lista_cartas) {
    printf("Lista de Cartas:\n");
    while (lista_cartas != NULL) {
        printf("Nombre: %s\n", lista_cartas->Nombre);
        printf("Clase: %s\n", lista_cartas->Clase);
        printf("Vida: %d\n", lista_cartas->Vida);
        printf("Ataque: %d\n", lista_cartas->Ataque);
        printf("Defensa: %d\n", lista_cartas->Defensa);
        printf("\n");
        lista_cartas = lista_cartas->next;
    }
}


//Funcion para crear carta
void Crear_Carta(Cartas_Juego **carta_creada)
{
    int ClaseGuardian;
    Cartas_Juego *nuevaCarta = (Cartas_Juego*)malloc(sizeof(Cartas_Juego));

    printf("***********************************************\n");
    printf("* Bienvenido al apartado para crear una carta *\n");
    printf("*     ¿Que nombre desea darle al guardian?     *\n");
    scanf("%s", &nuevaCarta->Nombre);
    printf("¿De que clase sera el guardian? \n");
    printf("Ingresa un numero para asignarle la clase a tu guardian");
    //validacion de clase valida
    do
    {
        printf("(1)Mago, (2)Vikingo, Nigromante(3), Bestia(4)");
        scanf("%s", &nuevaCarta->Clase);   
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
                    nuevaCarta->Clase = "Mago";
                    break;
                case 2:
                    nuevaCarta->Clase = "Vikingo";
                    break;
                case 3:
                    nuevaCarta->Clase = "Nigromante";
                    break;
                case 4:
                    nuevaCarta->Clase = "Bestia";
                    break;        
            }
        }
        
         
    } while (ClaseGuardian >=1 && ClaseGuardian <= 4);

    //Verifica que la vida ingresada sea un valor entre 1 y 200
    printf("¿Cuanta vida posee el guardian? \n"); 
    do
    {
        printf("La vida debe ser un valor entre 1 y 200\n");
        scanf("%d", &nuevaCarta->Vida);
        if (nuevaCarta->Vida <1 || nuevaCarta->Vida > 200)
        {
            printf("Por favor ingrese un valor para vida valido\n");
        }
        
    } while (nuevaCarta->Vida < 1 && nuevaCarta->Vida > 200);

    //Verifica que el ataque ingresado sea un valor entre 1 y 200
    printf("¿Cuanto ataque tiene el guardian?");

    do
    {   
        printf("El ataque debe ser un valor entre 1 y 200\n");

        scanf("%d", &nuevaCarta->Ataque);

    } while (nuevaCarta->Ataque <1 && nuevaCarta->Ataque >200);
    
    //Verifica que la defensa ingresada sea un valor entre 1 y 200
    printf("¿Cuanta defensa tiene el guardian?");
    do
    {   
        printf("La defensa debe ser un valor entre 1 y 200\n");

        scanf("%d", &nuevaCarta->Defensa);

    } while (nuevaCarta->Defensa <1 && nuevaCarta->Defensa >200);

    Agregar_Carta(nuevaCarta, "Cartas_Juego.txt");
}


void jugador(int vidas)
{
    vidas = 5;
  
}


int main()
{
    int Opcion;
    Cartas_Juego *cartas = cargarCartasDesdeArchivo("Cartas_Juego.txt");
    Imprimir_Cartas(cartas);

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
                    Crear_Carta(&cartas);
                break;
    
                case 2:
                    Imprimir_Cartas(cartas);

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