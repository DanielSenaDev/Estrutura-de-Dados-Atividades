#include <stdio.h>
#include <stdlib.h> //usado system
#include <ctype.h>  //usado toupper
#include <string.h> //usado strcmp

/// Variavel dinamica de String Auxiliar
struct TpStringAux
{
  char Palavra[20];
} StringAux;


struct TpFarma
{
  char Nome[20];
  float Preco;
  int QEstoque;
  int Ativo; // 0 excluido; 1 ativo
};

typedef struct TpFarma TpFARMA;
TpFARMA RgFarma;

FILE *ArqFarma;

long int Tamanho = sizeof(TpFARMA);

/// Calcula tamanho do arquivo
long int TArquivo()
{
  fseek(ArqFarma, 0, 2);
  long int R = ftell(ArqFarma) / Tamanho;
  return R;
}

/// Funcao para deixar palavra toda em maiusculo
void toUpperString(char palavra[])
{
  for (int i = 0; i < strlen(palavra); i++)
  {
    palavra[i] = toupper(palavra[i]);
  }
  return;
}

/// Funcao para receber nome do Farmaco e devolve o nome digitado com todas letras em maiusculo
char *pergunteNome()
{
  scanf("%s", StringAux.Palavra);
  toUpperString(StringAux.Palavra);
  return StringAux.Palavra;
}

// Abre arquivo de acordo com o parametro
/// Tipo 0: a+b (adicionar dados)
/// Tipo 1: r+b (alterar dados)
void AbrirArquivoTipo(int tipo)
{

  switch (tipo)
  {
  case 0:
    ArqFarma = fopen("Famacos.dat", "a+b");
    break;
  case 1:
    ArqFarma = fopen("Famacos.dat", "r+b");
    break;
  }
  return;
}

/// Inclui novo medicamento com nome, preco e quantidade definidos pelo usuario;
/// O medicamento eh ativado
void Incluir()
{
  char R;
  do
  {
    system("cls");
    printf("*** inclusao ***\n\n");
    printf("Nome: ");

    char Farmaco[20];

    strcpy(Farmaco, pergunteNome());

    if (ConsultarEspecifico(Farmaco) == 1)
    {
      printf("\n### ALGUM FARMACO JA FOI REGISTRADO COM ESTE NOME ###\n### COLOQUE OUTRO NOME ###\n");
      system("pause");
      return;
    }
    else
    {
      strcpy(RgFarma.Nome, Farmaco);

      printf("Preco: ");
      scanf("%f", &RgFarma.Preco);
      printf("Estoque: ");
      scanf("%d", &RgFarma.QEstoque);
      RgFarma.Ativo = 1; //ativa o medicamento
      fseek(ArqFarma, 0, 2);
      fwrite(&RgFarma, Tamanho, 1, ArqFarma);
      printf("\nNova inclusao? S/N ");
      scanf(" %c", &R);
      R = toupper(R);
    }
  } while (R != 'N');
  return;
}

/// Exclui o medicamento
void Excluir()
{
  fclose(ArqFarma);
  AbrirArquivoTipo(1); // r+b

  system("cls");
  printf("\n*** EXCLUSAO ***\n\n");

  printf("Qual farmaco deseja EXCLUIR? ");
  char Farmaco[20];
  strcpy(Farmaco, pergunteNome());

  if (ConsultarEspecifico(Farmaco) == 0)
  {
    printf("\nNOME DE MEDICAMENTO INVALIDO\n");
    system("pause");
    return;
  }

  char Certeza;
  printf("\nTEM Certeza QUE DESEJA EXCLUIR ESTE MEDICAMENTO?\nDigite S ou N: ");

  scanf(" %c", &Certeza);

  Certeza = toupper(Certeza);

  switch (Certeza)
  {
  case 'S':
    printf("\nEste medicamento sera EXCLUIDO\n");
    break;
  case 'N':
    printf("\nVOCE IRA VOLTAR AO INICIO\n");
    system("pause");
    return;
  default:
    printf("\nVALOR INVALIDO, VOCE IRA VOLTAR AO INICIO POR SEGURANCA\n");
    system("pause");
    return;
  }

  fseek(ArqFarma, 0, 0);
  int Achou = 0;
  do
  {
    fread(&RgFarma, Tamanho, 1, ArqFarma);
    if (strcmp(RgFarma.Nome, Farmaco) == 0)
    {
      if (RgFarma.Ativo == 1)
      {
        Achou = 1;
        RgFarma.Ativo = 0;
        printf(&RgFarma.Ativo);
        fseek(ArqFarma, -Tamanho, 1);
        fwrite(&RgFarma, Tamanho, 1, ArqFarma);
        printf("\nMEDICAMENTO EXCLUIDO\n");
      }
    }
  } while (!feof(ArqFarma) && (Achou == 0));

  system("pause");
  fclose(ArqFarma);
  AbrirArquivoTipo(0); // a+b
  return;
}

void Alterar()
{
  if (TArquivo() != 0)
  {
    fclose(ArqFarma);

    AbrirArquivoTipo(1); // r+b

    system("cls");
    printf("*** alterar ***\n\n");
    fseek(ArqFarma, 0, 0);
    printf("Qual farmaco? ");
    char Farmaco[20];

    strcpy(Farmaco, pergunteNome());

    int Achou = 0;
    do
    {
      fread(&RgFarma, Tamanho, 1, ArqFarma);
      if (strcmp(RgFarma.Nome, Farmaco) == 0)
      {
        if (RgFarma.Ativo == 1)
        {
          Achou = 1;
          printf("Nome: %s\n", RgFarma.Nome);
          printf("Valor: %f\n", RgFarma.Preco);
          printf("Estoque: %d\n", RgFarma.QEstoque);
        }
      }
    } while (!feof(ArqFarma) && (Achou == 0));
    if (Achou == 0)
      printf("Registro inexistente!");
    else
    {
      printf("Qual o novo preco? \n");
      scanf("%f", &RgFarma.Preco);
      printf("Qual a nova quantidade? \n");
      scanf("%d", &RgFarma.QEstoque);
      fseek(ArqFarma, -Tamanho, 1);
      fwrite(&RgFarma, Tamanho, 1, ArqFarma);
      printf(">>> Alteracao efetuada com sucesso! <<<\n");
    }
    system("pause");
    fclose(ArqFarma);

    AbrirArquivoTipo(0); // a+b
  }
  else
  {
    printf("Arquivo Vazio.  Nao existem dados a alterar.");
    system("pause");
  }
  return;
}

/// Consulta medicamento passando nome do farmaco no parametro
/// Retorna 0 se nao encontrar
/// Retorna 1 se encontrar
int ConsultarEspecifico(char Farmaco[20])
{

  int Achou = 0;

  fseek(ArqFarma, 0, 0);
  do
  {
    fread(&RgFarma, Tamanho, 1, ArqFarma);
    if (strcmp(RgFarma.Nome, Farmaco) == 0 && RgFarma.Ativo == 1)
    {
      Achou = 1;
    }
  } while (!feof(ArqFarma) && (Achou == 0));

  if (Achou == 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

/// Consulta todos medicamentos ativos
void Consultar()
{
  system("cls");
  printf("*** consulta ***\n\n");

  printf("Qual farmaco? ");
  char Farmaco[20];

  strcpy(Farmaco, pergunteNome());

  if (ConsultarEspecifico(Farmaco) == 1)
  {
    printf("\n");
    printf("Nome: %s\n", RgFarma.Nome);
    printf("Valor: %f\n", RgFarma.Preco);
    printf("Estoque: %d\n", RgFarma.QEstoque);
    printf("Ativo(1 para sim, 0 para nao): %d\n", RgFarma.Ativo);
    printf("\n");
  }
  else
  {
    printf("\nRegistro inexistente!\n");
  }
}

/// Lista todos medicamentos ativos
void LTodos()
{
  system("cls");
  printf("\n******************\n");
  printf("*** lista todos ***\n\n");
  fseek(ArqFarma, 0, 0);
  do
  {
    fread(&RgFarma, Tamanho, 1, ArqFarma);
    if (!feof(ArqFarma) && RgFarma.Ativo == 1)
    {
      printf("Nome: %s\n", RgFarma.Nome);
      printf("Valor: R$%.2f\n", RgFarma.Preco);
      printf("Estoque: %d\n", RgFarma.QEstoque);
      printf("***\n\n");
    }
  } while (!feof(ArqFarma));
  system("pause");
  return;
}

int main()
{
  AbrirArquivoTipo(0); // a+b;

  char Opcao;

  do
  {
    system("cls");
    printf("\n\n> > > Pague Pouco < < < \n\n");
    printf("Que deseja fazer? \n\n");
    printf("I - Incluir \n");
    printf("E - Excluir \n");
    printf("A - Alterar \n");
    printf("C - Consultar \n");
    printf("T - Listar Todos \n");
    printf("S - Sair \n\n");

    scanf(" %c", &Opcao);
    Opcao = toupper(Opcao);
    switch (Opcao)
    {
    case 'I':
      Incluir();
      break;
    case 'E':
      Excluir();
      break;
    case 'A':
      Alterar();
      break;
    case 'C':
      Consultar();
      system("pause");
      break;
    case 'T':
      LTodos();
      break;
    }
  } while (Opcao != 'S');
  fclose(ArqFarma);
  return 0;
}
