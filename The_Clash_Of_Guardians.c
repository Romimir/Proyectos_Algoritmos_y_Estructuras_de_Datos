#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estructura para leer Cartas.txt
typedef struct cartas 
{
    char Nombre[100];
    char Clase[20];
    int Vida;
    int Ataque;
    int Defensa;
    struct cartas* next;
} Cartas_Juego;

typedef struct jugador 
{
  // Mano de cartas
  Cartas_Juego* mano[3];
  // Baraja de cartas
  Cartas_Juego* baraja[15];
  // Puntos de vida
  int puntosDeVida;
} Jugador;


// PREPARACIÓN DEL JUEGO

// Función para cargar cartas desde un archivo
Cartas_Juego* cargarCartasDesdeArchivo(const char* nombreArchivo) 
{
    FILE* archivoCartas = fopen(nombreArchivo, "r");
    if (archivoCartas == NULL) 
    {
        printf("Error al abrir el archivo de cartas.\n");
        return NULL;
    }

    Cartas_Juego* primerCarta = NULL;
    Cartas_Juego* ultimaCarta = NULL;

    while (!feof(archivoCartas)) 
    {
        Cartas_Juego* nuevaCarta = (Cartas_Juego*)malloc(sizeof(Cartas_Juego));
        if (nuevaCarta == NULL) 
        {
            printf("Error al asignar memoria para la nueva carta.\n");
            fclose(archivoCartas);
            return NULL;
        }

        int elementosLeidos = fscanf(archivoCartas, "%[^,],%[^,],%d,%d,%d\n", nuevaCarta->Nombre, nuevaCarta->Clase,
                                     &nuevaCarta->Vida, &nuevaCarta->Ataque, &nuevaCarta->Defensa);

        if (elementosLeidos == 5) 
        {
            nuevaCarta->next = NULL;

            if (primerCarta == NULL) 
            {
                primerCarta = nuevaCarta;
                ultimaCarta = nuevaCarta;
            } else 
            {
                ultimaCarta->next = nuevaCarta;
                ultimaCarta = nuevaCarta;
            }
        } 
        else 
        {
            printf("Error al leer los datos de la carta desde el archivo.\n");
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
        printf("Error al abrir el archivo de cartas.\n");
        return;
    }

    fprintf(archivoCartas, "%s,%s,%d,%d,%d\n", nuevaCarta->Nombre, nuevaCarta->Clase,
                        nuevaCarta->Vida, nuevaCarta->Ataque, nuevaCarta->Defensa);

    fclose(archivoCartas);
}


// Función para imprimir cartas
void Imprimir_Cartas(Cartas_Juego* lista_cartas) 
{
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

    printf("************************************************************\n");
    printf("*         Bienvenido al apartado para crear cartas         *\n");
    printf("*            Que nombre desea darle al guardian?           *\n");
    scanf("%s", &nuevaCarta->Nombre);
    printf("*              De que clase sera el guardian?              *\n");
    printf("*    Ingresa uno de los siguientes numeros para la clase   *\n");
   
    //validacion de clase valida
    do
    {
        printf("*       (1)Mago, (2)Vikingo, Nigromante(3), Bestia(4)      *\n");
        scanf("%d", &ClaseGuardian);  // FAltaba el &
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
                    strcpy(nuevaCarta->Clase, "Mago"); // Eran sin el &
                    break;
                case 2:
                    strcpy(nuevaCarta->Clase, "Vikingo");
                    break;
                case 3:
                    strcpy(nuevaCarta->Clase, "Nigromante");
                    break;
                case 4:
                    strcpy(nuevaCarta->Clase, "Bestia");
                    break;        
            }
        }
    } while (ClaseGuardian < 1 || ClaseGuardian > 5); //Se usaba || en vez de &&

    //Verifica que la vida ingresada sea un valor entre 1 y 200
    printf("*¿             Cuanta vida posee el guardian?*             *\n"); 
    do
    {
        printf("*          La vida debe ser un valor entre 1 y 200         *\n");
        scanf("%d", &nuevaCarta->Vida);
        if (nuevaCarta->Vida < 1 || nuevaCarta->Vida > 200)
        {
            printf("*       Por favor ingrese un valor para vida valido        *\n");
        }
        
    } while (nuevaCarta->Vida < 1 || nuevaCarta->Vida > 200); //Se usaba || en vez de &&

    //Verifica que el ataque ingresado sea un valor entre 1 y 200
    printf("*             ¿Cuanto ataque tiene el guardian?            *\n");

    do
    { 
        printf("*        El ataque debe ser un valor entre 1 y 200         *\n");

        scanf("%d", &nuevaCarta->Ataque);

    } while (nuevaCarta->Ataque < 1 || nuevaCarta->Ataque > 200); //Se usaba || en vez de &&
    
    //Verifica que la defensa ingresada sea un valor entre 1 y 200
    printf("*            ¿Cuanta defensa tiene el guardian?            *\n");
    do
    {   
        printf("*        La defensa debe ser un valor entre 1 y 200        *\n");

        scanf("%d", &nuevaCarta->Defensa);

    } while (nuevaCarta->Defensa < 1 || nuevaCarta->Defensa > 200); //Se usaba || en vez de &&

    Agregar_Carta(nuevaCarta, "Cartas_Juego.txt");
}


// Función para revolver cartas de manera aleatoria
void revolverCartas(Cartas_Juego **cartas, int numeroCartas) 
{
    // Crear un array para almacenar las cartas
    Cartas_Juego **cartasArray = (Cartas_Juego **)malloc(numeroCartas * sizeof(Cartas_Juego *));
    if (cartasArray == NULL) {
        printf("Error al asignar memoria para el array de cartas.\n");
        return;
    }

    // Llenar el array con las cartas
    Cartas_Juego *actual = *cartas;
    int i = 0;
    while (actual != NULL) 
    {
        cartasArray[i] = actual;
        actual = actual->next;
        i++;
    }

    // Usar una semilla aleatoria para garantizar que la mezcla sea aleatoria
    srand(time(NULL));

    // Mezclar el array de cartas de manera aleatoria
    for (i = numeroCartas - 1; i > 0; i--) 
    {
        int j = rand() % (i + 1);
        Cartas_Juego *temp = cartasArray[i];
        cartasArray[i] = cartasArray[j];
        cartasArray[j] = temp;
    }

    // Reconstruir la lista de cartas con el nuevo orden
    for (i = 0; i < numeroCartas - 1; i++) 
    {
        cartasArray[i]->next = cartasArray[i + 1];
    }
    cartasArray[numeroCartas - 1]->next = NULL;

    // Actualizar el puntero original a la primera carta
    *cartas = cartasArray[0];

    // Liberar el array temporal
    free(cartasArray);
}


// FUNCIONES DEL JUEGO

void repartir(Cartas_Juego *cartas, Jugador *jugador, Jugador *NPC) 
{
    // Inicializa las manos de jugador y NPC
    for (size_t i = 0; i < 15; i++) 
    {
        jugador->baraja[i] = NULL;
        NPC->baraja[i] = NULL;
    }

    // Asigna las cartas al jugador de manera secuencial
    Cartas_Juego *cartaActual = cartas;
    size_t i = 0;
    while (cartaActual != NULL && i < 15) 
    {
        jugador->baraja[i] = cartaActual;
        cartaActual = cartaActual->next;
        i++;
    }
    
    i = 0;  // Reinicia i para las cartas del NPC
    while (cartaActual != NULL && i < 15)
    {
        NPC->baraja[i] = cartaActual;
        cartaActual = cartaActual->next;
        i++;
    }
}




void juego(Cartas_Juego *cartas)
{
    Jugador* jugador = (Jugador*)malloc(sizeof(Jugador));
    Jugador* NPC = (Jugador*)malloc(sizeof(Jugador));

    jugador-> puntosDeVida = 5;
    NPC-> puntosDeVida = 5;

    repartir(cartas, jugador, NPC);

}

int main() 
{
    int Opcion;
    Cartas_Juego *cartas = cargarCartasDesdeArchivo("Cartas_Juego.txt");
    int numeroCartas = 0;

    Imprimir_Cartas(cartas);

    Cartas_Juego *paraContar = cartas;
    while (paraContar != NULL)
    {
        numeroCartas++;
        paraContar = paraContar->next;
    }

    
    printf("Cartas %d \n",numeroCartas);

    do {
        cartas = cargarCartasDesdeArchivo("Cartas_Juego.txt");
        printf("***********************************************\n");
        printf("*     Bienvenido a The Clash Of Guardians     *\n");
        printf("*    Para crear tu propia carta ingrese 1     *\n");
        printf("* Para ver el historial de partidas ingrese 2 *\n");
        printf("*             Para jugar ingrese 3            *\n");
        printf("*    Si desea salir del programa ingrese 4    *\n");
        printf("***********************************************\n");
        scanf("%d", &Opcion);

        if (Opcion <= 0 || Opcion >= 5) 
        {
            printf("Por favor ingrese una opcion valida");
        } 
        else 
        {
            switch (Opcion) 
            {
                case 1:
                    Crear_Carta(&cartas);
                    numeroCartas++;
                    break;

                case 2:
                    revolverCartas(&cartas, numeroCartas);
                    Imprimir_Cartas(cartas);
                    break;

                case 3:
                    revolverCartas(&cartas, numeroCartas);
                    juego(cartas);
                    break;

                case 4:
                    printf("¡Gracias por jugar The Clash of Guardians!\n");
                    exit(0);
                    break;
            }
        }
    } while (Opcion >= 1 && Opcion <= 4);

    return 0;
}