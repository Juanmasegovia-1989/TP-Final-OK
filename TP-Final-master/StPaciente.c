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

StPaciente cargaPacientes ()
{
    StPaciente paciente;

    printf ("\n\n\t\t>>>>> INGRESO NUEVO PACIENTE: <<<<<<\n");

    printf ("\n NOMBRE: \n");
    fflush (stdin);
    gets (paciente.nombre);
    printf ("\n APELLIDO: \n");
    fflush (stdin);
    gets (paciente.apellido);
    printf ("\n DNI:\n");
    fflush (stdin);
    scanf ("%d", &paciente.dni);
    printf ("\n Nro. CELULAR:\n");
    fflush (stdin);
    scanf ("%d", &paciente.movil);
    paciente.eliminado =0;

    return paciente;
}
void imprimirUnPaciente(StPaciente paciente)
{

    printf("\n\t>>>>> DATOS PACIENTE: <<<<<<\n");
    printf("\n      ID #: ...............%d",paciente.idPaciente);
    printf("\n    NOMBRE: ...............%s", paciente.nombre);
    printf("\n  APELLIDO: ...............%s", paciente.apellido);
    printf("\n       DNI: ...............%d", paciente.dni);
    printf("\n   Nro.CEL: ...............%d", paciente.movil);
    if(paciente.eliminado==0)
    {
        printf("\n EL PACIENTE ESTA ACTIVO ");
    }else{
    printf("\n EL PACIENTE ESTA INACTIVO");
    }
}
void cargarArchivoPacientes(char archivopacientes[])
{
    char opc =0;
    StPaciente paciente;
    FILE * Arc=fopen(archivopacientes, "ab");
    if(Arc!=NULL)
    {
    int contador= ultimoIdpac(archivopacientes);

        do
        {
            contador++;
            paciente =cargaPacientes();
            paciente.idPaciente=contador;
            fflush(stdin);
            fwrite(&paciente, sizeof(StPaciente), 1, Arc);
            printf("\n Ingrese ESC para salir o cualquier tecla para seguir cargando pacientes");
            opc =getche ();
        }while(opc != ESC);

        fclose(Arc);
    }
}
int ultimoIdpac (char archivopacientes[])
{
    int endId = 0;

    FILE* Arc = fopen(archivopacientes, "rb");

    if (Arc)
        {
        StPaciente ultimoPaciente;

        fseek(Arc, -1 * sizeof(StPaciente), SEEK_END);

        if (fread(&ultimoPaciente, sizeof(StPaciente), 1, Arc) > 0)
            {
            endId = ultimoPaciente.idPaciente;
            }

        fclose(Arc);
        }

    return endId;
}
void mostrarArchivoPacientes (char archivopacientes[])
{

FILE* Arc = fopen (archivopacientes, "rb");
StPaciente paciente;
   if (Arc!=NULL)
   {
       while (fread (&paciente, sizeof(StPaciente),1,Arc)>0)
       {
           printf("\n=========================================\n");
           imprimirUnPaciente(paciente);
       }
   }
   else
   {
       printf ("\n ERROR en archivo");
   }

   fclose (Arc);
}
void buscarxDni(char archivopacientes[], int dni)
{

FILE *arc=fopen(archivopacientes,"rb");
    StPaciente paciente;

    if (arc!=NULL){
            fread(&paciente,sizeof(StPaciente),1,arc);
       while ((!feof(arc))&&(paciente.dni!=dni)){
            fread(&paciente,sizeof(StPaciente),1,arc);
       }
       if ( dni ==paciente.dni){

            imprimirUnPaciente(paciente);


        puts("\n ----------------------------------\n");
}

       else
       {

         printf ("\n No se encuentra el dni en el archivo \n");
       }
    }
    fclose(arc);
}
void buscarApellidoNombre(char archivopacientes[])
{
    FILE *arc = fopen(archivopacientes,"rb");
    StPaciente paciente;
    char apellido[30];
    printf("Ingrese el apellido a buscar \n");
    fflush(stdin);
    gets(apellido);
    int flag =0;

    if (arc!=NULL){

       while (fread(&paciente,sizeof(StPaciente),1,arc)>0){


        if (strcmpi(paciente.apellido, apellido)==0){

            imprimirUnPaciente(paciente);
            flag =1;

        puts("\n ----------------------------------\n");
            }

       }
       if (flag == 0)
       {
           printf("El apellido no se encuentra en el archivo \n");
       }
       }
    fclose(arc);

}


void modificarxdni (char archi[], int dni)
{
    int flag = 0;
    StPaciente aux;
    int idaux;

    FILE * dat = fopen(archi, "r+b");
    if (dat != NULL)
    {
        while((!feof(dat))&& (flag == 0))
        {
            fread(&aux, sizeof(StPaciente), 1, dat);
            if(aux.dni == dni)
            {
                imprimirUnPaciente(aux);
                idaux= aux.idPaciente;
                aux = cargaPacientes();
                aux.idPaciente=idaux;
                fseek(dat, -1*sizeof(StPaciente), SEEK_CUR);
                fwrite(&aux, sizeof(StPaciente), 1, dat);
                flag = 1;
            }
        }fclose(dat);
        if (flag == 0)
        {
            printf("El dni no se encuentra en el archivo");
        }
    }
}

void modificarxapellido (char archi[], char nombre[], char apellido[])
{
    int flag = 0;
    StPaciente aux;
    int idaux;

    FILE * dat = fopen(archi, "r+b");
    if (dat != NULL)
    {
        while((!feof(dat))&& (flag == 0))
        {
            fread(&aux, sizeof(StPaciente), 1, dat);
            if((strcmpi(aux.apellido, apellido)==0)&&(strcmpi(aux.nombre, nombre)==0))
            {
                imprimirUnPaciente(aux);
                idaux = aux.idPaciente;
                aux = cargaPacientes();
                aux.idPaciente = idaux;
                fseek(dat, -1*sizeof(StPaciente), SEEK_CUR);
                fwrite(&aux, sizeof(StPaciente), 1, dat);
                flag = 1;
            }
        }fclose(dat);
        if(flag==0)
        {
            printf("El paciente buscado no se encuentra en el archivo");
        }
    }
}



void modificarPacientes ()
{
    int opc=0;
    char apellido[30];
    char nombre[30];
    int dni;

    do
    {
        printf(" \t \t MENU BUSQUEDA PARA MODIFICAR \n");
        printf("\t \t 1. Busqueda por APELLIDO y NOMBRE \n");
        printf("\t \t 2. Busqueda por DNI \n");
        printf("\t \t 3. Volver MENU ANTERIOR \n");
        fflush(stdin);
        scanf("%d", &opc);

        switch(opc)
        {
        case 1:
            system("cls");
            printf("Ingrese el nombre a buscar \n");
            fflush(stdin);
            gets(nombre);
            printf("Ingrese el apellido a buscar \n");
            fflush(stdin);
            gets(apellido);
            modificarxapellido(AR_Paciente, nombre, apellido);
            break;

        case 2:
            system("cls");
            printf("Ingrese el dni a buscar \n");
            scanf("%d", &dni);
            modificarxdni(AR_Paciente, dni);
            break;

        case 3:
            system("cls");
            menuPacientes();
            break;

        default:
            system("cls");
            printf("OPCION NO VALIDA");
            break;
        }
    }while (opc!=ESC);

}



void menuPacientes()
{
    int opc=0;


    while (opc!=ESC){

    printf("\t \t MENU PACIENTES \n");
    printf("\t \t 1. Listado de pacientes \n");
    printf("\t \t 2. Modificar pacientes \n");
    printf("\t \t 3. Agregar pacientes \n ");
    printf("\t \t 4. Baja de pacientes \n ");
    printf("\t \t 5. Buscar paciente por DNI \n ");
    printf("\t \t 6. Buscar paciente por apellido \n ");
    printf("\t \t 7. Volver al MENU ANTERIOR \n ");
    scanf("%d", &opc);

    switch(opc)
    {
        case 1: system("cls");
                mostrarArchivoPacientes(AR_Paciente);
                break;

        case 2: system("cls");
                modificarPacientes();
                break;

        case 3: system("cls");
                fflush(stdin);
                cargarArchivoPacientes(AR_Paciente);
                fflush(stdin);
                break;

        case 4: system("cls");
                fflush(stdin);
                ///funcion baja de paciente
                fflush(stdin);
                break;

        case 5: system("cls");
                int dni;
                printf("Ingrese el DNI que quiere buscar \n");
                scanf("%d", &dni);
                buscarxDni(AR_Paciente, dni);
                break;

        case 6: system("cls");
                buscarApellidoNombre(AR_Paciente);
                break;

        case 7: fflush(stdin);
                system("cls");
                menuPrincipal();
                fflush(stdin);
                system("cls");
                break;


        default: system("cls");
                printf("OPCION NO VALIDA");
                break;
    }
    }
}











