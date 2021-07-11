

#ifndef SELECTWIDGET_H
#define SELECTWIDGET_H

#include <QWidget>

#include<QSqlQuery>
#include<QSqlTableModel>
#include<QItemSelectionModel>
#include<QDataWidgetMapper>
#include"widget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class selectWidget; }
QT_END_NAMESPACE

class selectWidget : public QWidget
{
    Q_OBJECT

public:
    selectWidget(QWidget *parent = nullptr);
    ~selectWidget();

    QList<std::pair<QString,QString>> getalltext();

    QSqlQuery *query;
    void on_test_clicked();

//QSqlTableModel * model;

QSqlDatabase  db;//数据库连接
QSqlTableModel* m_pTabModel;  //数据模型
QItemSelectionModel* m_pTabSelection; //选择模型
QDataWidgetMapper* m_pTabDataMapper; //数据映射

QSqlQueryModel* m_pQryModel; //数据模型
QItemSelectionModel* m_pQrySelection; //选择模型
QDataWidgetMapper* m_pQryDataMapper; //数据映射

private slots:


    void on_reset_clicked();

    void on_selectbth_clicked();

    void on_viewtab_clicked();

    //QTableView的SelectionModel的行发生了变化，进行处理
    void qrySelection_currentRowChanged(const QModelIndex& current, const QModelIndex& previous);
void tabSelection_currentChanged(const QModelIndex& current, const QModelIndex& previous);
void tabSelection_currentRowChanged(const QModelIndex& current, const QModelIndex& previous);

void comboFields_currentIndexChanged(int index);

void  radioBtnAscend_clicked();
void radioBtnDescend_clicked();
void refreshTableView();



void on_firstrecord_clicked();



void on_lastrecord_clicked();

void on_preitem_clicked();

void on_nextitem_clicked();

void on_mohuselect_clicked();

void on_excelout_clicked();

 QList<std::pair<bool,int>> gethiden();
 void on_printpdf_clicked();

 void on_checkid_clicked();

 void on_checkname_clicked();

 void on_checktime_clicked();

 void on_checkthing_clicked();

 void on_checkmoney_clicked();

 void on_checkcompany_clicked();

 void on_checkconnect_clicked();

 void on_checkphone_clicked();

 void on_checknum_clicked();

 void on_checkoperator_clicked();

 void on_checkfeiliao_clicked();

 void on_checkwater_clicked();

 void on_checkgrowth_clicked();

 void on_checkothers_clicked();

 void sethead();
 void on_printpdf_2_clicked();

 void on_shouge_clicked();

 void on_gengxin_clicked();

 void on_del_clicked();

private:
    Ui::selectWidget *ui;
    Widget  www1;
};
#endif // SELECTWIDGET_H
