#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include <ctime>
#include <iomanip>
using namespace std;
#include "fecha.h"
#include "rlutil.h"


int Fecha::getDia(){
    return dia;
}
int Fecha::getMes(){
    return mes;
}
int Fecha::getAnio(){
    return anio;
}

Fecha::Fecha(){
    time_t tiempo;
    struct tm *tmPtr;
    tiempo = time(NULL);
    tmPtr = localtime(&tiempo);
    anio=tmPtr->tm_year+1900;
    mes=tmPtr->tm_mon+1;
    dia=tmPtr->tm_mday;
}

void Fecha::setDia(int d){
    dia = d;
}
void Fecha::setMes(int m){
    mes = m;
}
void Fecha::setAnio(int a){
    anio = a;
}
void Fecha::mostrar(){
    cout << dia << "/" << mes << "/" << anio;
}
bool Fecha::cargar(){
    bool f=true;
    cout<<setw(36) << "" << "DIA: ";
    cin >> dia;
    cout<<setw(36) << "" << "MES: ";
    cin >> mes;
    cout<<setw(36) << "" << "ANIO: ";
    cin >> anio;
    if((dia<=0)||(mes<=0)||(anio<=0)){
        f=false;
        return f;
    }
    Fecha uno;///FECHA DEL SISTEMA
    if((anio>uno.anio)||((anio==uno.anio)&&(mes>uno.mes))||((anio==uno.anio)&&(mes>=uno.mes)&&(dia>uno.dia))){
        f=false;
        return f;
    }
    if ((anio < (uno.anio-65)) || ((mes < 1)|| (mes > 12))|| ((dia < 1) || (dia > 31)) || ((mes == 02) && (dia > 29)) || ((mes== 04)&& (dia>30)) || ((mes== 06)&& (dia>30)) || ((mes== 9 )&& (dia>30)) || ((mes== 11)&& (dia>30))){
        f=false;
        return false;
    }
    return f;
}
bool Fecha::cargarReporteMes(){
    bool f=true;
    cout<<setw(36) << ""  << "MES: ";
    cin >> mes;
    cout<<setw(36) << ""  << "ANIO: ";
    cin >> anio;
    if((mes<=0)||(anio<=0)){
        f=false;
        return f;
    }
    Fecha uno;///FECHA DEL SISTEMA
    if((anio>uno.anio)||((anio==uno.anio)&&(mes>uno.mes))||((anio==uno.anio)&&(mes>uno.mes))){
        f=false;
        return f;
    }
    if ((anio < (uno.anio-65)) || ((mes < 1)|| (mes > 12))){
        f=false;
        return false;
    }
    return f;
}
bool Fecha::cargarReporteAnio(){
    bool f=true;
    cout<<setw(36) << ""  << "ANIO: ";
    cin >> anio;
    if(anio<=0){
        f=false;
        return f;
    }
    Fecha uno;///FECHA DEL SISTEMA
    if(anio>uno.anio){
        f=false;
        return f;
    }
    if (anio < (uno.anio-65)){
        f=false;
        return false;
    }
    return f;
}
