#include<stdlib.h>
#include<stdio.h>
#include<locale.h>
#include<string.h>
#include<time.h>


typedef struct produto
{
    int cod_prod;
    char nome[50];
    float preco;
    int qtd;
} Prod;
typedef struct venda
{
    int cod_vend;
    Prod prod_vend;
    int qtd;
    float valor_tot_vend;
} vend;

void Cad_produto(Prod a[], int *qtd)
{
    int aux = *qtd;

    printf("\t================================================");
    int i, intermed;
    do
    {
        printf("\n\t Digite o Código do Produto[%d]: ", aux);
        scanf("%d", &intermed);
        while ((getchar()) != '\n');

        for (i = 0; i < aux; i++)
        {
            if (a[i].cod_prod == intermed)
            {
                printf("\n\t Código de produto já existe. Por favor, digite outro.\n");
                break;
            }
        }
    } while (i < aux);
    a[aux].cod_prod = intermed;

    printf("\t Digite o Nome do Produto [%d]: ", aux);
    fgets(a[aux].nome, sizeof(a[aux].nome), stdin);
    a[aux].nome[strcspn(a[aux].nome, "\n")] = 0;

    printf("\t Digite o Preço do Produto [%d]: ", aux);
    scanf("%f", &a[aux].preco);
    while ((getchar()) != '\n');

    printf("\t Digite a Quantidade em Estoque [%d]:", aux);
    scanf("%d", &a[aux].qtd);
    while ((getchar()) != '\n');

    printf("\t================================================\n\n\t");
    system("pause");
    aux++;
    *qtd = aux;
}

void lista_pd (Prod a[], int i)
{

    while(i>0)
    {
        if (a[i-1].qtd!=0)
        {
        printf("\n\t========================================");
        printf("\n\t Código:%d",a[i-1].cod_prod);
        printf("\n\t Nome:%s",a[i-1].nome);
        printf("\n\t Preço:R$ %.2f",a[i-1].preco);
        printf("\n\t Quantidades:%d",a[i-1].qtd);
        printf("\n\t========================================");
        printf("\n\n\t");
        }
        i--;
    }
    system("pause");
}

void reg_venda(vend b[], Prod a[], int *total_vendas_ptr, int total_produtos)
{
    int i, cod_produto_desejado, qtd_desejada;
    int produto_encontrado_idx = -1;

    printf("\n\t--- REGISTRAR NOVA VENDA ---\n");

    if (total_produtos == 0) {
        printf("\n\tNenhum produto cadastrado para realizar uma venda.\n");
        system("pause");
        system("cls");
        return;
    }

    printf("\n\t Qual o Código do Produto Desejado: ");
    scanf("%d", &cod_produto_desejado);

    for (i = 0; i < total_produtos; i++)
    {
       if (cod_produto_desejado == a[i].cod_prod)
       {
           produto_encontrado_idx = i;
           break;
       }
    }

    if (produto_encontrado_idx == -1)
    {
        printf("\n\t=============================");
        printf("\n\t Código de Produto Inexistente!");
        printf("\n\t=============================\n\n\t");
        system("pause");
    }
    else
    {
        printf("\n\t Quantas Unidades Desse Produto Deseja Comprar: ");
        scanf("%d", &qtd_desejada);

        if (qtd_desejada <= 0) {
            printf("\n\t======================================");
            printf("\n\t Quantidade de venda deve ser positiva!");
            printf("\n\t======================================\n\n\t");
            system("pause");
        }
        else if (qtd_desejada > a[produto_encontrado_idx].qtd)
        {
            printf("\n\t======================================");
            printf("\n\t Estoque Insuficiente! Apenas %d unidades disponiveis.", a[produto_encontrado_idx].qtd);
            printf("\n\t======================================\n\n\t");
            system("pause");
        }
        else
        {
            b[*total_vendas_ptr].cod_vend = *total_vendas_ptr + 1;

            strcpy(b[*total_vendas_ptr].prod_vend.nome, a[produto_encontrado_idx].nome);
            b[*total_vendas_ptr].prod_vend.cod_prod = a[produto_encontrado_idx].cod_prod;
            b[*total_vendas_ptr].prod_vend.preco = a[produto_encontrado_idx].preco;

            b[*total_vendas_ptr].qtd = qtd_desejada;
            b[*total_vendas_ptr].valor_tot_vend = a[produto_encontrado_idx].preco * qtd_desejada;

            a[produto_encontrado_idx].qtd -= qtd_desejada;

            printf("\n\t===========================================");
            printf("\n\t Venda Realizada Com Sucesso!");
            printf("\n\t Codigo da Venda: %d", b[*total_vendas_ptr].cod_vend);
            printf("\n\t===========================================\n\n\t");
            system("pause");

            if (a[produto_encontrado_idx].qtd == 0) {
                printf("\n\tATENCAO: Produto '%s' (Codigo: %d) agora esta EM FALTA no estoque!\n",
                       a[produto_encontrado_idx].nome, a[produto_encontrado_idx].cod_prod);
                system("pause");
            }

            (*total_vendas_ptr)++;
        }
    }
    system("cls");
}

void lista_pf (Prod a[], int i)
{
    int x=0;
    while(i>0)
    {
        if (a[i-1].qtd==0)
        {
        printf("\n\t==========================");
        printf("\n\t Código: %d",a[i-1].cod_prod);
        printf("\n\t Nome: %s",a[i-1].nome);
        printf("\n\t Preço: %.2f R$",a[i-1].preco);
        printf("\n\t Quantidade em Estoque: %d",a[i-1].qtd);
        printf("\n\t==========================\n\n\t");
        x=1;
        }
        i--;
    }
    if (x==0)
    {
    printf("\n\t======================================");
    printf("\n\t Nenhum Produto em Falta");
    printf("\n\t======================================");
    printf("\n\n\t");
    }
    system("pause");
}

void lista_vend(vend b[],int i)
{
     while(i>0)
    {
        if (b[i-1].qtd!=0)
        {
        printf("\n\t========================================");
        printf("\n\t Código: %d",b[i-1].cod_vend);
        printf("\n\t Código: %d",b[i-1].prod_vend.cod_prod);
        printf("\n\t Nome: %s",b[i-1].prod_vend.nome);
        printf("\n\t Preço: R$ %.2f",b[i-1].prod_vend.preco);
        printf("\n\t Quantidades: %d",b[i-1].qtd);
        printf("\n\t Valor Total da Venda: R$ %.2f",b[i-1].valor_tot_vend);
        printf("\n\t========================================");
        printf("\n\n\t");
        }
        i--;
    }
    system("pause");
}

void valor_total_vendas(vend b[],int i)
{
    int g;
    int tot=0;
    for (g=0;g<i;g++)
    {
        tot=tot+b[g].valor_tot_vend;
    }
    printf("\n\t=======================");
    printf("\n\tValor Total de Venda");
    printf("\n\t=======================");
    printf("\n\n\t Total: %d\n\n\t",tot);
    system("pause");
}

void total_vendas_por_produto(vend vendas[], int total_vendas, Prod produtos[], int total_produtos)
{
    printf("\n\t--- TOTAL DE VENDAS POR PRODUTO ---\n");
    if (total_vendas == 0) {
        printf("\n\tNenhuma venda registrada para gerar o relatório de vendas por produto.\n");
    } else {
        int qtd_vendida_por_prod[50] = {0};

        for (int k = 0; k < total_vendas; k++) {
            int codigo_do_produto_da_venda = vendas[k].prod_vend.cod_prod;
            int prod_idx = -1;
            for (int p = 0; p < total_produtos; p++) {
                if (produtos[p].cod_prod == codigo_do_produto_da_venda) {
                    prod_idx = p;
                    break;
                }
            }
            if (prod_idx != -1) {
                qtd_vendida_por_prod[prod_idx] += vendas[k].qtd;
            }
        }

        int produtos_vendidos_encontrados = 0;
        for (int p = 0; p < total_produtos; p++) {
            if (produtos[p].cod_prod != 0 && qtd_vendida_por_prod[p] > 0) {
                printf("\n\tProduto: %s (Codigo: %d) - Unidades Vendidas: %d",
                       produtos[p].nome, produtos[p].cod_prod, qtd_vendida_por_prod[p]);
                produtos_vendidos_encontrados = 1;
            }
        }
        if (!produtos_vendidos_encontrados) {
            printf("\n\tNenhum produto teve vendas registradas.\n");
        }
        printf("\n");
    }
    system("pause");
}


void produto_mais_vendido(vend vendas[], int total_vendas, Prod produtos[], int total_produtos)
{
    printf("\n\t--- PRODUTO MAIS VENDIDO ---\n");
    if (total_vendas == 0) {
        printf("\n\tNenhuma venda registrada para determinar o produto mais vendido.\n");
    } else {
        int qtd_vendida_por_prod[50] = {0};
        int produto_mais_vendido_idx = -1;
        int maior_qtd_vendida = -1;

        for (int k = 0; k < total_vendas; k++) {
            int codigo_do_produto_da_venda = vendas[k].prod_vend.cod_prod;
            int prod_idx = -1;
            for (int p = 0; p < total_produtos; p++) {
                if (produtos[p].cod_prod == codigo_do_produto_da_venda) {
                    prod_idx = p;
                    break;
                }
            }
            if (prod_idx != -1) {
                qtd_vendida_por_prod[prod_idx] += vendas[k].qtd;
            }
        }

        for (int p = 0; p < total_produtos; p++) {
            if (produtos[p].cod_prod != 0) {
                if (qtd_vendida_por_prod[p] > maior_qtd_vendida) {
                    maior_qtd_vendida = qtd_vendida_por_prod[p];
                    produto_mais_vendido_idx = p;
                }
            }
        }

        if (produto_mais_vendido_idx != -1 && maior_qtd_vendida > 0) {
            printf("\n\t Nome: %s", produtos[produto_mais_vendido_idx].nome);
            printf("\n\t Código: %d", produtos[produto_mais_vendido_idx].cod_prod);
            printf("\n\t Quantidade Total Vendida: %d\n", maior_qtd_vendida);
        } else {
            printf("\n\tNao foi possivel determinar o produto mais vendido (ou nenhum produto teve vendas).\n");
        }
    }
    system("pause");
}


void Gerar_relatorio (vend b[],int i,Prod a[],int j)
{
    int opcao2;

    printf("\n\t\t\t<==================>");
    printf("\n\t\t\t Gerar Relatório");
    printf("\n\t\t\t<==================>");
    printf("\n\n\t\t====================================");
    printf("\n\t\t\t 1 ===> Produto Mais Vendido");
    printf("\n\t\t\t 2 ===> Total de Venda por Produto");
    printf("\n\t\t\t 3 ===> Valor de Vendas Obtido");
    printf("\n\t\t\t 4 ===> Sair da Função");
    printf("\n\n\t\t====================================");
    printf("\n\n\t\tDigite a Opção Dada Acima: ");
    scanf("%d",&opcao2);
    system("cls");

    switch (opcao2)
    {
        case 1:
        produto_mais_vendido(b,i,a,j);
        break;

        case 2:
        total_vendas_por_produto(b,i,a,j);
        break;

        case 3:
        valor_total_vendas(b,i);
        break;

        default :
        break;
    }
}

int main ()
{
    int pmv=0;
    int k=1,qProd=0,dados,qVend=0;
    int lista_produtos_disponiveis[50];
    int lista_produtos_falta[50];
    int vendas_ate_agr=0;
    Prod produtos[50];
    vend venda[100];
    int opcao;

    while(k==1)
    {
        setlocale(LC_ALL,"portuguese");
        do
        {

        printf("\n\t\t\t<=====================================================>");
        printf("\n\t\t\t\t\t Bem Vindo ao Sistema");
        printf("\n\t\t\t<=====================================================>");
        printf("\n\n\t\t\t\t====================================");
        printf("\n\t\t\t\t 1 ===> Cadastrar um Produto");
        printf("\n\t\t\t\t 2 ===> Lista de Produto");
        printf("\n\t\t\t\t 3 ===> Registrar Venda");
        printf("\n\t\t\t\t 4 ===> Lista de Produtos em Falta");
        printf("\n\t\t\t\t 5 ===> Lista de Venda");
        printf("\n\t\t\t\t 6 ===> Relatório");
        printf("\n\t\t\t\t 7 ===> Sair do Sistema");
        printf("\n\t\t\t\t====================================");
        printf("\n\n\t\t\t Digite a opção Dada Acima: ");
        scanf("%d",&opcao);
        system("cls");

        if (opcao < 1 || opcao > 7)
        {
            system("cls");
            printf("\n\t============================================================");
            printf("\n\n\t INVALIDO!, Por favor Digite a Opção Novamente de 1 a 7");
            printf("\n\t============================================================\n\n\t");
        }
        } while (opcao < 1 || opcao > 7);
    system("cls");

    switch (opcao)
    {
        case 1:
        Cad_produto(produtos,&qProd);
        break;

        case 2:
        lista_pd(produtos,qProd);
        break;

        case 3:
        reg_venda(venda,produtos,&qVend,qProd);
        break;

        case 4:
        lista_pf(produtos,qProd);
        break;

        case 5:
        lista_vend(venda,qVend);
        break;

        case 6:
        Gerar_relatorio (venda,qVend,produtos,qProd);
        break;

        case 7:
        k=0;
        break;

        default:
            break;
    }
    system("cls");
    }
    return 0;
}
