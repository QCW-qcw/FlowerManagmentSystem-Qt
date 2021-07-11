#include "uidemo18.h"
#include "loginwindow.h"
#include "flowersclass.h"
#include <QDate>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include "registerwindow.h"

/*添加花卉信息函数实现*/
void BaseFlowers::addFlowers(QString flowerType, QString plantTime, QString farming, QString nongzi, QString location1, QString location2, QString location3, QString location4, QString company, QString contactPerson, QString contactNum, QString quantity, QString costperPlant, QString userName, QString remark)
{
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

    float sum = quantity.toFloat();
    float costperplant = costperPlant.toFloat();
    float cost = sum * costperplant;
    QString id = "";

    QSqlQuery query;
    QString sql = "SELECT MAX(id) FROM flower_info; ";
    query.prepare(sql);
    query.exec();
    if(query.next()){
        int num = query.value(0).toInt();
        num = num+1;
        id = QString("%1").arg(num);
    }

    sql = "insert into flower_info(id,type, plantTime, farming, nongzi, location1, location2, location3, location4, company, contactPerson, contactNum, quantity, costperPlant, cost, operator, fertilization, watering, growth, remark) "
          "values( '" +id+"','"+ flowerType + "', '" +plantTime + "' , '" + farming + "', '" + nongzi + "', '"
            +location1 + "', '" + location2+ "', '"+location3 + "', '" +location4 + "',  '"
            +company + "', '" + contactPerson+ "', '"+contactNum + "', '" +quantity
            + "' , '" + QString("%1").arg(costperPlant) + "', '"+QString("%1").arg(cost) + "', '"
            +userName + "' ,'肥料情况正常','浇水情况正常', 'A','" +remark+"');";
    query.prepare(sql);
    qDebug()<<"用户 " << Global::username<<" 新增花卉记录： "<<sql<<endl;
    /*   query.prepare("insert into flower_info(type, plantTime, farming, nongzi, location1, location2, location3, location4, company, contactPerson, contactNum, quantity, costperPlant, cost, operator, fertilization, watering, growth, remark)"
                  "values(:type,:plantTime,:farming,:nongzi,:location1,:location2,:location3,:location4,:company,:contactPerson,:contactNum,:quantity,:costperPlant,:cost,:operator,:fertilization,:watering,:growth,:remark)");
    query.bindValue(":type", flowerType);
    query.bindValue(":plantTime",plantTime);
    query.bindValue(":farming", farming);
    query.bindValue(":nongzi", nongzi);
    query.bindValue(":location1", location1);
    query.bindValue(":location2", location2);
    query.bindValue(":location3", location3);
    query.bindValue(":location4", location4);
    query.bindValue(":company", company);
    query.bindValue(":contactPerson", contactPerson);
    query.bindValue(":contactNum", contactNum);
    query.bindValue(":quantity", quantity);
    query.bindValue(":costperPlant", costperPlant);
    query.bindValue(":cost", cost);
    query.bindValue(":operator", userName);
    query.bindValue(":fertilization", "肥料情况正常");
    query.bindValue(":watering", "浇水情况正常");
    query.bindValue(":growth", "A");
    query.bindValue(":remark", remark);
    */
    query.exec();
}
