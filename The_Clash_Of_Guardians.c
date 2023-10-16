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

// Estructura para manejar al jugador y NPC
typedef struct jugador 
{
  Cartas_Juego* mano[15];
  Cartas_Juego* baraja[15];
  int puntosDeVida;
  int cartas;
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
            } 
            else 
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

// Funcion para agregar las cartas al archivo
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
    while (lista_cartas != NULL) 
    {
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
   
    //validacion de clase
    do
    {
        printf("*       (1)Mago, (2)Vikingo, Nigromante(3), Bestia(4)      *\n");
        scanf("%d", &ClaseGuardian);

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
                    strcpy(nuevaCarta->Clase, "Mago");
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
    } while (ClaseGuardian < 1 || ClaseGuardian > 5); 

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
        
    } while (nuevaCarta->Vida < 1 || nuevaCarta->Vida > 200);

    //Verifica que el ataque ingresado sea un valor entre 1 y 200
    printf("*             ¿Cuanto ataque tiene el guardian?            *\n");

    do
    { 
        printf("*        El ataque debe ser un valor entre 1 y 200         *\n");

        scanf("%d", &nuevaCarta->Ataque);

    } while (nuevaCarta->Ataque < 1 || nuevaCarta->Ataque > 200);
    
    //Verifica que la defensa ingresada sea un valor entre 1 y 200
    printf("*            ¿Cuanta defensa tiene el guardian?            *\n");
    do
    {   
        printf("*        La defensa debe ser un valor entre 1 y 200        *\n");

        scanf("%d", &nuevaCarta->Defensa);

    } while (nuevaCarta->Defensa < 1 || nuevaCarta->Defensa > 200);

    Agregar_Carta(nuevaCarta, "Cartas_Juego.txt");
}

// Función para revolver cartas de manera aleatoria
void Revolver_Cartas(Cartas_Juego **cartas, int numeroCartas) 
{


    // Crear un array para almacenar las cartas
    Cartas_Juego **cartasArray = (Cartas_Juego **)malloc(numeroCartas * sizeof(Cartas_Juego *));
    if (cartasArray == NULL) 
    {
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

// Revolver la baraja de cartas
void Revolver_Baraja(Cartas_Juego **baraja, int numeroCartas) {
    // Crear un array para almacenar las cartas
    Cartas_Juego **cartasArray = (Cartas_Juego **)malloc(numeroCartas * sizeof(Cartas_Juego *));
    if (cartasArray == NULL) {
        printf("Error al asignar memoria para el array de cartas.\n");
        return;
    }

    // Llenar el array con las cartas de la baraja del jugador
    for (int i = 0; i < numeroCartas; i++) {
        cartasArray[i] = baraja[i];
    }

    // Usar una semilla aleatoria para garantizar que la mezcla sea aleatoria
    srand(time(NULL));

    // Mezclar el array de cartas de manera aleatoria
    for (int i = numeroCartas - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Cartas_Juego *temp = cartasArray[i];
        cartasArray[i] = cartasArray[j];
        cartasArray[j] = temp;
    }

    // Copiar el array mezclado de vuelta a la baraja del jugador
    for (int i = 0; i < numeroCartas; i++) {
        baraja[i] = cartasArray[i];
    }

    // Liberar el array temporal
    free(cartasArray);
}

// Repartir carta entre los jugadores
void Repartir(Cartas_Juego *cartas, Jugador *jugador, Jugador *NPC) {
    // Inicializa las manos de jugador y NPC
    for (size_t i = 0; i < 15; i++) {
        jugador->baraja[i] = NULL;
        NPC->baraja[i] = NULL;
    }

    // Asigna las cartas al jugador de manera secuencial
    Cartas_Juego *cartaActual = cartas;
    size_t i = 0;
    while (cartaActual != NULL && i < 15) {
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

// Seleccionar cartas iniciales
void Seleccionar(Jugador *jugador)
{
    int seleccion = 0;
    int cartaUno = 0;
    int cartaDos = 0;
    // Imprime las cartas en la mano del jugador
    printf("Cartas en la baraja del jugador:\n");
    for (size_t j = 0; j < 15; j++) {
        if (jugador->baraja[j] != NULL) {
            printf("%d Nombre: %s \nClase: %s \nAtaque/Defensa/Vida: %d/%d/%d\n", j+1, jugador->baraja[j]->Nombre, jugador->baraja[j]->Clase, jugador->baraja[j]->Ataque, jugador->baraja[j]->Defensa, jugador->baraja[j]->Vida);
        }
        printf("\n");
    }

    printf("Seleccione el número de la primera carta de la mano: ");
    do
    {
        scanf("%d", &seleccion);
        fflush(stdin);
        if (seleccion > 0 && seleccion < 16)
        {
            jugador->mano[0] = jugador->baraja[seleccion-1];
            cartaUno = seleccion;
            printf("Carta seleccionada\n");
        }
        else
        {
            printf("Seleccione un valor valido\n");
        }
        
    } while (seleccion < 1 || seleccion > 15);

    printf("Seleccione el número de la segunda carta de la mano: ");
    do
    {
        scanf("%d", &seleccion);
        fflush(stdin);
        if (seleccion > 0 && seleccion < 16 && seleccion != cartaUno)
        {
            jugador->mano[1] = jugador->baraja[seleccion-1];
            cartaDos = seleccion;
            printf("Carta seleccionada\n");
        }
        else
        {
            printf("Seleccione un valor valido\n");
        }
        
    } while (seleccion < 1 || seleccion > 15 || seleccion == cartaUno);

    printf("Seleccione el número de la segunda carta de la mano: ");
    do
    {
        scanf("%d", &seleccion);
        fflush(stdin);
        if (seleccion > 0 && seleccion < 16 && seleccion != cartaUno && seleccion != cartaDos)
        {
            jugador->mano[2] = jugador->baraja[seleccion-1];
            printf("Carta seleccionada\n");
        }
        else
        {
            printf("Seleccione un valor valido\n");
        }
        
    } while (seleccion < 1 || seleccion > 15 || seleccion == cartaUno || seleccion == cartaDos);
    
    printf("Cartas en la mano del jugador:\n");
    for (size_t j = 0; j < 3; j++) {
        if (jugador->mano[j] != NULL) 
        {
            printf("%d Nombre: %s \nClase: %s \nAtaque/Defensa/Vida: %d/%d/%d\n", j+1, jugador->mano[j]->Nombre, jugador->mano[j]->Clase, jugador->mano[j]->Ataque, jugador->mano[j]->Defensa, jugador->mano[j]->Vida);
        }
        printf("\n");
    }

    Revolver_Baraja(jugador->baraja, 15);
}

// Asignar cartas iniciales al NPC
void Asignar(Jugador *NPC)
{
    int cartas_disponibles[15]; // Un arreglo para mantener un seguimiento de las cartas disponibles
    for (int i = 0; i < 15; i++)
    {
        cartas_disponibles[i] = i;
    }

    // Inicializa la semilla aleatoria
    srand(time(NULL));

    // Asigna 3 cartas aleatorias al NPC sin repetir
    for (int i = 0; i < 3; i++)
    {
        int carta_aleatoria;
        do
        {
            carta_aleatoria = rand() % 15; // Genera un número aleatorio entre 0 y 14
        } while (cartas_disponibles[carta_aleatoria] == -1);

        NPC->mano[i] = NPC->baraja[carta_aleatoria];
        cartas_disponibles[carta_aleatoria] = -1; // Marca la carta como asignada
    }

    printf("Cartas en la mano del NPC:\n");
    for (size_t j = 0; j < 3; j++) {
        if (NPC->mano[j] != NULL) {
            printf("%d Nombre: %s \nClase: %s \nAtaque/Defensa/Vida: %d/%d/%d\n", j+1, NPC->mano[j]->Nombre, NPC->mano[j]->Clase, NPC->mano[j]->Ataque, NPC->mano[j]->Defensa, NPC->mano[j]->Vida);
        }
        printf("\n");
    }
}

// Roba cartas de la baraja
void Robar(Jugador *jugador) {
    // Iterar sobre la baraja del jugador
    for (int i = 0; i < 15; i++) {
        if (jugador->baraja[i] != NULL) {
            Cartas_Juego *cartaRobada = jugador->baraja[i];
            // Verificar si la carta ya está en la mano del jugador
            int repetida = 0;
            for (int j = 0; j < jugador->cartas; j++) {
                if (jugador->mano[j] != NULL) {
                    if (strcmp(jugador->mano[j]->Nombre, cartaRobada->Nombre) == 0) {
                        repetida = 1;
                        break;  // Sale del bucle interno si encuentra una carta repetida
                    }
                } else if (jugador->mano[j] != NULL && jugador->mano[j]->Vida <= 0) {
                    // Reemplaza la carta si está en la mano y su Vida es menor o igual a 0
                    jugador->mano[j] = cartaRobada;
                    return;  // Sale de la función después de reemplazar
                }
            }

            if (!repetida) {
                // Agregar la carta robada a la mano del jugador
                if (jugador->cartas < 15) {
                    jugador->mano[jugador->cartas] = cartaRobada;
                    jugador->cartas++;
                }
                break;  // Sale del bucle externo si agrega una carta
            }
        }
    }
    
    if (jugador->cartas == 15) {
        printf("No quedan cartas en la baraja del jugador para robar o todas las cartas disponibles ya están en la mano del jugador.\n");
    }
}

// Ataque del jugador al NPC
void Atacar(Jugador *jugador, Jugador *NPC)
{
    int opcionAtacante;
    int opcionAtacado;
    int danio;
    printf("¿Con que carta desea atacar?\n");
    printf("Cartas en la mano:\n");
    for (size_t j = 0; j < jugador->cartas; j++) {
        if (jugador->mano[j] != NULL && jugador->mano[j]->Vida > 0) {
            printf("%d Nombre: %s \nClase: %s \nAtaque/Defensa/Vida: %d/%d/%d\n", j+1, jugador->mano[j]->Nombre, jugador->mano[j]->Clase, jugador->mano[j]->Ataque, jugador->mano[j]->Defensa, jugador->mano[j]->Vida);
        }
        printf("\n");
    }
    do
    {
        scanf("%d", &opcionAtacante);
        if (opcionAtacante >= 1 && opcionAtacante <= jugador->cartas && jugador->mano[opcionAtacante-1]->Vida > 0)
        {
            printf("Atacante seleccionado\n");
        }
        else
        {
            printf("Opcion invalida, intente nuevamente: \n");
        }
        
    } while (opcionAtacante < 1 || opcionAtacante > jugador->cartas || jugador->mano[opcionAtacante-1]->Vida <= 0);
    

    printf("¿A que carta desea atacar?\n");
    printf("Cartas en la mano del NPC:\n");
    for (size_t j = 0; j < NPC->cartas; j++) 
    {
        if (NPC->mano[j] != NULL && NPC->mano[j]->Vida > 0) 
        {
            printf("%d Nombre: %s \nClase: %s \nAtaque/Defensa/Vida: %d/%d/%d\n", j+1, NPC->mano[j]->Nombre, NPC->mano[j]->Clase, NPC->mano[j]->Ataque, NPC->mano[j]->Defensa, NPC->mano[j]->Vida);
            printf("\n");
        }
    }

    do
    {
        scanf("%d", &opcionAtacado);
        if ((opcionAtacado >= 1 && opcionAtacado <= NPC->cartas) && NPC->mano[opcionAtacado-1]->Vida > 0)
        {
            printf("Objetivo seleccionado\n");
        }
        else
        {
            printf("Opcion invalida, intente nuevamente: \n");
        }
        
    } while (opcionAtacado < 1 || opcionAtacado > NPC->cartas || NPC->mano[opcionAtacado-1]->Vida <= 0);

    danio = jugador->mano[opcionAtacante - 1]->Ataque - NPC->mano[opcionAtacado - 1]->Defensa;

    // Asegurarse de que el daño no sea negativo
    if (danio < 0) 
    {
        danio = 0;
    }

    // Reducir la vida del objetivo según el daño infligido
    NPC->mano[opcionAtacado - 1]->Vida -= danio;
    
    printf("%s ataca a %s y le inflije %d puntos de daño, le quedan %d puntos de vida\n", jugador->mano[opcionAtacante-1]->Nombre, NPC->mano[opcionAtacado-1]->Nombre, jugador->mano[opcionAtacante-1]->Ataque-NPC->mano[opcionAtacado-1]->Defensa, NPC->mano[opcionAtacado-1]->Vida);

    if (NPC->mano[opcionAtacado - 1]->Vida <= 0)
    {
        NPC->puntosDeVida--;
        Robar(NPC);
    }
}

// Ataque del NPC al jugador
void Atacar_NPC(Jugador *NPC, Jugador *jugador)
{
    int opcionAtacante, opcionAtacado, maxAtaque = 0, minVida = 300;
    int danio;
    for (size_t j = 0; j < NPC->cartas; j++) 
    {
        if (NPC->mano[j] != NULL && NPC->mano[j]->Ataque > maxAtaque && NPC->mano[j]->Vida > 0) 
        {
            maxAtaque = NPC->mano[j]->Ataque;
            opcionAtacante = j;
        }
    }
    
    for (size_t j = 0; j < jugador->cartas; j++) 
    {
        if (jugador->mano[j] != NULL && jugador->mano[j]->Vida > 0 && jugador->mano[j]->Vida < minVida) 
        {
            minVida = jugador->mano[j]->Vida;
            opcionAtacado = j;
        }
    }

    danio = NPC->mano[opcionAtacante]->Ataque - jugador->mano[opcionAtacado]->Defensa;

    // Asegurarse de que el daño no sea negativo
    if (danio < 0) 
    {
        danio = 0;
    }

    // Reducir la vida del objetivo según el daño infligido
    jugador->mano[opcionAtacado]->Vida -= danio;
    
    printf("%s ataca a %s y le inflije %d puntos de daño, le quedan %d puntos de vida\n", NPC->mano[opcionAtacante]->Nombre, jugador->mano[opcionAtacado]->Nombre, NPC->mano[opcionAtacante]->Ataque - jugador->mano[opcionAtacado]->Defensa, jugador->mano[opcionAtacado]->Vida);

    if (jugador->mano[opcionAtacado]->Vida <= 0)
    {
        jugador->puntosDeVida--;
        Robar(jugador);
    }
}

// Turno del NPC
int Turno_NPC(Jugador *jugador, Jugador *NPC)
{
    int decision = (rand() % 10) + 1;

    if (decision <= 7)
    {
        printf("Ataque\n");
        Atacar_NPC(NPC, jugador);
    }
    else
    {
        printf("Roba carta\n");
        Robar(NPC);
    }

    return 1;
    
}

// Turno del jugador
int Turno_Jugador(Jugador *jugador, Jugador *NPC)
{
    int opcion;
    
    printf("¿Que accion desea realizar?");
    printf("\n\t1. Tomar una carta.");
    printf("\n\t2. Atacar.\n");
    do
    {
        scanf("%d", &opcion);
        if(opcion == 1)
        {
            Robar(jugador);
        }
        else if(opcion == 2)
        {
            Atacar(jugador, NPC);
        }
        else
        {
            printf("Opcion invalida");
        }
    } while (opcion < 1 || opcion > 3);
    

    return 2;
}

// Gameloop
void Juego(Cartas_Juego *cartas)
{
    int turno = 1;
    Jugador* jugador = (Jugador*)malloc(sizeof(Jugador));
    Jugador* NPC = (Jugador*)malloc(sizeof(Jugador));

    jugador-> puntosDeVida = 5;
    NPC-> puntosDeVida = 5;
    jugador->cartas = 3;
    NPC-> cartas = 3;

    Repartir(cartas, jugador, NPC);

    Seleccionar(jugador);

    Asignar(NPC);

    do
    {
        if(turno == 1)
        {
            printf("Turno Jugador, puntos de vida restantes %d\n", jugador->puntosDeVida);
            turno = Turno_Jugador(jugador, NPC);
        }
        else
        {
            printf("Turno NPC, puntos de vida restantes %d\n", NPC->puntosDeVida);
            turno = Turno_NPC(jugador, NPC);
        }
    } while (jugador->puntosDeVida > 0 && NPC->puntosDeVida > 0);
}

int main() {
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

        if (Opcion <= 0 || Opcion >= 5) {
            printf("Por favor ingrese una opcion valida");
        } else {
            switch (Opcion) {
                case 1:
                    Crear_Carta(&cartas);
                    numeroCartas++;
                    break;

                case 2:
                    break;

                case 3:
                    Revolver_Cartas(&cartas, numeroCartas);
                    Juego(cartas);
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