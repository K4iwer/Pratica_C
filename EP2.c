# include <stdio.h>
# include <math.h>
# include <float.h>

void read_data(double *x0, double *x1, double *x2, double *x3, double *v0, double *v1, double*v2, double *v3, double *m0, double *m1, double *m2, double *m3, double *T_max) {
    scanf ("%lf %lf %lf", x0, v0, m0);
    scanf ("%lf %lf %lf", x1, v1, m1);
    scanf ("%lf %lf %lf", x2, v2, m2);
    scanf ("%lf %lf %lf", x3, v3, m3);
    scanf ("%lf", T_max);
}

double t (double x, double xx, double v, double vv) {
    double dis, vel;                                          /*distância total, velocidade resultante entre as particulas*/

    if (xx < x && vv > v) {
        dis = (x - xx) - 0.1;
        vel = vv - v;

        if (dis == 0 && vel == 0) {
            return HUGE_VAL;
        }

        if (dis < 0) {
            dis *= -1;
        }
    }

    else {
        dis = (xx - x) - 0.1;
        vel = v - vv;

        if (dis == 0 && vel == 0) {
            return HUGE_VAL;
        }

        if (dis < 0) {
            dis *= -1;
        }
    }

    if ((vv > v && xx > x) || ((vv < v) && xx < x)) {
        return HUGE_VAL;
    }

    else {
        return (dis / vel);
    } 
}

double min (double a, double b, double c, int *i) {
    double m;
    m = 0;

    if (a <= b && a <= c) {
        m = a;
        *i = 1;
    }

    if (b < a && b <= c) {
        m = b;
        *i = 2;
    }

    if (c < a && c < b) {
        m = c;
        *i = 3;
    }

    return m;
}

double adv(double *x, double v, double t) {
    double desl;                                  /*deslocamento absoluto*/
    desl = 0;

    if (v != 0 && t != 0) {

        if (v > 0) {
            desl = (v * t);
        }

        else {
            desl = (v * t);
        }

        *x = *x + desl;
    }

    if (desl >= 0) {
        return desl;
    }

    else {
        return desl * (-1);
    }
}

void resolve (double *v, double *vv, double m, double mm) {
    double aux;
    aux = *v;
    *v = ((2 * ((m * (*v)) + (mm * (*vv)))) / (m + mm)) - *v;
    *vv = ((2 * ((m * (aux)) + (mm * (*vv)))) / (m + mm)) - *vv;
}

void print_data (long int c1, long int c2, long int c3, double x0, double x1, double x2, double x3, double v0, double v1, double v2, double v3, double d0, double d1, double d2, double d3) {
    printf ("%ld %ld %ld\n", c1, c2, c3);
    printf ("%f %f %f %f\n", x0, x1, x2, x3);
    printf ("%f %f %f %f\n", v0, v1, v2, v3);
    printf ("%f %f %f %f\n", d0, d1, d2, d3);
}

int main () {
    double x0, x1, x2, x3, v0, v1, v2, v3, m0, m1, m2, m3, d0, d1, d2, d3, T_max, T, te, t1, t2, t3;      /*te = intervalo de tempo até algum evento*/
    long int c1, c2, c3;
    int i, coli;                                                                                          /*coli = boolean q diz se haverao mais colisoes*/
    c1 = c2 = c3 = 0;
    i = 0;
    d0 = d1 = d2 = d3 = 0;
    T = 0.0;
    coli = 1;

    read_data(&x0, &x1, &x2, &x3, &v0, &v1, &v2, &v3, &m0, &m1, &m2, &m3, &T_max);

    while (T < T_max) {
        t1 = t(x0, x1, v0, v1);  
        t2 = t(x1, x2, v1, v2);  
        t3 = t(x2, x3, v2, v3); 
        te = min (t1, t2, t3, &i);

        if (T + te > T_max) {
            i = 0;
        } 
        
        if (te == HUGE_VAL) { 
            coli = 0;
        }

        /*Para quando nao vao haver mais colisoes*/

        if (i == 0) {
            d0 += adv (&x0, v0, (T_max - T));
            d1 += adv (&x1, v1, (T_max - T));
            d2 += adv (&x2, v2, (T_max - T));
            d3 += adv (&x3, v3, (T_max - T));
        }

        /*Ocorrendo colisoes*/

        if (i == 1) {
            d0 += adv (&x0, v0, te);
            d1 += adv (&x1, v1, te);
            d2 += adv (&x2, v2, te);
            d3 += adv (&x3, v3, te);

            resolve (&v0, &v1, m0, m1);

            c1 ++;
        }

        if (i == 2) {
            d0 += adv (&x0, v0, te);
            d1 += adv (&x1, v1, te);
            d2 += adv (&x2, v2, te);
            d3 += adv (&x3, v3, te);

            resolve (&v1, &v2, m1, m2);

            c2 ++;
        }

        if (i == 3) {
            d0 += adv (&x0, v0, te);
            d1 += adv (&x1, v1, te);
            d2 += adv (&x2, v2, te);
            d3 += adv (&x3, v3, te);

            resolve (&v2, &v3, m2, m3);

            c3 ++;
        }

        i = 0;
        T += te;
    }

    printf ("Numero de colisoes por bloco: %ld %ld %ld\n", c1, c2, c3);
    printf ("Numero total de colisoes: %ld\n", c1 + c2 + c3);
    printf ("Colisoes dos dois blocos a direita: %ld\n", c2 + c3);

    printf ("x0 = %9.6f  v0 = %9.6f  d0 = %9.6f\n", x0, v0, d0);
    printf ("x1 = %9.6f  v1 = %9.6f  d1 = %9.6f\n", x1, v1, d1);
    printf ("x2 = %9.6f  v2 = %9.6f  d2 = %9.6f\n", x2, v2, d2);
    printf ("x3 = %9.6f  v3 = %9.6f  d3 = %9.6f\n", x3, v3, d3);

    if (coli == 1) {
        printf ("Ha colisoes remanescentes\n");
    }

    else {
        printf ("Nao ha mais colisoes\n");
    }

    return 0;
}
