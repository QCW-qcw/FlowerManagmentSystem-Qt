#ifndef SQLDATAREAD_H
#define SQLDATAREAD_H

#include <QMainWindow>
#include<QVariant>
#include <QtCharts>
#include <QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include"flowergrowth.h"
#include"folwernumform.h"
QT_BEGIN_NAMESPACE
namespace Ui { class sqldataread; }
QT_END_NAMESPACE

class sqldataread : public QMainWindow
{
    Q_OBJECT

public:
    sqldataread(QWidget *parent = nullptr);
    ~sqldataread();
    std::vector<std::vector<QString>> gettable(QString tablename);
    std::map<QString, std::vector<std::vector<std::tuple<QVariant::Type, QString, QString>>>> read(const QString& name);

    std::vector<std::vector<std::tuple<QVariant::Type, QString, QString>>> read(const QString& databasename,const QString& tablename);

    //连接数据库查询
    //获取指定表的数据，以二维数组形式返回
    std::vector<std::vector<QString>> readtable(const QString& databasename,const QString& tablename);
    std::vector<std::pair<QString,int>> getnum();
    QChart * mywaterchart();
    std::map<QString,std::vector<int>> getwater();

    QChart * myfeiliaochart();
    std::map<QString,std::vector<int>> getfeiliao();
    QChart * mygrowthchart();
    std::map<QString,std::vector<int>> getgrowth();

    std::pair<QString,std::vector<int>> getFlowerGrowth(QString flowerName);
    QChart * flowerGrowthChart(QString flowerName);



private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::sqldataread *ui;
    QMainWindow window;
     folwernumForm ff;
    Flowergrowth  fg;
};
#endif // SQLDATAREAD_H
