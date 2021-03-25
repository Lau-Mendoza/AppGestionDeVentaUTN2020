#ifndef DETALLEVENTA_H_INCLUDED
#define DETALLEVENTA_H_INCLUDED

///    ----- FACTURA -----
class DetalleVenta{
    private:

        int IDventa;
        int IDproducto;
        float precio;
        int cantidad;
        //PRECIO


    public:
        DetalleVenta();

        //Venta getVenta();

        void setIDventa(int);
        void setIDproducto(int);
        void setCantidad (int);
        void setPrecio (float);

        int getIdVenta();
        int getIDproducto();
        int getCantidad();
        float getPrecio();

        bool cargar();
        void mostrar();
        bool guardar();
        bool leer(int);

};


float buscar_precio(int );
bool verif_codprod (int , int);
int CodVenta();

int buscar_Detalle(int);
void listar_detalle();
void listar_detalles();






#endif // DETALLEVENTA_H_INCLUDED
