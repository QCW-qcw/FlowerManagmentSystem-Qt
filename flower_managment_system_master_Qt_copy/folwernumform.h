#ifndef FOLWERNUMFORM_H
#define FOLWERNUMFORM_H

#include <QWidget>
#include <QtCharts>
#include <QChartView>
#include <QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
namespace Ui {
class folwernumForm;
}

class folwernumForm : public QWidget
{
    Q_OBJECT

public:
    explicit folwernumForm(QWidget *parent = nullptr);
    ~folwernumForm();
    QChart * folwernumchart();

   std::vector<std::pair<QString,int>> getFlowerNum(QString flowerName);
private:
    Ui::folwernumForm *ui;
};

#endif // FOLWERNUMFORM_H
