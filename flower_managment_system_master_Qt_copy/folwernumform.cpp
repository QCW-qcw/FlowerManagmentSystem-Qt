#include "folwernumform.h"
#include "ui_folwernumform.h"
#include "drilldownchart.h"
#include "drilldownslice.h"


#include <QtCharts>
#include <QChartView>
#include <QBarSeries>
#include<QPieSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>


#include<QSqlError>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QDebug>
#include<QSqlQuery>
#include<QSqlTableModel>
#include<QTextCodec>
#include<QSqlRecord>
#include<QTextEdit>
#include<QSqlField>
#include <QFileDialog>
#include <QDesktopServices>
#include <QMessageBox>
#include<map>
#include <vector>
#include<global.h>
folwernumForm::folwernumForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::folwernumForm)
{
    ui->setupUi(this);
    QChart * folwerForm =folwernumchart();
    ui->graphicsView->setChart(folwerForm);
    setWindowTitle("花卉数量分布图");

}

folwernumForm::~folwernumForm()
{
    delete ui;
}


QChart * folwernumForm::folwernumchart(){
    DrilldownChart *chart = new DrilldownChart();
    chart->setTheme(QChart::ChartThemeLight);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    QPieSeries *yearSeries = new QPieSeries();
    yearSeries->setName("花卉数量分布图");

    //#`carnation``lily``narcissus``rose``tulip`

    //"康乃馨","百合","水仙","玫瑰","郁金香"
    const QStringList names = {
        "康乃馨","百合","水仙","玫瑰","郁金香"
    };
    //公司加数量

    for (const QString &name : names) {
        QPieSeries *series = new QPieSeries();
        series->setName("需求方 - " + name);

        if(name ==  "康乃馨" ){
            std::vector<std::pair<QString,int>> kax = getFlowerNum(name);
            for(auto item : kax){
                *series << new DrilldownSlice(item.second,  item.first, yearSeries);
            }
            QObject::connect(series, &QPieSeries::clicked, chart, &DrilldownChart::handleSliceClicked);

            *yearSeries << new DrilldownSlice(series->sum(), name, series);
        }
        if(name ==  "百合" ){
            std::vector<std::pair<QString,int>> kax = getFlowerNum(name);
            for(auto item : kax){
                *series << new DrilldownSlice(item.second,  item.first, yearSeries);
            }
            QObject::connect(series, &QPieSeries::clicked, chart, &DrilldownChart::handleSliceClicked);

            *yearSeries << new DrilldownSlice(series->sum(), name, series);
        }
        if(name ==  "水仙" ){
            std::vector<std::pair<QString,int>> kax =getFlowerNum(name);
            for(auto item : kax){
                *series << new DrilldownSlice(item.second,  item.first, yearSeries);
            }
            QObject::connect(series, &QPieSeries::clicked, chart, &DrilldownChart::handleSliceClicked);

            *yearSeries << new DrilldownSlice(series->sum(), name, series);
        }
        if(name ==  "玫瑰" ){
            std::vector<std::pair<QString,int>> kax =getFlowerNum(name);
            for(auto item : kax){
                *series << new DrilldownSlice(item.second,  item.first, yearSeries);
            }
            QObject::connect(series, &QPieSeries::clicked, chart, &DrilldownChart::handleSliceClicked);

            *yearSeries << new DrilldownSlice(series->sum(), name, series);
        }
        if(name ==  "郁金香" ){
            std::vector<std::pair<QString,int>> kax = getFlowerNum(name);
            for(auto item : kax){
                *series << new DrilldownSlice(item.second,  item.first, yearSeries);
            }
            QObject::connect(series, &QPieSeries::clicked, chart, &DrilldownChart::handleSliceClicked);

            *yearSeries << new DrilldownSlice(series->sum(), name, series);
        }
    }

    QObject::connect(yearSeries, &QPieSeries::clicked, chart, &DrilldownChart::handleSliceClicked);

    chart->changeSeries(yearSeries);
    return  chart;

}

std::vector<std::pair<QString,int>> folwernumForm::getFlowerNum(QString flowerName){
    std::vector<std::pair<QString,int>> tmpdata;
    //#`carnation``lily``narcissus``rose``tulip`
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection")){
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else{
        db =QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(Global::sqlIp);
        db.setUserName(Global::sqlUserName);
        db.setPassword(Global::sqlPassWord);
    }
    db.setDatabaseName(Global::dataBaseName);
    //#`carnation``lily``narcissus``rose``tulip`

    db.open();

    QString selectSql = QString("SELECT company,quantity FROM flower_info where type = '" + flowerName + "' order by quantity asc;");
    QSqlQuery query;
    query.exec(selectSql);
    while (query.next()){
        QString conpany = query.value(0).toString();
        int num = query.value(1).toInt();
        tmpdata.emplace_back(std::make_pair(conpany,num));
    }
    /*for(auto item : tmpdata){
          qDebug()<<item.first<<item.second<<endl;
      }*/

    return tmpdata;
}

