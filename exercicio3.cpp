// Exercicio 3 - Classe Gerenciadora do Sistema
// Grupo: Leyla Macuacua, Dercio Chipura, Joana Uelemo, Edwin Taimo Gema

#include <iostream>
using namespace std;

class Pessoa {
protected:
    string nome; int idade; string sexo;
public:
    Pessoa(string n, int i, string s) { nome=n; idade=i; sexo=s; }
    virtual ~Pessoa() {}
    string getNome() { return nome; }
    virtual void mostrarDados() = 0;
};

class Estudante : public Pessoa {
private:
    string numero, curso;
    double notas[3];
public:
    Estudante(string n, int i, string s, string num, string c, double t1, double t2, double tr)
        : Pessoa(n,i,s) { numero=num; curso=c; notas[0]=t1; notas[1]=t2; notas[2]=tr; }
    string getNumero() { return numero; }
    double calcularMedia() { return (notas[0]+notas[1]+notas[2])/3; }
    string verificarAprovacao() {
        double m = calcularMedia();
        if(m>=14) return "DISPENSADO";
        if(m>=10) return "ADMITIDO";
        return "REPROVADO";
    }
    void mostrarDados() {
        cout << "Estudante: " << nome << " | Numero: " << numero
             << " | Media: " << calcularMedia()
             << " | " << verificarAprovacao() << endl;
    }
};

class Professor : public Pessoa {
private:
    string codigo, disciplina;
    double salario;
public:
    Professor(string n, int i, string s, string cod, string disc, double sal)
        : Pessoa(n,i,s) { codigo=cod; disciplina=disc; salario=sal; }
    string getCodigo() { return codigo; }
    void aumentarSalario(double p) { salario += salario*p/100; }
    void mostrarDados() {
        cout << "Professor: " << nome << " | Codigo: " << codigo
             << " | " << disciplina << " | Salario: " << salario << " MT" << endl;
    }
};

// ---- classe gerenciadora ----
class Sistema {
private:
    Estudante* estudantes[10]; // array de ponteiros para ate 10 estudantes
    Professor* professores[5]; // array de ponteiros para ate 5 professores
    int totalEst;  // contador de estudantes
    int totalProf; // contador de professores

public:
    // construtor inicializa os contadores a zero
    Sistema() { totalEst = 0; totalProf = 0; }

    // destrutor liberta a memoria alocada
    ~Sistema() {
        for(int i=0; i<totalEst;  i++) delete estudantes[i];
        for(int i=0; i<totalProf; i++) delete professores[i];
    }

    // cadastra um novo estudante se nao atingiu o limite
    void cadastrarEstudante(Estudante* e) {
        if(totalEst >= 10) { cout << "Limite de estudantes atingido!" << endl; return; }
        estudantes[totalEst] = e; // guarda o ponteiro na posicao actual
        totalEst++;
        cout << "Estudante cadastrado com sucesso." << endl;
    }

    // cadastra um novo professor se nao atingiu o limite
    void cadastrarProfessor(Professor* p) {
        if(totalProf >= 5) { cout << "Limite de professores atingido!" << endl; return; }
        professores[totalProf] = p;
        totalProf++;
        cout << "Professor cadastrado com sucesso." << endl;
    }

    // mostra todos os estudantes cadastrados
    void listarEstudantes() {
        cout << "=== ESTUDANTES ===" << endl;
        for(int i=0; i<totalEst; i++)
            estudantes[i]->mostrarDados();
    }

    // mostra todos os professores cadastrados
    void listarProfessores() {
        cout << "=== PROFESSORES ===" << endl;
        for(int i=0; i<totalProf; i++)
            professores[i]->mostrarDados();
    }

    // pesquisa por nome (busca linear)
    void pesquisarPorNome(string nome) {
        bool achou = false;
        for(int i=0; i<totalEst; i++) {
            if(estudantes[i]->getNome() == nome) {
                estudantes[i]->mostrarDados(); achou = true;
            }
        }
        for(int i=0; i<totalProf; i++) {
            if(professores[i]->getNome() == nome) {
                professores[i]->mostrarDados(); achou = true;
            }
        }
        if(!achou) cout << "Nenhum registo encontrado." << endl;
    }

    // remove estudante pelo numero - desloca os restantes
    void removerEstudante(string numero) {
        for(int i=0; i<totalEst; i++) {
            if(estudantes[i]->getNumero() == numero) {
                delete estudantes[i]; // liberta a memoria do objeto
                // move os elementos seguintes uma posicao para tras
                for(int j=i; j<totalEst-1; j++)
                    estudantes[j] = estudantes[j+1];
                totalEst--;
                cout << "Estudante removido." << endl;
                return;
            }
        }
        cout << "Estudante nao encontrado." << endl;
    }

    // remove professor pelo codigo
    void removerProfessor(string codigo) {
        for(int i=0; i<totalProf; i++) {
            if(professores[i]->getCodigo() == codigo) {
                delete professores[i];
                for(int j=i; j<totalProf-1; j++)
                    professores[j] = professores[j+1];
                totalProf--;
                cout << "Professor removido." << endl;
                return;
            }
        }
        cout << "Professor nao encontrado." << endl;
    }
};

int main() {
    Sistema sys;

    sys.cadastrarEstudante(new Estudante("Joana Uelemo", 22, "F", "E003", "Informatica", 18, 17, 19));
    sys.cadastrarEstudante(new Estudante("Edwin Taimo",  20, "M", "E004", "Informatica",  9,  8,  7));
    sys.cadastrarProfessor(new Professor("Prof. Ana", 38, "F", "P002", "Estruturas de Dados", 92000));

    sys.listarEstudantes();
    cout << endl;
    sys.listarProfessores();
    cout << endl;

    sys.pesquisarPorNome("Edwin Taimo");
    cout << endl;

    sys.removerEstudante("E004");
    sys.listarEstudantes();

    return 0;
}
