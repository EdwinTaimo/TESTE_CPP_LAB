#include <iostream> // Biblioteca padrão para fluxos de entrada e saída (permite usar cout para exibir dados e cin para ler o teclado)
#include <string>   // Biblioteca de classes nativa para manipulação e tratamento seguro de cadeias de caracteres (textos)
#include <fstream>  // Biblioteca de manipulação de fluxos de arquivos/ficheiros, permitindo abrir, gravar e ler dados em disco rígido

using namespace std; // Define o escopo global padrão 'std', liberando o uso direto de comandos como cout, cin e string sem o prefixo std::

//==================== CLASSE PESSOA ====================

class Pessoa { // Declaração da classe abstrata 'Pessoa' que funcionará como a Superclasse (Classe-Mãe) de todo o projeto
protected: // Modificador de acesso: Bloqueia o acesso externo total, mas permite que as variáveis sejam herdadas e usadas diretamente pelas classes filhas
    string nome; // Atributo protegido que armazena a identificação textual completa da pessoa
    int idade;   // Atributo protegido que armazena a idade numérica inteira da pessoa
    string sexo; // Atributo protegido que armazena a representação textual do gênero da pessoa

public: // Modificador de acesso: Torna todos os métodos abaixo públicos e visíveis por qualquer função ou classe externa
    // Construtor parametrizado: Executado ao criar o objeto para copiar as strings e inteiros recebidos para dentro dos atributos protegidos
    Pessoa(string n, int i, string s) {
        nome = n;
        idade = i;
        sexo = s;
    }

    // Destrutor virtual puro: Elemento vital em POO com herança. Garante que, ao apagar um ponteiro de Pessoa, o compilador limpe primeiro a memória da classe filha correspondente
    virtual ~Pessoa() {}

    // Métodos de Acesso (Getters): Funções públicas que retornam o valor de variáveis internas protegidas que estão blindadas de acessos externos directos
    string getNome() { return nome; }
    int getIdade() { return idade; }
    string getSexo() { return sexo; }

    // Métodos de Modificação (Setters): Funções públicas que permitem alterar de forma controlada os valores das variáveis protegidas por fora da classe
    void setNome(string n) { nome = n; }
    void setIdade(int i) { idade = i; }
    void setSexo(string s) { sexo = s; }

    // Função Virtual Pura: Declarada com '= 0', o que significa que não tem corpo aqui. Isto transforma a classe Pessoa em uma "Classe Abstrata" (Impossível de ser instanciada diretamente com 'new Pessoa') e obriga contratualmente todas as subclasses filhas a criarem as suas próprias versões deste método
    virtual void mostrarDados() = 0;
};

//==================== CLASSE ESTUDANTE ====================

class Estudante : public Pessoa { // Declaração da classe 'Estudante' aplicando Herança Pública (is-a / é-uma Pessoa), recebendo todos os atributos e métodos de Pessoa
private: // Atributos estritamente privados: Nenhuma classe fora de Estudante (nem mesmo a mãe Pessoa ou a main) consegue ler ou modificar estas variáveis diretamente
    string numeroEstudante; // Identificador/matrícula do estudante no sistema
    string curso;           // Nome do curso acadêmico que o estudante frequenta
    double notas[3];        // Vetor (array estático) interno capaz de guardar exatamente três notas com precisão decimal (double)

public:
    // Construtor parametrizado de Estudante: Utiliza a lista de inicialização ': Pessoa(n, i, s)' para repassar os dados comuns diretamente para o construtor da classe-mãe. No corpo do construtor, faz a cópia das variáveis específicas e preenche individualmente os índices 0, 1 e 2 do vetor de notas
    Estudante(string n, int i, string s,
              string num, string c,
              double n1, double n2, double n3)
        : Pessoa(n, i, s) {

        numeroEstudante = num;
        curso = c;

        notas[0] = n1; // Guarda a primeira nota na primeira posição do array (Índice 0)
        notas[1] = n2; // Guarda a segunda nota na segunda posição do array (Índice 1)
        notas[2] = n3; // Guarda a terceira nota na terceira posição do array (Índice 2)
    }

    // Getter específico para possibilitar ao sistema de gerenciamento ler o número de estudante sem quebrar o encapsulamento privado
    string getNumero() {
        return numeroEstudante;
    }

    // Método matemático simples: Realiza o somatório cumulativo das três notas armazenadas no vetor e divide o resultado por 3.0, devolvendo a média final calculada
    double calcularMedia() {
        return (notas[0] + notas[1] + notas[2]) / 3;
    }

    // Algoritmo de validação condicional: Avalia o retorno da função calcularMedia() e aplica a lógica de negócio acadêmica para retornar o veredito textual apropriado
    string verificarAprovacao() {
        double media = calcularMedia();

        if(media >= 14)
            return "Dispensado"; // Se a nota média final for estritamente igual ou superior a 14
        else if(media >= 10)
            return "Admitido";   // Se a nota média final estiver no intervalo de 10 a 13.99
        else
            return "Reprovado";  // Se a nota média final for estritamente menor do que 10
    }

    // Polimorfismo e Sobrescrita: O modificador 'override' prova ao compilador que estamos ativamente redefinindo a função virtual pura da classe-mãe com a lógica visual exclusiva para renderizar dados de estudantes
    void mostrarDados() override {
        cout << "\n===== ESTUDANTE =====\n";
        cout << "Nome: " << nome << endl; // Imprime a variável protegida 'nome' herdada legitimamente da classe mãe
        cout << "Idade: " << idade << endl;
        cout << "Sexo: " << sexo << endl;
        cout << "Numero: " << numeroEstudante << endl;
        cout << "Curso: " << curso << endl;
        cout << "Media: " << calcularMedia() << endl; // Executa o cálculo dinâmico da média no momento do print
        cout << "Estado: " << verificarAprovacao() << endl; // Executa a validação condicional de aprovação no momento do print
    }
};

//==================== CLASSE PROFESSOR ====================

class Professor : public Pessoa { // Declaração da classe 'Professor' que também herda diretamente a estrutura base da classe 'Pessoa'
private:
    string codigoProfessor; // Atributo privado que guarda o código de identificação funcional exclusivo do docente
    string disciplina;      // Atributo privado que armazena a cadeira/matéria que o professor leciona
    double salario;         // Atributo privado que controla os dados de vencimento financeiro do docente

public:
    // Construtor parametrizado de Professor: Invoca o construtor de Pessoa (:Pessoa) para validar nome, idade e sexo, e mapeia internamente as variáveis de identificação profissional e salário
    Professor(string n, int i, string s,
              string cod, string disc,
              double sal)
        : Pessoa(n, i, s) {

        codigoProfessor = cod;
        disciplina = disc;
        salario = sal;
    }

    // Getter específico para expor o código do professor de forma segura para as funções globais do sistema de busca ou remoção
    string getCodigo() {
        return codigoProfessor;
    }

    // Método de reajuste salarial: Recebe uma taxa em percentagem (ex: 15.0 para 15%), calcula o valor incremental e atualiza o montante acumulado na variável privada através do operador composto +=
    void aumentarSalario(double percentual) {
        salario += salario * percentual / 100;
    }

    // Implementação e sobrescrita polimórfica (override) da amostragem visual de dados, formatada especificamente para exibir as variáveis da entidade Professor
    void mostrarDados() override {
        cout << "\n===== PROFESSOR =====\n";
        cout << "Nome: " << nome << endl;
        cout << "Idade: " << idade << endl;
        cout << "Sexo: " << sexo << endl;
        cout << "Codigo: " << codigoProfessor << endl;
        cout << "Disciplina: " << disciplina << endl;
        cout << "Salario: " << salario << " MT" << endl;
    }
};

//==================== VETORES E CONTADORES GLOBAIS ====================

// Alocação estática de Vetores de Ponteiros: Criamos estruturas globais que não armazenam os objetos diretamente, mas sim os endereços hexadecimais (ponteiros '*') onde os objetos de fato residem dentro da memória RAM dinâmica (Heap)
Estudante* estudantes[10]; // Cria espaço para monitorar o endereço de até 10 estudantes em simultâneo
Professor* professores[5];  // Cria espaço para monitorar o endereço de até 5 professores em simultâneo

int totalEstudantes = 0;   // Inteiro de controle global atuando como índice dinâmico e contador de registros ativos de alunos
int totalProfessores = 0;  // Inteiro de controle global atuando como índice dinâmico e contador de registros ativos de docentes

//==================== CADASTRAR ESTUDANTE ====================

void cadastrarEstudante() {
    // Tratamento de transbordo (Buffer Overflow): Valida se o contador atingiu o tamanho estático máximo do vetor (10) para evitar gravação em espaço inválido de memória
    if(totalEstudantes >= 10) {
        cout << "Limite de estudantes atingido!\n";
        return; // Interrompe imediatamente o fluxo de execução da função e retorna ao menu
    }

    // Variáveis locais temporárias criadas na Stack para receber dados transitórios do terminal teclado
    string nome, sexo, numero, curso;
    int idade;
    double n1, n2, n3;

    cout << "Nome: ";
    cin.ignore(); // Crucial: Limpa caracteres residuais de quebra de linha ('\n') deixados no buffer do teclado por leituras numéricas anteriores
    getline(cin, nome); // Captura toda a string digitada incluindo espaços vazios (ex: "Edwin Taimo"), evitando que o espaço quebre a leitura

    cout << "Idade: "; cin >> idade;
    cout << "Sexo: "; cin >> sexo;
    cout << "Numero: "; cin >> numero;
    cout << "Curso: "; cin >> curso;
    cout << "Nota 1: "; cin >> n1;
    cout << "Nota 2: "; cin >> n2;
    cout << "Nota 3: "; cin >> n3;

    // Alocação Dinâmica de Memória: O operador 'new' reserva fisicamente um bloco de memória na Heap para construir um objeto Estudante permanente. O endereço dessa alocação é atribuído à posição atual do vetor e, em seguida, o operador pós-fixado '++' adiciona 1 unidade ao contador 'totalEstudantes'
    estudantes[totalEstudantes++] =
        new Estudante(nome, idade, sexo,
                      numero, curso,
                      n1, n2, n3);
    cout << "Estudante cadastrado com sucesso!\n";
}

//==================== CADASTRAR PROFESSOR ====================

void cadastrarProfessor() {
    // Validação preventiva de estouro de vetor: Garante que o sistema nunca tente popular além do índice 4 (limite de 5 vagas para docentes)
    if(totalProfessores >= 5) {
        cout << "Limite de professores atingido!\n";
        return; 
    }

    string nome, sexo, codigo, disciplina;
    int idade;
    double salario;

    cout << "Nome: ";
    cin.ignore(); // Higieniza o buffer de entrada removendo lixo ou caracteres '\n' pendentes
    getline(cin, nome); // Efetua a captura da string nominal de forma integral

    cout << "Idade: "; cin >> idade;
    cout << "Sexo: "; cin >> sexo;
    cout << "Codigo: "; cin >> codigo;
    cout << "Disciplina: "; cin >> disciplina;
    cout << "Salario: "; cin >> salario;

    // Constrói dinamicamente o objeto Professor na Heap, armazena o ponteiro gerado na posição controlada pelo índice e incrementa o contador global de professores logo após
    professores[totalProfessores++] =
        new Professor(nome, idade, sexo,
                      codigo, disciplina,
                      salario);
    cout << "Professor cadastrado com sucesso!\n";
}

//==================== LISTAR ====================

void listarEstudantes() {
    if(totalEstudantes == 0) { cout << "Nenhum estudante cadastrado.\n"; return; }
    // Loop de iteração linear: Inicia em 0 e caminha sequencialmente até o número exato de elementos inseridos
    for(int i=0; i<totalEstudantes; i++)
        estudantes[i]->mostrarDados(); // Usa a seta de indireção '->' porque 'estudantes[i]' é um ponteiro. Invoca a função de exibição do objeto apontado
}

void listarProfessores() {
    if(totalProfessores == 0) { cout << "Nenhum professor cadastrado.\n"; return; }
    // Percorre ciclicamente o vetor de controle de docentes executando a rotina de saída de dados
    for(int i=0; i<totalProfessores; i++)
        professores[i]->mostrarDados();
}

//==================== PESQUISAR ====================

void pesquisarNome() {
    string nome;
    cout << "Nome para pesquisar: ";
    cin.ignore();
    getline(cin, nome); // Lê o termo de busca fornecido pelo utilizador

    bool encontrado = false; // Flag booleana (sinalizador) para monitorar se alguma correspondência foi achada

    // Pesquisa linear no vetor de estudantes utilizando comparação de igualdade de strings (==) com o getter getNome()
    for(int i=0; i<totalEstudantes; i++) {
        if(estudantes[i]->getNome() == nome) {
            estudantes[i]->mostrarDados(); // Se encontrar igualdade perfeita, dispara a impressão dos dados
            encontrado = true; // Atualiza o estado do sinalizador comprovando o sucesso da busca
        }
    }

    // Pesquisa linear no vetor de professores buscando pelo mesmo termo informado
    for(int i=0; i<totalProfessores; i++) {
        if(professores[i]->getNome() == nome) {
            professores[i]->mostrarDados();
            encontrado = true;
        }
    }

    if(!encontrado) // Condicional executada se e somente se a flag booleana passou intacta pelos dois loops permanecendo falsa
        cout << "Nenhum registo encontrado com o nome fornecido.\n";
}

//==================== FUNÇÃO REMOVER (ADICIONADA) ====================

void removerPessoa() {
    string chave;
    cout << "Digite o Numero do Estudante ou Codigo do Professor para remover: ";
    cin >> chave; // Recebe o identificador alfa-numérico exclusivo do registro a ser extinto

    // 1º BLOCO: Tentativa de remoção no array de Estudantes
    for(int i = 0; i < totalEstudantes; i++) {
        if(estudantes[i]->getNumero() == chave) { // Verifica se o número do estudante confere com a chave digitada
            delete estudantes[i]; // DESALOCAÇÃO: Libera fisicamente o espaço ocupado pelo objeto na memória Heap, prevenindo vazamentos de memória (Memory Leak)
            
            // Loop de Compactação/Deslocamento (Shift Left): Arrasta todos os elementos subsequentes uma casa para trás, preenchendo a vaga que ficou nula no meio do vetor
            for(int j = i; j < totalEstudantes - 1; j++) {
                estudantes[j] = estudantes[j + 1]; // O ponteiro atual recebe o endereço guardado no ponteiro da frente
            }
            totalEstudantes--; // Decrementa em 1 unidade o total de estudantes para atualizar a nova realidade do sistema
            cout << "Estudante removido do sistema com sucesso!\n";
            return; // Aborta e encerra a função de remoção imediatamente, pois o alvo já foi localizado e destruído
        }
    }

    // 2º BLOCO: Tentativa de remoção no array de Professores (caso não tenha encontrado no bloco acima)
    for(int i = 0; i < totalProfessores; i++) {
        if(professores[i]->getCodigo() == chave) { // Realiza o teste lógico comparando o código funcional do docente
            delete professores[i]; // Apaga o objeto professor da memória RAM de forma limpa
            
            // Aplica a mesma lógica de reorganização e compactação de posições no array de professores
            for(int j = i; j < totalProfessores - 1; j++) {
                professores[j] = professores[j + 1];
            }
            totalProfessores--; // Decrementa a contagem de professores ativos
            cout << "Professor removido do sistema com sucesso!\n";
            return; // Finaliza o fluxo operacional
        }
    }

    // Mensagem disparada caso o fluxo de execução passe de forma limpa por ambos os ciclos de busca sem dar match com nenhuma chave
    cout << "Identificador invalido! Registro nao encontrado no sistema.\n";
}

//==================== VERIFICAR APROVAÇÃO (ADICIONADA ADAPTAÇÃO) ====================

void verificarAprovacaoDireta() {
    string num;
    cout << "Digite o Numero do Estudante: ";
    cin >> num;
    for(int i=0; i<totalEstudantes; i++) {
        if(estudantes[i]->getNumero() == num) {
            cout << "O estudante " << estudantes[i]->getNome() 
                 << " tem media: " << estudantes[i]->calcularMedia() 
                 << " e status: " << estudantes[i]->verificarAprovacao() << endl;
            return;
        }
    }
    cout << "Estudante nao encontrado.\n";
}

//==================== AUMENTAR SALÁRIO (ADICIONADA ADAPTAÇÃO) ====================

void aplicarAumentoProfessor() {
    string cod;
    double perc;
    cout << "Digite o Codigo do Professor: ";
    cin >> cod;
    cout << "Percentagem de aumento: ";
    cin >> perc;
    for(int i=0; i<totalProfessores; i++) {
        if(professores[i]->getCodigo() == cod) {
            professores[i]->aumentarSalario(perc);
            cout << "Salario reajustado! Novos dados:\n";
            professores[i]->mostrarDados();
            return;
        }
    }
    cout << "Professor nao encontrado.\n";
}

//==================== ARQUIVO ====================

void salvarArquivo() {
    // Instancia um fluxo de gravação de arquivos 'ofstream' que cria de forma automatizada o documento "dados.txt" no diretório local do projeto
    ofstream arq("dados.txt");

    // Validação de abertura: Verifica se o sistema operacional concedeu permissão e conseguiu criar o arquivo em disco
    if(!arq.is_open()) {
        cout << "Erro ao abrir o ficheiro para gravar dados!\n";
        return;
    }

    // Grava dados estruturados no formato de texto legível por humanos dentro do documento
    arq << "Total estudantes: " << totalEstudantes << endl;
    arq << "Total professores: " << totalProfessores << endl;

    arq.close(); // Fecha o fluxo físico de dados, consolidando a gravação dos dados gravados e liberando o descritor de arquivo para o SO
    cout << "Dados gravados e guardados no arquivo com sucesso!\n";
}

void lerArquivo() {
    // Instancia o fluxo de leitura de arquivos 'ifstream' buscando pelo documento "dados.txt"
    ifstream arq("dados.txt");

    // Validação de existência: Protege o sistema contra travamentos caso o usuário tente ler um arquivo inexistente
    if(!arq.is_open()) {
        cout << "Arquivo 'dados.txt' nao encontrado ou indisponivel no momento!\n";
        return;
    }

    string linha; // String auxiliar para reter temporariamente cada fragmento de texto extraído do disco

    // Loop de Varredura por Linha: Executa continuadamente a extração de uma linha textual inteira enquanto houver dados remanescentes no documento
    while(getline(arq, linha))
        cout << linha << endl; // Imprime diretamente no monitor a linha de texto recuperada

    arq.close(); // Libera os recursos associados ao arquivo fechado
}

//==================== MAIN ====================

int main() {
    int op; // Aloca uma variável inteira na Stack encarregada de mapear a decisão numérica do menu informada pelo utilizador

    do { // Inicia a construção do laço de controle do-while para garantir a persistência cíclica da interface de texto do menu

        cout << "\n===== MENU DE GERENCIAMENTO =====\n";
        cout << "1. Cadastrar estudante\n";
        cout << "2. Cadastrar professor\n";
        cout << "3. Mostrar estudantes\n";
        cout << "4. Mostrar professores\n";
        cout << "5. Pesquisar pessoa por nome\n";
        cout << "6. Remover pessoa (Estudante/Professor)\n"; // Agora integrada nativamente ao fluxo do switch
        cout << "7. Verificar aprovacao de estudante\n";
        cout << "8. Aumentar salario de professor\n";
        cout << "9. Salvar dados em arquivo\n";
        cout << "10. Ler dados do arquivo\n";
        cout << "11. Sair do programa\n";
        cout << "Opcao: ";
        cin >> op; // Retém e armazena o caractere operacional introduzido

        switch(op) { // Avaliador Switch-Case: Redireciona a linha de processamento de forma limpa de acordo com a opção mapeada

        case 1:
            cadastrarEstudante(); // Desvia para a rotina de input e alocação dinâmica de um novo Aluno
            break; // Interrompe o Switch evitando o vazamento em cascata (fall-through) para as opções seguintes

        case 2:
            cadastrarProfessor(); // Desvia para a rotina de input e alocação dinâmica de um novo Docente
            break;

        case 3:
            listarEstudantes(); // Aciona a exibição em lote de todos os registros estudantis mapeados
            break;

        case 4:
            listarProfessores(); // Aciona a exibição em lote de todos os registros de professores mapeados
            break;

        case 5:
            pesquisarNome(); // Desvia para o procedimento de localização nominal linear
            break;

        case 6:
            removerPessoa(); // Invoca a nova rotina adicionada encarregada da destruição do objeto e deslocamento de posições
            break;

        case 7:
            verificarAprovacaoDireta(); // Executa o método para localizar aluno por matrícula e exibir se está aprovado
            break;

        case 8:
            aplicarAumentoProfessor(); // Executa o reajuste salarial do docente escolhido
            break;

        case 9:
            salvarArquivo(); // Dispara o motor de persistência estruturada em formato .txt
            break;

        case 10:
            lerArquivo(); // Dispara o motor de leitura sequencial de dados em disco
            break;

        case 11:
            cout << "Encerrando o sistema e limpando buffers...\n"; // Sinalização amigável de fechamento do sistema
            break;

        default:
            cout << "Opcao invalida! Selecione um comando valido contido no Menu.\n"; // Tratamento de exceção para escolhas numéricas errôneas
            break;
        }

    } while(op != 11); // Mantém o programa em loop perene até que a opção de encerramento número 11 seja explicitamente selecionada

    // O programa limpa a memória global ao encerrar de vez
    for(int i=0; i<totalEstudantes; i++) delete estudantes[i];
    for(int i=0; i<totalProfessores; i++) delete professores[i];

    return 0; // Informa com sucesso ao sistema operacional que o programa executou e foi finalizado sem a ocorrência de anomalias ou falhas
}
