#include <iostream>
#include <vector>

using namespace std;

const int linha = 20;
const int coluna = 60;

struct Par{
    int l;
    int c;

    Par(int l,int c){
        this->l = l;
        this->c = c;
    }
};

vector<Par> vizinhos(Par par){

    vector<Par> vizinhos;

    vizinhos.push_back(Par(par.l,par.c + 1));
    vizinhos.push_back(Par(par.l,par.c - 1));
    vizinhos.push_back(Par(par.l + 1,par.c));
    vizinhos.push_back(Par(par.l - 1,par.c));

    return vizinhos;
}

void esperar(){
    char c;
    cin >> noskipws >> c;//capta o 'enter'
}

void mostrar(char mat[linha][coluna]){
    for(int l = 0; l < linha; l++){
        for(int c = 0; c < coluna; c++){
            cout << mat[l][c];
        }
        cout << "\n";
    }
}

void limparTela(){
    for(int i = 0; i < 2; i++){
        cout << endl;
    }
}

vector<Par> embaralhar(vector<Par> vet){
    for(int i = 0; i < (int)vet.size(); i++){
            int aleatorio = rand() % vet.size();
            swap(vet[i],vet[aleatorio]);
    }

    return vet;
}

int queimar(int l,int c, char mat[linha][coluna],int nivel){

    int contador = 0;

    if(l < 0 or l >= linha)
        return 0;
    if(c < 0 or c >= coluna)
        return 0;
    if(mat[l][c] == '#'){
        cont = 1;
        mat[l][c] = '0' + nivel;
        limparTela();
        mostrar(mat);
        esperar();

        int contNivel = nivel + 1;

        for(Par par : embaralhar(vizinhos(Par(l,c)))){
            cont += queimar(par.l,par.c,mat,contNivel);
            if(contNivel > 9){
                contNivel = 0;
            }
            mat[l][c] = '.';
        }
    }
    return contador;
}

int main(){

    char mat[linha][coluna];

    //Preenche a matriz
    for(int l = 0; l < linha; l++){
        for(int c = 0; c < coluna; c++){
            mat[l][c] = ' ';
        }
    }

    int qtd = linha * coluna * 1.5;

    for(int sorteio = 0; sorteio < qtd; sorteio++){
        mat[rand() % linha][rand() % coluna] = '#';
    }

    limparTela();
    mostrar(mat);

    int nivel = 0;

    int cont = queimar(0, 0, mat, nivel);
    cout << "Quantidade de arvores queimadas: " << cont << endl;

    return 0;
}
