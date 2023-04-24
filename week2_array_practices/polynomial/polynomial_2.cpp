#include <iostream>
#include <cstring>
#include <cctype>
#include <algorithm>

#define MaxDegree 100
#define MaxTerms 1000
using namespace std;

//================================================================
//  CLASS HEADER
//================================================================
//================
//  TERM
//================
class term
{
    friend class polynomial;

private:
    float coef;
    int exp;
};

//================
//  Polynomial
//================
class polynomial
{
public:
    polynomial();
    polynomial(char _name);
    polynomial Add(polynomial B);

    void init();
    void setPolynomial(const char *poly);
    void Attach(float coeffi, int exp);
    // change poly's coefficient
    void printResult();

    int COMPARE(int a, int b);

private:
    static class term termArray[MaxTerms];
    static int freePos;
    int Start, Finish;
};

//================================================================
//  MAIN DESIGN
//================================================================
int polynomial::freePos = 0;
term polynomial::termArray[MaxTerms];

polynomial::polynomial()
{
}

polynomial::polynomial(char polyId)
{
    char poly[0x400];

    // get a polynomial
    cout << "Enter polynomial " << polyId << " :";
    cin.getline(poly, 0x3ff);

    setPolynomial(poly);
}

void polynomial::setPolynomial(const char *poly)
{
    Start = polynomial::freePos;
    // parse
    bool is_exp = false;
    bool negaitive = false;
    bool coeffi_set = false;

    int len = strlen(poly);
    int coeffi;

    for (int i = 0; i < len || is_exp; i++)
    {

        if (isspace(poly[i]) && !is_exp)
            continue;
        if (poly[i] == 'x')
        { // poly: x
            is_exp = true;
            continue;
        }
        if (poly[i] == '+')
        {
            negaitive = false;
            continue;
        }
        if (poly[i] == '-')
        {
            negaitive = true;
            continue;
        }

        if (!is_exp)
        {
            coeffi = 0;
            while (isdigit(poly[i]))
            {
                coeffi *= 10;
                coeffi += poly[i++] - '0';
                coeffi_set = true;
            }
            if (poly[i] == 0 || poly[i] != 'x')
            { // end or constant
                if (negaitive)
                    coeffi = -coeffi;
                Attach(coeffi, 0);
                coeffi_set = false;
            }
            i--;
        }
        else
        {
            if (!coeffi_set)
                coeffi = 1;
            if (negaitive)
                coeffi = -coeffi;
            int exp = 0;
            if (poly[i] != '^')
                exp = 1;
            else
            {
                i++;
                while (isdigit(poly[i]))
                {
                    exp *= 10;
                    exp += poly[i++] - '0';
                }
                i--;
            }

            Attach(coeffi, exp);

            is_exp = false;
            coeffi_set = false;
        }
    }

    Finish = freePos - 1;
}

polynomial polynomial::Add(polynomial B)
{
    polynomial C;
    int a = Start;
    int b = B.Start;
    C.Start = freePos;
    float c;
    while (a <= Finish && b <= B.Finish)
    {
        switch (COMPARE(termArray[a].exp, termArray[b].exp))
        {
        case 1:
            Attach(termArray[a].coef, termArray[a].exp);
            a++;
            break;
        case 0:
            c = termArray[a].coef + termArray[b].coef;
            if (c)
                Attach(c, termArray[a].exp);
            a++, b++;
            break;
        case -1:
            Attach(termArray[b].coef, termArray[b].exp);
            b++;
            break;
        }
    }

    // add in remaining terms of A(x)
    for (; a <= Finish; a++)
        Attach(termArray[a].coef, termArray[a].exp);
    // add in remaining terms of B(x)
    for (; b <= B.Finish; b++)
        Attach(termArray[b].coef, termArray[b].exp);

    C.Finish = freePos - 1;

    return C;
}

int polynomial::COMPARE(const int a, const int b)
{
    if (a > b)
        return 1;
    else if (a == b)
        return 0;
    return -1;
}

void polynomial::Attach(float coeffi, int exp)
{
    termArray[freePos].coef = coeffi;
    termArray[freePos].exp = exp;
    freePos++;
}

void polynomial::printResult()
{
    for (int i = Start; i <= Finish; i++)
        cout << termArray[i].coef << " " << termArray[i].exp << endl;
}

//================================================================
//  MAIN DRIVER
//================================================================
int main()
{
    polynomial polyA('A');
    polynomial polyB('B');

    polynomial polyC;
    polyC = polyA.Add(polyB);
    polyC.printResult();

    return 0;
}