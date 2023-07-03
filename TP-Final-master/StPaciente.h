#ifndef STPACIENTE_H_INCLUDED
#define STPACIENTE_H_INCLUDED
typedef struct
{
int idPaciente; /// campo único y autoincremental
char nombre[30];
char apellido[30];
int dni;
int movil;
int eliminado; /// 0 si está activo - 1 si está eliminado

} StPaciente;
StPaciente cargaPacientes ();
void imprimirUnPaciente(StPaciente paciente);
void cargarArchivoPacientes( char archivoPacientes[]);
void mostrarArchivoPacientes (char archivoPacientes[],StPaciente array[],int estado);
int pasaArreglo (StPaciente array[], FILE* Arc, int estado, int validos);
int menorLetras(StPaciente array[], int pos, int validos);
void ordenaAlfabticamente (StPaciente array[], int validos);
void muestraArreglo (StPaciente array[],int validos);
void modificaUnPaciente(int flag );
void modificarPacientes ();
void costoTotal(char archivo[], char Archivo[], int ID);
void estadoPaciente ();
void estadoPacienteLogico( int flagLog, int dni);
int repiteDNI (char archi[], StPaciente aux);
void menuPacientes();

void menuPacientes();
#endif // STPACIENTE_H_INCLUDED
