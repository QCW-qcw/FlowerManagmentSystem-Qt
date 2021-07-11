#include "flowershow.h"
#include "ui_flowershow.h"
#include<QSqlDatabase>
#include<QMessageBox>
#include<QDebug>
#include<QSqlQuery>
#include<QSqlTableModel>
#include<QTextCodec>
#include<QSqlRecord>
#include<QTextEdit>
#include<QSqlField>
#include<global.h>
flowershow::flowershow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::flowershow)
{
    ui->setupUi(this);
    setWindowTitle("产品展示");

}

flowershow::~flowershow()
{
    delete ui;
}

//成本 数量 公司 肥料 浇水 生长
int flowershow::getcost(QString flowername){
    int flowercost = 0;
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

    QString selectSql = "SELECT SUM(cost) FROM flower_info WHERE TYPE = '" + flowername + "'" ;
    QSqlQuery query;
    query.exec(selectSql);
    if(query.next()){
        flowercost = query.value(0).toInt();
    }

    return flowercost;
}

int flowershow::getnum(QString flowername){
    int flowernum = 0;

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
    if(db.open()){
        qDebug()<<"ok"<<endl;
    }

    QString selectSql = "SELECT SUM(quantity) FROM flower_info WHERE TYPE = '" + flowername + "'" ;
    QSqlQuery query;
    query.exec(selectSql);
    if(query.next()){
        flowernum = query.value(0).toInt();
    }

    return flowernum;
}

std::tuple<QString,QString,QString> flowershow::getcompany(QString flowername){
    std::tuple<QString,QString,QString> flowercompany;

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

    QString company ;
    QString companynum;
    QString countcompany;
    QString selectSql;
    //最大数量
    selectSql = "SELECT MAX(quantity)FROM flower_info WHERE TYPE = '" + flowername + "'" ;
    QSqlQuery query;
    query.exec(selectSql);
    if(query.next()){
        companynum = query.value(0).toString();
    }
    //公司名
    selectSql = "SELECT company  FROM flower_info WHERE TYPE = '" + flowername + "'"  +  "AND  quantity =  " + companynum ;

    QSqlQuery query2;
    query2.exec(selectSql);
    if(query2.next()){
        company = query2.value(0).toString();
    }
    //公司数量
    selectSql = "SELECT COUNT(DISTINCT company) FROM flower_info WHERE TYPE = '" + flowername + "'" ;
    QSqlQuery query3;
    query3.exec(selectSql);
    if(query3.next()){
        countcompany = query3.value(0).toString();
    }

    flowercompany = std::make_tuple(countcompany,company,companynum);


    return flowercompany;
}


std::vector<std::pair<QString,int>>flowershow:: getgrowth(QString flowername){
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
        int num;
        QString selectSql =  "SELECT SUM(quantity) FROM flower_info  WHERE TYPE = '" + flowername + "'"  + " AND   growth = " + "'" + i + "';";
        qDebug()<<selectSql;
        QSqlQuery query;
        query.exec(selectSql);


        if(query.next()){
            num = query.value(0).toInt();
        }
        tmpdata.push_back(std::make_pair(i,num));
    }
    /*
    for(auto item : tmpdata){
        qDebug()<<item.first<<item.second<<endl;
    }
*/
    return tmpdata;

}



std::vector<std::pair<QString,int>>flowershow:: getwater(QString flowername){
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

    /*
缺少量水
浇水情况正常
急缺水
*/
    QStringList level  = {"浇水情况正常","缺少量水","急缺水"};

    for(auto i : level){
        int num;
        QString selectSql = "SELECT SUM(quantity) FROM flower_info  WHERE TYPE = '" + flowername + "'" + "AND watering =  " + "'" + i + "';";
        QSqlQuery query;
        query.exec(selectSql);
        if(query.next()){
            num = query.value(0).toInt();

        }
        tmpdata.push_back(std::make_pair(i,num));
    }
    /*
    for(auto item : tmpdata){
        qDebug()<<item.first<<item.second<<endl;
    }
*/
    return tmpdata;

}




std::vector<std::pair<QString,int>>flowershow:: getfeiliao(QString flowername){
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
    /*
缺少少量肥料
急缺肥料
肥料情况正常

*/
    QStringList level  = {"肥料情况正常","缺少少量肥料","急缺肥料"};
    for(auto i : level){
        int num;
        QString selectSql ="SELECT SUM(quantity) FROM flower_info  WHERE TYPE = '" + flowername + "'" + "AND fertilization =  " + "'" + i + "';";
        QSqlQuery query;
        query.exec(selectSql);
        if(query.next()){
            num = query.value(0).toInt();

        }
        tmpdata.push_back(std::make_pair(i,num));
    }
    /*
    for(auto item : tmpdata){
        qDebug()<<item.first<<item.second<<endl;
    }
*/
    return tmpdata;

}


void flowershow::showflower(QTextEdit* TextEdit,QString flowername){

    QString text;
    int num = getnum(flowername);
    int cost = getcost(flowername);
    std::tuple<QString,QString,QString>   company = getcompany(flowername);
    std::vector<std::pair<QString,int>> growth = getgrowth(flowername);
    std::vector<std::pair<QString,int>> water = getwater(flowername);

    std::vector<std::pair<QString,int>> feilao = getfeiliao(flowername);

    TextEdit->insertPlainText(flowername+'\n');
    TextEdit->insertPlainText("种植数量为：" + QString::number(num)  + "株"+'\n');
    TextEdit->insertPlainText("成本为：" + QString::number(cost) + "元"+'\n');
    TextEdit->insertPlainText("共计 " + std::get<0>(company) +" 家公司需求该花"+'\n');
    TextEdit->insertPlainText("其中需求最多的公司为： " + std::get<1>(company)+'\n');
    TextEdit->insertPlainText("该公司需求量为： "+ std::get<2>(company) + "株"+ '\n');

    TextEdit->insertPlainText(QString("生长状况： ")+ '\n');
    for(auto item : growth){
        TextEdit->insertPlainText( '\t' +item.first + " ："+QString::number(item.second)+ "株"+ '\n');
    }
    TextEdit->insertPlainText(QString("浇水情况： ")+ '\n');
    for(auto item : water){
        TextEdit->insertPlainText(  '\t'+item.first + " ："+QString::number(item.second)+ "株"+ '\n');
    }
    TextEdit->insertPlainText(QString("施肥情况： ")+ '\n');
    for(auto item : feilao){
        TextEdit->insertPlainText(  '\t'+item.first + " ："+QString::number(item.second)+ "株"+ '\n');
    }


}



void flowershow::on_pushButton_clicked()
{
    ui->textEdit->clear();
    showflower(ui->textEdit,"康乃馨");
    qDebug()<<"用户 "<<Global::username<<"查看康乃馨的需求展示"<<endl;

}

void flowershow::on_pushButton_2_clicked()
{
    ui->textEdit_2->clear();
    showflower(ui->textEdit_2,"水仙");
    qDebug()<<"用户 "<<Global::username<<"查看水仙的需求展示"<<endl;


}

void flowershow::on_pushButton_3_clicked()
{
    ui->textEdit_3->clear();

    showflower(ui->textEdit_3,"百合");
    qDebug()<<"用户 "<<Global::username<<"查看百合的需求展示"<<endl;

}

void flowershow::on_pushButton_4_clicked()
{
    ui->textEdit_4->clear();
    showflower(ui->textEdit_4,"玫瑰");
    qDebug()<<"用户 "<<Global::username<<"查看玫瑰的需求展示"<<endl;

}

void flowershow::on_pushButton_5_clicked()
{
    ui->textEdit_5->clear();
    showflower(ui->textEdit_5,"郁金香");
    qDebug()<<"用户 "<<Global::username<<"查看郁金香的需求展示"<<endl;

}

