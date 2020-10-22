/*
Project 4: Part 9 / 9
 video: Chapter 5 Part 8

Create a branch named Part9

 Rule of 3-5-0 and S.R.P.
 
 DO NOT EDIT YOUR PREVIOUS main(). 
 
 1) add the Leak Detector files from Project5
 
 2) add these macros after the JUCE_LEAK_DETECTOR macro :
 */

#define JUCE_DECLARE_NON_COPYABLE(className) \
            className (const className&) = delete;\
            className& operator= (const className&) = delete;

#define JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(className) \
            JUCE_DECLARE_NON_COPYABLE(className) \
            JUCE_LEAK_DETECTOR(className)

/*
 3) add JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Temporary) to the end of the  Temporary<> struct
 
 4) add JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Numeric) to the end of the Numeric<> struct
 
 if you compile it, you'll see lots of errors about deleted functions.
 
 5) Implement the Rule of 5 on Numeric<> and Temporary<> to fix this.
 
 You should end up with the same program output as Part 8's task if you did it right.
 */

/*
 If you did everything correctly, this is the output you should get:
 
I'm a Temporary<f> object, #0
I'm a Temporary<i> object, #0
I'm a Temporary<d> object, #0
f: -1.89
d: -3.024
i: -9
Point { x: -1.89, y: -9 }
d: 3.024
I'm a Temporary<d> object, #1
I'm a Temporary<d> object, #2
d: 1.49519e+08
Point { x: -2.82591e+08, y: -1.34567e+09 }
I'm a Temporary<f> object, #1
I'm a Temporary<i> object, #1
I'm a Temporary<i> object, #2
I'm a Temporary<i> object, #3
intNum: 5
I'm a Temporary<f> object, #2
f squared: 3.5721
I'm a Temporary<f> object, #3
f cubed: 45.5796
I'm a Temporary<d> object, #3
d squared: 2.2356e+16
I'm a Temporary<d> object, #4
d cubed: 1.11733e+49
I'm a Temporary<i> object, #4
i squared: 81
I'm a Temporary<i> object, #5
i cubed: 531441

Use a service like https://www.diffchecker.com/diff to compare your output. 
*/

#include<iostream>
#include <typeinfo>
template<typename NumericType>
struct Temporary
{
    Temporary(NumericType t) : v(t)
    {
        std::cout << "I'm a Temporary<" << typeid(v).name() << "> object, #"
                  << counter++ << std::endl;
    }
    
    operator NumericType() const { return v; }
    operator NumericType&() { return v; }
private:
    static int counter;
    NumericType v;
};

template<typename NumericType>
int Temporary<NumericType>::counter{0};

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
#include <cmath>
#include <functional>
#include <memory>


template <typename NumericType>
struct Numeric
{
    using Type = Temporary<NumericType>;

    Numeric(Type num) : numberPtr(std::make_unique<Type>(num)){}

    ~Numeric()
    {
        numberPtr = nullptr;
    }

    operator NumericType() const {return *numberPtr;}
    operator NumericType&() {return *numberPtr;}

    template<typename OtherType>
    Numeric& operator += ( const OtherType& o )
    {
        *numberPtr += static_cast<NumericType>(o);
        return *this;
    }

    template<typename OtherType>    
    Numeric& operator -= ( const OtherType& o )
    {
        *numberPtr -= static_cast<NumericType>(o);
        return *this;
    }

    template<typename OtherType>
    Numeric& operator *= ( const OtherType& o )
    {
        *numberPtr *= static_cast<NumericType>(o);
        return *this;
    }

    template<typename ParType>
    Numeric& operator /= ( const ParType& value )
    {
        if constexpr (std::is_same<NumericType, int>::value) 
        {
            if constexpr (std::is_same<ParType, int>::value)
            {
                if (value == 0)
                {
                    std::cout << "error: integer division by zero is an error and will crash the program!" << "\n";
                    return *this;
                }
            }
            else if (value < std::numeric_limits<ParType>::epsilon())
            {
                std::cout << "can't divide integers by zero!\n";
                return *this;
            }
        }
        else if (value < std::numeric_limits<NumericType>::epsilon())
        {
            std::cout << "warning: floating point division by zero!" << std::endl;
        }
        *numberPtr /= static_cast<NumericType>(value);
        return *this;
    }

    template<typename OtherType>
    Numeric& operator= (const OtherType& o)
    {
        *numberPtr = static_cast<NumericType>(o); 
        return *this; 
    } 
    
    operator Type&() const {return *numberPtr;}

    template<typename OtherType>
    Numeric& pow( const OtherType& value )
    {
        *numberPtr = static_cast<Type>( std::pow(*numberPtr, static_cast<NumericType>(value)) );
        return *this;
    }  

    template<typename Callable>
    Numeric& apply( Callable callable )
    {
        callable(numberPtr);
        return *this;
    }

private:
    std::unique_ptr<Type> numberPtr;
};



//================================================

template<typename NumericType>
void myNumericFreeFunct(std::unique_ptr<NumericType>& numberPtr)
{
    *numberPtr +=7;
}

//===========================================

template<typename Typex, typename Typey>
struct Point
{
    Point(const Typex& x_, const Typey& y_) : x(static_cast<float>(x_)), y(static_cast<float>(y_)){}

    ~Point(){}

    template<typename Type>
    Point& multiply(const Type& m)
    {
        return multiply(static_cast<float>(m));
    }

    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }

    void toString(){std::cout << "Point { x: " << x << ", y: " << y <<  " }\n";}
    
private:
    float x{0}, y{0};
};

template<typename Type>
void cube(std::unique_ptr<Type>& value)
{
    auto& v = *value;
    v = v*v*v;
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
    Numeric<float> f(0.1f);
    Numeric<int> i(3);
    Numeric<double> d(4.2);
    
    f += 2.f;
    f -= i;
    f *= d;
    f /= 2.f;
    std::cout << "f: " << f << std::endl;
    
    d += 2.f;
    d -= i;
    d *= f;
    d /= static_cast<double>(2.f);
    std::cout << "d: " << d << std::endl;
    
    i += 2.f; i -= f; i *= d; i /= 2.f;
    std::cout << "i: "<< i << std::endl;
    
    Point p(f, i);
    p.toString();
    
    d *= -1;
    std::cout << "d: " << d << std::endl;
    
    p.multiply(d.pow(f).pow(i));
    std::cout << "d: " << d << std::endl;
    
    p.toString();
    
    Numeric<float> floatNum(4.3f);
    Numeric<int> intNum(2);
    Numeric<int> intNum2(6);
    intNum = 2 + (intNum2 - 4) + static_cast<double>(floatNum) / 2.3;
    std::cout << "intNum: " << intNum << std::endl;
    
    {
        using Type = decltype(f)::Type;
        f.apply([&f](std::unique_ptr<Type>&value) -> decltype(f)&
                {
                    auto& v = *value;
                    v = v * v;
                    return f;
                });
        std::cout << "f squared: " << f << std::endl;
        
        f.apply( cube<Type> );
        std::cout << "f cubed: " << f << std::endl;
    }
    
    {
        using Type = decltype(d)::Type;
        d.apply([&d](std::unique_ptr<Type>&value) -> decltype(d)&
                {
                    auto& v = *value;
                    v = v * v;
                    return d;
                });
        std::cout << "d squared: " << d << std::endl;
        
        d.apply( cube<Type> );
        std::cout << "d cubed: " << d << std::endl;
    }
    
    {
        using Type = decltype(i)::Type;
        i.apply([&i](std::unique_ptr<Type>&value) -> decltype(i)&
                {
                    auto& v = *value;
                    v = v * v;
                    return i;
                });
        std::cout << "i squared: " << i << std::endl;
        
        i.apply( cube<Type> );
        std::cout << "i cubed: " << i << std::endl;
    }
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
