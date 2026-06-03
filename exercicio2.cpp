// Exercicio 2 - Classes Derivadas: Estudante e Professor
// Grupo: Leyla Macuacua, Dercio Chipura, Joana Uelemo, Edwin Taimo Gema

#include <iostream>
using namespace std;

// classe base (mesma do exercicio 1)
class Pessoa {
protected:
    string nome;
    int idade;
    string sexo;
public:
    Pessoa(string n, int i, string s) {
        nome = n; idade = i; sexo = s;
    }
    virtual ~Pessoa() {}
    string getNome()  { return nome;  }
    int    getIdade() { return idade; }
    string getSexo()  { return sexo;  }
    void setNome(string n)  { nome  = n; }
    void setIdade(int i)    { idade = i; }
    void setSexo(string s)  { sexo  = s; }
    virtual void mostrarDados() = 0;
};

// ---- classe Estudante herda de Pessoa ----
class Estudante : public Pessoa {
private:
    string numeroEstudante;
    string curso;
    double notas[3]; // posicao 0=TesteI, 1=TesteII, 2=Trabalho

public:
    // construtor chama o construtor da classe mae com ": Pessoa(...)"
    Estudante(string n, int i, string s, string num, string c, double t1, double t2, double tr)
        : Pessoa(n, i, s) {
        numeroEstudante = num;
        curso = c;
        notas[0] = t1;
        notas[1] = t2;
        notas[2] = tr;
    }

    // calcula a media das 3 notas
    double calcularMedia() {
        return (notas[0] + notas[1] + notas[2]) / 3;
    }

    // verifica se o estudante esta dispensado, admitido ou reprovado
    string verificarAprovacao() {
        double media = calcularMedia();
        if (media >= 14) return "DISPENSADO";
        if (media >= 10) return "ADMITIDO";
        return "REPROVADO";
    }

    // sobrescreve o metodo da classe mae (override)
    void mostrarDados() {
        cout << "-- ESTUDANTE --"           << endl;
        cout << "Nome  : " << nome          << endl;
        cout << "Idade : " << idade         << endl;
        cout << "Sexo  : " << sexo          << endl;
        cout << "Numero: " << numeroEstudante << endl;
        cout << "Curso : " << curso         << endl;
        cout << "T1    : " << notas[0]      << endl;
        cout << "T2    : " << notas[1]      << endl;
        cout << "Trab  : " << notas[2]      << endl;
        cout << "Media : " << calcularMedia()      << endl;
        cout << "Estado: " << verificarAprovacao() << endl;
    }
};

// ---- classe Professor herda de Pessoa ----
class Professor : public Pessoa {
private:
    string codigoProfessor;
    string disciplina;
    double salario;

public:
    Professor(string n, int i, string s, string cod, string disc, double sal)
        : Pessoa(n, i, s) {
        codigoProfessor = cod;
        disciplina = disc;
        salario = sal;
    }

    // aplica um aumento percentual ao salario
    void aumentarSalario(double percentual) {
        salario = salario + (salario * percentual / 100);
        cout << "Novo salario: " << salario << " MT" << endl;
    }

    void mostrarDados() {
        cout << "-- PROFESSOR --"              << endl;
        cout << "Nome      : " << nome         << endl;
        cout << "Idade     : " << idade        << endl;
        cout << "Sexo      : " << sexo         << endl;
        cout << "Codigo    : " << codigoProfessor << endl;
        cout << "Disciplina: " << disciplina   << endl;
        cout << "Salario   : " << salario << " MT" << endl;
    }
};

int main() {
    Estudante e("Dercio Chipura", 21, "M", "E002", "Informatica", 12, 11, 13);
    e.mostrarDados();
    cout << endl;

    Professor p("Prof. Carlos", 45, "M", "P001", "Laboratorio II", 85000);
    p.mostrarDados();
    cout << endl;
    p.aumentarSalario(10); // aumento de 10%

    return 0;
}
