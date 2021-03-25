#include <iostream>
#include "detalleVenta.h"
#include "productos.h"
#include "ventas.h"
#include "dibujo.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include "SOutil.h"
#include "rlutil.h"
using namespace rlutil;


using namespace std;

const char * FILE_DETALLEVENTAS ("Datos/detalleVentas.dat");

DetalleVenta::DetalleVenta(){

}

void DetalleVenta::setIDventa(int i){

    IDventa=i;
}
void DetalleVenta::setIDproducto(int id){
    IDproducto=id;
}
void DetalleVenta::setCantidad (int c){
    cantidad=c;
}
void DetalleVenta::setPrecio (float p){
    precio=p;
}


int DetalleVenta::getIdVenta(){
    return IDventa;
}
int DetalleVenta::getIDproducto(){
    return IDproducto;
}
int DetalleVenta::getCantidad(){
    return cantidad;
}
float DetalleVenta::getPrecio(){
    return precio;
}


bool DetalleVenta::cargar(){
    int productodv;

    system ("cls");
    cuadros2();
    gotoxy(52, 7);
    cout << "CARGAR UN PEDIDO";
    gotoxy(39, 10);
    cout << "CODIGOS DE PRODUCTOS: ";
    gotoxy(39, 11);
    cout << "1)HAMBURGUESA  2)PAPAS  3)MILANESA  4)PIZZA";
    gotoxy(39, 12);
    cout << "5)EMPANADAS  6)GASEOSA  7)AGUA  8)CERVEZA";

    //TODO: VALIDACIONES
    gotoxy(39, 14);
    cout << "Código de producto : " ;
    cin >> productodv;
    gotoxy(39, 15);
    cout << "Cantidad           : " ;
    cin >> cantidad;
    while (cantidad<=0){
        setBackgroundColor(RED);
        cout << "CANTIDAD MAL INGRESADA VUELVA A INGRESAR: " ;
        setBackgroundColor(BLACK);
        cin >> cantidad;
    }

    while (verif_codprod(productodv, cantidad)==false){
        gotoxy(39, 28);
        setBackgroundColor(RED);
        cout << "VUELVA A INGRESAR: " ;
        setBackgroundColor(BLACK);
        gotoxy(39, 29);
        cout << "Código de producto : " ;
        cin >> productodv;
        gotoxy(39, 30);
        cout << "Cantidad           : " ;
        cin >> cantidad;
        while (cantidad<=0){
        setBackgroundColor(RED);
        cout << "CANTIDAD MAL INGRESADA VUELVA A INGRESAR: " ;
        setBackgroundColor(BLACK);
        cin >> cantidad;
        }
    }
    setIDproducto(productodv);

    //setTotal(cantidad*getCosto);

    getch();

    return true;
}


float buscar_precio(int id_prod){
    int pos;

    Producto pr;
    pos=buscar_Producto(id_prod);
    pr.leer(pos);

    return pr.getPrecio();

}

bool verif_codprod(int id_prod, int cant){

    bool ver=false;
    int pos;

    Producto pr;
    pos=buscar_Producto(id_prod);

    if (pos>=0){
        pr.leer(pos);
        if  (cant>pr.getStock()) {
            cout << "\n\n\n\t\t\tNO HAY SUFICIENTE STOCK" <<endl;
            ver= false;
        }
        else{
        ver=true;
        }
        if (pr.getEstado()==false){
            ver=false;
            setBackgroundColor(RED);
            cout << "EL PRODUCTO FUE DADO DE BAJA ";
            setBackgroundColor(BLACK);
            cout << endl;
        }

    }
    else {
        setBackgroundColor(RED);
        cout << "NO EXISTE EL PRODUCTO";
        setBackgroundColor(BLACK);
        cout << endl;
        ver=false;
    }

    return ver;
}

void DetalleVenta::mostrar(){

    //cout <<setw(30) << "" << "Precio             : " <<precio <<endl;
    cout <<setw(30) << "" << "ID de producto     : " <<IDproducto <<endl;
    cout <<setw(30) << "" << "Cantidad           : " <<cantidad <<endl;

    getch();
}


bool DetalleVenta::guardar(){
    bool guardo;
    FILE *p = fopen (FILE_DETALLEVENTAS, "ab");
    if (p==NULL) return false;

    guardo = fwrite(this, sizeof(DetalleVenta), 1, p);
    fclose(p);

    return guardo;
}

int CodVenta(){
    int cantReg;
    FILE *p=fopen("Datos/ventas.dat", "rb");
    if(p==NULL) {
        cout << "       P NULL EN COD VENTA ()      ";
        return 0;
    }
    fseek(p,0,2);
    cantReg=ftell(p)/sizeof(Venta);
    fclose(p);
    return cantReg;
}


int buscar_Detalle(int cod){
    DetalleVenta dv;
    int i=0;

    while (dv.leer(i)){
        if (dv.getIdVenta()==cod){
            return i;
        }
        i++;
    }


    return -1;
}

bool DetalleVenta::leer(int pos){
    bool leer;
    if (pos>=0){

        FILE *p = fopen(FILE_DETALLEVENTAS, "rb");
        if (p==NULL) return false;

        fseek(p, pos* sizeof(DetalleVenta), SEEK_SET);
        leer = fread (this, sizeof(DetalleVenta), 1, p);
        fclose(p);
    }
    else leer = false;

    return leer;
}

void listar_detalles(){
    DetalleVenta dv;
    int i=0;
    int sleep100=100;
    cout << "LISTADO: " <<endl;
    cout << "---------------" << endl << endl;

    //cout << "ID VENTA\tIDPRODUCTO\t\t\tCANTIDAD" <<endl;
    while (dv.leer(i++)){
        cout << "ID VENTA: " <<endl;
        cout << dv.getIdVenta() <<endl;
        cout << "ID producto: " <<endl;
        cout << dv.getIDproducto() <<endl;
        cout << "cantidad: " <<endl;
        cout << dv.getCantidad() <<endl;
        Sleep(sleep100);
    }
    getch();
}
