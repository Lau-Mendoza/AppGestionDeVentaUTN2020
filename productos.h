#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED

class Producto{
    private:
        int ID;
        char nombre[50];
        float costo;
        float precio;
        float stock;
        bool estado;

    public:
        Producto();
        void setID(int);
        void setNombre(char *);
        void setCosto (float);
        void setPrecio (float);
        void setStock (float);
        void setEstado(bool);
        int getID();
        char* getNombre();
        float getCosto();
        float getPrecio();
        float getStock();
        bool getEstado();
        bool cargar();
        bool guardar();
        bool guardar(int);
        bool mostrar();
        bool leer(int);
};

void menuProducto();

bool nuevo_Producto();
void listar_Productos();
bool listar_Producto();
bool modificar_Producto();
bool agregar_Stock();
bool eliminar_Producto();
int buscar_Producto(int);

bool cod_rep(int);
bool nom_rep(char *);


#endif // PRODUCTOS_H_INCLUDED
