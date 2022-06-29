#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include <time.h>

// Registro / Tipo de Variavel
struct tCliente {
unsigned int rgCliente;
char nome[30];
float valor;
char deletado; // deletado = '*' / nao deletado = ' ' - exclusao logica
};

// Registro / Tipo de Variavel
struct tVeiculos {
int vagas;
int codigo;
char modelo[30];
float valorDiaria;
char deletado; // deletado = '*' / nao deletado = ' ' - exclusao logica
};

//Prototipos
int menu();
void cadastroDeCliente();
void cadastroDeVeiculo();
void listar();
void consultar();
void alterar();
void excluir();
void organizar();
void copiar();

//Programa Principal
int main(void) {
    setlocale(LC_ALL,"Portuguese");
int op;

do{
op = menu();
switch (op) {

case 1:
printf("===Incluir===\n");
cadastroDeCliente();
break;

case 2:
printf("===Incluir===\n");
cadastroDeVeiculo();
break;

case 3:
printf("===Lista de clientes===\n");
listarClientes();
break;

case 4:
printf("===Lista de veículos===\\n");
listarVeiculos ();
break;

case 5:
printf("===Listar todos===\\n");
listarTodos();
break;

case 6:
printf("===Consultar Cliente===\n");
consultarCliente();
break;

case 7:
printf("===Consultar Veículos===\n");
consultarVeiculos();
break;

case 8:
printf("===Alterar===\n");
alterar();
break;

case 9:
printf("===Randomizar===\n");
randomCode();
break;

case 10:
printf("===Organizar Arquivo===\n"); //funciona como uma exclusao fisica
organizar();
break;

case 11:
printf("===Backup===\n");
copiar();
break;

case 12:
printf("===Restore===\n");
copiar();
}
}while (op != 0);

// system("pause");
return 0;
}

//Menu de Opcoes
int menu (void){

int opcao;
do {
printf("=== MENU PARA CADASTRO DE PRODUTOS ===\\n");
printf("1. Cadastro de cliente\n");
printf("2. Cadastro de veículo\n");
printf("3. Listar clientes\n");
printf("4. Listar veículos\n");
printf("5. Listar todos\n");
printf("6. Consultar clientes\n");
printf("7. Consultar veículos\n");
printf("8. Alterar\n");
printf("9. Excluir\n");
printf("10. Organizar Arquivo\n");
printf("11. Backup\n");
printf("12. Restore\n");
printf("0. Sair\n");
printf("Digite sua opcao: ");
scanf("%d", &opcao);
if ((opcao < 0) || (opcao > 8))
printf ("Opcao Digitada Incorreta!\n");
} while ((opcao < 0) || (opcao > 8));

return opcao;
}

//Funcao Inclusao
void cadastroDeCliente(){
struct tCliente clientes;

FILE *arq = fopen("clientes.pro", "ab");
if (arq == NULL){
printf("Erro ao abrir arquivo");
return;
}
printf("Digite o número do rg do cliente: \n");
scanf("%u", &clientes.rgCliente);
printf("Digite o nome do cliente: \n");
fflush(stdin);
gets(clientes.nome);
/*printf("Digite o valor do produto: \n");
scanf("%f", &clientes.valor);*/
fwrite (&clientes, sizeof(clientes), 1, arq);
fclose(arq);
}

void cadastroDeVeiculo(){
struct tVeiculos veiculos;

FILE *arq = fopen("veiculos.pro", "ab");
if (arq == NULL){
printf("Erro ao abrir arquivo");
return;
}
printf("Digite a quantidade de vagas do veiculo: \n");
scanf("%d", &veiculos.vagas);
printf("Digite o modelo do veiculo: \n");
fflush(stdin);
gets(veiculos.modelo);
printf("Digite o valor da diária do veículo: \n");
scanf("%f", &veiculos.valorDiaria);
veiculos.codigo = randomCode(rand() % 10);
fwrite (&veiculos, sizeof(veiculos), 1, arq);
fclose(arq);
}

//Funcao Listar Clientes
void listarClientes (){

struct tCliente clientes;
FILE *arq = fopen("clientes.pro", "rb");
if (arq == NULL){
printf("Arquivo inexistente!");
return;
}

while (fread (&clientes, sizeof(clientes), 1, arq))
printf("Cod %u --- Descricao: %-8s --- Valor R$ %4.2f --- Deletado?(%c)\n",clientes.rgCliente, clientes.nome, clientes.valor, clientes.deletado);

fclose(arq);
}

//Funcao Listar Veículos
void listarVeiculos (){

struct tVeiculos veiculos;
FILE *arq = fopen("veiculos.pro", "rb");
if (arq == NULL){
printf("Arquivo inexistente!");
return;
}

while (fread (&veiculos, sizeof(veiculos), 1, arq))
printf("Cod %hu --- Modelo: %s --- Valor da diária R$ %.2f\n",veiculos.codigo, veiculos.modelo, veiculos.valorDiaria);

fclose(arq);
}

void listarTodos()
{
    printf("\n===Lista de clientes===\n");
    listarClientes();

    printf("\n===Lista de veículos===\n");
    listarVeiculos();
}

//Funcao Randomizar código
int randomCode(unsigned int aleatorio){

unsigned short cod;
cod = ((aleatorio * (time(NULL)))%1000000); //num aleatório entre 0 e 999

return cod;
}

//Funcao Consultar Veículos
void consultarVeiculos(){

FILE *arq = fopen("veiculos.pro", "rb");
if (arq == NULL){
printf("Arquivo inexistente!");
return;
}

struct tVeiculos veiculos;
int cod, achei = 0;
printf ("Digite o código de veículo que procura: \n");
scanf ("%d", &cod);

while (fread (&veiculos, sizeof(veiculos), 1, arq)){
if ((cod == veiculos.codigo)) {
printf("Cod %u --- Modelo: %s --- Valor R$ %.2f\n",veiculos.codigo, veiculos.modelo, veiculos.valorDiaria);
achei = 1;
}
}

if (!achei)
printf ("\\nCodigo nao cadastrado!!\n");

fclose(arq);

}

//Funcao Consultar clientes
void consultarCliente(){

FILE *arq = fopen("clientes.pro", "rb");
if (arq == NULL){
printf("Arquivo inexistente!");
return;
}

struct tCliente clientes;
int cod, achei = 0;
printf ("Digite o rg que procura: \n");
scanf ("%d", &cod);

while (fread (&clientes, sizeof(clientes), 1, arq)){
if ((cod == clientes.rgCliente) && (clientes.deletado != '*')) {
printf("Cod %u --- Descricao: %-8s --- Valor R$ %4.2f\n",clientes.rgCliente, clientes.nome, clientes.valor);
achei = 1;
}
}

if (!achei)
printf ("\\nCodigo nao cadastrado!!\n");

fclose(arq);

}

//Funcao Alterar
void alterar(){
FILE *arq = fopen("clientes.pro", "r+b");
if (arq == NULL){
printf("Arquivo inexistente!");
return;
}

struct tCliente clientes;
int cod, achei = 0;
printf ("Digite o número rg do cliente que deseja alterar: \n");
scanf ("%d", &cod);

while (fread (&clientes, sizeof(clientes), 1, arq)){
if (cod == clientes.rgCliente){
printf("Cod %d --- Descricao: %-8s --- Valor R$ %4.2f\\n\\n",clientes.rgCliente, clientes.nome, clientes.valor);
achei = 1;

fseek(arq,sizeof(struct tCliente)*-1, SEEK_CUR);
printf("\\nDigite a nova nome: \\n");
fflush(stdin);
gets(clientes.nome);
printf("\\nDigite o novo preco....: \\n");
scanf("%f", &clientes.valor);

fwrite(&clientes, sizeof(clientes), 1, arq);
fseek(arq, sizeof(clientes)* 0, SEEK_END);
return;
}
}

if (!achei)
printf ("\\nCodigo nao cadastrado!!\\n");

fclose(arq);
}

//Exclusao Logica
void excluir(){

FILE *arq = fopen("clientes.pro", "r+b");
if (arq == NULL){
printf("Arquivo inexistente!");
return;
}

struct tCliente clientes;
int cod, achei = 0;
char certeza;
printf ("\\nDigite o número do rg do cliente que deseja EXCLUIR: \\n");
scanf ("%d", &cod);

while (fread (&clientes, sizeof(clientes), 1, arq)){
if (cod == clientes.rgCliente){
printf("Cod %d --- Descricao: %-8s --- Valor R$ %4.2f\\n\\n",clientes.rgCliente, clientes.nome, clientes.valor);
achei = 1;

printf("\\nTem certeza que quer excluir este produto? s/n \\n");
fflush(stdin);
scanf("%c", &certeza);
if (certeza == 's'){
clientes.deletado = '*';
printf("\\nProduto excluido com Sucesso! \\n");
fseek(arq,sizeof(struct tCliente)*-1, SEEK_CUR);
fwrite(&clientes, sizeof(clientes), 1, arq);
fseek(arq, sizeof(clientes)* 0, SEEK_END);
return;
}
else if (certeza == 'n')
return;
}
}

if (!achei)
printf ("\\nCodigo nao cadastrado!!\\n");

fclose(arq);
}

//Organizar Arquivo
void organizar(){
struct tCliente clientes;
//struct tCliente produtosB; // arquivo de backup

FILE *arq = fopen("clientes.pro", "rb");
if (arq == NULL){
printf("Arquivo inexistente!");
return;
}

FILE *arqB = fopen("BackupProdutos.pro", "wb");
if (arqB == NULL){
printf("Erro na abertura!");
return;
}

while (fread (&clientes, sizeof(clientes), 1, arq)){
if (clientes.deletado != '*'){

fseek(arqB,sizeof(clientes)*-1, SEEK_CUR);
fwrite(&clientes, sizeof(clientes), 1, arqB);
fseek(arqB, sizeof(clientes)* 0, SEEK_END);

}
}

fclose(arq);
fclose(arqB);

remove("clientes.pro");
int teste = 0;
teste = rename("BackupProdutos.pro", "clientes.pro");
if (teste == 0){
printf("\\nArquivo Renomeado com Sucesso! \\n");
printf("\\nArquivo organizado com Sucesso! %d \\n", teste);

}
else printf("\\nErro ao Renomear! %d \\n",teste);
return;

}

//Backup e Restore
void copiar(){
}
