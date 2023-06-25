#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1000
#define MODE_BTXT_ON 1

int i, d;

FILE *fp;
fpos_t position;
//
void Busca_txt(FILE *fp, char str[60], const int _MODE), teste_de_fun(), printFile(FILE *fptr), apagar_linha(const int line), substituir_texto(char texto[60]);
void pegar_posicao(FILE *fp, int i), Busca_txt(FILE *fp, char str[60], const int _MODE);
void label(int Lin, int Col, char Texto[]), janela(int x1, int y1, int x2, int y2, char *tipo_moldura, char titulo[]), inicializar_tela();
int centralizar_text(char vector[]);
void gotoxy(int x, int y);
void ler_string(int x, int y, int tamanho,char* string);
//{
double ler_decimal(int x, int y, int tamanho);
char resp;
char str[60], c, resposta;
//}


int main(void)
{
    inicializar_tela();
    janela(1, 1, 29, 80, "░", "Titulo");
    fp = fopen("file.txt", "r+");
    if (fp == NULL)
    {
        perror("Error opening file");
        return (-1);
    }

    int idade;
    double altura;
    char nome[50];
    
    label(3, 2, "-Digite seu nome:");
    
    ler_string(3,20,50,nome);


    label(4, 2, "-Digite sua altura:");
    altura = ler_decimal(4, 22, 10);

    label(5, 2, "-Digite sua idade:");
    idade = ler_inteiro(5, 21, 10);

     gotoxy(3,30);
     printf("Nome: %s ",nome);
     gotoxy(4,30);
     printf("Altura: %0.2f ",altura);
     gotoxy(5,30);
     printf("idade: %i ",idade);
     

  
    

    gotoxy(29, 1);  
    
    {
        fclose(fp);
    }
    return 0;
}

void gotoxy(int x, int y)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){y - 1, x - 1});
}

void inicializar_tela()
{
    system("mode con:cols=80 lines=30");
    system("cls");
    gotoxy(29, 1);
}

int centralizar_text(char vector[])
{
    int veri_vaz;
    int i;

    do
    {

        veri_vaz = vector[i];
        i++;
    } while (veri_vaz != NULL);
    if(i%2 == 0){
        i = (int)floor((i+1) / 2);
    }else{
        i = (int)ceil((i) / 2);
    }
    
    return i;
}

void label(int Lin, int Col, char Texto[])
{
    gotoxy(Lin, Col);
    printf("%s", Texto);
}

void janela(int x1, int y1, int x2, int y2, char *tipo_moldura, char titulo[])
{
    int var_centr = 0;
    for (int i = 1; i < y2 + 1; i++)
    {
        gotoxy(x1, i);
        printf(tipo_moldura);
        gotoxy(x2, i);
        printf(tipo_moldura);
    }

    {
        var_centr = centralizar_text(titulo);
        gotoxy(x1, (y2) / 2 - var_centr);
        printf("%s", titulo);
    }
    gotoxy(29, y1);
}

double ler_decimal(int x, int y, int tamanho)
{
    char texto[30];
    double float_number;
    gotoxy(x, y);
    fgets(texto, tamanho+1, stdin);
    fflush(stdin);
    for (int i = 0; i < tamanho; i++)
    {
        if (texto[i] == ',')
        {
            texto[i] = '.';
            break;
        }
    }
    float_number = atof(texto);
    return float_number;
}

int ler_inteiro(int x, int y, int tamanho)
{
    char texto[30];
    int int_number;
    gotoxy(x, y);
    fflush(stdin);
    fgets(texto, tamanho+1, stdin);
    fflush(stdin);

    int_number = atoi(texto);

    return int_number;
}

void ler_string(int x, int y, int tamanho,char* string){
    char str[tamanho];
    gotoxy(x, y);
    
    fgets(str,tamanho,stdin);
    fflush(stdin);
    
    strcpy(string,str); 
    
}

// ESSAS SÃO AS FUNÇÕES RELACIONADA A DELETAR, PEGAR POSIÇÃO, SUBSTITUIR O TEXTO EM UMA POSIÇÃO DETERMINADA, BUSCAR UM TEXTO ESPECIFICO E PRINTAR UMA COPIA DO ARQUIVO NA TELA
void Busca_txt(FILE *fp, char str[60], const int _MODE)
{

    char copiatexto[60];
    printf("Digite o texto que deseja buscar ? \n");
    scanf("%s", copiatexto);
    getchar();

    if (_MODE == MODE_BTXT_ON)
    {
        strcat(copiatexto, "\n");
        while (strcoll(str, copiatexto) != 0)
        {
            fgets(str, 60, fp);
            printf("%i -- %s", i, str);
            i++;
        }
        pegar_posicao(fp, 2);
    }
    else
    {
        printFile(fp);
    }
}

void pegar_posicao(FILE *fp, int i)
{
    fflush(fp);
    rewind(fp);
    int k = 0;
    freopen("file.txt", "r+", fp);
    while (k != i)
    {
        fgets(str, 60, fp);
        k++;
    }
    fgetpos(fp, &position);
    fclose(fp);
}

void substituir_texto(char texto[60])
{
    freopen("file.txt", "r+", fp);
    fsetpos(fp, &position);
    fsetpos(fp, &position);
    fputs(texto, fp);
}

void apagar_linha(const int line)
{
    FILE *temp, *src;
    char buffer[BUFFER_SIZE];
    int count = 1;

    fflush(fp);
    fclose(fp);
    freopen("file.txt", "r", fp);

    temp = fopen("delete.tmp", "w");
    if (temp == NULL)
    {
        printf("Não foi possível criar o arquivo temp");
        exit(1);
    }
    {
        rewind(fp);

        while ((fgets(buffer, BUFFER_SIZE, fp)) != NULL)
        {
            if (line != count)
            {
                fputs(buffer, temp);
                count++;
            }
            else
            {
                if (line == count)
                {
                    fputs("\n", temp);
                    count++;
                }
            }
        }
    }
    fclose(fp);
    fclose(temp);
    remove("file.txt");
    rename("delete.tmp", "file.txt");
    src = fopen(fp, "r");
    printFile(src);
    fclose(src);

}

void printFile(FILE *fptr)
{
    char ch;
    while ((ch = fgetc(fptr)) != EOF)
        putchar(ch);
}

void teste_de_fun()
{

    // essa função sempre precisa vir antes de substituir texto
    pegar_posicao(fp, 2);
    apagar_linha(2);
    // Pode trocar o texto aqui dentro
    substituir_texto("Futebol");

    printf("\n\nDeseja apagar uma linha ");
    resposta = getchar();
    getchar();

    if (resposta == 's')
    {
        scanf("%i", &d);
        apagar_linha(d);
    }
}
// ESSAS SÃO AS FUNÇÕES RELACIONADA A DELETAR, PEGAR POSIÇÃO, SUBSTITUIR O TEXTO EM UMA POSIÇÃO DETERMINADA, BUSCAR UM TEXTO ESPECIFICO E PRINTAR UMA COPIA DO ARQUIVO NA TELA