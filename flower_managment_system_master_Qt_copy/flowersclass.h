#ifndef FLOWERSCLASS_H
#define FLOWERSCLASS_H

#include <QWidget>
#include<QString>
#include<QDate>
#include<QSql>
#include<QSqlQuery>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

/*
基类： BaseFlowers
        子类：RoseFlowers
             KnxFlowers
             TulipFlowers
             SxFlowers
             BhFlowers
组合类作为子类的成员：
        卖花SaleFlowers
        花期FlowerDate
*/

typedef struct{
    QString flowerName;
    QDateTime plantTime;
    QString farming;
    QString nongzi;
    QString location1;
    QString location2;
    QString location3;
    QString location4;
    QString company;
    QString contactPerson;
    QString contactNum;
    int quantity;
    float costperPlant;
    float cost;
    QString sysOperator;
    QString fertilization;
    QString watering;
    QString growth;
    QString remark;
}FlowerInfo;


enum WaterState
{
    W1,//极度缺水---0
    W2,//少量缺水----1
    W3//浇水情况正常--2
};
//QStringList waterlist ={"极度缺水","少量缺水","浇水情况正常"};

enum FeiLiao
{
    F1,//极度缺肥---0
    F2,//缺少量肥---1
    F3//肥料情况正常---2
};
//QStringList fllist ={"极度缺肥","缺少量肥","肥料情况正常"};

enum GrowthState{
    G1,
    G2,
    G3,
    G4,
    G5,
    G6
};
//QStringList growthlist ={"A","A-","B","C","D"};


class BaseFlowers:public QObject
{
public:
    FlowerInfo flowerInfo;

    QString flowername;//花名

    WaterState watering;
    FeiLiao feiliao;
    GrowthState growthstate;

    QString flowerarea;//地块
    QString flowerthing;//农事
    QString flowermoney;//农资

    QString operater;//操作人员
    QString others;//其他，备注

    void addFlowers(QString flowerType, QString plantTime, QString farming, QString nongzi, QString location1, QString location2, QString location3, QString location4, QString company, QString contactPerson, QString contactNum, QString quantity, QString costperPlant, QString userName, QString remark);
    void  setwater(int n ) {
        if(n>2)return;
        else watering = WaterState(n);
    }
    QString getwaterstate() {
        QStringList waterlist ={"极度缺水","少量缺水","浇水情况正常"};

        switch (watering)
        {
        case 0:
            return waterlist[0]; break;
        case 1:
            return waterlist[1]; break;
        case 2:
            return waterlist[2];break;
        }
    }

    void  setfeiliao(int n ) {
        if(n>2)return;
        else feiliao = FeiLiao(n);
    }
    QString getflstate() {

        QStringList fllist ={"极度缺肥","缺少量肥","肥料情况正常"};

        switch (feiliao)
        {
        case 0:
            return fllist[0]; break;
        case 1:
            return fllist[1]; break;
        case 2:
            return fllist[2];break;
        }
    }

    QString getgrowthstate(){
        QStringList growthlist ={"A","A-","B","C","D"};

        int tmp = watering + feiliao;
        switch (tmp) {
        case 4: return growthlist[0];break;
        case 3: return growthlist[1];break;
        case 2: return growthlist[2];break;
        case 1: return growthlist[3];break;
        case 0: return growthlist[4];break;
        }
        return "";
    }
};

//卖花
class SaleFlowers{
public:
    //设置默认值为0
    int flowernum = 0;//数量
    float onecost = 0;//单株成本价
    float onesale = 0;//单株售价

    float oneprofit = onesale - onecost;//单株利润
    float totalsale = flowernum * onesale;//总销售额
    float totalcost = flowernum * onecost;//总成本
    float totalprofit = flowernum * (onesale - onecost);//总利润

    SaleFlowers() {};

    //重写有参构造函数 --保持默认拷贝构造函数
    SaleFlowers(int num,float cost,float sale):flowernum(num),onecost(cost),onesale(sale){}

    float get_oneprofit(){
        return onesale - onecost;
    }
    float get_totalsale() {
        return flowernum * onesale;
    }
    float get_totalcost() {
        return flowernum * onecost;
    }
    float get_totalprofit() {
        return flowernum * (onesale - onecost);
    }

};

//未确定 花生长状态确定
class FlowerDate{
public:
    QDateTime createtime;//种植时间
    QDateTime growthtime;//生长时间
    QDateTime florescence;//花期
    QString weekday;
    /*
       依据当前时间去判断花的生长状态：
                    生长中 --- 施肥等
                    开花中 ---收割等
*/

/*    QString GetFlowerState(){
        QDateTime today = QDateTime::currentDateTime();
        weekday = today.toString("ddd");
        if(growthtime >today){

        }
    }
*/

};
//玫瑰
class RoseFlowers:public BaseFlowers{
public:
     SaleFlowers flowersale;//卖花

     RoseFlowers() {
//        flowername = "rose";
     };
     RoseFlowers(int num, float cost, float sale) :flowersale(num, cost, sale) {}



};
//康乃馨
class KnxFlowers:public BaseFlowers{
public:
     SaleFlowers flowersale;//卖花

     KnxFlowers() {
//        flowername = "carnation";
     };
     KnxFlowers(int num, float cost, float sale) :flowersale(num, cost, sale) {}

};
//郁金香
class TulipFlowers:public BaseFlowers{
public:
     SaleFlowers flowersale;//卖花

     TulipFlowers() {
//          flowername = "tulip";
     };
     TulipFlowers(int num, float cost, float sale) :flowersale(num, cost, sale) {}

};
//水仙
class SxFlowers:public BaseFlowers{
public:
     SaleFlowers flowersale;//卖花

     SxFlowers() {
//         flowername = "narcissus";
     };
     SxFlowers(int num, float cost, float sale) :flowersale(num, cost, sale) {}

};
//百合
class BhFlowers:public BaseFlowers{
public:
     SaleFlowers flowersale;//卖花

     BhFlowers() {
//         flowername = "lilium";
     };
     BhFlowers(int num, float cost, float sale) :flowersale(num, cost, sale) {}


};


#endif // FLOWERSCLASS_H
