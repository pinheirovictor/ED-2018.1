#include <iostream>

using namespace std;

struct  Node{
    int value;
    Node * next;
    Node(int value = 0, Node * next = nullptr){
        this->value = value;
        this->next = next;
    }
};

struct SList{
    Node * head;
    SList(){
        this->head = nullptr;
    }

    //destrutor
    ~SList(){
       head = deletarTudo(head);
    }

    void apagar(){
        head = deletarTudo(head);
    }

    Node * deletarTudo(Node * node){
       if(node == nullptr)
           return nullptr;
        deletarTudo(node->next);
        delete node;
        return nullptr;
    }

private:
    //arranca rabo recurssivo
    Node * arrancaRabo(Node * node, int value){
        if(node == nullptr)
            return nullptr;
        node->next = arrancaRabo(node->next, value);
        if(node->next == nullptr){
            if(node->value != value){
                delete node;
                return nullptr;
            }else{
                return node;
            }
        }
        return node;
    }

public:
    //metodo arrancar rabo
    void cortaRabo(int value){
        arrancaRabo(head, value);
    }

private:
    // Arranca Venta Recursivo
    Node * arrancaVenta(Node * node, int value){
        if(node == nullptr)
            return nullptr;
        if(node->value == value)
            return node;

        auto aux = node;
        delete node;
        node = nullptr;
        aux = arrancaVenta(aux->next, value);
        return aux;
    }

public:
    //metodo arrancar venta
    void cortarVenta(int value){
        head = arrancaVenta(head, value);
    }

    //metodo size iterativo
    int size(){
        int contador = 0;
        auto node = head;
        while(node != nullptr){
            node = node->next;
            contador++;
        }
        return contador;
    }

private:
    //metodo siz recursivo
   int _rsize(Node * node){
        if(node->next == nullptr)
            return 1;
        return 1 + _rsize(node->next);
    }

public:
   //metodo size recursivo
    void rsize(){
      cout <<  _rsize(head) << endl;
    }

    //metodo adiciona na frente
    void push_front(int value){
        //this->head = new Node(value, this->head);
        Node * node = new Node(value);
        node->next = head;
        this->head = node;
    }

    //metodo apaga da frente
    void pop_front(){
        if(head == nullptr)
            return;
        Node * aux = head;
        head = head->next;
        delete aux;
    }

    //metodo adiciona no final
    void push_back(int value){ //todo
        if(head == nullptr){
            head = new Node(value);
            return;
        }
        auto node = head;
        while(node->next != nullptr)
            node = node->next;
        node->next = new Node(value);
    }

private:
    //metodo adiciona no final recursivo
    Node * _push_back(Node * node, int value){
        if(node->next == nullptr){
            node->next = new Node(value);
            return node->next;
        }
          node = _push_back(node->next, value);
    }

public:
    //metodo adiciona no final recursivo
    void rpush_back(int value){
        _push_back(head, value);
    }

    //metodo apaga do final iterativo
    void pop_back(){
        if(head == nullptr)
            return;
        if(head->next == nullptr){
            delete head;
            head = nullptr;
            return;
        }
        auto node = head;
        while(node->next->next != nullptr)
            node = node->next;
        delete node->next;
        node->next = nullptr;
    }

private:
    //metodo apaga do final recursivo
    Node * _rpop_back(Node * node){
        if(node->next == nullptr){
            delete node;
            return nullptr;
        }
        node->next = _rpop_back(node->next);
    }

public:
    //metodo apaga do final recursivo, chama a função recursiva
    void rpop_back(){
        this->head = _rpop_back(head);
    }

    //metodo mostar iterativo
    void ishow(){
        auto node = head;
        while(node != nullptr){
            cout << node->value << " ";
            node = node->next;
        }
        cout << endl;
    }

private:
    //metodo mostrar recursivo
    void _rshow(Node * node){
        if(node == nullptr)
            return;
        cout << node->value << " ";
        _rshow(node->next);
    }

public:
    //metodo mostrar recursivo
    void rshow(){
        _rshow(head);
        cout << endl;
    }

private:
    //metodo remover recursivo
    Node * _remove(Node * node, int value){
        if(node == nullptr)
            return nullptr;
        if(node->value == value){
            auto aux = node->next;
            delete node;
            return aux;
        }
        node->next = _remove(node->next, value);
    }

public:
    //metodo remover recursivo
    void rremove(int value){
        head = _remove(head, value);
    }

    //metodo remover iterativo
    void iremove(int value){
        if(head == nullptr)
            return;
        if(head->value == value && head->next == nullptr){
            delete head;
            head = nullptr;
            return;
        }if(head->value == value && head->next != nullptr){
            auto aux = head;
            head = head->next;
            delete aux;
        }
       //falta
    }

    //metodo inserir ordenado iterativo
    void inserir_ordenado(int value){
        auto node = head;
        if(head == nullptr || head->value > value){
            this->head = new Node(value, head);
            return;
        }
        while(node->next != nullptr && node->next->value < value){
            node = node->next;
        }
        node->next = new Node(value, node->next);
    }

private:
    //metodo inserir oredenado recursivo
    Node * _rinserir_ordenado(Node * node, int value){
        if(node == nullptr)
            return new Node(value);
        if(node->value > value)
            return new Node(value, node);
        node->next = _rinserir_ordenado(node->next, value);
        return node;
    }
public:
    //metodo inserir oredenado recursivo
    void rinserir_ordenado(int value){
        head = _rinserir_ordenado(head, value);
    }

private:
    //metodo somar
    int rsomar(Node * node){
        if(node->next == nullptr)
            return node->value;

        return node->value + rsomar(node->next);
    }

public:
    //metodo somar chamando recursivo
    void somar(){
        rsomar(head);
         cout << rsomar(head) << endl;
    }

private:
    // metodo menor recursivo
    int _rmin(Node * node){
        if(node->next == nullptr)
            return node->value;
        return std::min(node->value, _rmin(node->next));
    }
public:
    //metodo menor
    int rmin(){
        return _rmin(head);
    }

    //metodo menor iterativo
    int min(){
        if(head == nullptr)
            return 0;
        int min = head->value;
        auto node = head;
        while(node->next != nullptr){
            min = std::min(min, node->next->value);
            node = node->next;
        }
        return min;
    }

};

int main(){

       SList lista;

    cout << "Adicionando elementos na lista" << endl;
    for(int i = 0; i < 8; i++)
        lista.push_back(i+1);

    cout << "Elementos da lista" << endl;
    lista.ishow();

    cout << "metodo Size interativo: "<< lista.size() << endl;


    cout << "metodo somar recursivo " << endl;
    lista.somar();

    cout << "metodo menor recursivo: " << lista.rmin() << endl;

    cout << "testando metodo pop_front" << endl;
    lista.pop_front();
    lista.ishow();

    cout << "testando pop_back interativo" << endl;
    lista.pop_back();
    lista.ishow();

    cout << " testando pop_back recursivo" << endl;
    lista.rpop_back();
    lista.rshow();

    cout << "testando metodo remove valor 2 interativo" << endl;
    lista.iremove(2);
    lista.rshow();

    cout << "testando remove  4 recursivo" << endl;
    lista.rremove(4);
    lista.rshow();

    cout << "testando metodo inserir ordenado  16 interativo" << endl;
    lista.inserir_ordenado(16);
    lista.ishow();

    cout << "testanto metodo inserir ordenado  23 recursivo" << endl;
    lista.rinserir_ordenado(23);
    lista.ishow();

    cout << "inserir ordenado  -14 recursivo" << endl;
    lista.rinserir_ordenado(-14);
    lista.ishow();

    cout << "metodo somar recursivo " << endl;
    lista.somar();

    cout << "metodo menor interativo: "<< lista.min()  << endl;

    cout << "metodo arranca rabo " << endl;
    lista.cortaRabo(5);
    lista.ishow();

    cout << "metodo arranca venta " << endl;
    lista.cortarVenta(5);
    lista.ishow();

    cout << "metodo apagar todos os elementos da lista " << endl;
    lista.apagar();
    lista.ishow();
    return 0;
}
