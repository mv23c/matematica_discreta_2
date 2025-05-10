#include <stdio.h>

// Função para calcular o MDC usando o Algoritmo de Euclides
int mdc(int a, int b) {
    int temp;

    while (b != 0) {
        temp = a % b;
        a = b;
        b = temp;
    }

    return a;
}

// Função para calcular o inverso modular usando o algoritmo extendido de Euclides
int inversoModular(int a, int n) {
    int t = 0, novo_t = 1;
    int r = n, novo_r = a;
    int quociente, temp;

    while (novo_r != 0) {
        quociente = r / novo_r;

        temp = t;
        t = novo_t;
        novo_t = temp - quociente * novo_t;

        temp = r;
        r = novo_r;
        novo_r = temp - quociente * novo_r;
    }

    if (r > 1) 
        return -1; // sem inverso

    if (t < 0) 
        t += n;

    return t;
}

// Função para verificar se dois números são coprimos
int coprimos(int a, int b) {
    return mdc(a, b) == 1;
}

// Função para verificar se um número é primo
int ehPrimo(int n) {
    if (n < 2) 
        return 0;

    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return 0;

    return 1;
}

// Função para calcular a função totiente de Euler
int totienteEuler(int n) {
    int resultado = n;
    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;
            resultado -= resultado / p;
        }
    }
    if (n > 1)
        resultado -= resultado / n;
        
    return resultado;
}

// Função de exponenciação modular eficiente
int expMod(int base, int expoente, int mod) {
    int resultado = 1;
    base = base % mod;
    while (expoente > 0) {
        if (expoente % 2 == 1)
            resultado = (resultado * base) % mod;
        expoente = expoente >> 1;
        base = (base * base) % mod;
    }
    return resultado;
}

int main() {
    int H; 
    int G; 
    int n; 
    int x; // expoente 
    int n1; // modulo

    printf("Informe o valor de H: ");
    scanf("%d", &H);
    printf("Informe o valor de G: ");
    scanf("%d", &G);
    printf("Informe o valor de n: ");
    scanf("%d", &n);
    printf("Informe o expoente x: ");
    scanf("%d", &x);
    printf("Informe o modulo n1: ");
    scanf("%d", &n1);

    printf("\nEtapa 1: Verificar se G e n são primos\n");
    if (!ehPrimo(G) || !ehPrimo(n)) {
        printf("G (%d) e n (%d) devem ser primos. Divisão modular não é possível.\n", G, n);
        return 0;
    } else {
        printf("G (%d) e n (%d) são primos.\n", G, n);
    }

    printf("\nEtapa 2: Calcular o inverso de G em Zn\n");
    int G_inverso = inversoModular(G, n);
    if (G_inverso == -1) {
        printf("G (%d) não possui inverso em Z%d. Divisão modular impossível.\n", G, n);
        return 0;
    } else {
        printf("O inverso de G (%d) em Z%d é %d.\n", G, n, G_inverso);
    }

    printf("\nEtapa 3: Dividir H por G e encontrar a\n");
    int a = (H * G_inverso) % n;
    printf("a = (H * G^-1) mod n = (%d * %d) mod %d = %d\n", H, G_inverso, n, a);

    printf("\nEtapa 4: Verificar se a e n1 são coprimos\n");
    if (coprimos(a, n1)) {
        printf("a (%d) e n1 (%d) são coprimos.\n", a, n1);
    } else {
        printf("a (%d) e n1 (%d) não são coprimos. Operação inválida.\n", a, n1);
        return 0;
    }

    printf("\nEtapa 5: Verificar se n1 é primo\n");
    int n1EhPrimo = ehPrimo(n1);
    if (n1EhPrimo)
        printf("n1 (%d) é primo.\n", n1);
    else
        printf("n1 (%d) não é primo.\n", n1);

    printf("\nEtapa 6: Determinar x1\n");
    int x1;
    if (n1EhPrimo) {
        x1 = n1 - 1;
        printf("Como n1 é primo, x1 = n1 - 1 = %d\n", x1);
    } else {
        x1 = totienteEuler(n1);
        printf("Como n1 não é primo, x1 = φ(n1) = %d\n", x1);
    }

    printf("\nEtapa 7: Decompor x na forma x = x1 * q + r\n");
    int q = x / x1;
    int r = x % x1;
    printf("x = %d = %d * %d + %d\n", x, x1, q, r);

    printf("\nEtapa 8: Calcular a^x1 mod n1\n");
    int x2 = expMod(a, x1, n1);
    printf("a^x1 mod n1 = %d^%d mod %d = %d\n", a, x1, n1, x2);

    printf("\nEtapa 9: Calcular (x2^q) mod n1\n");
    int x2q = expMod(x2, q, n1);
    printf("(%d^%d) mod %d = %d\n", x2, q, n1, x2q);

    printf("\nEtapa 10: Calcular a^r mod n1\n");
    int ar = expMod(a, r, n1);
    printf("%d^%d mod %d = %d\n", a, r, n1, ar);

    printf("\nEtapa 11: Calcular resultado final\n");
    int resultado = (x2q * ar) % n1;
    printf("Resultado final: ((%d * %d) mod %d) = %d\n", x2q, ar, n1, resultado);

    return 0;
}
