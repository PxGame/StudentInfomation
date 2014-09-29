#include "detailsinfo.h"

DetailsInfo::DetailsInfo(QSqlDatabase *base, QWidget *parent) :
    QWidget(parent)
{
    this->base = base;//使用打开的数据库
    if (!base->isOpen())
    {
        if(!base->open())
        {
            QMessageBox::about(this, tr("error"), tr("DetailsInfo::DetailsInfo(QSqlDatabase *base, QWidget *parent)"));
            return;
        }
    }

    loadInfoWidget();//1
    loadBtnWidget();//2

    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(InfoLayout);
    mainLayout->addLayout(btnLayout);

    this->setReadOnly(true);

    connect(this, SIGNAL(alterDetailsInfo()),
            this, SLOT(actionAlterClicked()));
}

void DetailsInfo::actionAlterClicked()
{
    this->setReadOnly(false);
}

void DetailsInfo::setReadOnly(bool mode)
{
    //simple
    numberLe->setReadOnly(mode);
    nameLe->setReadOnly(mode);
    sexLe->setReadOnly(mode);
    schoolNameLe->setReadOnly(mode);
    departmentNameLe->setReadOnly(mode);
    majorNameLe->setReadOnly(mode);
    classNameLe->setReadOnly(mode);
    educationLe->setReadOnly(mode);
    phoneNumberLe->setReadOnly(mode);

    //details
    nationLe->setReadOnly(mode);
    nationPlaceLe->setReadOnly(mode);
    addressLe->setReadOnly(mode);
    birthdayLe->setReadOnly(mode);
    politicalLe->setReadOnly(mode);
    languageLevelLe->setReadOnly(mode);
    qqNumberLe->setReadOnly(mode);
    emailLe->setReadOnly(mode);
    remarkTe->setReadOnly(mode);

    //photo
    photoAlterBtn->setHidden(mode);

    //btn
    returnBtn->setHidden(!mode);
    repealBtn->setHidden(mode);
    alterOkBtn->setHidden(mode);
    cancelBtn->setHidden(mode);
}

void DetailsInfo::setInfo(QString number)
{
    if (!base->isOpen())
    {
        QMessageBox::about(this, tr("error"), tr("void DetailsInfo::setInfo(QString number)"));
        return;
    }

    numberInfo = number;//备份显示的信息的主键

    QSqlQuery query;
    //---------------------------------------------------------------------------------------------------------
    bool ok = query.exec(tr("select 学号,姓名,性别,学校,系,专业,班级,教育等级,电话 "
                            "from studentInfo "
                            "where 学号 = '%1'").arg(numberInfo));
    if (ok == false)
    {
        QMessageBox::about(this, tr("error"), tr("void DetailsInfo::setInfo(QString number)\n studentInfo is query error"));
        return;
    }
    if (query.next())
    {
        //simple
        numberLe->setText(query.value(tr("学号")).toString());
        nameLe->setText(query.value(tr("姓名")).toString());
        sexLe->setText(query.value(tr("性别")).toString());
        schoolNameLe->setText(query.value(tr("学校")).toString());
        departmentNameLe->setText(query.value(tr("系")).toString());
        majorNameLe->setText(query.value(tr("专业")).toString());
        classNameLe->setText(query.value(tr("班级")).toString());
        educationLe->setText(query.value(tr("教育等级")).toString());
        phoneNumberLe->setText(query.value(tr("电话")).toString());
    }
    query.clear();
    //---------------------------------------------------------------------------------------------------------
    ok = query.exec(tr("select 民族,籍贯,住址,出生日期,政治面貌,外语等级,QQ号码,电子邮箱,备注 "
                       "from studentDetailsInfo "
                       "where 学号 = '%1'").arg(numberInfo));
    if (ok == false)
    {
        QMessageBox::about(this, tr("error"), tr("void DetailsInfo::setInfo(QString number)\n studentDetailsInfo is query error"));
        return;
    }
    if (query.next())
    {
        //details
        nationLe->setText(query.value(tr("民族")).toString());
        nationPlaceLe->setText(query.value(tr("籍贯")).toString());
        addressLe->setText(query.value(tr("住址")).toString());
        birthdayLe->setText(query.value(tr("出生日期")).toString());
        politicalLe->setText(query.value(tr("政治面貌")).toString());
        languageLevelLe->setText(query.value(tr("外语等级")).toString());
        qqNumberLe->setText(query.value(tr("QQ号码")).toString());
        emailLe->setText(query.value(tr("电子邮箱")).toString());
        remarkTe->setText(query.value(tr("备注")).toString());
    }
    query.clear();
    //---------------------------------------------------------------------------------------------------------
    ok = query.exec(tr("select 照片 "
                       "from studentImage "
                       "where 学号 = '%1'").arg(numberInfo));
    if (ok == false)
    {
        QMessageBox::about(this, tr("error"), tr("void DetailsInfo::setInfo(QString number)\n studentImage is query error"));
        return;
    }
    if (query.next())
    {
        //photo
        QPixmap pix;
        pix.loadFromData(query.value(tr("照片")).toByteArray());
        photoLb->setPixmap(pix);
    }
}

void DetailsInfo::clear()
{
    //simple
    numberLe->clear();
    nameLe->clear();
    sexLe->clear();
    schoolNameLe->clear();
    departmentNameLe->clear();
    majorNameLe->clear();
    classNameLe->clear();
    educationLe->clear();
    phoneNumberLe->clear();

    //details
    nationLe->clear();
    nationPlaceLe->clear();
    addressLe->clear();
    birthdayLe->clear();
    politicalLe->clear();
    languageLevelLe->clear();
    qqNumberLe->clear();
    emailLe->clear();
    remarkTe->clear();

    //photo
    photoLb->clear();
}
//----------------------------------------------------------------------------------------
void DetailsInfo::loadInfoWidget()
{
    //simple
    numberLb = new QLabel(tr("学号："));
    numberLe = new QLineEdit();
    nameLb = new QLabel(tr("姓名："));
    nameLe = new QLineEdit();
    sexLb = new QLabel(tr("性别："));
    sexLe = new QLineEdit();
    schoolNameLb = new QLabel(tr("学校："));
    schoolNameLe = new QLineEdit();
    departmentNameLb = new QLabel(tr("系："));
    departmentNameLe = new QLineEdit();
    majorNameLb = new QLabel(tr("专业："));
    majorNameLe = new QLineEdit();
    classNameLb = new QLabel(tr("班级："));
    classNameLe = new QLineEdit();
    educationLb = new QLabel(tr("教育等级："));
    educationLe = new QLineEdit();
    phoneNumberLb = new QLabel(tr("电话："));
    phoneNumberLe = new QLineEdit();

    //details
    nationLb = new QLabel(tr("民族："));
    nationLe = new QLineEdit();
    nationPlaceLb = new QLabel(tr("籍贯："));
    nationPlaceLe = new QLineEdit();
    addressLb = new QLabel(tr("地址："));
    addressLe = new QLineEdit();
    birthdayLb = new QLabel(tr("出生日期："));
    birthdayLe = new QLineEdit();
    politicalLb = new QLabel(tr("政治面貌："));
    politicalLe = new QLineEdit();
    languageLevelLb = new QLabel(tr("外语等级："));
    languageLevelLe = new QLineEdit();
    qqNumberLb = new QLabel(tr("QQ号码："));
    qqNumberLe = new QLineEdit();
    emailLb = new QLabel(tr("电子邮箱："));
    emailLe = new QLineEdit();
    remarkLb = new QLabel(tr("备注："));
    remarkTe = new QTextEdit();

    remarkLb->setFixedHeight(remarkLb->minimumSizeHint().height());

    //photo
    photoLb = new QLabel();
    photoAlterBtn = new QPushButton(tr("选择"));
    photoLb->setFixedSize(120, 160);
    photoLb->setFrameStyle(QFrame::Sunken | QFrame::Panel);
    photoLayout = new QVBoxLayout();
    photoLayout->addWidget(photoLb);
    photoLayout->addWidget(photoAlterBtn);
    photoLayout->addStretch(1);

    //add widget------------------------------------------------------------
    InfoLayout = new QGridLayout();

    //simple
    InfoLayout->addWidget(numberLb, 0, 0);
    InfoLayout->addWidget(numberLe, 0, 1);
    InfoLayout->addWidget(nameLb, 1, 0);
    InfoLayout->addWidget(nameLe, 1, 1);
    InfoLayout->addWidget(sexLb, 2, 0);
    InfoLayout->addWidget(sexLe, 2, 1);
    InfoLayout->addWidget(educationLb, 3, 0);
    InfoLayout->addWidget(educationLe, 3, 1);
    InfoLayout->addWidget(phoneNumberLb, 4, 0);
    InfoLayout->addWidget(phoneNumberLe, 4, 1);

    InfoLayout->addWidget(schoolNameLb, 0, 2);
    InfoLayout->addWidget(schoolNameLe, 0, 3);
    InfoLayout->addWidget(departmentNameLb, 1, 2);
    InfoLayout->addWidget(departmentNameLe, 1, 3);
    InfoLayout->addWidget(majorNameLb, 2, 2);
    InfoLayout->addWidget(majorNameLe, 2, 3);
    InfoLayout->addWidget(classNameLb, 3, 2);
    InfoLayout->addWidget(classNameLe, 3, 3);

    //details
    InfoLayout->addWidget(nationLb, 6, 0);
    InfoLayout->addWidget(nationLe, 6, 1);
    InfoLayout->addWidget(nationPlaceLb, 7, 0);
    InfoLayout->addWidget(nationPlaceLe, 7, 1);
    InfoLayout->addWidget(addressLb, 8, 0);
    InfoLayout->addWidget(addressLe, 8, 1);
    InfoLayout->addWidget(qqNumberLb, 9, 0);
    InfoLayout->addWidget(qqNumberLe, 9, 1);

    InfoLayout->addWidget(birthdayLb, 6, 2);
    InfoLayout->addWidget(birthdayLe, 6, 3);
    InfoLayout->addWidget(politicalLb, 7, 2);
    InfoLayout->addWidget(politicalLe, 7, 3);
    InfoLayout->addWidget(languageLevelLb, 8, 2);
    InfoLayout->addWidget(languageLevelLe, 8, 3);
    InfoLayout->addWidget(emailLb, 9, 2);
    InfoLayout->addWidget(emailLe, 9, 3);

    InfoLayout->addWidget(remarkLb, 10, 0, 1, 5);
    InfoLayout->addWidget(remarkTe, 11, 0, 1, 5);

    //photo
    InfoLayout->addLayout(photoLayout, 0, 4, 9, 1);

    connect(photoAlterBtn, SIGNAL(clicked()),
            this, SLOT(photoAlterBtnClicked()));
}

void DetailsInfo::photoAlterBtnClicked()
{
    QString filePath;
    QPixmap pix;
    filePath = QFileDialog::getOpenFileName(this, tr("选择照片"), "/",
                                            tr("所有照片 (*.jpg *.png *.bmp);;JPG 照片 (*.jpg);;PNG 照片 (*.png);;BMP 照片 (*.bmp)"));
    if(!pix.load(filePath))
    {
        QMessageBox::about(this, tr("错误"), tr("照片选择失败！"));
        return;
    }
    if(pix.size() != photoLb->size())
    {
        QMessageBox::about(this, tr("提示"), tr("选择的照片大小不符合规定(宽：%1、高：%2）。\n将被自动缩放。").
                           arg(photoLb->size().width()).arg(photoLb->size().height()));
    }
    photoLb->setPixmap(pix.scaled(photoLb->size()));
}

//----------------------------------------------------------------------------------------
void DetailsInfo::loadBtnWidget()
{
    returnBtn = new QPushButton(tr("返回"));
    repealBtn = new QPushButton(tr("撤销"));
    alterOkBtn = new QPushButton(tr("提交"));
    cancelBtn = new QPushButton(tr("取消"));

    //add widget
    btnLayout = new QHBoxLayout();

    btnLayout->addStretch(1);
    btnLayout->addWidget(returnBtn);
    btnLayout->addWidget(repealBtn);
    btnLayout->addWidget(alterOkBtn);
    btnLayout->addWidget(cancelBtn);

    connect(returnBtn, SIGNAL(clicked()),
            this, SLOT(returnBtnClicked()));
    connect(repealBtn, SIGNAL(clicked()),
            this, SLOT(repealBtnClicked()));\
    connect(alterOkBtn ,SIGNAL(clicked()),
            this, SLOT(alterOkBtnClicked()));
    connect(cancelBtn, SIGNAL(clicked()),
            this, SLOT(cancelBtnClicked()));
}

void DetailsInfo::returnBtnClicked()
{
    this->clear();
}

void DetailsInfo::repealBtnClicked()
{
    this->setInfo(this->numberInfo);
}

void DetailsInfo::alterOkBtnClicked()
{
    if (!base->isOpen())
    {
        QMessageBox::about(this, tr("error"), tr("void DetailsInfo::setInfo(QString number)"));
        return;
    }

    if(QMessageBox::No == QMessageBox::information(this, tr("提示"), tr("确认提交"), QMessageBox::Yes, QMessageBox::No))
    {
        return;
    }

    QSqlQuery query;
    //------------------------------------------------------------------------------------------------------------------------------------
    int ok = query.prepare(tr("update studentInfo set 学号=?,姓名=?,性别=?,学校=?,系=?,专业=?,班级=?,教育等级=?,电话=? "
                     "where 学号=%1").arg(numberInfo));
    if (ok == false)
    {
        QMessageBox::about(this, tr("error"), tr("void DetailsInfo::alterOkBtnClicked()\nstudentInfo query is error"));
        return;
    }
    query.bindValue(0, numberLe->text().toInt());
    query.bindValue(1, nameLe->text());
    query.bindValue(2, sexLe->text());
    query.bindValue(3, schoolNameLe->text());
    query.bindValue(4, departmentNameLe->text());
    query.bindValue(5, majorNameLe->text());
    query.bindValue(6, classNameLe->text());
    query.bindValue(7, educationLe->text());
    query.bindValue(8, phoneNumberLe->text());
    if(!query.exec())
    {
        QMessageBox::about(this, tr("error"), tr("void DetailsInfo::alterOkBtnClicked()\nupdate studentInfo is error\n%1").arg(query.lastError().text()));
        return;
    }
    query.clear();

    //------------------------------------------------------------------------------------------------------------------------------------
    ok = query.prepare(tr("update studentDetailsInfo set 民族=?,籍贯=?,住址=?,出生日期=?,政治面貌=?,外语等级=?,QQ号码=?,电子邮箱=?,备注=? "
                     "where 学号=%1").arg(numberInfo));
    if (ok == false)
    {
        QMessageBox::about(this, tr("error"), tr("void DetailsInfo::alterOkBtnClicked()\nstudentDetailsInfo query is error"));
        return;
    }
    query.bindValue(0, nationLe->text());
    query.bindValue(1, nationPlaceLe->text());
    query.bindValue(2, addressLe->text());
    query.bindValue(3, birthdayLe->text());
    query.bindValue(4, politicalLe->text());
    query.bindValue(5, languageLevelLe->text());
    query.bindValue(6, qqNumberLe->text());
    query.bindValue(7, emailLe->text());
    query.bindValue(8, remarkTe->toPlainText());
    if(!query.exec())
    {
        QMessageBox::about(this, tr("error"), tr("void DetailsInfo::alterOkBtnClicked()\nupdate studentDetailsInfo is error\n%1").arg(query.lastError().text()));
        return;
    }
    query.clear();

    //------------------------------------------------------------------------------------------------------------------------------------
    const QPixmap *pix = photoLb->pixmap();
    if(pix != NULL && !pix->isNull())
    {
        QByteArray byte;
        QBuffer buf(&byte);
        buf.open(QIODevice::WriteOnly);
        if (!pix->save(&buf, "JPG"))
        {
            QMessageBox::about(this, tr("error"), tr("void DetailsInfo::alterOkBtnClicked()\nupdate studentImage is error\n%1").arg(query.lastError().text()));
        }
        buf.close();
        ok = query.prepare(tr("update studentImage set 照片=? "
                         "where 学号=%1").arg(numberInfo));
        if (ok == false)
        {
            QMessageBox::about(this, tr("error"), tr("void DetailsInfo::alterOkBtnClicked()\nstudentImage query is error"));
            return;
        }
        query.bindValue(0, byte);
        if(!query.exec())
        {
            QMessageBox::about(this, tr("error"), tr("void DetailsInfo::alterOkBtnClicked()\nupdate studentImage is error\n%1").arg(query.lastError().text()));
            return;
        }
    }
    this->setReadOnly(true);
}

void DetailsInfo::cancelBtnClicked()
{
    this->setInfo(this->numberInfo);
    this->setReadOnly(true);
}
//----------------------------------------------------------------------------------------

