#include <stdio.h>

int eh_primo(int numero) {
    if (numero <= 1) return 0;
    if (numero <= 3) return 1;
    if (numero % 2 == 0 || numero % 3 == 0) return 0;
    
    for (int i = 5; i * i <= numero; i += 6) {
        if (numero % i == 0 || numero % (i + 2) == 0) return 0;
    }
    return 1;
}

int calcular_mdc(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int calcular_inverso_modular(int G, int n) {
    int t = 0, novo_t = 1;
    int r = n, novo_r = G;
    
    while (novo_r != 0) {
        int quociente = r / novo_r;
        int temp = novo_t;
        novo_t = t - quociente * novo_t;
        t = temp;
        
        temp = novo_r;
        novo_r = r - quociente * novo_r;
        r = temp;
    }
    
    if (r > 1) {
        printf("O inverso de %d em Z%d nao existe pois MDC(%d, %d) = %d != 1\n", G, n, G, n, r);
        return -1;
    }
    if (t < 0) {
        t += n;
    }
    return t;
}

int calcular_totiente_euler(int n) {
    if (n == 1) return 1;
    if (eh_primo(n)) return n - 1;

    int resultado = n;
    for (int p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0) n /= p;
            resultado -= resultado / p;
        }
    }
    if (n > 1) resultado -= resultado / n;
    return resultado;
}

int exponenciacao_modular(int base, int expoente, int modulo) {
    int resultado = 1;
    base = base % modulo;

    while (expoente > 0) {
        if (expoente % 2 == 1)
            resultado = (resultado * base) % modulo;
        expoente = expoente >> 1;
        base = (base * base) % modulo;
    }

    return resultado;
}

int main() {
    int H, G, n, expoente, modulo_final;

    printf("=== Sistema de Verificacao Modular ===\n");
    printf("Autor: Enzo Lopes Ferreira\n");
    printf("Matricula: 232002000\n\n");

    printf("Digite os valores de H, G e n (para calcular base = H/G em Zn): ");
    scanf("%d %d %d", &H, &G, &n);
    printf("Digite o expoente: ");
    scanf("%d", &expoente);
    printf("Digite o modulo final: ");
    scanf("%d", &modulo_final);

    printf("\n=== ETAPA 1: Verificar se G e n sao primos entre si ===\n");
    printf("Para que a divisao modular H/G seja valida, G e n precisam ser coprimos.\n");
    int mdc_gn = calcular_mdc(G, n);
    if (mdc_gn != 1) {
        printf("G (%d) e n (%d) NAO sao coprimos (MDC = %d).\n", G, n, mdc_gn);
        printf("Nao e possivel calcular o inverso de G em Z%d.\n", n);
        return 0;
    } else {
        printf("G (%d) e n (%d) SAO coprimos (MDC = 1).\n", G, n);
    }

    printf("\n=== ETAPA 2: Calcular o inverso de G em Zn ===\n");
    printf("Como G e n sao coprimos, podemos calcular o inverso modular de G em relacao a n.\n");
    int inverso_G = calcular_inverso_modular(G, n);
    if (inverso_G == -1) return 0;
    printf("O inverso de %d em Z%d e %d, pois (%d * %d) mod %d = 1\n", G, n, inverso_G, G, inverso_G, n);

    printf("\n=== ETAPA 3: Calcular base = H/G em Zn ===\n");
    printf("Formula: base = (H * inverso_G) mod n\n");
    int base = (H % n) * inverso_G % n;
    printf("Calculo: base = (%d * %d) mod %d = %d\n", H % n, inverso_G, n, base);

    printf("\n=== ETAPA 4: Verificar se base e modulo_final sao coprimos ===\n");
    int mdc_base_modulo = calcular_mdc(base, modulo_final);
    printf("Verificando se podemos aplicar Fermat ou Euler...\n");
    if (mdc_base_modulo != 1) {
        printf("base (%d) e modulo_final (%d) NAO sao coprimos (MDC = %d).\n", base, modulo_final, mdc_base_modulo);
    } else {
        printf("base (%d) e modulo_final (%d) SAO coprimos (MDC = 1).\n", base, modulo_final);
    }

    printf("\n=== ETAPA 5: Verificar se modulo_final e primo ===\n");
    int modulo_primo = eh_primo(modulo_final);
    if (modulo_primo) {
        printf("modulo_final (%d) E um numero primo.\n", modulo_final);
    } else {
        printf("modulo_final (%d) NAO e primo.\n", modulo_final);
    }

    printf("\n=== ETAPA 6/7: Determinar x1 usando Fermat ou Euler ===\n");
    int x1;
    if (modulo_primo && mdc_base_modulo == 1) {
        printf("Como modulo_final e primo e base e coprimo com ele, usamos o Pequeno Teorema de Fermat:\n");
        printf("Fermat: base^(modulo_final - 1) equivale a 1 (mod modulo_final)\n");
        x1 = modulo_final - 1;
        printf("Entao, x1 = %d\n", x1);
    } else if (mdc_base_modulo == 1) {
        printf("Usamos o Teorema de Euler: base^phi(n) equivale a 1 (mod n)\n");
        x1 = calcular_totiente_euler(modulo_final);
        printf("phi(%d) = %d, entao x1 = %d\n", modulo_final, x1, x1);
    } else {
        printf("Nao e possivel aplicar os teoremas de Fermat nem de Euler.\n");
        printf("Motivo: base (%d) e modulo_final (%d) NAO sao coprimos (MDC = %d) e modulo_final NAO e primo.\n",
               base, modulo_final, mdc_base_modulo);
        return 0;
    }

    printf("\n=== ETAPA 8: Decompor o expoente ===\n");
    int quociente = expoente / x1;
    int resto = expoente % x1;
    printf("Usamos: expoente = x1 * quociente + resto\n");
    printf("%d = %d * %d + %d\n", expoente, x1, quociente, resto);

    printf("\n=== ETAPA 9/10: Calcular os valores intermediarios ===\n");
    printf("Reescrevendo a potencia:\n");
    printf("base^expoente mod modulo_final = ((base^x1)^quociente * base^resto) mod modulo_final\n");

    int x2 = exponenciacao_modular(base, x1, modulo_final);
    printf("1. base^x1 mod modulo_final = %d^%d mod %d = %d\n", base, x1, modulo_final, x2);

    int x2_quociente = exponenciacao_modular(x2, quociente, modulo_final);
    printf("2. (base^x1)^quociente mod modulo_final = %d^%d mod %d = %d\n", x2, quociente, modulo_final, x2_quociente);

    int base_resto = exponenciacao_modular(base, resto, modulo_final);
    printf("3. base^resto mod modulo_final = %d^%d mod %d = %d\n", base, resto, modulo_final, base_resto);

    printf("\n=== ETAPA 11: Combinar os resultados ===\n");
    int resultado_final = (x2_quociente * base_resto) % modulo_final;
    printf("Resultado final:\n");
    printf("((%d * %d) mod %d) = %d\n", x2_quociente, base_resto, modulo_final, resultado_final);

    printf("\n=== RESULTADO FINAL ===\n");
    printf("Resposta: %d^%d mod %d = %d\n", base, expoente, modulo_final, resultado_final);

    printf("\n=== AGRADECIMENTO ===\n");
    printf("Obrigado por utilizar o meu sistema de verificacao modular!\n");
    printf("Espero que o programa tenha sido claro e importante para o seu aprendizado.\n");

    return 0;
}
