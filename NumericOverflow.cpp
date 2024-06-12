// NumericOverflows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits
#include <typeinfo>     // typeid
#include <utility>      // std::pair

/// <summary>
/// Template function to abstract away the logic of:
///   start + (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to add each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>A pair with the result and a boolean indicating if overflow occurred</returns>
template <typename T>
std::pair<T, bool> add_numbers(T const& start, T const& increment, unsigned long int const& steps)
{
    T result = start;
    bool overflow = false;

    for (unsigned long int i = 0; i < steps; ++i)
    {
        if (result > std::numeric_limits<T>::max() - increment)
        {
            overflow = true;
            break;
        }
        result += increment;
    }

    return std::make_pair(result, overflow);
}

/// <summary>
/// Template function to abstract away the logic of:
///   start - (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to subtract each step</param>
/// <param "steps">The number of steps to iterate</param>
/// <returns>A pair with the result and a boolean indicating if underflow occurred</returns>
template <typename T>
std::pair<T, bool> subtract_numbers(T const& start, T const& decrement, unsigned long int const& steps)
{
    T result = start;
    bool underflow = false;

    for (unsigned long int i = 0; i < steps; ++i)
    {
        if (result < std::numeric_limits<T>::min() + decrement)
        {
            underflow = true;
            break;
        }
        result -= decrement;
    }

    return std::make_pair(result, underflow);
}

//  NOTE:
//    You will see the unary ('+') operator used in front of the variables in the test_XXX methods.
//    This forces the output to be a number for cases where cout would assume it is a character. 

template <typename T>
void test_overflow()
{
    const unsigned long int steps = 5;
    const T increment = std::numeric_limits<T>::max() / steps;
    const T start = 0;

    std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;

    std::cout << "\tAdding Numbers Without Overflow (" << +start << ", " << +increment << ", " << steps << ") = ";
    std::pair<T, bool> result = add_numbers<T>(start, increment, steps);
    std::cout << +result.first << " (Overflow: " << std::boolalpha << result.second << ")" << std::endl;

    std::cout << "\tAdding Numbers With Overflow (" << +start << ", " << +increment << ", " << (steps + 1) << ") = ";
    result = add_numbers<T>(start, increment, steps + 1);
    std::cout << +result.first << " (Overflow: " << std::boolalpha << result.second << ")" << std::endl;
}

template <typename T>
void test_underflow()
{
    const unsigned long int steps = 5;
    const T decrement = std::numeric_limits<T>::max() / steps;
    const T start = std::numeric_limits<T>::max();

    std::cout << "Underflow Test of Type = " << typeid(T).name() << std::endl;

    std::cout << "\tSubtracting Numbers Without Overflow (" << +start << ", " << +decrement << ", " << steps << ") = ";
    std::pair<T, bool> result = subtract_numbers<T>(start, decrement, steps);
    std::cout << +result.first << " (Underflow: " << std::boolalpha << result.second << ")" << std::endl;

    std::cout << "\tSubtracting Numbers With Overflow (" << +start << ", " << +decrement << ", " << (steps + 1) << ") = ";
    result = subtract_numbers<T>(start, decrement, steps + 1);
    std::cout << +result.first << " (Underflow: " << std::boolalpha << result.second << ")" << std::endl;
}

void do_overflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Overflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primitive types see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_overflow<char>();
    test_overflow<wchar_t>();
    test_overflow<short int>();
    test_overflow<int>();
    test_overflow<long>();
    test_overflow<long long>();

    // unsigned integers
    test_overflow<unsigned char>();
    test_overflow<unsigned short int>();
    test_overflow<unsigned int>();
    test_overflow<unsigned long>();
    test_overflow<unsigned long long>();

    // real numbers
    test_overflow<float>();
    test_overflow<double>();
    test_overflow<long double>();
}

void do_underflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Underflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primitive types see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_underflow<char>();
    test_underflow<wchar_t>();
    test_underflow<short int>();
    test_underflow<int>();
    test_underflow<long>();
    test_underflow<long long>();

    // unsigned integers
    test_underflow<unsigned char>();
    test_underflow<unsigned short int>();
    test_underflow<unsigned int>();
    test_underflow<unsigned long>();
    test_underflow<unsigned long long>();

    // real numbers
    test_underflow<float>();
    test_underflow<double>();
    test_underflow<long double>();
}

/// <summary>
/// Entry point into the application
/// </summary>
/// <returns>0 when complete</returns>
int main()
{
    const std::string star_line = std::string(50, '*');

    std::cout << "Starting Numeric Underflow / Overflow Tests!" << std::endl;

    // run the overflow tests
    do_overflow_tests(star_line);

    // run the underflow tests
    do_underflow_tests(star_line);

    std::cout << std::endl << "All Numeric Underflow / Overflow Tests Complete!" << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu