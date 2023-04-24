#include <iostream>
using namespace std;

#define CMPLXCHAR 'j'
#define CHARLIMIT 512

class Complex_number
{
private:
    double real;
    double imaginary;

public:
    // Constructor
    Complex_number();

    // Loading values
    Complex_number(double real, double imaginary);

    // Copy constructor, const is very important when copying.
    // const s.t. it does not change the reference accidently
    Complex_number(const Complex_number &other);

    // Operator overloading
    const Complex_number &operator=(const Complex_number &other);

    // I/O value, note const must be added, otherwise cannot work
    // Add CONST We dont want other methods to destroy the data within.
    double getReal() const { return real; }
    double getImaginary() const { return imaginary; }

    // Add two complex numbers
    Complex_number Add(const Complex_number &other);

    // Add two complex numbers
    Complex_number Mult(const Complex_number &other);

    // friend function - can access members but NOT a member
    // BE CAREFUL when choosing a friend!
    // overload insertion operator
    friend ostream &operator<<(ostream &out, const Complex_number &c);
    friend istream &operator>>(istream &in, Complex_number &c);

    // Multiply two complex numbers
    float norm(float f);
};

//------------------------------------------------------------------------------
// arithmetic operators
Complex_number operator+(Complex_number &complex1, Complex_number &complex2);
Complex_number operator-(Complex_number &complex1, Complex_number &complex2);
Complex_number operator*(Complex_number &complex1, Complex_number &complex2);
Complex_number operator/(Complex_number &complex1, Complex_number &complex2);
//------------------------------------------------------------------------------

Complex_number::Complex_number()
    : real(0), imaginary(0)
{
    // Complex number and set the value as (0,0) when instatiating
}

Complex_number::Complex_number(double real, double imaginary)
    : real(real), imaginary(imaginary)
{
    // Auto generate complex number and puts the number into the variable
}

Complex_number::Complex_number(const Complex_number &other)
{
    // Copy constructor
    cout << "Copied" << endl;
    real = other.real;
    imaginary = other.imaginary;
}

// Operator overloading
const Complex_number &Complex_number::operator=(const Complex_number &other)
{
    real = other.real;
    imaginary = other.imaginary;

    return *this;
}

Complex_number Complex_number::Add(const Complex_number &other)
{
    // Remember to specify the return type.
    Complex_number temp;
    temp.real = other.real + real;
    temp.imaginary = other.imaginary + imaginary;
    return temp;
}

ostream &operator<<(ostream &out, const Complex_number &c)
{
    int img = c.getImaginary();
    if (img >= 0)
    {
        cout << c.getReal() << " + " << img << CMPLXCHAR << endl;
    }
    else
    {
        cout << c.getReal() << " - " << abs(img) << CMPLXCHAR << endl;
    }
}

istream &operator>>(istream &in, Complex_number &c)
{
    cout << "\nReal : ";
    in >> c.real;
    cout << "\nImaginary:";
    in >> c.imaginary;
    cout << "The value you just entered is:"<<endl;
    cout << c;
    return in;
}

Complex_number operator+(Complex_number &complex1, Complex_number &complex2)
{
    double cReal = complex1.getReal() + complex2.getReal();
    double cImag = complex1.getImaginary() + complex2.getImaginary();
    Complex_number cTemp(cReal, cImag);
    return cTemp;
}

// Driver code
int main()
{
    Complex_number c1,c2,c3,c4;
    cin >> c1;
    cin >> c2;

    c1 = c1 + c2;
    c2 = c1 + c1;
    cout << c2;

    return 0;
}