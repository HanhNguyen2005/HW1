#include <iostream> // provides cout
#include <string>   // provides string type
#include <stdexcept> // provides exception types
using namespace std;

unsigned int power(unsigned short a, unsigned short b){ // power function
    unsigned int result = 1;
    for (int i = 0; i < b; i++){
        result = result * a;   // use multiplication to have a custom power function
    }
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 3){ // the program needs exactly 2 values
        cout <<"Enter 2 inputs please!"<< endl;
        return 1;
    }

    string input_a = argv[1];
    string input_b = argv[2];
    
    // Handle negative inputs because this program only allow non-negative numbers
    if (input_a[0] == '-' || input_b[0] == '-'){
        cout <<"No negative allowed!"<< endl;
        return 1;
    }

    // Handle non-integer inputs (letters and decimals)
    for (int i = 0; i < input_a.length(); i++)
    {
        if (input_a[i] < '0' || input_a[i] > '9'){
            cout <<"Input a is not an integer!"<< endl;
            return 1;
        }
    }
    
    for (int i = 0; i < input_b.length(); i++)
    {
        if (input_b[i] < '0' || input_b[i] > '9'){
            cout <<"Input b is not an integer!"<< endl;
            return 1;
        }
    }

    // Handle too large value
    long a;
    long b;
    
    // Catch an out-of-range conversion because a value might be bigger than long type
    // Reference: https://stackoverflow.com/questions/11776210/convert-c-string-variable-to-long
    // Got help from this website on how to convert string to long
    try
    {
        a = stol(input_a); // use stol to convert string to long
        b = stol(input_b); 
        
    }
    catch(const std::out_of_range&)
    {
        cout <<"Value too large!"<< endl;
        return 1;
    }
    
    // Reference: https://learn.microsoft.com/en-us/cpp/cpp/data-type-ranges?view=msvc-170
    // This website offers the range of unsigned short
    if (a > 65535 || b > 65535) // range of unsigned short: 0 to 65535
    {
        cout <<"Value too large!"<< endl;
        return 1;
    }
    
    unsigned int n = power(a, b);
    cout << a << '^' << b << " = " << n << endl; // Got help from ChatGPT on how to format cout in C++
    unsigned int remaining_part = n;
    unsigned int sum = 0;

    // Digit sum loop:
    while (remaining_part > 0) {
        unsigned int digit = remaining_part % 10; // % 10 to get the last digit
        sum += digit;
        remaining_part = remaining_part / 10; // to remove the last digit
    }
    cout << "Sum of digits: " << sum << endl;
    return 0;
}