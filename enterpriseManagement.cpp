#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <ctype.h>
#include <io.h>
#include <string.h>
#include <dos.h>
#include <locale.h>
#include <direct.h>

void menuPrincipal();
void menuCliente();
void menuFornenecedor();
void menuFuncionario();
void menuProdutos();

using namespace std;

struct dadosCli
{
  char nomeCli[20];
  int idadeCli;
  float salarioCli;
  float vcomprasCli;
} Cliente;

struct dadosForn
{
  char nomeForn[20];
  char endeForn[30];
  char emailForn[30];
  char cnpj[20];
} Fornecedor;

struct dadosFunc
{
  char nomeFunc[20];
  char endeFunc[30];
  char emailFunc[30];
  char cpfFunc[20];
  float salarioFunc;
} Funcionario;

struct dadosProd
{
  char nomeProd[30];
  int codProd;
  float valorProd;
} Produto;

FILE *fClientes;
FILE *fAuxCli;

FILE *fFornecedores;
FILE *fAuxForn;

FILE *fFuncionarios;
FILE *fAuxFunc;

FILE *fProdutos;
FILE *fAuxProd;

int opc;

void criaArquivoCliente()
{
  if ((fClientes = fopen("Clientes.dat", "a")) == NULL)
  {
    printf("\nErro de cria��o do arquivo Clientes");
    return;
  }
  fclose(fClientes);
}

void criaArquivoAuxiliarCliente()
{
  if ((fAuxCli = fopen("AuxCli.dat", "a")) == NULL)
  {
    printf("\nErro de cria��o do arquivo AuxCli");
    return;
  }
  fclose(fAuxCli);
}

void criaArquivoFornecedor()
{
  if ((fFornecedores = fopen("Fornecedores.dat", "a")) == NULL)
  {
    printf("\nErro de cria��o do arquivo Fornecedores");
    return;
  }
  fclose(fFornecedores);
}

void criaArquivoAuxiliarForn()
{
  if ((fAuxForn = fopen("AuxForn.dat", "a")) == NULL)
  {
    printf("\nErro de cria��o do arquivo AuxForn");
    return;
  }
  fclose(fAuxForn);
}

void criaArquivoFuncionario()
{
  if ((fFuncionarios = fopen("Funcionarios.dat", "a")) == NULL)
  {
    printf("\nErro de cria��o do arquivo Funcion�rios");
    return;
  }
  fclose(fFuncionarios);
}

void criaArquivoAuxiliarFuncionarios()
{
  if ((fAuxFunc = fopen("AuxFunc.dat", "a")) == NULL)
  {
    printf("\nErro de cria��o do arquivo AuxFunc");
    return;
  }
  fclose(fAuxFunc);
}

void criaArquivoProduto()
{
  if ((fProdutos = fopen("Produtos.dat", "a")) == NULL)
  {
    printf("\nErro dee cria��o do arquivo Produtos");
    return;
  }
  fclose(fProdutos);
}

void criaArquivoAuxiliarProdutos()
{
  if ((fAuxProd = fopen("AuxProd.dat", "a")) == NULL)
  {
    printf("\nErro de cria��o do arquivo AuxProd");
    return;
  }
  fclose(fAuxProd);
}

// Inicio do cliente
void cadastrarCliente()
{
  char op;
  system("cls");
  int tamanho = 0;
  fClientes = fopen("Clientes.dat", "r+");
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
    fflush(stdin);
    cout << "\nDigite o nome do cliente: ";
    gets(Cliente.nomeCli);
    printf("\nDigite a idade do cliente: ");
    cin >> Cliente.idadeCli;
    printf("\nDigite o sal�rio do cliente: ");
    cin >> Cliente.salarioCli;
    printf("\nDigite o valor da compra: ");
    cin >> Cliente.vcomprasCli;
    tamanho = tamanho + fwrite(&Cliente, sizeof(struct dadosCli), 1, fClientes);
    printf("\n\nContinuar cadastrando <S> ou <N>: ");
    cin >> op;
    op = toupper(op);
  } while (op == 'S');
  fclose(fClientes);
  menuCliente();
}

void consultarCliente()
{
  system("cls");
  fClientes = fopen("Clientes.dat", "r");
  fseek(fClientes, sizeof(struct dadosCli), 0);
  while (fread(&Cliente, sizeof(Cliente), 1, fClientes) == 1)
  {
    system("cls");
    printf("\nNome Cliente        : %s\n", Cliente.nomeCli);
    printf("\nIdade Cliente       : %d\n", Cliente.idadeCli);
    printf("\nSalario Cliente     : %.2f\n", Cliente.salarioCli);
    printf("\nValor Compra Cliente: %.2f\n", Cliente.vcomprasCli);
    getch();
  }
  printf("\n\nFim do arquivo...");
  getch();
  fclose(fClientes);
  menuCliente();
}

void consultarNomeCliente()
{
  char nom_pro[20];
  int achou = 1;
  int localizou = 1;
  char op;

  system("cls");
  fClientes = fopen("Clientes.dat", "r+");
  fseek(fClientes, sizeof(struct dadosCli), 0);
  fflush(stdin);
  printf("\nDigite o nome para a procura: ");
  gets(nom_pro);
  while (fread(&Cliente, sizeof(Cliente), 1, fClientes) == 1)
  {
    achou = strcmp(Cliente.nomeCli, nom_pro);

    if (achou == 0)
    {
      printf("\n O Nome �.............: %s", Cliente.nomeCli);
      printf("\n A Idade �............: %d", Cliente.idadeCli);
      printf("\n O Sal�rio Bruto �....: %0.2f", Cliente.salarioCli);
      printf("\n O Valor da Compra ,..: %0.2f", Cliente.vcomprasCli);
      printf("\n_____________________________________________\n");
      printf("\nDigite <enter> para continuar...");
      getch();
      localizou = 0;
    }
  }

  if (localizou == 1)
  {
    printf("\nCliente n�o cadastrado\n");
    printf("\nCadastrar cliente <S> ou <N>: ");
    cin >> op;
    op = toupper(op);

    if (op == 'S')
    {
      cadastrarCliente();
      getch();
    }
  }
  menuCliente();
}

void alterarCliente()
{
  char nom_pro[20];
  int achou;
  int pos = 0;

  system("cls");
  fClientes = fopen("Clientes.dat", "r+");
  fseek(fClientes, sizeof(struct dadosCli), 0);
  fflush(stdin);
  printf("\nDigite o nome para procura: ");
  gets(nom_pro);
  while (fread(&Cliente, sizeof(Cliente), 1, fClientes) == 1)
  {
    achou = strcmp(Cliente.nomeCli, nom_pro);
    pos++;
    if (achou == 0)
    {
      printf("\n O Nome �.............: %s", Cliente.nomeCli);
      printf("\n A Idade �............: %d", Cliente.idadeCli);
      printf("\n O Sal�rio Bruto �....: %0.2f", Cliente.salarioCli);
      printf("\n O Valor da Compra �..: %0.2f", Cliente.vcomprasCli);
      printf("\n_____________________________________________\n");
      printf("\nDigite <enter> para continuar");
      getch();

      fflush(stdin);
      printf("\n\nDigite a altera��o do nome do cliente: ");
      gets(Cliente.nomeCli);
      printf("\nDigite a nova idade: ");
      cin >> Cliente.idadeCli;
      printf("\nDigite o novo sal�rio: ");
      cin >> Cliente.salarioCli;
      printf("\nDigite o novo valor da compra: ");
      cin >> Cliente.vcomprasCli;
      fseek(fClientes, pos * sizeof(struct dadosCli), SEEK_SET);
      fwrite(&Cliente, sizeof(struct dadosCli), 1, fClientes);
      fseek(fClientes, sizeof(struct dadosCli), SEEK_END);
    }

    printf("\nDigite <enter> para continuar...");
    getche();
  }

  fclose(fClientes);
  menuCliente();
}

void excluirCLiente()
{
  char nom_pro[20];
  int achou;
  int tamanhoaux = 0;
  int tamanhocli = 0;

  system("cls");
  fClientes = fopen("Clientes.dat", "r+");
  fseek(fClientes, sizeof(struct dadosCli), 0);
  criaArquivoAuxiliarCliente();
  fAuxCli = fopen("AuxCli.dat", "r+");
  fseek(fAuxCli, sizeof(struct dadosCli), 0);
  fflush(stdin);
  printf("\nDigite o nome do cliente para procura: ");
  cin >> nom_pro;

  while (fread(&Cliente, sizeof(Cliente), 1, fClientes) == 1)
  {
    achou = strcmp(Cliente.nomeCli, nom_pro);

    if (achou == 0)
    {
      printf("\n O Nome �.............: %s", Cliente.nomeCli);
      printf("\n A Idade �............: %d", Cliente.idadeCli);
      printf("\n O Sal�rio Bruto �....: %0.2f", Cliente.salarioCli);
      printf("\n O Valor da Compra �..: %0.2f", Cliente.vcomprasCli);
      printf("\n_____________________________________________\n");
      printf("\n Digite <enter> para continuar");
      getch();
    }
    else
    {
      tamanhoaux = tamanhoaux + fwrite(&Cliente, sizeof(struct dadosCli), 1, fAuxCli);
    }
  }

  fclose(fAuxCli);
  fclose(fClientes);
  remove("Clientes.dat");
  criaArquivoCliente();
  fClientes = fopen("Clientes.dat", "r+");
  fseek(fClientes, sizeof(struct dadosCli), 0);
  fAuxCli = fopen("AuxCli.dat", "r+");
  fseek(fAuxCli, sizeof(struct dadosCli), 0);
  while (fread(&Cliente, sizeof(Cliente), 1, fAuxCli) == 1)
  {
    tamanhocli = tamanhocli + fwrite(&Cliente, sizeof(struct dadosCli), 1, fClientes);
  }
  fclose(fAuxCli);
  remove("AuxCli.dat");
  fclose(fClientes);
  printf("\n\nCliente excl�ido - Digite <enter> para continuar...");
  getche();
  menuCliente();
}

void excluirAuxiliarCliente()
{
  char op;
  printf("\n\nDeletar Arquivo ? <S> ou <N>: ");
  cin >> op;
  op = toupper(op);
  if (op == 'S')
  {
    remove("Clientes.dat");
    printf("\nArquivo deletado. - Digite <enter> para continuar...");
    getche();
  }
  else
  {
    printf("\n\nArquivo n�o foi deletado por sua op��o.");
  }
  criaArquivoCliente();
  menuCliente();
}
// final dos clientes

// Inicio dos fornecedores
void cadastrarFornecedor()
{
  char op;
  system("cls");
  int tamanho = 0;
  fFornecedores = fopen("Fornecedores.dat", "r+");
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
    fflush(stdin);
    cout << "\nDigite o nome do fornecedor: ";
    gets(Fornecedor.nomeForn);
    fflush(stdin);
    printf("\nDigite o endere�o do fornecedor: ");
    gets(Fornecedor.endeForn);
    fflush(stdin);
    printf("\nDigite o email do fornecedor: ");
    gets(Fornecedor.emailForn);
    fflush(stdin);
    printf("\nDigite o CNPJ do fornecedor: ");
    gets(Fornecedor.cnpj);
    tamanho = tamanho + fwrite(&Fornecedor, sizeof(struct dadosForn), 1, fFornecedores);
    printf("\n\nContinuar cadastrando <S> ou <N>: ");
    cin >> op;
    op = toupper(op);
  } while (op == 'S');

  fclose(fFornecedores);
  menuFornenecedor();
}

void consultarFornecedor()
{
  system("cls");
  fFornecedores = fopen("Fornecedores.dat", "r");
  fseek(fFornecedores, sizeof(struct dadosForn), 0);
  while (fread(&Fornecedor, sizeof(Fornecedor), 1, fFornecedores) == 1)
  {
    system("cls");
    printf("\nNome Fornecedor     : %s\n", Fornecedor.nomeForn);
    printf("\nEndere�o Fornecedor : %s\n", Fornecedor.endeForn);
    printf("\nEmail Fornecedor    : %s\n", Fornecedor.emailForn);
    printf("\nCNPJ Fornecedor     : %s\n", Fornecedor.cnpj);
    printf("\nDigite <enter> para continuar");
    getch();
  }
  printf("\n\nFim do arquivo...");
  getch();
  fclose(fFornecedores);
  menuFornenecedor();
}

void consultarNomeFornecedor()
{
  char nom_pro[20];
  int achou = 1;
  int localizou = 1;
  char op;
  system("cls");
  fFornecedores = fopen("Fornecedores.dat", "r+");
  fseek(fFornecedores, sizeof(struct dadosForn), 0);
  fflush(stdin);
  printf("\nDigite o nome para a procura: ");
  gets(nom_pro);

  while (fread(&Fornecedor, sizeof(Fornecedor), 1, fFornecedores) == 1)
  {
    achou = strcmp(Fornecedor.nomeForn, nom_pro);
    if (achou == 0)
    {
      printf("\n O Nome �.............: %s", Fornecedor.nomeForn);
      printf("\n O Endere�o �.........: %s", Fornecedor.endeForn);
      printf("\n O Email �............: %s", Fornecedor.emailForn);
      printf("\n O CNPJ �.............: %s", Fornecedor.cnpj);
      printf("\n_____________________________________________\n");
      printf("\nDigite <enter> para continuar");
      getch();
      localizou = 0;
    }
  }

  if (localizou == 1)
  {
    printf("\nFornecedor n�o cadastrado\n");
    printf("\nCadastrar fornecedor <S> ou <N>: ");
    cin >> op;
    op = toupper(op);
    if (op == 'S')
    {
      cadastrarFornecedor();
      getch();
    }
  }
  menuFornenecedor();
}
void alteraForn()
{
  char nom_pro[20];
  int achou;
  int pos = 0;

  system("cls");
  fFornecedores = fopen("Fornecedores.dat", "r+");
  fseek(fFornecedores, sizeof(struct dadosForn), 0);

  fflush(stdin);
  printf("\nDigite o nome para procura: ");
  gets(nom_pro);

  while (fread(&Fornecedor, sizeof(Fornecedor), 1, fFornecedores) == 1)
  {
    achou = strcmp(Fornecedor.nomeForn, nom_pro);
    pos++;
    if (achou == 0)
    {
      printf("\n O Nome �.............: %s", Fornecedor.nomeForn);
      printf("\n O Endere�o �.........: %s", Fornecedor.endeForn);
      printf("\n O Email �............: %s", Fornecedor.emailForn);
      printf("\n O CNPJ �.............: %s", Fornecedor.cnpj);
      printf("\n_____________________________________________\n");
      printf("\nDigite <enter> para continuar");
      getch();
      fflush(stdin);
      printf("\n\nDigite a altera��o do nome do fornecedor: ");
      gets(Fornecedor.nomeForn);
      fflush(stdin);
      printf("\nDigite o novo endere�o: ");
      gets(Fornecedor.endeForn);
      printf("\nDigite o novo email: ");
      cin >> Fornecedor.emailForn;
      fflush(stdin);
      printf("\nDigite o novo CNPJ: ");
      gets(Fornecedor.cnpj);
      fseek(fFornecedores, pos * sizeof(struct dadosForn), SEEK_SET);
      fwrite(&Fornecedor, sizeof(struct dadosForn), 1, fFornecedores);
      fseek(fFornecedores, sizeof(struct dadosForn), SEEK_END);
    }
    printf("\nDigite <enter> para continuar...");
    getche();
  }

  fclose(fFornecedores);
  menuFornenecedor();
}

void excluirFornecedor()
{
  char nom_pro[20];
  int achou;
  int tamanhoaux = 0;
  int tamanhoforn = 0;

  system("cls");
  fFornecedores = fopen("Fornecedores.dat", "r+");
  fseek(fFornecedores, sizeof(struct dadosForn), 0);
  criaArquivoAuxiliarForn();
  fAuxForn = fopen("AuxForn.dat", "r+");
  fseek(fAuxForn, sizeof(struct dadosForn), 0);
  fflush(stdin);
  printf("\nDigite o nome do fornecedor para procura: ");
  gets(nom_pro);
  while (fread(&Fornecedor, sizeof(Fornecedor), 1, fFornecedores) == 1)
  {
    achou = strcmp(Fornecedor.nomeForn, nom_pro);
    if (achou == 0)
    {
      printf("\n O Nome �.............: %s", Fornecedor.nomeForn);
      printf("\n O Endere�o �.........: %s", Fornecedor.endeForn);
      printf("\n O Email �............: %s", Fornecedor.emailForn);
      printf("\n O CNPJ �.............: %s", Fornecedor.cnpj);
      printf("\n_____________________________________________\n");
      printf("\nDigite <enter> para continuar");
      getch();
    }
    else
    {
      tamanhoaux = tamanhoaux + fwrite(&Fornecedor, sizeof(struct dadosForn), 1, fAuxForn);
    }
  }

  fclose(fAuxForn);
  fclose(fFornecedores);
  remove("Fornecedores.dat");
  criaArquivoFornecedor();
  fFornecedores = fopen("Fornecedores.dat", "r+");
  fseek(fFornecedores, sizeof(struct dadosForn), 0);
  fAuxForn = fopen("AuxForn.dat", "r+");
  fseek(fAuxForn, sizeof(struct dadosForn), 0);
  while (fread(&Fornecedor, sizeof(Fornecedor), 1, fAuxForn) == 1)
  {
    tamanhoforn = tamanhoforn + fwrite(&Fornecedor, sizeof(struct dadosForn), 1, fFornecedores);
  }
  fclose(fAuxForn);
  remove("AuxForn.dat");
  fclose(fFornecedores);
  printf("\n\nFornecedor excl�ido - Digite <enter> para continuar...");
  getche();
  menuFornenecedor();
}

void excluirArquivoFornecedor()
{
  char op;
  printf("\n\nDeletar o Arquivo <S> ou <N>: ");
  cin >> op;
  op = toupper(op);
  if (op == 'S')
  {
    remove("Fornecedores.dat");
    printf("\nArquivo deletado.");
  }
  else
  {
    printf("\n\nArquivo n�o foi deletado por sua op��o.");
  }
  criaArquivoFornecedor();
  getche();
  menuFornenecedor();
}
// fim fornecedor

// Inicio Funcionarios
void cadastrarFuncionario()
{
  char op;
  system("cls");
  int tamanho = 0;
  fFuncionarios = fopen("Funcionarios.dat", "r+");
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
    fflush(stdin);
    cout << "\nDigite o nome do funcion�rio: ";
    gets(Funcionario.nomeFunc);
    fflush(stdin);
    printf("\nDigite o endere�o do funcion�rio: ");
    gets(Funcionario.endeFunc);
    fflush(stdin);
    printf("\nDigite o email do funcion�rio: ");
    gets(Funcionario.emailFunc);
    fflush(stdin);
    printf("\nDigite o CPF do funcion�rio: ");
    gets(Funcionario.cpfFunc);
    printf("\nDigite o sal�rio do funcion�rio: ");
    cin >> Funcionario.salarioFunc;
    tamanho = tamanho + fwrite(&Funcionario, sizeof(struct dadosFunc), 1, fFuncionarios);
    printf("\n\nContinuar cadastrando <S> ou <N>: ");
    cin >> op;
    op = toupper(op);
  } while (op == 'S');
  fclose(fFuncionarios);
  menuFuncionario();
}

void consultarFuncionario()
{
  system("cls");
  fFuncionarios = fopen("Funcionarios.dat", "r");
  fseek(fFuncionarios, sizeof(struct dadosFunc), 0);
  while (fread(&Funcionario, sizeof(Funcionario), 1, fFuncionarios) == 1)
  {
    system("cls");
    printf("\nNome Funcion�rio     : %s\n", Funcionario.nomeFunc);
    printf("\nEndere�o Funcion�rio : %s\n", Funcionario.endeFunc);
    printf("\nEmail Funcion�rio    : %s\n", Funcionario.emailFunc);
    printf("\nCPF Funcion�rio      : %s\n", Funcionario.cpfFunc);
    printf("\nSal�rio Funcion�rio  : %.2f\n", Funcionario.salarioFunc);
    printf("\nDigite <enter> para continuar");
    getch();
  }
  printf("\n\nFim do arquivo...");
  getch();
  fclose(fFuncionarios);
  menuFuncionario();
}

void consultarNomeFuncionario()
{
  char nom_pro[20];
  int achou = 1;
  int localizou = 1;
  char op;
  system("cls");
  fFuncionarios = fopen("Funcionarios.dat", "r+");
  fseek(fFuncionarios, sizeof(struct dadosFunc), 0);
  fflush(stdin);
  printf("\nDigite o nome para a procura: ");
  gets(nom_pro);
  while (fread(&Funcionario, sizeof(Funcionario), 1, fFuncionarios) == 1)
  {
    achou = strcmp(Funcionario.nomeFunc, nom_pro);
    if (achou == 0)
    {
      printf("\n O Nome �.............: %s", Funcionario.nomeFunc);
      printf("\n O Endere�o �.........: %s", Funcionario.endeFunc);
      printf("\n O Email �............: %s", Funcionario.emailFunc);
      printf("\n O CPF �..............: %s", Funcionario.cpfFunc);
      printf("\n O Sal�rio ,...........: %.2f", Funcionario.salarioFunc);
      printf("\n_____________________________________________\n");
      printf("\nDigite <enter> para continuar");
      getch();
      localizou = 0;
    }
  }
  if (localizou == 1)
  {
    printf("\nFuncion�rio n�o cadastrado\n");
    printf("\nCadastrar funcion�rio <S> ou <N>: ");
    cin >> op;
    op = toupper(op);
    if (op == 'S')
    {
      cadastrarFuncionario();
      getch();
    }
  }
  menuFuncionario();
}

void alterarFuncionario()
{
  char nom_pro[20];
  int achou;
  int pos = 0;
  system("cls");
  fFuncionarios = fopen("Funcionarios.dat", "r+");
  fseek(fFuncionarios, sizeof(struct dadosFunc), 0);
  fflush(stdin);
  printf("\nDigite o nome para procura: ");
  gets(nom_pro);
  while (fread(&Funcionario, sizeof(Funcionario), 1, fFuncionarios) == 1)
  {
    achou = strcmp(Funcionario.nomeFunc, nom_pro);
    pos++;
    if (achou == 0)
    {
      printf("\n O Nome �.............: %s", Funcionario.nomeFunc);
      printf("\n O Endere�o �.........: %s", Funcionario.endeFunc);
      printf("\n O Email �............: %s", Funcionario.emailFunc);
      printf("\n O CPF �..............: %s", Funcionario.cpfFunc);
      printf("\n O Sal�rio ,...........: %.2f", Funcionario.salarioFunc);
      printf("\n_____________________________________________\n");
      printf("\nDigite <enter> para continuar");
      getch();
      fflush(stdin);
      printf("\n\nDigite a altera��o do nome do funcion�rio: ");
      gets(Funcionario.nomeFunc);
      fflush(stdin);
      printf("\nDigite o novo endere�o: ");
      gets(Funcionario.endeFunc);
      printf("\nDigite o novo email: ");
      cin >> Funcionario.emailFunc;
      fflush(stdin);
      printf("\nDigite o novo CPF: ");
      gets(Funcionario.cpfFunc);
      printf("\nDigite o novo sal�rio: ");
      cin >> (Funcionario.salarioFunc);
      fseek(fFuncionarios, pos * sizeof(struct dadosFunc), SEEK_SET);
      fwrite(&Funcionario, sizeof(struct dadosFunc), 1, fFuncionarios);
      fseek(fFuncionarios, sizeof(struct dadosFunc), SEEK_END);
    }
    printf("\nDigite <enter> para continuar...");
    getche();
  }

  fclose(fFuncionarios);
  menuFuncionario();
}
void exlcuirFuncionario()
{
  char nom_pro[20];
  int achou;
  int tamanhoaux = 0;
  int tamanhofunc = 0;

  system("cls");
  fFuncionarios = fopen("Funcionarios.dat", "r+");
  fseek(fFuncionarios, sizeof(struct dadosFunc), 0);
  criaArquivoAuxiliarFuncionarios();
  fAuxFunc = fopen("AuxFunc.dat", "r+");
  fseek(fAuxFunc, sizeof(struct dadosFunc), 0);
  fflush(stdin);
  printf("\nDigite o nome do funcion�rio para procura: ");
  gets(nom_pro);
  while (fread(&Funcionario, sizeof(Funcionario), 1, fFuncionarios) == 1)
  {
    achou = strcmp(Funcionario.nomeFunc, nom_pro);
    if (achou == 0)
    {
      printf("\n O Nome �.............: %s", Funcionario.nomeFunc);
      printf("\n O Endere�o �.........: %s", Funcionario.endeFunc);
      printf("\n O Email �............: %s", Funcionario.emailFunc);
      printf("\n O CPF �..............: %s", Funcionario.cpfFunc);
      printf("\n O Sal�rio ,..........: %.2f", Funcionario.salarioFunc);
      printf("\n_____________________________________________\n");
      printf("\nDigite <enter> para continuar");
      getch();
    }
    else
    {
      tamanhoaux = tamanhoaux + fwrite(&Funcionario, sizeof(struct dadosFunc), 1, fAuxFunc);
    }
  }
  fclose(fAuxFunc);
  fclose(fFuncionarios);
  remove("Funcionarios.dat");
  criaArquivoFuncionario();
  fFuncionarios = fopen("Funcionarios.dat", "r+");
  fseek(fFuncionarios, sizeof(struct dadosFunc), 0);
  fAuxFunc = fopen("AuxFunc.dat", "r+");
  fseek(fAuxFunc, sizeof(struct dadosFunc), 0);
  while (fread(&Funcionario, sizeof(Funcionario), 1, fAuxFunc) == 1)
  {
    tamanhofunc = tamanhofunc + fwrite(&Funcionario, sizeof(struct dadosFunc), 1, fFuncionarios);
  }
  fclose(fAuxFunc);
  remove("AuxFunc.dat");
  fclose(fFuncionarios);
  printf("\n\nFuncion�rio excl�ido - Digite <enter> para continuar...");
  getche();
  menuFuncionario();
}

void excluirArquivoFuncionario()
{
  char op;
  printf("\n\nDeletar o Arquivo <S> ou <N>: ");
  cin >> op;
  op = toupper(op);
  if (op == 'S')
  {
    remove("Funcionarios.dat");
    printf("\nArquivo deletado.");
  }
  else
  {
    printf("\n\nArquivo n�o foi deletado por sua op��o.");
  }
  criaArquivoFuncionario();
  getche();
  menuFuncionario();
}
// fim funcionarios

// inicio produtos
void cadastrarProduto()
{
  char op;
  system("cls");
  int tamanho = 0;
  fClientes = fopen("Produtos.dat", "r+");
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
    fflush(stdin);
    cout << "\nDigite o nome do produto: ";
    gets(Produto.nomeProd);
    printf("\nDigite o c�digo do produto: ");
    cin >> Produto.codProd;
    printf("\nDigite o valor do produto: ");
    cin >> Produto.valorProd;
    tamanho = tamanho + fwrite(&Produto, sizeof(struct dadosProd), 1, fProdutos);

    printf("\n\nContinuar cadastrando <S> ou <N>: ");
    cin >> op;
    op = toupper(op);
  } while (op == 'S');

  fclose(fProdutos);
  menuProdutos();
}

void consultarProduto()
{
  system("cls");
  fProdutos = fopen("Produtos.dat", "r");
  fseek(fProdutos, sizeof(struct dadosProd), 0);
  while (fread(&Produto, sizeof(Produto), 1, fProdutos) == 1)
  {
    system("cls");
    printf("\nNome Produto   : %s\n", Produto.nomeProd);
    printf("\nC�digo Produto : %d\n", Produto.codProd);
    printf("\nValor Produto  : %.2f\n", Produto.valorProd);
    printf("\nDigite <enter> para continuar");
    getch();
  }
  printf("\n\nFim do arquivo...");
  getche();
  fclose(fProdutos);
  menuProdutos();
}
void consulta_nomeProd()
{
  char nom_pro[20];
  int achou = 1;
  int localizou = 1;
  char op;
  system("cls");
  fProdutos = fopen("Produtos.dat", "r+");
  fseek(fProdutos, sizeof(struct dadosProd), 0);
  fflush(stdin);
  printf("\nDigite o nome do produto para a procura: ");
  gets(nom_pro);
  while (fread(&Produto, sizeof(Produto), 1, fProdutos) == 1)
  {
    achou = strcmp(Produto.nomeProd, nom_pro);
    if (achou == 0)
    {
      printf("\n O Produto �.............: %s", Produto.nomeProd);
      printf("\n O C�digo do Produto �...: %d", Produto.codProd);
      printf("\n O Valor do Produto �....: %.2f", Produto.valorProd);
      printf("\n_____________________________________________\n");
      printf("\nDigite <enter> para continuar");
      getch();
      localizou = 0;
    }
  }

  if (localizou == 1)
  {
    printf("\nProduto n�o cadastrado\n");
    printf("\nCadastrar produto <S> ou <N>: ");
    cin >> op;
    op = toupper(op);
    if (op == 'S')
    {
      cadastrarProduto();
      getch();
    }
  }
  menuProdutos();
}

void alterarProduto()
{
  char nom_pro[20];
  int achou;
  int pos = 0;
  system("cls");
  fProdutos = fopen("Produtos.dat", "r+");
  fseek(fProdutos, sizeof(struct dadosProd), 0);
  fflush(stdin);
  printf("\nDigite o nome do produto para procura: ");
  gets(nom_pro);
  while (fread(&Produto, sizeof(Produto), 1, fProdutos) == 1)
  {
    achou = strcmp(Produto.nomeProd, nom_pro);
    pos++;
    if (achou == 0)
    {
      printf("\n O Produto �.............: %s", Produto.nomeProd);
      printf("\n O C�digo do Produto �...: %d", Produto.codProd);
      printf("\n O Valor do Produto �....: %.2f", Produto.valorProd);
      printf("\n_____________________________________________\n");
      printf("\nDigite <enter> para continuar");
      getch();
      fflush(stdin);
      printf("\n\nDigite a altera��o do nome do produto: ");
      gets(Produto.nomeProd);
      printf("\nDigite o novo c�digo do produto: ");
      cin >> Produto.codProd;
      printf("\nDigite o novo valor do produto: ");
      cin >> Produto.valorProd;
      fseek(fProdutos, pos * sizeof(struct dadosProd), SEEK_SET);
      fwrite(&Produto, sizeof(struct dadosProd), 1, fProdutos);
      fseek(fProdutos, sizeof(struct dadosProd), SEEK_END);
    }
    printf("\nDigite <enter> para continuar...");
    getche();
  }

  fclose(fProdutos);
  menuProdutos();
}

void excluirProduto()
{
  char nom_pro[20];
  int achou;
  int tamanhoaux = 0;
  int tamanhoprod = 0;
  system("cls");
  fProdutos = fopen("Produtos.dat", "r+");
  fseek(fProdutos, sizeof(struct dadosProd), 0);
  criaArquivoAuxiliarProdutos();
  fAuxProd = fopen("AuxProd.dat", "r+");
  fseek(fAuxProd, sizeof(struct dadosProd), 0);
  fflush(stdin);
  printf("\nDigite o nome do produto para procura: ");
  gets(nom_pro);
  while (fread(&Produto, sizeof(Produto), 1, fProdutos) == 1)
  {
    achou = strcmp(Produto.nomeProd, nom_pro);
    if (achou == 0)
    {
      printf("\n O Produto �.............: %s", Produto.nomeProd);
      printf("\n O C�digo do Produto �...: %d", Produto.codProd);
      printf("\n O Valor do Produto �....: %.2f", Produto.valorProd);
      printf("\n_____________________________________________\n");
      printf("\nDigite <enter> para continuar");
      getch();
    }
    else
    {
      tamanhoaux = tamanhoaux + fwrite(&Produto, sizeof(struct dadosProd), 1, fAuxProd);
    }
  }
  fclose(fAuxProd);
  fclose(fProdutos);
  remove("Produtos.dat");
  criaArquivoProduto();
  fProdutos = fopen("Produtos.dat", "r+");
  fseek(fProdutos, sizeof(struct dadosProd), 0);
  fAuxProd = fopen("AuxProd.dat", "r+");
  fseek(fAuxProd, sizeof(struct dadosProd), 0);
  while (fread(&Produto, sizeof(Produto), 1, fAuxProd) == 1)
  {
    tamanhoprod = tamanhoprod + fwrite(&Produto, sizeof(struct dadosProd), 1, fProdutos);
  }
  fclose(fAuxProd);
  remove("AuxProd.dat");
  fclose(fProdutos);
  printf("\n\nProduto excl�ido - Digite <enter> para continuar...");
  getche();
  menuProdutos();
}
void exlcuirArquivoProduto()
{
  char op;
  printf("\n\nDeletar Arquivo <S> ou <N>: ");
  cin >> op;
  op = toupper(op);

  if (op == 'S')
  {
    remove("Produtos.dat");
    printf("\nArquivo deletado.");
  }
  else
  {
    printf("\n\nArquivo n�o foi deletado por sua op��o.");
  }
  criaArquivoProduto();
  getche();
  menuProdutos();
}
// Menu Principal
void menuPrincipal()
{
  system("cls");
  printf("\nMenu Principal: \n");
  printf("\n1 - Clientes");
  printf("\n2 - Fornecedores");
  printf("\n3 - Funcion�rios");
  printf("\n4 - Produtos");
  printf("\n5 - Sair do sistema\n");
  printf("\nDigite uma op��o: ");
  cin >> opc;
  switch (opc)
  {
  case 1:
    menuCliente();
    break;
  case 2:
    menuFornenecedor();
    break;
  case 3:
    menuFuncionario();
    break;
  case 4:
    menuProdutos();
    break;
  case 5:
    exit(0);
  }
}

void menuCliente()
{
  system("cls");
  printf("\nMenu Cliente: \n");
  printf("\n1 - Cadastrar Cliente");
  printf("\n2 - Consultar todos os Clientes");
  printf("\n3 - Consultar Cliente Por Nome");
  printf("\n4 - Alterar um Registro de um Cliente");
  printf("\n5 - Excluir um Registro de um Cliente");
  printf("\n6 - Excluir todo o Arquivo Clientes");
  printf("\n7 - Voltar ao Menu Principal\n");
  printf("\nDigite uma op��o: ");
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
    excluirCLiente();
    break;
  case 6:
    excluirAuxiliarCliente();
    break;
  case 7:
    menuPrincipal();
    break;
  }
}
void menuFornenecedor()
{
  system("cls");
  printf("\nMenu Fornecedor: \n");
  printf("\n1 - Cadastrar Fornecedor");
  printf("\n2 - Consultar todos os Fornecedores");
  printf("\n3 - Consultar Fornecedor Por Nome");
  printf("\n4 - Alterar um Registro de um Fornecedor");
  printf("\n5 - Excluir um Registro de um Fornecedor");
  printf("\n6 - Excluir todo o Arquivo Fornecedores");
  printf("\n7 - Voltar ao Menu Principal\n");
  printf("\nDigite uma op��o: ");
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
    alteraForn();
    break;
  case 5:
    excluirFornecedor();
    break;
  case 6:
    excluirArquivoFornecedor();
    break;
  case 7:
    menuPrincipal();
    break;
  }
}

void menuFuncionario()
{
  system("cls");
  printf("\nMenu Funcion�rio: \n");
  printf("\n1 - Cadastrar Funcion�rio");
  printf("\n2 - Consultar todos os Funcion�rios");
  printf("\n3 - Consultar Funcion�rio Por Nome");
  printf("\n4 - Alterar um Registro de um Funcion�rio");
  printf("\n5 - Excluir um Registro de um Funcion�rio");
  printf("\n6 - Excluir todo o Arquivo Funcion�rios");
  printf("\n7 - Voltar ao Menu Principal\n");
  printf("\nDigite uma op��o: ");
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
    alterarFuncionario();
    break;
  case 5:
    exlcuirFuncionario();
    break;
  case 6:
    excluirArquivoFuncionario();
    break;
  case 7:
    menuPrincipal();
    break;
  }
}

void menuProdutos()
{
  system("cls");
  printf("\nMenu Produto: \n");
  printf("\n1 - Cadastrar Produto");
  printf("\n2 - Consultar todos os Produtos");
  printf("\n3 - Consultar Produto Por Nome");
  printf("\n4 - Alterar um Registro de um Produto");
  printf("\n5 - Excluir um Registro de um Produto");
  printf("\n6 - Excluir todo o Arquivo Produtos");
  printf("\n7 - Voltar ao Menu Principal\n");

  printf("\nDigite uma op��o: ");
  cin >> opc;
  switch (opc)
  {
  case 1:
    cadastrarProduto();
    break;
  case 2:
    consultarProduto();
    break;
  case 3:
    consulta_nomeProd();
    break;
  case 4:
    alterarProduto();
    break;
  case 5:
    excluirProduto();
    break;
  case 6:
    exlcuirArquivoProduto();
    break;
  case 7:
    menuPrincipal();
    break;
  }
}

main()
{
  setlocale(LC_ALL, "portuguese");
  system("cls");
  criaArquivoCliente();
  criaArquivoFornecedor();
  criaArquivoFuncionario();
  criaArquivoProduto();
  opc = 1;
  do
  {
    menuPrincipal();

  } while (opc != 5);
}
