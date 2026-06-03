# 🎓 Sistema de Gestão Universitária — Laboratório II (C++)

> **Licenciatura em Informática — 2.º Ano**  
> Teste de Laboratório II (C++) · Duração: 120 min · Data: 03/06/2026

---

## 👥 Membros do Grupo

| # | Nome | Número |
|---|------|--------|
| 1 | Leyla Gloria Macuacua | E001 |
| 2 | Dercio Filipe Chipura | E002 |
| 3 | Joana Assunção Uelemo | E003 |
| 4 | Edwin Jerry Joaquim Taimo Gema | E004 |

---

## 📋 Descrição do Projecto

Sistema de gestão universitária em C++ que implementa os conceitos de **Programação Orientada a Objectos**:

| Conceito | Como foi aplicado |
|----------|-------------------|
| **Encapsulamento** | Atributos `private`/`protected` + getters/setters públicos |
| **Herança** | `Estudante` e `Professor` herdam de `Pessoa` |
| **Polimorfismo** | `virtual` + `override` + vector de `Pessoa*` (Late Binding) |
| **Classe Abstrata** | `Pessoa` com método puramente virtual `mostrarDados() = 0` |
| **Ficheiros** | Gravação e leitura em `.txt` com `ofstream`/`ifstream` |
| **STL Vector** | Armazenamento dinâmico substituindo arrays fixos |

---

## 🏗️ Arquitectura das Classes

```
Pessoa  (classe abstrata)
│   - nome, idade, sexo  (protected)
│   - getters / setters  (public)
│   - mostrarDados() = 0 (puramente virtual)
│
├── Estudante
│       - numeroEstudante, curso, notas[3]
│       - calcularMedia()
│       - verificarAprovacao()
│       - mostrarDados() override
│
└── Professor
        - codigoProfessor, disciplina, salario
        - aumentarSalario(percentual)
        - mostrarDados() override

Sistema  (classe gerenciadora)
    - vector<Estudante>  (max 10)
    - vector<Professor>  (max 5)
    - cadastrar / listar / pesquisar / remover
    - salvarEmFicheiro / lerDeFicheiro
    - demonstrarPolimorfismo()
```

---

## ✅ Funcionalidades do Menu

```
 1. Cadastrar Estudante
 2. Cadastrar Professor
 3. Mostrar Estudantes
 4. Mostrar Professores
 5. Pesquisar Pessoa (por nome)
 6. Remover Pessoa
 7. Verificar Aprovação de Estudante
 8. Aumentar Salário de Professor
 9. Salvar Dados em Ficheiro (.txt)
10. Ler Dados do Ficheiro (.txt)
11. Demonstrar Polimorfismo (Late Binding)
12. Sair
```

---

## 📐 Critérios de Aprovação

| Estado | Condição |
|--------|----------|
| **DISPENSADO** | Média ≥ 14,0 |
| **ADMITIDO** | 10,0 ≤ Média < 14,0 |
| **REPROVADO** | Média < 10,0 |

---

## 🚀 Como Compilar e Executar

### Pré-requisitos
- Compilador C++ com suporte a C++11 ou superior (`g++`, `clang++`, MinGW, etc.)

### Linux / macOS
```bash
# Compilar
g++ -std=c++11 -Wall -o sistema sistema.cpp

# Executar
./sistema
```

### Windows (MinGW / cmd)
```cmd
g++ -std=c++11 -Wall -o sistema.exe sistema.cpp
sistema.exe
```

### Windows (PowerShell)
```powershell
g++ -std=c++11 -Wall -o sistema.exe sistema.cpp
.\sistema.exe
```

---

## 📁 Estrutura do Repositório

```
sistema_universitario/
│
├── sistema.cpp      ← código-fonte completo (comentado linha a linha)
├── README.md        ← este ficheiro
└── dados.txt        ← gerado automaticamente pela opção 9 do menu
```

---

## 💡 Nota sobre os Comentários

Cada linha de código possui um comentário `//` explicativo directamente após ela, descrevendo:
- **O quê** a instrução faz
- **Por quê** é necessária
- **Como** funciona internamente (ex: vtable, iteradores, stod/stoi)

---

*Vamos Djimar! 🎓*
