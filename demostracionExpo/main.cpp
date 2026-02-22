#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <windows.h>
using namespace std;





struct Paciente{
    int dni;
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


struct Chequeo{
    //parte de signos vitales
    int frecCardiac; //usando lpm
    int temp; //usando C
    int satOxigen; //medido en %
    int peso; //usando kg
    float altura; //usando m
    string presionA; //usando mmHg

    //datos de consulta
    string fecha;
    string motConsulta;
    string sintomatologia;
    string diagnostico;
    string tratamiento;
};


//Prototipado de funciones
void agregarPaciente(vector<Paciente> lista);
void crearChequeo(Paciente paciente);
void showMenuPrincipal();
void validarEntero(string mensaje);


int main()
{
    SetConsoleOutputCP(65001);

    std::vector<Paciente> listaPacientes;

    return 0;
}



void agregarPaciente(vector<Paciente> lista){
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
    cin.clear();
    cout<<"Antecedentes Medicos: "; //es decir, si padece ya de otras enfermedades
    getline(cin, newPaciente.antMedicos);

    //agregamos nuevo paciente
    lista.push_back(newPaciente);

}



void crearChequeo(Paciente paciente){
    Chequeo newCheck;

    cout<<"\n===REGISTRO DE NUEVO CHEQUEO==="<<endl;

    cout<<"---RECOLECCION DE SIGNOS VITALES---"<<endl;
    cout<<"Presion arterial(mmHg): ";
    cin>>newCheck.presionA;
    newCheck.frecCardiac=validarEntero("Frecuencia Cardiaca(Lpm): ");
    newCheck.temp=validarEntero("Temperatura(C): ");
    newCheck.satOxigen=validarEntero("Saturación de Oxígeno(%): ");
    newCheck.peso=validarEntero("Peso(kg): ");
    newCheck.altura=validarEntero("Altura(m): ");

    cout<<"--DATOS DE CONSULTA--"<<endl;
    cin.clear();
    cout<<"Motivo de Consulta: ";
    getline(cin, newCheck.motConsulta);
    cin.clear();
    cout<<"Sintomatología: ";
    getline(cin, newCheck.sintomatologia);
    cin.clear();
    cout<<"Diagnóstico: ";
    getline(cin, newCheck.diagnostico);
    cin.clear();
    cout<<"Tratamiento: ";
    getline(cin,newCheck.tratamiento);
    cin.clear();

    //agregamos el nuevo chequeo al expediente del paciente
    paciente.expediente.push_back(newCheck);
}



void validarEntero(string mensaje){
    int numero=0;
    cout<<mensaje;

    while(!(cin>>numero)){
        cout<<">>AVISO: Ingrese un dato válido."<<endl;
        cout<<mensaje;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return numero;
}


