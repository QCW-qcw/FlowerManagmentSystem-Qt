#include "whetherwindow.h"
#include "ui_whetherwindow.h"
#include<QNetworkAccessManager>
#include<QMessageBox>
#include<QFile>
#include <QNetworkReply>
#include<QDebug>
#include <QRegularExpression>
#include <QRegExpValidator>
#include<vector>
#include<map>
#include<global.h>
WhetherWindow::WhetherWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WhetherWindow)
{
    ui->setupUi(this);
    setWindowTitle("花卉管理系统天气助手");
    ui->winddir->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->windpower->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->bindstate->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->toptem->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->lowtem->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->nowtem->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->whether->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->shidu->setStyleSheet("background:transparent;border-width:0;border-style:outset");
    ui->update->setStyleSheet("background:transparent;border-width:0;border-style:outset");

    QStringList city = getcity();
    ui->cityComboBox->addItems(city);


}

WhetherWindow::~WhetherWindow()
{
    delete ui;
}
//得到字符串
QString WhetherWindow::getconnect(){
    //网页地址
    const QString URLSTR = "http://flash.weather.com.cn/wmaps/xml/xinyang.xml";
    QUrl url(URLSTR);
    QNetworkAccessManager manager;
    QEventLoop loop;
    qDebug() << "Reading code form " << URLSTR;
    //发出请求
    QNetworkReply *reply = manager.get(QNetworkRequest(url));
    //请求结束并下载完成后，退出子事件循环
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    //开启子事件循环
    loop.exec();
    QString code = reply->readAll();
    // qDebug() <<code<<"\n"<< "Finished! " ;
    return code;
}
//得到网页并下载
void WhetherWindow::gettext()
{
    const QString URLSTR = "http://flash.weather.com.cn/wmaps/xml/shanghai.xml";
    const QString FILE_NAME="text.txt";
    QUrl url(URLSTR);
    QEventLoop loop;
    bool hasSourceFile;
    QString sourceCode;
    QNetworkAccessManager manager;

    //发出请求
    QNetworkReply *reply=manager.get(QNetworkRequest(url));

    //请求结束并下载完成后，退出子事件循环
    connect(reply,SIGNAL(finished()),&loop,SLOT(quit()),Qt::UniqueConnection);

    //开启子事件循环
    loop.exec();

    //将读取到的信息写入文件
    sourceCode=reply->readAll();
    // QString str = QString(sourceCode);
    // qDebug()<<str;
    // qDebug()<<sourceCode;


    QFile file(FILE_NAME);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out<<sourceCode<<endl;
    if(file.size()>10){
        QMessageBox::information(this,tr("提示"),tr("网站数据获取成功！"),QMessageBox::Ok);
        hasSourceFile=true;
    }
    else{
        QMessageBox::information(this,tr("提示"),tr("网站数据获取失败！"),QMessageBox::Ok);
        hasSourceFile=false;
    }
    file.close();
    if(file.size()<10){
        file.remove();
    }
}



//得到网页并下载
void WhetherWindow::gethtml()
{
    //网页地址
    const QString URLSTR = "http://work.doshow.com.cn";
    //储存网页代码的文件
    const QString FILE_NAME = "code.txt";

    QUrl url(URLSTR);
    QNetworkAccessManager manager;
    QEventLoop loop;
    qDebug() << "Reading code form " << URLSTR;
    //发出请求
    QNetworkReply *reply = manager.get(QNetworkRequest(url));
    //请求结束并下载完成后，退出子事件循环
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    //开启子事件循环
    loop.exec();

    //将读到的信息写入文件
    QString code = reply->readAll();
    QFile file(FILE_NAME);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << code << endl;
    file.close();
    qDebug() << "Finished, the code have written to " << FILE_NAME;
}
/*
#<cityname="潢川县" centername="潢川县" fontColor="FFFFFF" pyName="" state1="7" state2="1" stateDetailed="小雨转多云" tem1="22" tem2="13" temNow="14" windState="西北风微风级" windDir="西风" windPower="1级" humidity="91%" time="07:00" url="101180607"/>
#城市 centername
#天气状况 stateDetailed
#最高温度：tem1
#最低温度：tem2
#现在温度：temNow
#风力：windState ，windDir，windPower
#湿度：humidity
#更新时间：time
*/

std::vector<std::map<QString,QString>> WhetherWindow::getwhether(){
    QString code = getconnect();
    QStringList res,tmp;
    std::vector<std::map<QString,QString>> whether;
    res = code.split("/>");
    for  (auto item :res){
        code = item.replace("\n","");
        code = code.replace("\r","");
        code = code.replace("\"","");
        int start = code.indexOf("centername");
        int end = code.indexOf("url");
        code = code.mid(start,end);
        //qDebug()<<code<<endl;

        std::map<QString,QString> onecity;
        //城市
        QString s = "centername=";
        QRegularExpression reCenterName("centername=(.+?) ");
        QRegularExpressionMatch centername = reCenterName.match(code);
        //qDebug()<<centername.captured(0).mid(s.length())<<endl;
        onecity.insert(std::make_pair("地区",centername.captured(0).mid(s.length())));

        //#天气状况 stateDetailed
        s = "stateDetailed=";
        QRegularExpression restateDetailed("stateDetailed=(.+?) ");
        QRegularExpressionMatch stateDetailed = restateDetailed.match(code);
        //qDebug()<<stateDetailed.captured(0).mid(s.length())<<endl;
        onecity.insert(std::make_pair("天气状况",stateDetailed.captured(0).mid(s.length())));



        s = "tem1=";
        QRegularExpression retem1("tem1=(.+?) ");
        QRegularExpressionMatch tem1 = retem1.match(code);
        //qDebug()<<tem1.captured(0).mid(s.length())<<endl;
        onecity.insert(std::make_pair("最高温度",tem1.captured(0).mid(s.length()) + "度"));


        s = "tem2=";
        QRegularExpression retem2("tem2=(.+?) ");
        QRegularExpressionMatch tem2 = retem2.match(code);
        //qDebug()<<tem2.captured(0).mid(s.length())<<endl;
        onecity.insert(std::make_pair("最低温度",tem2.captured(0).mid(s.length()) + "度"));


        s = "temNow=";
        QRegularExpression retemNow("temNow=(.+?) ");
        QRegularExpressionMatch temNow = retemNow.match(code);
        //qDebug()<<temNow.captured(0).mid(s.length())<<endl;
        onecity.insert(std::make_pair("现在温度",temNow.captured(0).mid(s.length()) + "度"));


        s = "windState=";
        QRegularExpression rewindState("windState=(.+?) ");
        QRegularExpressionMatch windState = rewindState.match(code);
        //qDebug()<<windState.captured(0).mid(s.length())<<endl;
        onecity.insert(std::make_pair("刮风情况",windState.captured(0).mid(s.length())));

        s = "windDir=";
        QRegularExpression rewindDir("windDir=(.+?) ");
        QRegularExpressionMatch windDir = rewindDir.match(code);
        //qDebug()<<windDir.captured(0).mid(s.length())<<endl;
        onecity.insert(std::make_pair("风向",windDir.captured(0).mid(s.length())));


        s = "windPower=";
        QRegularExpression rewindPower("windPower=(.+?) ");
        QRegularExpressionMatch windPower = rewindPower.match(code);
        //qDebug()<<windPower.captured(0).mid(s.length())<<endl;
        onecity.insert(std::make_pair("风力",windPower.captured(0).mid(s.length())));


        s = "humidity=";
        QRegularExpression rehumidity("humidity=(.+?) ");
        QRegularExpressionMatch humidity = rehumidity.match(code);
        //qDebug()<<humidity.captured(0).mid(s.length())<<endl;
        onecity.insert(std::make_pair("湿度",humidity.captured(0).mid(s.length())));


        s = "time=";
        QRegularExpression retime("time=(.+?) ");
        QRegularExpressionMatch time = retime.match(code);
        //qDebug()<<time.captured(0).mid(s.length())<<endl;
        onecity.insert(std::make_pair("更新时间",time.captured(0).mid(s.length())));

        whether.push_back(onecity);

    }
    /*
 * for(auto &it : m){
        cout << it.first << "-" << it.second <<endl;
    }
 * */
    /*
   for (auto item : whether){
       for(auto &it : item){
           qDebug()<<it.first<<":"<<it.second<<endl;
       }

   }
   */
    return whether;

}


QStringList WhetherWindow::getcity(){
    QStringList city;
    std::vector<std::map<QString,QString>> whether = getwhether();

    for (auto item : whether){
        for(auto &it : item){
            if(it.first =="地区"){
                city.push_back(it.second);
            }
        }
    }
    return city;

}



void WhetherWindow::on_pushButton_2_clicked()
{

    std::vector<std::map<QString,QString>> whether = getwhether();
    QString nowcity = ui->cityComboBox->currentText();
    std::map<QString,QString> citywhether;
    for(size_t i = 0;i<whether.size();i++){
        for(auto &it : whether[i]){

            // qDebug()<<it.first<<":"<<it.second<<endl;
            if(it.second ==nowcity){

                citywhether = whether[i];
                break;
            }
        }
    }
    QString topwd ="" ;
    QString lowwd  ="";

    for(auto item: citywhether){

        // qDebug()<<item.first<<":"<<item.second<<endl;
        if(item.first =="刮风情况" )
            ui->bindstate->setText(item.second);
        else if(item.first =="天气状况")
            ui->whether->setText(item.second);
        else if(item.first =="更新时间")
            ui->update->setText(item.second);
        else if(item.first =="最高温度"){
            topwd = item.second.split(" ")[0];
            qDebug()<<topwd;
        }
        //ui->toptem->setText(item.second);
        else if(item.first =="最低温度"){
            lowwd = item.second.split(" ")[0];
        }
        //ui->lowtem->setText(item.second);
        else if(item.first =="现在温度")
            ui->nowtem->setText(item.second);
        else if(item.first =="湿度")
            ui->shidu->setText(item.second);
        else if(item.first =="风向")
            ui->winddir->setText(item.second);
        else
            ui->windpower->setText(item.second);

        //  if(QString::number(topwd) >QString::number(lowwd)){
        if(topwd!="" &&lowwd!=""){
            if(topwd.toInt() >lowwd.toInt()){
                ui->toptem->setText((topwd + "度"));
                ui->lowtem->setText((lowwd + "度"));

            }else{
                ui->toptem->setText((lowwd + "度"));
                ui->lowtem->setText((topwd + "度"));

            }

        }



        /*
 *
 * #城市 cityname
#天气状况 stateDetailed
#最高温度：tem1
#最低温度：tem2
#现在温度：temNow
#风力：windState ，windDir，windPower
#湿度：humidity
#更新时间：time
 * */
    }
    /*
    for (auto item : whether){
        for(auto &it : item){
        if(it.second ==( nowcity)){
            //qDebug()<<it.first<<":"<<it.second<<endl;
            citywhether = item;
            break;
        }
    }

        for(auto item: citywhether){
            qDebug()<<item.first<<":"<<item.second<<endl;
        }
 }
*/
    qDebug()<<"用户 " << Global::username<<"进行天气查询，查询"<<nowcity<<"的天气"<<endl;

}
