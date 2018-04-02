#include "cpen.h"

#include "pen.h"

static Pen *spen;

void pen_open(int largura, int altura){
    spen = new Pen(largura, altura);
}


void pen_walk(float distance){
    spen->walk(distance);
}


void pen_close(){
    delete(spen);
}


void pen_left(float angulo) {
    spen->rotate(-angulo);
}


void pen_right(float angulo){
    spen->rotate(angulo);
}


void pen_move(float x, float y){
    spen->move(x, y);
}


void pen_wait(int seconds){
    spen->wait(seconds);
}


void pen_wait(){
    spen->wait();
}


void pen_set_color(int R, int G, int B){
    spen->setColor(R, G, B);
}


void pen_set_back_color(int R, int G, int B){
    spen->setBackColor(R, G, B);
}


void pen_clear(){
    spen->clear();
}


void pen_up(){
    spen->up();
}


void pen_down(){
    spen->down();
}


void pen_set_xy(float x, float y){
    spen->setXY(x, y);
}


void pen_set_heading(float angulo){
    spen->setHeading(angulo);
}


void pen_set_speed(int velocidade){
    spen->setSpeed(velocidade);
}


void pen_set_thickness(int espessura){
    spen->setThickness(espessura);
}


float pen_get_x(){
    return spen->getX();
}


float pen_get_y(){
    return spen->getY();
}


int pen_get_speed(){
    return spen->getSpeed();
}


float pen_get_heading(){
    return spen->getHeading();
}


int pen_get_thickness(){
    return spen->getThickness();
}

void pen_circle(float radius){
    spen->circle(radius);
}
