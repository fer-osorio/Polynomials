#include<stdio.h>
#include<stdlib.h>
#include"Racionales.h"

typedef struct Monomial{
  rational Q;
  int degree;
  struct Monomial *next_monomial;  
}monomial;

typedef monomial* ptr_monomial; 

void simplify_pol(ptr_monomial *poly)
{
    ptr_monomial aux;

    while((*poly) != NULL)
    {
        if((*poly)->Q.p == 0)
        {
            aux = *poly;
            *poly = (*poly)->next_monomial;
            free(aux);
        }else   poly = &((*poly)->next_monomial);
    }
}

ptr_monomial new_monomial(int degree, rational Q)
{
    ptr_monomial mono;

    mono = (monomial*)malloc(sizeof(monomial));
    mono->degree = degree;
    mono->Q = Q;
    mono->next_monomial = NULL;

    return mono;    
}

ptr_monomial get_poly(void)
{
    ptr_monomial poly, mon;
    int deg, i;
    
    printf("Degree: "); scanf("%d",&deg);
    while(deg < 0)
    {
        printf("Degree has to be non-negative.\nDegree: ");
        scanf("%d",&deg);
    }

    poly = (monomial*)malloc(sizeof(monomial));
    printf("Q_%d =\n",deg);
    poly->Q = get_rational();
    poly->degree = deg;    
    poly->next_monomial = NULL;

    mon = poly; i = deg-1;
    while(i >= 0)
    {
        mon->next_monomial = (monomial*)malloc(sizeof(monomial));
        printf("Q_%d =\n ",i);
        mon->next_monomial->Q = get_rational();
        mon->next_monomial->degree = i;
        mon->next_monomial->next_monomial = NULL;
        mon = mon->next_monomial;
        i--;
    }
    simplify_pol(&poly); 

    return poly;
}

int print_poly(ptr_monomial P)
{
    if(P == NULL) {printf("0"); return 0;}

    if(P->degree == 0)  print_rational(P->Q);
    if(P->degree == 1)  
    {
        print_rational(P->Q);
        printf("x");
    }
    if(P->degree > 1)
    {
        print_rational(P->Q);
        printf("x^%d",P->degree);
    }
    P = P->next_monomial;

    while(P != NULL)
    {
        if(P->degree == 0)  
        {
            if(P->Q.p < 0) print_rational(P->Q);
            else
            {
                printf("+");
                print_rational(P->Q);
            }
            
        }
        if(P->degree == 1)  
        {
            if(P->Q.p < 0) {print_rational(P->Q); printf("x");}
            else
            {
                printf("+");
                print_rational(P->Q);
                printf("x");
            }
            
        }
        if(P->degree > 1)
        {
            if(P->Q.p < 0) print_rational(P->Q);
            else
            {
                printf("+");
                print_rational(P->Q);
                printf("x^%d",P->degree);
            }
            
        }
        P = P->next_monomial;
    }
    return 0;
}

ptr_monomial copy_poly(ptr_monomial P)
{
    if(P == NULL) return P;

    ptr_monomial Q, Q_0;

    Q = (monomial*)malloc(sizeof(monomial));
    Q->degree = P->degree;
    Q->Q = P->Q;
    Q->next_monomial = NULL;
    Q_0 = Q;

    P = P->next_monomial;
    while(P != NULL)
    {
        Q->next_monomial = (monomial*)malloc(sizeof(monomial));
        Q->next_monomial->degree = P->degree;
        Q->next_monomial->Q = P->Q;
        Q->next_monomial->next_monomial = NULL;
        Q = Q->next_monomial;
        P = P->next_monomial;
    }

    return Q_0;
}

ptr_monomial add_poly(ptr_monomial P_1, ptr_monomial P_2)
{
    if(P_1 == NULL) return P_2;
    if(P_2 == NULL) return P_1;

    int deg_1, deg_2;
    ptr_monomial P, P_0, aux;  

    if(P_1->degree > P_2->degree)   
    {
        P = new_monomial(P_1->degree, P_1->Q);
        P_1 = P_1->next_monomial;
    }else   
        {
            if(P_1->degree == P_2->degree)
            {
                P = new_monomial(P_1->degree,rational_sum(P_1->Q,P_2->Q));
                P_1 = P_1->next_monomial;
                P_2 = P_2->next_monomial;
            }else 
                {
                    P = new_monomial(P_2->degree, P_2->Q);
                    P_2 = P_2->next_monomial;
                }
        }

    P_0 = P;

    while(P_1 != NULL && P_2 != NULL)
    {
       if(P_1->degree > P_2->degree)   
        {
            P->next_monomial = new_monomial(P_1->degree, P_1->Q);
            P_1 = P_1->next_monomial;
        }else   
            {
                if(P_1->degree == P_2->degree)
                {
                    P->next_monomial = new_monomial(P_1->degree,rational_sum(P_1->Q,P_2->Q));
                    P_1 = P_1->next_monomial;
                    P_2 = P_2->next_monomial;
                }else 
                    {
                        P->next_monomial = new_monomial(P_2->degree, P_2->Q);
                        P_2 = P_2->next_monomial;
                    }
            }
        P = P->next_monomial;
    }

    if(P_1 == NULL && P_2 == NULL) {simplify_pol(&P_0); return P_0;}
    if(P_1 == NULL)
    {
        while(P_2 != NULL)
        {
            P->next_monomial = new_monomial(P_2->degree, P_2->Q);
            P_2 = P_2->next_monomial;
            P = P->next_monomial;
        }
        simplify_pol(&P_0);
        return P_0;
    }
    if(P_2 == NULL)
    {
        while(P_1 != NULL)
        {
            P->next_monomial = new_monomial(P_1->degree, P_1->Q);
            P_1 = P_1->next_monomial;
            P = P->next_monomial;
        }
        simplify_pol(&P_0);
        return P_0;
    }
}

ptr_monomial diff_poly(ptr_monomial P_1, ptr_monomial P_2)
{
    if(P_2 == NULL) return P_1;

    ptr_monomial aux;  
    aux = P_2;
    while(aux != NULL)
    {
        aux->Q.p = -aux->Q.p;
        aux = aux->next_monomial;
    }
    if(P_1 == NULL) return P_2;

    return add_poly(P_1,P_2);
}

void free_pol(ptr_monomial P)
{
    ptr_monomial P_aux;
    while(P_aux)
    {
        P_aux = P->next_monomial;
        free(P);
        P = P_aux;
    }
}

ptr_monomial prod_poly(ptr_monomial P_1, ptr_monomial P_2)
{
    if(P_1 == NULL || P_2 == NULL) return NULL;

    ptr_monomial P, P_aux, aux;
    P = NULL;

    do
    {
        P_aux = copy_poly(P_1); aux = P_aux;
        while(aux != NULL)
        {
            aux->Q = rational_prod(aux->Q, P_2->Q);
            aux->degree = aux->degree+P_2->degree;
            aux = aux->next_monomial;
        }
        P = add_poly(P,P_aux);
        P_2 = P_2->next_monomial; 
    }while(P_2 != NULL);
  
    return P;
}

int quorem_poly(ptr_monomial P_1, ptr_monomial P_2, ptr_monomial *quotient, ptr_monomial *remainder)
{
    if(P_2 == NULL) return -1;
    if(P_1 == NULL) 
    {
        *quotient = NULL;
        *remainder = NULL;
        return 0;
    }

    if(P_1->degree < P_2->degree)
    {
        *quotient = NULL;
        *remainder = P_2;
        return 0;
    }

    ptr_monomial quo_aux;

    *remainder = copy_poly(P_1);
    *quotient = new_monomial((*remainder)->degree-P_2->degree, rational_div((*remainder)->Q,P_2->Q));
    *remainder = diff_poly(*remainder, prod_poly(*quotient,P_2));
    quo_aux = *quotient;

    while((*remainder)!= NULL &&(*remainder)->degree >= P_2->degree)
    {
        quo_aux->next_monomial = new_monomial((*remainder)->degree-P_2->degree, rational_div((*remainder)->Q,P_2->Q));
        *remainder = diff_poly(*remainder, prod_poly(quo_aux->next_monomial,P_2));
        quo_aux = quo_aux->next_monomial;
    }   
    
    return 0;
}

ptr_monomial gcd_poly(ptr_monomial P, ptr_monomial Q)
{
    ptr_monomial quo, rem;
    quorem_poly(P,Q,&quo,&rem);

    if(rem == NULL) return Q;
    return gcd_poly(Q,rem);
}

ptr_monomial coef_poly(ptr_monomial P, ptr_monomial Q, ptr_monomial u_0, ptr_monomial u_1)
{
    ptr_monomial quo, rem;
    quorem_poly(P,Q,&quo,&rem);

    if(rem == NULL) return u_1;

    ptr_monomial aux = copy_poly(u_1);
    u_1 = diff_poly(u_0,prod_poly(quo,u_1));

    return coef_poly(Q, rem, aux, u_1);
}