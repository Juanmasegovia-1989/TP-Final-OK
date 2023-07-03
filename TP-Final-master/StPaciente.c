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
#define DIM_ARRAY 200

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
    paciente.eliminado =1;

    return paciente;
}
void imprimirUnPaciente(StPaciente paciente)
{

    printf("\n\t     >>>>> DATOS PACIENTE: <<<<<< \n");
    printf("\n\t      ID #: ...............%d",paciente.idPaciente);
    printf("\n\t   NOMBRE: ................%s", paciente.nombre);
    printf("\n\t  APELLIDO: ...............%s", paciente.apellido);
    printf("\n\t       DNI: ...............%d", paciente.dni);
    printf("\n\t   Nro.CEL: ...............%d \n\n", paciente.movil);
    costoTotal(ARCHIVOLABORATORIOS, ARCHIVOPRACTICAS, paciente.idPaciente);
    if(paciente.eliminado==0)
    {
        printf("\n\t EL PACIENTE ESTA ACTIVO \n\n\n ");
    }else{
    printf("\n\t EL PACIENTE ESTA INACTIVO \n\n\n");
    }

}
void cargarArchivoPacientes(char archivopacientes[])  ///Opcion N°3
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
            fflush(stdin);
            if (repiteDNI(AR_Paciente, paciente)==1) ///chequea que no exista el dni del paciente en el archivo
            {
                printf("El DNI ingresado ya se encuentra en el sistema\n");
                printf("Ingrese de nuevo los datos \n ");
                paciente = cargaPacientes();
                fflush(stdin);
            }
            fflush(stdin);
            paciente.idPaciente=contador;
            fwrite(&paciente, sizeof(StPaciente), 1, Arc);
            printf("\n Ingrese ESC para salir o cualquier tecla para seguir cargando pacientes");
            opc =getche ();
        }while(opc != ESC);

        fclose(Arc);
    }
}
void costoTotal(char archivo[], char Archivo[], int ID) ///funcion interna Opcion N°1
{
    FILE * archi = fopen(ARCHIVOLABORATORIOS, "rb");
    FILE * ptr = fopen(ARCHIVOPRACTICAS, "rb");

    int i = 0;
    int acumuladorCosto = 0;
    StLaboratorios auxlab;
    stPracticas auxprac;

    if(ptr && archi)
    {
        while(fread(&auxlab, sizeof(StLaboratorios), 1, archi) > 0)
        {
            if(ID == auxlab.idPaciente)
            {
                while(fread(&auxprac, sizeof(stPracticas), 1, ptr) > 0)
                {
                    if(auxprac.idPractica == auxlab.PracticaRealizada)
                    {
                    acumuladorCosto = acumuladorCosto + auxprac.costo ;
                    i++;
                    }
                }
                rewind (ptr);
            }
        }
        printf("\n\t  El costo total es %i, en %i laboratorios\n", acumuladorCosto, i);
        fclose(archi);
        fclose(ptr);
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
void muestraPacientes (char archivopacientes[])
{
    int opc=0;

    do
    {
        printf(" \t \t MENU MOSTRAR PACIENTES \n");
        printf("\t \t 1. Pacientes Activos \n");
        printf("\t \t 2. Pacientes Inactivos\n");
        printf("\t \t 3. Mostrar todos \n");  ///No discrimina estado (alta/baja)
        printf("\t \t 4. Volver al menu anterior \n");
        fflush(stdin);
        scanf("%d", &opc);

        switch(opc)
        {
        case 1:
            system("cls");
            StPaciente arrayalta [DIM_ARRAY];
            mostrarArchivoPacientes (archivopacientes,arrayalta, 0);

            break;

        case 2:
            system("cls");
            StPaciente arraybaja [DIM_ARRAY];
            mostrarArchivoPacientes (archivopacientes,arraybaja, 1);
            break;

         case 3:
            system("cls");
            StPaciente arraytodos [DIM_ARRAY];
            mostrarArchivoPacientes (archivopacientes,arraytodos, 2);
            break;

        case 4:
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
void mostrarArchivoPacientes (char archivopacientes[], StPaciente array[], int estado)   ///Opcion N°1 para ordenarlo alfabeticamente lo pasamos a un arreglo
{
int validos=ultimoIdpac(archivopacientes);
FILE* Arc = fopen (archivopacientes, "rb");
   if (Arc!=NULL)
   {
        printf("\n=============================================================\n");
        ///imprimirUnPaciente(paciente);
        validos=pasaArreglo(array,Arc,estado,validos);
        ordenaAlfabticamente(array,validos);
        muestraArreglo(array, validos);
        printf("\n=============================================================\n");
   }
   else
   {
       printf ("\n ERROR en archivo");
   }

   fclose (Arc);
    system("pause");
    system("cls");

   }
int pasaArreglo (StPaciente array[], FILE* Arc, int estado , int validos)
{
    StPaciente orden;
    int i=0;

    if (Arc!= NULL)
    {
        while ( fread(&orden, sizeof(StPaciente),1,Arc)>0)
        {
            if ( estado==0)
            {
                if (orden.eliminado==0) ///paciente activo
                {
                    array[i]=orden;
                    i++;
                }
                else
                {
                    validos --;
                }
            }
            if ( estado== 1)
            {
                if (orden.eliminado==1) ///paciente eliminado
                {
                    array[i]=orden;
                    i++;
                }
                else
                {
                    validos --;
                }
            }
            if(estado==2)
            {
                array[i]=orden;
                i++;
            }
        }
    }
    else
    {
        printf(" \n\t ERROR \n");
    }
    return validos;
}
int menorLetras(StPaciente array[], int pos, int validos)
{
    StPaciente menor = array[pos];
    int i = pos +1;
    int posmenor = pos;
        while (i<validos)
    {
        if (strcmpi(menor.apellido,array[i].apellido)==1)
        {
            menor = array[i];
            posmenor = i;
        }
        i++;
    }
    return posmenor;
}
void ordenaAlfabticamente (StPaciente array[], int validos)
{
    int posmenor;
    StPaciente aux;
    int i = 0;

    while (i<validos-1)
    {
        posmenor = menorLetras(array,i,validos);
        aux = array[posmenor];
        array[posmenor]=array[i];
        array[i]= aux;
        i++;
    }
}
void muestraArreglo (StPaciente array[],int validos)
{
    int i=0;

   while(i<validos)
   {
       imprimirUnPaciente(array[i]);
       i++;
   }
}
void buscarxDni(char archivopacientes[], int dni)  ///Opcion N°5
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

         printf ("\n\t No se encuentra el dni en el archivo \n\n");
       }
    }
    fclose(arc);
}
void buscarApellidoNombre(char archivopacientes[])  ///Opcion N°6
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
void modificarxdni (char archi[], int dni)    ///Opcion N°2.2
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
void modificarxapellido (char archi[], char nombre[], char apellido[])   ///Opcion N°2.1
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
void modificarPacientes ()   ///Opcion N°2
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
void estadoPaciente ()  ///Opcion N°4
{
    int opc=0;
    int dni=0;
    int flaglogico=0;

    do
    {
        printf(" \t \t MENU MODIFICACION ESTADO DE PACIENTE \n\n\n");
        printf("\t \t 1. Baja de Paciente \n");
        printf("\t \t 2. Reactivacion de Paciente \n");
        printf("\t \t 3. Volver MENU ANTERIOR \n");
        fflush(stdin);
        scanf("%d", &opc);

        switch(opc)
        {
        case 1:
            system("cls");
            printf("\n Ingrese el dni del Paciente que desea dar de BAJA \n");
            fflush(stdin);
            scanf("%d",&dni);
            flaglogico=0;
            estadoPacienteLogico ( flaglogico, dni );
            break;

        case 2:
            system("cls");
            printf("\n Ingrese el dni del Paciente que desea REACTIVAR \n");
            fflush(stdin);
            scanf("%d", &dni);
            flaglogico=1;
            estadoPacienteLogico ( flaglogico, dni );
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
void estadoPacienteLogico( int flagLog, int dni) ///Opcion N°4.1 y 4.2
{
    FILE *arc=fopen(AR_Paciente,"r+b");
    StPaciente paciente;
    if (arc!=NULL)
    {
        if (flagLog == 1) /// eliminacion logica del paciente
        {
            while ((!feof(arc))&&(paciente.dni!=dni))
            {
                fread(&paciente,sizeof(StPaciente),1,arc);
                if ( dni == paciente.dni && paciente.eliminado==1)
                {
                    printf("\n\t Su cambio de efectuo correctamente \n");
                    paciente.eliminado=0;
                    fseek(arc,-1*sizeof(StPaciente),SEEK_CUR);
                    fwrite(&paciente, sizeof(StPaciente),1,arc);
                    imprimirUnPaciente(paciente);
                    puts("\n\t ------------------------------------ \n");
                    system("pause");
                    system("cls");
                }
            }
        }

        else  /// Cambio de valor asignado al Flag para que sea TRUE
        {
            while ((!feof(arc))&&(paciente.dni!=dni))
            {
                fread(&paciente,sizeof(StPaciente),1,arc);
                if ( dni == paciente.dni && paciente.eliminado==0)
                {
                    printf("\n\t Su cambio de efectuo correctamente \n");
                    paciente.eliminado=1;
                    fseek(arc,-1*sizeof(StPaciente),SEEK_CUR);
                    fwrite(&paciente, sizeof(StPaciente),1,arc);
                    imprimirUnPaciente(paciente);
                    puts("\n\t ------------------------------------ \n");
                    system("pause");
                    system("cls");
                }
            }
        }

    }
    else
    {
        printf ("\n\t No se encuentra el dni en el archivo \n");
        system("pause");
        system("cls");
    }
    fclose(arc);
}
void menuPacientes()
{
    int opc=0;


    while (opc!=ESC){

    printf("\n\t>>>>> MENU PACIENTES: <<<<<\n");
    printf("\n \t 1. Listado de pacientes ");
    printf("\n \t 2. Modificar pacientes ");
    printf("\n \t 3. Agregar pacientes  ");
    printf("\n \t 4. Estado de pacientes  ");
    printf("\n \t 5. Buscar paciente por DNI ");
    printf("\n \t 6. Buscar paciente por apellido ");
    printf("\n \t 7. Volver al MENU ANTERIOR \n ");
    scanf("%d", &opc);

    switch(opc)
    {
        case 1: system("cls");
                muestraPacientes(AR_Paciente);
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
                estadoPaciente();
                fflush(stdin);
                break;

        case 5: system("cls");
                int dni;
                printf("\n\t Ingrese el DNI que quiere buscar \n");
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
int repiteDNI (char archi[], StPaciente aux) ///retorna 1 si encuentra el nombre en el archivo, sirve para validacion
{
    FILE * dat = fopen(archi, "rb");
    rewind(dat);
    StPaciente aux1;
    int flag = 0;

    if((dat!=NULL)){

    while (fread(&aux1, sizeof(StPaciente), 1, dat)>0)
    {
        if (aux1.dni==aux.dni)
        {
            flag = 1;
        }
    }
    fclose(dat);
    return flag;
    }
}

































