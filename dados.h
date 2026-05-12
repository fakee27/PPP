#ifndef DADOS_H
#define DADOS_H

/* ── Estruturas base ── */

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct NoDespesa {
    float valor;
    char descricao[100];
    Data data;
    struct NoDespesa *prox;
} NoDespesa;

typedef struct {
    char nome[100];
    Data dataNascimento;
    char curso[50];
    int ano;
    int numero;
    float saldo;
    NoDespesa *despesas;
} Aluno;

/* Nó da lista de alunos: apontador para o registo real */
typedef struct NoAluno {
    Aluno *aluno;
    struct NoAluno *prox;
} NoAluno;

typedef struct {
    NoAluno *cabeca;
    int tamanho;
} ListaAlunos;

/* ── Funções de Data ── */
Data criarData(int dia, int mes, int ano);
void imprimirData(Data d);

/* ── Funções de Aluno ── */
Aluno *criarAluno(const char *nome, Data dataNasc, const char *curso, int ano, int numero, float saldo);
void imprimirAluno(const Aluno *a);
void libertarAluno(Aluno *a);

/* ── Funções de Despesa ── */
NoDespesa *criarDespesa(float valor, const char *descricao, Data data);
void adicionarDespesa(Aluno *a, float valor, const char *descricao, Data data);
void imprimirDespesas(const Aluno *a);

/* ── Funções da Lista de Alunos ── */
void inicializarLista(ListaAlunos *lista);
void inserirAluno(ListaAlunos *lista, Aluno *aluno);
int eliminarAluno(ListaAlunos *lista, int numero);
void listarAlunos(const ListaAlunos *lista);
Aluno *encontrarAluno(const ListaAlunos *lista, int numero);
void carregarSaldo(Aluno *a, float valor);
void libertarLista(ListaAlunos *lista);

#endif
