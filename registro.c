#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIAS 5
#define BLOQUES 5

// =======================
// ESTRUCTURAS
// =======================
typedef struct Docente {
    char nombre[50];
    struct Docente *sig;
} Docente;

typedef struct Materia {
    char nombre[50];
    struct Materia *sig;
} Materia;

typedef struct Aula {
    char nombre[50];
    int numero;
    int capacidad;
    struct Aula *sig;
} Aula;

typedef struct Horario {
    char nombreMateria[50];
    char nombreDocente[50];
    char nombreAula[50];
    int dia;
    int bloque;
    struct Horario *sig;
} Horario;

// =======================
// CABEZAS DE LISTAS
// =======================
Docente *inicioDocentes = NULL;
Materia *inicioMaterias = NULL;
Aula *inicioAulas = NULL;
Horario *inicioHorarios = NULL;

// =======================
// FUNCIONES DE REGISTRO
// =======================
void insertarDocente(char nombre[]) {
    Docente *nuevo = (Docente*)malloc(sizeof(Docente));
    strcpy(nuevo->nombre, nombre);
    if(!inicioDocentes) {
        inicioDocentes = nuevo;
        nuevo->sig = inicioDocentes;
    } else {
        Docente *temp = inicioDocentes;
        while(temp->sig != inicioDocentes) temp = temp->sig;
        temp->sig = nuevo;
        nuevo->sig = inicioDocentes;
    }
    printf("Docente registrado: %s\n", nombre);
}

void insertarMateria(char nombre[]) {
    Materia *nuevo = (Materia*)malloc(sizeof(Materia));
    strcpy(nuevo->nombre, nombre);
    if(!inicioMaterias) {
        inicioMaterias = nuevo;
        nuevo->sig = inicioMaterias;
    } else {
        Materia *temp = inicioMaterias;
        while(temp->sig != inicioMaterias) temp = temp->sig;
        temp->sig = nuevo;
        nuevo->sig = inicioMaterias;
    }
    printf("Materia registrada: %s\n", nombre);
}

void insertarAula(char nombre[], int numero, int capacidad) {
    Aula *nuevo = (Aula*)malloc(sizeof(Aula));
    strcpy(nuevo->nombre, nombre);
    nuevo->numero = numero;
    nuevo->capacidad = capacidad;
    if(!inicioAulas) {
        inicioAulas = nuevo;
        nuevo->sig = inicioAulas;
    } else {
        Aula *temp = inicioAulas;
        while(temp->sig != inicioAulas) temp = temp->sig;
        temp->sig = nuevo;
        nuevo->sig = inicioAulas;
    }
    printf("Aula registrada: %s (N %d, Capacidad %d)\n", nombre, numero, capacidad);
}

// =======================
// MOSTRAR LISTAS ENUMERADAS
// =======================
int mostrarDocentesEnumerados() {
    if(!inicioDocentes) { printf("No hay docentes.\n"); return -1; }
    Docente *temp = inicioDocentes;
    int i = 1;
    do {
        printf("%d. %s\n", i, temp->nombre);
        temp = temp->sig;
        i++;
    } while(temp != inicioDocentes);
    return i-1;
}

int mostrarMateriasEnumeradas() {
    if(!inicioMaterias) { printf("No hay materias.\n"); return -1; }
    Materia *temp = inicioMaterias;
    int i = 1;
    do {
        printf("%d. %s\n", i, temp->nombre);
        temp = temp->sig;
        i++;
    } while(temp != inicioMaterias);
    return i-1;
}

int mostrarAulasEnumeradas() {
    if(!inicioAulas) { printf("No hay aulas.\n"); return -1; }
    Aula *temp = inicioAulas;
    int i = 1;
    do {
        printf("%d. %s (N %d, Capacidad: %d)\n", i, temp->nombre, temp->numero, temp->capacidad);
        temp = temp->sig;
        i++;
    } while(temp != inicioAulas);
    return i-1;
}

// =======================
// OBTENER POR NUMERO
// =======================
Docente* obtenerDocentePorNumero(int num) {
    Docente *temp = inicioDocentes;
    int i = 1;
    while(i < num && temp) { temp = temp->sig; i++; }
    return temp;
}

Materia* obtenerMateriaPorNumero(int num) {
    Materia *temp = inicioMaterias;
    int i = 1;
    while(i < num && temp) { temp = temp->sig; i++; }
    return temp;
}

Aula* obtenerAulaPorNumero(int num) {
    Aula *temp = inicioAulas;
    int i = 1;
    while(i < num && temp) { temp = temp->sig; i++; }
    return temp;
}

// =======================
// VALIDACION CONFLICTOS
// =======================
int estaDisponible(char nombreDocente[], char nombreAula[], int dia, int bloque) {
    if(!inicioHorarios) return 1;
    Horario *temp = inicioHorarios;
    do {
        if(temp->dia == dia && temp->bloque == bloque) {
            if(strcmp(temp->nombreDocente, nombreDocente) == 0 || strcmp(temp->nombreAula, nombreAula) == 0)
                return 0;
        }
        temp = temp->sig;
    } while(temp != inicioHorarios);
    return 1;
}

// =======================
// ASIGNAR HORARIO
// =======================
void asignarHorario() {
    if(!inicioDocentes || !inicioMaterias || !inicioAulas) {
        printf("Debe registrar docentes, materias y aulas antes de asignar horario.\n");
        return;
    }

    int dia, bloque;
    int opcion;
    Docente *doc;
    Materia *mat;
    Aula *aul;

    printf("\nSeleccione docente:\n");
    mostrarDocentesEnumerados();
    printf("Ingrese numero de docente: "); scanf("%d",&opcion);
    doc = obtenerDocentePorNumero(opcion);

    printf("\nSeleccione materia:\n");
    mostrarMateriasEnumeradas();
    printf("Ingrese numero de materia: "); scanf("%d",&opcion);
    mat = obtenerMateriaPorNumero(opcion);

    printf("\nSeleccione aula:\n");
    mostrarAulasEnumeradas();
    printf("Ingrese numero de aula: "); scanf("%d",&opcion);
    aul = obtenerAulaPorNumero(opcion);

    printf("Ingrese dia (0=Lunes,...,4=Viernes): "); scanf("%d",&dia);
    printf("Ingrese bloque (0=7-9,...,4=15-17): "); scanf("%d",&bloque);

    if(!estaDisponible(doc->nombre, aul->nombre, dia, bloque)) {
        printf("Conflicto de horario. No se puede asignar.\n");
        return;
    }

    Horario *nuevo = (Horario*)malloc(sizeof(Horario));
    strcpy(nuevo->nombreDocente, doc->nombre);
    strcpy(nuevo->nombreMateria, mat->nombre);
    strcpy(nuevo->nombreAula, aul->nombre);
    nuevo->dia = dia;
    nuevo->bloque = bloque;

    if(!inicioHorarios) {
        inicioHorarios = nuevo;
        nuevo->sig = inicioHorarios;
    } else {
        Horario *temp = inicioHorarios;
        while(temp->sig != inicioHorarios) temp = temp->sig;
        temp->sig = nuevo;
        nuevo->sig = inicioHorarios;
    }

    printf("Horario asignado correctamente.\n");
}

// =======================
// MOSTRAR HORARIO COMPLETO (LISTADO)
// =======================
void mostrarHorarioCompleto() {
    char *dias[DIAS] = {"Lunes","Martes","Miercoles","Jueves","Viernes"};
    char *bloques[BLOQUES] = {"7-9","9-11","11-13","13-15","15-17"};

    printf("\n%-20s %-20s %-20s %-10s %-10s\n", "Docente", "Materia", "Aula", "Dia", "Bloque");
    printf("-----------------------------------------------------------------------------\n");

    if(!inicioHorarios) { printf("No hay horarios asignados.\n"); return; }

    Horario *temp = inicioHorarios;
    do {
        printf("%-20.20s %-20.20s %-20.20s %-10s %-10s\n",
               temp->nombreDocente,
               temp->nombreMateria,
               temp->nombreAula,
               dias[temp->dia],
               bloques[temp->bloque]);
        temp = temp->sig;
    } while(temp != inicioHorarios);
}

// =======================
// CONSULTA POR DOCENTE, MATERIA O AULA
// =======================
void consultaHorario() {
    int opcion;
    char nombre[50];
    char *dias[DIAS] = {"Lunes","Martes","Miercoles","Jueves","Viernes"};
    char *bloques[BLOQUES] = {"7-9","9-11","11-13","13-15","15-17"};

    printf("\nConsulta horario por:\n");
    printf("1. Docente\n");
    printf("2. Materia\n");
    printf("3. Aula\n");
    printf("Seleccione opcion: ");
    scanf("%d", &opcion); getchar();

    printf("Ingrese nombre: ");
    fgets(nombre, 50, stdin);
    nombre[strcspn(nombre, "\n")] = 0;

    printf("\n%-20s %-20s %-20s %-10s %-10s\n", "Docente", "Materia", "Aula", "Dia", "Bloque");
    printf("-----------------------------------------------------------------------------\n");

    int encontrado = 0;
    if(inicioHorarios) {
        Horario *temp = inicioHorarios;
        do {
            int mostrar = 0;
            if(opcion == 1 && strcmp(temp->nombreDocente, nombre) == 0) mostrar = 1;
            if(opcion == 2 && strcmp(temp->nombreMateria, nombre) == 0) mostrar = 1;
            if(opcion == 3 && strcmp(temp->nombreAula, nombre) == 0) mostrar = 1;

            if(mostrar) {
                printf("%-20.20s %-20.20s %-20.20s %-10s %-10s\n",
                       temp->nombreDocente,
                       temp->nombreMateria,
                       temp->nombreAula,
                       dias[temp->dia],
                       bloques[temp->bloque]);
                encontrado = 1;
            }
            temp = temp->sig;
        } while(temp != inicioHorarios);
    }

    if(!encontrado) printf("No se encontraron registros.\n");
}

// =======================
// FUNCIONES DE ELIMINACION
// =======================
void eliminarDocente() {
    if(!inicioDocentes) { printf("No hay docentes.\n"); return; }
    printf("\nDocentes registrados:\n");
    mostrarDocentesEnumerados();
    int opc; printf("Ingrese el numero del docente a eliminar: "); scanf("%d",&opc);
    Docente *temp = inicioDocentes, *prev = NULL;
    int i = 1;
    do {
        if(i == opc) {
            if(temp==inicioDocentes && temp->sig==inicioDocentes) inicioDocentes=NULL;
            else {
                if(temp==inicioDocentes) inicioDocentes=inicioDocentes->sig;
                if(prev) prev->sig = temp->sig;
                else {
                    Docente *last = inicioDocentes;
                    while(last->sig != inicioDocentes) last=last->sig;
                    last->sig = temp->sig;
                }
            }
            free(temp);
            printf("Docente eliminado.\n");
            return;
        }
        prev=temp; temp=temp->sig; i++;
    } while(temp != inicioDocentes);
}

void eliminarMateria() {
    if(!inicioMaterias) { printf("No hay materias.\n"); return; }
    printf("\nMaterias registradas:\n");
    mostrarMateriasEnumeradas();
    int opc; printf("Ingrese el numero de la materia a eliminar: "); scanf("%d",&opc);
    Materia *temp = inicioMaterias, *prev = NULL;
    int i=1;
    do {
        if(i==opc){
            if(temp==inicioMaterias && temp->sig==inicioMaterias) inicioMaterias=NULL;
            else {
                if(temp==inicioMaterias) inicioMaterias=inicioMaterias->sig;
                if(prev) prev->sig=temp->sig;
                else {
                    Materia *last=inicioMaterias;
                    while(last->sig!=inicioMaterias) last=last->sig;
                    last->sig=temp->sig;
                }
            }
            free(temp);
            printf("Materia eliminada.\n");
            return;
        }
        prev=temp; temp=temp->sig; i++;
    } while(temp!=inicioMaterias);
}

void eliminarAula() {
    if(!inicioAulas) { printf("No hay aulas.\n"); return; }
    printf("\nAulas registradas:\n");
    mostrarAulasEnumeradas();
    int opc; printf("Ingrese el numero del aula a eliminar: "); scanf("%d",&opc);
    Aula *temp = inicioAulas, *prev=NULL;
    int i=1;
    do {
        if(i==opc){
            if(temp==inicioAulas && temp->sig==inicioAulas) inicioAulas=NULL;
            else {
                if(temp==inicioAulas) inicioAulas=inicioAulas->sig;
                if(prev) prev->sig=temp->sig;
                else {
                    Aula *last=inicioAulas;
                    while(last->sig!=inicioAulas) last=last->sig;
                    last->sig=temp->sig;
                }
            }
            free(temp);
            printf("Aula eliminada.\n");
            return;
        }
        prev=temp; temp=temp->sig; i++;
    } while(temp!=inicioAulas);
}

// =======================
// EXPORTAR HORARIO SEMANAL
// =======================
void exportarHorarioSemanal() {
    FILE *f = fopen("horario_semanal.txt","w");
    if(!f){ printf("Error al crear archivo.\n"); return; }

    char *dias[DIAS] = {"Lunes","Martes","Miercoles","Jueves","Viernes"};
    char *bloques[BLOQUES] = {"7-9","9-11","11-13","13-15","15-17"};

    fprintf(f, "%-20s %-20s %-20s %-10s %-10s\n", "Docente", "Materia", "Aula", "Dia", "Bloque");
    fprintf(f, "-----------------------------------------------------------------------------\n");

    if(inicioHorarios){
        Horario *temp = inicioHorarios;
        do {
            fprintf(f, "%-20.20s %-20.20s %-20.20s %-10s %-10s\n",
                    temp->nombreDocente,
                    temp->nombreMateria,
                    temp->nombreAula,
                    dias[temp->dia],
                    bloques[temp->bloque]);
            temp=temp->sig;
        } while(temp!=inicioHorarios);
    }

    fclose(f);
    printf("Horario exportado a 'horario_semanal.txt'.\n");
}

// =======================
// GUARDAR Y CARGAR DATOS
// =======================
void guardarDatos() {
    FILE *f;
    Docente *dtemp = inicioDocentes;
    if(dtemp){
        f=fopen("docentes.dat","wb");
        do { fwrite(dtemp,sizeof(Docente),1,f); dtemp=dtemp->sig; } while(dtemp!=inicioDocentes);
        fclose(f);
    }
    Materia *mtemp = inicioMaterias;
    if(mtemp){
        f=fopen("materias.dat","wb");
        do { fwrite(mtemp,sizeof(Materia),1,f); mtemp=mtemp->sig; } while(mtemp!=inicioMaterias);
        fclose(f);
    }
    Aula *atemp = inicioAulas;
    if(atemp){
        f=fopen("aulas.dat","wb");
        do { fwrite(atemp,sizeof(Aula),1,f); atemp=atemp->sig; } while(atemp!=inicioAulas);
        fclose(f);
    }
    Horario *htemp = inicioHorarios;
    if(htemp){
        f=fopen("horarios.dat","wb");
        do { fwrite(htemp,sizeof(Horario),1,f); htemp=htemp->sig; } while(htemp!=inicioHorarios);
        fclose(f);
    }
    printf("Datos guardados correctamente.\n");
}

void cargarDatos() {
    FILE *f;
    Docente bufferD; Materia bufferM; Aula bufferA; Horario bufferH;
    Docente *nuevoD; Materia *nuevoM; Aula *nuevoA; Horario *nuevoH;

    // Docentes
    f=fopen("docentes.dat","rb");
    if(f){
        inicioDocentes=NULL;
        while(fread(&bufferD,sizeof(Docente),1,f)){
            nuevoD=(Docente*)malloc(sizeof(Docente));
            *nuevoD=bufferD;
            if(!inicioDocentes){ inicioDocentes=nuevoD; nuevoD->sig=inicioDocentes; }
            else{ Docente *temp=inicioDocentes; while(temp->sig!=inicioDocentes) temp=temp->sig; temp->sig=nuevoD; nuevoD->sig=inicioDocentes; }
        }
        fclose(f);
    }

    // Materias
    f=fopen("materias.dat","rb");
    if(f){
        inicioMaterias=NULL;
        while(fread(&bufferM,sizeof(Materia),1,f)){
            nuevoM=(Materia*)malloc(sizeof(Materia));
            *nuevoM=bufferM;
            if(!inicioMaterias){ inicioMaterias=nuevoM; nuevoM->sig=inicioMaterias; }
            else{ Materia *temp=inicioMaterias; while(temp->sig!=inicioMaterias) temp=temp->sig; temp->sig=nuevoM; nuevoM->sig=inicioMaterias; }
        }
        fclose(f);
    }

    // Aulas
    f=fopen("aulas.dat","rb");
    if(f){
        inicioAulas=NULL;
        while(fread(&bufferA,sizeof(Aula),1,f)){
            nuevoA=(Aula*)malloc(sizeof(Aula));
            *nuevoA=bufferA;
            if(!inicioAulas){ inicioAulas=nuevoA; nuevoA->sig=inicioAulas; }
            else{ Aula *temp=inicioAulas; while(temp->sig!=inicioAulas) temp=temp->sig; temp->sig=nuevoA; nuevoA->sig=inicioAulas; }
        }
        fclose(f);
    }

    // Horarios
    f=fopen("horarios.dat","rb");
    if(f){
        inicioHorarios=NULL;
        while(fread(&bufferH,sizeof(Horario),1,f)){
            nuevoH=(Horario*)malloc(sizeof(Horario));
            *nuevoH=bufferH;
            if(!inicioHorarios){ inicioHorarios=nuevoH; nuevoH->sig=inicioHorarios; }
            else{ Horario *temp=inicioHorarios; while(temp->sig!=inicioHorarios) temp=temp->sig; temp->sig=nuevoH; nuevoH->sig=inicioHorarios; }
        }
        fclose(f);
    }
    printf("Datos cargados correctamente.\n");
}

// =======================
// MENUS
// =======================
void menuEliminar(){
    int opc;
    do{
        printf("\nEliminar registro:\n1.Docente\n2.Materia\n3.Aula\n4.Salir\nOpcion: ");
        scanf("%d",&opc);
        switch(opc){
            case 1: eliminarDocente(); break;
            case 2: eliminarMateria(); break;
            case 3: eliminarAula(); break;
        }
    }while(opc!=4);
}

void menuPrincipal(){
    int opc;
    do{
        printf("\n=== Menu Principal ===\n");
        printf("1. Registrar Docente\n");
        printf("2. Registrar Materia\n");
        printf("3. Registrar Aula\n");
        printf("4. Asignar Horario\n");
        printf("5. Mostrar Horario Completo\n");
        printf("6. Consultar Horario\n");
        printf("7. Eliminar Registro\n");
        printf("8. Exportar Horario\n");
        printf("9. Guardar Datos\n");
        printf("10. Cargar Datos\n");
        printf("11. Salir\n");
        printf("Seleccione opcion: "); scanf("%d",&opc);
        getchar();

        char nombre[50]; int numero, capacidad;

        switch(opc){
            case 1: printf("Ingrese nombre docente: "); fgets(nombre,50,stdin); nombre[strcspn(nombre,"\n")]=0; insertarDocente(nombre); break;
            case 2: printf("Ingrese nombre materia: "); fgets(nombre,50,stdin); nombre[strcspn(nombre,"\n")]=0; insertarMateria(nombre); break;
            case 3: printf("Ingrese nombre aula: "); fgets(nombre,50,stdin); nombre[strcspn(nombre,"\n")]=0; printf("Ingrese numero aula: "); scanf("%d",&numero); printf("Ingrese capacidad: "); scanf("%d",&capacidad); insertarAula(nombre,numero,capacidad); break;
            case 4: asignarHorario(); break;
            case 5: mostrarHorarioCompleto(); break;
            case 6: consultaHorario(); break;
            case 7: menuEliminar(); break;
            case 8: exportarHorarioSemanal(); break;
            case 9: guardarDatos(); break;
            case 10: cargarDatos(); break;
        }
    }while(opc!=11);
}

// =======================
// MAIN
// =======================
int main() {
    cargarDatos();
    menuPrincipal();
    return 0;
}
