#include <iostream>
#include "../external/exprtk.hpp"
#include <QApplication>
#include <QWidget>
#include <QtCharts>
#include <stdio.h>
#include <map>

using namespace std;
using namespace exprtk;

QLineSeries* getPoints(double &x, string equation, symbol_table<double> &symbol_table, expression<double> &expression, 
    parser<double> &parser, double min_x, double max_x, int FPS = 30)
{

    x = min_x;
    double y;

    QLineSeries* series = new QLineSeries();
    double range = (max_x - min_x); 
    double numberOfPoints = range * FPS;

    for (double i = 0.0; i <= numberOfPoints; i++)
    {
        y = expression.value();
        series->append(x, y);
        x += (range / numberOfPoints);
    }
    
    return series;
}

int main(int argc, char *argv[])
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

    double x = 0;
    symbol_table.add_variable("x", x);
    expression.register_symbol_table(symbol_table);
    parser.compile(equation, expression);

    QLineSeries* series = getPoints(x, equation, symbol_table, expression, parser, -10, 10);

    QApplication app(argc, argv);
    QWidget window;
    window.setWindowTitle("Oscilloscope");
    window.resize(400, 300);
    window.show();

    return app.exec();
}