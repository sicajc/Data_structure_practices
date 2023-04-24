#include <iostream>
#include <cstring>
#include <cctype>
#include <algorithm>

#define MaxDegree 100
using namespace std;

//================================================================
//  CLASS HEADER
//================================================================
// p(x) = a_1 x^e1 + ... + a_n x^en
class polynomial
{
    // objects:                      a set of ordered pairs of <e_i, a_i>
    // where a_i Coefficient and e_i Exponent
    // We assume that Exponent consits of integers >= 0
public:
    polynomial(char polyId);
    // return the polynomial p(x) = 0
    polynomial(const char *poly);
    // return presetting polynomial

    void setPolynomial(const char *poly);

    int operator!();
    // if *this is the zero polynomial, return 1; else return 0;

    float Coef(polynomial poly, int e) const;
    // return the coefficient of e in *this

    int LeadExp(polynomial poly) const;
    // return the largest exponent in *this

    polynomial Add(polynomial poly);
    // return the sum of the polynomials *this and poly

    polynomial Mult(polynomial poly);
    // return the product of polynomials *this and poly

    float Eval(float f);
    // Evaluate the polynomial *this at f and return the result

    int COMPARE(const int a, const int b);
    // 1: bigger 0: equal -1: smaller

    void Attach(polynomial &poly, float coeffi, int exp);
    // change poly's coefficient

    void Remove(polynomial &poly, int exp);
    // remove poly's exp term

    void printResult();

private:
    int degree; // degree <= MaxDegree
    float coef[MaxDegree + 1];
};

//================================================================
//  MAIN DESIGN
//================================================================
polynomial::polynomial(char polyId)
{
    char poly[0x400];

    // get a polynomial
    cout << "Enter polynomial " << polyId << " :";
    cin.getline(poly, 0x3ff);

    setPolynomial(poly);
}

polynomial::polynomial(const char *poly)
{
    setPolynomial(poly);
}

void polynomial::setPolynomial(const char *poly)
{
    // parse
    memset(coef, 0, sizeof(coef)); // Initialize the first sizeof(coef) with 0.
    degree = 0;

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
                coef[0] = coeffi;
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

            coef[exp] = coeffi;
            degree = max(degree, exp);

            is_exp = false;
            coeffi_set = false;
        }
    }
}

int polynomial::operator!()
{
    for (int i = 0; i <= degree; i++)
        if (coef[i] != 0)
            return 0;
    return 1;
}

float polynomial::Coef(polynomial poly, int e) const
{
    return poly.coef[e];
}

int polynomial::LeadExp(polynomial poly) const
{
    return poly.degree;
}

polynomial polynomial::Add(polynomial poly)
{
    //Naive polynomial adds
    polynomial d("0");
    d.degree = max(LeadExp(static_cast<polynomial>(*this)), LeadExp(poly));
    while (!this == 0 && !poly == 0) // in ADT we define operation! which returns 1 if poly is zero, really wierd Uh!
    {
        float sum;
        switch (COMPARE(LeadExp(static_cast<polynomial>(*this)), LeadExp(poly)))
        {
        case 1:
            Attach(d, Coef(static_cast<polynomial>(*this), LeadExp(static_cast<polynomial>(*this))), LeadExp(static_cast<polynomial>(*this)));
            Remove(static_cast<polynomial &>(*this), LeadExp(static_cast<polynomial>(*this)));
            break;
        case 0:
            sum = Coef(static_cast<polynomial>(*this), LeadExp(static_cast<polynomial>(*this))) + Coef(poly, LeadExp(poly));
            if (sum)
                Attach(d, sum, LeadExp(poly));
            Remove(static_cast<polynomial &>(*this), LeadExp(static_cast<polynomial>(*this)));
            Remove(poly, LeadExp(poly));
            break;
        case -1:
            Attach(d, Coef(poly, LeadExp(poly)), LeadExp(poly));
            Remove(poly, LeadExp(poly));
            break;
        }
    }

    return d;
}

int polynomial::COMPARE(const int a, const int b)
{
    if (a > b)
        return 1;
    else if (a == b)
        return 0;
    return -1;
}

void polynomial::Attach(polynomial &poly, float coeffi, int exp)
{
    poly.coef[exp] = coeffi;
}

void polynomial::Remove(polynomial &poly, int exp)
{
    poly.coef[exp] = 0;
    if (exp == poly.degree)
        for (; poly.coef[poly.degree] == 0 && poly.degree != 0; poly.degree--)
            ;
}

void polynomial::printResult()
{
    if (degree == 0)
    {
        cout << coef[0] << endl;
        return;
    }
    if (degree == 1)
    {
        if (coef[1] == 1)
            cout << "x";
        else if (coef[1] == -1)
            cout << "-x";
        else
            cout << coef[1] << "x";
        if (coef[0] > 0)
            cout << " + " << coef[0];
        else if (coef[0] < 0)
            cout << " - " << -coef[0];
        cout << endl;
        return;
    }

    int lowest_term;
    for (int i = 0; i <= degree; i++)
        if (coef[i])
        {
            lowest_term = i;
            break;
        }

    if (coef[degree] == 1)
        cout << "x^" << degree;
    else if (coef[degree] == -1)
        cout << "-x^" << degree;
    else
        cout << coef[degree] << "x^" << degree;

    for (int i = degree - 1; i > lowest_term && i != 1; i--)
        if (coef[i] == 1)
            cout << " + x^" << i;
        else if (coef[i] == -1)
            cout << " - x^" << i;
        else if (coef[i] > 0)
            cout << " + " << coef[i] << "x^" << i;
        else if (coef[i] < 0)
            cout << " - " << -coef[i] << "x^" << i;

    if (coef[1] == 1)
        cout << " + x";
    else if (coef[1] == -1)
        cout << " - x";
    else if (coef[1] > 0)
        cout << " + " << coef[1] << "x";
    else if (coef[1] < 0)
        cout << " - " << coef[1] << "x";

    if (coef[0] > 0)
        cout << " + " << coef[0];
    else if (coef[0] < 0)
        cout << " - " << -coef[0];

    cout << endl;
}

//=====================================================================
//  MAIN DRIVER
//=====================================================================

char rule[] = "**********\n1: add\n2: mult\n3: check if poly is zero\n4: check coeffi with expoential e\n\
5: print polynomial\n6:exit\n***************\nYour choice:";

int main()
{
    polynomial polyA('A');
    polynomial polyB('B');
    polynomial polyD("0");

    int option;
    while (true)
    {
        cout << rule;
        cin >> option;
        switch (option)
        {
        case 1:
            polyD = polyA.Add(polyB);
            break;
        case 2:
            // polyA.Mult(polyB);
            break;
        case 3:
            if (!polyA)
                cout << "Yes\n";
            else
                cout << "No\n";
            break;
        case 4:
            int e;
            cout << "e = ";
            cin >> e;
            // cout << polyA.Coef(e) << endl;
            break;
        case 5:
            char polyId;
            cout << "A or B or D:";
            cin >> polyId;
            switch (polyId)
            {
            case 'A':
                polyA.printResult();
                break;
            case 'B':
                polyB.printResult();
                break;
            case 'D':
                polyD.printResult();
                break;
            default:
                cout << "Nothing" << endl;
                break;
            }
            break;
        case 6:
            return 0;
        default:
            cout << "Nothing done!\n";
            break;
        }
    }

    return 0;
}