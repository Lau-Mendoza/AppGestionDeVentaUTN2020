#ifndef VENTAS_H_INCLUDED
#define VENTAS_H_INCLUDED

#include "detalleVenta.h"
#include "fecha.h"

class Venta{
    private:
        int ID;
        char localidad [50];
        int mesa;
        Fecha fechaVenta;
        int idVendedor;
        char formaPago[50];
        float total;
        float totalCosto;
        bool entregado;
        bool estado;

    public:
        Venta();

        DetalleVenta getDetalle();

        void setID(int);
        void setLocalidad (char *);
        void setMesa(int);
        void setFechaVenta(Fecha);
        void setIdVendedor(int);
        void setFormaPago(char *);
        void setTotal (float);
        void setTotalCosto (float);
        void setEntregado(bool);
        void setEstado(bool);

        int getID();
        char * getLocalidad ();
        int getMesa();
        Fecha getFechaVenta();
        int getIdVendedor();
        char * getFormaPago();
        float getTotal();
        float getTotalCosto();
        bool getEntregado();
        bool getEstado();

        bool cargar();
        bool guardar();
        bool guardar(int);
        void mostrar();
        bool leer(int);
        bool buscar();
        bool eliminar(int);


};

void menuVentas();

bool nueva_Venta();
int buscar_Venta(int );

bool eliminar_Venta();
bool listar_Venta();
bool listar_Ventas();
bool modificar_Venta();
int IDventa();
int contar_ventas();
float totalDetalle(int , int);
float calcularTotalCostos (int , int);
void comandasActuales();

#endif // VENTAS_H_INCLUDED
