#include "pen.h"
#include <iostream>
using namespace std;

//Inicializando os membros estaticos
vector <sfLine> Pen::tracos;
int Pen::init = 0;

void Pen::make_y_path(Vector2f a, Vector2f b, vector<Vector2f> &path)
{
    double x, y = a.y;
    double d=(b.x - a.x)/(b.y - a.y);
    while(1)//controle de parada e incremento no corpo do laco
    {
        x = a.x + (d*(y - a.y));
        //fn(x, y, param);
        path.push_back(Vector2f(x, y));

        if(a.y < b.y)
        {
            if(y >= b.y)
                return;
            y++;
        }
        if(a.y > b.y)
        {
            if(y <= b.y)
                return;
            y--;
        }
    }
}

void Pen::make_x_path(Vector2f a, Vector2f b, vector<Vector2f> &path)
{
    double x = a.x, y;
    double d=(b.y - a.y)/(b.x - a.x);
    while(1)
    {
        y = a.y + (d*(x - a.x));
        //fn(x, y, param);
        path.push_back(Vector2f(x, y));

        if(a.x < b.x)
        {
            if(x >= b.x)
                return;
            x++;
        }
        if(a.x > b.x)
        {
            if(x <= b.x)
                return;
            x--;
        }
    }
}

vector<Vector2f> Pen::make_path(Vector2f a, Vector2f b)
{
    vector<Vector2f> path;
    if(a.x == b.x && a.y == b.y){
        path.push_back(Vector2f(a.x, a.y));
        return path;
    }

    if( fabs(a.x - b.x) > fabs(a.y - b.y) )
        make_x_path(a, b, path);
    else
        make_y_path(a, b, path);
    return path;
}

void Pen::processarEventos(){
    sf::Event event;
    while (janela->pollEvent(event))
    {
        // Request for closing the window
        if (event.type == sf::Event::Closed)
            janela->close();
        if(event.type == sf::Event::Resized)
            janela->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
    }
}

int Pen::rand(){
    static int init = 1;
    if(init == 1){
        init = 0;
        std::srand(time(NULL));
    }
    return std::rand();
}

Pen::Pen(int largura, int altura):
    pos(largura/2, altura/2)
{
    if(init == 0){
        init = 1;
        janela = new RenderWindow();
        janela->create(VideoMode(largura, altura), "Pintor");
        janela->setFramerateLimit(FRAMERATE);

        janela->clear(backGroundColor);
    }
}

//desabilitando construtor de copia
Pen::Pen(const Pen &other):
    pos(other.pos),
    heading(other.heading),
    isDown(other.isDown),
    color(other.color),
    thickness(other.thickness),
    speed(other.speed)
{ }

Pen::~Pen(){delete janela;}


void Pen::move(double x, double y){
    vector<Vector2f> path = make_path(pos, Vector2f(x, y));
    static long cont = 0;

    //atualiza a posicao do pincel
    pos.x = x;
    pos.y = y;

    //se ele nao esta abaixado entao podemos sair
    if(!isDown)
        return;

    //se ele esta abaixado vamos adicionar linhas ao desenho
    tracos.push_back(sfLine(path.front(), path.back(), this->thickness, this->color));
    if(speed > 0){
        for (size_t i = 0; i < path.size() - 1; i++, cont++){

           this->processarEventos();

            //drawPoint(Vector2i(path[i].x, path[i].y), thickness);
            tracos.back().setEnd(path[i]);
            //redesenha so o ultimo traco
            janela->draw(tracos.back());
            if(cont % speed == 0){
                janela->display();
            }

            //reprintando tudo
            if(clock.getElapsedTime() > sf::milliseconds(500)){
                clock.restart();
                janela->clear(backGroundColor);
                for(const auto& elem : tracos){
                    janela->draw(elem);
                }
                janela->display();
            }
        }

    }
}

void Pen::walk(double distance){
    double x = pos.x + distance * std::cos(heading * M_PI/180);
    double y = pos.y - distance * std::sin(heading * M_PI/180);
    move(x, y);
}

void Pen::rotate(double angulo){
    heading -= angulo;
}

void Pen::wait(int seconds){
    sf::sleep(sf::milliseconds(seconds * 1000));
}

void Pen::wait(){

    while(janela->isOpen()){
        processarEventos();
        janela->clear(backGroundColor);
        for(const auto& elem : tracos){
            janela->draw(elem);
        }
        janela->display();
        sf::sleep(sf::milliseconds(100));
    }
}

void Pen::setColor(sf::Color color)
{
    this->color = color;
}

void Pen::setColor(int R, int G, int B){
    color = Color(R, G, B);
}

void Pen::circle(double radius) {
    if(isDown) {
        register unsigned int i;
        unsigned int discretization = (unsigned int)
                std::max(200*radius/std::max(janela->getSize().x, janela->getSize().y), 15.0);
        double angle, step_angle = 2*M_PI/discretization;

        Vector2f center_pos = pos;
        double head = this->heading;
        pos.x += radius;

        // Calculando os pontos
        for(i = 0, angle = step_angle; i < discretization; ++i, angle += step_angle) {
            double next_x, next_y;

            // y subtrai, por conta das coordenadas y da janela
            next_x = center_pos.x + cos(angle)*radius;
            next_y = center_pos.y - sin(angle)*radius;

            move(next_x, next_y);
        }

        pos = center_pos;
        this->heading = head;
    }
}
