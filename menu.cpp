#include <iostream>
#include "dibujo.h"
#include "menu.h"
#include "ventas.h"
#include "detalleVenta.h"
#include "reportes.h"
#include "productos.h"
#include "configuracion.h"
#include <cstdio>
#include <cstdlib>
#include "SOutil.h"
#include "rlutil.h"
using namespace rlutil;

using namespace std;

///VER DONDE CARGAR LOS DATOS DEL EMPLEADO PARA DESPUES CARGAR POR ID LAS VENTAS
/*  Listado de vendedores???
    Ordenados por apellido???*/
///SE PODRIA AGREGAR VENDEDOR DEL DIA???

void menuPrincipal(){
    while(true){
        system ("cls");
        cuadros();
        gotoxy(53, 7);
        cout << "¿QUE DESEAS HACER?" <<endl;
        gotoxy(39, 12);
        cout << "1 - VENTAS" << endl; ///FACTURAS. AGREGAR "IMPRIMIR COMPROBANTE" PARA ENVIAR AL CLIENTE POR MAIL
        gotoxy(39, 14);
        cout << "2 - PRODUCTOS Y STOCK" << endl; ///CARGAR TODOS LOS MENUES CON COSTO Y PRECIO DE VENTA. **LISTADO**
        gotoxy(39, 16);
        cout << "3 - REPORTES" << endl;
        gotoxy(39, 18);
        cout << "4 - CONFIGURACION" << endl;
        gotoxy(55, 23);
        cout << "0 - VOLVER" << endl;

        int pos;
        gotoxy(39, 20);
        cout << endl << "> ";
        cin >> pos;



        switch(pos){
            case 1:
                system ("cls");
                menuVentas();
            break;
            case 2:
                system ("cls");
                menuProducto();
            break;
            case 3:
                system ("cls");
                menuReportes();
            break;
            case 4:
                system ("cls");
                menuConfiguracion();
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

