#include <iostream>
#include <vector>

using namespace std;

struct Vetor{
    int * _data;
    int _capacidade;
    int _size;


    Vetor(int capacidade){
        this->_capacidade = capacidade;
        this->_size = 0;
        this->_data = new int[capacidade];
    }

    void push_back(int value){
        if(this->_size == this->_capacidade)
            return;
        this->_data[this->_size] = value;
        this->_size += 1;
    }

    void pop_back(){
        if(this->_size == 0)
            return;
        this->_data[_size] = 0;
        this->_size -= 1;
    }

    int& at(int indice){
        return this->_data[indice];
    }

    int& front(){
        return this->_data[0];
    }

    int& back(){
        return this->_data[this->_size - 1];
    }

    int * begin(){
        return &this->_data[0];
    }

    int * end(){
        return &this->_data[this->_size];
    }

    int size(){
        return this->_size;
    }

    int capacity(){
        return this->_capacidade;
    }

    void reserve(int novacapacidade){
        if(this->_capacidade > novacapacidade)
            return;
        _capacidade += novacapacidade;
        this->_data = new int[_capacidade];
       }
    
};


int main(){

    Vetor vector(5);

    vector.push_back(6);
    vector.push_back(3);
    vector.push_back(9);
    vector.push_back(5);

    for(auto p : vector){
        cout << p << " ";
    }
    cout << endl;

    cout << "O elemento do índice[1] é: " << vector.at(1);
    cout << endl;
    vector.at(2) = 9;

    cout << "capacidade: " << vector.capacity();
    cout << " size: " << vector.size();
    cout << endl;

    for(auto p : vector){
        cout << p << " ";
    }

    cout << endl;
    vector.reserve(50);

    cout << "Nova capacidade: " << vector.capacity() << endl;

    return 0;
}

