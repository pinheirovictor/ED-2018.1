#include <iostream>
#include <list>

using namespace std;

//metodo prencher a lista
void preencherLista(list<int>& participantes,int qtd){
    for(int i = 0; i < qtd; i++){
        participantes.push_back(i + 1);
    }
}

//metodo mostrar a lista
void mostarLista(list<int> lista){
    for(auto elemento : lista){
        cout << elemento;
    }
    cout << "\n";
}

int main(){
    int qtd = 0;
    int escolhido = 0;
    int salto = 0;

    cout << "Numero total de participantes: ";
    cin >> qtd;

    cout << "Participante inicial: ";
    cin >> escolhido;

    cout << "Número de saltos: ";
    cin >> salto;

    list<int> participantes;

    preencherLista(participantes,qtd);

    mostarLista(participantes);

    while(participantes.front() != escolhido){

        participantes.push_back(participantes.front());
        participantes.pop_front();
    }

    while(participantes.size() > 1){
        while(salto > 0 ){
            participantes.push_back(participantes.front());
            participantes.pop_front();
            salto--;
        }
            participantes.pop_front();
            mostarLista(participantes);
    }
    return 0;
}

