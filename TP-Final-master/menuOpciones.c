#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "StPaciente.h"
#include "StPracticas.h"
#include "StLaboratorio.h"
#include "menuOpciones.h"
#define ARCHIVO "archivo.bin"
#define AR_Paciente "pacientes.dat"
#define DIM_ARRAY 30
#define ESC 27
#include <string.h>
#define ARCHIVOPRACTICAS "practicas.dat"
#define ARCHIVOLABORATORIOS "laboratorios.dat"

void menuPrincipal ()
{
    int opc=0;

    while (opc!=ESC)
    {
        printf("\n\t>>>>> MENU PRINCIPAL: <<<<<<\n");
        printf( "\n   1. Menu de Pacientes.");
        printf( "\n   2. Menu de Practicas.");
        printf( "\n   3. Menu de Laboratorio." );
        printf( "\n   4. Salir." );
        printf( "\n\n   Introduzca opcion (1-4): ");
        fflush(stdin);
        scanf("%d", &opc);
        switch (opc)
        {
        default:
            system("cls");
            printf("Ingrese una opcion valida \n");
            menuPrincipal();
            break;
        case 1:
            system("cls");
            menuPacientes();
            break;

        case 2:
            system("cls");
            menuPracticas();
            break;

        case 3:
            system("cls");
            menuLaboratorios();
            break;

        case 4:
            printf("\n   Salir \n\n\n\n");
            opc = ESC;
            break;
        }

    }

}
