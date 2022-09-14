#ifndef RACIONALES
    #define RACIONALES
    
    struct Rational{
    int p;
    int q;
    };

    typedef struct Rational rational;
    
    rational get_rational(void);
    int gcd(int a, int b);
    void simplify(rational *Q);
    rational rational_sum(rational P, rational Q);
    rational rational_diff(rational P, rational Q);
    rational rational_prod(rational P, rational Q);
    rational rational_div(rational P, rational Q);
    void print_rational(rational Q);
    
#endif
