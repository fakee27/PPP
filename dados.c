#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"

/* ── Data ── */

Data criarData(int dia, int mes, int ano) {
    Data d = {dia, mes, ano};
    return d;
}

void imprimirData(Data d) {
    printf("%02d/%02d/%04d", d.dia, d.mes, d.ano);
}

/* ── Aluno ── */

Aluno *criarAluno(const char *nome, Data dataNasc, const char *curso, int ano, int numero, float saldo) {
    Aluno *a = (Aluno *)malloc(sizeof(Aluno));
    if (a == NULL) return NULL;

    strncpy(a->nome, nome, sizeof(a->nome) - 1);
    a->nome[sizeof(a->nome) - 1] = '\0';
    a->dataNascimento = dataNasc;
    strncpy(a->curso, curso, sizeof(a->curso) - 1);
    a->curso[sizeof(a->curso) - 1] = '\0';
    a->ano = ano;
    a->numero = numero;
    a->saldo = saldo;
    a->despesas = NULL;
    return a;
}

void imprimirAluno(const Aluno *a) {
    printf("%-30s | Nº %5d | Curso: %-20s | Ano: %d | Saldo: %.2f EUR | Nasc: ",
           a->nome, a->numero, a->curso, a->ano, a->saldo);
    imprimirData(a->dataNascimento);
    printf("\n");
}

void libertarAluno(Aluno *a) {
    if (a == NULL) return;
    NoDespesa *d = a->despesas;
    while (d != NULL) {
        NoDespesa *tmp = d->prox;
        free(d);
        d = tmp;
    }
    free(a);
}

/* ── Despesa ── */

NoDespesa *criarDespesa(float valor, const char *descricao, Data data) {
    NoDespesa *d = (NoDespesa *)malloc(sizeof(NoDespesa));
    if (d == NULL) return NULL;

    d->valor = valor;
    strncpy(d->descricao, descricao, sizeof(d->descricao) - 1);
    d->descricao[sizeof(d->descricao) - 1] = '\0';
    d->data = data;
    d->prox = NULL;
    return d;
}

void adicionarDespesa(Aluno *a, float valor, const char *descricao, Data data) {
    if (a == NULL || valor <= 0) return;

    NoDespesa *nova = criarDespesa(valor, descricao, data);
    if (nova == NULL) return;

    nova->prox = a->despesas;
    a->despesas = nova;
    a->saldo -= valor;
}

void imprimirDespesas(const Aluno *a) {
    if (a->despesas == NULL) {
        printf("  Sem despesas registadas.\n");
        return;
    }
    NoDespesa *d = a->despesas;
    while (d != NULL) {
        printf("  [");
        imprimirData(d->data);
        printf("] %-40s  %.2f EUR\n", d->descricao, d->valor);
        d = d->prox;
    }
}

/* ── Lista de Alunos ── */

void inicializarLista(ListaAlunos *lista) {
    lista->cabeca = NULL;
    lista->tamanho = 0;
}

/* Insere por ordem alfabética */
void inserirAluno(ListaAlunos *lista, Aluno *aluno) {
    NoAluno *novo = (NoAluno *)malloc(sizeof(NoAluno));
    if (novo == NULL) return;

    novo->aluno = aluno;
    novo->prox = NULL;

    /* Inserção ordenada pelo nome */
    if (lista->cabeca == NULL || strcmp(aluno->nome, lista->cabeca->aluno->nome) < 0) {
        novo->prox = lista->cabeca;
        lista->cabeca = novo;
    } else {
        NoAluno *atual = lista->cabeca;
        while (atual->prox != NULL && strcmp(aluno->nome, atual->prox->aluno->nome) >= 0)
            atual = atual->prox;
        novo->prox = atual->prox;
        atual->prox = novo;
    }

    lista->tamanho++;
}

int eliminarAluno(ListaAlunos *lista, int numero) {
    NoAluno *atual = lista->cabeca;
    NoAluno *anterior = NULL;

    while (atual != NULL) {
        if (atual->aluno->numero == numero) {
            if (anterior == NULL)
                lista->cabeca = atual->prox;
            else
                anterior->prox = atual->prox;

            libertarAluno(atual->aluno);
            free(atual);
            lista->tamanho--;
            return 1;
        }
        anterior = atual;
        atual = atual->prox;
    }
    return 0;
}

void listarAlunos(const ListaAlunos *lista) {
    if (lista->cabeca == NULL) {
        printf("Sem alunos registados.\n");
        return;
    }
    printf("%-30s | %-6s | %-20s | %-4s | %-10s\n",
           "Nome", "Numero", "Curso", "Ano", "Saldo");
    printf("%s\n", "-------------------------------+--------+----------------------+------+-----------");
    NoAluno *atual = lista->cabeca;
    while (atual != NULL) {
        imprimirAluno(atual->aluno);
        atual = atual->prox;
    }
    printf("Total: %d aluno(s)\n", lista->tamanho);
}

Aluno *encontrarAluno(const ListaAlunos *lista, int numero) {
    NoAluno *atual = lista->cabeca;
    while (atual != NULL) {
        if (atual->aluno->numero == numero)
            return atual->aluno;
        atual = atual->prox;
    }
    return NULL;
}

void carregarSaldo(Aluno *a, float valor) {
    if (a == NULL || valor <= 0) return;
    a->saldo += valor;
}

void libertarLista(ListaAlunos *lista) {
    NoAluno *atual = lista->cabeca;
    while (atual != NULL) {
        NoAluno *tmp = atual->prox;
        libertarAluno(atual->aluno);
        free(atual);
        atual = tmp;
    }
    lista->cabeca = NULL;
    lista->tamanho = 0;
}
