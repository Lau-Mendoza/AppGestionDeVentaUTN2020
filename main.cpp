#include <iostream>
#include <conio.h>
#include <fstream>
#include "SOutil.h"
#include "rlutil.h"
using namespace rlutil;

#include "menu.h"
#include "fecha.h"
#include "dibujo.h"

#include <clocale>

using namespace std;

int main(){
    //getch();
    setlocale(LC_ALL, "");
    initUI();
    imagen_bienvenida();
    setColor(WHITE);
    menuPrincipal();


    return 0;
}
