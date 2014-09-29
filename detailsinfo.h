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

class DetailsInfo : public QWidget
{
    Q_OBJECT
public:
    DetailsInfo(QWidget *parent = 0);
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

public:
    void loadInfo();
    void loadBtn();


signals:
    void alterDetailsInfo();

public slots:
    void actionAlterClicked();

};

#endif // DETAILSINFO_H
