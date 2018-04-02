#include <lib/pen.h>

void linha(Pen &p, int lado, int rotacao){
    if(lado < 1)
        return;
    p.setColor(rand()%255, rand()%255, rand()%255);

    p.walk(lado);
    p.right(90 * rotacao);
    linha(p, lado - 5, 1);

    p.setColor(rand()%255, rand()%255, rand()%255);
    linha(p, lado - 5, -1);
}

//metodo do embuar indo e voltando
void embuar(Pen& p, int lado){
    if(lado < 20)
        return;
    p.setColor(sf::Color::Green);
    p.walk(lado);
    p.right(90);
    embuar(p, lado - 10);

    p.setColor(sf::Color::Yellow);
    p.left(90);
    p.walk(-lado);
}

//metodo arvore feita de acordo com a frescuragem
void arvore(Pen& p, int lado){
    float ang = 35;
    float dec = 0.75;
    lado -= (rand() % 7 -3);
    if(lado < 10)
        return;
    p.setColor(sf::Color::Green);
    p.setThickness(5);
    p.walk(lado);
    p.right(ang);
    arvore(p, lado * dec);
    p.left(ang);
    arvore(p, lado * dec);
    p.left(ang);
    arvore(p, lado * dec);
    p.right(ang);
    //p.setColor(sf::Color::Blue);
    p.setThickness(4);
    p.walk(-lado);
    p.setColor(rand() %133, rand() %133, rand() %133);
}

//metodo dos triangulos
void triangulo(Pen& p, int lado){
    if(lado < 10)
        return ;
    for(int i = 0; i < 3; i++){
        p.walk(lado);
        p.left(120);
        triangulo(p, lado / 2);
    }
}

//metodo do palitinho, tentativa de fazer uma coisa e saiu outra legal
void palitinho(Pen& p, int lado){
    if(lado < 10)
        return;
    for(int i = 0; i < 5; i++){
        p.setColor(rand() %133, rand() %133, rand() %133);
        p.walk(lado);
        p.right(72);
        p.left(144);
        palitinho(p,lado / 5);

        //estrela
        p.walk(lado);
        p.left(144);
    }
}

//metodo floco de neve
void floco(Pen& p, int lado){
    if(lado < 3)
        return;
    //p.setColor(rand() %255, rand() %255,rand() %255 );
    p.walk(lado);
    p.right(72);
    p.walk(-lado);
    floco(p,lado / 3);

    p.walk(lado);
    p.right(72);
    p.walk(-lado);
    floco(p,lado / 3);

    p.walk(lado);
    p.right(72);
    p.walk(-lado);
    floco(p,lado / 3);

    p.walk(lado);
    p.right(72);
    p.walk(-lado);
    floco(p,lado / 3);

    p.walk(lado);
    p.right(72);
    p.walk(-lado);
    floco(p,lado / 3);
}

//metodo quadrado, nao deu muito certo mas fez alguns quadradros
void quadrado(Pen& p, int lado){
   if(lado < 4)
       return;
   for(int i = 0; i < 4; i++){
       p.walk(lado);
       p.right(90);
       quadrado(p, lado / 3);

   }
   p.walk(lado);
   //p.right(90);
   //quadrado(p, lado / 3);
}

//metodo do trigo
void trigo(Pen& p, int lado){
    if(lado < 0.1)
        return;
    for(int i = 0; i < 7; i++){
        p.walk(lado);
        p.right(45);
        trigo(p, lado / 5);
        p.left(90);
        trigo(p, lado / 5);
        p.right(45);
    }
    p.walk(-lado * 7);
}


void fractal(){
    Pen p(800, 600);
    //coloca o pincel na posicao x 300 y 500

    p.setXY(300, 400);
    //faz o pincel apontar pra direita

    p.setHeading(0);
    //se speed = 0 entao ele faz o mais rapido possivel
    //se foi a partir de 1 ele controla a velocidade

    p.setSpeed(30);
    //p.circle(200);
   // linha(p, 100, -1);
    int lado = 300;


    //embuar(p, lado);
    //arvore(p, lado);
    //triangulo(p,lado);
    //palitinho(p,lado);
    //floco(p,lado);
    //quadrado(p,lado);
    //trigo(p, lado);


    //espera clicar no botao de fechar
    p.wait();
}

int main(){
    fractal();
    return 0;
}
