#include "polynomial.h"
#include <iostream>
#include <math.h>


//
// Implementation
//


// Copy constructor
Polynomial::Polynomial(const Polynomial& source)
{
    capacity = source.Capacity();
    terms = source.Terms();
    termArray = new Term[capacity];
    for(int i=0; i<terms; i++){
        termArray[i] = source.GetTerm(i);
    }
}

// Destructor
Polynomial::~Polynomial()
{
    delete[] termArray;
}


Polynomial& Polynomial::operator = (const Polynomial& source)
{
    capacity = source.Capacity();
    terms = source.Terms();
    termArray = new Term[capacity];
    for(int i=0; i<terms; i++){
        termArray[i] = source.GetTerm(i);
    }
}



// Sum of *this and source polynomials
Polynomial Polynomial::operator +(const Polynomial& source)
{
    Polynomial c;
    int a = 0; int b = 0; int aEnd = terms; int bEnd = source.terms;
    Term* A = termArray; Term* B = source.termArray;
    float result;

    while ((a<aEnd)&&(b<bEnd)){
        if (A[a].exp == B[b].exp){
            result = A[a].coef + B[b].coef;
            if (result != 0 && 1.0e-6 <= abs(result)){
                c.CreateTerm(result, A[a].exp);
            }
            a++; b++;
        } else if(A[a].exp < B[b].exp){
            c.CreateTerm(B[b].coef, B[b].exp);
            b++;
        } else{
            c.CreateTerm(A[a].coef, A[a].exp);
            a++;
        }
    }
    for (; a<aEnd; a++){
        c.CreateTerm(A[a].coef,A[a].exp);
    }
    for (; b<bEnd; b++){
        c.CreateTerm(B[b].coef,B[b].exp);
    }

    return c;
}

Polynomial Polynomial::operator - (const Polynomial& source)
{
    Polynomial c;
    int a = 0; int b = 0; int aEnd = terms; int bEnd = source.terms;
    Term* A = termArray; Term* B = source.termArray;
    float result;

    while ((a<aEnd)&&(b<bEnd)){
        if (A[a].exp == B[b].exp){
            result = A[a].coef - B[b].coef;
            if (result != 0 && 1.0e-6 <= abs(result)){
                c.CreateTerm(result, A[a].exp);
            }
            a++; b++;
        } else if(A[a].exp < B[b].exp){
            c.CreateTerm(-B[b].coef, B[b].exp);
            b++;
        } else{
            c.CreateTerm(A[a].coef, A[a].exp);
            a++;
        }
    }
    for (; a<aEnd; a++){
        c.CreateTerm(A[a].coef,A[a].exp);
    }
    for (; b<bEnd; b++){
        c.CreateTerm(-B[b].coef,B[b].exp);
    }

    return c;
}

Polynomial Polynomial::operator * (const Polynomial& source)
{
    Polynomial c;
    int aEnd = terms; int bEnd = source.terms;
    Term* A = termArray; Term* B = source.termArray;

    for (int a=0; a<aEnd; a++){
        Polynomial t = Polynomial();
        for (int b=0; b<bEnd; b++){
            t.CreateTerm(A[a].coef * B[b].coef, A[a].exp + B[b].exp);
        }
        c = c + t;
    }
    return c;
}

bool Polynomial::operator == (const Polynomial& source)
{
    bool ret = true;

    int aEnd = terms; int bEnd = source.terms;
    if (aEnd != bEnd){
        ret = false;
    } else{
        Term* A = termArray; Term* B = source.termArray;
        for (int a=0; a<aEnd; a++){
            if (A[a].exp != B[a].exp || A[a].coef != B[a].coef){
                ret = false;
                break;
            }
        }
    }

    return ret;
}

float Polynomial::Eval(float x)
{
    float ret = 0; int aEnd = terms;

    for (int a=0; a<aEnd; a++){
        ret += termArray[a].coef * (pow(x,termArray[a].exp));
    }

    return ret;
}

// Compute derivative of the current polynomial
Polynomial Polynomial::Derivative()
{
    Polynomial c;
    int aEnd = terms;
    Term* A = termArray;
    for (int a=0; a<aEnd; a++){
        if (A[a].exp != 0){
            c.CreateTerm(A[a].coef * A[a].exp, A[a].exp-1);
        }
    }

    return c;

}

void Polynomial::CreateTerm(const float coef, const int exp)
{
    if (capacity==terms){
        capacity = capacity*2;
        Term* NewTermArray = new Term[capacity];
        for (int i=0; i<terms; i++){
            NewTermArray[i] = termArray[i];
        }
        delete[] termArray;
        termArray = NewTermArray;
    }

    for (int i =0; i<terms; i++){
        if (termArray[i].exp == exp){
            termArray[i].exp = exp;
            termArray[i].coef = coef;
            return;
        }
    }

    int i = terms-1;
    while (0<=i && termArray[i].exp <= exp){
        termArray[i+1] = termArray[i];
        i--;
    }
    termArray[i+1].exp = exp;
    termArray[i+1].coef = coef;
    terms++;
}

