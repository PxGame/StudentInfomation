#ifndef DETAILSINFO_H
#define DETAILSINFO_H

#include <QWidget>
# include <QLineEdit>
# include <QPushButton>
# include <QLabel>
# include <QTextEdit>
# include <QHBoxLayout>
# include <QVBoxLayout>
# include <QGridLayout>
# include <QPixmap>
# include <QByteArray>
# include <QVariant>
# include <QBuffer>
# include <QMessageBox>
# include <QFileDialog>

# include <QSqlDatabase>
# include <QSqlDriver>
# include <QSqlError>
# include <QSqlQuery>

class DetailsInfo : public QWidget
{
    Q_OBJECT
public:
    DetailsInfo(QSqlDatabase *base, QWidget *parent = 0);
public:
    QLabel *titleLb;
    //simpleInfo-----------------------------------
    QLabel *numberLb;
    QLineEdit *numberLe;
    QLabel *nameLb;
    QLineEdit *nameLe;
    QLabel *sexLb;
    QLineEdit *sexLe;
    QLabel *schoolNameLb;
    QLineEdit *schoolNameLe;
    QLabel *departmentNameLb;
    QLineEdit *departmentNameLe;
    QLabel *majorNameLb;
    QLineEdit *majorNameLe;
    QLabel *classNameLb;
    QLineEdit *classNameLe;
    QLabel *educationLb;
    QLineEdit *educationLe;
    QLabel *phoneNumberLb;
    QLineEdit *phoneNumberLe;

    //photo
    QLabel *photoLb;
    QPushButton *photoAlterBtn;
    QVBoxLayout *photoLayout;

    //detailsInfo-----------------------------------
    QLabel *nationLb;
    QLineEdit *nationLe;
    QLabel *nationPlaceLb;
    QLineEdit *nationPlaceLe;
    QLabel *addressLb;
    QLineEdit *addressLe;
    QLabel *birthdayLb;
    QLineEdit *birthdayLe;
    QLabel *politicalLb;
    QLineEdit *politicalLe;
    QLabel *languageLevelLb;
    QLineEdit *languageLevelLe;
    QLabel *qqNumberLb;
    QLineEdit *qqNumberLe;
    QLabel *emailLb;
    QLineEdit *emailLe;
    QLabel *remarkLb;
    QTextEdit *remarkTe;

    QGridLayout *InfoLayout;

    //button-----------------------------------------
    QPushButton *returnBtn;
    QPushButton *repealBtn;
    QPushButton *alterOkBtn;
    QPushButton *cancelBtn;

    QHBoxLayout *btnLayout;

    //main-------------------------------------------
    QVBoxLayout *mainLayout;

private:
    QString numberInfo;
    QSqlDatabase *base;
public:
    void loadInfoWidget();
    void loadBtnWidget();
    void setReadOnly(bool mode = true);
    void setInfo(QString number);//通过主键学号查找学生所有相关信息
    void clear();//清除所有显示的数据


signals:
    void alterDetailsInfo();

public slots:
    void actionAlterClicked();
    void returnBtnClicked();
    void repealBtnClicked();
    void alterOkBtnClicked();
    void cancelBtnClicked();
    void photoAlterBtnClicked();
};

#endif // DETAILSINFO_H
