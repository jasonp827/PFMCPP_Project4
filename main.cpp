/*
 Project 4 - Part 3 / 9
 Video: Chapter 4 Part 3 
 Casting

 Create a branch named Part3
 
 do not remove anything from main().  you'll be revising your main() to work with these new code changes.
 
    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.

 1) remove your functions that accepted a User-Defined Type
 
 2) remove any getValue() functions if you added them
 
 3) move all of your add/subtract/multiply/divide implementations out of the class.
  
 4) add user-defined conversion functions that convert to the numeric type your object holds.
        i.e. if your type holds an int, you'll need an operator int() function.
 
 5) make your member variable private.
         this conversion function should be the ONLY WAY to access the held value.
         use the proper casting technique to invoke this conversion function
 
 6) clean up any forward declaration that you might have.
 
 7) make sure it compiles & runs without errors.
 
 8) use your knowledge of casting to remove any conversion warnings. 

 9) insert 'part3();' before the 'good to go' at the end of your main(); 
        move this part3 function to before main()

 10) click the [run] button.  Clear up any errors or warnings as best you can.

 */
#include <iostream>

/*
your program should generate the following output EXACTLY.
This includes the warnings.
The output should have zero warnings.
Use a service like https://www.diffchecker.com/diff to compare your output. 

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

The result of FloatType^4 divided by IntType is: 26.9136
The result of DoubleType times 3 plus IntType is : 67.3
The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: 711
An operation followed by attempts to divide by 0, which are ignored and warns user: 
error: integer division by zero is an error and will crash the program!
error: integer division by zero is an error and will crash the program!
error: integer division by zero is an error and will crash the program!
505521
FloatType x IntType  =  13143546
(IntType + DoubleType + FloatType) x 24 = 315447336
good to go!

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

#include <iostream>

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

    operator float(){return *floatPtr;}

    FloatType& add( float value );
    FloatType& subtract( float value );
    FloatType& multiply( float value );
    FloatType& divide( float value );

private:
    float* floatPtr;
};

struct DoubleType
{
    DoubleType(double dbl):doublePtr(new double(dbl)){}
    ~DoubleType()
    {
        delete doublePtr;
        doublePtr = nullptr;
    }
    operator double(){return *doublePtr;}

    DoubleType& add( double value );
    DoubleType& subtract( double value );
    DoubleType& multiply( double value );
    DoubleType& divide( double value );

private:
   double* doublePtr;
};

struct IntType
{
    IntType(int val):intPtr(new int(val)){}
    ~IntType()
    {
        delete intPtr;
        intPtr = nullptr;
    }

    operator int(){return *intPtr;}

    IntType& add( int value );
    IntType& subtract( int value );
    IntType& multiply( int value );
    IntType& divide( int value );

private:
    int* intPtr;
};

//====================================================

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
        std::cout << "warning: floating point division by zero!" << "\n";
    }
    *floatPtr /= value;
    return *this;
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
        std::cout << "warning: floating point division by zero!" << "\n";
    }
    *doublePtr /= value;
    return *this;
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

    std::cout << "The result of FloatType^4 divided by IntType is: " << ft.multiply( static_cast<float>(ft) ).multiply( static_cast<float>(ft) ).divide( static_cast<float>(it) ) << std::endl;
    std::cout << "The result of DoubleType times 3 plus IntType is : " << dt.multiply( static_cast<double>(3) ).add( static_cast<double>(it) ) << std::endl;
    std::cout << "The result of IntType divided by 3.14 multiplied by DoubleType minus FloatType is: " << it.divide( static_cast<int>(pi) ).multiply( static_cast<int>(dt) ).subtract( static_cast<int>(ft) ) << std::endl;
    std::cout << "An operation followed by attempts to divide by 0, which are ignored and warns user: " << std::endl;
    std::cout << it.multiply(static_cast<int>(it)).divide(static_cast<int>(0)).divide(static_cast<int>(0.0f)).divide(0.0) << std::endl;
    
    std::cout << "FloatType x IntType  =  " << it.multiply( static_cast<int>(ft) ) << std::endl;
    std::cout << "(IntType + DoubleType + FloatType) x 24 = " << it.add( static_cast<int>(dt) ).add( static_cast<int>(ft) ).multiply( static_cast<int>(24) ) << std::endl;
}

int main()
{   
    //testing instruction 0
    HeapA heapA; 

    //assign heap primitives
    FloatType ft ( 2.0f );
    DoubleType dt ( 2 );
    IntType it ( 2 ) ;

    std::cout << "FloatType add result=" << ft.add( 2.0f ) << std::endl;
    std::cout << "FloatType subtract result=" << ft.subtract( 2.0f ) << std::endl;
    std::cout << "FloatType multiply result=" << ft.multiply( 2.0f )<< std::endl;
    std::cout << "FloatType divide result=" << ft.divide( 16.0f) << std::endl << std::endl;

    std::cout << "DoubleType add result=" << dt.add(2.0) << std::endl;
    std::cout << "DoubleType subtract result=" << dt.subtract(2.0) << std::endl;
    std::cout << "DoubleType multiply result=" << dt.multiply(2.0) << std::endl;
    std::cout << "DoubleType divide result=" << dt.divide(static_cast<double>(5.0f)) << std::endl << std::endl;

    std::cout << "IntType add result=" << it.add(2) << std::endl;
    std::cout << "IntType subtract result=" << it.subtract(2) << std::endl;
    std::cout << "IntType multiply result=" << it.multiply(2) << std::endl;
    std::cout << "IntType divide result=" << it.divide(3) << std::endl << std::endl;
    std::cout << "Chain calculation = " << it.multiply(1000).divide(2).subtract(10).add(100) << std::endl;

        // FloatType object instanciation and method tests
    // --------
    std::cout << "New value of ft = (ft + 3.0f) * 1.5f / 5.0f = " << ft.add( 3.0f ).multiply(1.5f).divide(5.0f) << std::endl;
       
    std::cout << "---------------------\n" << std::endl; 
    
    // DoubleType/IntType object instanciation and method tests
    // --------
    std::cout << "Initial value of dt: " << dt << std::endl;
    std::cout << "Initial value of it: " << it << std::endl;
    // --------
    std::cout << "Use of function concatenation (mixed type arguments) " << std::endl;
    std::cout << "New value of dt = (dt * it) / 5.0f + ft = " << (dt.multiply(static_cast<double>(it)).divide(static_cast<double>(5.0f)).add(static_cast<double>(ft))) << std::endl;

    std::cout << "---------------------\n" << std::endl; 
    
    // Intercept division by 0
    // --------
    std::cout << "Intercept division by 0 " << std::endl;
    std::cout << "New value of it = it / 0 = " << it.divide(static_cast<int>(0)) << std::endl;
    std::cout << "New value of ft = ft / 0 = " << ft.divide(static_cast<float>(0)) << std::endl;
    std::cout << "New value of dt = dt / 0 = " << dt.divide(static_cast<double>(0)) << std::endl;

    std::cout << "---------------------\n" << std::endl; 
    part3();
    
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
