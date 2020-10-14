/*
Project 4 - Part 6 / 9
Video: Chapter 5 Part 3
 
Create a branch named Part6
 
 Lambdas
 
    Do not delete your previous main. you will be adding to it.

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) add two member functions named "apply()" to each of your Heap-Allocated Numeric Type wrappers.
         both apply() functions should work with chaining (return *this)
 
 2) One of the apply() functions should takes a std::function<> object as the function argument.
    the std::function<> object should return *this;
 
 3) the other apply() function should take a function pointer. 
    the function pointer should return void.
 
 4) Make both of the member functions's Callable Function Parameter use your owned object as it's single parameter.
         e.g. if you manage your owned object via std::unique_ptr<T>, you'd use this for your std::function argument:
             std::function< OwnedT&(std::unique_ptr<T>&)>
             
         if you managed your owned object via a raw pointer, you'd use this for your std::function argument:
             std::function<OwnedT&(T&)>    
 
 5) call that Callable Function Parameter in the apply() member function.
         be sure to practice safe std::function usage (make sure it's not a nullptr function being called)
 
 6) copy the part6() function below and paste it after part4()
 7) call part6() after part4() is called at the end of main().

 8) fill in the missing arguments in part6 such that you produce the expected output.

 9) Make your lambda & free function update the value of your held object
 
 
build/run to make sure you don't have any errors
 
 If you need to see an example, look at https://bitbucket.org/MatkatMusic/pfmcpptasks/src/master/Projects/Project4/Part6Example.cpp
 */


/*
your program should generate the following output EXACTLY.
This includes the warnings.
The output should have zero warnings.



FloatType add result=4
FloatType subtract result=2
FloatType multiply result=4
FloatType divide result=0.25

DoubleType add result=4
DoubleType subtract result=2
DoubleType multiply result=4
DoubleType divide result=0.8

IntType add result=4
IntType subtract result=2
IntType multiply result=4
IntType divide result=1

Chain calculation = 590
New value of ft = (ft + 3.0f) * 1.5f / 5.0f = 0.975
---------------------

Initial value of dt: 0.8
Initial value of it: 590
Use of function concatenation (mixed type arguments) 
New value of dt = (dt * it) / 5.0f + ft = 95.375
---------------------

Intercept division by 0 
New value of it = it / 0 = error: integer division by zero is an error and will crash the program!
590
New value of ft = ft / 0 = warning: floating point division by zero!
inf
New value of dt = dt / 0 = warning: floating point division by zero!
inf
---------------------

The result of FloatType^3 divided by IntType is: 26.9136
The result of DoubleType times 3 plus IntType is : 67.3
The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: 711
An operation followed by attempts to divide by 0, which are ignored and warns user: 
error: integer division by zero is an error and will crash the program!
error: integer division by zero is an error and will crash the program!
error: integer division by zero is an error and will crash the program!
505521
FloatType x IntType  =  13143546
(IntType + DoubleType + FloatType) x 24 = 315447336
Power tests with FloatType 
pow(ft1, floatExp) = 2^2 = 4
pow(ft1, itExp) = 4^2 = 16
pow(ft1, ftExp) = 16^2 = 256
pow(ft1, dtExp) = 256^2 = 65536
---------------------

Power tests with DoubleType 
pow(dt1, doubleExp) = 2^2 = 4
pow(dt1, itExp) = 4^2 = 16
pow(dt1, ftExp) = 16^2 = 256
pow(dt1, dtExp) = 256^2 = 65536
---------------------

Power tests with IntType 
pow(it1, intExp) = 2^2 = 4
pow(it1, itExp) = 4^2 = 16
pow(it1, ftExp) = 16^2 = 256
pow(it1, dtExp) = 256^2 = 65536
===============================

Point tests with float argument:
Point { x: 3, y: 6 }
Multiplication factor: 6
Point { x: 18, y: 36 }
---------------------

Point tests with FloatType argument:
Point { x: 3, y: 3 }
Multiplication factor: 3
Point { x: 9, y: 9 }
---------------------

Point tests with DoubleType argument:
Point { x: 3, y: 4 }
Multiplication factor: 4
Point { x: 12, y: 16 }
---------------------

Point tests with IntType argument:
Point { x: 3, y: 4 }
Multiplication factor: 5
Point { x: 15, y: 20 }
---------------------

Calling FloatType::apply() using a lambda (adds 7.0f) and FloatType as return type:
ft3 before: 3
ft3 after: 10
Calling FloatType::apply() using a free function (adds 7.0f) and void as return type:
ft3 before: 10
ft3 after: 17
---------------------

Calling DoubleType::apply() using a lambda (adds 6.0) and DoubleType as return type:
dt3 before: 4
dt3 after: 10
Calling DoubleType::apply() using a free function (adds 6.0) and void as return type:
dt3 before: 10
dt3 after: 16
---------------------

Calling IntType::apply() using a lambda (adds 5) and IntType as return type:
it3 before: 5
it3 after: 10
Calling IntType::apply() using a free function (adds 5) and void as return type:
it3 before: 10
it3 after: 15
---------------------

good to go!

Use a service like https://www.diffchecker.com/diff to compare your output. 
*/

#include <iostream>
#include <cmath>
#include <functional>

struct A{};

struct HeapA
{  
    A* aPtr;
    HeapA() : aPtr(new A()){}
    ~HeapA()
    {
        delete aPtr;
        aPtr = nullptr;
    }
};


struct IntType;
struct DoubleType;

struct FloatType
{
    FloatType(float fl):floatPtr(new float(fl)){}
    ~FloatType()
    {
        delete floatPtr;
        floatPtr = nullptr;
    }

    operator float() const {return *floatPtr;}

    FloatType& operator +=( float value );
    FloatType& operator -=( float value );
    FloatType& operator *=( float value );
    FloatType& operator /=( float value );
    

    FloatType& pow( float value );
    FloatType& pow( const IntType& it );
    FloatType& pow( const FloatType& ft );
    FloatType& pow( const DoubleType& dt );

    FloatType& apply( std::function<FloatType&(float&)> func );

    FloatType& apply( void(*func)(float&) );

private:
    float* floatPtr;
    FloatType& powInternal( float value );
};

struct DoubleType
{
    DoubleType(double dbl):doublePtr(new double(dbl)){}
    ~DoubleType()
    {
        delete doublePtr;
        doublePtr = nullptr;
    }
    operator double() const {return *doublePtr;}

    DoubleType& operator +=( double value );
    DoubleType& operator -=( double value );
    DoubleType& operator *=( double value );
    DoubleType& operator /=( double value );

    DoubleType& pow( double value );
    DoubleType& pow( const IntType& it );
    DoubleType& pow( const FloatType& ft );
    DoubleType& pow( const DoubleType& dt );

    DoubleType& apply( std::function<DoubleType&(double&)> func );
    DoubleType& apply( void(*func)(double&) );

private:
    double* doublePtr;
    DoubleType& powInternal( double value);
};

struct IntType
{
    IntType(int val):intPtr(new int(val)){}
    ~IntType()
    {
        delete intPtr;
        intPtr = nullptr;
    }

    operator int() const{return *intPtr;}

    IntType& operator +=( int value );
    IntType& operator -=( int value );
    IntType& operator *=( int value );
    IntType& operator /=( int value );

    IntType& pow( int value );
    IntType& pow( const IntType& it );
    IntType& pow( const FloatType& ft );
    IntType& pow( const DoubleType& dt );

    IntType& apply( std::function<IntType&(int&)> func );
    IntType& apply( void(*func)(int&) );

private:
    int* intPtr;
    IntType& powInternal( int value );
};

struct Point
{
    Point(const IntType& x_, const IntType& y_) : x(static_cast<float>(x_)), y(static_cast<float>(y_)){}

    Point(const FloatType& x_, const FloatType& y_) : x(static_cast<float>(x_)), y(static_cast<float>(y_)){}

    Point(const DoubleType& x_, const DoubleType& y_) : x(static_cast<float>(x_)), y(static_cast<float>(y_)){}

  
    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }

    Point& multiply(const FloatType& m)
    {
        return multiply(static_cast<float>(m));
    }

    Point& multiply(const DoubleType& m)
    {
        return multiply(static_cast<float>(m));
    }

    Point& multiply(const IntType& m)
    {
        return multiply(static_cast<float>(m));
    }

    void toString(){std::cout << "Point { x: " << x << ", y: " << y <<  " }\n";}
    
private:
    float x{0}, y{0};
};

//====================================================

FloatType& FloatType::operator +=( float value )
{
    *floatPtr += value;
    return *this;
}

FloatType& FloatType::operator -=( float value)
{
    *floatPtr -= value;
    return *this;
}

FloatType& FloatType::operator *=( float value )
{
    *floatPtr *= value;
    return *this;
}
FloatType& FloatType::operator /=( float value )
{
    if(value == 0.0f)
    {
        std::cout << "warning: floating point division by zero!" << "\n";
    }
    *floatPtr /= value;
    return *this;
}

FloatType& FloatType::pow( float value )
{
    return powInternal( value );
}

FloatType& FloatType::pow( const IntType& it )
{
    return powInternal(static_cast<float>(it));
}

FloatType& FloatType::pow( const FloatType& ft )
{
    return powInternal(static_cast<float>(ft));
}

FloatType& FloatType::pow( const DoubleType& dt )
{
    return powInternal(static_cast<float>(dt));
}

FloatType& FloatType::powInternal( float value )
{
    *floatPtr = std::pow(*floatPtr, value);
    return *this;
}

FloatType& FloatType::apply( std::function<FloatType&(float&)> func )
{
    if (func)
    {
        return func(*floatPtr);
    }
    return *this;
}


FloatType& FloatType::apply( void(*func)(float&) )
{
    if (func)
    {
        func(*floatPtr);
    }
    return *this;
}

void myFloatFreeFunct(float& floatPtr)
{
    floatPtr += 7.0f;
}

//============================================================

DoubleType& DoubleType::operator +=( double value )
{
    *doublePtr += value;
    return *this;
}

DoubleType& DoubleType::operator -=( double value )
{
    *doublePtr -= value;
    return *this;
}

DoubleType& DoubleType::operator *=( double value )
{
    *doublePtr *= value;
    return*this;
}

DoubleType& DoubleType::operator /=( double value)
{
    if(value == 0.0)
    {
        std::cout << "warning: floating point division by zero!" << "\n";
    }
    *doublePtr /= value;
    return *this;
}

DoubleType& DoubleType::pow( double value )
{
    return powInternal( value );
}

DoubleType& DoubleType::pow( const IntType& it )
{
    return powInternal(static_cast<double>(it));
}

DoubleType& DoubleType::pow( const FloatType& ft )
{
    return powInternal(static_cast<double>(ft));
}

DoubleType& DoubleType::pow( const DoubleType& dt )
{
    return powInternal(static_cast<double>(dt));
}

DoubleType& DoubleType::powInternal( double value )
{
    *doublePtr = std::pow(*doublePtr, value);
    return *this;
}

DoubleType& DoubleType::apply( std::function<DoubleType&(double&)> func )
{
    if (func)
    {
        return func(*doublePtr);
    }
    return *this;
}


DoubleType& DoubleType::apply( void(*func)(double&) )
{
    if (func)
    {
        func(*doublePtr);
    }
    return *this;
}

void myDoubleFreeFunct(double& doublePtr)
{
    doublePtr += 6.0;
}
//========================================================

IntType& IntType::operator +=( int value )
{
    *intPtr += value;
    return *this;
}

IntType& IntType::operator -=( int value )
{
    *intPtr -= value;
    return *this;
}

IntType& IntType::operator *=( int value )
{
    *intPtr *= value;
    return *this;
}

IntType& IntType::operator /=( int value )
{
    if(value == 0)
    {
        std::cout << "error: integer division by zero is an error and will crash the program!" << "\n";
        return *this;
    }
    *intPtr /= value;
    return *this;
}

IntType& IntType::pow( int value )
{
    return powInternal( value );
}

IntType& IntType::pow( const IntType& it )
{
    return powInternal(static_cast<int>(it));
}

IntType& IntType::pow( const FloatType& ft )
{
    return powInternal(static_cast<int>(ft));
}

IntType& IntType::pow( const DoubleType& dt )
{
    return powInternal(static_cast<int>(dt));
}

IntType& IntType::powInternal( int value )
{
    *intPtr = static_cast<int>(std::pow(*intPtr, value));
    return *this;
}

IntType& IntType::apply( std::function<IntType&(int&)> func )
{
    if (func)
    {
        return func(*intPtr);
    }
    return *this;
}


IntType& IntType::apply( void(*func)(int&) )
{
    if (func)
    {
        func(*intPtr);
    }
    return *this;
}

void myIntFreeFunct(int& intPtr)
{
    intPtr += 5;
}
/*
 MAKE SURE YOU ARE NOT ON THE MASTER BRANCH

 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 If you didn't already: 
    Make a pull request after you make your first commit
    pin the pull request link and this repl.it link to our DM thread in a single message.

 send me a DM to review your pull request when the project is ready for review.

 Wait for my code review.
 */

    void part3()
{
    FloatType ft( 5.5f );
    DoubleType dt( 11.1 );
    IntType it ( 34 );
    DoubleType pi( 3.14 );

    ft *= ft;
    ft *= ft;
    ft /= it;
    std::cout << "The result of FloatType^3 divided by IntType is: " << ft << std::endl;

    dt *= 3;
    dt += it;
    std::cout << "The result of DoubleType times 3 plus IntType is : " << dt << std::endl;

    it /= static_cast<int>(pi);
    it *= static_cast<int>(dt);
    it -= static_cast<int>(ft);
    std::cout << "The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: " << it << std::endl;
    std::cout << "An operation followed by attempts to divide by 0, which are ignored and warns user: " << std::endl;

    it *= it;
    it /= 0;
    it /= 0.0f;
    it /= 0.0;
    std::cout << it << std::endl;
    
    it *= static_cast<int>(ft);
    std::cout << "FloatType x IntType  =  " << it << std::endl;

    it += static_cast<int>(dt);
    it += static_cast<int>(ft);
    it *= 24;
    std::cout << "(IntType + DoubleType + FloatType) x 24 = " << it << std::endl;
}

void part4()
{
    // ------------------------------------------------------------
    //                          Power tests
    // ------------------------------------------------------------
    FloatType ft1(2);
    DoubleType dt1(2);
    IntType it1(2);    
    int floatExp = 2.0f;
    int doubleExp = 2.0;
    int intExp = 2;
    IntType itExp(2);
    FloatType ftExp(2.0f);
    DoubleType dtExp(2.0);
    
    // Power tests with FloatType
    std::cout << "Power tests with FloatType " << std::endl;
    std::cout << "pow(ft1, floatExp) = " << ft1 << "^" << floatExp << " = " << ft1.pow(floatExp)  << std::endl;
    std::cout << "pow(ft1, itExp) = " << ft1 << "^" << itExp << " = " << ft1.pow(itExp)  << std::endl;
    std::cout << "pow(ft1, ftExp) = " << ft1 << "^" << ftExp << " = " << ft1.pow(ftExp)  << std::endl;    
    std::cout << "pow(ft1, dtExp) = " << ft1 << "^" << dtExp << " = " << ft1.pow(dtExp)  << std::endl;    
    std::cout << "---------------------\n" << std::endl;  

    // Power tests with DoubleType
    std::cout << "Power tests with DoubleType " << std::endl;
    std::cout << "pow(dt1, doubleExp) = " << dt1 << "^" << doubleExp << " = " << dt1.pow(intExp)  << std::endl;
    std::cout << "pow(dt1, itExp) = " << dt1 << "^" << itExp << " = " << dt1.pow(itExp)  << std::endl;
    std::cout << "pow(dt1, ftExp) = " << dt1 << "^" << ftExp << " = " << dt1.pow(ftExp)  << std::endl;    
    std::cout << "pow(dt1, dtExp) = " << dt1 << "^" << dtExp << " = " << dt1.pow(dtExp)  << std::endl;    
    std::cout << "---------------------\n" << std::endl;    

    // Power tests with IntType
    std::cout << "Power tests with IntType " << std::endl;
    std::cout << "pow(it1, intExp) = " << it1 << "^" << intExp << " = " << it1.pow(intExp)  << std::endl;
    std::cout << "pow(it1, itExp) = " << it1 << "^" << itExp << " = " << it1.pow(itExp)  << std::endl;
    std::cout << "pow(it1, ftExp) = " << it1 << "^" << ftExp << " = " << it1.pow(ftExp)  << std::endl;    
    std::cout << "pow(it1, dtExp) = " << it1 << "^" << dtExp << " = " << it1.pow(dtExp)  << std::endl;    
    std::cout << "===============================\n" << std::endl; 

    // ------------------------------------------------------------
    //                          Point tests
    // ------------------------------------------------------------
    FloatType ft2(3.0f);
    DoubleType dt2(4.0);
    IntType it2(5);
    float floatMul = 6.0f;

    // Point tests with float
    std::cout << "Point tests with float argument:" << std::endl;
    Point p0(ft2, floatMul);
    p0.toString();   
    std::cout << "Multiplication factor: " << floatMul << std::endl;
    p0.multiply(floatMul); 
    p0.toString();   
    std::cout << "---------------------\n" << std::endl;

    // Point tests with FloatType
    std::cout << "Point tests with FloatType argument:" << std::endl;
    Point p1(ft2, ft2);
    p1.toString();   
    std::cout << "Multiplication factor: " << ft2 << std::endl;
    p1.multiply(ft2); 
    p1.toString();   
    std::cout << "---------------------\n" << std::endl;

    // Point tests with DoubleType
    std::cout << "Point tests with DoubleType argument:" << std::endl;
    Point p2(ft2, static_cast<float>(dt2));
    p2.toString();   
    std::cout << "Multiplication factor: " << dt2 << std::endl;
    p2.multiply(dt2); 
    p2.toString();   
    std::cout << "---------------------\n" << std::endl;

    // Point tests with IntType
    std::cout << "Point tests with IntType argument:" << std::endl;
    Point p3(ft2, static_cast<float>(dt2));
    p3.toString();   
    std::cout << "Multiplication factor: " << it2 << std::endl;
    p3.multiply(it2); 
    p3.toString();   
    std::cout << "---------------------\n" << std::endl;
}

void part6()
{
    FloatType ft3(3.0f);
    DoubleType dt3(4.0);
    IntType it3(5);
    
    std::cout << "Calling FloatType::apply() using a lambda (adds 7.0f) and FloatType as return type:" << std::endl;
    std::cout << "ft3 before: " << ft3 << std::endl;
    ft3.apply( [&ft3](float& f) -> FloatType&
    {
        f += 7.0f;
        return ft3;
    } );

    std::cout << "ft3 after: " << ft3 << std::endl;

    std::cout << "Calling FloatType::apply() using a free function (adds 7.0f) and void as return type:" << std::endl;
    std::cout << "ft3 before: " << ft3 << std::endl;
    ft3.apply(myFloatFreeFunct);
    std::cout << "ft3 after: " << ft3 << std::endl;
    std::cout << "---------------------\n" << std::endl;

    std::cout << "Calling DoubleType::apply() using a lambda (adds 6.0) and DoubleType as return type:" << std::endl;
    std::cout << "dt3 before: " << dt3 << std::endl;
    dt3.apply( [&dt3](double& d)-> DoubleType&
    {
        d += 6.0;
        return dt3;
    } );
    std::cout << "dt3 after: " << dt3 << std::endl;

    std::cout << "Calling DoubleType::apply() using a free function (adds 6.0) and void as return type:" << std::endl;
    std::cout << "dt3 before: " << dt3 << std::endl;
    dt3.apply(myDoubleFreeFunct);
    std::cout << "dt3 after: " << dt3 << std::endl;
    std::cout << "---------------------\n" << std::endl;

    std::cout << "Calling IntType::apply() using a lambda (adds 5) and IntType as return type:" << std::endl;
    std::cout << "it3 before: " << it3 << std::endl;
    it3.apply( [&it3](int& i)->IntType&
    {
        i += 5;
        return it3;
    } );
    std::cout << "it3 after: " << it3 << std::endl;
    std::cout << "Calling IntType::apply() using a free function (adds 5) and void as return type:" << std::endl;
    std::cout << "it3 before: " << it3 << std::endl;
    it3.apply(myIntFreeFunct);
    std::cout << "it3 after: " << it3 << std::endl;
    std::cout << "---------------------\n" << std::endl;    
}

int main()
{   
    //testing instruction 0
    HeapA heapA; 

    //assign heap primitives
    FloatType ft ( 2.0f );
    DoubleType dt ( 2 );
    IntType it ( 2 ) ;
    
    ft += 2.0f;
    std::cout << "FloatType add result=" << ft << std::endl;
    ft -= 2.0f;
    std::cout << "FloatType subtract result=" << ft << std::endl;
    ft *= 2.0f;
    std::cout << "FloatType multiply result=" << ft << std::endl;
    ft /= 16.0f;
    std::cout << "FloatType divide result=" << ft << std::endl << std::endl;

    dt += 2.0;
    std::cout << "DoubleType add result=" << dt << std::endl;
    dt -= 2.0;
    std::cout << "DoubleType subtract result=" << dt << std::endl;
    dt *= 2.0;
    std::cout << "DoubleType multiply result=" << dt << std::endl;
    dt /= (static_cast<double>(5.0f));
    std::cout << "DoubleType divide result=" << dt << std::endl << std::endl;

    std::cout << "IntType add result=" << (it += 2) << std::endl;
    std::cout << "IntType subtract result=" << (it -= 2) << std::endl;
    std::cout << "IntType multiply result=" << (it *= 2) << std::endl;
    std::cout << "IntType divide result=" << (it /= 3) << std::endl << std::endl;

    it *= 1000;
    it /= (2);
    it -= 10;
    it += (100);
    std::cout << "Chain calculation = " << it << std::endl;

        // FloatType object instanciation and method tests
    // --------
    ft += 3.0f;
    ft *= (1.5f);
    ft /= (5.0f);
    std::cout << "New value of ft = (ft + 3.0f) * 1.5f / 5.0f = " << ft << std::endl;
       
    std::cout << "---------------------\n" << std::endl; 
    
    // DoubleType/IntType object instanciation and method tests
    // --------
    std::cout << "Initial value of dt: " << dt << std::endl;
    std::cout << "Initial value of it: " << it << std::endl;
    // --------
    std::cout << "Use of function concatenation (mixed type arguments) " << std::endl;

    dt *= it;
    dt /= static_cast<double>(5.0f);
    dt += static_cast<double>(ft);
    std::cout << "New value of dt = (dt * it) / 5.0f + ft = " << dt << std::endl;

    std::cout << "---------------------\n" << std::endl; 
    
    // Intercept division by 0
    // --------
    std::cout << "Intercept division by 0 " << std::endl;
    std::cout << "New value of it = it / 0 = " << (it /= 0) << std::endl;
    std::cout << "New value of ft = ft / 0 = " << (ft /= 0) << std::endl;
    std::cout << "New value of dt = dt / 0 = " << (dt /= 0) << std::endl;

    std::cout << "---------------------\n" << std::endl; 
    
    
    part3();
    part4();
    part6();
    std::cout << "good to go!\n";

   


    return 0;
}

/*
your program should generate the following output.  
Use a service like https://www.diffchecker.com/diff to compare your output. 
you should have no errors or warnings.


clang++ -std=c++17 -Weverything -Wno-c++98-compat -Wno-missing-prototypes main.cpp && ./a.out
result of ft.add(): 555.556
result of ft.subtract(): -308.644
result of ft.multiply(): 53345.3
result of ft.divide(): 0.285712
result of ft.add(): 4444.56
result of ft.subtract(): 4444.56
result of ft.multiply(): 0
result of ft.divide(): 
warning, floating point division by zero returns 'inf' !
inf
result of db.add(): 555.556
result of db.subtract(): -308.644
result of db.multiply(): 53345.3
result of db.divide(): 0.285712
result of db.add(): 123.456
result of db.subtract(): 123.456
result of db.multiply(): 0
result of db.divide(): 
warning, floating point division by zero returns 'inf' !
inf
result of i.add(): 30
result of i.subtract(): -10
result of i.multiply(): 200
result of i.divide(): 0
result of i.add(): 10
result of i.subtract(): 10
result of i.multiply(): 0
result of i.divide(): error, integer division by zero will crash the program!
returning lhs
10
good to go!
*/
