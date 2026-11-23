#include <iostream>
#include "Rational.h"
#include <string>

static string get_valid_string(const string& prompt)
{
    string name;
    bool isValidName;
    do
    {
        isValidName = true;

        cout << prompt;
        getline(cin, name);
        if (name.empty() || name == " ")
        {
            isValidName = false;
            cout << "Input name cannot be empty"<<endl;
        }
    } while (!isValidName);
    return name;
}

// Function to trim leading and trailing spaces
static string trim(const string &str) {
    int start = 0;
    int end = str.size();

    // Remove leading spaces
    while (start < end && std::isspace(static_cast<unsigned char>(str[start]))) {
        start++;
    }

    // Remove trailing spaces
    while (end > start && std::isspace(static_cast<unsigned char>(str[end - 1]))) {
        end--;
    }

    return str.substr(start, end - start);
}
static char get_selected_operation()
{
    bool validOperation = false;
    string operation;
    do
    {
        cout << "Enter the one of the following options to execute on your rational numbers" << endl;
        operation = trim(get_valid_string("[ +, -, *, / ]: "));

        if (operation == "+" || operation == "-" || operation == "*" || operation == "/")
        {
            validOperation = true;
        } else
        {
            cout << "That is not a valid operation. Try again"<<endl;
        }
    } while (!validOperation);
    return operation[0];
}

static Rational preform_operation(Rational& obj1, const Rational& obj2)
{
    switch (get_selected_operation())
    {
        case '+':
        obj1 = obj1 + obj2; break;
        case '-':
        obj1 = obj1 - obj2; break;
        case '*':
        obj1 = obj1 * obj2; break;
        case '/':
        obj1 = obj1 / obj2; break;
    default:
        throw runtime_error("Unknown operation");
    }
    return obj1;
}
Rational get_rational_object()
{
    bool validRational = false;
    do
    {
        string userString = get_valid_string("Enter a number or fraction, Ex '3/7' or '-5/8': ");

        if (Rational::is_valid_number(userString))
        {
            validRational = true;
            return Rational(userString);
        }
        cout << "That is not a valid number. Try again"<<endl;

    } while (!validRational);
}

static int do_operation_demos()
{
    bool validRational = true;
    do
    {
        try
        {
            cout << " ================ Creating a Rational object 1 ================ " << endl;
            Rational obj1 = get_rational_object();

            cout << " ================ Creating a Rational object 2 ================ " << endl;
            Rational obj2 = get_rational_object();

            Rational rationalFinal = preform_operation(obj1, obj2);
            cout << " ================ Rational final object created" << endl;
            cout << rationalFinal << endl;
        } catch (invalid_argument& e)
        {
            validRational = false;
            cout << "[WARN] INVALID CREATION, TRYING AGAIN" << endl;
            cout << "[ERROR] " << e.what() << endl;
        }
    } while (!validRational);

    return 0;
}

int main()
{
   do_operation_demos();

    return 0;
}