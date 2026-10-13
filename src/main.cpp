#include <iostream>
#include "../external/exprtk.hpp"
#include <stdio.h>
#include <map>

using namespace std;
using namespace exprtk;

int main()
{
    symbol_table<double> symbol_table;
    expression<double> expression;
    parser<double> parser;

    string equation;
    cout << "y = ";
    cin >> equation;

    vector<string> variables;

    if (collect_variables(equation, variables))
    {
        for (const auto& var : variables)
        {
            if (var != "x")
            {
                double value;
                cout << var << " = ";
                cin >> value;
                symbol_table.add_variable(var, value);
            }
        }
    }
    double x = 0.0;
    symbol_table.add_variable("x", x);
    expression.register_symbol_table(symbol_table);
    parser.compile(equation, expression);
    cout << "y = " << expression.value();

    return 0;
}