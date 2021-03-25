#include <iostream>
#include "configuracion.h"
#include "ventas.h"
#include "detalleVenta.h"
#include "productos.h"
#include "dibujo.h"
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <fstream>
#include "rlutil.h"
using namespace rlutil;

using namespace std;

const char * FILE_BKPVENTAS ("Datos/bkpventas.dat");
const char * FILE_BKPDETALLES ("Datos/bkpDetalleventa.dat");
const char * FILE_BKPRODUCTOS ("Datos/bkpproductos.dat");

bool restaurarVentas(){
    Venta v;

    FILE *p=fopen(FILE_BKPVENTAS, "rb");
    if (p==NULL){
            cout<<"NO SE ENCONTRO EL ARCHIVO";
            return false;
    }
    FILE *pB=fopen("Datos/ventas.dat", "wb");
		if(pB==NULL) {
            fclose(p);
            return false;
		}
    while(fread(&v, sizeof (Venta), 1, p)==1){
        fwrite(&v,sizeof (Venta), 1,pB);
    }
    fclose(p);
    fclose(pB);
    return true;
}

bool restaurarDetalles(){
    DetalleVenta dv;

    FILE *p=fopen(FILE_BKPDETALLES, "rb");
    if (p==NULL){
            cout<<"NO SE ENCONTRO EL ARCHIVO";
            return false;
    }
    FILE *pB=fopen("Datos/detalleVentas.dat", "wb");
		if(pB==NULL) {
            fclose(p);
            return false;
		}
    while(fread(&dv, sizeof (DetalleVenta), 1, p)==1){
        fwrite(&dv,sizeof (DetalleVenta), 1,pB);
    }
    fclose(p);
    fclose(pB);
    return true;
}

bool restaurarProductos(){
    Producto pr;

    FILE *p=fopen(FILE_BKPRODUCTOS, "rb");
    if (p==NULL){
            cout<<"NO SE ENCONTRO EL ARCHIVO";
            return false;
    }
    FILE *pB=fopen("Datos/productos.dat", "wb");
		if(pB==NULL) {
            fclose(p);
            return false;
		}
    while(fread(&pr, sizeof (Producto), 1, p)==1){
        fwrite(&pr,sizeof (Producto), 1,pB);
    }
    fclose(p);
    fclose(pB);
    return true;
}

bool backupVentas(){
    Venta v;

    FILE *p=fopen("Datos/ventas.dat", "rb");
    if (p==NULL)return false;
    FILE *pB=fopen(FILE_BKPVENTAS, "wb");
		if(pB==NULL) {
            fclose(p);
            return false;
		}
    while(fread(&v, sizeof (Venta), 1, p)==1){
        fwrite(&v,sizeof (Venta), 1,pB);
    }
    fclose(p);
    fclose(pB);
    return true;
}

bool backupDetalleVenta(){
    DetalleVenta dv;

    FILE *p=fopen("Datos/detalleVentas.dat", "rb");
    if (p==NULL)return false;
    FILE *pB=fopen(FILE_BKPDETALLES, "wb");
		if(pB==NULL) {
            fclose(p);
            return false;
		}
    while(fread(&dv, sizeof (DetalleVenta), 1, p)==1){
        fwrite(&dv,sizeof (DetalleVenta), 1,pB);
    }
    fclose(p);
    fclose(pB);
    return true;
}

bool backupProductos(){
    Producto pr;

    FILE *p=fopen("Datos/productos.dat", "rb");
    if (p==NULL)return false;
    FILE *pB=fopen(FILE_BKPRODUCTOS, "wb");
		if(pB==NULL) {
            fclose(p);
            return false;
		}
    while(fread(&pr, sizeof (Producto), 1, p)==1){
        fwrite(&pr,sizeof (Producto), 1,pB);
    }
    fclose(p);
    fclose(pB);
    return true;
}



void menuExportar(){

    while(true){
        system ("cls");
        cout << "\n\n\t\t EXPORTAR ARCHIVOS\n\n" <<endl;
        cout << "1 - VENTAS" << endl;
        cout << "2 - PRODUCTOS" << endl;
        cout << "3 - VENDEDORES" << endl;
        cout << "------------------" << endl;
        cout << "0 - VOLVER " << endl;
        int pos;
        cout << endl << "> ";
        cin >> pos;

        switch(pos){
            case 1:
            //exportarVentas();
            break;
            case 2:

            break;
            case 3:

            break;
            case 0:
                return;
            break;
            system ("cls");
                cout << "\t\t\tOPCION INCORRECTA \n\n\n";
                system ("pause");
                return;
            break;
        }
    }
}

void menuBackup(){

    while(true){
        system ("cls");
        cuadros2();
        gotoxy(50, 7);
        cout << "REALIZAR COPIA DE SEGURIDAD";
        gotoxy(41, 10);
        cout << "1 - VENTAS";
        gotoxy(41, 12);
        cout << "2 - PRODUCTOS";
        gotoxy(41, 14);
        cout << "3 - REALIZAR BACK UP COMPLETO";
        gotoxy(55, 23);
        cout << "0 - VOLVER ";
        int pos;
        cout << endl << "> ";
        cin >> pos;

        switch(pos){
            case 1:
                system ("cls");
                imagen_backup();
                if (backupVentas()&&backupDetalleVenta()){
                    setBackgroundColor(GREEN);
                    cout << "BACK UP REALIZADO CORRECTAMENTE";
                    setBackgroundColor(BLACK);
                }
                else{
                    setBackgroundColor(RED);
                    cout << "NO SE PUDO REALIZAR EL BACK UP";
                    setBackgroundColor(BLACK);
                }
                getch();
            break;
            case 2:
                system ("cls");
                imagen_backup();
                if (backupProductos()){
                    setBackgroundColor(GREEN);
                    cout << "BACK UP REALIZADO CORRECTAMENTE";
                    setBackgroundColor(BLACK);
                }
                else{
                    setBackgroundColor(RED);
                    cout << "NO SE PUDO REALIZAR EL BACK UP";
                    setBackgroundColor(BLACK);
                }
                getch();
            break;
            case 3:
                system ("cls");
                imagen_backup();
                if (backupVentas()&&backupDetalleVenta()&&backupProductos()){
                    setBackgroundColor(GREEN);
                    cout << "BACK UP REALIZADO CORRECTAMENTE";
                    setBackgroundColor(BLACK);
                }
                else{
                    setBackgroundColor(RED);
                    cout << "NO SE PUDO REALIZAR EL BACK UP";
                    setBackgroundColor(BLACK);
                }
                getch();
            break;
            case 0:
                return;
            break;
                setBackgroundColor(RED);
                cout << "\t\t\tOPCION INCORRECTA \n\n\n";
                setBackgroundColor(BLACK);
                system ("pause");
                return;
            break;
        }
    }
    return;
}


void menuRestaurar(){

    while(true){
        system ("cls");
        cuadros2();
        gotoxy(50, 7);
        cout << "RESTAURAR COPIA DE SEGURIDAD";
        gotoxy(41, 10);
        cout << "1 - VENTAS";
        gotoxy(41, 12);
        cout << "2 - PRODUCTOS";
        gotoxy(41, 14);
        cout << "3 - RESTAURAR POR COMPLETO";
        gotoxy(55, 23);
        cout << "0 - VOLVER ";
        int pos;
        cout << endl << "> ";
        cin >> pos;

        switch(pos){
            case 1:
                system ("cls");
                imagen_restauracion();
                if (restaurarVentas()&&restaurarDetalles()){
                    setBackgroundColor(GREEN);
                    cout << "RESTAURADO CORRECTAMENTE";
                    setBackgroundColor(BLACK);
                }
                else{
                    setBackgroundColor(RED);
                    cout << "NO SE PUDO RESTAURAR";
                    setBackgroundColor(BLACK);
                }
                getch();
            break;
            case 2:
                system ("cls");
                imagen_restauracion();
                if (restaurarProductos()){
                    setBackgroundColor(GREEN);
                    cout << "RESTAURADO CORRECTAMENTE";
                    setBackgroundColor(BLACK);
                }
                else{
                    setBackgroundColor(RED);
                    cout << "NO SE PUDO RESTAURAR";
                    setBackgroundColor(BLACK);
                }
                getch();
            break;
            case 3:
                system ("cls");
                imagen_restauracion();
                if (restaurarVentas()&&restaurarDetalles()&&restaurarProductos()){
                    setBackgroundColor(GREEN);
                    cout << "RESTAURADO CORRECTAMENTE";
                    setBackgroundColor(BLACK);
                }
                else{
                    setBackgroundColor(RED);
                    cout << "NO SE PUDO RESTAURAR";
                    setBackgroundColor(BLACK);
                }
                getch();
            break;
            case 0:
                return;
                setBackgroundColor(RED);
                cout << "\t\t\tOPCION INCORRECTA \n\n\n";
                setBackgroundColor(BLACK);
                system ("pause");
                return;
            break;
        }
    }
    return;
}



void menuConfiguracion(){

    while(true){
        system ("cls");
        cuadros();
        gotoxy(52, 7);
        cout << "MENU DE CONFIGURACION";
        gotoxy(39, 12);
        cout << "1 - REALIZAR COPIA DE SEGURIDAD";
        gotoxy(39, 14);
        cout << "2 - RESTAURAR COPIA DE SEGURIDAD";
        gotoxy(39, 16);
        cout << "3 - EXPORTAR DATOS";
        gotoxy(55, 23);
        cout << "0 - VOLVER ";
        int pos;
        cout << endl << "> ";
        cin >> pos;

        switch(pos){
            case 1:
                menuBackup();
            break;
            case 2:
                menuRestaurar();
            break;
            case 3:
                menuExportar();
            break;
            case 0:
                return;
            break;
            system ("cls");
                cout << "\t\t\tOPCION INCORRECTA \n\n\n";
                system ("pause");
                return;
            break;
        }
    }
}
