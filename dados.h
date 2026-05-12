#ifndef DADOS_H
#define DADOS_H

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

typedef struct NoAluno {
    Aluno *aluno;
    struct NoAluno *prox;
} NoAluno;

typedef struct {
    NoAluno *cabeca;
    int tamanho;
} ListaAlunos;
