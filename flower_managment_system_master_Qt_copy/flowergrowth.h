#ifndef FLOWERGROWTH_H
#define FLOWERGROWTH_H

#include <QWidget>
#include <QtCharts>
#include <QChartView>
#include <QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
namespace Ui {
class Flowergrowth;
}

class Flowergrowth : public QWidget
{
    Q_OBJECT

public:
    explicit Flowergrowth(QWidget *parent = nullptr);
    ~Flowergrowth();
    QChart * folwergrowthchart();
    std::vector<std::pair<QString,int>>Flowergrowth:: getFlowerGrowth(QString flowerName);
    std::vector<std::pair<QString,int>>  flowersort(std::vector<std::pair<QString,int>> vec);

private:
    Ui::Flowergrowth *ui;
};

#endif // FLOWERGROWTH_H
