#ifndef POL_RAC
    #define POL_RAC
    #include"Racionales.h"

    typedef struct Monomial{
    rational Q;
    int degree;
    struct Monomial *next_monomial;  
    }monomial;

    typedef monomial* ptr_monomial; 

    void simplify_pol(ptr_monomial *poly);
    ptr_monomial new_monomial(int degree, rational Q);
    ptr_monomial get_poly(void);
    int print_poly(ptr_monomial P);
    ptr_monomial copy_poly(ptr_monomial P);
    ptr_monomial add_poly(ptr_monomial P_1, ptr_monomial P_2);
    ptr_monomial diff_poly(ptr_monomial P_1, ptr_monomial P_2);
    void free_pol(ptr_monomial P);
    ptr_monomial prod_poly(ptr_monomial P_1, ptr_monomial P_2);
    int quorem_poly(ptr_monomial P_1, ptr_monomial P_2, ptr_monomial *quotient, ptr_monomial *remainder);
    ptr_monomial gcd_poly(ptr_monomial P, ptr_monomial Q);
    ptr_monomial coef_poly(ptr_monomial P, ptr_monomial Q, ptr_monomial u_0, ptr_monomial u_1);

#endif