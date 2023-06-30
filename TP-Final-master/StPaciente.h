#ifndef STPACIENTE_H_INCLUDED
#define STPACIENTE_H_INCLUDED
typedef struct
{
int idPaciente; /// campo �nico y autoincremental
char nombre[30];
char apellido[30];
int dni;
int movil;
int eliminado; /// 0 si est� activo - 1 si est� eliminado

} StPaciente;
StPaciente cargaPacientes ();
void imprimirUnPaciente(StPaciente paciente);
void cargarArchivoPacientes( char archivoPacientes[]);
void mostrarArchivoPacientes (char archivoPacientes[]);
void modificaUnPaciente(int flag );
void modificarPacientes ();
void menuPacientes();

void menuPacientes();
#endif // STPACIENTE_H_INCLUDED
