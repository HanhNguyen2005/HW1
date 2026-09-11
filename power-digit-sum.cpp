#include <iostream>  // provides cout
#include <string>    // provides string type
#include <stdexcept> // provides exception types
#include <vector>    // provides vector
#include <limits>    // provides maximum limit of data type
#include <cmath>     // provides log
#include <cstddef>   // provides std::size_t

using namespace std;

// power function
unsigned long long int power(unsigned int a, unsigned int b){ 
    unsigned long long int result = 1;
    for (unsigned int i = 0; i < b; i++){
        result = result * a;   // use multiplication to have a custom power function
    }
    return result;
}

// vector function to extract digits
vector<int> vectorize_digits(unsigned long long n) {
    vector<int> digits;
    if (n == 0)  // when the digit is 0, add it to the front of vector
    {
        digits.insert(digits.begin(), 0);
    }
    while (n > 0)
    {
        int digit = n % 10;                   // extract the last digit
        digits.insert(digits.begin(), digit); // add to the front; shift right
        n /= 10;                              // remove the last digit
    }
    return digits;
}

// sum_vector() function to add digits together
int sum_vector(vector<int> v) {
    int sum = 0;
    for (size_t i = 0; i < v.size(); i++) // use size_t for the index to match the unsigned type returned by size() 
    {
        sum += v[i]; // increment the sum by v[i]
    }
    return sum;
}


// vec_to_string() function to take a vector and return a string
// Got help from Prof. Novak to clarify whether to_string() could be used in this function
string vec_to_string(vector<int> vec){
    string string = "[";
    if (vec.size() == 0)
        {
            return "[]";
        }
    
    for (size_t i = 0; i < vec.size(); i++)    
    {
        if (i == vec.size() - 1)
        { // avoid adding the last comma at the end of the string
            string += to_string(vec[i]); // Reference: https://www.geeksforgeeks.org/cpp/stdto_string-in-cpp/#google_vignette to learn how to use to_string()
        }
        else
        {
            string += to_string(vec[i]) + ", "; 
        }
    }
    string += "]";
    return string;    
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
    for (size_t i = 0; i < input_a.length(); i++)
    {
        if (input_a[i] < '0' || input_a[i] > '9'){
            cout <<"Input a is not an integer!"<< endl;
            return 1;
        }
    }
    
    for (size_t i = 0; i < input_b.length(); i++)
    {
        if (input_b[i] < '0' || input_b[i] > '9'){
            cout <<"Input b is not an integer!"<< endl;
            return 1;
        }
    }

    // Handle too large value
    unsigned long long int a;
    unsigned long long int b;
    try
    {
        a = stoull(input_a); // use stoull to convert string to unsigned long long
        b = stoull(input_b); 
        
    }
    catch(const std::out_of_range&)
    {
        cout <<"Value too large!"<< endl;
        return 1;
    }
    
    if (a > numeric_limits<unsigned int>::max() || b > numeric_limits<unsigned int>::max()) 
    {
        cout <<"Value too large!"<< endl;
        return 1;
    }

    // Got help from Prof. Novak on where to place the overflow-checking code for Task 2
    // Handle overflow by computing b*log(a)
    if (a > 0 && b*log10(a) >= 64*log10(2)) { // need a > 0 because log10(0) is undefined
        cout <<"a^b will cause overflow."<< endl;
        return 1;
    }
    

    // Call power() function:
    unsigned long long int n = power(a, b);
    cout << a << '^' << b << " = " << n << endl; // Got help from ChatGPT on how to format cout in C++
    
    vector<int> digits = vectorize_digits(n);
    int sum = sum_vector(digits);

    cout << "Sum of digits: " << sum << endl;

    //Test case 1: try the vectorize_digits():
    //vector<int> try_digits1 = vectorize_digits(1602);
    //cout << "vectorize_digits(1602): " << vec_to_string(try_digits1) << endl;
    //vector<int> try_digits2 = vectorize_digits(0);
    //cout << "vectorize_digits(0): " << vec_to_string(try_digits2) << endl;


    //Test case 2: try the vec_to_string()
    //string string1 = vec_to_string({}); // vector size = 0
    //cout << "String: " << string1 << endl;
    //string string2 = vec_to_string(digits);
    //cout << "String: " << string2 << endl;

    return 0;

}