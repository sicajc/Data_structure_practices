# Notes when implementing ComplexNumber class
1. When declaring method class, you must specify the return type.
2. When doing i/o overloading, you must use friend function, otherwise you might accidentally destroy the I/O
3. You should declare the class header and class function implementations seperately.
4. The arithmetic operators should not be within a class function.
5. You must declare constructor and copy constructor to the class header and implement them for their initial value.
6. cin.get(),cin.ignore() can be used to read in string or value in your specified ways.
7. &operator>> and &operator<< are used to read in and output the value or string.
8. const means do not change this variable, this kinds of declaration prevents you from accidentally changing the variable.