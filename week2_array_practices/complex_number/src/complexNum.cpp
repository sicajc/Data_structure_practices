#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
using namespace std;
#define CHARLIMIT 40
#define CMPLXCHAR 'j'
//================================================================
//  CLASS HEADER
//================================================================
class AComplex
{

private:
    // The inner variable.
    double mReal;
    double mImag;
    bool mDivideByZero;

public:
    AComplex();
    AComplex(AComplex &); // copy constructor
    AComplex(double, double);
    AComplex(char *);
    double Real(void);
    double Imag(void);
    double Magnitude(void);
    double Argument(void);         // in degree
    void SetPolar(double, double); // second argument in degree
    void DivideError(void);        // used by divide operator
    bool DivideByZero(void);
    // friend function - can access members but NOT a member
    // BE CAREFUL when choosing a friend!
    // overload insertion operator
    friend ostream &operator<<(ostream &, AComplex &);
};
//===========================
//  ARITHMETICS
//===========================
// arithmetic operators
AComplex operator+(AComplex &, AComplex &);
AComplex operator-(AComplex &, AComplex &);
AComplex operator*(AComplex &, AComplex &);
AComplex operator/(AComplex &, AComplex &);
//================================================================
//  MAIN DESIGN
//================================================================
//===========================
//  CONSTRUCTOR
//===========================
AComplex::AComplex()
{
    //Constructor called automatically when instantiating a class
    mReal = 0.0;
    mImag = 0.0;
    mDivideByZero = false;
}
//===========================
//  COPY CONSTRUCTOR
//===========================
AComplex::AComplex(AComplex &aComplex)
{
    //Copy constructor, copy one element to another
    mReal = aComplex.Real();
    mImag = aComplex.Imag();
    mDivideByZero = false;
}
//===========================
//  REPLACE VALUE
//===========================
AComplex::AComplex(double aReal, double aImag)
{
    mReal = aReal;
    mImag = aImag;
    mDivideByZero = false;
}
//===========================
//  READ COMPLEX VALUE STRING
//===========================
AComplex::AComplex(char *aString)
{
    // default to zero
    mReal = 0.0;
    mImag = 0.0;
    mDivideByZero = false;
    // get length
    int cCount = strlen(aString);
    // create temp storage for both
    char *cArgument1 = new char[cCount];
    char *cArgument2 = new char[cCount];
    int cCount1 = 0, cCount2 = -1;
    // param check flag
    int cSingleOp = 0;
    int cSingleJ = 0;
    bool cNegative = false;
    bool cComplete = true;
    // scan string
    for (int cLoop = 0; cLoop < cCount; cLoop++)
    {
        if (aString[cLoop] == '+')
        {
            cSingleOp++;
            if (cSingleOp > 1)
            {
                cComplete = false;
                break;
            }
        }
        else if (aString[cLoop] == '-')
        {
            cSingleOp++;
            cNegative = true;
            if (cSingleOp > 1)
            {
                cComplete = false;
                break;
            }
        }
        else if (aString[cLoop] == CMPLXCHAR)
        {
            cSingleJ++;
            if (cSingleJ > 1)
            {
                cComplete = false;
                break;
            }
            if (cSingleOp)
                cCount2 = 0;
        }
        else if (aString[cLoop] != ' ')
        {
            if (cCount2 < 0)
            {
                // first param
                cArgument1[cCount1] = aString[cLoop];
                cCount1++;
            }
            else
            {
                // second param
                cArgument2[cCount2] = aString[cLoop];
                cCount2++;
            }
        }
        else
        {
            if (cCount2 < 0 && cCount1 > 0)
            {
                // first param done!
                cArgument1[cCount1] = 0x0;
                cCount1++;
                cCount2 = 0;
            }
            else if (cCount2 > 0)
            {
                // second param done!
                cArgument2[cCount2] = 0x0;
                cCount2++;
                if (!(cSingleOp > 0 && cSingleJ > 0))
                    cComplete = false;
                break;
            }
        }
    }
    if (cComplete)
    {
        if (cCount1 > 0 && cCount2 > 0)
        {
            // in case skipping second termination
            cArgument1[cCount1] = 0x0;
            cArgument2[cCount2] = 0x0;
            mReal = atof(cArgument1);
            mImag = atof(cArgument2);
            if (cNegative)
                mImag = -mImag;
        }
    }
    //Destructor
    delete[] cArgument1;
    delete[] cArgument2;
}
//===========================
//  GET REAL VALUE
//===========================
double AComplex::Real(void)
{
    return mReal;
}
//===========================
//  GET IMAGINARY VALUE
//===========================
double AComplex::Imag(void)
{
    return mImag;
}
//===========================
//  GET MAGNITUDE
//===========================
double AComplex::Magnitude(void)
{
    return sqrt(mReal * mReal + mImag * mImag);
}
double AComplex::Argument(void)
{
    double cTemp = 22.0 / 7;
    if (mImag == 0)
        cTemp = 90;
    else
        cTemp = atan(mImag / mReal) * 180 / cTemp;
    return cTemp;
}
void AComplex::SetPolar(double aMagnitude, double aArgument)
{
    double cTemp = 22.0 / 7;
    aArgument = aArgument * cTemp / 180;
    mReal = aMagnitude * cos(aArgument);
    mImag = aMagnitude * sin(aArgument);
}
void AComplex::DivideError(void)
{
    mDivideByZero = true;
}
bool AComplex::DivideByZero(void)
{
    bool cFlag = mDivideByZero;
    mDivideByZero = false;
    return cFlag;
}
//=====================================================================
//  I/O operator overloading
//=====================================================================
// friend function - NOT a member
// overloaded insertion operator
ostream &operator<<(ostream &aStream, AComplex &aComplex)
{
    // First argument is the I/O address
    aStream << aComplex.mReal;
    aComplex.mImag < 0.0 ? aStream << " - " << CMPLXCHAR << -aComplex.mImag : aStream << " + " << CMPLXCHAR << aComplex.mImag;
    return aStream;
}
// arithmetic functions - NOT member of AComplex
AComplex operator+(AComplex &aComplex1, AComplex &aComplex2)
{
    double cReal = aComplex1.Real() + aComplex2.Real();
    double cImag = aComplex1.Imag() + aComplex2.Imag();
    AComplex cTemp(cReal, cImag);
    return cTemp;
}
// arithmetic functions - NOT member of AComplex
AComplex operator-(AComplex &aComplex1, AComplex &aComplex2)
{
    double cReal = aComplex1.Real() - aComplex2.Real();
    double cImag = aComplex1.Imag() - aComplex2.Imag();
    AComplex cTemp(cReal, cImag);
    return cTemp;
}
// arithmetic functions - NOT member of AComplex
AComplex operator*(AComplex &aComplex1, AComplex &aComplex2)
{
    AComplex cTemp;
    double cMagnitude = aComplex1.Magnitude();
    cMagnitude *= aComplex2.Magnitude();
    double cArgument = aComplex1.Argument();
    cArgument += aComplex2.Argument();
    cTemp.SetPolar(cMagnitude, cArgument);
    return cTemp;
}
// arithmetic functions - NOT member of AComplex
AComplex operator/(AComplex &aComplex1, AComplex &aComplex2)
{
    AComplex cTemp;
    double cMagnitude = aComplex1.Magnitude();
    double cArgument = aComplex1.Argument();
    double cMag2 = aComplex2.Magnitude();
    if (cMag2 == double(0))
    {
        cMagnitude = 0.0;
        cArgument = 0.0;
        cTemp.DivideError();
    }
    else
    {
        cMagnitude /= cMag2;
        cArgument -= aComplex2.Argument();
        cTemp.SetPolar(cMagnitude, cArgument);
    }
    return cTemp;
}


//=====================================================================
//  MAIN DRIVER
//=====================================================================
int main(void)
{
    AComplex cComplex1, cComplex2, cResult;
    cout << endl;
    do
    {
        cout << "------------------" << endl;
        cout << "Complex Arithmetic" << endl;
        cout << "------------------" << endl;
        cout << "1. View First Number" << endl;
        cout << "2. View Second Number" << endl;
        cout << "3. View Previous Result" << endl;
        cout << "4. Addition" << endl;
        cout << "5. Subtraction" << endl;
        cout << "6. Multiplication" << endl;
        cout << "7. Division" << endl;
        cout << "8. Exit" << endl;
        cout << "------------------" << endl;
        cout << "Your choice: ";
        int cSelect;
        cin >> cSelect;
        cout << endl;
        if (cSelect == 1)
        {
            cout << "Your first complex number is: " << cComplex1 << endl;
            cout << "1- Set Value 2-Main Menu" << endl;
            cout << "Your choice: ";
            cin >> cSelect;
            if (cSelect == 1)
            {
                char cBuffer[CHARLIMIT];
                cout << "Enter new value (A+" << CMPLXCHAR << "B): ";
                cin.ignore();
                cin.get(cBuffer, CHARLIMIT, '\n');
                cin.ignore();
                cComplex1 = AComplex(cBuffer);
                cout << "Your first complex number is: " << cComplex1 << endl;
            }
        }
        else if (cSelect == 2)
        {
            cout << "Your second complex number is: " << cComplex2 << endl;
            cout << "1- Set Value 2-Main Menu" << endl;
            cout << "Your choice: ";
            cin >> cSelect;
            if (cSelect == 1)
            {
                char cBuffer[CHARLIMIT];
                cout << "Enter new value (A+" << CMPLXCHAR << "B): ";
                cin.ignore();
                cin.get(cBuffer, CHARLIMIT, '\n');
                cin.ignore();
                cComplex2 = AComplex(cBuffer);
                cout << "Your second complex number is: " << cComplex2 << endl;
            }
        }
        else if (cSelect == 3)
        {
            cout << "Your previous result is: " << cResult << endl;
        }
        else if (cSelect == 4)
        {
            cResult = cComplex1 + cComplex2;
            cout << "Result is: " << cResult << endl;
        }
        else if (cSelect == 5)
        {
            cResult = cComplex1 - cComplex2;
            cout << "Result is: " << cResult << endl;
        }
        else if (cSelect == 6)
        {
            cResult = cComplex1 * cComplex2;
            cout << "Result is: " << cResult << endl;
        }
        else if (cSelect == 7)
        {
            cResult = cComplex1 / cComplex2;
            cout << "Result is: " << cResult << endl;
        }
        else if (cSelect == 8)
        {
            cout << "I'm outta here..." << endl;
            break;
        }
        else
        {
            cout << "Huh? What's that?" << endl;
        }
        cout << endl;
    } while (true);
    return 0;
}
