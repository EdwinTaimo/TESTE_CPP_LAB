

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//==================== CLASSE PESSOA ====================

class Pessoa {
protected:
    string nome;
    int idade;
    string sexo;

public:
    Pessoa(string n, int i, string s) {
        nome = n;
        idade = i;
        sexo = s;
    }

    virtual ~Pessoa() {}

    string getNome() { return nome; }
    int getIdade() { return idade; }
    string getSexo() { return sexo; }

    void setNome(string n) { nome = n; }
    void setIdade(int i) { idade = i; }
    void setSexo(string s) { sexo = s; }

    virtual void mostrarDados() = 0;
};

//==================== CLASSE ESTUDANTE ====================

class Estudante : public Pessoa {
private:
    string numeroEstudante;
    string curso;
    double notas[3];

public:
    Estudante(string n, int i, string s,
              string num, string c,
              double n1, double n2, double n3)
        : Pessoa(n, i, s) {

        numeroEstudante = num;
        curso = c;

        notas[0] = n1;
        notas[1] = n2;
        notas[2] = n3;
    }

    string getNumero() {
        return numeroEstudante;
    }

    double calcularMedia() {
        return (notas[0] + notas[1] + notas[2]) / 3;
    }

    string verificarAprovacao() {
        double media = calcularMedia();

        if(media >= 14)
            return "Dispensado";
        else if(media >= 10)
            return "Admitido";
        else
            return "Reprovado";
    }

    void mostrarDados() override {
        cout << "\n===== ESTUDANTE =====\n";
        cout << "Nome: " << nome << endl;
        cout << "Idade: " << idade << endl;
        cout << "Sexo: " << sexo << endl;
        cout << "Numero: " << numeroEstudante << endl;
        cout << "Curso: " << curso << endl;
        cout << "Media: " << calcularMedia() << endl;
        cout << "Estado: " << verificarAprovacao() << endl;
    }
};

//==================== CLASSE PROFESSOR ====================

class Professor : public Pessoa {
private:
    string codigoProfessor;
    string disciplina;
    double salario;

public:
    Professor(string n, int i, string s,
              string cod, string disc,
              double sal)
        : Pessoa(n, i, s) {

        codigoProfessor = cod;
        disciplina = disc;
        salario = sal;
    }

    string getCodigo() {
        return codigoProfessor;
    }

    void aumentarSalario(double percentual) {
        salario += salario * percentual / 100;
    }

    void mostrarDados() override {
        cout << "\n===== PROFESSOR =====\n";
        cout << "Nome: " << nome << endl;
        cout << "Idade: " << idade << endl;
        cout << "Sexo: " << sexo << endl;
        cout << "Codigo: " << codigoProfessor << endl;
        cout << "Disciplina: " << disciplina << endl;
        cout << "Salario: " << salario << endl;
    }
};

//==================== ARRAYS ====================

Estudante* estudantes[10];
Professor* professores[5];

int totalEstudantes = 0;
int totalProfessores = 0;

//==================== CADASTRAR ESTUDANTE ====================

void cadastrarEstudante() {

    if(totalEstudantes >= 10) {
        cout << "Limite de estudantes atingido!\n";
        return;
    }

    string nome, sexo, numero, curso;
    int idade;
    double n1, n2, n3;

    cout << "Nome: ";
    cin.ignore();
    getline(cin, nome);

    cout << "Idade: ";
    cin >> idade;

    cout << "Sexo: ";
    cin >> sexo;

    cout << "Numero: ";
    cin >> numero;

    cout << "Curso: ";
    cin >> curso;

    cout << "Nota 1: ";
    cin >> n1;

    cout << "Nota 2: ";
    cin >> n2;

    cout << "Nota 3: ";
    cin >> n3;

    estudantes[totalEstudantes++] =
        new Estudante(nome, idade, sexo,
                      numero, curso,
                      n1, n2, n3);
}

//==================== CADASTRAR PROFESSOR ====================

void cadastrarProfessor() {

    if(totalProfessores >= 5) {
        cout << "Limite de professores atingido!\n";
        return;
    }

    string nome, sexo, codigo, disciplina;
    int idade;
    double salario;

    cout << "Nome: ";
    cin.ignore();
    getline(cin, nome);

    cout << "Idade: ";
    cin >> idade;

    cout << "Sexo: ";
    cin >> sexo;

    cout << "Codigo: ";
    cin >> codigo;

    cout << "Disciplina: ";
    cin >> disciplina;

    cout << "Salario: ";
    cin >> salario;

    professores[totalProfessores++] =
        new Professor(nome, idade, sexo,
                      codigo, disciplina,
                      salario);
}

//==================== LISTAR ====================

void listarEstudantes() {
    for(int i=0; i<totalEstudantes; i++)
        estudantes[i]->mostrarDados();
}

void listarProfessores() {
    for(int i=0; i<totalProfessores; i++)
        professores[i]->mostrarDados();
}

//==================== PESQUISAR ====================

void pesquisarNome() {

    string nome;

    cout << "Nome: ";
    cin.ignore();
    getline(cin, nome);

    for(int i=0;i<totalEstudantes;i++)
        if(estudantes[i]->getNome() == nome)
            estudantes[i]->mostrarDados();

    for(int i=0;i<totalProfessores;i++)
        if(professores[i]->getNome() == nome)
            professores[i]->mostrarDados();
}

//==================== POLIMORFISMO ====================

void mostrarPessoasPolimorficas() {

    Pessoa* pessoas[15];
    int total = 0;

    for(int i=0;i<totalEstudantes;i++)
        pessoas[total++] = estudantes[i];

    for(int i=0;i<totalProfessores;i++)
        pessoas[total++] = professores[i];

    for(int i=0;i<total;i++)
        pessoas[i]->mostrarDados();
}

//==================== ARQUIVO ====================

void salvarArquivo() {

    ofstream arq("dados.txt");

    arq << "Total estudantes: "
        << totalEstudantes << endl;

    arq << "Total professores: "
        << totalProfessores << endl;

    arq.close();

    cout << "Dados gravados!\n";
}

void lerArquivo() {

    ifstream arq("dados.txt");

    string linha;

    while(getline(arq, linha))
        cout << linha << endl;

    arq.close();
}

//==================== MAIN ====================

int main() {

    int op;

    do {

        cout << "\n===== MENU =====\n";
        cout << "1. Cadastrar estudante\n";
        cout << "2. Cadastrar professor\n";
        cout << "3. Mostrar estudantes\n";
        cout << "4. Mostrar professores\n";
        cout << "5. Pesquisar pessoa\n";
        cout << "6. Remover pessoa\n";
        cout << "7. Verificar aprovacao\n";
        cout << "8. Aumentar salario\n";
        cout << "9. Salvar arquivo\n";
        cout << "10. Ler arquivo\n";
        cout << "11. Sair\n";
        cout << "Opcao: ";
        cin >> op;

        switch(op) {

        case 1:
            cadastrarEstudante();
            break;

        case 2:
            cadastrarProfessor();
            break;

        case 3:
            listarEstudantes();
            break;

        case 4:
            listarProfessores();
            break;

        case 5:
            pesquisarNome();
            break;

        case 9:
            salvarArquivo();
            break;

        case 10:
            lerArquivo();
            break;

        case 11:
            cout << "Encerrando...\n";
            break;
        }

    } while(op != 11);

    return 0;
}
