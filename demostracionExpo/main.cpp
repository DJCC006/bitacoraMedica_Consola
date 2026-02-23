#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <windows.h>
#include <iomanip>
using namespace std;






struct Chequeo{
    //parte de signos vitales
    int frecCardiac; //usando lpm
    int temp; //usando C
    int satOxigen; //medido en %
    int peso; //usando kg
    float altura; //usando m.............X
    string presionA; //usando mmHg

    //datos de consulta
    int idExpediente;
    string fecha;
    string motConsulta;
    string sintomatologia;
    string diagnostico;
    string tratamiento;
};



struct Paciente{
    unsigned int dni;
    int edad;
    int telefono;
    char genero;
    string nombre;
    string apellido;
    string typeBlood;
    string antMedicos;//Antecedentes medicos

    //vector que guarda todos los chequeos del paciente
    std::vector<Chequeo> expediente;
};




//Prototipado de funciones
void agregarPaciente(Paciente* lista, int &contador, int TAM);
void crearChequeo(const Paciente* paciente, int index);
void showMenuPrincipal();
int validarEntero(string mensaje);
void listarPacientes(const Paciente* lista, int contador);
void showExpedientes( const Paciente* lista, int index);
void ordenarPacientes(Paciente* lista, int TAM);
int buscarPorDNI(const Paciente* lista, int TAM, int IDBuscado);


int main()
{
    SetConsoleOutputCP(65001);
    int TAM=8;
    //STACK
    Paciente* listaPacientes= new Paciente[TAM];
    int contador=0;
    int opcion=0;

    do{
        showMenuPrincipal();
        opcion=validarEntero("Ingrese una opcion: ");

        switch(opcion){
            case 1:{
                agregarPaciente(listaPacientes, contador, TAM);
                //ordenarPacientes(listaPacientes, TAM);//ordenado automatico
                break;
            }

            case 2:{
                /*
                 * Buscamos por dni
                 * mandamos info
                 *
                 * */
                int dniBuscado=0;
                cout<<"\nIngrese el DNI del paciente a realizar chequeo: ";
                cin>>dniBuscado;
                int index=buscarPorDNI(listaPacientes, TAM, dniBuscado);
                crearChequeo(listaPacientes, index);

                break;
            }

            case 3:{
                listarPacientes(listaPacientes, contador);
                break;
            }

            case 4:{
                int dniBuscado=0;
                cout<<"\nIngrese el DNI de paciente: ";
                cin>>dniBuscado;
                int index = buscarPorDNI(listaPacientes, TAM, dniBuscado);
                cout<<"index: "<<index<<endl;
                showExpedientes(listaPacientes, index);
                break;
            }

            case 5:{
                cout<<"\nCerrando Sesion..."<<endl;
                delete[] listaPacientes;
                listaPacientes=nullptr;
                break;
            }
        }



    }while(opcion!=5);

    return 0;
}



void agregarPaciente(Paciente* lista, int &contador, int TAM){
    if(contador>TAM){
        cout<<">>Aviso: Máximo de Pacientes Alcanzado"<<endl;
    }else{
        //Creamos obj de nuevo paciente
        Paciente newPaciente;

        //Pedimos datos
        cout<<"\n---Registro de Nuevo Paciente---"<<endl;
        cout<<"Nombre: ";
        cin>>newPaciente.nombre;
        cout<<"Apellido: ";
        cin>>newPaciente.apellido;
        newPaciente.edad=validarEntero("Edad: ");
        cout<<"Sexo (M/F): ";
        cin>>newPaciente.genero;
        newPaciente.telefono=validarEntero("Número Telefonico: ");
        newPaciente.dni=validarEntero("DNI: ");
        cout<<"Tipo de Sangre: ";
        cin>>newPaciente.typeBlood;
        // cin.clear();
        // cout<<"Antecedentes Medicos: "; //es decir, si padece ya de otras enfermedades
        // getline(cin, newPaciente.antMedicos);

        //agregamos nuevo paciente
        lista[contador]= newPaciente;
        contador++;

        cout<<endl;

    }

}



void crearChequeo(const Paciente* lista, int index){

    Paciente pacienteAdd = lista[index];


    Chequeo newCheck;

    cout<<"\n===REGISTRO DE NUEVO CHEQUEO==="<<endl;

    cout<<"\n---RECOLECCION DE SIGNOS VITALES---"<<endl;
    cout<<"Presion arterial(mmHg): ";
    cin>>newCheck.presionA;
    newCheck.frecCardiac=validarEntero("Frecuencia Cardiaca(Lpm): ");
    newCheck.temp=validarEntero("Temperatura(C): ");
    newCheck.satOxigen=validarEntero("Saturación de Oxígeno(%): ");
    newCheck.peso=validarEntero("Peso(kg): ");
    newCheck.altura=validarEntero("Altura(m): ");
    cin.ignore(1000,'\n');

    cout<<"\n--DATOS DE CONSULTA--"<<endl;
    cout<<"Fecha de Consulta: ";
    cin>>newCheck.fecha;


    cin.ignore(1000, '\n');

    cout<<"Motivo de Consulta: ";
    getline(cin, newCheck.motConsulta);

    cout<<"Sintomatología: ";
    getline(cin, newCheck.sintomatologia);

    cout<<"Diagnóstico: ";
    getline(cin, newCheck.diagnostico);

    cout<<"Tratamiento: ";
    getline(cin,newCheck.tratamiento);


    //Registramos codigo de chequeo
    pacienteAdd.expediente.push_back(newCheck);
    int idChequeo= pacienteAdd.expediente.size();
    newCheck.idExpediente=idChequeo;

    //agregamos el nuevo chequeo al expediente del paciente


    cout<<"TOTAL: "<<pacienteAdd.expediente.size();
    cout<<">>Chequeo Registrado Exitosamente"<<endl;
}



int validarEntero(string mensaje){
    unsigned int numero=0;
    cout<<mensaje;

    while(!(cin>>numero)){
        cout<<">>AVISO: Ingrese un dato válido."<<endl;
        cout<<mensaje;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return numero;
}



void listarPacientes(const Paciente* lista,int contador){


    //heading
    cout<<"\nDNI         NOMBRE      APELLIDO      SEXO      EDAD      TIPO SANGRE      TELEFONO"<<endl;
    cout<<"-------------------------------------------------------------------------------------"<<endl;

    //iteracion
    for(int i=0; i<contador; i++){
        //Paciente actual = lista[i];
        cout<<lista[i].dni;
        cout<<setw(10)<<lista[i].nombre;
        cout<<setw(14)<<lista[i].apellido;
        cout<<setw(10)<<lista[i].genero;
        cout<<setw(10)<<lista[i].edad;
        cout<<setw(10)<<lista[i].typeBlood;
        cout<<setw(21)<<lista[i].telefono<<endl;
        cout<<"-------------------------------------------------------------------------------------"<<endl;
    }
}


void showExpedientes(const Paciente* lista, int index){
    Paciente actualPaciente= lista[index];
    //std::vector<Chequeo> actual = actualPaciente.expediente;
    int totalExpediente = actualPaciente.expediente.size();

    cout<<"total: "<<totalExpediente<<endl;
    //heading
    cout<<"\nCODIGO      FECHA      MOTIVO      "<<endl;
    cout<<"--------------------------------------"<<endl;
    for(int i=0; i<totalExpediente; i++){
       // Chequeo check= actualPaciente.expediente.at(i);
        cout<<actualPaciente.expediente.at(i).idExpediente;
        cout<<setw(10)<<actualPaciente.expediente.at(i).fecha;
        cout<<setw(10)<<actualPaciente.expediente.at(i).motConsulta<<endl;
        cout<<"--------------------------------------"<<endl;
    }

}


void showMenuPrincipal(){
    cout<<"\n===== GESTOR MEDICO ====="<<endl;
    cout<<"1.Agregar Nuevo Paciente"<<endl;
    cout<<"2.Registrar Chequeo"<<endl;
    cout<<"3.Mostrar Lista Pacientes"<<endl;
    cout<<"4.Mostrar Expediente de Paciente"<<endl;
    cout<<"5.Cerrar Sesion"<<endl;
}


void ordenarPacientes(Paciente* lista, int TAM){
    for(int i=0; i<TAM-1; i++){
        int min_inx=i;

        for(int j=i+1; j<TAM; j++){
            if(lista[j].dni< lista[j+1].dni){
                min_inx=j;
            }
        }

        Paciente temp = lista[min_inx];

        lista[min_inx]=lista[i];
        lista[i]=temp;
    }
}

int buscarPorDNI(const Paciente* lista, int TAM, int IDBuscado){
    for(int i=0; i<TAM; i++){
        if(lista[i].dni==IDBuscado){
            return i;
        }
    }
    return -1;
}
