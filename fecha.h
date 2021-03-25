#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

class Fecha{
    private:
    int dia, mes, anio;
    public:
        Fecha();
        int getDia();
        int getMes();
        int getAnio();
        void setDia(int);
        void setMes(int);
        void setAnio(int);
        void mostrar();
        bool cargar();
        bool cargarReporteMes();
        bool cargarReporteAnio();
};

#endif // FECHA_H_INCLUDED
