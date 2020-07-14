/*
 Project 4 - Part 2 / 9
 Video: Chapter 3 Part 6

 Create a branch named Part2

New/This/Pointers/References conclusion

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 0) in the blank space below, declare/define an empty struct named 'A' on a single Line. 
     on the lines below it, write a struct named 'HeapA' that correctly shows how to own an instance of 'A' 
         on the heap without leaking, without using smart pointers. 
 */

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

 /*
 1) Edit your 3 structs so that they own a heap-allocated primitive type without using smart pointers named 'value'
         IntType should own a heap-allocated int, for example.
 
 2) give it a constructor that takes the appropriate primitive
    this argument will initialize the owned primitive's value.
         i.e. if you're owning an int on the heap, your ctor argument will initialize that heap-allocated int's value.
 
 3) modify those add/subtract/divide/multiply member functions from chapter 2 on it
         a) make them modify the owned numeric type
         b) set them up so they can be chained together.
             i.e.
             DoubleType dt(3.5);
             dt.add(3.0).multiply(-2.5).divide(7.2); //an example of chaining
 
 4) write add/subtract/divide/multiply member functions for each type that take your 3 UDTs
        These are in addition to your member functions that take primitives
        for example, IntType::divide(const DoubleType& dt);
        These functions should return the result of calling the function that takes the primitive.
     
 5) Don't let your heap-allocated owned type leak!
 
 6) replace your main() with the main() below.
    It has some intentional mistakes that you need to fix to match the expected output
    i.e. don't forget to dereference your pointers to get the value they hold.

 7) click the [run] button.  Clear up any errors or warnings as best you can.
 */

/*
your program should generate the following output.  
Use a service like https://www.diffchecker.com/diff to compare your output. 
you'll learn to solve the conversion warnings in the next project part.

18 warnings generated.
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

good to go!



*/

#include <iostream>

struct IntType;
struct DoubleType;

struct FloatType
{
    float* floatPtr;
    FloatType(float fl):floatPtr(new float(fl)){}
    ~FloatType()
    {
        delete floatPtr;
        floatPtr = nullptr;
    }

    FloatType& add( float value );
    FloatType& subtract( float value );
    FloatType& multiply( float value );
    FloatType& divide( float value );

    FloatType& add(DoubleType& dt);
    FloatType& subtract(DoubleType& dt);
    FloatType& multiply(DoubleType& dt);
    FloatType& divide(DoubleType& dt);
    
    FloatType& add(IntType& it);
    FloatType& subtract(IntType& it);
    FloatType& multiply(IntType& it);
    FloatType& divide(IntType& it);

    FloatType& add(FloatType& ft);
    FloatType& subtract(FloatType& ft);
    FloatType& multiply(FloatType& ft);
    FloatType& divide(FloatType& ft);
};

struct DoubleType
{
    double* doublePtr;
    DoubleType(double dbl):doublePtr(new double(dbl)){}
    ~DoubleType()
    {
        delete doublePtr;
        doublePtr = nullptr;
    }
    
    DoubleType& add( double value );
    DoubleType& subtract( double value );
    DoubleType& multiply( double value );
    DoubleType& divide( double value );

    DoubleType& add(DoubleType& dt);
    DoubleType& subtract(DoubleType& dt);
    DoubleType& multiply(DoubleType& dt);
    DoubleType& divide(DoubleType& dt);
    
    DoubleType& add(IntType& it);
    DoubleType& subtract(IntType& it);
    DoubleType& multiply(IntType& it);
    DoubleType& divide(IntType& it);

    DoubleType& add(FloatType& ft);
    DoubleType& subtract(FloatType& ft);
    DoubleType& multiply(FloatType& ft);
    DoubleType& divide(FloatType& ft);
};

struct IntType
{
    int* intPtr;
    IntType(int val):intPtr(new int(val)){}
    ~IntType()
    {
        delete intPtr;
        intPtr = nullptr;
    }
    IntType& add( int value );
    IntType& subtract( int value );
    IntType& multiply( int value );
    IntType& divide( int value );

    IntType& add(DoubleType& dt);
    IntType& subtract(DoubleType& dt);
    IntType& multiply(DoubleType& dt);
    IntType& divide(DoubleType& dt);
    
    IntType& add(IntType& it);
    IntType& subtract(IntType& it);
    IntType& multiply(IntType& it);
    IntType& divide(IntType& it);

    IntType& add(FloatType& ft);
    IntType& subtract(FloatType& ft);
    IntType& multiply(FloatType& ft);
    IntType& divide(FloatType& ft);
};

FloatType& FloatType::add( float value )
{
    *floatPtr += value;
    return *this;
}

FloatType& FloatType::subtract( float value)
{
    *floatPtr -= value;
    return *this;
}

FloatType& FloatType::multiply( float value )
{
    *floatPtr *= value;
    return *this;
}
FloatType& FloatType::divide( float value )
{
    if(value == 0.0f)
    {
        std::cout << "warning, floating point division by zero!" << "\n";
    }
    *floatPtr /= value;
    return *this;
}

FloatType& FloatType::add( DoubleType& dt )
{
    return add(*dt.doublePtr);
}
FloatType& FloatType::subtract( DoubleType& dt )
{
    return subtract(*dt.doublePtr);
}
FloatType& FloatType::multiply( DoubleType& dt )
{
    return multiply(*dt.doublePtr);
}
FloatType& FloatType::divide( DoubleType& dt )
{
    return divide(*dt.doublePtr);
}


FloatType& FloatType::add( IntType& it )
{
    return add(*it.intPtr);
}

FloatType& FloatType::subtract( IntType& it )
{
    return subtract(*it.intPtr);
}

FloatType& FloatType::multiply( IntType& it )
{
    return multiply(*it.intPtr);
}

FloatType& FloatType::divide( IntType& it )
{
    return divide(*it.intPtr);
}


FloatType& FloatType::add( FloatType& ft )
{
    return add(*ft.floatPtr);
}

FloatType& FloatType::subtract( FloatType& ft )
{
    return subtract(*ft.floatPtr);
}

FloatType& FloatType::multiply( FloatType& ft )
{
    return multiply(*ft.floatPtr);
}

FloatType& FloatType::divide( FloatType& ft )
{
    return divide(*ft.floatPtr);
}

//============================================================

DoubleType& DoubleType::add( double value )
{
    *doublePtr += value;
    return *this;
}

DoubleType& DoubleType::subtract( double value )
{
    *doublePtr -= value;
    return *this;
}

DoubleType& DoubleType:: multiply( double value )
{
    *doublePtr *= value;
    return*this;
}

DoubleType& DoubleType::divide( double value)
{
    if(value == 0.0)
    {
        std::cout << "warning, floating point division by zero!" << "\n";
    }
    *doublePtr /= value;
    return *this;
}

DoubleType& DoubleType::add( DoubleType& dt)
{
    return add(*dt.doublePtr);
}

DoubleType& DoubleType::subtract( DoubleType& dt)
{
    return subtract(*dt.doublePtr);
}

DoubleType& DoubleType::multiply( DoubleType& dt)
{
    return multiply(*dt.doublePtr);
}

DoubleType& DoubleType::divide( DoubleType& dt)
{
    return divide(*dt.doublePtr);
}


DoubleType& DoubleType::add( IntType& it)
{
    return add(*it.intPtr);
}

DoubleType& DoubleType::subtract( IntType& it)
{
    return subtract(*it.intPtr);
}

DoubleType& DoubleType::multiply( IntType& it)
{
    return multiply(*it.intPtr);
}

DoubleType& DoubleType::divide( IntType& it)
{
    return divide(*it.intPtr);
}


DoubleType& DoubleType::add( FloatType& ft)
{
    return add(*ft.floatPtr);
}

DoubleType& DoubleType::subtract( FloatType& ft)
{
    return subtract(*ft.floatPtr);
}

DoubleType& DoubleType::multiply( FloatType& ft)
{
    return multiply(*ft.floatPtr);
}

DoubleType& DoubleType::divide( FloatType& ft)
{
    return divide(*ft.floatPtr);
}
//========================================================

IntType& IntType::add( int value )
{
    *intPtr += value;
    return *this;
}

IntType& IntType::subtract( int value )
{
    *intPtr -= value;
    return *this;
}

IntType& IntType::multiply( int value )
{
    *intPtr *= value;
    return *this;
}
IntType& IntType::divide( int value )
{
    if(value == 0)
    {
        std::cout << "error: integer division by zero is an error and will crash the program!" << "\n";
        return *this;
    }
    *intPtr /= value;
    return *this;
}

IntType& IntType::add( DoubleType& dt )
{
    return add(*dt.doublePtr);
}

IntType& IntType::subtract( DoubleType& dt )
{
    return subtract(*dt.doublePtr);
}

IntType& IntType::multiply( DoubleType& dt )
{
    return multiply(*dt.doublePtr);
}

IntType& IntType::divide( DoubleType& dt )
{
    return divide(*dt.doublePtr);
}


IntType& IntType::add( IntType& it )
{
    return add(*it.intPtr);
}

IntType& IntType::subtract( IntType& it )
{
    return subtract(*it.intPtr);
}

IntType& IntType::multiply( IntType& it )
{
    return multiply(*it.intPtr);
}

IntType& IntType::divide( IntType& it )
{
    return divide(*it.intPtr);
}


IntType& IntType::add( FloatType& ft )
{
    return add(*ft.floatPtr);
}

IntType& IntType::subtract( FloatType& ft )
{
    return subtract(*ft.floatPtr);
}

IntType& IntType::multiply( FloatType& ft )
{
    return subtract(*ft.floatPtr);
}

IntType& IntType::divide( FloatType& ft )
{
    return add(*ft.floatPtr);
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


int main()
{   
    //testing instruction 0
    HeapA heapA; 

    //assign heap primitives
    FloatType ft ( 2.0f );
    DoubleType dt ( 2 );
    IntType it ( 2 ) ;

    std::cout << "FloatType add result=" << *ft.add( 2.0f ).floatPtr << std::endl;
    std::cout << "FloatType subtract result=" << *ft.subtract( 2.0f ).floatPtr << std::endl;
    std::cout << "FloatType multiply result=" << *ft.multiply( 2.0f ).floatPtr << std::endl;
    std::cout << "FloatType divide result=" << *ft.divide( 16.0f).floatPtr << std::endl << std::endl;

    std::cout << "DoubleType add result=" << *dt.add(2.0).doublePtr << std::endl;
    std::cout << "DoubleType subtract result=" << *dt.subtract(2.0).doublePtr << std::endl;
    std::cout << "DoubleType multiply result=" << *dt.multiply(2.0).doublePtr << std::endl;
    std::cout << "DoubleType divide result=" << *dt.divide(5.f).doublePtr << std::endl << std::endl;

    std::cout << "IntType add result=" << *it.add(2).intPtr << std::endl;
    std::cout << "IntType subtract result=" << *it.subtract(2).intPtr << std::endl;
    std::cout << "IntType multiply result=" << *it.multiply(2).intPtr << std::endl;
    std::cout << "IntType divide result=" << *it.divide(3).intPtr << std::endl << std::endl;
    std::cout << "Chain calculation = " << *it.multiply(1000).divide(2).subtract(10).add(100).intPtr << std::endl;

        // FloatType object instanciation and method tests
    // --------
    std::cout << "New value of ft = (ft + 3.0f) * 1.5f / 5.0f = " << *ft.add( 3.0f ).multiply(1.5f).divide(5.0f).floatPtr << std::endl;
       
    std::cout << "---------------------\n" << std::endl; 
    
    // DoubleType/IntType object instanciation and method tests
    // --------
    std::cout << "Initial value of dt: " << *dt.doublePtr << std::endl;
    std::cout << "Initial value of it: " << *it.intPtr << std::endl;
    // --------
    std::cout << "Use of function concatenation (mixed type arguments) " << std::endl;
    std::cout << "New value of dt = (dt * it) / 5.0f + ft = " << (*dt.multiply(it).divide(5.0f).add(ft).doublePtr) << std::endl;

    std::cout << "---------------------\n" << std::endl; 
    
    // Intercept division by 0
    // --------
    std::cout << "Intercept division by 0 " << std::endl;
    std::cout << "New value of it = it / 0 = " << *it.divide(0).intPtr << std::endl;
    std::cout << "New value of ft = ft / 0 = " << *ft.divide(0).floatPtr << std::endl;
    std::cout << "New value of dt = dt / 0 = " << *dt.divide(0).doublePtr << std::endl;

    std::cout << "---------------------\n" << std::endl; 

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
