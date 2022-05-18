#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <ctype.h>
#include <io.h>
#include <string.h>
#include <direct.h>

void MenuCli();
void menuPrincipal();

using namespace std;

struct dadosCli
{
  char nomeCli[20];
  char CPFC[20];
  int idadeCli;
  float sbaseCli;
  float vcomprasCli;

} Cliente;

struct dadosForn
{
  char nomeForn[20];
  char endeForn[30];
  char emailForn[30];
  char cnpj[20];
} Fornecedor;

struct dadosProd
{
  int codprod;
  char nomeprod[30];
  float valorUniprod;

} Produto;

struct dadosFunc
{
  char nomeFunc[20];
  char endeFunc[30];
  char emailFunc[30];
  char CPFF[20];
  float salario;
} Funcionario;

FILE *fClientes;
FILE *fFornecedores;
FILE *fProdutos;
FILE *fFuncionarios;
FILE *fAuxCli;
FILE *fAuxForn;
FILE *fAuxProd;
FILE *fAuxFunc;
int opc;
// incio do cliente
void criarArquivoCliente()
{
  if ((fClientes = fopen("clientes.dat", "a")) == NULL)
  {
    printf("\n Erro de criaþÒo do arquivo Clientes");
    return;
  }
  printf("\n Arquivo Clientes Criado");
  fclose(fClientes);
}

void cria_arqAuxCli()
{
  if ((fAuxCli = fopen("auxcli.dat", "a")) == NULL)
  {
    system("cls");
    printf("\n Erro de criaþÒo de arquivo AuxCli");
    return;
  }
  printf("\n Arquivo AuxCli Criado");
  fclose(fAuxCli);
}

void cadastrarCliente()
{
  char op;
  system("cls");
  int tamanho = 0;
  fClientes = fopen("clientes.dat", "r+");
  rewind(fClientes);
  do
  {
    fread(&Cliente, sizeof(Cliente), 1, fClientes);
    tamanho++;
  } while (!feof(fClientes));

  fseek(fClientes, sizeof(Cliente), tamanho);
  do
  {
    system("cls");
    cout << "\n Digite o nome do cliente:";
    cin >> Cliente.nomeCli;
    printf("\n Digite a idade:");
    cin >> Cliente.idadeCli;
    printf("\n Digite o salario base:");
    cin >> Cliente.sbaseCli;
    printf("\n Digite o valor da compra:");
    cin >> Cliente.vcomprasCli;
    tamanho = tamanho + fwrite(&Cliente, sizeof(struct dadosCli), 1, fClientes);

    printf("\n Continuar cadastrando <S> ou <N>:");
    cin >> op;
    op = toupper(op);
  } while (op == 'S');
  fclose(fClientes);
}

void consultarCliente()
{
  system("cls");
  fClientes = fopen("clientes.dat", "r");
  fseek(fClientes, sizeof(struct dadosCli), 0);

  while (fread(&Cliente, sizeof(Cliente), 1, fClientes) == 1)
  {
    system("cls");
    printf("Nome Cliente  :        %s\n", Cliente.nomeCli);
    printf("Idade Cliente :       %d\n", Cliente.idadeCli);
    printf("Salario Ciente:     %.2f\n", Cliente.sbaseCli);
    printf("Valor Compr Cliente: %.2f\n", Cliente.vcomprasCli);
    printf("\n Digite enter para continuar\n");
    getch();
  }
  printf("\n fim do arquivo");
  fclose(fClientes);
  getch();
}

void consultarNomeCliente()
{
  char nom_pro[20];
  int achou = 1;
  int localizou = 1;
  char op;

  system("cls");
  fClientes = fopen("clientes.dat", "r+");
  fseek(fClientes, sizeof(struct dadosCli), 0);
  printf("\n Digite o Nome p/ Procura : ");
  cin >> nom_pro;
  while (fread(&Cliente, sizeof(Cliente), 1, fClientes) == 1)
  {
    achou = strcmp(Cliente.nomeCli, nom_pro);
    if (achou == 0)
    {
      printf("\n O Nome é.................:%s", Cliente.nomeCli);
      printf("\n A Idade é................:%d", Cliente.idadeCli);
      printf("\n O Salßrio Bruto é........:%0.2f", Cliente.sbaseCli);
      printf("\n O Valor da Compra é......:%0.2f", Cliente.vcomprasCli);
      printf("\n_____________________________________________\n");
      getch();
      localizou = 0;
    }
  }

  if (localizou == 1)
  {
    printf("\n Cliente nÒo Cadastrado\n");
    printf("\n Cadastrar Cliente <S> ou <N>:");
    cin >> op;
    op = toupper(op);
    if (op == 'S')
    {
      cadastrarCliente();
    }
    else
    {
      fclose(fClientes);
    }
    getch();
  }
}

void alterarCliente()
{
  char nom_pro[20];
  int achou;
  int pos = 0;
  system("cls");
  fClientes = fopen("clientes.dat", "r+");
  fseek(fClientes, sizeof(struct dadosCli), 0);
  printf("\n Digite o Nome p/ Procura : ");
  cin >> nom_pro;
  while (fread(&Cliente, sizeof(Cliente), 1, fClientes) == 1)
  {
    achou = strcmp(Cliente.nomeCli, nom_pro);
    if (achou == 0)
    {
      printf("\n O Nome é.................:%s", Cliente.nomeCli);
      printf("\n A Idade é................:%d", Cliente.idadeCli);
      printf("\n O Salßrio Bruto é........:%0.2f", Cliente.sbaseCli);
      printf("\n O Valor da Compra é......:%0.2f", Cliente.vcomprasCli);
      printf("_____________________________________________\n");
      printf("Digite <enter> para continuar e alterar____________\n");
      getch();

      printf("\n Digite a alterþÒo do nome do cliente: %s", Cliente.nomeCli);
      cin >> Cliente.nomeCli;
      printf("\n Digite a idade:");
      cin >> Cliente.idadeCli;
      printf("\n Digite o salario base:");
      cin >> Cliente.sbaseCli;
      printf("\n Digite o valor da compra:");
      cin >> Cliente.vcomprasCli;
      fseek(fClientes, pos * sizeof(struct dadosCli), SEEK_SET);
      fwrite(&Cliente, sizeof(struct dadosCli), 1, fClientes);
      fseek(fClientes, sizeof(struct dadosCli), SEEK_END);
    }
    printf("Digite <enter> para continuar___________________\n");
    getch();
  }
  fclose(fClientes);
}

void excluirCliente()
{
  char nom_pro[20];
  int achou = 1;
  int tamanhoAuxiliar = 0;
  int tamanhoCliente = 0;

  system("cls");
  fClientes = fopen("Clientes.dat", "r+");
  fseek(fClientes, sizeof(struct dadosCli), 0);
  cria_arqAuxCli();
  fAuxCli = fopen("auxcli.dat", "r+");
  fseek(fAuxCli, sizeof(struct dadosCli), 0);

  printf("\n Digite o Nome do cliente p/ Procura : ");
  cin >> nom_pro;
  while (fread(&Cliente, sizeof(Cliente), 1, fClientes) == 1)
  {
    achou = strcmp(Cliente.nomeCli, nom_pro);
    if (achou == 0)
    {
      printf("\n O Nome é.................:%s", Cliente.nomeCli);
      printf("\n A Idade é................:%d", Cliente.idadeCli);
      printf("\n O Salßrio Bruto é........:%0.2f", Cliente.sbaseCli);
      printf("\n O Valor da Compra é......:%0.2f", Cliente.vcomprasCli);
      printf("_____________________________________________\n");
      getch();
    }
    else
    {
      tamanhoAuxiliar = tamanhoAuxiliar + fwrite(&Cliente, sizeof(struct dadosCli), 1, fAuxCli);
    }
  }
  fclose(fAuxCli);
  fclose(fClientes);
  remove("clientes.dat");
  criarArquivoCliente();
  fClientes = fopen("clientes.dat", "r+");
  fseek(fClientes, sizeof(struct dadosCli), 0);

  fAuxCli = fopen("auxcli.dat", "r+");
  fseek(fAuxCli, sizeof(struct dadosCli), 0);
  while (fread(&Cliente, sizeof(Cliente), 1, fAuxCli) == 1)
  {
    tamanhoCliente = tamanhoCliente + fwrite(&Cliente, sizeof(struct dadosCli), 1, fClientes);
  }

  fclose(fAuxCli);
  remove("auxcli.dat");
  fclose(fClientes);
  printf("\n Cliente ExcluÝdo - Digite <enter> para continuar___________________\n");
  getch();
}

void excluirArquivoCliente()
{
  char op;
  printf("\n Deleta Arquivo <S> ou <N>? ");
  cin >> op;
  op = toupper(op);
  if (op == 'S')
  {
    remove("clientes.dat");
    printf("arquivo deletado");
  }

  else
  {
    printf("\n Arquivo nÒo foi deletado por sua opþÒo");
    getch();
  }
  criarArquivoCliente();
}
void MenuCli()
{
  system("cls");
  criarArquivoCliente();
  printf("Menu de opcoes");
  printf("\n");
  printf("1 - Cadastrar Clientes\n");
  printf("2 - Consultar Listar todos Clintes  \n");
  printf("3 - Consultar Por Nome de Cliente \n");
  printf("4 - Alterar Registro de Cliente \n");
  printf("5 - Excluir Registro de Clientes \n");
  printf("6 - Exclui Arquivo total de Clientes\n");
  printf("7 - Voltar ao Menu principal \n");
  printf("Digite uma opcao \n");
  cin >> opc;
  switch (opc)
  {
  case 1:
    cadastrarCliente();
    break;
  case 2:
    consultarCliente();
    break;
  case 3:
    consultarNomeCliente();
    break;
  case 4:
    alterarCliente();
    break;
  case 5:
    excluirCliente();
    break;
  case 6:
    excluirArquivoCliente();
    break;
  case 7:
    menuPrincipal();
  }
}
// fim do cliente
//  inicio do fornecedor

void cria_arqForn()
{
  if ((fFornecedores = fopen("fornecedores.dat", "a")) == NULL)
  {
    printf("\n Erro de criacao do arquivo Fornecedores");
    return;
  }
  printf("\n Arquivo fornecedores Criado");
  fclose(fFornecedores);
}

void cria_arqAuxForn()
{
  if ((fAuxForn = fopen("auxforn.dat", "a")) == NULL)
  {
    system("cls");
    printf("\n Erro de criacao de arquivo AuxForn");
    return;
  }
  printf("\n Arquivo AuxForn Criado");
  fclose(fAuxForn);
}

void cadastrarFornecedor()
{
  char op;
  system("cls");
  int tamanho = 0;
  fFornecedores = fopen("fornecedores.dat", "r+");
  rewind(fFornecedores);
  do
  {
    fread(&Fornecedor, sizeof(Fornecedor), 1, fFornecedores);
    tamanho++;
  } while (!feof(fFornecedores));

  fseek(fFornecedores, sizeof(Fornecedor), tamanho);
  do
  {
    system("cls");
    cout << "\n Digite o nome do fornecedor:";
    cin >> Fornecedor.nomeForn;
    printf("\n Digite o endereco do fornecedor:");
    cin >> Fornecedor.endeForn;
    printf("\n Digite o email do fornecedor:");
    cin >> Fornecedor.emailForn;
    printf("\n Digite o CNPJ do fornecedor:");
    cin >> Fornecedor.cnpj;

    tamanho = tamanho + fwrite(&Fornecedor, sizeof(struct dadosForn), 1, fFornecedores);

    printf("\n Continuar cadastrando <S> ou <N>:");
    cin >> op;
    op = toupper(op);
  } while (op == 'S');
  fclose(fFornecedores);
}

void consultarFornecedor()
{

  system("cls");
  fFornecedores = fopen("fornecedores.dat", "r");
  fseek(fFornecedores, sizeof(struct dadosForn), 0);

  while (fread(&Fornecedor, sizeof(Fornecedor), 1, fFornecedores) == 1)
  {
    system("cls");
    printf("Nome Fornecedor:         %s\n", Fornecedor.nomeForn);
    printf("endereco do Fornecedor:  %s\n", Fornecedor.endeForn);
    printf("Email do Fornecedor:     %s\n", Fornecedor.emailForn);
    printf("CNPJ do Fornecedor:      %s\n", Fornecedor.cnpj);
    printf("\n Digite enter para continuar\n");
    getch();
  }
  printf("\n fim do arquivo");
  fclose(fFornecedores);
  getch();
}
void consultarNomeFornecedor()
{
  char nom_pro[20];
  int achou = 1;
  int localizou = 1;
  char op;

  system("cls");
  fFornecedores = fopen("fornecedores.dat", "r+");
  fseek(fFornecedores, sizeof(struct dadosForn), 0);
  printf("\n Digite o Nome p/ Procura : ");
  cin >> nom_pro;
  while (fread(&Fornecedor, sizeof(Fornecedor), 1, fFornecedores) == 1)
  {
    achou = strcmp(Fornecedor.nomeForn, nom_pro);
    if (achou == 0)
    {
      printf("\n O Nome é:%s ", Fornecedor.nomeForn);
      printf("\n O email e:%s ", Fornecedor.emailForn);
      printf("\n O Endereco do fornecedor e:%s ", Fornecedor.endeForn);
      printf("\n O CNPJ do fornecedor e:%s ", Fornecedor.cnpj);
      printf("\n_____________________________________________\n");
      getch();
      localizou = 0;
    }
  }

  if (localizou == 1)
  {
    printf("\n Fornecedor nÒo Cadastrado\n");
    printf("\n Cadastrar Fornecedor? <S> ou <N>:");
    cin >> op;
    op = toupper(op);
    if (op == 'S')
    {
      cadastrarFornecedor();
    }
    else
    {
      fclose(fFornecedores);
    }
    getch();
  }
}
void alterarFornecedor()
{
  char nom_pro[20];
  int achou;
  int pos = 0;
  system("cls");
  fFornecedores = fopen("fornecedores.dat", "r+");
  fseek(fFornecedores, sizeof(struct dadosForn), 0);
  printf("\n Digite o Nome p/ Procura : ");
  cin >> nom_pro;
  while (fread(&Fornecedor, sizeof(Fornecedor), 1, fFornecedores) == 1)
  {
    achou = strcmp(Fornecedor.nomeForn, nom_pro);
    pos++;
    if (achou == 0)
    {
      printf("\n O Nome é:%s ", Fornecedor.nomeForn);
      printf("\n O email e:%s ", Fornecedor.emailForn);
      printf("\n O Endereco do fornecedor e:%s ", Fornecedor.endeForn);
      printf("\n O CNPJ do fornecedor e:%s ", Fornecedor.cnpj);
      printf("\n_____________________________________________\n");
      printf("Digite <enter> para continuar e alterar____________\n");
      getch();
      printf("\n Digite a alterþÒo do nome do cliente: %s", Fornecedor.nomeForn);
      cin >> Fornecedor.nomeForn;
      printf("\n Digite o Email:");
      cin >> Fornecedor.emailForn;
      printf("\n Digite o endereco:");
      cin >> Fornecedor.endeForn;
      printf("\n Digite o CNPJ do fornecedor");
      cin >> Fornecedor.cnpj;
      fseek(fFornecedores, pos * sizeof(struct dadosForn), SEEK_SET);
      fwrite(&Fornecedor, sizeof(struct dadosForn), 1, fFornecedores);
      fseek(fFornecedores, sizeof(struct dadosForn), SEEK_END);
    }
    printf("Digite <enter> para continuar___________________\n");
    getch();
  }
  fclose(fFornecedores);
}

void excluirFornecedor()
{
  char nom_pro[20];
  int achou = 1;
  int tamanhoAuxiliar = 0;
  int tamanhoForn = 0;

  system("cls");
  fFornecedores = fopen("fornecedores.dat", "r+");
  fseek(fFornecedores, sizeof(struct dadosForn), 0);
  cria_arqAuxForn();
  fAuxForn = fopen("auxforn.dat", "r+");
  fseek(fAuxForn, sizeof(struct dadosForn), 0);

  printf("\n Digite o Nome do Fornecedor p/ Procura : ");
  cin >> nom_pro;
  while (fread(&Fornecedor, sizeof(Fornecedor), 1, fFornecedores) == 1)
  {
    achou = strcmp(Fornecedor.nomeForn, nom_pro);

    if (achou == 0)
    {
      printf("\n O Nome é:%s ", Fornecedor.nomeForn);
      printf("\n O email e:%s ", Fornecedor.emailForn);
      printf("\n O Endereco do fornecedor e:%s ", Fornecedor.endeForn);
      printf("\n O CNPJ do fornecedor e:%s ", Fornecedor.cnpj);
      printf("\n_____________________________________________\n");
      getch();
    }
    else
    {

      tamanhoAuxiliar = tamanhoAuxiliar + fwrite(&Fornecedor, sizeof(struct dadosForn), 1, fAuxForn);
    }
  }

  fclose(fAuxForn);
  fclose(fFornecedores);
  remove("fornecedores.dat");
  cria_arqForn();
  fFornecedores = fopen("fornecedores.dat", "r+");
  fseek(fFornecedores, sizeof(struct dadosForn), 0);

  fAuxForn = fopen("auxforn.dat", "r+");
  fseek(fAuxForn, sizeof(struct dadosForn), 0);
  while (fread(&Fornecedor, sizeof(Fornecedor), 1, fAuxForn) == 1)
  {
    tamanhoForn = tamanhoForn + fwrite(&Fornecedor, sizeof(struct dadosForn), 1, fFornecedores);
  }

  fclose(fAuxForn);
  remove("auxforn.dat");
  fclose(fFornecedores);
  printf("\n Fornecedor ExcluÝdo - Digite <enter> para continuar___________________\n");
  getch();
}

void excluirArquivoFornecedor()
{
  char op;
  printf("\n Deleta Arquivo <S> ou <N>? ");
  cin >> op;
  op = toupper(op);
  if (op == 'S')
  {
    remove("fornecedores.dat");
    printf("arquivo deletado");
  }

  else
  {
    printf("\n Arquivo nÒo foi deletado por sua opþÒo");
    getch();
  }
  cria_arqForn();
}
void MenuForn()
{
  system("cls");
  cria_arqForn();
  printf("Menu de opcoes");
  printf("\n");
  printf("1 - Cadastrar Fornecedores\n");
  printf("2 - Consultar Listar todos Fornecedores  \n");
  printf("3 - Consultar Por Nome de Fornecedores \n");
  printf("4 - Alterar Registro de Fornecedores \n");
  printf("5 - Excluir Registro de Fornecedores \n");
  printf("6 - Exclui Arquivo total de Fornecedores\n");
  printf("7 - Voltar ao Menu principal \n");
  printf("Digite uma opcao \n");
  cin >> opc;
  switch (opc)
  {
  case 1:
    cadastrarFornecedor();
    break;
  case 2:
    consultarFornecedor();
    break;
  case 3:
    consultarNomeFornecedor();
    break;
  case 4:
    alterarFornecedor();
    break;
  case 5:
    excluirFornecedor();
    break;
  case 6:
    excluirArquivoFornecedor();
    break;
  case 7:
    menuPrincipal();
  }
}
// Fim fornecedor
// inicio do produto
void cria_arqProd()
{
  if ((fProdutos = fopen("produto.dat", "a")) == NULL)
  {
    printf("\n Erro de criaþÒo do arquivo Produto");
    return;
  }
  printf("\n Arquivo Produto Criado");
  fclose(fProdutos);
}

void cria_arqAuxProd()
{
  if ((fAuxProd = fopen("auxProd.dat", "a")) == NULL)
  {
    system("cls");
    printf("\n Erro de criaþÒo de arquivo AuxProd");
    return;
  }
  printf("\n Arquivo AuxProd Criado");
  fclose(fAuxProd);
}

void cadastrarProduto()
{
  char op;
  system("cls");
  int tamanho = 0;
  fProdutos = fopen("produto.dat", "r+");
  rewind(fProdutos);
  do
  {
    fread(&Produto, sizeof(Produto), 1, fProdutos);
    tamanho++;
  } while (!feof(fProdutos));

  fseek(fProdutos, sizeof(Produto), tamanho);
  do
  {
    system("cls");

    cout << "\n Digite o nome do Produto:";
    cin >> Produto.nomeprod;
    printf("\n Digite o codigo do Produto:");
    cin >> Produto.codprod;
    printf("\n Digite o valor unitario do produto base:");
    cin >> Produto.valorUniprod;
    tamanho = tamanho + fwrite(&Produto, sizeof(struct dadosProd), 1, fProdutos);

    printf("\n Continuar cadastrando <S> ou <N>:");
    cin >> op;
    op = toupper(op);
  } while (op == 'S');
  fclose(fProdutos);
}

void consultarProdutos()
{
  system("cls");
  fProdutos = fopen("produto.dat", "r");
  fseek(fProdutos, sizeof(struct dadosProd), 0);

  while (fread(&Produto, sizeof(Produto), 1, fProdutos) == 1)
  {
    system("cls");
    printf("Nome Produto :        %s\n", Produto.nomeprod);
    printf("Codigo do Produto :       %d\n", Produto.codprod);
    printf("Valor unitario do produto:     %.2f\n", Produto.valorUniprod);
    printf("\n Digite enter para continuar\n");
    getch();
  }
  printf("\n fim do arquivo");
  fclose(fProdutos);
  getch();
}

void consultarNomeProduto()
{

  char nomeprod[30];
  int achou = 1;
  int localizou = 1;
  char op;

  system("cls");
  fProdutos = fopen("produto.dat", "r+");
  fseek(fProdutos, sizeof(struct dadosProd), 0);
  printf("\n Digite o Nome p/ Procura : ");
  cin >> nomeprod;
  while (fread(&Produto, sizeof(Produto), 1, fProdutos) == 1)
  {
    achou = strcmp(Produto.nomeprod, nomeprod);
    if (achou == 0)
    {
      printf("\n O Nome é.................:%s", Produto.nomeprod);
      printf("\n O Codigo é................:%d", Produto.codprod);
      printf("\n O Valor Unitario é........:%0.2f", Produto.valorUniprod);
      printf("\n_____________________________________________\n");
      getch();
      localizou = 0;
    }
  }

  if (localizou == 1)
  {
    printf("\n Produto nÒo Cadastrado\n");
    printf("\n Cadastrar Produto <S> ou <N>:");
    op = toupper(op);
    if (op == 'S')
    {
      cadastrarProduto();
    }
    else
    {
      fclose(fProdutos);
    }
    getch();
  }
}

void aterarProduto()
{
  char nomeprod[30];
  int achou;
  int pos = 0;
  system("cls");
  fProdutos = fopen("produto.dat", "r+");
  fseek(fProdutos, sizeof(struct dadosProd), 0);
  printf("\n Digite o Nome p/ Procura : ");
  cin >> nomeprod;
  while (fread(&Produto, sizeof(Produto), 1, fProdutos) == 1)
  {
    achou = strcmp(Produto.nomeprod, nomeprod);
    if (achou == 0)
    {
      printf("\n O Nome é.................:%s", Produto.nomeprod);
      printf("\n O Codigo é................:%d", Produto.codprod);
      printf("\n O Valor Unitario é........:%0.2f", Produto.valorUniprod);
      printf("_____________________________________________\n");
      printf("Digite <enter> para continuar e alterar____________\n");
      getch();
      printf("\n Digite a alterþÒo do nome do produto: %s", Produto.nomeprod);
      cin >> Produto.nomeprod;
      printf("\n Digite o codigo do produto:");
      cin >> Produto.codprod;
      printf("\n Digite o valor unitario do produto:");
      cin >> Produto.valorUniprod;
      fseek(fProdutos, pos * sizeof(struct dadosProd), SEEK_SET);
      fwrite(&Produto, sizeof(struct dadosProd), 1, fProdutos);
      fseek(fProdutos, sizeof(struct dadosProd), SEEK_END);
    }
    printf("Digite <enter> para continuar___________________\n");
    getch();
  }
  fclose(fProdutos);
}

void excluirProduto()
{
  char nomeprod[30];
  int achou = 1;
  int tamanhoAuxiliar = 0;
  int tamanhoProduto = 0;

  system("cls");
  fProdutos = fopen("produto.dat", "r+");
  fseek(fProdutos, sizeof(struct dadosProd), 0);
  cria_arqAuxProd();
  fAuxProd = fopen("auxProd.dat", "r+");
  fseek(fAuxProd, sizeof(struct dadosProd), 0);
  printf("\n Digite o Nome do Produto p/ Procura : ");
  cin >> nomeprod;
  while (fread(&Produto, sizeof(Produto), 1, fProdutos) == 1)
  {
    achou = strcmp(Produto.nomeprod, nomeprod);
    if (achou == 0)
    {
      printf("\n O Nome é.................:%s", Produto.nomeprod);
      printf("\n A Codigo do Produto................:%d", Produto.codprod);
      printf("\n O Salßrio Bruto é........:%0.2f", Produto.valorUniprod);
      printf("_____________________________________________\n");
      getch();
    }
    else
    {
      tamanhoAuxiliar = tamanhoAuxiliar + fwrite(&Produto, sizeof(struct dadosProd), 1, fAuxProd);
    }
  }
  fclose(fAuxProd);
  fclose(fProdutos);
  remove("produto.dat");
  cria_arqProd();
  fProdutos = fopen("produto.dat", "r+");
  fseek(fProdutos, sizeof(struct dadosProd), 0);

  fAuxProd = fopen("auxProd.dat", "r+");
  fseek(fAuxProd, sizeof(struct dadosProd), 0);
  while (fread(&Produto, sizeof(Produto), 1, fAuxProd) == 1)
  {
    tamanhoProduto = tamanhoProduto + fwrite(&Produto, sizeof(struct dadosProd), 1, fProdutos);
  }
  fclose(fAuxProd);
  remove("auxProd.dat");
  fclose(fProdutos);
  printf("\n Produto ExcluÝdo - Digite <enter> para continuar___________________\n");
  getch();
}

void excluirArquivoProduto()
{
  char op;
  printf("\n Deleta Arquivo <S> ou <N>? ");
  cin >> op;
  op = toupper(op);
  if (op == 'S')
  {
    remove("produto.dat");
    printf("arquivo deletado");
  }

  else
  {
    printf("\n Arquivo nÒo foi deletado por sua opþÒo");
    getch();
  }
  cria_arqProd();
}
void MenuProd()
{
  system("cls");
  cria_arqProd();
  printf("Menu de opcoes");
  printf("\n");
  printf("1 - Cadastrar Produto\n");
  printf("2 - Consultar Listar todos os Produtos  \n");
  printf("3 - Consultar Por Nome do Produto \n");
  printf("4 - Alterar Registro do Produto \n");
  printf("5 - Excluir Registro do Produto \n");
  printf("6 - Exclui Arquivo total do Produto\n");
  printf("7 - Voltar ao Menu principal \n");
  printf("Digite uma opcao \n");
  cin >> opc;
  switch (opc)
  {
  case 1:
    cadastrarProduto();
    break;
  case 2:
    consultarProdutos();
    break;
  case 3:
    consultarNomeProduto();
    break;
  case 4:
    aterarProduto();
    break;
  case 5:
    excluirProduto();
    break;
  case 6:
    excluirArquivoProduto();
    break;
  case 7:
    menuPrincipal();
  }
}
// Fim produto

void criarArquivoFuncionario()
{
  if ((fFuncionarios = fopen("funcionario.dat", "a")) == NULL)
  {
    printf("\n Erro de criaþÒo do arquivo Funcionario");
    return;
  }
  printf("\n Arquivo Produto Criado");
  fclose(fFuncionarios);
}

void cria_arqAuxFunc()
{
  if ((fAuxFunc = fopen("auxFunc.dat", "a")) == NULL)
  {
    system("cls");
    printf("\n Erro de criaþÒo de arquivo AuxFunc");
    return;
  }
  printf("\n Arquivo AuxFunc Criado");
  fclose(fAuxFunc);
}

void cadastrarFuncionario()
{
  char op;
  system("cls");
  int tamanho = 0;
  fFuncionarios = fopen("funcionario.dat", "r+");
  rewind(fFuncionarios);
  do
  {
    fread(&Funcionario, sizeof(Funcionario), 1, fFuncionarios);
    tamanho++;
  } while (!feof(fFuncionarios));

  fseek(fFuncionarios, sizeof(Funcionario), tamanho);
  do
  {
    system("cls");

    cout << "\n Digite o nome do Funcionario:";
    cin >> Funcionario.nomeFunc;
    printf("\n Digite o endereco do Funcionario:");
    cin >> Funcionario.endeFunc;
    printf("\n Digite o Email do Funcionario:");
    cin >> Funcionario.emailFunc;
    printf("\n Digite o CPF do Funcionario:");
    cin >> Funcionario.CPFF;
    printf("\n Digite o salario do Funcionario:");
    cin >> Funcionario.salario;
    tamanho = tamanho + fwrite(&Funcionario, sizeof(struct dadosFunc), 1, fFuncionarios);

    printf("\n Continuar cadastrando <S> ou <N>:");
    cin >> op;
    op = toupper(op);
  } while (op == 'S');
  fclose(fFuncionarios);
}

void consultarFuncionario()
{
  system("cls");
  fFuncionarios = fopen("funcionario.dat", "r");
  fseek(fFuncionarios, sizeof(struct dadosFunc), 0);

  while (fread(&Funcionario, sizeof(Funcionario), 1, fFuncionarios) == 1)
  {
    system("cls");
    printf("Nome Funcionario :        %s\n", Funcionario.nomeFunc);
    printf("Endereco Funcionario :       %s\n", Funcionario.endeFunc);
    printf("Email Funcionario:     %s\n", Funcionario.emailFunc);
    printf("CPF Funcionario:     %s\n", Funcionario.CPFF);
    printf("Salario Funcionario:     %.2f\n", Funcionario.salario);
    printf("\n Digite enter para continuar\n");
    getch();
  }
  printf("\n fim do arquivo");
  fclose(fFuncionarios);
  getch();
}

void consultarNomeFuncionario()
{

  char nomeFunc[20];
  int achou = 1;
  int localizou = 1;
  char op;

  system("cls");
  fFuncionarios = fopen("funcionario.dat", "r+");
  fseek(fFuncionarios, sizeof(struct dadosFunc), 0);
  printf("\n Digite o Nome p/ Procura : ");
  cin >> nomeFunc;
  while (fread(&Funcionario, sizeof(Funcionario), 1, fFuncionarios) == 1)
  {
    achou = strcmp(Funcionario.nomeFunc, nomeFunc);
    if (achou == 0)
    {
      printf("\n O Nome é.................:%s", Funcionario.nomeFunc);
      printf("\n O Endereco é................:%s", Funcionario.endeFunc);
      printf("\n O Email é........:%s", Funcionario.emailFunc);
      printf("\n O CPF é........:%s", Funcionario.CPFF);
      printf("\n O Salario é........:%.2f", Funcionario.salario);
      printf("\n_____________________________________________\n");
      getch();
      localizou = 0;
    }
  }

  if (localizou == 1)
  {
    printf("\n Funcionario nÒo Cadastrado\n");
    printf("\n Cadastrar Funcionario <S> ou <N>:");
    op = toupper(op);
    if (op == 'S')
    {
      cadastrarFuncionario();
    }
    else
    {
      fclose(fFuncionarios);
    }
    getch();
  }
}

void alterarFunciconario()
{
  char nomeFunc[20];
  int achou;
  int pos = 0;
  system("cls");
  fFuncionarios = fopen("funcionario.dat", "r+");
  fseek(fFuncionarios, sizeof(struct dadosFunc), 0);
  printf("\n Digite o Nome p/ Procura : ");
  cin >> nomeFunc;
  while (fread(&Funcionario, sizeof(Funcionario), 1, fFuncionarios) == 1)
  {
    achou = strcmp(Funcionario.nomeFunc, nomeFunc);
    if (achou == 0)
    {
      printf("\n O Nome é.................:%s", Funcionario.nomeFunc);
      printf("\n O Endereco é................:%s", Funcionario.endeFunc);
      printf("\n O Email é........:%s", Funcionario.emailFunc);
      printf("\n O CPF é........:%s", Funcionario.CPFF);
      printf("\n O Salario é........:%.2f", Funcionario.salario);
      printf("_____________________________________________\n");
      printf("Digite <enter> para continuar e alterar____________\n");
      getch();
      printf("\n Digite a alterþÒo do nome do Funcionario: %s", Funcionario.nomeFunc);
      cin >> Funcionario.nomeFunc;
      printf("\n Digite o endereco do funcionario:");
      cin >> Funcionario.endeFunc;
      printf("\n Digite o email do funcionario:");
      cin >> Funcionario.emailFunc;
      printf("\n Digite o CPF do funcionario:");
      cin >> Funcionario.CPFF;
      printf("\n Digite o salario do funcionario:");
      cin >> Funcionario.salario;
      fseek(fFuncionarios, pos * sizeof(struct dadosFunc), SEEK_SET);
      fwrite(&Funcionario, sizeof(struct dadosFunc), 1, fFuncionarios);
      fseek(fFuncionarios, sizeof(struct dadosFunc), SEEK_END);
    }
    printf("Digite <enter> para continuar___________________\n");
    getch();
  }
  fclose(fFuncionarios);
}

void excluirFuncionario()
{
  char nomeFunc[20];
  int achou = 1;
  int tamanhoAuxiliar = 0;
  int tamanhoFuncionario = 0;

  system("cls");
  fFuncionarios = fopen("funcionarios.dat", "r+");
  fseek(fFuncionarios, sizeof(struct dadosFunc), 0);
  cria_arqAuxFunc();
  fAuxFunc = fopen("auxFunc.dat", "r+");
  fseek(fAuxFunc, sizeof(struct dadosFunc), 0);
  printf("\n Digite o Nome do Funcionario p/ Procura : ");
  cin >> nomeFunc;
  while (fread(&Funcionario, sizeof(Funcionario), 1, fFuncionarios) == 1)
  {
    achou = strcmp(Funcionario.nomeFunc, nomeFunc);
    if (achou == 0)
    {
      printf("\n O Nome é.................:%s", Funcionario.nomeFunc);
      printf("\n O Endereco do Funcionario................:%s", Funcionario.endeFunc);
      printf("\n O Email do Funcionario........:%s", Funcionario.emailFunc);
      printf("\n O CPF do Funcionario........:%s", Funcionario.CPFF);
      printf("\n O Salario do Funcionario........:%.2f", Funcionario.salario);
      printf("_____________________________________________\n");
      getch();
    }
    else
    {
      tamanhoAuxiliar = tamanhoAuxiliar + fwrite(&Funcionario, sizeof(struct dadosFunc), 1, fAuxFunc);
    }
  }
  fclose(fAuxFunc);
  fclose(fFuncionarios);
  remove("Funcionarios.dat");
  criarArquivoFuncionario();
  fFuncionarios = fopen("funcionarios.dat", "r+");
  fseek(fFuncionarios, sizeof(struct dadosFunc), 0);

  fAuxFunc = fopen("auxFunc.dat", "r+");
  fseek(fAuxFunc, sizeof(struct dadosFunc), 0);
  while (fread(&Funcionario, sizeof(Funcionario), 1, fAuxFunc) == 1)
  {
    tamanhoFuncionario = tamanhoFuncionario + fwrite(&Funcionario, sizeof(struct dadosFunc), 1, fFuncionarios);
  }
  fclose(fAuxFunc);
  remove("auxFunc.dat");
  fclose(fFuncionarios);
  printf("\n Produto ExcluÝdo - Digite <enter> para continuar___________________\n");
  getch();
}

void excluirArquivoFuncionario()
{
  char op;
  printf("\n Deleta Arquivo <S> ou <N>? ");
  cin >> op;
  op = toupper(op);
  if (op == 'S')
  {
    remove("funcionarios.dat");
    printf("arquivo deletado");
  }

  else
  {
    printf("\n Arquivo nÒo foi deletado por sua opþÒo");
    getch();
  }
  criarArquivoFuncionario();
}
void MenuFunc()
{
  system("cls");
  criarArquivoFuncionario();
  printf("Menu de opcoes");
  printf("\n");
  printf("1 - Cadastrar Funcionario\n");
  printf("2 - Consultar Listar todos os Funcionarios  \n");
  printf("3 - Consultar Por Nome do Funcionario \n");
  printf("4 - Alterar Registro do Funcionario \n");
  printf("5 - Excluir Registro do Funcionario \n");
  printf("6 - Exclui Arquivo total do Funcionario\n");
  printf("7 - Voltar ao Menu principal \n");
  printf("Digite uma opcao \n");
  cin >> opc;
  switch (opc)
  {
  case 1:
    cadastrarFuncionario();
    break;
  case 2:
    consultarFuncionario();
    break;
  case 3:
    consultarNomeFuncionario();
    break;
  case 4:
    alterarFunciconario();
    break;
  case 5:
    excluirFuncionario();
    break;
  case 6:
    excluirArquivoFuncionario();
    break;
  case 7:
    menuPrincipal();
  }
}
// fim funcionarios

// Menu principal
void menuPrincipal()
{
  void MenuCli();
  void MenuFunc();
  void MenuForn();
  void MenuProd();
  system("cls");
  printf("Menu de opcoes");
  printf("\n");
  printf("1 - Clientes\n");
  printf("2 - Funcionßrios\n");
  printf("3 - Fornecedores\n");
  printf("4 - Produtos\n");
  printf("5 - Sair do Sistema\n");
  printf("Digite uma opcao \n");
  cin >> opc;
  switch (opc)
  {
  case 1:
    MenuCli();
    break;
  case 2:
    MenuFunc();
    break;
  case 3:
    MenuForn();
    break;
  case 4:
    MenuProd();
    break;
  case 5:
    exit(0);
    break;
  }
}
main()
{
  setlocale(LC_ALL, "portuguese");
  system("cls");
  opc = 1;
  do
  {
    menuPrincipal();
  } while (opc != 5);
}
