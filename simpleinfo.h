#ifndef SIMPLEINFO_H
#define SIMPLEINFO_H

#include <QWidget>
# include <QLabel>
# include <QComboBox>
# include <QLineEdit>
# include <QPushButton>
# include <QTableView>
# include <QMessageBox>
# include <QFileDialog>
# include <QPixmap>
# include <QByteArray>
# include <QBuffer>

# include <QSqlDatabase>
# include <QSqlQuery>
# include <QSqlDriver>
# include <QSqlError>
# include <QSqlTableModel>

# include <QGridLayout>
# include <QHBoxLayout>
# include <QVBoxLayout>


class SimpleInfo : public QWidget
{
    Q_OBJECT
public:
    SimpleInfo(QSqlDatabase *base, QWidget *parent = 0);
    ~SimpleInfo();

public://layout
    QVBoxLayout *mainLayout;

    QHBoxLayout *selectLayout;
    QLabel *selectLb;
    QComboBox *selectCb;
    QLineEdit *selectLe;
    QPushButton *selectBtn;
    QPushButton *selectQuitBtn;

    QHBoxLayout *infoLayout;
    QTableView *tableView;
    QSqlTableModel *tableMode;

    QVBoxLayout *photolayout;
    QLabel *photoLb;
    QLabel *photoNameLb;
    QLabel *photoNumberLb;
    QPushButton *photoAlterBtn;

    QHBoxLayout *btnLayout;
    QPushButton *btnAdd;
    QPushButton *btnDelete;
    QPushButton *btnRepeal;
    QPushButton *btnALterOk;
    QPushButton *btnCancel;

public slots:
    void selectBtnClicked();
    void selectQuitBtnClicked();
    void photoAlterBtnClicked();
    void actionAlterClicked();
    void btnRepealClicked();
    void btnAlterOkClicked();
    void btnCancelClicked();
    void btnAddClicked();
    void btnDeleteClicked();

    void tableViewSelect(QModelIndex index);

private:
    QSqlDatabase *base;

private:
    void loadSelectWidget();
    void loadInfoWidget();
    void loadBtnWidget();

public:
    void loadDataBase();


signals:
    void alterSimpleInfo();//修改Simple表内容
public slots:

};

#endif // SIMPLEINFO_H
