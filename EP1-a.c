# include <stdio.h>
int main () {
    int n;
    int repn;
    int res;
    int soma;
    int pot3;
    printf("Envie uma sequência de números em base 3 terminada em 0:\n");
    scanf("%d",& n);
    repn = n;
    while (repn > 0) {
        soma = 0;
        pot3 = 1;
        while (n > 0) {
            res = n % 10;
            n = n / 10;
            soma = soma + res * pot3;
            pot3 = pot3 * 3; 
        } 
        if (soma != 0) {
            printf("%d\n", soma);
            scanf("%d", & n);
        }
        repn = soma;
    }
    return 0;
}
