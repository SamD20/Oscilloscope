#include <iostream>
#include "../external/exprtk.hpp"
#include <QApplication>
#include <QWidget>
#include <QtCharts>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
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
        symbol_table.get_variable("x")->ref() = x;
        y = expression.value();
        series->append(x, y);
        x += (range / numberOfPoints);
    }
    
    return series;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    double x = 0;
    double x_range = 10;
    double y_range = 10;
    
    QLineSeries* series = new QLineSeries();
    QWidget* window = new QWidget();
    window->setWindowTitle("mathMusic");
    window->resize(1000, 700);

    symbol_table<double> symbol_table;
    expression<double> expression;
    parser<double> parser;

    symbol_table.add_variable("x", x);
    expression.register_symbol_table(symbol_table);

    QLineEdit* input = new QLineEdit();
    input->setPlaceholderText("Enter an equation...");

    QObject::connect(input, &QLineEdit::textChanged, [&]
    (const QString& text)
    {
        string equation = text.toStdString();

        if (equation.empty())
        {
            series->clear();
            return;
        }

        expression.register_symbol_table(symbol_table);

        if (!parser.compile(equation, expression))
        {
            series->clear();
            return;
        }

        QLineSeries* newSeries = getPoints(
            x, equation, symbol_table, expression, parser,
            -x_range, x_range
        );

        series->replace(newSeries->points());
        delete newSeries;
    });

    // vector<string> variables;

    // // if (collect_variables(equation, variables))
    // // {
    // //     for (const auto& var : variables)
    // //     {
    // //         if (var != "x")
    // //         {
    // //             symbol_table.add_variable(var, 0.0);
    // //         }
    // //     }
    // // }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);

    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(-x_range, x_range);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(-y_range, y_range);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    QChartView chartView(chart);
    chartView.setRenderHint(QPainter::Antialiasing);
    chartView.resize(800, 700);

    QLabel* equationLabel = new QLabel("y =");

    QHBoxLayout* layout = new QHBoxLayout(window);
    layout->addWidget(equationLabel);
    layout->addWidget(input);
    layout->addWidget(&chartView, 1);

    window->show();

    return app.exec();
}