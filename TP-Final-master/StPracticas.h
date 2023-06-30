#ifndef STPRACTICAS_H_INCLUDED
#define STPRACTICAS_H_INCLUDED
typedef struct
{
int idPractica; /// campo único y autoincremental
char nombre[30];
int costo; /// valores enteros entre 1000 y 10000 como mínimos y máximos respectivamente
int baja; /// 0 si está activo - 1 si está eliminado
} stPracticas;

stPracticas cargaPractica ();
void cargaPracticas(char archi[]);
void mostrarPractica(stPracticas aux);
void mostrarPracticas(char archi[]);
int ultimoIdprac(char archi[]);
int modificarxid (char archi[]);
void modificarPractica (char archi[]);
int repiteNombre (char archi[], stPracticas aux);
void menuPracticas ();


#endif // STPRACTICAS_H_INCLUDED
#ifndef STPRACTICAS_H_INCLUDED
#define STPRACTICAS_H_INCLUDED
typedef struct
{
int idPractica; /// campo único y autoincremental
char nombre[30];
int costo; /// valores enteros entre 1000 y 10000 como mínimos y máximos respectivamente
int baja; /// 0 si está activo - 1 si está eliminado
} stPracticas;

stPracticas cargaPractica ();
void cargaPracticas(char archi[]);
void mostrarPractica(stPracticas aux);
void mostrarPracticas(char archi[]);
int ultimoId(char archi[]);
int modificarxid (char archi[]);
void modificarPractica (char archi[]);
int repiteNombre (char archi[], stPracticas aux);
void menuPracticas ();


#endif // STPRACTICAS_H_INCLUDED
