// Exercicio 4 - Polimorfismo em Tempo de Execucao (Late Binding)
// Grupo: Leyla Macuacua, Dercio Chipura, Joana Uelemo, Edwin Taimo Gema

#include <iostream>
using namespace std;

class Pessoa {
protected:
    string nome; int idade; string sexo;
public:
    Pessoa(string n, int i, string s) { nome=n; idade=i; sexo=s; }
    virtual ~Pessoa() {}
    virtual void mostrarDados() = 0; // metodo puramente virtual
};

class Estudante : public Pessoa {
private:
    string numero, curso;
    double notas[3];
public:
    Estudante(string n, int i, string s, string num, string c, double t1, double t2, double tr)
        : Pessoa(n,i,s) { numero=num; curso=c; notas[0]=t1; notas[1]=t2; notas[2]=tr; }

    double calcularMedia() { return (notas[0]+notas[1]+notas[2])/3; }

    // override: esta versao e chamada quando o ponteiro aponta para Estudante
    void mostrarDados() {
        cout << "[Estudante] " << nome << " | " << curso
             << " | Media: " << calcularMedia() << endl;
    }
};

class Professor : public Pessoa {
private:
    string codigo, disciplina;
    double salario;
public:
    Professor(string n, int i, string s, string cod, string disc, double sal)
        : Pessoa(n,i,s) { codigo=cod; disciplina=disc; salario=sal; }

    // override: esta versao e chamada quando o ponteiro aponta para Professor
    void mostrarDados() {
        cout << "[Professor] " << nome << " | " << disciplina
             << " | Salario: " << salario << " MT" << endl;
    }
};

// funcao que percorre a colecao e chama mostrarDados() pelo ponteiro da classe base
// o compilador decide em tempo de execucao qual versao chamar (Late Binding)
void mostrarTodos(Pessoa* colecao[], int total) {
    cout << "=== POLIMORFISMO ===" << endl;
    for(int i=0; i<total; i++)
        colecao[i]->mostrarDados(); // chamada polimorfica
}

int main() {
    // array de ponteiros do tipo BASE (Pessoa*) que guarda objetos de tipos DIFERENTES
    Pessoa* colecao[4];

    colecao[0] = new Estudante("Leyla Macuacua", 20, "F", "E001", "Informatica", 15, 13, 16);
    colecao[1] = new Estudante("Dercio Chipura", 21, "M", "E002", "Informatica", 12, 11, 13);
    colecao[2] = new Professor("Prof. Carlos",   45, "M", "P001", "Lab II",      85000);
    colecao[3] = new Professor("Prof. Ana",       38, "F", "P002", "Estruturas",  92000);

    // mesmo usando ponteiro Pessoa*, cada objeto chama a sua propria versao do metodo
    mostrarTodos(colecao, 4);

    // liberta a memoria de cada objeto alocado com new
    for(int i=0; i<4; i++) delete colecao[i];

    return 0;
}
