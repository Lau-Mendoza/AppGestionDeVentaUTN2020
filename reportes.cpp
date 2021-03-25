#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include "reportes.h"
#include "fecha.h"
#include "ventas.h"
#include "productos.h"
#include "dibujo.h"
#include <windows.h>
#include <conio.h>
#include "SOutil.h"
#include "rlutil.h"
using namespace rlutil;

using namespace std;


/*
INFORMES
A continuación se detallan los informes que el sistema generará
 Recaudación SEMANAL / MENSUAL
 Recaudación por menú.
 Recaudación por Localidad

*/

void menu_masvendido(){
    DetalleVenta dv;
    //Producto prod;
    int mayor=0 , contador [8]={} , nroMenu=0;
    //float mayor=0, menu[8]={};
    char nomProd[50];
    int sleep100=1500;

    cuadros2();
    gotoxy(49, 7);
    cout << "EL MENU MAS VENDIDO ES ..... " <<endl;
    Sleep(sleep100);

    FILE *p = fopen("Datos/detalleVentas.dat", "rb");
    while (fread(&dv, sizeof(DetalleVenta), 1, p)){
        contador [dv.getIDproducto()]+=dv.getCantidad();
    }
    fclose(p);
    for (int i=0; i<8; i++){
        if (i==0){
            mayor=contador[i];
            nroMenu = i;
        }
        else{
            if (contador[i]>mayor){
                mayor=contador[i];
                nroMenu = i;
            }
        }
    }
    if (nroMenu==1) strcpy (nomProd, "HAMBURGUESA");
    if (nroMenu==2) strcpy (nomProd, "PAPAS FRITAS");
    if (nroMenu==3) strcpy (nomProd, "MILANESA");
    if (nroMenu==4) strcpy (nomProd, "PIZZA");
    if (nroMenu==5) strcpy (nomProd, "EMPANADAS");
    if (nroMenu==6) strcpy (nomProd, "GASEOSA");
    if (nroMenu==7) strcpy (nomProd, "AGUA");
    if (nroMenu==8) strcpy (nomProd, "CERVEZA");


    setColor(BLACK);
    for (int i=0; i<3 ; i++){
        system("cls");
        cuadros2();
        gotoxy(53, 7);
        cout << "MENU MAS VENDIDO" <<endl;
        gotoxy(52, 12);
        setBackgroundColor(LIGHTCYAN);
        setColor(BLACK);
        cout << " " <<nomProd <<" ";
        setBackgroundColor(BLACK);

        system("cls");
        cuadros2();
        gotoxy(53, 7);
        cout << "MENU MAS VENDIDO" <<endl;
        gotoxy(52, 12);
        setBackgroundColor(LIGHTMAGENTA);
        setColor(BLACK);
        cout << " " <<nomProd <<" ";
        setBackgroundColor(BLACK);

        system("cls");
        cuadros2();
        gotoxy(53, 7);
        cout << "MENU MAS VENDIDO" <<endl;
        gotoxy(52, 12);
        setBackgroundColor(LIGHTGREEN);
        setColor(BLACK);
        cout << " " <<nomProd <<" ";
        setBackgroundColor(BLACK);
    }

    getch();
}


bool venta_localidad(){
    //preguntar la localidad mostrando las que estan en los registros.
    Venta v;
    DetalleVenta dv;
    char localidad [50];
    int i=0;
    bool b=true, bandera=false;
    float recauda=0, ganancia=0;

    cuadros2();
    gotoxy(50, 7);
    cout << "VENTAS POR LOCALIDAD/EVENTO" <<endl;
    gotoxy(33, 10);
    cout << "INGRESE LA LOCALIDAD/EVENTO QUE QUIERA VER: (en MAYUSCULA)" <<endl;
    cout <<"\n\t\t\t\t\t";
    cin.ignore();
    cin.getline(localidad, 50);


    system ("cls");
    cuadrosLista2();
    gotoxy(32, 5);
    cout << "LISTADO DE VENTAS DE LA LOCALIDAD/EVENTO: " << localidad;
    cout << endl << endl <<endl;

    while (v.leer(i++)){
        if (strcmp(v.getLocalidad(), localidad)==0){
            bandera=true;
            v.mostrar();
            recauda+=v.getTotal();
            ganancia+=(v.getTotal())-(v.getTotalCosto());
            FILE *p = fopen("Datos/detalleVentas.dat", "rb");
            if (p==NULL) return false;

            while (fread(&dv, sizeof(DetalleVenta), 1, p)){
                if (v.getID()==dv.getIdVenta()){
                    dv.mostrar();
                }
            }
            fclose(p);
            //cout << "TOTAL          : " << v.getTotal() <<endl <<endl;
            cout << endl <<"                                     ---------------" << endl << endl;
        }
    }
    if (bandera==true){
        cout << " FIN DEL LISTADO " <<endl;
        setBackgroundColor(LIGHTGREEN);
        setColor(BLACK);
        cout << " RECAUDACIÓN TOTAL DE LA LOCALIDAD/EVENTO: $" << recauda;
        setBackgroundColor(BLACK);
        cout << endl;
        setBackgroundColor(LIGHTGREEN);
        cout << " GANANCIA TOTAL DEL EVENTO/LOCALIDAD: $" << ganancia;
        setBackgroundColor(BLACK);
        cout << endl;
        setColor(WHITE);
    }
    else{
        setBackgroundColor(RED);
        cout << "\t\t\t\tNo hay ventas en esta localidad/no existe el evento\n\n" <<endl;
        setBackgroundColor(BLACK);
    }
    getch();
    return b;
}

bool rango_anio(){
    Venta v;
    DetalleVenta dv;
    Fecha comienzo;
    int i=0, sleep100=100;
    bool b=true, bandera=false;
    float recauda=0, ganancia=0;

    cuadros2();
    gotoxy(47, 7);
    cout << "VENTAS POR AÑO";
    gotoxy(35, 10);
    cout << " Ingrese año para ver las recaudaciones: " <<endl;

    while (comienzo.cargarReporteAnio()==false){
        setBackgroundColor(RED);
        cout << "\t\t\t\t\t Fecha incorrecta. Vuelva a cargar" << endl;
        setBackgroundColor(BLACK);
    }

    system ("cls");
    cout << "LISTADO: " <<endl;
    system ("cls");
    cuadrosLista2();
    gotoxy(35, 5);
    cout << "LISTADO DE VENTAS DEL AÑO " << comienzo.getAnio();
    cout << endl << endl <<endl;


    while (v.leer(i++)){
        if (v.getFechaVenta().getAnio()==comienzo.getAnio()){
            bandera=true;
            v.mostrar();
            recauda+=v.getTotal();
            ganancia+=(v.getTotal())-(v.getTotalCosto());
            FILE *p = fopen("Datos/detalleVentas.dat", "rb");
            if (p==NULL) return false;

            while (fread(&dv, sizeof(DetalleVenta), 1, p)){
                if (v.getID()==dv.getIdVenta()){
                    dv.mostrar();
                }
            }
            fclose(p);
            //cout << "TOTAL          : " << v.getTotal() <<endl <<endl;
            Sleep(sleep100);

            setColor(LIGHTCYAN);
            cout << endl <<"                                     ---------------" << endl << endl;
            setColor(WHITE);
        }
    }
    if (bandera==true){
        cout << " FIN DEL LISTADO " <<endl;
        setBackgroundColor(LIGHTGREEN);
        setColor(BLACK);
        cout << " RECAUDACIÓN TOTAL DEL AÑO: $" << recauda;
        setBackgroundColor(BLACK);
        cout << endl;
        setBackgroundColor(LIGHTGREEN);
        cout << " GANANCIA TOTAL DEL AÑO: $" << ganancia;
        setBackgroundColor(BLACK);
        cout << endl;
        setColor(WHITE);
    }
    else{
        setBackgroundColor(RED);
        cout << "\t\t\t\tNo hay ventas en este rango de fecha" <<endl;
        setBackgroundColor(BLACK);
    }
    getch();
    return b;
}

bool rango_mes(){
    Venta v;
    DetalleVenta dv;
    Fecha comienzo;
    int i=0, sleep100=100;
    bool b=true, bandera=false;
    float recauda=0, ganancia=0;

    cuadros2();
    gotoxy(47, 7);
    cout << "VENTA POR MES";
    gotoxy(35, 10);
    cout << " Ingrese mes y año para ver las recaudaciones: "<<endl;
    while (comienzo.cargarReporteMes()==false){
        setBackgroundColor(RED);
        cout << "\t\t\t\t\t Fecha incorrecta. Vuelva a cargar" << endl;
        setBackgroundColor(BLACK);
    }
    system ("cls");
    cout << "LISTADO: " <<endl;
    system ("cls");
    cuadrosLista2();
    gotoxy(35, 5);
    cout << "LISTADO DE VENTAS DEL MES " << comienzo.getMes() <<" AÑO "<< comienzo.getAnio();
    cout << endl << endl <<endl;
    while (v.leer(i++)){
        if ((v.getFechaVenta().getAnio()==comienzo.getAnio())&&(v.getFechaVenta().getMes()==comienzo.getMes())){
            bandera=true;

            v.mostrar();
            recauda+=v.getTotal();
            ganancia+=(v.getTotal())-(v.getTotalCosto());
            FILE *p = fopen("Datos/detalleVentas.dat", "rb");
            if (p==NULL) return false;

            while (fread(&dv, sizeof(DetalleVenta), 1, p)){
                if (v.getID()==dv.getIdVenta()){
                    dv.mostrar();
                }
            }
            fclose(p);
            //cout << "TOTAL          : " << v.getTotal() <<endl <<endl;
            Sleep(sleep100);
            setColor(LIGHTCYAN);
            cout << endl <<"                                     ---------------" << endl << endl;
            setColor(WHITE);
        }
    }
    if (bandera==true){
        cout << " FIN DEL LISTADO " <<endl;
        setBackgroundColor(LIGHTGREEN);
        setColor(BLACK);
        cout << " RECAUDACIÓN TOTAL DEL MES: $" << recauda;
        setBackgroundColor(BLACK);
        cout << endl;
        setBackgroundColor(LIGHTGREEN);
        cout << " GANANCIA TOTAL DEL MES: $" << ganancia;
        setBackgroundColor(BLACK);
        cout << endl;
        setColor(WHITE);
    }
    else{
        setBackgroundColor(RED);
        cout << "\n\n\t\tNo hay ventas en este rango de fecha\n\n" <<endl;
        setBackgroundColor(BLACK);
    }
    getch();
    return b;
}

bool rango_semana(){
    Venta v;
    DetalleVenta dv;
    Fecha comienzo, fin;
    int i=0, sleep100=100;
    bool b=true, bandera=false;
    float recauda=0, ganancia=0;
    cuadros2();
    gotoxy(43, 7);
    cout << "VENTA POR RANGO SEMANAL / DIARIA";
    gotoxy(35, 10);
    cout << " Ingrese desde qué fecha desea ver las recaudaciones:";
    gotoxy(35, 11);
    cout << "(MISMO MES, MISMO AÑO)";
    cout << endl;
    while (comienzo.cargar()==false){
        setBackgroundColor(RED);
        cout << "\t\t\t\t\t Fecha incorrecta. Vuelva a cargar" << endl;
        setBackgroundColor(BLACK);
    }
    cuadros2();
    gotoxy(35, 18);
    cout << " Ingrese hasta qué fecha desea ver las recaudaciones: " <<endl;
    while (fin.cargar()==false){
        setBackgroundColor(RED);
        cout << "\t\t\t\t\t Fecha incorrecta. Vuelva a cargar" << endl;
        setBackgroundColor(BLACK);
    }
    cuadros2();
    if ((comienzo.getAnio()==fin.getAnio())&&(comienzo.getMes()==fin.getMes())&&comienzo.getDia()<=fin.getDia()){
        system ("cls");
        cuadrosLista2();
        gotoxy(35, 5);
        cout << "LISTADO DE VENTAS  ";
        comienzo.mostrar();
        cout << " - ";
        fin.mostrar();
        cout << endl;
        while (v.leer(i++)){
            if ((v.getFechaVenta().getAnio()==comienzo.getAnio())&&(v.getFechaVenta().getMes()==fin.getMes())&&
                (v.getFechaVenta().getDia()<=fin.getDia()&&v.getFechaVenta().getDia()>=comienzo.getDia())){
                bandera=true;
                cout << endl <<endl;
                v.mostrar();
                recauda+=v.getTotal();
                ganancia+=(v.getTotal())-(v.getTotalCosto());
                FILE *p = fopen("Datos/detalleVentas.dat", "rb");
                if (p==NULL) return false;

                while (fread(&dv, sizeof(DetalleVenta), 1, p)){
                    if (v.getID()==dv.getIdVenta()){
                        dv.mostrar();
                    }
                }
                fclose(p);
                //cout << "TOTAL          : " << v.getTotal() <<endl <<endl;
                Sleep(sleep100);
                setColor(LIGHTCYAN);
                cout << endl << endl <<"                                ---------------" << endl << endl;
                setColor(WHITE);
            }
        }
        if (bandera==true){
            cout << "FIN DEL LISTADO " <<endl;
            setBackgroundColor(LIGHTGREEN);
            setColor(BLACK);
            cout << " RECAUDACIÓN TOTAL DEL RANGO: $" << recauda;
            setBackgroundColor(BLACK);
            cout << endl;
            setBackgroundColor(LIGHTGREEN);
            cout << " GANANCIA TOTAL DEL RANGO: $" << ganancia;
            setBackgroundColor(BLACK);
            cout << endl;
            setColor(WHITE);
        }
        else{
            setBackgroundColor(RED);
            cout << "\n\n\t\tNo hay ventas en este rango de fecha" <<endl;
            setBackgroundColor(BLACK);
        }
    }
    else{
        setBackgroundColor(RED);
        cout << " El rango de fecha no es el correcto" <<endl;
        b= false;
        setBackgroundColor(BLACK);
    }
    getch();
    return b;
}

void venta_Rango(){
    int campo;

    cuadros2();
    gotoxy(53, 7);
    cout << "VENTA POR RANGO" <<endl;
    gotoxy(42, 10);
    cout << "INGRESE LA SELECCION QUE QUIERA VER";
    gotoxy(40, 12);
    cout << "1 - BUSCAR POR DIA/S o SEMANA/S" << endl;
    gotoxy(40, 13);
    cout << "2 - BUSCAR POR MES" << endl;
    gotoxy(40, 14);
    cout << "3 - BUSCAR POR AÑO" << endl;
    gotoxy(54, 20);
    cout << "0 - VOLVER" <<  endl << endl;
    cout << endl << "> ";
    cin >> campo;

    switch(campo){
        case 1:
            system ("cls");
            rango_semana();
            getch ();
        break;
        case 2:
            system("cls");
            rango_mes();
            getch ();
        break;
        case 3:
            system("cls");
            rango_anio();
            getch ();
        break;
        case 0:
            return;
        break;
        default:
        system ("cls");
            setBackgroundColor(RED);
            cout << "\n\n\n\t\t\tOPCION INCORRECTA \n\n\n";
            setBackgroundColor(BLACK);
            system ("pause");
            return;
        break;
    }
}

void menuReportes(){
    while(true){
        system ("cls");
        cuadros();
        gotoxy(55, 7);
        cout << "MENU REPORTES" <<endl;
        gotoxy(39, 12);
        cout << "1 - VENTAS POR RANGO DE FECHA" << endl;
        gotoxy(39, 14);
        cout << "2 - VENTAS POR LOCALIDAD"<< endl; //Ordenado de mayor a menor. INT
        gotoxy(39, 16);
        cout << "3 - MENU MAS VENDIDO" << endl; //Recaudación por menú, ordenado de mayor a menor
        gotoxy(55, 22);
        cout << "0 - VOLVER " << endl;
        int pos;
        cout << endl << "> ";
        cin >> pos;

        switch(pos){
            case 1:
                system("cls");
                venta_Rango();
            break;
            case 2:
                system("cls");
                venta_localidad();
            break;
            case 3:
                system("cls");
                menu_masvendido();
            break;
            case 0:
                return;
            break;
            default:
                system ("cls");
                cout << "\t\t\tOPCION INCORRECTA \n\n\n";
                system ("pause");
                return;
            break;
        }
    }
}
