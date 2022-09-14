/*Management of rational numbers.*/

    #include<stdio.h>

    typedef struct Rational{
    int p;
    int q;
    }rational;

    int gcd(int a, int b)
    {
        if(a%b == 0) return b;
        return gcd(b, a%b);
    }

    void simplify(rational *Q)
    {
        int mcd;

        mcd = gcd(Q->p,Q->q);
        Q->p = Q->p/mcd;
        Q->q = Q->q/mcd;
    }

    rational get_rational(void)
    {
        rational Q;

        printf("p: "); scanf("%d",&Q.p);
        printf("q: "); scanf("%d",&Q.q);
        while(Q.q == 0)
        {
            printf("q must be different to zero.\n");
            printf("q: "); scanf("%d",&Q.q);
        }

        simplify(&Q);
        return Q;
    }

    rational rational_sum(rational P, rational Q)
    {
        P.p = P.p*Q.q+P.q*Q.p;
        P.q = P.q*Q.q;
        simplify(&P);

        return P;        
    }

    rational rational_diff(rational P, rational Q)
    {
        P.p = P.p*Q.q-P.q*Q.p;
        P.q = P.q*Q.q;
        simplify(&P);

        return P;                
    }

    rational rational_prod(rational P, rational Q)
    {
        P.p = P.p*Q.p;
        P.q = P.q*Q.q;
        simplify(&P);

        return P;
    }

    rational rational_div(rational P, rational Q)
    {
        P.p = P.p*Q.q;
        P.q = P.q*Q.p;
        simplify(&P);

        return P;
    }

    void print_rational(rational Q)
    {
        if(Q.p > 0)
        {
            if(Q.q > 0 && Q.q != 1) printf("%d/%d",Q.p,Q.q);
            if(Q.q == 1)    printf("%d",Q.p);
            if(Q.q < 0)     printf("-%d/%d",Q.p,-Q.q);
        }

        if(Q.p == 0) printf("0");

        if(Q.p < 0)
        {
            if(Q.q > 0 && Q.q != 1) printf("%d/%d",Q.p,Q.q);
            if(Q.q == 1)    printf("%d",Q.p);
            if(Q.q < 0)     printf("%d/%d",-Q.p,-Q.q);
        }
    }
