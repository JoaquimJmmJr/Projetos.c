#include <stdio.h>
#include <stdlib.h> //biblioteca do malloc
#include <string.h> //necessária para usar a função "strcspn" além das funções de string

typedef struct Data{
    int dia;
    int mes;
    int ano;
}Data;

typedef struct Registro{
    char nome[50];
    int idade;
    char RG[9];
    Data Entrada; // data em que o paciente foi registrado
    int id;       // identificação do paciente
    struct Registro* proximo;
}Registro;

// ===== ESTRUTURA DA LISTA (Item Cadastrar)=====
typedef struct Lista {
    struct Elista *inicio;
    int qtd;
} Lista;

typedef struct Elista {
    Registro *dados;
    struct Elista *proximo; 
} Elista;

Registro *inicializa_cadastro(){ 
    return NULL;
}
Registro* cadastrar_paciente(Registro* lista) {
    Registro* novo = (Registro*) malloc(sizeof(Registro));
    if (!novo) {
        printf("Erro de alocação de memória.\n");
        return lista;
    }

    printf("ID do paciente: ");
    scanf("%d", &novo->id);

    printf("Nome do paciente: ");
    getchar();                                    // Limpa o buffer
    fgets(novo->nome, sizeof(novo->nome), stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0'; // Remover '\n'

    printf("Idade: ");
    scanf("%d", &novo->idade);

    printf("RG: ");
    scanf("%s", novo->RG);

    printf("Data de registro (dd mm aaaa): ");
    scanf("%d %d %d", &novo->Entrada.dia, &novo->Entrada.mes, &novo->Entrada.ano);

    novo->proximo = lista;
    return novo; // novo passa a ser o início da lista
}
Registro* consultar_paciente(Registro *lista, int id){
    Registro *atual = lista;    //Cria o ponteiro "atual" para acessar os dados
    /* Encontra os dados do Paciente. */
    while (atual != NULL) {  
        if(atual->id == id){
            return atual;
        }
        atual = atual->proximo; //"atual" recebe o próximo paciente
    }
    return NULL;                //Paciente não encontrado
}
void mostrar_lista_completa(Registro* lista) {
    if (lista == NULL) {
        printf("\nNenhum paciente cadastrado.\n");
        return;
    }

    printf("\n==== Lista de Pacientes Cadastrados ====\n");
    Registro* atual = lista;
    int contador = 1;

    while (atual != NULL) {
        printf("%d) Nome: %s | Idade: %d | RG: %s | Data: %02d/%02d/%04d | ID: %d\n",
               contador, atual->nome, atual->idade, atual->RG,
               atual->Entrada.dia, atual->Entrada.mes, atual->Entrada.ano, atual->id);
        atual = atual->proximo;
        contador++;
    }
    printf("=========================================\n");
}
void atualizar_paciente(Registro *lista,int id){
    Registro* paciente = consultar_paciente(lista,id); 
    if(paciente == NULL){   
        printf("Paciente não encontrado.\n");
        return;
    }

    printf("Novo nome: ");
    getchar();
    fgets(paciente->nome, sizeof(paciente->nome), stdin);
    paciente->nome[strcspn(paciente->nome, "\n")] = '\0';

    printf("Nova idade: ");
    scanf("%d", &paciente->idade);

    printf("Novo RG: ");
    scanf("%s", paciente->RG);

    printf("Nova data de registro (dd mm aaaa): ");
    scanf("%d %d %d", &paciente->Entrada.dia, &paciente->Entrada.mes, &paciente->Entrada.ano);

    printf("Dados atualizados com sucesso!\n");
}
Registro* remover_paciente(Registro *lista, int id) {
    Registro *atual = lista; 
    Registro *anterior = NULL;

    /* Encontra o ID correto para remover os dados. */
    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Paciente com ID %d não encontrado.\n", id);
        return lista;                       
    }
  
    if (anterior == NULL) {
        // Remove o primeiro paciente da lista
        lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
  
    free(atual);                
    printf("Paciente removido com sucesso.\n");
    return lista;                  
}
void salvar_lista_em_arquivo(Registro* lista, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "w");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    Registro* atual = lista;
    while (atual != NULL) {
        fprintf(arquivo, "%d;%s;%d;%s;%02d;%02d;%04d\n",
                atual->id, atual->nome, atual->idade, atual->RG,
                atual->Entrada.dia, atual->Entrada.mes, atual->Entrada.ano);
        atual = atual->proximo;
    }

    fclose(arquivo);
    printf("Lista salva com sucesso em '%s'.\n", nome_arquivo);
}
Registro* carregar_lista_de_arquivo(const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        printf("Arquivo '%s' não encontrado.\n", nome_arquivo);
        return NULL;
    }

    Registro* lista = NULL;
    Registro* novo;
    int id, idade, dia, mes, ano;
    char nome[50], RG[9];

    while (fscanf(arquivo, "%d;%49[^;];%d;%8[^;];%d;%d;%d\n", 
                  &id, nome, &idade, RG, &dia, &mes, &ano) == 7) {
        novo = (Registro*) malloc(sizeof(Registro));
        if (!novo) {
            printf("Erro de memória.\n");
            break;
        }

        novo->id = id;
        strcpy(novo->nome, nome);
        novo->idade = idade;
        strcpy(novo->RG, RG);
        novo->Entrada.dia = dia;
        novo->Entrada.mes = mes;
        novo->Entrada.ano = ano;

        novo->proximo = lista;
        lista = novo;
    }

    fclose(arquivo);
    printf("Lista carregada com sucesso de '%s'.\n", nome_arquivo);
    return lista;
}
void liberar_lista(Registro* lista) {
    // Função para liberar toda a memória da lista encadeada
    Registro* atual = lista;
    while (atual != NULL) {
        Registro* temp = atual;
        atual = atual->proximo;
        free(temp); // Libera a memória alocada para cada paciente
    }
    printf("Memoria liberada com sucesso!\n");
}

// ===== ESTRUTURA DA FILA (Item Atendimento)=====
typedef struct Fila{
    struct Efila *head;
    struct Efila *tail;
    int qtd;
} Fila;

typedef struct Efila {
    struct Efila *anterior;
    Registro *paciente;          // Armazena o ponteiro para o paciente
    struct Efila *proximo;
} Efila;

Fila* criar_fila() {
    Fila* fila = malloc(sizeof(Fila));
    fila->head = NULL;
    fila->tail = NULL;
    fila->qtd = 0;
    return fila;
}
void enfileirar(Fila* fila, Registro* paciente) {
    Efila* nova = malloc(sizeof(Efila));
    nova->paciente = paciente;
    nova->proximo = NULL;
    nova->anterior = fila->tail;

    if (fila->qtd == 0) {
        fila->head = nova;
    } else {
        fila->tail->proximo = nova;
    }

    fila->tail = nova;
    fila->qtd++;

    printf("Paciente %s foi enfileirado com sucesso!\n", paciente->nome);
}
Registro* desenfileirar(Fila* fila, int mostrar) {
    if (fila->head == NULL) return NULL;

    Efila* removido = fila->head;
    Registro* paciente = removido->paciente;

    fila->head = fila->head->proximo;
    if (fila->head == NULL) {
        fila->tail = NULL;
    } else {
        fila->head->anterior = NULL;
    }

    free(removido);
    fila->qtd--;

    if (mostrar)
        printf("Paciente %s foi chamado para atendimento!\n", paciente->nome);

    return paciente;
}


void mostrar_fila(Fila* fila) {
    if (fila->qtd == 0) {
        printf("Fila de atendimento vazia.\n");
        return;
    }

    Efila* atual = fila->head;
    printf("\n=== Fila de Atendimento ===\n");
    int pos = 1;
    while (atual != NULL) {
        printf("%d) %s (ID: %d)\n", pos, atual->paciente->nome, atual->paciente->id);
        atual = atual->proximo;
        pos++;
    }
    printf("===========================\n");
}

// ===== ESTRUTURA DE HEAP (item Atendimento prioritário)=====
#define MAX_HEAP 100

typedef struct Heap {
    Registro* pacientes[MAX_HEAP];
    int tamanho;
} Heap;

Heap* criar_heap() {
    Heap* h = malloc(sizeof(Heap));
    h->tamanho = 0;
    return h;
}
void trocar(Registro** a, Registro** b) {
    Registro* temp = *a;
    *a = *b;
    *b = temp;
}
void subir_heap(Heap* h, int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;
        if (h->pacientes[i]->idade > h->pacientes[pai]->idade) {
            trocar(&h->pacientes[i], &h->pacientes[pai]);
            i = pai;
        } else break;
    }
}
void descer_heap(Heap* h, int i) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < h->tamanho && h->pacientes[esq]->idade > h->pacientes[maior]->idade)
        maior = esq;
    if (dir < h->tamanho && h->pacientes[dir]->idade > h->pacientes[maior]->idade)
        maior = dir;

    if (maior != i) {
        trocar(&h->pacientes[i], &h->pacientes[maior]);
        descer_heap(h, maior);
    }
}
void inserir_heap(Heap* h, Registro* paciente) {
    if (h->tamanho >= MAX_HEAP) {
        printf("Heap cheia!");
        return;
    }
    h->pacientes[h->tamanho] = paciente;
    subir_heap(h, h->tamanho);
    h->tamanho++;
    printf("Paciente %s inserido na fila prioritária.", paciente->nome);
}
Registro* remover_heap(Heap* h) {
    if (h->tamanho == 0) return NULL;
    Registro* removido = h->pacientes[0];
    h->tamanho--;
    h->pacientes[0] = h->pacientes[h->tamanho];
    descer_heap(h, 0);
    return removido;
}
void mostrar_heap(Heap* h) {
    if (h->tamanho == 0) {
        printf("Fila prioritária vazia.");
        return;
    }
    printf("--- Fila Prioritária (por idade) ---\n");
    for (int i = 0; i < h->tamanho; i++) {
        printf("%d) %s | Idade: %d\n", i + 1, h->pacientes[i]->nome, h->pacientes[i]->idade);
    }
}

// ===== ESTRUTURA DA ARVORE BINÁRIA DE BUSCA (Item Pesquisa)=====
typedef struct EABB{
	Registro *dados;
	struct EABB* FilhoEsq;
	struct EABB* FilhoDir;
} EABB;

typedef struct ABB{
	EABB* Raiz;
	int Qtde;
} ABB;

//Insere os pacientes por ano de registro
void inserir_na_ABB(EABB** raiz, Registro* paciente) {
    if (*raiz == NULL) {
        EABB* novo = (EABB*) malloc(sizeof(EABB));
        novo->dados = paciente;
        novo->FilhoEsq = NULL;
        novo->FilhoDir = NULL;
        *raiz = novo;
        return;
    }

    if (paciente->Entrada.ano < (*raiz)->dados->Entrada.ano) {
        inserir_na_ABB(&((*raiz)->FilhoEsq), paciente);
    } else {
        inserir_na_ABB(&((*raiz)->FilhoDir), paciente);
    }
}
//Cria a ABB e preenche com os pacientes da lista
ABB* criar_ABB() {
    ABB* arvore = (ABB*) malloc(sizeof(ABB));
    arvore->Raiz = NULL;
    arvore->Qtde = 0;
    return arvore;
}
void construir_ABB_com_lista(ABB* arvore, Registro* lista) {
    Registro* atual = lista;
    while (atual != NULL) {
        inserir_na_ABB(&(arvore->Raiz), atual);
        arvore->Qtde++;
        atual = atual->proximo;
    }
}
void mostrar_ordenado_ano(EABB* raiz) {
    if (raiz == NULL) return;

    mostrar_ordenado_ano(raiz->FilhoEsq);
    printf("Ano: %d | Nome: %s | ID: %d\n",
           raiz->dados->Entrada.ano, raiz->dados->nome, raiz->dados->id);
    mostrar_ordenado_ano(raiz->FilhoDir);
}
void inserir_em_lista(Elista** inicio, Registro* dados) {
    Elista* novo = malloc(sizeof(Elista));
    novo->dados = dados;
    novo->proximo = *inicio;
    *inicio = novo;
}
void coletar_em_lista(EABB* raiz, Elista** lista) {
    if (raiz == NULL) return;
    coletar_em_lista(raiz->FilhoEsq, lista);
    inserir_em_lista(lista, raiz->dados);
    coletar_em_lista(raiz->FilhoDir, lista);
}
//Mostra lista ordenada por idade
void ordenar_por_idade(Elista* lista) {
    for (Elista* i = lista; i != NULL; i = i->proximo) {
        for (Elista* j = i->proximo; j != NULL; j = j->proximo) {
            if (i->dados->idade > j->dados->idade) {
                Registro* temp = i->dados;
                i->dados = j->dados;
                j->dados = temp;
            }
        }
    }
}
void mostrar_lista_aux(Elista* lista, const char* criterio) {
    printf("\n--- Registros ordenados por %s ---\n", criterio);
    while (lista != NULL) {
        printf("Nome: %s | Idade: %d | RG: %s | Data: %02d/%02d/%04d | ID: %d\n",
               lista->dados->nome, lista->dados->idade, lista->dados->RG,
               lista->dados->Entrada.dia, lista->dados->Entrada.mes, lista->dados->Entrada.ano,
               lista->dados->id);
        lista = lista->proximo;
    }
}
void mostrar_ordenado_idade(EABB* raiz) {
    Elista* lista = NULL;
    coletar_em_lista(raiz, &lista);
    ordenar_por_idade(lista);
    mostrar_lista_aux(lista, "idade");
}
void mostrar_ordenado_mes(EABB* raiz) {
    Elista* lista = NULL;
    coletar_em_lista(raiz, &lista);
    for (Elista* i = lista; i != NULL; i = i->proximo) {
        for (Elista* j = i->proximo; j != NULL; j = j->proximo) {
            if (i->dados->Entrada.mes > j->dados->Entrada.mes) {
                Registro* temp = i->dados;
                i->dados = j->dados;
                j->dados = temp;
            }
        }
    }
    mostrar_lista_aux(lista, "mês");
}
void mostrar_ordenado_dia(EABB* raiz) {
    Elista* lista = NULL;
    coletar_em_lista(raiz, &lista);
    for (Elista* i = lista; i != NULL; i = i->proximo) {
        for (Elista* j = i->proximo; j != NULL; j = j->proximo) {
            if (i->dados->Entrada.dia > j->dados->Entrada.dia) {
                Registro* temp = i->dados;
                i->dados = j->dados;
                j->dados = temp;
            }
        }
    }
    mostrar_lista_aux(lista, "dia");
}

// ===== ESTRUTURA DE PILHA PARA DESFAZER (item Desfazer) =====
typedef struct Operacao {
    int tipo_operacao; // 1 = enfileirar, 2 = desenfileirar
    Registro* registro;
} Operacao;

typedef struct Celula {
    Operacao operacao;
    struct Celula* anterior;
} Celula;

typedef struct Stack {
    Celula* topo;
    int qtde;
} Stack;

Stack* criar_stack() {
    Stack* s = (Stack*) malloc(sizeof(Stack));
    s->topo = NULL;
    s->qtde = 0;
    return s;
}

void push(Stack* stack, int tipo, Registro* paciente) {
    Celula* nova = (Celula*) malloc(sizeof(Celula));
    nova->operacao.tipo_operacao = tipo;
    nova->operacao.registro = paciente;
    nova->anterior = stack->topo;
    stack->topo = nova;
    stack->qtde++;
}
Operacao pop(Stack* stack) {
    Operacao op = {0, NULL};
    if (stack->qtde == 0) return op;
    Celula* temp = stack->topo;
    op = temp->operacao;
    stack->topo = temp->anterior;
    free(temp);
    stack->qtde--;
    return op;
}
void desfazer(Stack* stack, Fila* fila) {
    if (stack->qtde == 0) {
        printf("Nenhuma operação para desfazer.\n");
        return;
    }

    Operacao op = stack->topo->operacao;

    printf("Deseja desfazer a operação: ");
    if (op.tipo_operacao == 1)
        printf("Enfileirar %s? (1-Sim/2-Nao): ", op.registro->nome);
    else if (op.tipo_operacao == 2)
        printf("Desenfileirar %s? (1-Sim/2-Nao): ", op.registro->nome);

    int resp;
    scanf("%d", &resp);
    if (resp != 1) return;

    pop(stack);  // Remove a operação do histórico

    if (op.tipo_operacao == 1) {
       desenfileirar(fila, 0); // não exibe mensagem e desfaz o enfileiramento
    } else if (op.tipo_operacao == 2) {
        enfileirar(fila, op.registro); // refaz o enfileiramento
    }

    printf("Operação desfeita com sucesso.\n");
}

void mostrar_log(Stack* stack) {
    if (stack->qtde == 0) {
        printf("Nenhuma operação registrada.");
        return;
    }
    printf("--- Histórico de Operações na Fila ---\n");
    Celula* atual = stack->topo;
    int i = stack->qtde;
    while (atual != NULL) {
        printf("%d) ", i--);
        if (atual->operacao.tipo_operacao == 1)
            printf("Enfileirou: %s\n", atual->operacao.registro->nome);
        else if (atual->operacao.tipo_operacao == 2)
            printf("Desenfileirou: %s\n", atual->operacao.registro->nome);
        atual = atual->anterior;
    }
}


// Menus:
void limpar_tela() {
    #ifdef _WIN32
        system("cls");    //Limpa o terminal do Windows
    #else
        system("clear");  //Limpa o terminal do MacOS ou Linux
    #endif
}
void exibir_menu() {
    printf("\n");
    printf("========================================\n");
    printf("       SISTEMA DE GERENCIAMENTO         \n");
    printf("             DE PACIENTES               \n");
    printf("========================================\n");
    printf("[1] Cadastrar\n");
    printf("[2] Gerenciar fila de atendimento\n");
    printf("[3] Atendimento Prioritário (Heap)\n");
    printf("[4] Pesquisa (Árvore de busca)\n");
    printf("[5] Desfazer operações da fila\n");
    printf("[6] Sair do sistema\n");
    printf("[7] Sobre\n");
    printf("========================================\n");
    printf("Escolha uma opcao: ");
}

//Item Cadastrar: LDE
void menu_lista(Registro** lista) {
    int opcao, id;
    Registro* encontrado;

    do {
        printf("\n--- Menu de Cadastro de Pacientes ---\n");
        printf("[1] Cadastrar novo paciente\n");
        printf("[2] Consultar paciente cadastrado\n");
        printf("[3] Mostrar lista completa de pacientes\n");
        printf("[4] Atualizar dados de um paciente\n");
        printf("[5] Remover paciente\n");
        printf("[0] Voltar ao menu principal\n");
        printf("---------------------------------------\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                *lista = cadastrar_paciente(*lista);
                break;

            case 2:
                printf("Informe o ID do paciente: ");
                scanf("%d", &id);
                encontrado = consultar_paciente(*lista, id);
                if (encontrado) {
                    printf("Paciente encontrado!\n");
                    printf("Nome: %s | Idade: %d | RG: %s | Data: %02d/%02d/%04d | ID: %d\n",
                           encontrado->nome, encontrado->idade, encontrado->RG,
                           encontrado->Entrada.dia, encontrado->Entrada.mes, encontrado->Entrada.ano,
                           encontrado->id);
                } else {
                    printf("Paciente com ID %d não encontrado.\n", id);
                }
                break;

            case 3:
                mostrar_lista_completa(*lista);
                break;

            case 4:
                printf("ID do paciente a atualizar: ");
                scanf("%d", &id);
                atualizar_paciente(*lista, id);
                break;

            case 5:
                printf("ID do paciente a remover: ");
                scanf("%d", &id);
                *lista = remover_paciente(*lista, id);
                break;

            case 0:
                printf("Retornando ao menu principal...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);
}
//Item Atendimento: Fila
void menu_fila(Fila* fila, Registro* lista, Stack* stack) {
    int escolha, id;
    do {
        printf("\n--- Fila de Atendimento ---\n");
        printf("[1] Enfileirar paciente\n");
        printf("[2] Desenfileirar paciente\n");
        printf("[3] Mostrar fila atual\n");
        printf("[0] Voltar ao menu principal\n");
        printf("-----------------------------\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("ID do paciente a enfileirar: ");
                scanf("%d", &id);
                Registro* p = consultar_paciente(lista, id);
                if (p) {
                    enfileirar(fila, p);
                    push(stack, 1, p); // 1 = enfileirar
                }
                else printf("Paciente não encontrado!\n");
                break;
            case 2:{
                Registro* desenf = desenfileirar(fila, 1); // exibe mensagem
                if (desenf != NULL){
                    push(stack, 2, desenf);
                }
                break;
            }
            case 3:
                mostrar_fila(fila);
                break;
            case 0:
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (escolha != 0);
}
// Atendimento prioritário com heap (ex: baseado na idade do paciente)
void menu_heap(Heap* heap, Registro* lista) {
    int opcao;
    do {
        printf("\n--- Atendimento Prioritário (Heap) ---\n");
        printf("[1] Inserir paciente na fila prioritária\n");
        printf("[2] Chamar próximo paciente prioritário\n");
        printf("[3] Mostrar fila prioritária atual\n");
        printf("[0] Voltar ao menu principal\n");
        printf("---------------------------------------\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int id;
            printf("ID do paciente a inserir: ");
            scanf("%d", &id);
            Registro* paciente = consultar_paciente(lista, id);
            if (paciente) inserir_heap(heap, paciente);
            else printf("Paciente não encontrado.");
        } else if (opcao == 2) {
            Registro* chamado = remover_heap(heap);
            if (chamado)
                printf("Paciente chamado: %s | Idade: %d", chamado->nome, chamado->idade);
            else
                printf("Nenhum paciente na fila prioritária.");
        } else if (opcao == 3) {
            mostrar_heap(heap);
        } else if (opcao != 0) {
            printf("Opção inválida.");
        }
    } while (opcao != 0);
}
//Item Pesquisa: Arvore binária de Busca 
void menu_abb(ABB* arvore) {
    int opcao;
    do {
        printf("\n--- Menu de Pesquisa (ABB) ---\n");
        printf("[1] Mostrar registros ordenados por ANO\n");
        printf("[2] Mostrar registros ordenados por MÊS\n");
        printf("[3] Mostrar registros ordenados por DIA\n");
        printf("[4] Mostrar registros ordenados por IDADE\n");
        printf("[0] Voltar ao menu principal\n");
        printf("---------------------------------------\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                mostrar_ordenado_ano(arvore->Raiz);
                break;
            case 2:
                mostrar_ordenado_mes(arvore->Raiz);
                break;
            case 3:
                mostrar_ordenado_dia(arvore->Raiz);
                break;
            case 4:
                mostrar_ordenado_idade(arvore->Raiz);
                break;
            case 0:
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);
}
//Item Sobre
void sobre(){
    printf("Aluno: Joaquim Jonkel Magalhães Melo Junior - R.A: 11.122.230-6\n");
    printf("Aluno: Rafael Oliveira Vale - R.A: 11.122.208-9\n");
    printf("Ciclo: 7ª Semestre\n");
    printf("Curso: Engenharia de Robôs\n");
    printf("Disciplina: Estrutura de dados (CCA230) Professor: Charles Henrique P. Ferreira\n");
    printf("Data de entrega: 14/05/2025\n");
}
void menu_fila(Fila* fila, Registro* lista, Stack* stack);
Registro* desenfileirar(Fila* fila, int mostrar);

int main() {
    Registro* lista = inicializa_cadastro(); // Começa a lista vazia
    Fila* fila = criar_fila();
    Heap* heap = criar_heap();
    ABB* arvore = criar_ABB();
    Stack* stack = criar_stack();

    limpar_tela();
    int opcao;
    int id;
    
    Registro* p1 = (Registro*) malloc(sizeof(Registro));
    strcpy(p1->nome, "Michael Jackson");    // strcpy é usado para copiar strings em C
    p1->idade = 51;
    strcpy(p1->RG, "459872431");            // strcpy também aqui
    p1->Entrada.dia = 25;
    p1->Entrada.mes = 6;
    p1->Entrada.ano = 2009;
    p1->id = 1;
    p1->proximo = lista;
    lista = p1;

    Registro* p2 = (Registro*) malloc(sizeof(Registro));
    strcpy(p2->nome, "Joaquim Jonkel");
    p2->idade = 21;
    strcpy(p2->RG, "123456789");
    p2->Entrada.dia = 16;
    p2->Entrada.mes = 8;
    p2->Entrada.ano = 2003;
    p2->id = 2;
    p2->proximo = lista;
    lista = p2;

    Registro* p3 = (Registro*) malloc(sizeof(Registro));
    strcpy(p3->nome, "Freddie Mercury");
    p3->idade = 45;
    strcpy(p3->RG, "987654321");
    p3->Entrada.dia = 24;
    p3->Entrada.mes = 11;
    p3->Entrada.ano = 1991;
    p3->id = 3;
    p3->proximo = lista;
    lista = p3;

    Registro* p4 = (Registro*) malloc(sizeof(Registro));
    strcpy(p4->nome, "Rafael Oliveira");
    p4->idade = 21;
    strcpy(p4->RG, "112233445");
    p4->Entrada.dia = 11;
    p4->Entrada.mes = 2;
    p4->Entrada.ano = 2003;
    p4->id = 4;
    p4->proximo = lista;
    lista = p4;

    Registro* p5 = (Registro*) malloc(sizeof(Registro));
    strcpy(p5->nome, "Airton Irokawa");
    p5->idade = 41;
    strcpy(p5->RG, "556677889");
    p5->Entrada.dia = 20;
    p5->Entrada.mes = 7;
    p5->Entrada.ano = 2017;
    p5->id = 5;
    p5->proximo = lista;
    lista = p5;

    do {
        exibir_menu();
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                menu_lista(&lista);
                break;
            case 2: {
                menu_fila(fila, lista, stack);
                break;
            }
            case 3:{
                menu_heap(heap,lista);
                break;
            }
            case 4:{
                construir_ABB_com_lista(arvore, lista);
                menu_abb(arvore);
                break;
            }
                break;
            case 5: {
                int op_desf;
                do {
                    printf("\n--------- Menu Desfazer --------\n");
                    printf("[1] Mostrar histórico de operações\n");
                    printf("[2] Desfazer última operação\n");
                    printf("[0] Voltar\n");
                    printf("----------------------------------\n");
                    printf("Escolha uma opção: ");
                    scanf("%d", &op_desf);

                    switch (op_desf) {
                        case 1:
                            mostrar_log(stack);
                            break;
                        case 2:
                            desfazer(stack, fila);
                            break;
                        case 0:
                            break;
                        default:
                            printf("Opção inválida.\n");
                    }
                } while (op_desf != 0);
                break;
            }
            case 6: {
                int resposta;
                printf("\nDeseja salvar a lista antes de sair? (1-Sim / 2-Nao): ");
                scanf("%d", &resposta);
                if (resposta == 1) {
                    salvar_lista_em_arquivo(lista, "pacientes.txt");
                    printf("Lista salva com sucesso.\n");
                } else {
                    printf("Saindo sem salvar alteracoes.\n");
                }
                liberar_lista(lista);
                printf("Programa encerrado.\n");
                break;
            }
            case 7:
                sobre();
                break;
            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 6);
    
    return 0;
}


