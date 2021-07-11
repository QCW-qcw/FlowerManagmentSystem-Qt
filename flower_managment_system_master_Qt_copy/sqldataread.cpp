#include "sqldataread.h"
#include "ui_sqldataread.h"
#include "drilldownchart.h"
#include "drilldownslice.h"

#include <QtWidgets/QMainWindow>
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


#include <QtCharts>
#include <QChartView>
#include <QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include<global.h>
sqldataread::sqldataread(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::sqldataread)
{
    ui->setupUi(this);
    setWindowTitle("生成分析");


}

sqldataread::~sqldataread()
{
    delete ui;
}

//map类型的 --- 传入数据库
//键值对 ：   数据表 和 对应的该表中的数据 （二维数组存储元组）
//                                                                                            ：每一行  每一列的该值
//                                                                                                         vector <vector<  元组类型    >
std::map<QString, std::vector<std::vector<std::tuple<QVariant::Type, QString, QString>>>> sqldataread::read(const QString& name)
{
    std::map<QString, std::vector<std::vector<std::tuple<QVariant::Type, QString, QString>>>> values{};
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection")){
        db = QSqlDatabase::database("qt_sql_default_connection");
        db.setDatabaseName(name);
    }
    else{
        db =QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(Global::sqlIp);
        db.setUserName(Global::sqlUserName);
        db.setPassword(Global::sqlPassWord);
        db.setDatabaseName(name);
    }

    // 打开数据库

    if (!db.open())
    {
        //qDebug() << db.lastError().text();

        return values;
    }

    // 读数据
    for (const auto& tableName : db.tables())
    {
        QString selectSql = QString("select * from %1;").arg(tableName);
        QSqlQuery query{};
        if (!query.exec(selectSql))
        {
            // qDebug() << query.lastError().text();
            continue;
        }

        std::vector<std::vector<std::tuple<QVariant::Type, QString, QString>>> tableDatas;
        while (query.next())
        {
            std::vector<std::tuple<QVariant::Type, QString, QString>> singleResultInfos{}; // 单条数据信息
            for (int i = 0; i < query.record().count(); ++i)
            {
                auto type = query.record().field(i).type();
                auto name = query.record().fieldName(i);
                auto value = query.record().value(i).toString();
                singleResultInfos.emplace_back(std::make_tuple(type, name, value));
            }

            tableDatas.emplace_back(std::move(singleResultInfos));
        }
        values[tableName] = std::move(tableDatas);
    }

    return std::move(values);

}

//读取单张表数据 ---最终版
std::vector<std::vector<QString>>sqldataread:: readtable(const QString& databasename,const QString& tablename){
    std::map<QString, std::vector<std::vector<std::tuple<QVariant::Type, QString, QString>>>> values{};
    std::vector<std::vector<std::tuple<QVariant::Type, QString, QString>>> tableDatas;
    std::vector<std::vector<QString>>tmp;
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection")){
        db = QSqlDatabase::database("qt_sql_default_connection");
        db.setDatabaseName(databasename);
    }
    else{
        db =QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(Global::sqlIp);
        db.setUserName(Global::sqlUserName);
        db.setPassword(Global::sqlPassWord);
        db.setDatabaseName(databasename);
    }

    if (!db.open())
    {
        return tmp;
    }
    for (const auto& tableName : db.tables())
    {
        if(tableName ==tablename){
            QString selectSql = QString("select * from %1;").arg(tableName);
            QSqlQuery query{};
            if (!query.exec(selectSql))
            {
              //  qDebug() << query.lastError().text();
                continue;
            }

            while (query.next())
            {
                std::vector<std::tuple<QVariant::Type, QString, QString>> singleResultInfos{}; // 单条数据信息
                for (int i = 0; i < query.record().count(); ++i)
                {
                    auto type = query.record().field(i).type();
                    auto name = query.record().fieldName(i);
                    auto value = query.record().value(i).toString();
                    singleResultInfos.emplace_back(std::make_tuple(type, name, value));
                }

                tableDatas.emplace_back(std::move(singleResultInfos));
            }
            values[tableName] = std::move(tableDatas);
        }
    }

    std::map<QString, std::vector<std::vector<std::tuple<QVariant::Type, QString, QString>>>>::iterator tmpiter = values.find(tablename);
    /*
      qDebug()<<"数据表个数："<<values.size();
      qDebug()<<"行数："<<tmpiter->second.size();
      qDebug()<<"列数："<<tmpiter->second[0].size();
      */
    int hangshu = tmpiter->second.size();
    int lieshu = tmpiter->second[0].size();
    std:: vector< std:: vector<QString>> table(hangshu+1,std::vector<QString>(lieshu+1));
    table[0][0] = "";

    for( std::map<QString, std::vector<std::vector<std::tuple<QVariant::Type, QString, QString>>>>::iterator it=values.begin();it!=values.end();it++)
    {
        if(it->first == tablename){
            for(size_t i = 0;i<it->second.size();i++){
                table[i][0] = i;
                for(size_t j = 0;j<it->second[i].size();j++){
                    // qDebug()<< i <<std::get<1>(it->second[i][j])<<" "<<std::get<2>(it->second[i][j])<<endl;
                    //                  行                               列名                                          该值
                    table[0][j+1] = std::get<1>(it->second[i][j]);
                    table[int(i)+1][int(j) +1] = std::get<2>(it->second[i][j]);
                }
            }
        }
    }
    return table;

}

//可以提取单张表的数据 ---- 传入参数： 数据库名字 ，数据表名字
std::vector<std::vector<std::tuple<QVariant::Type, QString, QString>>>sqldataread:: read(const QString& databasename,const QString& tablename){
    //    std::map<QString, std::vector<std::vector<std::tuple<QVariant::Type, QString, QString>>>> values{};
    std::vector<std::vector<std::tuple<QVariant::Type, QString, QString>>> tableDatas;

    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection")){
        db = QSqlDatabase::database("qt_sql_default_connection");
        db.setDatabaseName(databasename);
    }
    else{
        db =QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(Global::sqlIp);
        db.setUserName(Global::sqlUserName);
        db.setPassword(Global::sqlPassWord);
        db.setDatabaseName(databasename);
    }

    if (!db.open())
    {

        return tableDatas;
    }

    // 读数据
    for (const auto& tableName : db.tables())
    {
        if(tableName ==tablename){
            QString selectSql = QString("select * from %1;").arg(tableName);
            QSqlQuery query{};
            if (!query.exec(selectSql))
            {
                //qDebug() << query.lastError().text();
                continue;
            }

            while (query.next())
            {
                std::vector<std::tuple<QVariant::Type, QString, QString>> singleResultInfos{}; // 单条数据信息
                for (int i = 0; i < query.record().count(); ++i)
                {
                    auto type = query.record().field(i).type();
                    auto name = query.record().fieldName(i);
                    auto value = query.record().value(i).toString();
                    singleResultInfos.emplace_back(std::make_tuple(type, name, value));
                }

                tableDatas.emplace_back(std::move(singleResultInfos));
            }
        }
    }

    return tableDatas;
}


//设置好数据库以及要读取的数据表名称 ---- 数据表的行数和列数要注意一致
//获取数据表
std::vector<std::vector<QString>>sqldataread:: gettable(QString tablename){
    std::map<QString, std::vector<std::vector<std::tuple<QVariant::Type, QString, QString>>>> tabledata = read(Global::dataBaseName);

    std::map<QString, std::vector<std::vector<std::tuple<QVariant::Type, QString, QString>>>>::iterator tmp = tabledata.find(tablename);

//    qDebug()<<"数据表个数："<<tabledata.size();
//    qDebug()<<"行数："<<tmp->second.size();
//    qDebug()<<"列数："<<tmp->second[0].size();
    int hangshu = tmp->second.size();
    int lieshu = tmp->second[0].size();
    std:: vector< std:: vector<QString>> table(hangshu+1,std::vector<QString>(lieshu+1));
    table[0][0] = "";

    for( std::map<QString, std::vector<std::vector<std::tuple<QVariant::Type, QString, QString>>>>::iterator it=tabledata.begin();it!=tabledata.end();it++)
    {
        if(it->first == tablename){
            for(size_t i = 0;i<it->second.size();i++){
                table[i][0] = i;
                for(size_t j = 0;j<it->second[i].size();j++){
                    // qDebug()<< i <<std::get<1>(it->second[i][j])<<" "<<std::get<2>(it->second[i][j])<<endl;
                    //                  行                               列名                                          该值
                    table[0][j+1] = std::get<1>(it->second[i][j]);
                    table[int(i)+1][int(j) +1] = std::get<2>(it->second[i][j]);
                }
            }
        }
    }
    return table;
}


std::vector<std::pair<QString,int>> sqldataread::getnum(){
    std::vector<std::pair<QString,int>> tmpdata;

    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection")){
        db = QSqlDatabase::database("qt_sql_default_connection");
        db.setDatabaseName(Global::dataBaseName);

    }
    else{
        db =QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(Global::sqlIp);
        db.setUserName(Global::sqlUserName);
        db.setPassword(Global::sqlPassWord);
        db.setDatabaseName(Global::dataBaseName);

    }
    //#`carnation``lily``narcissus``rose``tulip`

    db.open();


    QStringList tablename = {"carnation","lily","narcissus","rose","tulip"};
    for (const auto& tableName : db.tables())
    {
        for(int i = 0;i<tablename.size();i++){

            if(tableName ==tablename[i]){
                QString selectSql = QString("SELECT SUM(quantity) FROM %1;").arg(tableName);
                QSqlQuery query;
                query.exec(selectSql);
                if(query.next()){
                    int num = query.value(0).toInt();
                    tmpdata.emplace_back(std::make_pair(tableName,num));
                }
            }

        }
    }

    return tmpdata;
}


//花的浇水

//"康乃馨","百合","水仙","玫瑰","郁金香"   浇水情况 需要三个数组按浇水情况返回
//康乃馨：
//                   浇水情况正常：
//                   缺水
//                   急缺水
//                  "SELECT SUM(`quantity`) FROM flower_info  WHERE  TYPE = '" + flowername + "' + "AND `watering` ='浇水情况正常';"
std::map<QString,std::vector<int>> sqldataread::getwater(){
    std::map<QString,std::vector<int>> m1;

    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection")){
        db = QSqlDatabase::database("qt_sql_default_connection");
        db.setDatabaseName(Global::dataBaseName);

    }
    else{
        db =QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(Global::sqlIp);
        db.setUserName(Global::sqlUserName);
        db.setPassword(Global::sqlPassWord);
        db.setDatabaseName(Global::dataBaseName);

    }
    //#`carnation``lily``narcissus``rose``tulip`
    //"康乃馨","百合","水仙","玫瑰","郁金香"

    db.open();

    QStringList tablename = {"carnation","lily","narcissus","rose","tulip"};
    QStringList ChinaTablename = {"康乃馨","百合","水仙","玫瑰","郁金香"};

    for(int i = 0;i<tablename.size();i++){
        QStringList selectSql = {QString("SELECT SUM(`quantity`) FROM flower_info  WHERE  TYPE = '" + ChinaTablename[i] + "' AND `watering` ='浇水情况正常';"),QString("SELECT SUM(`quantity`) FROM flower_info  WHERE  TYPE = '" + ChinaTablename[i] + "' AND `watering` ='缺少量水';"),QString("SELECT SUM(`quantity`) FROM flower_info  WHERE  TYPE = '" + ChinaTablename[i] + "' AND `watering` ='急缺水';")};
        QSqlQuery query;
        std::vector<int> tmp1;
        for(auto sql:selectSql){

            query.exec(sql);
            if(query.next()){

                int num = query.value(0).toInt();
                tmp1.push_back(num);

            }
            m1[tablename[i]] =tmp1;
        }

    }

    /*
    std::map<QString,std::vector<int>> :: iterator      iter;
    for(  iter=m1.begin();     iter!=m1.end();   iter++)
           {

               QString a= iter->first;
                  std::vector<int>  p = iter->second;
                  qDebug()<<a<<" "<<p<<endl;

          }
*/

    return m1;
}

//花的肥料
std::map<QString,std::vector<int>> sqldataread::getfeiliao(){
    std::map<QString,std::vector<int>> m1;
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection")){
        db = QSqlDatabase::database("qt_sql_default_connection");
        db.setDatabaseName(Global::dataBaseName);

    }
    else{
        db =QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(Global::sqlIp);
        db.setUserName(Global::sqlUserName);
        db.setPassword(Global::sqlPassWord);
        db.setDatabaseName(Global::dataBaseName);

    }
    //#`carnation``lily``narcissus``rose``tulip`
    //"康乃馨","百合","水仙","玫瑰","郁金香"

    db.open();

    QStringList tablename = {"carnation","lily","narcissus","rose","tulip"};
    QStringList ChinaTablename = {"康乃馨","百合","水仙","玫瑰","郁金香"};

    for(int i = 0;i<tablename.size();i++){
        QStringList selectSql = {QString("SELECT SUM(`quantity`) FROM flower_info  WHERE  TYPE = '" + ChinaTablename[i] + "' AND `fertilization` ='肥料情况正常';"),QString("SELECT SUM(`quantity`) FROM flower_info  WHERE  TYPE = '" + ChinaTablename[i] + "' AND `fertilization` ='缺少少量肥料';"),QString("SELECT SUM(`quantity`) FROM flower_info  WHERE  TYPE = '" + ChinaTablename[i] + "' AND  `fertilization` ='急缺肥料';")};
        QSqlQuery query;
        std::vector<int> tmp1;
        for(auto sql:selectSql){

            query.exec(sql);
            if(query.next()){

                int num = query.value(0).toInt();
                tmp1.push_back(num);

            }
            m1[tablename[i]] =tmp1;
        }

    }
    /*
    std::map<QString,std::vector<int>> :: iterator      iter;
    for(  iter=m1.begin();     iter!=m1.end();   iter++)
           {

               QString a= iter->first;
                  std::vector<int>  p = iter->second;
                  qDebug()<<a<<" "<<p<<endl;

          }
*/

    return m1;
}


//"康乃馨","百合","水仙","玫瑰","郁金香"   浇水情况 需要三个数组按浇水情况返回
std::map<QString,std::vector<int>> sqldataread::getgrowth(){
    std::map<QString,std::vector<int>> m1;
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
    //"康乃馨","百合","水仙","玫瑰","郁金香"
    db.open();

    QStringList tablename = {"carnation","lily","narcissus","rose","tulip"};
    QStringList ChinaTablename = {"康乃馨","百合","水仙","玫瑰","郁金香"};

    for(int i = 0;i<tablename.size();i++){
        QStringList selectSql = {QString("SELECT SUM(`quantity`)  FROM flower_info  WHERE  TYPE = '" + ChinaTablename[i] + "'   AND   `growth` ='A';"),
                                 QString("SELECT SUM(`quantity`)  FROM flower_info  WHERE  TYPE = '" + ChinaTablename[i] + "'   AND   `growth` ='B+';"),
                                 QString("SELECT SUM(`quantity`)  FROM flower_info  WHERE  TYPE = '" + ChinaTablename[i] + "'   AND   `growth` ='B';"),
                                 QString("SELECT SUM(`quantity`)  FROM flower_info  WHERE  TYPE = '" + ChinaTablename[i] + "'   AND   `growth` ='C+';"),
                                 QString("SELECT SUM(`quantity`)  FROM flower_info  WHERE  TYPE = '" + ChinaTablename[i] + "'   AND   `growth` ='C';"),
                                 QString("SELECT SUM(`quantity`)  FROM flower_info  WHERE  TYPE = '" + ChinaTablename[i] + "'   AND   `growth` ='D';")};
        QSqlQuery query;
        std::vector<int> tmp1;
        for(auto sql:selectSql){

            query.exec(sql);
            if(query.next()){

                int num = query.value(0).toInt();
                tmp1.push_back(num);

            }
            m1[tablename[i]] =tmp1;
        }
    }

    return m1;
}



// 返回 花名 + 生长情况的数组
std::pair<QString,std::vector<int>> sqldataread:: getFlowerGrowth(QString flowerName){
    std::pair<QString,std::vector<int>> flowerGrowth;
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
    db.open();
    QStringList selectSql = {QString( "SELECT SUM(`quantity`) FROM flower_info  WHERE  TYPE = '" + flowerName + "' AND  `growth` ='A';"),
                             QString( "SELECT SUM(`quantity`) FROM flower_info  WHERE  TYPE = '" + flowerName + "' AND  `growth` ='B+';"),
                             QString( "SELECT SUM(`quantity`) FROM flower_info  WHERE  TYPE = '" + flowerName + "' AND  `growth` ='B';"),
                             QString( "SELECT SUM(`quantity`) FROM flower_info  WHERE  TYPE = '" + flowerName + "' AND  `growth` ='C+';"),
                             QString( "SELECT SUM(`quantity`) FROM flower_info  WHERE  TYPE = '" + flowerName + "' AND  `growth` ='C';"),
                             QString( "SELECT SUM(`quantity`) FROM flower_info  WHERE  TYPE = '" + flowerName + "' AND  `growth` ='D';")};
    QSqlQuery query;
    std::vector<int> tmp1;
    for(auto sql:selectSql){
        query.exec(sql);
        if(query.next()){

            int num = query.value(0).toInt();
            tmp1.push_back(num);
        }
    }
    flowerGrowth = std::make_pair(flowerName,tmp1);

    return flowerGrowth;
}

//单个花的生长情况
//花名 (中文）
//控制显示长度
QChart * sqldataread::flowerGrowthChart(QString flowerName){
    //![1]
    QBarSet *set0 = new QBarSet("A");
    QBarSet *set1 = new QBarSet("B+");
    QBarSet *set2 = new QBarSet("B");
    QBarSet *set3 = new QBarSet("C+");
    QBarSet *set4 = new QBarSet("C");
    QBarSet *set5 = new QBarSet("D");
    std::pair<QString,std::vector<int>> oneFlowerGrowth = getFlowerGrowth(flowerName);
    std::vector<int>  p = oneFlowerGrowth.second;

    *set0 << p[0];
    *set1 << p[1];
    *set2 << p[2];
    *set3 << p[3];
    *set4 << p[4];
    *set5 << p[5];

    int maxi = 0;
    int sum = 0;
    for (int i : p) {
        if(i>maxi){
            maxi = i;
        }
        sum += i;
    }

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);
    series->append(set5);
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(flowerName + "生长情况");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    categories <<flowerName;
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,maxi+int(sum/6));
    axisY->setLabelFormat("%d"); //标签格式

    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    //![4]
    //![5]
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    //![5]
    //!
    //额外设置
    series->setBarWidth(0.95);
    series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd); // 设置数据系列标签的位置于数据柱内测上方
    series->setLabelsVisible(true); // 设置显示数据系列标签
    chart->setTheme(QChart::ChartThemeBlueCerulean);

    //![6]
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //![6]
    return chart;

}

//五种花的浇水情况
QChart * sqldataread:: mywaterchart(){
    //    QStringList tablename = {"carnation","lily","narcissus","rose","tulip"};
    //    QStringList caobei =  {"康乃馨","百合","水仙","玫瑰","郁金香"};
    //生长状况  统计
    //  浇水状况 --
    // 施肥状况=-- 每种有多少，各自有多少

    /*
急缺肥料	浇水情况正常
肥料情况正常	急缺水
缺少少量肥料	急缺水
缺少少量肥料	缺少量水
急缺肥料	急缺水

*/

    //![1]
    QBarSet *set0 = new QBarSet("浇水情况正常");
    QBarSet *set1 = new QBarSet("缺少量水");
    QBarSet *set2 = new QBarSet("急缺水");

    std::map<QString,std::vector<int>> m = getwater();
    std::map<QString,std::vector<int>> :: iterator      iter;
    int maxi = 0;
    for(  iter=m.begin();     iter!=m.end();   iter++)
    {
        std::vector<int>  p = iter->second;
        *set0 << p[0];
        *set1 << p[1];
        *set2 << p[2];
        //       qDebug()<<a<<" "<<p<<endl;
        for (int i : p) {
            if(i>maxi){
                maxi = i;
            }
        }

    }


    //五种花各各自的情况
    //"康乃馨","百合","水仙","玫瑰","郁金香"


    //![1]


    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("花卉浇水情况");
    chart->setAnimationOptions(QChart::SeriesAnimations);


    //![4]
    QStringList categories;
    categories <<"康乃馨"<<"百合"<<"水仙"<<"玫瑰"<<"郁金香";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);

    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,maxi + int(maxi/3));
    axisY->setLabelFormat("%d"); //标签格式


    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    //![4]
    //!
    //额外设置
    series->setBarWidth(0.95);
    series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd); // 设置数据系列标签的位置于数据柱内测上方
    series->setLabelsVisible(true); // 设置显示数据系列标签
    chart->setTheme(QChart::ChartThemeBlueCerulean);



    //![5]
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);


    //![6]
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //![6]
    return chart;

}

//五种花的肥料情况
QChart * sqldataread:: myfeiliaochart(){
    //    QStringList tablename = {"carnation","lily","narcissus","rose","tulip"};
    //    QStringList caobei =  {"康乃馨","百合","水仙","玫瑰","郁金香"};
    //生长状况  统计
    //  浇水状况 --
    // 施肥状况=-- 每种有多少，各自有多少

    /*
急缺肥料	浇水情况正常
肥料情况正常	急缺水
缺少少量肥料	急缺水
缺少少量肥料	缺少量水
急缺肥料	急缺水

*/

    //![1]
    QBarSet *set0 = new QBarSet("肥料情况正常");
    QBarSet *set1 = new QBarSet("缺少少量肥料");
    QBarSet *set2 = new QBarSet("急缺肥料");

    std::map<QString,std::vector<int>> m = getfeiliao();
    std::map<QString,std::vector<int>> :: iterator      iter;
    int maxi = 0;
    for(  iter=m.begin();     iter!=m.end();   iter++)
    {
        std::vector<int>  p = iter->second;
        *set0 << p[0];
        *set1 << p[1];
        *set2 << p[2];
        //       qDebug()<<a<<" "<<p<<endl;
        for (int i : p) {
            if(i>maxi){
                maxi = i;
            }
        }

    }


    //五种花各各自的情况
    //"康乃馨","百合","水仙","玫瑰","郁金香"
    /*
        *set0 << 1 << 2 << 3 << 4 << 5 << 6;//浇水情况正常
        *set1 << 5 << 0 << 0 << 4 << 0 << 7;//缺少量水
        *set2 << 3 << 5 << 8 << 13 << 8 << 5;//急缺水
*/


    //![1]


    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);


    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("花卉施肥情况");
    chart->setAnimationOptions(QChart::SeriesAnimations);


    //![4]
    QStringList categories;
    categories <<"康乃馨"<<"百合"<<"水仙"<<"玫瑰"<<"郁金香";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,maxi + int(maxi/3));
    axisY->setLabelFormat("%d"); //标签格式

    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    //![4]

    //![5]
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    //![5]

    //额外设置
    series->setBarWidth(0.95);
    series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd); // 设置数据系列标签的位置于数据柱内测上方
    series->setLabelsVisible(true); // 设置显示数据系列标签
    chart->setTheme(QChart::ChartThemeBlueCerulean);

    //![6]
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //![6]
    return chart;

}

//全部花的生长情况
QChart * sqldataread::mygrowthchart(){
    //    QStringList tablename = {"carnation","lily","narcissus","rose","tulip"};
    //    QStringList caobei =  {"康乃馨","百合","水仙","玫瑰","郁金香"};
    //生长状况  统计
    //  浇水状况 --
    // 施肥状况=-- 每种有多少，各自有多少

    /*
    急缺肥料	浇水情况正常
    肥料情况正常	急缺水
    缺少少量肥料	急缺水
    缺少少量肥料	缺少量水
    急缺肥料	急缺水

    */

    //![1]
    QBarSet *set0 = new QBarSet("A");
    QBarSet *set1 = new QBarSet("B+");
    QBarSet *set2 = new QBarSet("B");
    QBarSet *set3 = new QBarSet("C+");
    QBarSet *set4 = new QBarSet("C");
    QBarSet *set5 = new QBarSet("D");

    std::map<QString,std::vector<int>> m = getgrowth();
    std::map<QString,std::vector<int>> :: iterator      iter;
    int maxi = 0;
    for(  iter=m.begin();     iter!=m.end();   iter++)
    {
        std::vector<int>  p = iter->second;
        *set0 << p[0];
        *set1 << p[1];
        *set2 << p[2];
        *set3 << p[3];
        *set4 << p[4];
        *set5 << p[5];
        //       qDebug()<<a<<" "<<p<<endl;
        for (int i : p) {
            if(i>maxi){
                maxi = i;
            }
        }

    }



    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);
    series->append(set5);





    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("花卉生长情况");
    chart->setAnimationOptions(QChart::SeriesAnimations);


    //![4]
    QStringList categories;
    categories <<"康乃馨"<<"百合"<<"水仙"<<"玫瑰"<<"郁金香";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,maxi + int(maxi/3));
    axisY->setLabelFormat("%d"); //标签格式

    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    //![4]

    //![5]
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    //![5]
    //额外设置
    series->setBarWidth(0.95);

    chart->setTheme(QChart::ChartThemeBlueCerulean);
    //![6]
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //![6]
    return chart;
}


//一键生成分析
void sqldataread::on_pushButton_10_clicked()
{
    on_pushButton_3_clicked();
    on_pushButton_clicked();
    on_pushButton_4_clicked();
    on_pushButton_5_clicked();
    on_pushButton_6_clicked();
    on_pushButton_7_clicked();
    on_pushButton_8_clicked();
    on_pushButton_9_clicked();
}

//一键清空
void sqldataread::on_pushButton_11_clicked()
{

    ui->graphicsView->close();
    ui->graphicsView_2->close();
    ui->graphicsView_3->close();
    ui->graphicsView_4->close();
    ui->graphicsView_5->close();
    ui->graphicsView_6->close();
    ui->graphicsView_7->close();
    ui->graphicsView_8->close();
    qDebug()<<"用户 " << Global::username<<"情况所有图表区"<<endl;


}

//花卉生长
void sqldataread::on_pushButton_4_clicked()
{
    QChart * growthchart = mygrowthchart();
    ui->graphicsView_3->show();
    ui->graphicsView_3->setChart( growthchart);
    qDebug()<<"用户 " << Global::username<<"查看花卉生长情况图"<<endl;

}


//花卉施肥
void sqldataread::on_pushButton_clicked()
{
    QChart * feiliaochart = myfeiliaochart();
    ui->graphicsView_2->show();
    ui->graphicsView_2->setChart( feiliaochart);
    qDebug()<<"用户 " << Global::username<<"查看花卉施肥情况图"<<endl;


}

//花卉浇水情况
void sqldataread::on_pushButton_3_clicked()
{
    QChart * chart = mywaterchart();
    ui->graphicsView->show();
    ui->graphicsView->setChart( chart);
    qDebug()<<"用户 " << Global::username<<"查看花卉浇水情况图"<<endl;


}


//康乃馨生长
void sqldataread::on_pushButton_5_clicked()
{
    QChart * knx =flowerGrowthChart( "康乃馨");
    ui->graphicsView_4->show();
    ui->graphicsView_4->setChart( knx);
    qDebug()<<"用户 " << Global::username<<"查看康乃馨生长情况图"<<endl;

}
//百合生长
void sqldataread::on_pushButton_6_clicked()
{
    QChart * lily = flowerGrowthChart( "百合");
    ui->graphicsView_5->show();
    ui->graphicsView_5->setChart( lily);
    qDebug()<<"用户 " << Global::username<<"查看百合生长情况图"<<endl;

}

//水仙生长
void sqldataread::on_pushButton_7_clicked()
{

    QChart * shuixian = flowerGrowthChart( "水仙");
    ui->graphicsView_6->show();
    ui->graphicsView_6->setChart( shuixian);
    qDebug()<<"用户 " << Global::username<<"查看水仙生长情况图"<<endl;

}

//玫瑰生长
void sqldataread::on_pushButton_8_clicked()
{

    QChart * rose = flowerGrowthChart( "玫瑰");
    ui->graphicsView_7->show();
    ui->graphicsView_7->setChart( rose);
    qDebug()<<"用户 " << Global::username<<"查看玫瑰生长情况图"<<endl;


}

//郁金香生长
void sqldataread::on_pushButton_9_clicked()
{
    QChart * tulip =flowerGrowthChart( "郁金香");
    ui->graphicsView_8->show();
    ui->graphicsView_8->setChart( tulip);
    qDebug()<<"用户 " << Global::username<<"查看郁金香生长情况图"<<endl;

}

//花卉生长情况分布
void sqldataread::on_pushButton_12_clicked()
{
    fg.show();
    qDebug()<<"用户 " << Global::username<<"查看花卉生长情况分布图"<<endl;

}

//花卉数量分布
void sqldataread::on_pushButton_2_clicked()
{
    ff.show();
    qDebug()<<"用户 " << Global::username<<"查看花卉数量分布图"<<endl;

}
