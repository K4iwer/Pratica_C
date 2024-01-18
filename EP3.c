# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# define MAX_PIXELS 1000000
# define rand2166() (rand2166f(-1))
# define srand2166(seed) (rand2166f((seed)))
# define AA 16807
# define MM 2147483647

void output_image(int col, int row, int v_max, int image[]);
void read_image(int *col, int *row, int *v_max, int image[]);
void encode(int col, int row, int v_max, int image[], int key);
void decode(int col, int row, int v_max, int image[], int key, int decoded[]);
void decode_in_loco(int col, int row, int v_max, int image[], int key);
void decode_brute_force(int col, int row, int v_max, int image[], int max_key);
double entropy(int v_max, int N, int image[]);
int rand2166f(int seed);

int main(int argc, char *argv[]) {
    int col, row, v_max, max_key;
    int image[MAX_PIXELS];
    int opcao = atoi(argv[1]);
    int key = atoi(argv[2]);
    max_key = key;

    srand2166(key);

    read_image(& col, & row, & v_max, image);
    
    if (opcao == 0) {                                            /*0 = codificar uma imagem*/
        encode(col, row, v_max, image, key);
    }

    if (opcao == 1) {                                            /*1 = decodificar uma imagem com senha*/
        decode_in_loco(col, row, v_max, image, key);
    }

    if (opcao == 2) {                                            /*2 = decodificar por foca bruta, sem senha*/
        decode_brute_force(col, row, v_max, image, max_key);
    }

    output_image(col, row, v_max, image);
    return 0;
}

void read_image(int *col, int *row, int *v_max, int image[]) {
    int k;
    char p2;                                    /*p2 = variavel para descartar o "P2" da leitura*/
    scanf("%c", & p2);
    scanf("%c", & p2);
    scanf("%d", col);
    scanf("%d", row);
    scanf("%d", v_max);

    for (k = 0; k < (*row) * (*col); k ++) {
        scanf("%d", & image[k]);
    }
}

void output_image(int col, int row, int v_max, int image[]) {
    int i, j, k;
    k = 0;
    printf("P2\n");
    printf("%d %d\n", col, row);
    printf("%d\n", v_max);

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%03d ", image[k]);
            k ++;
        }
        j = 0;
        printf("\n");
    }
}

void encode(int col, int row, int v_max, int image[], int key) {
    int i, j, p;
    p = 0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j ++) {
            image[p] = (image[p] + (rand2166() % (v_max + 1))) % (v_max + 1);
            p ++;
        }
    }
}

void decode(int col, int row, int v_max, int image[], int key, int decoded[]) {
    int i, N;
    N = row * col;

    for (i = 0; i < N; i++) {
        decoded[i] = (image[i] - (rand2166() % (v_max + 1)) + (v_max + 1)) % (v_max + 1);
    }
}

void decode_in_loco(int col, int row, int v_max, int image[], int key) {
    decode(col, row, v_max, image, key, image);
}

double entropy(int v_max, int N, int image[]) {
    double HI = 0.0, termo = 0.0;
    int i, j, fi[255];                                         /*fi = quantidade de pixels da imagem iguais a i*/
    i = j = 0; 

    for (j = 0; j <= v_max; j ++) {
        fi[j] = 0;
    }

    for (j = 0; j <= N; j ++) {
        fi[image[j]]++;
    }

    while (i <= v_max) {

        if (fi[i] != 0) {
            termo = ((double)fi[i] / (double)N) * (log((double)N / (double)fi[i]));
        }

        if (fi[i] == 0) {
            termo = 0;
        }

        HI += termo;
        i++;
    }

    return HI;
}

void decode_brute_force(int col, int row, int v_max, int image[], int max_key) {
    int key, i, N, decoded[MAX_PIXELS]; 
    double min_val;                                                          /*min_val = entropia de menor valor*/
    key = 0;
    N = row * col;
    min_val = 10000;

    for (i = 0; i <= max_key; i ++) {

        srand2166(i);

        decode(col, row, v_max, image, i, decoded);

        if (min_val > entropy(v_max, N, decoded)) {
            min_val = entropy(v_max, N, decoded);
            key = i;         
        }
    }

    srand2166(key);

    decode_in_loco(col, row, v_max, image, key);
}

int rand2166f(int seed) {
    static long r;

    if (seed >= 0) {
        r = seed;
        return 0;
    }

    r = (r * AA) % MM;
    return r;
}

