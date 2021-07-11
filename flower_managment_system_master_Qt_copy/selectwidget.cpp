#include "selectwidget.h"
#include "ui_selectwidget.h"
#include<QSql>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QDebug>
#include<QSqlQuery>
#include<QSqlTableModel>
#include<QTextCodec>
#include<QSqlRecord>
#include<QTextEdit>
#include<QDebug>
#include <QFileDialog>
#include <QDesktopServices>
#include <QMessageBox>
#include <QAxObject>
#include<QPainter>
#include<QPrinter>
#include"global.h"
selectWidget::selectWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::selectWidget)
{
    ui->setupUi(this);
    QFont ft;
    ft.setPointSize(10);
    ui->starttime->setFont(ft);
    setWindowTitle("报表查询");


    connect(ui->shengxu, SIGNAL(clicked()), this, SLOT(radioBtnAscend_clicked()));
    connect(ui->jiangxu, SIGNAL(clicked()), this, SLOT(radioBtnDescend_clicked()));

    // 使数据库支持中文
    // 包含头文件
    //设置db
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

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


    //如果数据库连接成功打开窗口否则退出程序
    if(db.open()){
        qDebug()<<"success,数据库连接成功";
    }
    else{
        qDebug()<<"success,数据库连接失败";
    }
    db.exec("set NAMES UTF8");



    m_pQryModel = new QSqlQueryModel(ui->tableView);

    m_pQrySelection = new QItemSelectionModel(m_pQryModel);
    //选择行变化时
    connect(m_pQrySelection, SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
            this, SLOT(qrySelection_currentRowChanged(QModelIndex, QModelIndex)));

    //创建数据映射
    m_pQryDataMapper = new QDataWidgetMapper();
    m_pQryDataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    m_pQryDataMapper->setModel(m_pQryModel);
    m_pQryDataMapper->addMapping(ui->id, 0);//"empNo";
    m_pQryDataMapper->addMapping(ui->flowername, 1);//"Name";
    m_pQryDataMapper->addMapping(ui->starttime, 2);//"Gender";
    m_pQryDataMapper->addMapping(ui->thing, 3);
    m_pQryDataMapper->addMapping(ui->money, 4);
    m_pQryDataMapper->addMapping(ui->company, 9);//
    m_pQryDataMapper->addMapping(ui->contacts, 10);
    m_pQryDataMapper->addMapping(ui->phone, 11);
    m_pQryDataMapper->addMapping(ui->num, 12);
    m_pQryDataMapper->addMapping(ui->operater, 15);
    m_pQryDataMapper->addMapping(ui->feiliao, 16);
    m_pQryDataMapper->addMapping(ui->water, 17);
    m_pQryDataMapper->addMapping(ui->growth, 18);

    m_pQryDataMapper->addMapping(ui->others, 19);

    m_pQryDataMapper->toFirst();//移动到首记录
    QSqlRecord  emptyRec1 = m_pQryModel->record();//获取空记录，只有字段名
    for (int i = 0; i < emptyRec1.count(); i++)
        ui->thesort->addItem(emptyRec1.fieldName(i));


    // tableView显示属性设置
    //以项为单位选择SelectItems  ---列SelectColumns  行 SelectRows
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //单选
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    //隔行变色
    ui->tableView->setAlternatingRowColors(true);
    //    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableView->horizontalHeader()->setMinimumSectionSize(100);


    m_pTabModel = new QSqlTableModel(this, db);//数据表

    //flower_info
    //operator_info
    //flower_info_copy
    //model->setTable("flower_info");

    m_pTabModel->setTable("flower_info");



    //关联选择模型
    m_pTabSelection = new QItemSelectionModel(m_pTabModel);
    //theSelection当前项变化时触发currentChanged信号
    connect(m_pTabSelection, SIGNAL(currentChanged(QModelIndex, QModelIndex)),
            this, SLOT(tabSelection_currentChanged(QModelIndex, QModelIndex)));
    //选择行变化时
    connect(m_pTabSelection, SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
            this, SLOT(tabSelection_currentRowChanged(QModelIndex, QModelIndex)));

    //创建界面组件与数据模型的字段之间的数据映射
    m_pTabDataMapper = new QDataWidgetMapper();
    m_pTabDataMapper->setModel(m_pTabModel);//设置数据模型
    m_pTabDataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);//

    //type	plantTime	farming	nongzi	location1	location2	location3	location4	company	contactPerson	contactNum	quantity	costperPlant	cost	operator	fertilization	watering	growth	remark
    //QList<QString> title = {"编号", "花种","种植时间","农事","农资","单位","联系人","联系方式","数量","操作人员","施肥情况","浇水情况","生长情况","备注"};

    //界面组件与tabModel的具体字段之间的联系
    m_pTabDataMapper->addMapping(ui->id, m_pTabModel->fieldIndex("编号"));
    m_pTabDataMapper->addMapping(ui->flowername, m_pTabModel->fieldIndex("花种"));
    m_pTabDataMapper->addMapping(ui->starttime, m_pTabModel->fieldIndex("种植时间"));
    m_pTabDataMapper->addMapping(ui->thing, m_pTabModel->fieldIndex("农事"));
    m_pTabDataMapper->addMapping(ui->money, m_pTabModel->fieldIndex("农资"));
    m_pTabDataMapper->addMapping(ui->company, m_pTabModel->fieldIndex("单位"));
    m_pTabDataMapper->addMapping(ui->contacts, m_pTabModel->fieldIndex("联系人"));
    m_pTabDataMapper->addMapping(ui->phone, m_pTabModel->fieldIndex("联系方式"));
    m_pTabDataMapper->addMapping(ui->num, m_pTabModel->fieldIndex("数量"));
    m_pTabDataMapper->addMapping(ui->operater, m_pTabModel->fieldIndex("操作人员"));
    m_pTabDataMapper->addMapping(ui->feiliao, m_pTabModel->fieldIndex("施肥情况"));
    m_pTabDataMapper->addMapping(ui->water, m_pTabModel->fieldIndex("浇水情况"));
    m_pTabDataMapper->addMapping(ui->growth,m_pTabModel->fieldIndex("生长情况")); //图片无法直接映射
    m_pTabDataMapper->addMapping(ui->others,m_pTabModel->fieldIndex("备注")); //图片无法直接映射

    m_pTabDataMapper->toFirst();//移动到首记录
    QSqlRecord  emptyRec = m_pTabModel->record();//获取空记录，只有字段名
    for (int i = 0; i < emptyRec.count(); i++)
        ui->thesort->addItem(emptyRec.fieldName(i));

    connect(ui->thesort, SIGNAL(currentIndexChanged(int)), this, SLOT(comboFields_currentIndexChanged(int)));


    //仅显示不能修改
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //网格背景画笔
    //ui->tableView->setGridStyle(Qt::DashLine);
    ui->tableView->setGridStyle(Qt::DotLine);

    //样式
    ui->tableView->setStyleSheet("QTableView { border: none;"
                                 "selection-background-color: #8EDE21;"
                                 "color: block}");

}

void selectWidget::sethead(){

    m_pQryModel->setHeaderData(0, Qt::Horizontal, "编号");
    m_pQryModel->setHeaderData(1, Qt::Horizontal, "花种");
    m_pQryModel->setHeaderData(2, Qt::Horizontal, "种植时间");
    m_pQryModel->setHeaderData(3, Qt::Horizontal, "农事");
    m_pQryModel->setHeaderData(4, Qt::Horizontal, "农资");
    m_pQryModel->setHeaderData(5, Qt::Horizontal, "地理位置1");
    m_pQryModel->setHeaderData(6, Qt::Horizontal, "地理位置2");
    m_pQryModel->setHeaderData(7, Qt::Horizontal, "地理位置3");
    m_pQryModel->setHeaderData(8, Qt::Horizontal, "地理位置4");
    m_pQryModel->setHeaderData(9, Qt::Horizontal, "单位");
    m_pQryModel->setHeaderData(10, Qt::Horizontal, "联系人");
    m_pQryModel->setHeaderData(11, Qt::Horizontal, "联系方式");
    m_pQryModel->setHeaderData(12, Qt::Horizontal, "数量");
    m_pQryModel->setHeaderData(13, Qt::Horizontal, "单株成本");
    m_pQryModel->setHeaderData(14, Qt::Horizontal, "成本");

    m_pQryModel->setHeaderData(15, Qt::Horizontal, "操作人员");
    m_pQryModel->setHeaderData(16, Qt::Horizontal, "施肥情况");
    m_pQryModel->setHeaderData(17, Qt::Horizontal, "浇水情况");
    m_pQryModel->setHeaderData(18, Qt::Horizontal, "生长情况");
    m_pQryModel->setHeaderData(19, Qt::Horizontal, "备注");


}

void selectWidget::on_selectbth_clicked()
{

    //自定义查询 ---sql语句
    QList<std::pair<QString,QString>> res =  getalltext();
    // QString basesql = "SELECT * FROM flower_info WHERE 1=1 ";
    QString basesql =  "SELECT * FROM flower_info  ";
    QString finallsql;
    if(res.length() !=0)
        basesql +=QString(" WHERE ");
    for(int i = 0;i<res.length();i++){
        if(i == res.length()-1)
            basesql += res[i].first +QString( " = ") + QString("'")+res[i].second+QString("'") + QString( " ") ;
        else
            basesql +=  res[i].first+QString( " = ") + QString("'")+res[i].second+QString("'") + QString( " ")+QString("AND ") ;
    }
    finallsql = basesql;
    finallsql += QString(" ORDER By ") + ui->thesort->currentText();
    if(ui->shengxu->isChecked())
        finallsql += QString(" ASC ");
    else
        finallsql +=QString(" DESC ");


    // select a,b,c   from flower_info order by d;
    m_pQryModel->setQuery(finallsql,this->db);
    ui->tableView->setModel(m_pQryModel);
    sethead();
    ui->tableView->setSelectionModel(m_pQrySelection);
    if(ui->tableView->model()->rowCount() == 0)
        QMessageBox::warning(this, tr("Warning"),tr("没有查到您想要的结果，请核实查询条件") );

    //校验隐藏信息
    QList<std::pair<bool,int>> re = gethiden();
    for (int i = 0;i<res.length();i++) {
        if(re[i].first){
            ui->tableView->setColumnHidden(re[i].second,true);
        }
    }

    //隐藏地理位置
    ui->tableView->setColumnHidden(5,true);
    ui->tableView->setColumnHidden(6,true);
    ui->tableView->setColumnHidden(7,true);
    ui->tableView->setColumnHidden(8,true);
    qDebug()<<"用户 " << Global::username<<" 进行精确查询，查询sql语句为:"<<finallsql<<endl;

}
void selectWidget::on_mohuselect_clicked()
{

    QList<std::pair<QString,QString>> res =  getalltext();
    QString basesql =  "SELECT * FROM flower_info  ";
    QString finallsql;
    if(res.length() !=0)
        basesql +=QString(" WHERE ");
    for(int i = 0;i<res.length();i++){
        if(i == res.length()-1)
            basesql += res[i].first +QString( " LIKE ") + QString("'%")+res[i].second+QString("%'") + QString( " ") ;
        else
            basesql +=  res[i].first+QString( " LIKE ") + QString("'%")+res[i].second+QString("%'")+QString("AND ") ;
    }
    finallsql = basesql;
    finallsql += QString(" ORDER By ") + ui->thesort->currentText();
    if(ui->shengxu->isChecked())
        finallsql += QString(" ASC ");
    else
        finallsql +=QString(" DESC ");

    // select a,b,c   from flower_info order by d;
    m_pQryModel->setQuery(finallsql,this->db);
    ui->tableView->setModel(m_pQryModel);
    sethead();
    ui->tableView->setSelectionModel(m_pQrySelection);
    if(ui->tableView->model()->rowCount() == 0)
        QMessageBox::warning(this, tr("Warning"),tr("没有查到您想要的结果，请核实查询条件") );

    //校验隐藏信息
    QList<std::pair<bool,int>> re = gethiden();
    for (int i = 0;i<res.length();i++) {
        if(re[i].first){
            ui->tableView->setColumnHidden(re[i].second,true);
        }
    }

    //隐藏地理位置
    ui->tableView->setColumnHidden(5,true);
    ui->tableView->setColumnHidden(6,true);
    ui->tableView->setColumnHidden(7,true);
    ui->tableView->setColumnHidden(8,true);
    qDebug()<<"用户 " << Global::username<<" 进行模糊查询，查询sql语句为:"<<finallsql<<endl;

}

void selectWidget::on_shouge_clicked()
{

    QList<std::pair<QString,QString>> res =  getalltext();
    QString basesql =  "UPDATE flower_info SET ";
    QString finallsql;
    if(res.length() !=0){
        for(int i = 0;i<res.length();i++){

            if(res[i].first== "quantity"){
                basesql +=   res[i].first+QString( " =   '0'");
            }
        }
        finallsql = basesql + "WHERE id = '" + res[0].second+ "'; ";
        //qDebug()<<finallsql;
        //qDebug()<<res.length()<<endl;
        QSqlQuery query;
        //插入花卉信息
        query.prepare(finallsql);
        query.exec();
        QMessageBox::information(this,"success","收割成功");
        qDebug()<<"用户 " << Global::username<<" 进行收割，收割sql语句为:"<<finallsql<<endl;



        //       qDebug()<<"finallsql is ok";

    }else{
        qDebug()<<"用户 " << Global::username<<" 收割失败"<<endl;

        QMessageBox::information(this,"info","未选择收割的花卉");
    }

}

void selectWidget::on_gengxin_clicked()
{
    //UPDATE SET 字段 1=值 1 [,字段 2=值 2… ] [WHERE 子句 ]


    QList<std::pair<QString,QString>> res =  getalltext();
    QString basesql =  "UPDATE flower_info SET ";
    QString finallsql;
    if(res.length() !=0){
        for(int i = 0;i<res.length();i++){

            if(i == 0){
                basesql +=   res[i].first+QString( " =  '") + res[i].second + "' ";
            }
            else{
                basesql +=    ", " +res[i].first+QString( " =  '") + res[i].second + "' ";

            }
            qDebug()<<res[i].first<< "  "<<res[i].second<<endl;

        }
        finallsql = basesql + "WHERE id = '" + res[0].second+ "'; ";
        //qDebug()<<finallsql;
        //qDebug()<<res.length()<<endl;
        QSqlQuery query;
        //插入花卉信息
        query.prepare(finallsql);
        query.exec();
        qDebug()<<"用户 " << Global::username<<" 更新花卉信息，更新sql语句为 ："<<finallsql<<endl;

        QMessageBox::information(this,"success","修改数据成功");


        //       qDebug()<<"finallsql is ok";

    }else{
        qDebug()<<"用户 " << Global::username<<" 未选择更新花卉信息"<<endl;
        QMessageBox::information(this,"info","未选择要修改行");
    }
}





void selectWidget::comboFields_currentIndexChanged(int index)
{
    if (m_pTabModel)
    {
        if (ui->shengxu->isChecked())
            m_pTabModel->setSort(index, Qt::AscendingOrder);
        else
            m_pTabModel->setSort(index, Qt::DescendingOrder);
        m_pTabModel->select();
    }
}

//升序
void selectWidget::radioBtnAscend_clicked()
{
    m_pTabModel->setSort(ui->thesort->currentIndex(), Qt::AscendingOrder);
    m_pTabModel->select();
}

//降序
void selectWidget::radioBtnDescend_clicked()
{
    m_pTabModel->setSort(ui->thesort->currentIndex(), Qt::DescendingOrder);
    m_pTabModel->select();
}



//QTableView的SelectionModel的行发生了变化，进行处理
void selectWidget::qrySelection_currentRowChanged(const QModelIndex& current, const QModelIndex& previous)
{
    Q_UNUSED(previous);

    m_pQryDataMapper->setCurrentModelIndex(current);//更新数据映射的行号

    bool first = (current.row() == 0); //是否首记录
    bool last = (current.row() == m_pQryModel->rowCount() - 1);//是否尾记录

    int curRecNo = m_pQrySelection->currentIndex().row();
    QSqlRecord  curRec = m_pQryModel->record(curRecNo); //获取当前记录
    int id = curRec.value("id").toInt();

}


void selectWidget::tabSelection_currentChanged(const QModelIndex& current, const QModelIndex& previous)
{
    //更新actPost和actCancel 的状态
    Q_UNUSED(current);
    Q_UNUSED(previous);
}


void selectWidget::tabSelection_currentRowChanged(const QModelIndex& current, const QModelIndex& previous)
{
    Q_UNUSED(previous);
    // 行切换时的状态控制

    m_pTabDataMapper->setCurrentIndex(current.row()); //更细数据映射的行号

    int curRecNo = current.row();//获取行号
    QSqlRecord  curRec = m_pTabModel->record(curRecNo); //获取当前记录

}




selectWidget::~selectWidget()
{
    delete ui;
}




QStringList getlist(QComboBox  *Q1){
    QStringList q1 = {};
    int n1 ;
    for( n1 = 0;n1<Q1->count();n1++){
        q1.push_back(Q1->itemText(n1));
    }
    return q1;
}

void selectWidget::on_reset_clicked()
{
    /*
    combobox:
                    addItems();
                    addItem();
                    clear();
                    setItemText(index,QString);
                    currentIndex();
                    currentText();
                    itemText(int);
                    insertItem( , );
                    insertItems( , );

*/
    QList<QCheckBox *>mylist = {ui->checkid,ui->checkname,ui->checktime,ui->checkthing,ui->checkmoney,ui->checkcompany,ui->checkconnect,ui->checkphone,ui->checknum,ui->checkoperator,ui->checkfeiliao,ui->checkwater,ui->checkgrowth,ui->checkothers};
    for (int i = 0;i<mylist.length();i++) {
        mylist[i]->setCheckState(Qt::Unchecked);
    }
    QList<std::pair<bool,int>> res = gethiden();
    for (int i = 0;i<res.length();i++) {
        ui->tableView->setColumnHidden(res[i].second,false);
    }

    //隐藏地理位置
    ui->tableView->setColumnHidden(5,true);
    ui->tableView->setColumnHidden(6,true);
    ui->tableView->setColumnHidden(7,true);
    ui->tableView->setColumnHidden(8,true);

    QStringList q1 = getlist(ui->num);
    ui->num->clear();
    ui->num->addItems(q1);

    QStringList q2 = getlist(ui->id);
    ui->id->clear();
    ui->id->addItems(q2);

    QStringList q3 = getlist(ui->company);
    ui->company->clear();
    ui->company->addItems(q3);


    QStringList q4 = getlist(ui->contacts);
    ui->contacts->clear();
    ui->contacts->addItems(q4);


    QStringList q5 = getlist(ui->feiliao);
    ui->feiliao->clear();
    ui->feiliao->addItems(q5);

    QStringList q6 = getlist(ui->growth);
    ui->growth->clear();
    ui->growth->addItems(q6);

    QStringList q7 = getlist(ui->money);
    ui->money->clear();
    ui->money->addItems(q7);

    QStringList q8 = getlist(ui->operater);
    ui->operater->clear();
    ui->operater->addItems(q8);

    QStringList q9 = getlist(ui->phone);
    ui->phone->clear();
    ui->phone->addItems(q9);

    QStringList q10 = getlist(ui->thing);
    ui->thing->clear();
    ui->thing->addItems(q10);

    QStringList q11 = getlist(ui->water);
    ui->water->clear();
    ui->water->addItems(q11);

    QStringList q12 = getlist(ui->flowername);
    ui->flowername->clear();
    ui->flowername->addItems(q12);
    qDebug()<<"用户 " << Global::username<<" 重置查询面板"<<endl;

}


QList<std::pair<bool,int>> selectWidget::gethiden(){
    //          0                   1                   2                       3                       4                       5                               6                       7               8                                   9                   10                      11                  12                      13
    QList<QCheckBox *>mylist = {ui->checkid,ui->checkname,ui->checktime,ui->checkthing,ui->checkmoney,ui->checkcompany,ui->checkconnect,ui->checkphone,ui->checknum,ui->checkoperator,ui->checkfeiliao,ui->checkwater,ui->checkgrowth,ui->checkothers};
    QList<bool>state;
    QList<std::pair<bool,int>> res;
    for (int i = 0;i<mylist.length();i++) {
        if(mylist[i]->isChecked())
            state.push_back(true);
        else
            state.push_back(false);
    }
    for (int i = 0;i<5;i++) {
        res.push_back(std::make_pair(state[i],i));
    }
    for(int i = 9;i<13;i++){
        res.push_back(std::make_pair(state[i-4],i));
    }
    for (int i = 15;i<20;i++) {
        res.push_back(std::make_pair(state[i-6],i));

    }
    return res;

}


void selectWidget::on_viewtab_clicked()
{

    QString basesql =  "SELECT * FROM flower_info ORDER By id ASC ";

    m_pQryModel->setQuery(basesql,this->db);
    ui->tableView->setModel(m_pQryModel);
    sethead();
    ui->tableView->setSelectionModel(m_pQrySelection);
    /*
    m_pTabModel->setTable("flower_info");
    m_pTabModel->select();
       m_pTabModel->sort(0,Qt::AscendingOrder);//升

       ui->tableView->setModel(m_pTabModel);//设置数据模型
       ui->tableView->setSelectionModel(m_pTabSelection); //设置选择模型
//数据表列名从0 开始 ---建立列索引和是否勾选的对应
*/
    //校验隐藏信息
    QList<std::pair<bool,int>> res = gethiden();
    for (int i = 0;i<res.length();i++) {
        if(res[i].first){
            ui->tableView->setColumnHidden(res[i].second,true);
        }
    }

    //隐藏地理位置
    ui->tableView->setColumnHidden(5,true);
    ui->tableView->setColumnHidden(6,true);
    ui->tableView->setColumnHidden(7,true);
    ui->tableView->setColumnHidden(8,true);

    // model->select();
    // model->sort(0,Qt::DescendingOrder);//降
    //   model->sort(0,Qt::AscendingOrder);//升

    qDebug()<<"用户 " << Global::username<<" 浏览全表"<<endl;

}

QList<std::pair<QString,QString>> selectWidget:: getalltext(){
    QList<QComboBox *>mylist = {ui->id,ui->flowername,ui->thing,ui->money,ui->company,ui->contacts,ui->phone,ui->num,ui->operater,ui->feiliao,ui->water,ui->growth,ui->others};

    //种植时间单列处理
    //QList<QString> title = {"编号", "花种","种植时间","农事","农资","单位","联系人","联系方式","数量","操作人员","施肥情况","浇水情况","生长情况","备注"};
    QList<QString> title = {"id",	"type","farming"	,"nongzi",		"company",	"contactPerson",	"contactNum","quantity","operator"	,"fertilization",	"watering",	"growth",	"remark"
                           };

    //  QList<QString> title = {"编号", "花种","农事","农资","单位","联系人","联系方式","数量","操作人员","施肥情况","浇水情况","生长情况","备注"};

    //数据表的列名 + 要索引的值
    QList<std::pair<QString,QString>> text;
    QString t = ui->starttime->date().toString("yyyy/MM/dd");
    if(t != "" && ui->checkBox->checkState()){
        text.push_back(std::make_pair(" plantTime",t));
    }
    for(int i = 0;i<mylist.length();i++){
        QString tmp = mylist[i]->currentText() ;
        if(tmp !=""){
            text.push_back(std::make_pair(title[i],tmp));
        }
    }
    //qDebug()<<text;
    return text;
}

void selectWidget::on_test_clicked()
{
    getalltext();
}


void selectWidget::refreshTableView()
{
    //刷新tableView的当前选择行
    int index = m_pQryDataMapper->currentIndex();
    QModelIndex curIndex = m_pQryModel->index(index, 1);//
    m_pQrySelection->clearSelection();//清空选择项
    m_pQrySelection->setCurrentIndex(curIndex, QItemSelectionModel::Select);//设置刚插入的行为当前选择行
}


//首记录
void selectWidget::on_firstrecord_clicked()
{
    ui->tableView->selectRow(0);
    qDebug()<<"用户 " << Global::username<<" 查看当前首记录"<<endl;

}

void selectWidget::on_lastrecord_clicked()
{
    int r = ui->tableView->model()->rowCount();
    //qDebug()<<r;
    ui->tableView->selectRow(r-1);
    qDebug()<<"用户 " << Global::username<<" 查看当尾记录"<<endl;

}

void selectWidget::on_preitem_clicked()
{
    int cur=ui->tableView->currentIndex().row(); //选中行
    if(cur!=0)
        ui->tableView->selectRow(cur-1);
    else
        ui->tableView->selectRow(0);
    qDebug()<<"用户 " << Global::username<<" 查看上一行"<<endl;

}

void selectWidget::on_nextitem_clicked()
{
    int r = ui->tableView->model()->rowCount();
    int cur=ui->tableView->currentIndex().row(); //选中行
    if(cur!=r-1)
        ui->tableView->selectRow(cur+1);
    else
        ui->tableView->selectRow(r-1);
    qDebug()<<"用户 " << Global::username<<" 查看下一行"<<endl;

}




//依靠查询项进行选择
void selectWidget::on_excelout_clicked()
{
    QList<std::pair<QString,QString>> res =  getalltext();
    QDateTime date = QDateTime::currentDateTime();
    QString basefilename = date.toString("yyyy-MM-dd");
    QString filename;
    if(res.length() == 0)
        filename = basefilename + QString("-全部");
    else{
        filename = basefilename;
        for (int i = 0;i<res.length();i++) {
            filename += QString("-")+ res[i].second;
        }
    }
    QString filepath = QFileDialog::getSaveFileName(this, tr("Save as..."),
                                                    filename, tr("EXCEL files (*.xls);;HTML-Files (*.txt);;"));
    //设置导出文件名！！！
    // 文件导出时间 + 导出项 + 操作人
    //获取当前时间 ：
    //获取导出文件项：

    if (filepath != "")
    {
        int row = ui->tableView->model()->rowCount();
        int col = ui->tableView->model()->columnCount();
        QList<QString> list;
        //添加列标题
        QString HeaderRow;
        for (int i = 0; i < col; i++)
        {
            HeaderRow.append(ui->tableView->model()->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\t");
        }
        list.push_back(HeaderRow);
        for (int i = 0; i < row; i++)
        {
            QString rowStr = "";
            for (int j = 0; j < col; j++){
                QModelIndex index = ui->tableView->model()->index(i, j);
                rowStr += ui->tableView->model()->data(index).toString() + "\t";
            }
            list.push_back(rowStr);
        }
        QTextEdit textEdit;
        for (int i = 0; i < list.size(); i++)
        {
            textEdit.append(list.at(i));
        }

        QFile file(filepath);
        if (file.open(QFile::WriteOnly | QIODevice::Text))
        {
            QTextStream ts(&file);
            ts.setCodec("GB2312");//判断是否用“utf-8”
            //  ts.setCodec("utf-8");
            ts << textEdit.document()->toPlainText();
            file.close();
            qDebug()<<"用户 " << Global::username<<" 选择导出查询excel文件,导出文件路径为："<<filepath<<"  导出文件名为   "<<filename<<endl;

            QMessageBox::information(this, tr("success"),tr("文件导出成功！") );

        }else{
            qDebug()<<"用户 " << Global::username<<"查询数据导出失败";
            QMessageBox::information(this, tr("fail"),tr("文件导出失败！") );

        }
    }
}

void selectWidget::on_printpdf_clicked()
{
    QList<std::pair<QString,QString>> res =  getalltext();
    QDateTime date = QDateTime::currentDateTime();
    QString basefilename = date.toString("yyyy-MM-dd");
    QString filename;
    if(res.length() == 0)
        filename = basefilename + QString("-全部");
    else{
        filename = basefilename;
        for (int i = 0;i<res.length();i++) {
            filename += QString("-")+ res[i].second;
        }
    }
    QString fileName = QFileDialog::getSaveFileName(this, tr("保存PDF文件"), filename, "*.pdf");
    if (!fileName.isEmpty())
    {
        // 如果文件后缀为空，则默认使用.pdf
        if (QFileInfo(fileName).suffix().isEmpty())
        {
            fileName.append(".pdf");
        }
        QPrinter printerPixmap(QPrinter::HighResolution);
        //自定义纸张大小，这里要打印的内容都在stackedWidget上
        printerPixmap.setPageSize(QPrinter::Custom);
        printerPixmap.setPaperSize(QSizeF(ui->tableView->height(), ui->tableView->width()), QPrinter::Point);
        //设置纸张大小为A4，这里注释掉了，建议自定义纸张 ，否则保存的就会有很多空白
        //printerPixmap.setPageSize(QPrinter::A4);
        //横向打印
        printerPixmap.setOrientation(QPrinter::Landscape);
        //设置输出格式为pdf
        printerPixmap.setOutputFormat(QPrinter::PdfFormat);
        //设置输出路径
        printerPixmap.setOutputFileName(fileName);
        //获取界面的图片
        QPixmap pixmap = QPixmap::grabWidget(ui->tableView, ui->tableView->rect());

        QPainter painterPixmap;
        painterPixmap.begin(&printerPixmap);
        QRect rect = painterPixmap.viewport();
        int x = rect.width() / pixmap.width();
        int y = rect.height() / pixmap.height();
        //将图像(所有要画的东西)在pdf上按比例尺缩放
        painterPixmap.scale(x, y);
        //画图
        painterPixmap.drawPixmap(0, 0, pixmap);
        painterPixmap.end();
        qDebug()<<"用户 " << Global::username<<" 选择导出查询pdf文件,导出文件路径为："<<"  导出文件名为   "<<filename<<endl;

        QMessageBox::information(this, tr("生成PDF"), tr("保存PDF文件成功"), QMessageBox::Ok);
    }

}

void selectWidget::on_checkid_clicked()
{
    if(ui->checkid->isChecked())
        ui->tableView->setColumnHidden(0,true);
    else
        ui->tableView->setColumnHidden(0,false);

}

void selectWidget::on_checkname_clicked()
{
    if(ui->checkname->isChecked())
        ui->tableView->setColumnHidden(1,true);
    else
        ui->tableView->setColumnHidden(1,false);

}

void selectWidget::on_checktime_clicked()
{
    if(ui->checktime->isChecked())
        ui->tableView->setColumnHidden(2,true);
    else
        ui->tableView->setColumnHidden(2,false);

}

void selectWidget::on_checkthing_clicked()
{
    if(ui->checkthing->isChecked())
        ui->tableView->setColumnHidden(3,true);
    else
        ui->tableView->setColumnHidden(3,false);

}

void selectWidget::on_checkmoney_clicked()
{
    if(ui->checkmoney->isChecked())
        ui->tableView->setColumnHidden(4,true);
    else
        ui->tableView->setColumnHidden(4,false);
}

void selectWidget::on_checkcompany_clicked()
{
    if(ui->checkcompany->isChecked())
        ui->tableView->setColumnHidden(9,true);
    else
        ui->tableView->setColumnHidden(9,false);
}

void selectWidget::on_checkconnect_clicked()
{
    if(ui->checkconnect->isChecked())
        ui->tableView->setColumnHidden(10,true);
    else
        ui->tableView->setColumnHidden(10,false);
}

void selectWidget::on_checkphone_clicked()
{
    if(ui->checkphone->isChecked())
        ui->tableView->setColumnHidden(11,true);
    else
        ui->tableView->setColumnHidden(11,false);
}

void selectWidget::on_checknum_clicked()
{
    if(ui->checknum->isChecked())
        ui->tableView->setColumnHidden(12,true);
    else
        ui->tableView->setColumnHidden(12,false);
}

void selectWidget::on_checkoperator_clicked()
{
    if(ui->checkoperator->isChecked())
        ui->tableView->setColumnHidden(15,true);
    else
        ui->tableView->setColumnHidden(15,false);
}

void selectWidget::on_checkfeiliao_clicked()
{
    if(ui->checkfeiliao->isChecked())
        ui->tableView->setColumnHidden(16,true);
    else
        ui->tableView->setColumnHidden(16,false);
}

void selectWidget::on_checkwater_clicked()
{
    if(ui->checkwater->isChecked())
        ui->tableView->setColumnHidden(17,true);
    else
        ui->tableView->setColumnHidden(17,false);

}

void selectWidget::on_checkgrowth_clicked()
{
    if(ui->checkgrowth->isChecked())
        ui->tableView->setColumnHidden(18,true);
    else
        ui->tableView->setColumnHidden(18,false);
}

void selectWidget::on_checkothers_clicked()
{
    if(ui->checkothers->isChecked())
        ui->tableView->setColumnHidden(19,true);
    else
        ui->tableView->setColumnHidden(19,false);
}

void selectWidget::on_printpdf_2_clicked()
{
    //www1 = new Widget();
    www1.show();
    qDebug()<<"用户 " << Global::username<<" 选择发送文件"<<endl;

}


void selectWidget::on_del_clicked()
{
    //1 为管理员
    //0 为用户
    if(Global::type =="1"){
        //DELETE FROM 表名 WHERE 字段1 = ‘' and 字段2 = ‘' and
        if( ui->id->currentText() !=""){

            QString id = ui->id->currentText();

            QList<std::pair<QString,QString>> res =  getalltext();
            QString basesql =  "DELETE FROM  flower_info WHERE  id  = " +  id ;

            QSqlQuery query;
            //插入花卉信息
            query.prepare(basesql);
            query.exec();
            qDebug()<<"管理员 " << Global::username<<" 选择删除记录，删除的sql语句为 ："<< basesql<<endl;

            QMessageBox::information(this,"success","删除成功");
        }else{
            qDebug()<<"管理员 " << Global::username<<" 选择删除记录，但未选择要删除的行"<<endl;

            QMessageBox::information(this,"info","请输入要删除花卉的id信息");
        }

    }else{
        qDebug()<<"用户 " << Global::username<<" 选择删除记录，越权操作！"<<endl;

        QMessageBox::warning(this, tr("waring"),tr("删除数据请联系管理员！") );

    }
}
