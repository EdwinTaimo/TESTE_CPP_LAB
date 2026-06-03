// Exercicio 1 - Classe Abstrata Pessoa
// Grupo: Leyla Macuacua, Dercio Chipura, Joana Uelemo, Edwin Taimo Gema

#include <iostream>
using namespace std;

class Pessoa {
protected:
    string nome;  // guarda o nome da pessoa
    int idade;    // guarda a idade
    string sexo;  // guarda o sexo

public:
    // construtor que recebe os dados e inicializa os atributos
    Pessoa(string n, int i, string s) {
        nome = n;
        idade = i;
        sexo = s;
    }

    // destrutor virtual para funcionar bem com heranca
    virtual ~Pessoa() {}

    // getters - retornam os valores dos atributos
    string getNome()  { return nome;  }
    int    getIdade() { return idade; }
    string getSexo()  { return sexo;  }

    // setters - permitem alterar os valores dos atributos
    void setNome(string n)  { nome  = n; }
    void setIdade(int i)    { idade = i; }
    void setSexo(string s)  { sexo  = s; }

    // metodo puramente virtual - obriga as classes filhas a implementa-lo
    // o "= 0" torna esta classe abstrata (nao pode ser instanciada)
    virtual void mostrarDados() = 0;
};

// classe de teste para mostrar que Pessoa funciona como base
class PessoaTeste : public Pessoa {
public:
    PessoaTeste(string n, int i, string s) : Pessoa(n, i, s) {}

    void mostrarDados() {
        cout << "Nome : " << nome  << endl;
        cout << "Idade: " << idade << endl;
        cout << "Sexo : " << sexo  << endl;
    }
};

int main() {
    PessoaTeste p("Leyla Macuacua", 20, "F");
    p.mostrarDados();
    return 0;
}
