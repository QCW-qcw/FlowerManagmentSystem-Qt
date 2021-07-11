#include "qapplication.h"
#include "appinit.h"
#include "uidemo18.h"
#include <QApplication>
#include <QtSql>
#include <QMessageBox>
#include "loginwindow.h"
#include <QTextCodec>

void MessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();

    QString strMsg("");
    switch(type)
    {
    case QtDebugMsg:
        strMsg = QString("Debug:");
        break;
    case QtWarningMsg:
        strMsg = QString("Warning:");
        break;
    case QtCriticalMsg:
        strMsg = QString("Critical:");
        break;
    case QtFatalMsg:
        strMsg = QString("Fatal:");
        break;
    }

    // 设置输出信息格式
    QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ");
    QString strMessage = strMsg + QString("%1 *File:%2  *Line:%3  *Function:%4  *Message:%5  ")
            .arg(strDateTime) .arg(context.file).arg(context.line).arg(context.function).arg(localMsg.constData());

    //加锁
    static QMutex mutex;
    mutex.lock();
    // 循环写日志
    QTime current_time = QTime::currentTime();
    int hour = current_time.hour();        //当前的小时
    int minute = current_time.minute();    //当前的分
    //    QString fileName1 = (QDateTime::currentDateTime().toString("yyyy年MM月dd日")) + QString("%1时%2分").arg(hour).arg(minute) + ".txt";
    //    QString fileName2 = (QDateTime::currentDateTime().toString("yyyy年MM月dd日")) + QString("%1时%2分").arg(hour).arg(minute) + ".txt";
    QString fileName1 = (QDateTime::currentDateTime().toString("yyyy年MM月dd日")) + QString("%1时").arg(hour) + ".txt";
    QString fileName2 = (QDateTime::currentDateTime().toString("yyyy年MM月dd日")) + QString("%1时").arg(hour)+ ".txt";

    QFile outfile1(fileName1);
    QFile outfile2(fileName2);
    outfile1.open(QIODevice::WriteOnly | QIODevice::Append);

    if(outfile1.size() >= 1024*100000 )
    {
        outfile1.close();
        outfile2.remove();
        QFile::copy((fileName1),(fileName2));
        outfile1.remove();
        QFile outfile3(fileName1);
        outfile3.open(QIODevice::WriteOnly | QIODevice::Append);

        QTextStream stream(&outfile3);
        stream << strMessage << endl;
    }
    else
    {

        QTextStream stream(&outfile1);
        stream << strMessage << endl;
    }

    //     解锁
    mutex.unlock();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setFont(QFont("Microsoft Yahei", 10));
    AppInit::Instance()->start();
    qInstallMessageHandler(MessageOutput);
    //连接数据库
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db =QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(Global::sqlIp);
    db.setUserName(Global::sqlUserName);
    db.setPassword(Global::sqlPassWord);
    db.setDatabaseName(Global::dataBaseName);
    LoginWindow Login;


    //如果数据库连接成功打开窗口否则退出程序
    if(db.open()){
        Login.show();
        qDebug()<<"数据库连接成功"<<endl;

    }
    else{
        qDebug()<<"数据库连接加载失败"<<endl;
        QMessageBox::warning(NULL,"error","数据库连接失败");
        return 0;
    }

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    return a.exec();
}
