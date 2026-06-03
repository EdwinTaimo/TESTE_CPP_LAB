#include <iostream> // Biblioteca standard para comandos de entrada e saída (cout, cin)
#include <string>   // Biblioteca necessária para o uso e manipulação de variáveis do tipo string
#include <fstream>  // Biblioteca necessária para manipulação de arquivos/ficheiros (leitura e escrita)

using namespace std; // Evita a necessidade de usar o prefixo "std::" antes de comandos como cout e string

//==================== CLASSE PESSOA ====================

class Pessoa { // Declaração da classe abstrata Pessoa (Classe-Mãe)
protected: // Atributos protegidos: acessíveis apenas na própria classe e pelas classes filhas
    string nome;
    int idade;
    string sexo;

public:
    // Construtor de Pessoa: Inicializa os atributos protegidos usando os parâmetros recebidos
    Pessoa(string n, int i, string s) {
        nome = n;
        idade = i;
        sexo = s;
    }

    virtual ~Pessoa() {} // Destrutor virtual: Garante a correta libertação de memória ao destruir classes filhas

    // Métodos Getters: Permitem o acesso controlado aos valores das variáveis protegidas fora da classe
    string getNome() { return nome; }
    int getIdade() { return idade; }
    string getSexo() { return sexo; }

    // Métodos Setters: Permitem modificar os valores das variáveis protegidas fora da classe com segurança
    void setNome(string n) { nome = n; }
    void setIdade(int i) { idade = i; }
    void setSexo(string s) { sexo = s; }

    virtual void mostrarDados() = 0; // Função Virtual Pura: Torna esta classe abstrata e obriga as filhas a implementarem este método
};

//==================== CLASSE ESTUDANTE ====================

class Estudante : public Pessoa { // Classe Estudante que herda os atributos e métodos públicos/protegidos de Pessoa
private: // Atributos privados: Acessíveis somente dentro da própria classe Estudante
    string numeroEstudante;
    string curso;
    double notas[3]; // Vetor (array) estático para armazenar 3 notas

public:
    // Construtor de Estudante: Passa os dados comuns para o construtor da mãe (: Pessoa) e inicializa os dados específicos
    Estudante(string n, int i, string s,
              string num, string c,
              double n1, double n2, double n3)
        : Pessoa(n, i, s) {

        numeroEstudante = num;
        curso = c;

        // Armazena as notas fornecidas nas posições do vetor (índices 0, 1 e 2)
        notas[0] = n1;
        notas[1] = n2;
        notas[2] = n3;
    }

    string getNumero() { // Getter para ler o número de estudante fora da classe
        return numeroEstudante;
    }

    double calcularMedia() { // Método para somar as 3 notas e dividir por 3, retornando a média final
        return (notas[0] + notas[1] + notas[2]) / 3;
    }

    string verificarAprovacao() { // Analisa a média calculada e retorna uma string contendo a situação académica
        double media = calcularMedia();

        if(media >= 14)
            return "Dispensado"; // Caso a média seja maior ou igual a 14
        else if(media >= 10)
            return "Admitido";   // Caso a média esteja entre 10 e 13.9
        else
            return "Reprovado";  // Caso a média seja menor do que 10
    }

    void mostrarDados() override { // Implementação e sobreposição (override) da função virtual pura declarada na mãe
        cout << "\n===== ESTUDANTE =====\n";
        cout << "Nome: " << nome << endl; // Acede diretamente ao atributo protegido herdado da mãe
        cout << "Idade: " << idade << endl;
        cout << "Sexo: " << sexo << endl;
        cout << "Numero: " << numeroEstudante << endl;
        cout << "Curso: " << curso << endl;
        cout << "Media: " << calcularMedia() << endl; // Executa a função interna de média
        cout << "Estado: " << verificarAprovacao() << endl; // Executa a função interna de estado académico
    }
};

//==================== CLASSE PROFESSOR ====================

class Professor : public Pessoa { // Classe Professor que também herda da classe Pessoa
private: // Atributos privados específicos da entidade Professor
    string codigoProfessor;
    string disciplina;
    double salario;

public:
    // Construtor do Professor: Encaminha os dados base para a mãe e preenche as informações do docente
    Professor(string n, int i, string s,
              string cod, string disc,
              double sal)
        : Pessoa(n, i, s) {

        codigoProfessor = cod;
        disciplina = disc;
        salario = sal;
    }

    string getCodigo() { // Getter para aceder ao código identificador do professor
        return codigoProfessor;
    }

    void aumentarSalario(double percentual) { // Método para recalcular o salário adicionando uma percentagem de acréscimo
        salario += salario * percentual / 100;
    }

    void mostrarDados() override { // Implementação específica do método de exibição de dados para o Professor
        cout << "\n===== PROFESSOR =====\n";
        cout << "Nome: " << nome << endl;
        cout << "Idade: " << idade << endl;
        cout << "Sexo: " << sexo << endl;
        cout << "Codigo: " << codigoProfessor << endl;
        cout << "Disciplina: " << disciplina << endl;
        cout << "Salario: " << salario << endl;
    }
};

//==================== ARRAYS GLOBAL ====================

Estudante* estudantes[10]; // Array global de ponteiros capaz de armazenar os endereços de até 10 estudantes na memória Heap
Professor* professores[5]; // Array global de ponteiros capaz de armazenar os endereços de até 5 professores na memória Heap

int totalEstudantes = 0; // Contador de controlo global para monitorar quantos estudantes estão ativos no array
int totalProfessores = 0; // Contador de controlo global para monitorar quantos professores estão ativos no array

//==================== CADASTRAR ESTUDANTE ====================

void cadastrarEstudante() {

    if(totalEstudantes >= 10) { // Validação de segurança: Impede o transbordo (overflow) caso o array atinja o limite máximo de 10
        cout << "Limite de estudantes atingido!\n";
        return; // Interrompe e sai imediatamente da função
    }

    string nome, sexo, numero, curso;
    int idade;
    double n1, n2, n3;

    cout << "Nome: ";
    cin.ignore(); // Limpa o caractere de nova linha '\n' que sobra no buffer de entrada antes de ler texto
    getline(cin, nome); // Lê a linha completa introduzida pelo utilizador, permitindo nomes com espaços intermédios

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

    // Aloca dinamicamente na memória (usando o operador new) um objeto do tipo Estudante e guarda no array
    estudantes[totalEstudantes++] =
        new Estudante(nome, idade, sexo,
                      numero, curso,
                      n1, n2, n3); // O operador pós-fixado ++ incrementa o contador global após a atribuição
}

//==================== CADASTRAR PROFESSOR ====================

void cadastrarProfessor() {

    if(totalProfessores >= 5) { // Verifica se a lista de docentes já atingiu a capacidade máxima estipulada de 5 vagas
        cout << "Limite de professores atingido!\n";
        return; // Finaliza o fluxo da função de cadastro
    }

    string nome, sexo, codigo, disciplina;
    int idade;
    double salario;

    cout << "Nome: ";
    cin.ignore(); // Efetua a limpeza do buffer de entrada de dados
    getline(cin, nome); // Captura o nome completo digitado

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

    // Aloca um novo objeto Professor dinamicamente e coloca o seu endereço no índice atual do ponteiro
    professores[totalProfessores++] =
        new Professor(nome, idade, sexo,
                      codigo, disciplina,
                      salario); // Incrementa o contador totalProfessores logo de seguida
}

//==================== LISTAR ====================

void listarEstudantes() {
    for(int i=0; i<totalEstudantes; i++) // Percorre o array desde o índice zero até ao limite preenchido de estudantes
        estudantes[i]->mostrarDados(); // Utiliza o operador '->' para invocar o método através de um ponteiro de objeto
}

void listarProfessores() {
    for(int i=0; i<totalProfessores; i++) // Percorre o array de professores até a quantidade total registada
        professores[i]->mostrarDados(); // Executa a amostragem de dados de cada docente
}

//==================== PESQUISAR ====================

void pesquisarNome() {

    string nome;

    cout << "Nome: ";
    cin.ignore(); // Limpa o buffer de entrada do teclado
    getline(cin, nome); // Obtém o termo textual que será pesquisado no sistema

    // Varre a lista de estudantes fazendo uma busca linear comparando as strings com getNome()
    for(int i=0;i<totalEstudantes;i++)
        if(estudantes[i]->getNome() == nome) // Se o nome guardado no objeto for idêntico ao pesquisado
            estudantes[i]->mostrarDados(); // Exibe as informações completas deste estudante encontrado

    // Varre a lista de professores executando a mesma comparação linear por string
    for(int i=0;i<totalProfessores;i++)
        if(professores[i]->getNome() == nome) // Se houver correspondência com o nome do professor
            professores[i]->mostrarDados(); // Exibe as informações completas deste professor encontrado
}

//==================== POLIMORFISMO ====================

void mostrarPessoasPolimorficas() {

    Pessoa* pessoas[15]; // Declara um array temporário de ponteiros do tipo genérico Pessoa (Classe-Mãe)
    int total = 0; // Variável local para gerir os índices deste array unificado

    // Agrupa todos os ponteiros do vetor de estudantes dentro do vetor genérico de pessoas
    for(int i=0;i<totalEstudantes;i++)
        pessoas[total++] = estudantes[i]; // Atribuição permitida diretamente por conta do conceito de Herança

    // Agrupa todos os ponteiros do vetor de professores na sequência do mesmo vetor de pessoas
    for(int i=0;i<totalProfessores;i++)
        pessoas[total++] = professores[i];

    // Executa a amostragem de maneira polimórfica
    for(int i=0;i<total;i++)
        pessoas[i]->mostrarDados(); // Polimorfismo em ação: O compilador decide em tempo de execução se chama o mostrarDados() do Aluno ou do Professor
}

//==================== ARQUIVO ====================

void salvarArquivo() {

    ofstream arq("dados.txt"); // Instancia o objeto de escrita de arquivos e cria/abre o arquivo físico "dados.txt"

    arq << "Total estudantes: "
        << totalEstudantes << endl; // Grava a linha contendo o número total de estudantes inseridos

    arq << "Total professores: "
        << totalProfessores << endl; // Grava a linha contendo o número total de professores inseridos

    arq.close(); // Fecha o fluxo do arquivo para salvar as alterações e desalocar o recurso do sistema operacional

    cout << "Dados gravados!\n"; // Feedback visual para o utilizador
}

void lerArquivo() {

    ifstream arq("dados.txt"); // Instancia o objeto de leitura abrindo o arquivo existente "dados.txt"

    string linha; // Variável auxiliar para armazenar temporariamente cada linha lida do ficheiro

    // Executa a leitura linha por linha enquanto o ficheiro possuir conteúdo de texto disponível
    while(getline(arq, linha))
        cout << linha << endl; // Imprime diretamente na consola o conteúdo que acabou de ser extraído da linha do arquivo

    arq.close(); // Fecha o arquivo de leitura liberando o recurso de forma correta
}

//==================== MAIN ====================

int main() {

    int op; // Variável de armazenamento para capturar o código numérico da opção escolhida no menu

    do { // Laço condicional do-while para garantir a exibição inicial e repetitiva do menu de controlo

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
        cin >> op; // Aguarda e recebe o comando inserido pelo utilizador

        switch(op) { // Estrutura de decisão switch-case para direcionar o fluxo com base na opção escolhida

        case 1:
            cadastrarEstudante(); // Redireciona para o procedimento de cadastro de estudantes
            break; // Interrompe o switch para não executar as opções abaixo por acidente

        case 2:
            cadastrarProfessor(); // Redireciona para o procedimento de cadastro de professores
            break;

        case 3:
            listarEstudantes(); // Invoca a função responsável pela exibição de todos os alunos
            break;

        case 4:
            listarProfessores(); // Invoca a função responsável pela exibição de todos os professores
            break;

        case 5:
            pesquisarNome(); // Redireciona para a rotina de localização de registros nominais
            break;

        case 9:
            salvarArquivo(); // Direciona para o procedimento que cria o relatório de gravação em TXT
            break;

        case 10:
            lerArquivo(); // Direciona para o procedimento de leitura de texto e exibição na tela
            break;

        case 11:
            cout << "Encerrando...\n"; // Mensagem amigável de fechamento de sistema
            break;
            
        default:
            cout << "Opcao invalida!\n"; // Tratamento complementar opcional para escolhas fora do padrão numérico de 1 a 11
            break;
        }

    } while(op != 11); // O ciclo repetitivo continuará em execução enquanto o utilizador não digitar o número 11

    return 0; // Finaliza a rotina operacional informando ao sistema operacional que o programa fechou sem erros
}
