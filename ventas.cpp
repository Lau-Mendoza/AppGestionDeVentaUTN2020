#include <iostream>
#include <ctime>
#include "fecha.h"
#include "ventas.h"
#include "detalleVenta.h"
#include "productos.h"
#include "dibujo.h"
#include <vector>
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

const char * FILE_VENTAS ("Datos/ventas.dat");

void Venta::setID(int i){
    ID=i;
}
void Venta::setLocalidad (char * l){
    strcpy(localidad, l);
}
void Venta::setMesa(int m){
    mesa=m;
}
void Venta::setFechaVenta(Fecha f){
    fechaVenta=f;
}
void Venta::setIdVendedor(int iv){
    idVendedor=iv;
}
void Venta::setFormaPago(char *fp){
    strcpy(formaPago,fp);
}
void Venta::setTotal(float t){
    total=t;
}
void Venta::setTotalCosto(float tc){
    totalCosto=tc;
}
void Venta::setEntregado(bool e){
    entregado=e;
}
void Venta::setEstado(bool es){
    estado=es;
}

Venta::Venta(){
    ID=IDventa();
    strcpy(localidad, "");
    mesa=0;
    idVendedor=0;
    strcpy(formaPago, "");
    total=0;
    entregado=0;
    estado=1;
}

int Venta::getID(){
    return ID;
}
char * Venta::getLocalidad (){
    return localidad;
}
int Venta::getMesa(){
    return mesa;
}
Fecha Venta::getFechaVenta(){
    return fechaVenta;
}
int Venta::getIdVendedor(){
    return idVendedor;
}
char * Venta::getFormaPago(){
    return formaPago;
}
float Venta::getTotal(){
    return total;
}
float Venta::getTotalCosto(){
    return totalCosto;
}
bool Venta::getEntregado(){
    return entregado;
}
bool Venta::getEstado(){
    return estado;
}

bool Venta::cargar(){
    system ("cls");
    cuadros2();
    gotoxy(52, 7);
    cout << "CARGAR UN PEDIDO";
    //fechaVenta.cargar();
    Fecha fechaVenta;
    gotoxy(39, 10);
    cout << "FECHA: ";
    fechaVenta.mostrar();
    gotoxy(39, 12);
    cout << "Localidad / Evento";
    gotoxy(39, 13);
    cout << "(INGRESAR TODO EN MAYUSCULAS): " ;
    cin.ignore();
    cin.getline(localidad, 50);
    gotoxy(39, 15);
    cout << "Mesa              : " ;
    cin >>mesa;
    while (mesa<1){
        setBackgroundColor(RED);
        gotoxy(39, 15);
        cout << "MESA MAL INGRESADA VUELVA A INGRESAR: " ;
        setBackgroundColor(BLACK);
        cin >>mesa;
    }
    //cout << "Codigo de vendedor: " ;
    //cin >> idVendedor;
    gotoxy(39, 17);
    cout << "Forma de pago     (E/TC/MP): " ;
    cin >> formaPago;
    while ((strcmp(formaPago, "E") !=0) && (strcmp(formaPago, "TC")!=0) && (strcmp(formaPago, "MP")!=0)){
        gotoxy(39, 17);
        setBackgroundColor(RED);
        cout << "FORMA DE PAGO MAL INGRESADO VUELVA A INGRESAR: " ;
        setBackgroundColor(BLACK);
        cin >>formaPago;
    }

    return true;
}
bool Venta::guardar(){
    bool guardo;
    FILE *p = fopen (FILE_VENTAS, "ab");
    if (p==NULL) return false;

    guardo = fwrite(this, sizeof(Venta), 1, p);
    fclose(p);

    return guardo;
}
bool Venta::guardar(int pos){
    bool guardo;
    if (pos>=0){
        FILE *p = fopen (FILE_VENTAS, "rb+");
        if (p==NULL) return false;
        fseek (p, pos* sizeof(Venta), SEEK_SET);
        guardo = fwrite(this, sizeof(Venta), 1, p);
        fclose(p);
    }
    else {
        guardo = false;
    }
    return guardo;
}
void Venta::mostrar(){

    cout <<setw(30) << "" << "Fecha              : ";
    fechaVenta.mostrar();
    cout << endl;
    cout <<setw(30) << "" << "ID de venta        : " <<ID <<endl;
    cout <<setw(30) << "" << "Localidad          : " <<localidad <<endl;
    cout <<setw(30) << "" << "Mesa               : " <<mesa <<endl;
    //cout << "Codigo de vendedor : " <<idVendedor <<endl;
    cout <<setw(30) << "" << "Forma de pago      : " <<formaPago <<endl;
    cout <<setw(30) << "" << "TOTAL              : $" <<total <<endl;
    cout <<setw(30) << "" << "Estado             : " <<estado <<endl;

    //cout << "Entregado:         : " <<entregado <<endl;

    getch();

}
bool Venta::leer(int pos){
    bool leer;
    if (pos>=0){

        FILE *p = fopen(FILE_VENTAS, "rb");
        if (p==NULL) return false;

        fseek(p, pos* sizeof(Venta), SEEK_SET);
        leer = fread (this, sizeof(Venta), 1, p);
        fclose(p);
    }
    else leer = false;

    return leer;
}
bool eliminar_Venta(){

    Venta v;
    DetalleVenta dv;
    int cod, pos;
    bool elimino;
    cuadros2();
    gotoxy(52, 7);
    cout << "ELIMINAR VENTA";
    gotoxy(39, 10);
    cout << "Ingrese el codigo de Venta a eliminar/Cancelar: " << endl;
    cin >> cod;

    pos=buscar_Venta(cod);

    if (pos>=0){
        /*int verif, verifUsuario;
        verif= 1 + rand()%(1000);
        */

        v.leer(pos);
        gotoxy(39, 11);
        cout << "Venta a eliminar/Cancelar: " << endl;
        v.mostrar();

        FILE *p = fopen("Datos/detalleVentas.dat", "rb");
        if (p==NULL) return false;
        while (fread(&dv, sizeof(DetalleVenta), 1, p)){
            if (v.getID()==dv.getIdVenta()){
                dv.mostrar();
            }
        }
        fclose(p);
        getch();
        system ("cls");
        cuadros2();
        gotoxy(52, 7);
        cout << "ELIMINAR VENTA";
        gotoxy(39, 10);
        cout << "¿ Está seguro que desea eliminar esta venta ?";
        gotoxy(40, 15);
        cout << "SI: 1    NO:   0";
        int opc;
        cin >>opc;
        if (opc==1){
        system ("cls");
        imagen_eliminando();
        setBackgroundColor(GREEN);
        cout << "\n\n\n\t\t\t ELIMINADA CORRECTAMENTE\n\n\n" <<endl;
        setBackgroundColor(BLACK);
        getch();

        v.setEstado(false);
        v.guardar(pos);

        elimino=true;
        }
        else{
            setBackgroundColor(GREEN);
            cout << "\n\n\n\t\t\t NO SE ELIMINO\n\n\n" <<endl;
            setBackgroundColor(BLACK);
            return false;
        }
    }
    else {
        gotoxy(39, 15);
        setBackgroundColor(RED);
        cout << "NO EXISTE LA VENTA" <<endl;
        setBackgroundColor(BLACK);
        elimino=false;
    }
    getch();
    return elimino;

}

bool nueva_Venta(){
    Venta v;
    DetalleVenta aux;
    vector <DetalleVenta> vecDV;
    float importeTotal=0, importeCostos=0;
    Producto pr;
    int opc=-1, opc2, opc3, pos;
    bool b;
    if (v.cargar()){
        do {
            if (aux.cargar()){
                importeTotal+=totalDetalle(aux.getIDproducto(), aux.getCantidad());
                importeCostos+=calcularTotalCostos(aux.getIDproducto(), aux.getCantidad());
                aux.setIDventa(v.getID());
                aux.setPrecio(buscar_precio(aux.getIDproducto()));
                vecDV.push_back(aux);
                system("cls");
                cuadros2();
                gotoxy(52, 7);
                cout << "CARGAR UN PEDIDO";
                gotoxy(39, 10);
                cout << "Cargar más?  SI: 1    NO: 0    ";
                cin >> opc;
            }
            else{
                b=false;
                return b;
            }
        }while(opc==1);
        system("cls");
        cuadros2();
        gotoxy(52, 7);
        cout << "CARGAR UN PEDIDO";
        gotoxy(39, 10);
        cout << "CONFIRMAR VENTA? si: 1     no: 0  ";
        cin >> opc2;
        if (opc2==1){
            v.setTotal(importeTotal);
            v.setTotalCosto(importeCostos);
            v.guardar();
            for(unsigned int i=0; i<vecDV.size(); i++){
                vecDV.at(i).guardar();
                pos=buscar_Producto(vecDV.at(i).getIDproducto());
                pr.leer(pos);
                pr.setStock(pr.getStock()-vecDV.at(i).getCantidad());
                pr.guardar(pos);
            }
            b=true;
            gotoxy(39, 28);
            setBackgroundColor(GREEN);
            cout << "VENTA GUARDADA CORRECTAMENTE" << endl;
            setBackgroundColor(BLACK);

        }
        else {
            gotoxy(41, 12);
            cout<< "CANCELAR VENTA? si: 1     no: 0"<< endl;
            cin >> opc3;
            if (opc3==1){
                b=false;
                setBackgroundColor(GREEN);
                gotoxy(43, 15);
                cout << "VENTA CANCELADA" << endl;
                setBackgroundColor(BLACK);
            }
            else{
                setBackgroundColor(RED);
                gotoxy(42, 15);
                cout << "VUELVA A CARGAR DE NUEVO";
            }
            setBackgroundColor(BLACK);
            b= false;
        }
    }
    else b= false;

    getch();

    return b;
}
float calcularTotalCostos(int id_prod, int cant){
    Producto pr;
    float total;
    int pos=buscar_Producto(id_prod);
    pr.leer(pos);
    total=pr.getCosto()*cant;
    return total;
}
float totalDetalle(int id_prod, int cant){
    Producto pr;
    float total;
    int pos=buscar_Producto(id_prod);
    pr.leer(pos);
    total=pr.getPrecio()*cant;
    return total;
}

int buscar_Venta(int cod){
    Venta v;
    int i=0;
    while (v.leer(i)){
        if (v.getID()==cod){
            return i;
        }
        i++;
    }
    return -1;
}

bool modificar_Venta(int){

    Venta v;
    int cod, pos, modifico;
    cout << "Ingrese el codigo de venta a modificar: " << endl;
    cin >> cod;

    pos=buscar_Venta(cod);
    if (pos>=0){
        v.leer(pos);

        if (v.getEstado()==false){
            cout << "\t\t  ATENCION!!! ESTA VENTA FUE ELIMINADA CON ANTERIORIDAD. \n\n" <<endl;
        }

        cout << "Detalles de la venta:" <<endl;
        v.mostrar();
        ///ACA HAY QUE MOSTRAR TAMBIEN EL DETALLE DE VENTA.
        cout << "\n\n";

        cout << "INGRESE LOS NUEVOS DATOS DE LA VENTA: " <<endl<<endl;
        getch();
        v.cargar();
        ///CARGAR DETALLE
        v.guardar(pos);
        modifico=true;
    }
    else modifico=false;

    return modifico;
}

bool listar_Venta(){
    Venta v;
    DetalleVenta dv;
    int cod, pos, pos2;
    bool listo;
    cuadrosLista();
    gotoxy(45, 5);
    cout << "VENTA POR ID";
    gotoxy(45, 7);
    cout << "Ingrese el codigo de venta que desea ver: ";
    cin >> cod;

    pos=buscar_Venta(cod);
    pos2=buscar_Detalle(cod);

    cout <<endl <<endl;
    if (pos>=0 && pos2>=0){
        v.leer(pos);
        v.mostrar();

        FILE *p = fopen("Datos/detalleVentas.dat", "rb");
        if (p==NULL) return false;
        while (fread(&dv, sizeof(DetalleVenta), 1, p)){
            if (v.getID()==dv.getIdVenta()){
                dv.mostrar();
            }
        }
        fclose(p);
        //cout << "TOTAL          :" << v.getTotal() <<endl;
        system ("pause");
        listo=true;
    }
    else {
        gotoxy(45, 9);
        setBackgroundColor(RED);
        cout << "NO SE ENCONTRO EL CODIGO DE VENTA" <<endl;
        setBackgroundColor(BLACK);
        listo = false;
        system ("pause");
    }
    return listo;
}

int IDventa(){
    int cant=0;
    cant=contar_ventas();
    if (cant==-1) return 1;
    else return cant=contar_ventas()+1;
}

int contar_ventas(){
    int cantReg;
    FILE *p=fopen(FILE_VENTAS, "rb");
    if(p==NULL) return -1;
    fseek(p,0,2);
    cantReg=ftell(p)/sizeof(Venta);
    fclose(p);
    return cantReg;
}

bool listar_Ventas(){
    Venta v;
    DetalleVenta dv;
    int i=0, sleep100=100;

    cuadrosLista();
    gotoxy(45, 5);
    cout << "LISTADO VENTAS"<<endl;

    cout <<endl <<endl;
    while (v.leer(i++)){
        v.mostrar();

        FILE *p = fopen("Datos/detalleVentas.dat", "rb");
        if (p==NULL) return false;

        while (fread(&dv, sizeof(DetalleVenta), 1, p)){
            if (v.getID()==dv.getIdVenta()){
                dv.mostrar();
            }
        }
        cout << endl << endl;
        fclose(p);
        //cout << "TOTAL          : " << v.getTotal() <<endl <<endl;
        Sleep(sleep100);
    }
    setBackgroundColor(GREEN);
    cout << endl << "FIN DEL LISTADO " <<endl;
    setBackgroundColor(BLACK);
    getch();
    return true;
}
void comandasActuales(){
    Venta v;
    DetalleVenta dv;
    Fecha f;
    float recauda=0;
    int i=0, sleep100=100;
    bool bandera=false;

    cuadrosLista();
    gotoxy(45, 5);
    cout << "COMANDAS ACTUALES"<<endl;

    while (v.leer(i++)){
        if ((v.getFechaVenta().getAnio()==f.getAnio())&&(v.getFechaVenta().getMes()==f.getMes())&&(v.getFechaVenta().getDia()==f.getDia())){
            recauda+=v.getTotal();
            bandera=true;
            cout << endl << endl ;
            v.mostrar();

            FILE *p = fopen("Datos/detalleVentas.dat", "rb");
            if (p==NULL) return;

            while (fread(&dv, sizeof(DetalleVenta), 1, p)){
                if (v.getID()==dv.getIdVenta()){
                    dv.mostrar();
                }
            }
            cout << endl;
            fclose(p);
            //gotoxy(40, 14+contador);
            //cout << "TOTAL          : " << v.getTotal() <<endl <<endl;
            Sleep(sleep100);
        }

    }
    if (bandera==true){
        cout << "\n\n\n\nFIN DEL LISTADO " <<endl;
        setBackgroundColor(LIGHTGREEN);
        setColor(BLACK);
        cout << "RECAUDACIÓN TOTAL DE HOY: $" << recauda;
        setBackgroundColor(BLACK);
        cout << endl;
        setColor(WHITE);
    }
    else{
        setBackgroundColor(RED);
        gotoxy(35, 15);
        cout << "Todavia no hay ventas en el dia de la fecha" <<endl;
        setBackgroundColor(BLACK);
    }
    getch();
}

DetalleVenta Venta::getDetalle(){
    DetalleVenta dv;
    int pos;

    pos=buscar_Detalle(ID);

    if (pos > 0){
        dv.leer(pos);
    }

    return dv;

}

void menuVentas(){
    while(true){
        system ("cls");
        cuadros();
        gotoxy(50, 7);
        cout << "MENU DE COMANDAS / VENTAS" <<endl;
        gotoxy(39, 11);
        cout << "1 - CARGAR PEDIDO" << endl;
        ///Las ventas serán almacenadas registrando su Vendedor/Mesero, Tipo, Id, cliente, monto, mesa, Localidad.
        gotoxy(39, 13);
        cout << "2 - VER COMANDAS ACTUALES" << endl;
        gotoxy(39, 15);
        cout << "3 - BUSCAR VENTA POR FACTURA" << endl;
        gotoxy(39, 17);
        cout << "4 - VER TODAS LAS VENTAS" << endl;
        gotoxy(39, 19);
        cout << "5 - CANCELAR VENTA" << endl;
        gotoxy(55, 23);
        cout << "0 - VOLVER " << endl;
        int pos;
        cout << endl << "> ";
        cin >> pos;

        switch(pos){
            case 1:
                system("cls");
                if (nueva_Venta()==false){
                    setBackgroundColor(RED);
                    cout << "NO SE PUDO GUARDAR LA VENTA"<< endl;
                    setBackgroundColor(BLACK);
                }
                getch ();
            break;
            case 2:
                system("cls");
                comandasActuales(); //lista solo el menu, la mesa, el importe, el vendedor.
            break;
            case 3:
                system("cls");
                listar_Venta();
            break;
            case 4:
                system("cls");
                listar_Ventas();
            break;
            case 5:
                system("cls");
                if (eliminar_Venta()== false) return;
            break;
            case 6:
                system("cls");
                ///reporteComandas();
            break;
            case 0:
                return;
            break;
            default:
            system ("cls");
                setBackgroundColor(RED);
                cout << "\t\t\tOPCION INCORRECTA \n\n\n";
                system ("pause");
                setBackgroundColor(BLACK);
                return;
            break;
        }
    }

}

