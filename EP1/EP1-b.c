# include <stdio.h>
int main () {
    int opcao, num, soma, res, fant, fatual, fprox, i;
    scanf("%d",& opcao);
    scanf("%d",& num);

    if (opcao == 0) {
        while (num > 0) {
            while (num > 0) {
                fant = 0;
                fatual = 1;
                printf("1");

                while (num >= (fatual + fant)) {
                    fprox = fatual + fant;
                    fant = fatual;
                    fatual = fprox;
                }

                num -= fatual;

                if (num == 0) {
                    fprox = fatual - fant;
                    fatual = fant;
                    fant = fprox;
                }

                while (num < fant) {
                    fprox = fatual - fant;
                    fatual = fant;
                    fant = fprox; 
                    printf("0");
                }
            }
            printf("\n");
            scanf("%d", & num);
        }
    }

    if (opcao == 1) {
        while (num != 0) {
            while (num > 0 ) {
                fant = 1;
                fatual = 1;
                i = 0;

                while (num > fatual) {
                    fprox = fant + fatual;
                    fant = fatual;
                    fatual = fprox;
                    i ++;
                }

                if (num == fatual) {
                    printf("F_%d (%d)",i + 1,fatual);
                    num -= fatual;
                }

                if (num > fant) {
                    printf("F_%d (%d) + ",i ,fant);
                    num -= fant;
                }
            }
            printf ("\n"),
            scanf("%d", & num);
        }
    }

    if (opcao == 2) {
        soma = 1;

        while (soma != 0) {
            soma = 0;
            fant = 1;
            fatual = 1;

            while (num != 0) {
                res = num % 10; 
                num = num / 10;
                soma = res * fatual + soma;
                fprox = fant + fatual;
                fant = fatual;
                fatual = fprox;
            }

            if (soma != 0) {
                printf("%d\n", soma);
                scanf("%d",& num);
            }
        }
    }

    return 0;
}
