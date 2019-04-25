#include "abstractmethod.h"
#include "QVBoxLayout"
#include "chart.h"
#include "chartview.h"
#include "QValueAxis"
#include "QSplineSeries"
#include "QScatterSeries"

AbstractMethod::AbstractMethod()
{
    m_layout = nullptr;
    m_data = QVector<QPair<float, float>>();
}

AbstractMethod::AbstractMethod(QVBoxLayout *layout, QVector<QPair<float, float>> data)
{
    m_layout = layout;
    m_data = data;
}

AbstractMethod::~AbstractMethod()
{
}

//draws the chart
void AbstractMethod::draw(QVector<QPair<float, float>> calculatedData)
{
    Chart *chart = new Chart();
    chart->setTitle("Интерполяция");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->createDefaultAxes();

    QValueAxis *axisX = new QValueAxis;
    axisX->setTickCount(5);
    chart->addAxis(axisX, Qt::AlignBottom);
    QValueAxis *axisY = new QValueAxis;
    axisY->setTickCount(5);
    chart->addAxis(axisY, Qt::AlignLeft);

    auto *series = new QSplineSeries();
    series->setName("Сплайн");
    QScatterSeries *points = new QScatterSeries();
    points->setName("Узлы интерполяции");

    for (auto &point : m_data)
    {
        points->append(static_cast<qreal>(point.first), static_cast<qreal>(point.second));
    }

    for (auto &value : calculatedData)
    {
        series->append(static_cast<qreal>(value.first), static_cast<qreal>(value.second));
    }

    chart->addSeries(series);
    chart->addSeries(points);
    series->attachAxis(axisX);
    series->attachAxis(axisY);    

    ChartView *chartView = new ChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    m_layout->addWidget(chartView);
}

void AbstractMethod::clearChart()
{
    //not tested yet! should clear layout
    //after this object being deleted
    for (int i = 0; i < m_layout->count();)
    {
        QLayoutItem *item = m_layout->itemAt(i);

        if (item != nullptr)
        {
            delete m_layout->takeAt(i);
        }
        else
        {
            i++;
        }
    }
}
