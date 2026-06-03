// Exercicio 5 - Menu Interactivo + Ficheiros
// Grupo: Leyla Macuacua, Dercio Chipura, Joana Uelemo, Edwin Taimo Gema

#include <iostream>
#include <fstream>  // para ler e escrever ficheiros
using namespace std;

// ---- classes (resumidas) ----
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
        cout << "Estudante : " << nome   << endl;
        cout << "Numero    : " << numero << endl;
        cout << "Curso     : " << curso  << endl;
        cout << "T1=" << notas[0] << " T2=" << notas[1] << " Trab=" << notas[2] << endl;
        cout << "Media     : " << calcularMedia()      << endl;
        cout << "Estado    : " << verificarAprovacao() << endl;
        cout << "------------------------" << endl;
    }
    // guarda dados numa linha para o ficheiro
    void salvar(ofstream& f) {
        f << "E|" << nome << "|" << idade << "|" << sexo << "|"
          << numero << "|" << curso << "|"
          << notas[0] << "|" << notas[1] << "|" << notas[2] << "\n";
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
        cout << "Professor  : " << nome       << endl;
        cout << "Codigo     : " << codigo     << endl;
        cout << "Disciplina : " << disciplina << endl;
        cout << "Salario    : " << salario << " MT" << endl;
        cout << "------------------------" << endl;
    }
    void salvar(ofstream& f) {
        f << "P|" << nome << "|" << idade << "|" << sexo << "|"
          << codigo << "|" << disciplina << "|" << salario << "\n";
    }
};

// ---- sistema ----
Estudante* estudantes[10];
Professor* professores[5];
int totalEst  = 0;
int totalProf = 0;

void cadastrarEstudante() {
    if(totalEst >= 10) { cout << "Limite atingido!\n"; return; }
    string n, s, num, c; int i; double t1,t2,tr;
    cout << "Nome: ";      getline(cin, n);
    cout << "Idade: ";     cin >> i; cin.ignore();
    cout << "Sexo: ";      getline(cin, s);
    cout << "Numero: ";    getline(cin, num);
    cout << "Curso: ";     getline(cin, c);
    cout << "Teste I: ";   cin >> t1;
    cout << "Teste II: ";  cin >> t2;
    cout << "Trabalho: ";  cin >> tr; cin.ignore();
    estudantes[totalEst++] = new Estudante(n,i,s,num,c,t1,t2,tr);
    cout << "Cadastrado!\n";
}

void cadastrarProfessor() {
    if(totalProf >= 5) { cout << "Limite atingido!\n"; return; }
    string n, s, cod, disc; int i; double sal;
    cout << "Nome: ";       getline(cin, n);
    cout << "Idade: ";      cin >> i; cin.ignore();
    cout << "Sexo: ";       getline(cin, s);
    cout << "Codigo: ";     getline(cin, cod);
    cout << "Disciplina: "; getline(cin, disc);
    cout << "Salario: ";    cin >> sal; cin.ignore();
    professores[totalProf++] = new Professor(n,i,s,cod,disc,sal);
    cout << "Cadastrado!\n";
}

void mostrarEstudantes() {
    if(totalEst==0) { cout << "Nenhum estudante.\n"; return; }
    for(int i=0;i<totalEst;i++) estudantes[i]->mostrarDados();
}

void mostrarProfessores() {
    if(totalProf==0) { cout << "Nenhum professor.\n"; return; }
    for(int i=0;i<totalProf;i++) professores[i]->mostrarDados();
}

void pesquisarPorNome() {
    string nome; cout << "Nome: "; getline(cin, nome);
    bool achou = false;
    for(int i=0;i<totalEst;i++)
        if(estudantes[i]->getNome()==nome) { estudantes[i]->mostrarDados(); achou=true; }
    for(int i=0;i<totalProf;i++)
        if(professores[i]->getNome()==nome) { professores[i]->mostrarDados(); achou=true; }
    if(!achou) cout << "Nao encontrado.\n";
}

void removerPessoa() {
    cout << "1-Estudante  2-Professor: "; int op; cin>>op; cin.ignore();
    if(op==1) {
        string num; cout << "Numero: "; getline(cin,num);
        for(int i=0;i<totalEst;i++) {
            if(estudantes[i]->getNumero()==num) {
                delete estudantes[i];
                for(int j=i;j<totalEst-1;j++) estudantes[j]=estudantes[j+1];
                totalEst--; cout << "Removido.\n"; return;
            }
        }
        cout << "Nao encontrado.\n";
    } else {
        string cod; cout << "Codigo: "; getline(cin,cod);
        for(int i=0;i<totalProf;i++) {
            if(professores[i]->getCodigo()==cod) {
                delete professores[i];
                for(int j=i;j<totalProf-1;j++) professores[j]=professores[j+1];
                totalProf--; cout << "Removido.\n"; return;
            }
        }
        cout << "Nao encontrado.\n";
    }
}

void verificarAprovacao() {
    string num; cout << "Numero do estudante: "; getline(cin,num);
    for(int i=0;i<totalEst;i++) {
        if(estudantes[i]->getNumero()==num) {
            cout << estudantes[i]->getNome() << ": " << estudantes[i]->verificarAprovacao() << endl;
            return;
        }
    }
    cout << "Nao encontrado.\n";
}

void aumentarSalario() {
    string cod; double pct;
    cout << "Codigo do professor: "; getline(cin,cod);
    cout << "Percentual (%): ";      cin >> pct; cin.ignore();
    for(int i=0;i<totalProf;i++) {
        if(professores[i]->getCodigo()==cod) {
            professores[i]->aumentarSalario(pct);
            cout << "Salario actualizado.\n"; return;
        }
    }
    cout << "Nao encontrado.\n";
}

// grava todos os registos no ficheiro dados.txt
void salvarFicheiro() {
    ofstream f("dados.txt"); // abre o ficheiro para escrita
    for(int i=0;i<totalEst;i++)  estudantes[i]->salvar(f);
    for(int i=0;i<totalProf;i++) professores[i]->salvar(f);
    f.close(); // fecha o ficheiro
    cout << "Dados gravados em dados.txt\n";
}

// le os registos do ficheiro dados.txt e repoe na memoria
void lerFicheiro() {
    ifstream f("dados.txt"); // abre o ficheiro para leitura
    if(!f.is_open()) { cout << "Ficheiro nao encontrado.\n"; return; }

    // limpa registos actuais antes de carregar
    for(int i=0;i<totalEst;i++)  delete estudantes[i];
    for(int i=0;i<totalProf;i++) delete professores[i];
    totalEst = totalProf = 0;

    string linha;
    while(getline(f, linha)) { // le linha a linha
        // separa os campos usando '|' como delimitador
        string campos[10]; int k=0; string tmp="";
        for(char ch : linha) {
            if(ch=='|') { campos[k++]=tmp; tmp=""; }
            else tmp+=ch;
        }
        campos[k]=tmp; // ultimo campo

        if(campos[0]=="E" && totalEst<10) {
            estudantes[totalEst++] = new Estudante(
                campos[1], stoi(campos[2]), campos[3],
                campos[4], campos[5],
                stod(campos[6]), stod(campos[7]), stod(campos[8])
            );
        } else if(campos[0]=="P" && totalProf<5) {
            professores[totalProf++] = new Professor(
                campos[1], stoi(campos[2]), campos[3],
                campos[4], campos[5], stod(campos[6])
            );
        }
    }
    f.close();
    cout << "Dados carregados: " << totalEst << " estudante(s), " << totalProf << " professor(es)\n";
}

// ---- menu ----
void exibirMenu() {
    cout << "\n========== MENU ==========\n";
    cout << " 1. Cadastrar estudante\n";
    cout << " 2. Cadastrar professor\n";
    cout << " 3. Mostrar estudantes\n";
    cout << " 4. Mostrar professores\n";
    cout << " 5. Pesquisar por nome\n";
    cout << " 6. Remover pessoa\n";
    cout << " 7. Verificar aprovacao\n";
    cout << " 8. Aumentar salario\n";
    cout << " 9. Salvar em ficheiro\n";
    cout << "10. Ler do ficheiro\n";
    cout << "11. Sair\n";
    cout << "Opcao: ";
}

int main() {
    // dados iniciais para teste
    estudantes[totalEst++] = new Estudante("Leyla Macuacua", 20,"F","E001","Informatica",15,13,16);
    estudantes[totalEst++] = new Estudante("Dercio Chipura", 21,"M","E002","Informatica",12,11,13);
    estudantes[totalEst++] = new Estudante("Joana Uelemo",   22,"F","E003","Informatica",18,17,19);
    estudantes[totalEst++] = new Estudante("Edwin Taimo",    20,"M","E004","Informatica", 9, 8, 7);
    professores[totalProf++] = new Professor("Prof. Carlos",45,"M","P001","Lab II C++",  85000);
    professores[totalProf++] = new Professor("Prof. Ana",   38,"F","P002","Estruturas",  92000);

    int opcao;
    do {
        exibirMenu();
        cin >> opcao; cin.ignore(); // le a opcao e limpa o buffer

        switch(opcao) {
            case 1:  cadastrarEstudante();  break;
            case 2:  cadastrarProfessor();  break;
            case 3:  mostrarEstudantes();   break;
            case 4:  mostrarProfessores();  break;
            case 5:  pesquisarPorNome();    break;
            case 6:  removerPessoa();       break;
            case 7:  verificarAprovacao();  break;
            case 8:  aumentarSalario();     break;
            case 9:  salvarFicheiro();      break;
            case 10: lerFicheiro();         break;
            case 11: cout << "Vamos Djimar! Ate logo.\n"; break;
            default: cout << "Opcao invalida.\n";
        }
    } while(opcao != 11); // repete ate escolher sair

    // liberta toda a memoria alocada com new
    for(int i=0;i<totalEst;i++)  delete estudantes[i];
    for(int i=0;i<totalProf;i++) delete professores[i];

    return 0;
}
