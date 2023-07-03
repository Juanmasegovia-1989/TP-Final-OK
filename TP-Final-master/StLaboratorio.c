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



StLaboratorios cargaLaboratorio()
{
   StLaboratorios lab;

    printf("Ingrese el ID del paciente \n");
    scanf("%d", &lab.idPaciente);
    while(validarPaciente(lab.idPaciente)==1)
    {
        printf("Ingrese un ID paciente valido: ");
        scanf("%d", &lab.idPaciente);
    }
    printf("Ingrese el anio \n");
    scanf("%d", &lab.anio);
    while(lab.anio>2023)
    {
        printf("\n Ingrese un año valido: ");
        scanf("%d", &lab.anio);
    }
    printf("Ingrese el mes (en numeros) \n");
    scanf("%d", &lab.mes);
    while (lab.mes>12)
    {
        printf("\n Ingrese un mes valido: ");
        scanf("%d", &lab.mes);
    }
    printf("Ingrese el dia \n");
    scanf("%d", &lab.dia);
    while (lab.dia>31)
    {
        printf("\n Ingrese un dia valido: ");
        scanf("%d", &lab.dia);
    }
    printf("Ingrese el ID de la practica realizada \n");
    scanf("%d", &lab.PracticaRealizada);
    while(validarPractica(lab.PracticaRealizada)==1)
    {
        printf("Ingrese un ID practica valido: ");
        scanf("%d", &lab.PracticaRealizada);
    }
    lab.baja = 0;

    return lab;
}
void cargaLaboratorios(char archi[])
{
    StLaboratorios aux;
    FILE * dat = fopen(archi, "ab");

    if(archi != NULL );
    {
        int contador = ultimoId(archi);
        do
        {
            contador++;
            system("cls");
            aux = cargaLaboratorio();
            fflush(stdin);
            aux.idLab = contador;
            fwrite(&aux, sizeof(StLaboratorios), 1, dat);
            printf("\n Ingrese ESC para salir o cualquier tecla para seguir cargando \n");

        }
        while(getch()!= 27);
        fclose(dat);
    }
}
int ultimoId(char archi[]) ///retorna el ult id del archivo labs, para cargar a partir de ese
{
    int ultId=0;

    FILE * dat = fopen(archi, "rb");

    if(dat!=NULL)
    {
        StLaboratorios aux;
        fseek(dat, -1*sizeof(StLaboratorios), SEEK_END);
        if(fread(&aux, sizeof(StLaboratorios),1,dat)>0)
        {
            ultId= aux.idLab;
        }fclose(dat);
    }
    return ultId;
}
void mostrarLaboratorio(StLaboratorios aux)
{
    printf("\n\t ID laboratorio:.%d ", aux.idLab);
    printf("\n\t ID paciente:....%d", aux.idPaciente);
    mostrarNombre(aux.idPaciente);
    printf("\n\t Anio:...........%d", aux.anio);
    printf("\n\t Mes:............%d", aux.mes);
    printf("\n\t Dia:............%d", aux.dia);
    printf("\n\t ID de la practica realizada: %d", aux.PracticaRealizada);
    imprimirPractica(aux.PracticaRealizada);

    if(aux.baja!=0)
    {
        printf("\n\t El laboratorio esta eliminado \n");
    }else{
    printf("\n\t El laboratorio esta activo \n");
    }
}
void mostrarLaboratorios(char archi [])
{
    FILE * dat = fopen(archi, "rb");
    StLaboratorios a;
    system("cls");

    if(dat!=NULL)
    {
        while(fread(&a, sizeof(StLaboratorios), 1, dat)>0)
        {
            mostrarLaboratorio(a);
            printf("\n -----------------------------------------------\n ");
        }fclose(dat);
    }
}
void modificarLaboratorios (char archi[])
{
        int id = modificarxid(archi);
    StLaboratorios aux;
    int flag = 0;
    int idaux; ///sirve para guardar el id y no perderlo al modificar el lab

    FILE * dat = fopen(archi, "r+b");
    if (dat != NULL)
    {
        while((!feof(dat))&& (flag == 0))
        {
            fread(&aux, sizeof(StLaboratorios), 1, dat);
            if(aux.idLab == id)
            {
                idaux = aux.idLab;
                mostrarLaboratorio(aux);
                aux = cargaLaboratorio();
                aux.idLab = idaux;
                fseek(dat, -1*sizeof(StLaboratorios), SEEK_CUR);
                fwrite(&aux, sizeof(StLaboratorios), 1, dat);
                flag = 1;
            }
        }
        fclose(dat);
        if (flag==0)
        {
            printf("No se encuentra el id en el archivo \n");
        }
    }fclose(dat);
}
void bajaLaboratorio (char archi[])
{
    StLaboratorios baja;
    int id=modificarxid(archi);
    FILE *dat = fopen(archi, "r+b");
    if (dat!=NULL)
    {
        while( (fread(&baja, sizeof(StLaboratorios),1,dat)>0) && baja.baja!=1)
        {
            if (baja.idLab=id)
            {
                baja.baja=1;
                fseek(dat,-1*sizeof(StLaboratorios),SEEK_CUR);
                fwrite(&baja, sizeof(StLaboratorios),1,dat);
                mostrarLaboratorio(baja);
                puts("\n\t ------------------------------------ \n");
                system("pause");
                system("cls");
            }
        }
    }
    else
    {
        printf("\n\t El ID ingresado no existe \n");
        system("pause");
        system("cls");
    }
    fclose(dat);
}
void menuLaboratorios ()
{
    int opc;

    do{
        printf("\t \t MENU LABORATORIOS \n");
        printf("\t \t 1. Listado de laboratorios \n");
        printf("\t \t 2. Modificar laboratorios \n");
        printf("\t \t 3. Agregar laboratorios \n ");
        printf("\t \t 4. Baja de laboratorios \n ");
        printf("\t \t 5. Volver al menu principal \n ");
        scanf("%d", &opc);

        switch(opc)
        {
        case 1: system("cls");
            mostrarLaboratorios(ARCHIVOLABORATORIOS);
            break;

        case 2: system("cls");
            modificarLaboratorios(ARCHIVOLABORATORIOS);
            break;

        case 3: system("cls");
            fflush(stdin);
            cargaLaboratorios(ARCHIVOLABORATORIOS);
            fflush(stdin);
            break;

        case 4: system("cls");
            fflush(stdin);
            bajaLaboratorio (ARCHIVOLABORATORIOS);
            fflush(stdin);
            break;

        case 5:
            system("cls");
            menuPrincipal();
            break;

        default:
            system("cls");
            printf("OPCION NO VALIDA");
            break;
        }
    }while (opc!=ESC);
}


void mostrarNombre (int idp)
{
    FILE * arcpaciente = fopen(AR_Paciente, "rb");
    StPaciente auxpac;

        if((arcpaciente!=NULL))
        {
             while(fread(&auxpac, sizeof(StPaciente),1, arcpaciente)>0)
                if(idp == auxpac.idPaciente)
             {
                 printf(" (%s %s)", auxpac.nombre, auxpac.apellido);
             }
        }fclose(arcpaciente);
}
void imprimirPractica (int idp)
{
    FILE * arcpractica = fopen(ARCHIVOPRACTICAS, "rb");
    stPracticas auxprac;

        if((arcpractica!=NULL))
        {
             while(fread(&auxprac, sizeof(stPracticas),1, arcpractica)>0)
                if(idp == auxprac.idPractica)
             {
                 printf(" (%s)", auxprac.nombre);
             }
        }fclose(arcpractica);
}
int validarPaciente (int idpac)
{
    FILE*dat = fopen(AR_Paciente, "rb");
    StPaciente aux;
    int ultid;
    int flag=0;

    if((dat!=NULL))
    {
        while(fread(&aux, sizeof(StPaciente),1, dat)>0)
        {
            ultid = ultimoIdpac(AR_Paciente);
            if(ultid<idpac)
            {
                flag=1;
            }
        }
    }
    fclose(dat);
    return flag;
}
int validarPractica (int idprac)
{
    FILE*dat = fopen(ARCHIVOPRACTICAS, "rb");
    stPracticas aux;
    int ultid;
    int flag=0;

    if((dat!=NULL))
    {
        while(fread(&aux, sizeof(stPracticas),1, dat)>0)
        {
            ultid = ultimoIdprac(ARCHIVOPRACTICAS);
            if(ultid<idprac)
            {
                flag=1;
            }
        }
    }
    fclose(dat);
    return flag;
}










