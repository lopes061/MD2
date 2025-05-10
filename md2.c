#include <stdio.h>
//Passo 1 usar o algoritmo de Euclides para descobrir o mdc
int mdc(int g , int n )
{
    while (n!=0)
    { 
        int temp = n;
        n = g%n; 
        g = temp; 
    }
    return g;
}
//Passo 1.2 apos calcular o mdc verifica se é igual a 1 se for retorna True se não retorna False.
// Se o mdc for igual a 1 signfiica que sao primos ou seja coprimos mas não significa que g é primo e n é primo mas sim que eles são coprimos.
int e_primo(int g, int n)
{
    return mdc(g,n) == 1;
}
//Passo 2 calcula o inverso usando divisões sucessivas
int inverso(int g, int n)
{
    
    
}

int main()
{
    int h,g,n,a,x,n;
    printf("Digite os valores inteiros positivos H, G, n, x e n1:\n");
    scanf("%d %d %d %d %d", h, &g, &n, &x, &n1);
    printf("Passo 1: Verificando se G = %d e n = %d são coprimos \n",g,n);
    if (!mdc)
    {
        printf("Não são primos logo a divisão não é possivel.")
    }
    

    return 0;
}