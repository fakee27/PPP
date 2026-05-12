#include <stdio.h>
#include "dados.h"

int main(void) {
    ListaAlunos lista;
    inicializarLista(&lista);

    /* Teste das estruturas e funções */
    Data nasc1 = criarData(15, 3, 2004);
    Data nasc2 = criarData(22, 7, 2003);

    Aluno *a1 = criarAluno("Maria Silva", nasc1, "Eng. Informatica", 2, 12345, 20.00f);
    Aluno *a2 = criarAluno("Ana Costa", nasc2, "Eng. Informatica", 3, 67890, 15.50f);

    inserirAluno(&lista, a1);
    inserirAluno(&lista, a2);

    printf("=== Lista de Alunos ===\n");
    listarAlunos(&lista);

    printf("\n=== Despesas de Maria Silva ===\n");
    adicionarDespesa(a1, 2.50f, "Cafe", criarData(12, 5, 2026));
    adicionarDespesa(a1, 4.00f, "Almoco", criarData(12, 5, 2026));
    imprimirDespesas(a1);
    printf("Saldo apos despesas: %.2f EUR\n", a1->saldo);

    printf("\n=== Carregar saldo de Ana Costa (+10.00) ===\n");
    carregarSaldo(a2, 10.00f);
    printf("Novo saldo: %.2f EUR\n", a2->saldo);

    printf("\n=== Eliminar Maria Silva (nº 12345) ===\n");
    eliminarAluno(&lista, 12345);
    listarAlunos(&lista);

    libertarLista(&lista);
    return 0;
}
