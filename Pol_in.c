/*Operating polynomial with rationals coeficients.*/

#include<stdio.h>
#include<stdlib.h>
#include"Racionales.h"
#include"Pol_Rac.h"

int main(int argc, char const *argv[])
{
    ptr_monomial P, Q, R, quotient, remainder, S; 
    rational I;
    I.p = 1; I.q = 1;
    int election;

    printf("Operating with polynomials.\n1. Addition\n2. Subtraction\n3. Product\n4. Quotient and remainder\n5. Greates common divisor\n6. Linear combination for gcd\n");
    scanf("%d",&election);

    printf("P = \n"); P = get_poly();
    printf("Q = \n"); Q = get_poly();

    switch (election)
    {
        case 1:
            R = add_poly(P,Q);
            break;
        case 2:
            R = diff_poly(P,Q);
            break;
        case 3:
            R = prod_poly(P,Q);
            break;
        case 4:
            quorem_poly(P, Q, &quotient, &remainder);
            printf("Quotient = "); print_poly(quotient);
            printf("\n");
            printf("Remainder = "); print_poly(remainder);
            break;
        case 5:
            R = gcd_poly(P,Q);
            break;
        case 6:
            R = coef_poly(P, Q, new_monomial(0,I), NULL);
            S = coef_poly(P, Q, NULL, new_monomial(0,I));
            printf("("); print_poly(R); printf(")"); 
            printf("("); print_poly(P); printf(")");
            printf("+");
            printf("("); print_poly(S); printf(")");  
            printf("("); print_poly(Q); printf(")"); 
            printf(" = ");
            print_poly(add_poly(prod_poly(R,P),prod_poly(S,Q)));
            printf("\n");
            break;
        default: printf("Option not found\n");
    }

    if(election != 4 && election != 6) print_poly(R);
    printf("\n");

    return 0;
}