#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include "productos.h"
#include "dibujo.h"

#include "SOutil.h"
#include "rlutil.h"
using namespace rlutil;

using namespace std;

const char *FILE_PRODUCTO = ("Datos/productos.dat");

Producto::Producto(){
    ID=0;
    strcpy(nombre, "");
    costo=0;
    precio=0;
    stock=0;
    estado=true;
}

void Producto::setID(int id){
    ID=id;
}
void Producto::setNombre(char * n){
    strcpy (nombre,n);
}
void Producto::setCosto (float c){
    costo=c;
}
void Producto::setPrecio (float p){
    precio=p;
}
void Producto::setStock (float s){
    stock=s;
}
void Producto::setEstado(bool e){
    estado=e;
}
int Producto::getID(){
    return ID;
}
char* Producto::getNombre(){
    return nombre;
}
float Producto::getCosto(){
    return costo;
}
float Producto::getPrecio(){
    return precio;
}
float Producto::getStock(){
    return stock;
}
bool Producto::getEstado(){
    return estado;
}

bool Producto::cargar(){

    system ("cls");
    int codigo;
    char nom[50];
    cuadros2();
    gotoxy(50, 7);
    cout << "NUEVO PRODUCTO" <<endl;
    gotoxy(41, 9);
    cout << "Codigo de producto: ";
    cin >> codigo;
    while(codigo<0){
        system ("cls");
        cuadros2();
        gotoxy(50, 7);
        cout << "NUEVO PRODUCTO" <<endl;
        gotoxy(41, 9);
        setBackgroundColor(RED);
        cout << "CODIGO MAL INGRESADO, VUELVA A INGRESAR: " ;
        setBackgroundColor(BLACK);
        cin >>codigo;
    }
    while(cod_rep(codigo)==1){
        system ("cls");
        cuadros2();
        gotoxy(50, 7);
        cout << "NUEVO PRODUCTO" <<endl;
        gotoxy(41, 9);
        setBackgroundColor(RED);
        cout << "ESTE CÓDIGO YA EXISTE EN LA BASE DE DATOS, POR FAVOR VUELVA A INGRESAR: " ;
        setBackgroundColor(BLACK);
        cin >>codigo;
    }
    setID(codigo);
    gotoxy(41, 10);
    cout << "Nombre: ";
    cin.ignore();
    cin.getline (nom, 50);
    while(nom_rep(nom)==1){
        system ("cls");
        cuadros2();
        gotoxy(50, 7);
        cout << "NUEVO PRODUCTO" <<endl;
        gotoxy(41, 10);
        setBackgroundColor(RED);
        cout << "ESTE NOMBRE YA EXISTE EN LA BASE DE DATOS, POR FAVOR VUELVA A INGRESAR: " ;
        setBackgroundColor(BLACK);
        cin >>nom;
    }
    setNombre(nom);
    gotoxy(41, 11);
    cout << "Costo: ";
    cin >> costo;
    while(costo<=0){
        system ("cls");
        cuadros2();
        gotoxy(50, 7);
        cout << "NUEVO PRODUCTO" <<endl;
        gotoxy(41, 11);
        setBackgroundColor(RED);
        cout << "NO SE PUEDE INGRESAR UN COSTO MENOR A 0, vuelva a ingresar: " ;
        setBackgroundColor(BLACK);
        cin >>costo;
    }
    setCosto(costo);
    gotoxy(41, 12);
    cout << "Precio de venta (sugerido: Costo x2): ";
    cin >> precio;
    while(precio<=0){
        system ("cls");
        cuadros2();
        gotoxy(50, 7);
        cout << "NUEVO PRODUCTO" <<endl;
        gotoxy(41, 12);
        setBackgroundColor(RED);
        cout << "NO SE PUEDE INGRESAR UN PRECIO DE VENTA MENOR A 0, vuelva a ingresar: " ;
        setBackgroundColor(BLACK);
        cin >>precio;
    }
    setPrecio(precio);
    gotoxy(41, 13);
    cout << "Stock a la fecha: ";
    cin >>stock;
    while(stock<=0){
        system ("cls");
        cuadros2();
        gotoxy(50, 7);
        cout << "NUEVO PRODUCTO" <<endl;
        gotoxy(41, 13);
        setBackgroundColor(RED);
        cout << "NO SE PUEDE INGRESAR STOCK MENOR A 0, vuelva a ingresar: " ;
        setBackgroundColor(BLACK);
        cin >>stock;
    }
    setStock(stock);
    //p.estado(true);

    return true;
}

bool Producto::guardar(){
    bool guardo;
    FILE *p = fopen (FILE_PRODUCTO, "ab");
    if (p==NULL) return false;

    guardo = fwrite(this, sizeof(Producto), 1, p);
    fclose(p);

    return guardo;
}

bool Producto::guardar(int pos){
    bool guardo;
    if (pos>=0){
        FILE *p = fopen (FILE_PRODUCTO, "rb+");
        if (p==NULL) return false;
        fseek (p, pos* sizeof(Producto), SEEK_SET);
        guardo = fwrite(this, sizeof(Producto), 1, p);
        fclose(p);
    }
    else {
        guardo = false;
    }
    return guardo;
}

bool Producto::leer(int pos){
    bool leer;
    if (pos>=0){
        //cout <<"pos : " << pos << endl;
        FILE *p = fopen(FILE_PRODUCTO, "rb");
        if (p==NULL) return false;

        fseek(p, pos* sizeof(Producto), SEEK_SET);
        leer = fread (this, sizeof(Producto), 1, p);
        fclose(p);
    }
    else leer = false;

    return leer;
}

bool Producto::mostrar(){
    cout << "\t\t\t\t\tCodigo de producto: " << ID <<endl;
    cout << "\t\t\t\t\tNombre: " << nombre << endl;
    cout << "\t\t\t\t\tCosto: $" << costo <<endl;
    cout << "\t\t\t\t\tPrecio de venta (sugerido: Costo x2): $" << precio << endl;
    cout << "\t\t\t\t\tStock a la fecha: " << stock <<endl;
    cout << "\n\n";

    return true;
}

void menuProducto(){

    while(true){
        system ("cls");
        cuadros();
        gotoxy(50, 7);
        cout << "MENU PRODUCTOS" <<endl;
        gotoxy(39, 11);
        cout << "1 - CARGAR PRODUCTO " << endl;
        gotoxy(39, 13);
        cout << "2 - MODIFICAR PRODUCTO" << endl;
        gotoxy(39, 15);
        cout << "3 - AGREGAR / DESCONTAR STOCK A UN PRODUCTO " << endl;
        gotoxy(39, 17);
        cout << "4 - ELIMINAR PRODUCTO " << endl;
        gotoxy(39, 19);
        cout << "5 - VER UN MENU EN PARTICULAR" << endl;
        gotoxy(39, 21);
        cout << "6 - LISTAR MENUES" << endl;
        gotoxy(55, 24);
        cout << "0 - VOLVER " << endl;
        int pos;
        cout << endl << "> ";
        cin >> pos;

        switch(pos){
            case 1:
                system ("cls");
                if (nuevo_Producto()){
                    gotoxy(50, 35);
                    setBackgroundColor(GREEN);
                    cout <<endl;
                    cout << "PRODUCTO GUARDADO CORRECTAMENTE" <<endl;
                    setBackgroundColor(BLACK);
                }
                else {
                    gotoxy(50, 35);
                    setBackgroundColor(RED);
                    cout << "NO SE PUDO GUARDAR EL PRODUCTO " << endl;
                    setBackgroundColor(BLACK);
                }
                getch();
            break;
            case 2:
                system ("cls");
                if (modificar_Producto()) {
                    gotoxy(50, 35);
                    setBackgroundColor(GREEN);
                    cout << "PRODUCTO MODIFICADO CORRECTAMENTE" <<endl;
                    setBackgroundColor(BLACK);
                    getch();
                }
                else{
                    gotoxy(50, 35);
                    setBackgroundColor(RED);
                    cout << "NO SE PUDO MODIFICAR  " << endl;
                    setBackgroundColor(BLACK);
                    getch();
                }
                system ("pause");
            break;
            case 3:
                system ("cls");
                if (agregar_Stock()) {
                    gotoxy(50, 35);
                    setBackgroundColor(GREEN);
                    cout << "STOCK MODIFICADO CORRECTAMENTE" <<endl;
                    setBackgroundColor(BLACK);
                    getch();
                }
                else {
                    gotoxy(50, 35);
                    setBackgroundColor(RED);
                    cout << "NO SE PUDO MODIFICAR STOCK  " << endl;
                    setBackgroundColor(BLACK);
                    getch();
                }
                system ("pause");
            break;
            case 4:
                system ("cls");
                if (eliminar_Producto()) {
                    gotoxy(50, 35);
                    setBackgroundColor(GREEN);
                    cout << "PRODUCTO ELIMINADO CORRECTAMENTE" <<endl;
                    setBackgroundColor(BLACK);
                    getch();
                }
                else{
                    gotoxy(50, 35);
                    setBackgroundColor(RED);
                    cout << "NO EXISTE EL PRODUCTO " << endl;
                    setBackgroundColor(BLACK);
                    getch();
                }
            break;
            case 5:
                system ("cls");
                if (listar_Producto()==false) {
                    gotoxy(50, 35);
                    setBackgroundColor(RED);
                    cout << "NO SE ENCONTRO EL CODIGO DE PRODUCTO" <<endl;
                    setBackgroundColor(BLACK);
                    getch();
                }
            break;
            case 6:
                system ("cls");
                listar_Productos();
            break;
            case 0:
                return;
            break;
            system ("cls");
                gotoxy(50, 35);
                setBackgroundColor(RED);
                cout << "\t\t\tOPCION INCORRECTA \n\n\n";
                setBackgroundColor(BLACK);
                system ("pause");
                return;
            break;
        }
    }
}

bool nuevo_Producto(){
    Producto p;
    if (p.cargar()==1 && p.guardar()==1){
        getch();
        return true;
    }
    else {
        system ("pause");
        return false;
    }
}
void listar_Productos(){
    Producto p;
    int i=0;
    int sleep100=100;
    cuadrosLista2();
    gotoxy(46, 5);
    cout << "LISTADO DE PRODUCTOS" <<endl;
    cout <<endl << endl << endl << endl;
    cout << left;
    cout << setw(15) <<"CODIGO";
    cout << setw(20) <<"NOMBRE";
    cout << setw(20) <<"COSTO";
    cout << setw(25) <<"PRECIO VENTA";
    cout << setw(22) <<"STOCK";
    cout << setw(46) <<"ESTADO";
    cout <<endl <<endl;
    while (p.leer(i++)){
        if (p.getEstado()==0){
            setColor(RED);
        }
        cout << setw(15) <<p.getID();
        cout << setw(20) <<p.getNombre();
        cout <<"$" << setw(20) <<p.getCosto();
        cout <<"$" << setw(25) <<p.getPrecio();
        cout << setw(22) <<p.getStock();
        cout << setw(46) <<p.getEstado();
        cout <<endl;
        Sleep(sleep100);
        setColor(WHITE);
    }
    getch();
    i=0;
    //msj("ATENCIÓN. Los siguientes productos se están quedando sin stock: ");
    setBackgroundColor(RED);
    cout << "\n\n\nATENCIÓN. Los siguientes productos se están quedando sin stock: " << endl;
    setBackgroundColor(BLACK);
    setColor(WHITE);
    while (p.leer(i++)){
        if (p.getID()==1&&p.getStock()<120){
        cout << p.getNombre() << endl; //HAMBURGUESA
        }
        if (p.getID()==2&&p.getStock()<100){
        cout << p.getNombre() << endl; //PAPAS FRITAS
        }
        if (p.getID()==3&&p.getStock()<50){
        cout << p.getNombre() << endl; //MILANESA
        }
        if (p.getID()==4&&p.getStock()<30){
        cout << p.getNombre() << endl; //PIZZA
        }
        if (p.getID()==5&&p.getStock()<72){
        cout << p.getNombre() << endl; //EMPANADAS
        }
        if (p.getID()==6&&p.getStock()<72){
        cout << p.getNombre() << endl; //GASEOSA
        }
        if (p.getID()==7&&p.getStock()<36){
        cout << p.getNombre() << endl; //AGUA
        }
        if (p.getID()==8&&p.getStock()<140){
        cout << p.getNombre() << endl; //CERVEZA
        }
        Sleep(sleep100);
    }

    getch();
}

bool listar_Producto(){
    Producto p;
    int cod, pos;
    bool listo;
    cuadros2();
    gotoxy(50, 7);
    cout << "NUEVO PRODUCTO" <<endl;
    gotoxy(41, 9);
    cout << "Ingrese el codigo de producto que desea ver: ";
    cin >> cod;

    pos=buscar_Producto(cod);

    if (pos>=0){
        p.leer(pos);
        gotoxy(41, 11);
        cout << "ID             : " <<p.getID();
        gotoxy(41, 12);
        cout << "Nombre         : " <<p.getNombre();
        gotoxy(41, 13);
        cout << "Costo          : " <<p.getCosto();
        gotoxy(41, 14);
        cout << "Precio         : " <<p.getPrecio();
        gotoxy(41, 15);
        cout << "Stock          : " <<p.getStock();
        getch();
        listo=true;
    }
    else {
        gotoxy(50, 35);
        setBackgroundColor(RED);
        cout << "NO SE ENCONTRO EL CODIGO DE PRODUCTO" <<endl;
        setBackgroundColor(BLACK);
        listo = false;
        system ("pause");
    }
    return listo;
}

bool modificar_Producto(){
    Producto p;
    int cod, pos, modifico, campo;

    cuadros2();
    gotoxy(50, 7);
    cout << "MODIFICAR PRODUCTO" <<endl;
    gotoxy(41, 9);
    cout << "Ingrese el codigo de producto a modificar: ";
    cin >> cod;

    pos=buscar_Producto(cod);
    if (pos>=0){
        p.leer(pos);

        if (p.getEstado()==false){
            setBackgroundColor(RED);
            cout << "\t\t  ATENCION!!! ESTE PRODUCTO FUE ELIMINADO CON ANTERIORIDAD. \n\n" <<endl;
            setBackgroundColor(BLACK);
        }
        gotoxy(41, 10);
        cout << "Detalles del producto:" <<endl;
        p.mostrar();
        getch();
        system("cls");
        cuadros2();
        gotoxy(50, 7);
        cout << "MODIFICAR PRODUCTO";
        gotoxy(45, 10);
        cout << "INGRESE EL CAMPO QUE DESEA MODIFICAR:";
        gotoxy(41, 12);
        cout << "1 - CODIGO DE PRODUCTO";
        gotoxy(41, 13);
        cout << "2 - NOMBRE";
        gotoxy(41, 14);
        cout << "3 - COSTO";
        gotoxy(41, 15);
        cout << "4 - PRECIO DE VENTA" ;
        gotoxy(55, 23);
        cout << "0 - VOLVER";
        gotoxy(43, 18);
        cout << "> ";
        cin >> campo;

        switch(campo){
            case 1:
                system("cls");
                cuadros2();
                gotoxy(50, 7);
                cout << "MODIFICAR PRODUCTO" <<endl;
                gotoxy(45, 10);
                int cod;
                cout << "INGRESE EL NUEVO CÓDIGO: ";
                cin >> cod;
                p.setID(cod);
                gotoxy(45, 12);
                setBackgroundColor(GREEN);
                cout << "CÓDIGO MODIFICADO CORRECTAMENTE"<< endl;
                setBackgroundColor(BLACK);
                getch ();
            break;
            case 2:
                system("cls");
                char nom[50];
                cuadros2();
                gotoxy(50, 7);
                cout << "MODIFICAR PRODUCTO" <<endl;
                gotoxy(45, 10);
                cout << "INGRESE EL NUEVO NOMBRE: " <<endl;
                cin.ignore();
                cin.getline(nom, 50);
                p.setNombre(nom);
                gotoxy(45, 12);
                setBackgroundColor(GREEN);
                cout << "NOMBRE MODIFICADO CORRECTAMENTE"<< endl;
                setBackgroundColor(BLACK);
                getch ();
            break;
            case 3:
                system("cls");
                float cos;
                cuadros2();
                gotoxy(50, 7);
                cout << "MODIFICAR PRODUCTO" <<endl;
                gotoxy(45, 10);
                cout << "INGRESE EL NUEVO COSTO DEL PRODUCTO: ";
                cin >> cos;
                p.setCosto(cos);
                gotoxy(45, 12);
                setBackgroundColor(GREEN);
                cout << "COSTO MODIFICADO CORRECTAMENTE"<< endl;
                setBackgroundColor(BLACK);
                getch ();
            break;
            case 4:
                system("cls");
                float pre;
                cuadros2();
                gotoxy(50, 7);
                cout << "MODIFICAR PRODUCTO" <<endl;
                gotoxy(45, 10);
                cout << "INGRESE EL NUEVO PRECIO DE VENTA: " <<endl;
                cin >> pre;
                p.setPrecio(pre);
                gotoxy(45, 12);
                setBackgroundColor(GREEN);
                cout << "PRECIO MODIFICADO CORRECTAMENTE"<< endl;
                setBackgroundColor(BLACK);
                getch ();
            break;
            case 0:
                return false;
            break;
            default:
            system ("cls");
                gotoxy(45, 12);
                setBackgroundColor(RED);
                cout << "\n\n\n\t\t\tOPCION INCORRECTA \n\n\n";
                setBackgroundColor(BLACK);
                system ("pause");
                return false;
            break;
        }
        getch();

        p.guardar(pos);
        modifico=true;
    }
    else modifico=false;

    return modifico;
}

bool agregar_Stock(){
    Producto p;
    int cod, pos, agregado, cantidad;
    cuadros2();
    gotoxy(50, 7);
    cout << "MODIFICAR STOCK" <<endl;
    gotoxy(41, 9);
    cout << "Ingrese el codigo de producto a agregar Stock: ";
    cin >> cod;

    pos=buscar_Producto(cod);
    if (pos>=0){
        p.leer(pos);

        if (p.getEstado()==false){
            gotoxy(45, 12);
            setBackgroundColor(RED);
            cout << "ATENCION!!! ESTE PRODUCTO FUE ELIMINADO CON ANTERIORIDAD." <<endl;
            setBackgroundColor(BLACK);
            getch();
            system ("cls");
            cuadros2();
            gotoxy(50, 7);
            cout << "MODIFICAR STOCK" <<endl;
        }
        gotoxy(43, 10);
        cout << "Detalles del producto:" <<endl;
        p.mostrar();
        getch();
        system ("cls");
        cuadros2();
        gotoxy(50, 7);
        cout << "MODIFICAR STOCK" <<endl;
        gotoxy(43, 10);
        cout << "INGRESE CANTIDAD DE STOCK A AGREGAR: ";
        cin >> cantidad;
        p.setStock(p.getStock()+cantidad);
        p.guardar(pos);
        agregado=true;
    }
    else agregado=false;

    return agregado;
    getch();
}

int buscar_Producto(int codigo){
    Producto p;
    int i=0;
    while (p.leer(i)){
        if (p.getID()==codigo){
            return i;
        }
        i++;
    }
    return -1;
}

bool eliminar_Producto(){
    Producto p;
    int cod, pos, elimino;
    cuadros2();
    gotoxy(50, 7);
    cout << "ELIMINAR PRODUCTO" <<endl;
    gotoxy(41, 9);
    cout << "Ingrese el codigo de producto a eliminar: ";
    cin >> cod;

    pos=buscar_Producto(cod);
    if (pos>=0){

        p.leer(pos);
        gotoxy(50, 12);
        cout << "Producto a eliminar: " << endl;
        p.mostrar();
        getch();
        system("cls");
        cuadros2();
        gotoxy(50, 7);
        cout << "ELIMINAR PRODUCTO" <<endl;
        gotoxy(40, 12);
        cout << "¿ Está seguro que desea eliminar este producto ?" ;
        gotoxy(40, 13);
        cout << "SI: 1    NO:   0   ";
        int opc;
        cin >>opc;
        if (opc==1){
        system ("cls");
        imagen_eliminando();
        gotoxy(40, 23);
        setBackgroundColor(GREEN);
        cout << "ELIMINADO CORRECTAMENTE" <<endl;
        setBackgroundColor(BLACK);
        getch();

        p.setEstado(false);
        p.guardar(pos);

        elimino=true;
        }
        else return false;
    }
    else elimino=false;

    return elimino;
}

bool cod_rep(int codigo){
    Producto p;
    int i=0;
    bool repetido=false;

    while (p.leer(i)){
        if (p.getID()==codigo){
            repetido=true;
        }
        i++;
    }
    return repetido;
}

bool nom_rep(char* nom){
    Producto p;
    int i=0;
    bool repetido=false;

    while (p.leer(i)){
        if (strcmp(p.getNombre(), nom)==0){
            repetido=true;
        }
        i++;
    }
    return repetido;
}

