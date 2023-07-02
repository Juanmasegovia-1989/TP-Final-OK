#ifndef STLABORATORIO_H_INCLUDED
#define STLABORATORIO_H_INCLUDED

typedef struct
{
int idLab; /// campo �nico y autoincremental
int idPaciente;
int anio;
int mes; /// 1 a 12
int dia; /// 1 a � dependiendo del mes
int PracticaRealizada; /// con c�digos entre 1 y 10.
int baja; /// 0 si est� activo - 1 si est� eliminado
} StLaboratorios;

StLaboratorios cargaLaboratorio();
void cargaLaboratorios(char archi[]);
int ultimoId(char archi[]);
void mostrarLaboratorio(StLaboratorios aux);
void mostrarLaboratorios(char archi []);
void modificarLaboratorios (char archi[]);
void bajaLaboratorio (char archi[]);
void menuLaboratorios ();









#endif // STLABORATORIO_H_INCLUDED
