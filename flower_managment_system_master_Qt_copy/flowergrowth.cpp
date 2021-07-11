#include "flowergrowth.h"
#include "ui_flowergrowth.h"
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
Flowergrowth::Flowergrowth(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Flowergrowth)
{
    ui->setupUi(this);
    QChart * folwerForm =folwergrowthchart();
    ui->graphicsView->setChart(folwerForm);
    setWindowTitle("花卉数量分布图");
}

Flowergrowth::~Flowergrowth()
{
    delete ui;
}


QChart * Flowergrowth::folwergrowthchart(){
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
        series->setName("生长状况 - " + name);

        if(name ==  "康乃馨" ){
            std::vector<std::pair<QString,int>> kax = getFlowerGrowth("康乃馨");
            for(auto item : kax){
                *series << new DrilldownSlice(item.second,  item.first, yearSeries);
            }
            QObject::connect(series, &QPieSeries::clicked, chart, &DrilldownChart::handleSliceClicked);

            *yearSeries << new DrilldownSlice(series->sum(), name, series);
        }
        if(name ==  "百合" ){
            std::vector<std::pair<QString,int>> kax =getFlowerGrowth("百合");
            for(auto item : kax){
                *series << new DrilldownSlice(item.second,  item.first, yearSeries);
            }
            QObject::connect(series, &QPieSeries::clicked, chart, &DrilldownChart::handleSliceClicked);

            *yearSeries << new DrilldownSlice(series->sum(), name, series);
        }
        if(name ==  "水仙" ){
            std::vector<std::pair<QString,int>> kax = getFlowerGrowth("水仙");
            for(auto item : kax){
                *series << new DrilldownSlice(item.second,  item.first, yearSeries);
            }
            QObject::connect(series, &QPieSeries::clicked, chart, &DrilldownChart::handleSliceClicked);

            *yearSeries << new DrilldownSlice(series->sum(), name, series);
        }
        if(name ==  "玫瑰" ){
            std::vector<std::pair<QString,int>> kax = getFlowerGrowth("玫瑰");
            for(auto item : kax){
                *series << new DrilldownSlice(item.second,  item.first, yearSeries);
            }
            QObject::connect(series, &QPieSeries::clicked, chart, &DrilldownChart::handleSliceClicked);

            *yearSeries << new DrilldownSlice(series->sum(), name, series);
        }
        if(name ==  "郁金香" ){
            std::vector<std::pair<QString,int>> kax = getFlowerGrowth("郁金香");
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

std::vector<std::pair<QString,int>>Flowergrowth:: getFlowerGrowth(QString flowerName){
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
    QStringList level  = {"A","B+","B","C+","C","D"};
    for(auto i : level){
        QString tmp = "SELECT sum(quantity) FROM flower_info where type = '" + flowerName + "' and growth = '%1' ;";
        QString selectSql = tmp.arg(i);
        QSqlQuery query;
        query.exec(selectSql);
        if (query.next()){
            int num = query.value(0).toInt();
            //每家公司及对应的数量
            //每中生长状况及对应的数量
            tmpdata.emplace_back(std::make_pair(i,num));
        }
    }
    /*
      for(auto item : tmpdata){
          qDebug()<<item.first<<item.second<<endl;
      }
      */
    tmpdata = flowersort(tmpdata);

    return tmpdata;

}


//从小到大

std::vector<std::pair<QString,int>>Flowergrowth::  flowersort(std::vector<std::pair<QString,int>> vec){
    /*  for(auto item : vec){
        qDebug()<<item.first<<item.second<<endl;
    }
    */
    size_t min;
    for(size_t i = 0;i<vec.size();i++){
        min = i;
        for(size_t j = i+1;j<vec.size();j++){
            if(vec[min].second>vec[j].second){
                min = j;
            }
        }
        if(min != i){
            std::pair<QString,int> tmp = vec[min];
            vec[min] = vec[i];
            vec[i] = tmp;
        }
    }
    return vec;
}
/*
 * void xuanze(int *a, int len) {
    int min;
    for (int i = 0; i < len; i++) {
        min = i;
        for (int j = i + 1; j < len; j++) {
            if (a[min] > a[j])
                min = j;

        }
        if (min != i) {
            swap(&a[min], &a[i]);
        }
    }
}
 *
 * */
