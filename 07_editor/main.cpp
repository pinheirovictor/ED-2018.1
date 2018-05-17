#include <iostream>
#include <list>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "sftext.h"

using namespace std;

struct Ambiente{
    list<char> texto;
    list<char>::iterator cursor;
    Ambiente(){
    cursor = texto.end();
    }

    string toString(){
        stringstream ss;
        for(auto it = texto.begin(); it != texto.end(); it++){
            if(it == cursor)
                ss << "|";
            ss << (*it);
        }
        if(cursor == texto.end())
            ss << "|";
        return ss.str();
    }

};

struct Amb{
    list<Ambiente> ambiente;
    list<Ambiente>::iterator cursorAmbiente;
};


int main(){

    Amb controlZR;
    Ambiente amb;
    amb.texto.push_back('E');
    amb.texto.push_back('D');
    amb.texto.push_back('I');
    amb.texto.push_back('T');
    amb.texto.push_back('O');
    amb.texto.push_back('R');
    amb.texto.push_back(' ');
    amb.texto.push_back('W');
    amb.texto.push_back('R');
    amb.texto.push_back('I');
    amb.texto.push_back('T');
    amb.texto.push_back('E');
    amb.texto.push_back('\n');

    sf::RenderWindow janela(sf::VideoMode(800, 600), "Janela");
    while(janela.isOpen()){

        sf::Event event;

        while(janela.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                janela.close();
            if(event.type == sf::Event::KeyPressed){
                if(event.key.control && event.key.code == sf::Keyboard::Z){
                        cout << "control z" << endl;
                        //implementar

                }
                else if(event.key.control && event.key.code == sf::Keyboard::R){
                        cout << "control r" << endl;
                       //implementar

                }
                else if((event.key.code >= sf::Keyboard::A) && (event.key.code <= sf::Keyboard::Z)){
                    char tecla = (event.key.code - sf::Keyboard::A) + 'a';
                    cout << tecla << endl;
                    amb.texto.insert(amb.cursor, tecla);
                }
                else if((event.key.code == sf::Keyboard::Space)){
                    cout << "espaco" << endl;
                    amb.texto.insert(amb.cursor, ' ');
                }
                else if((event.key.code == sf::Keyboard::Return)){
                    cout << "espaco" << endl;
                    amb.texto.insert(amb.cursor, '\n');
                }
                else if(event.key.code == sf::Keyboard::BackSpace){
                    cout << "backspace" << endl;
                    if(amb.cursor != amb.texto.begin())
                    amb.texto.erase(amb.cursor++, amb.cursor--);
                }
                else if(event.key.code == sf::Keyboard::Delete){
                    cout << "delete" << endl;
                    if(amb.cursor != amb.texto.end())
                    amb.texto.erase(amb.cursor++);
                }
                else if(event.key.code == sf::Keyboard::Left){
                    amb.cursor--;
                }
                else if(event.key.code == sf::Keyboard::Right){
                    amb.cursor++;
                }
                else if(event.key.code == sf::Keyboard::Escape){
                    janela.close();
                }
            }
        }
        auto pos = sf::Vector2f(30, 50);
        janela.clear();
        janela.draw(sfText(pos, amb.toString(), sf::Color::Green, 30));
        janela.display();
    }
    return 0;
}
