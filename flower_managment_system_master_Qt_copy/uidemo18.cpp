//#pragma execution_character_set("utf-8")


#include <QDesktopServices>
#include <QUrl>
#include "uidemo18.h"
#include "ui_uidemo18.h"
#include "iconhelper.h"
#include "registerwindow.h"
#include "flowersclass.h"
#include "browser.h"
#include "browserwindow.h"
#include "tabwidget.h"
#include <QApplication>
#include <QWebEngineProfile>
#include <QWebEngineSettings>

#include"global.h"
#define iconSize    50
#define iconWidth   100
#define iconHeight  70
#define navBtnWidth 45
#define navIcoWidth 18

UIDemo18::UIDemo18(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UIDemo18)
{
    ui->setupUi(this);
    this->initForm();
    this->initNav();
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

    ui->stackedWidget->setCurrentIndex(0);

    QStringList items;
    items.append(tr("请选择花种"));
    items.append(tr("玫瑰"));
    items.append(tr("康乃馨"));
    items.append(tr("郁金香"));
    items.append(tr("水仙"));
    items.append(tr("百合"));

    ui->comboBox->addItems(items);
    ui->comboBox->setCurrentIndex(0);

    ui->dateEdit->setCalendarPopup(true);

    ui->lineEdit->setStyleSheet("QLineEdit{background-color:transparent}"
                                     "QLineEdit{border-width:0;border-style:outset}");

    connect(ui->btn_Product, SIGNAL(clicked()), this, SLOT(btn_Product_Clicked_slots()));
    connect(ui->btn_Info, SIGNAL(clicked()), this, SLOT(btn_Info_Clicked_slots()));
    connect(ui->btn_Research, SIGNAL(clicked()), this, SLOT(btn_Research_Clicked_slots()));
    connect(ui->btn_Map, SIGNAL(clicked()), this, SLOT(btn_Map_Clicked_slots()));
    connect(ui->btn_Analysis, SIGNAL(clicked()), this, SLOT(btn_Analysis_Clicked_slots()));
    connect(ui->btn_Settings, SIGNAL(clicked()), this, SLOT(btn_Settings_Clicked_slots()));
}

UIDemo18::~UIDemo18()
{
    delete ui;
}



void UIDemo18::initForm()
{
    ui->labTitle->setText("花卉管理系统");
    this->setWindowTitle(ui->labTitle->text());
    this->setProperty("canMove", true);
    ui->widgetTop->setProperty("flag", "nav");
    ui->widgetTop->setFixedHeight(40);



    IconHelper::Instance()->setIcon(ui->btnReturn, 0xf122, navIcoWidth);
    IconHelper::Instance()->setIcon(ui->btnMsg, 0xf045, 20);
    IconHelper::Instance()->setIcon(ui->rili, 0xf073, navIcoWidth);
    IconHelper::Instance()->setIcon(ui->help, 0xf27a, navIcoWidth);
    IconHelper::Instance()->setIcon(ui->btnQuit, 0xf08b, navIcoWidth);
    IconHelper::Instance()->setIcon(ui->whether, 0xf0c2, navIcoWidth);
    //    IconHelper::Instance()->setIcon(ui->btnQuit, 0xfOOd, navIcoWidth);

    QStringList qss;

    //全局无焦点虚边框,全局文字颜色,全局字号
    qss.append(QString("*{outline:0px;color:#FEFEFE;}"));

    //主窗体背景
    qss.append(QString("QWidget#widgetMain{border-image:url(%1);}").arg(":/image/QQ图片20210524151000.jpg"));

    //标题字体大小
    qss.append(QString("QLabel#labTitle{font:%1px;}").arg(navIcoWidth));

    //顶部导航
    qss.append(QString("QWidget[flag=\"nav\"]{background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,"
                       "stop:0 %1,stop:1 %2);}").arg("#00688B").arg("#093746"));
    qss.append(QString("QWidget[flag=\"nav\"] QAbstractButton{background:none;border:none;"
                       "min-width:%1px;max-width:%1px;}").arg(navBtnWidth));

    this->setStyleSheet(qss.join(""));
}

void UIDemo18::initNav()
{
    QList<QString> listColorBg;
    listColorBg << "#1570A5" << "#16A085" << "#C0392B" << "#047058" << "#9B59BB" << "#34495E";
    QList<QString> listColorText;
    listColorText << "#FEFEFE" << "#FEFEFE" << "#FEFEFE" << "#FEFEFE" << "#FEFEFE" << "#FEFEFE";

    QList<QChar> listChar;
    listChar << 0xf030 << 0xf108 << 0xf002 << 0xf03e << 0xf0e8 << 0xf085;
    QList<QString> listText;
    listText << "产品展示"<< "档案记录" << "报表查询" << "地图管理" << "生成分析" << "系统设置";

    btns << ui->btn_Product << ui->btn_Info << ui->btn_Research << ui->btn_Map << ui->btn_Analysis << ui->btn_Settings;
    for (int i = 0; i < btns.count(); i++) {
        QToolButton *btn = btns.at(i);
        btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        btn->setIconSize(QSize(iconWidth, iconHeight));

        QPixmap pix = IconHelper::Instance()->getPixmap(listColorText.at(i), listChar.at(i), iconSize, iconWidth, iconHeight);
        btn->setIcon(QIcon(pix));
        btn->setText(listText.at(i));

        QStringList list;
        list.append(QString("QToolButton{font:%1px;background:%2;}").arg(iconSize / 2).arg(listColorBg.at(i)));
        list.append(QString("QToolButton{border:none;border-radius:8px;padding:30px;}"));
        list.append(QString("QToolButton:pressed{background:%1;}").arg("#737A97"));
        btn->setStyleSheet(list.join(""));
    }
}
void UIDemo18::userinfo(){
    ui->lineEdit->setText("欢迎用户 "+ Global::username);
}
void UIDemo18::btn_Product_Clicked_slots()
{
    fshow.show();
    IconHelper::Instance()->setIcon(ui->btnReturn, 0xf122, navIcoWidth);
    qDebug()<<tr("用户 ")  << Global::username<<"进入产品展示页面"<<endl;
}
void UIDemo18::btn_Info_Clicked_slots()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->labTitle->setText(ui->btn_Info->text());
    IconHelper::Instance()->setIcon(ui->btnReturn, 0xf122, navIcoWidth);
}
void UIDemo18::btn_Research_Clicked_slots()
{
    if(!s1.isVisible())
        s1.show();
    // ui->stackedWidget->setCurrentIndex(3);
    // ui->labTitle->setText(ui->btn_Research->text());
    IconHelper::Instance()->setIcon(ui->btnReturn, 0xf122, navIcoWidth);
    qDebug()<<tr("用户 ")  << Global::username<<" 进入报表查询页面"<<endl;

}
void UIDemo18::btn_Map_Clicked_slots()
{

    QCoreApplication::setOrganizationName("QtExamples");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    // QApplication app(argc, argv);
    // app.setWindowIcon(QIcon(QStringLiteral(":AppLogoColor.png")));

    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true);
    QWebEngineProfile::defaultProfile()->setUseForGlobalCertificateVerification();
#endif

    //   QUrl url = commandLineUrlArgument();
    QUrl url(Global::mapurl);

    //Browser browser;
    BrowserWindow *window = browser.createWindow();
    window->tabWidget()->setUrl(url);
    /*  ui->stackedWidget->setCurrentIndex(4);
    ui->labTitle->setText(ui->btn_Map->text());
    */
    IconHelper::Instance()->setIcon(ui->btnReturn, 0xf122, navIcoWidth);
    qDebug()<<tr("用户 ")  << Global::username<<" 进入地图管理页面"<<endl;

}
void UIDemo18::btn_Analysis_Clicked_slots()
{
    sqlfenxi.show();
    //ui->stackedWidget->setCurrentIndex(5);
    //ui->labTitle->setText(ui->btn_Analysis->text());
    IconHelper::Instance()->setIcon(ui->btnReturn, 0xf122, navIcoWidth);
    qDebug()<<tr("用户 ")  << Global::username<<" 进入生成分析页面"<<endl;

}
void UIDemo18::btn_Settings_Clicked_slots()
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->labTitle->setText(ui->btn_Settings->text());
    IconHelper::Instance()->setIcon(ui->btnReturn, 0xf122, navIcoWidth);
    qDebug()<<tr("用户 ")  << Global::username<<" 进入系统设置页面"<<endl;
}

//退出系统到登录页面  槽函数实现
void UIDemo18::on_btnMsg_clicked()
{
    user.userID = nullptr;
    user.password = nullptr;
    user.userType = NULL;
    //    qDebug()<<user.userID<< user.password<< user.userType;
    emit quit_Signal();
    qDebug()<<tr("用户 ")  << Global::username<<" 退出系统，返回登录页面"<<endl;
}

//返回槽函数实现
void UIDemo18::on_btnReturn_clicked()
{
    int index = ui->stackedWidget->currentIndex();
    if (index != 0) {
        ui->stackedWidget->setCurrentIndex(0);
        ui->labTitle->setText("花卉管理系统");
        IconHelper::Instance()->setIcon(ui->btnReturn, 0xf122, navIcoWidth);
        qDebug()<<tr("用户 ")  << Global::username<<" 返回主页面"<<endl;
    }
}


void UIDemo18::on_btn_AddAcount_clicked()
{
    //判断是否为管理员，如果是则打开注册页面
    //    qDebug()<<user.userType;
    if(user.userType != 1){
        QMessageBox::warning(NULL,"Error","您的操作权限不足！");
    }
    else{
        re.show();
        qDebug()<<"管理员 " << Global::username<<" 进入添加用户界面"<<endl;
    }
}

void UIDemo18::on_help_clicked()
{
    m1.show();
    qDebug()<<tr("用户 ")  << Global::username<<" 进入消息帮助页面"<<endl;
}

void UIDemo18::on_rili_clicked()
{
    f1.show();
    qDebug()<<tr("用户 ")  << Global::username<<" 进入生产日历页面"<<endl;

}

void UIDemo18::on_btnQuit_clicked()
{
    this->close();
    qDebug()<<tr("用户 ")  << Global::username<<" 退出系统"<<endl;
    exit(0);
}
void UIDemo18::on_whether_clicked()
{
    tianqi.show();
    qDebug()<<tr("用户 ")  << Global::username<<" 进入天气查询页面"<<endl;

}

void UIDemo18::on_btn_AddFlower_clicked()
{
    indexofCombobox = ui->comboBox->currentIndex();
    BaseFlowers baseFlowers;


    //判断输入信息是否为空  加强合法判断
    if(ui->comboBox->currentIndex() == 0){
        QMessageBox::information(this,"Error","<font size='12' color='red'>请选择花种</font>",QMessageBox::Ok);
    }
    else if(ui->lineEdit_Company->text() == ""){
        QMessageBox::information(this,"Error","<font size='12' color='red'>种植单位不能为空！</font>",QMessageBox::Ok);
    }
    else if(ui->lineEdit_ContactPerson->text() == ""){
        QMessageBox::information(this,"Error","<font size='12' color='red'>联系人不能为空！</font>",QMessageBox::Ok);
    }
    else if(ui->lineEdit_ContactNum->text() == ""){
        QMessageBox::information(this,"Error","<font size='12' color='red'>联系电话不能为空！</font>",QMessageBox::Ok);
    }
    else if(ui->lineEdit_Quantity->text() == ""){
        QMessageBox::information(this,"Error","<font size='12' color='red'>种植数量不能为空！</font>",QMessageBox::Ok);
    }
    else if(ui->lineEdit_Cost->text() == ""){
        QMessageBox::information(this,"Error","<font size='12' color='red'>单株成本不能为空！</font>",QMessageBox::Ok);
    }
    else{

        QDate datt =  ui->dateEdit->date();
        QString time = datt.toString("yyyy/MM/dd");


        baseFlowers.addFlowers(ui->comboBox->currentText(),
                               time,ui->lineEdit_Farming->text(),
                               ui->lineEdit_Nongzi->text(),
                               ui->lineEdit_Location1->text(),
                               ui->lineEdit_Location2->text(),
                               ui->lineEdit_Location3->text(),
                               ui->lineEdit_Location4->text(),
                               ui->lineEdit_Company->text(),
                               ui->lineEdit_ContactPerson->text(),
                               ui->lineEdit_ContactNum->text(),
                               ui->lineEdit_Quantity->text(),
                               ui->lineEdit_Cost->text(),
                               user.userName,
                               ui->lineEdit_Remark->text());

        QMessageBox::information(this,"success","<font size='12' color='red'>添加成功！</font>",QMessageBox::Ok);

    }
}

void UIDemo18::on_btn_cleartext_clicked()
{
    ui->lineEdit_Farming->clear();
    ui->lineEdit_Nongzi->clear();ui->lineEdit_Location1->clear();ui->lineEdit_Location2->clear();ui->lineEdit_Location3->clear();ui->lineEdit_Location4->clear();ui->lineEdit_Company->clear();ui->lineEdit_ContactPerson->clear();ui->lineEdit_ContactNum->clear();ui->lineEdit_Quantity->clear();ui->lineEdit_Cost->clear();user.userName,ui->lineEdit_Remark->clear();

}


void UIDemo18::on_pushButton_clicked()
{
    Global::ipaddress =  ui->lineEdit_ip->text();
    QMessageBox::information(this,"success","<font size='12' color='red'>文件传输IP已更改</font>",QMessageBox::Ok);
    qDebug()<<tr("用户 ")  << Global::username<<" 修改文件传输ip为 "<<Global::ipaddress<<endl;

}

void UIDemo18::on_pushButton_map_clicked()
{
    Global::mapurl =  ui->lineEdit_mapurl->text();
    QMessageBox::information(this,"success","<font size='12' color='red'>花卉地图url已更改</font>",QMessageBox::Ok);
    qDebug()<<tr("用户 ")  << Global::username<<" 修改地图链接为 "<<Global::mapurl<<endl;

}
