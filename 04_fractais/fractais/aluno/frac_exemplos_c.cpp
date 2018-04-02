#include "lib/cpen.h"
#include <stdlib.h>

void linhac(int lado){

    if(lado < 5)
        return;
    pen_set_color(rand()%255, rand()%255, rand()%255);

    pen_walk(lado);
    pen_right(90);
    linhac(lado - 5);
}

void fractalc(){
    pen_open(800, 600);
    //coloca o pincel na posicao x 300 y 500
    pen_set_xy(50, 50);

    //faz o pincel apontar pra direita
    pen_set_heading(0);
    //se speed = 0 entao ele faz o mais rapido possivel
    //se foi a partir de 1 ele controla a velocidade
    pen_set_speed(30);
    linhac(500);
    //espera clicar no botao de fechar
    pen_wait();
    pen_close();
}

//int main(){
//    fractalc();
//    return 0;
//}

