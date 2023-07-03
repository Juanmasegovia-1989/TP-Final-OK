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


    while (opc!=4)
    {
        printf("\n\t>>>>> MENU PRINCIPAL: <<<<<\n");
        printf( "\n\t   1. Menu de Pacientes.");
        printf( "\n\t   2. Menu de Practicas.");
        printf( "\n\t   3. Menu de Laboratorio." );
        printf( "\n\t   4. Salir." );
        printf( "\n\t   Introduzca opcion (1-4): ");
        fflush(stdin);
        scanf("%d", &opc);
        switch (opc)
        {

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
            ///printf("\n   Salir \n\n\n\n");
            ///abort();
            opc = 4;
            break;

        default:
            system("cls");
            printf("Ingrese una opcion valida \n");
            menuPrincipal();
            break;
        }

    }

}
