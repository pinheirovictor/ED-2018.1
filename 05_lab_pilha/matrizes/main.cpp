#include "libs/ed_base.h"
#include "libs/ed_mat.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <algorithm> //random_shuffle
#include <cstdlib>
#include <ctime>

using namespace std;

const char PAREDE = 'k';
const char ABERTO = 'w';
const char EMBUSCA = 'y';
const char CAMINHO = 'b';
const char ABATIDO = 'm';


void showMat(matchar& mat, vector<Par> pilha, Par inicio, Par fim){
    mat_draw(mat);
    for(Par par : pilha)
        mat_focus(par, 'c');
    if(pilha.size() > 0)
        mat_focus(pilha.back(), 'k');
    mat_focus(inicio, 'g');
    mat_focus(fim, 'r');
}

//metodo mostar matriz
//mesmo showmat
void mostrarMatriz(matchar& matriz, vector<Par> pilha, Par inicio, Par final){
    mat_draw(matriz);
    for(Par par : pilha)
        mat_focus(par, 'c');

    if(pilha.size() > 0)
        mat_focus(pilha.back(), 'k');
    mat_focus(inicio, 'g');
    mat_focus(final, 'r');
}

//metodo pegar vizinhos
//mesmo getNeib
vector<Par> buscaVizinhos(Par par){
    vector<Par> vizinhos;
    vizinhos.push_back(Par(par.l + 1, par.c));
    vizinhos.push_back(Par(par.l - 1, par.c));
    vizinhos.push_back(Par(par.l, par.c + 1));
    vizinhos.push_back(Par(par.l, par.c - 1));
    return vizinhos;
}

vector<Par> getNeib(Par par){
    vector<Par> vizinhos;
    vizinhos.push_back(Par(par.l + 1, par.c));
    vizinhos.push_back(Par(par.l - 1, par.c));
    vizinhos.push_back(Par(par.l, par.c + 1));
    vizinhos.push_back(Par(par.l, par.c - 1));
    return vizinhos;
}

//metodo contar vizinhos abertos apar serem furados
//mesmo countOpen
int contarVizinhosAbertos(matchar &matriz, Par par){
    int contador = 0;
    for(auto vizinho : buscaVizinhos(par))
        if(matriz.is_inside(vizinho) || matriz.get(vizinho) != PAREDE)
            contador++;
    return contador;
}

int countOpen(matchar &mat, Par par){
    int cont = 0;
    for(auto vizinho : getNeib(par))
        if(!mat.is_inside(vizinho) || mat.get(vizinho) != PAREDE)
            cont++;
    return cont;
}

//metodo embaralhar
//mesmo suffle
vector<Par> embaralhar(vector<Par> vetor){
    std::random_shuffle(vetor.begin(), vetor.end());
    return vetor;
}

vector<Par> shuffle(vector<Par> vet){
    std::random_shuffle(vet.begin(), vet.end());
    return vet;
}

//metodo furar vizinho aberto
//mesmo furar
void furarAberto(matchar &matriz, Par par){
    if(!matriz.equals(par, PAREDE || contarVizinhosAbertos(matriz, par) > 1))
        return;
    matriz.get(par) = ABERTO;
    for(Par vizinho : embaralhar(buscaVizinhos(par)))
        furarAberto(matriz, vizinho);
}

void furar(matchar &mat, Par par){
    if(!mat.equals(par, PAREDE) || countOpen(mat, par) > 1)
        return;
    mat.get(par) = ABERTO;
    for(Par vizinho : shuffle(getNeib(par)))
        furar(mat, vizinho);
}

//metodo encontar caminho no labirinto
//mesmo findpath
bool encontarCaminho(matchar& mat, Par inicio, Par final){
    vector<Par> pilha;
    pilha.push_back(inicio);
    mat.get(inicio) = EMBUSCA;

    while(pilha.size() != 0){
        Par topo = pilha.back();
        if(topo == final){
            mostrarMatriz(mat, pilha, inicio, final);
            ed_show();
            return true;
        }

        vector<Par> vizinhosAbertos;
        mostrarMatriz(mat, pilha, inicio, final);
        for(Par par : buscaVizinhos(topo)){
            if(mat.get(par) == ABERTO){
                vizinhosAbertos.push_back(par);
                mat_focus(par, 'r');
            }
        }

        ed_show();
        if(vizinhosAbertos.size() == 0){
            pilha.pop_back();
            mostrarMatriz(mat, pilha, inicio, final);
            ed_show();
        }else{
            Par escolhido = vizinhosAbertos[rand()% vizinhosAbertos.size()];
            mat.get(escolhido) = EMBUSCA;
            pilha.push_back(escolhido);

            //mostrar a matriz
            mostrarMatriz(mat, pilha, inicio, final);
            ed_show();
        }

    }
    mostrarMatriz(mat, pilha, inicio, final);
    ed_show();
    return false;
}

bool findPath(matchar& mat, Par inicio, Par final){
    vector<Par> pilha;
    pilha.push_back(inicio);
    mat.get(inicio) = EMBUSCA;

    while(pilha.size() != 0){
        Par topo = pilha.back();
        if(topo == final){
            showMat(mat, pilha, inicio, final);
            ed_show();
            return true;
        }
        vector<Par> viz_abertos;
        showMat(mat, pilha, inicio, final);
        for(Par par : getNeib(topo)){
            if(mat.get(par) == ABERTO){
                viz_abertos.push_back(par);
                mat_focus(par, 'r');
            }
        }
        ed_show();
        if(viz_abertos.size() == 0){
            pilha.pop_back();
            showMat(mat, pilha, inicio, final);
            ed_show();
        }else{
            Par escolhido = viz_abertos[rand() % viz_abertos.size()];
            mat.get(escolhido) = EMBUSCA;
            pilha.push_back(escolhido);
            showMat(mat, pilha, inicio, final);
            ed_show();
        }
    }
    showMat(mat, pilha, inicio, final);
    ed_show();
    return false;
}

//ver se e furavel
bool furavel(matchar& mat, Par p){
    int contador = 0;
    if(!mat.equals(p, PAREDE))
        return false;
    for(auto &viz : buscaVizinhos(p)){
        if(mat.equals(viz, PAREDE))
            contador++;
    }
    return (contador >= 3);
}

//colocar aleatorio
int sortear(int x){
    return rand() % x;
}

//metodo mostar labirinto com pilha
void mostarLab(matchar& mat, vector<Par> pilha){
    mat_draw(mat);
    vector<Par> aux;
    while(pilha.size() != 0){
        mat_focus(pilha.back(),'g');
        //aux.push_back(pilha.back());
        pilha.pop_back();
    }
    ed_show();
    while(aux.size() != 0){
        pilha.push_back(aux.back());
        aux.pop_back();
    }
}

//metodo criar labirinto com pilha
void criarLab(matchar& mat, vector<Par> pilha){
    mat.get(Par(1, 1)) = ABERTO;
    pilha.push_back(Par(1, 1));
    while(pilha.size() != 0){

        vector<Par> furaveis;
        for(auto viz : buscaVizinhos(pilha.back()))
            if(furavel(mat, viz))
                furaveis.push_back(viz);
        if(furaveis.size() == 0){
            pilha.pop_back();
            mostarLab(mat, pilha);
        }else{
           Par sortudo = furaveis[sortear(furaveis.size())];
           mat.get(sortudo) = ABERTO;
           pilha.push_back(sortudo);
           mostarLab(mat, pilha);
        }
    }
}
//main de teste
//int main(){
//    vector<Par> pilha;
//    matchar mat(20,35, PAREDE);
//    criarLab(mat, pilha);
//    mat_draw(mat);
//    ed_show;
//    ed_lock();
//    return 0;
//}

int main(){
    srand(time(NULL));
    vector<Par> pilha;
    matchar mat(20, 35, PAREDE);
    //furar(mat, Par(1, 1));//chama a função recursiva
    criarLab(mat, pilha);
    mat_draw(mat);
    ed_show();

    Par inicio = mat_get_click(mat, "digite o local de inicio");

    Par final = mat_get_click(mat, "digite o local de fim");
    mat_draw(mat);
    ed_show();

    findPath(mat, inicio, final);
    ed_lock();//impede que termine abruptamente
    return 0;
}
