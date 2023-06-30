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

int main()
{
    menuPrincipal();
    printf("\n Gracias por utilizar nuestro sistema\n");
    return 0;
}
