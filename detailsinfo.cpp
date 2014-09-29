#include "detailsinfo.h"

DetailsInfo::DetailsInfo(QWidget *parent) :
    QWidget(parent)
{
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
    birthdayDe->setReadOnly(mode);
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
//----------------------------------------------------------------------------------------
void DetailsInfo::loadInfoWidget()
{
    //simple
    numberLb = new QLabel(tr("学号"));
    numberLe = new QLineEdit();
    nameLb = new QLabel(tr("姓名"));
    nameLe = new QLineEdit();
    sexLb = new QLabel(tr("性别"));
    sexLe = new QLineEdit();
    schoolNameLb = new QLabel(tr("学校"));
    schoolNameLe = new QLineEdit();
    departmentNameLb = new QLabel(tr("系"));
    departmentNameLe = new QLineEdit();
    majorNameLb = new QLabel(tr("专业"));
    majorNameLe = new QLineEdit();
    classNameLb = new QLabel(tr("班级"));
    classNameLe = new QLineEdit();
    educationLb = new QLabel(tr("教育等级"));
    educationLe = new QLineEdit();
    phoneNumberLb = new QLabel(tr("电话"));
    phoneNumberLe = new QLineEdit();

    //details
    nationLb = new QLabel(tr("民族"));
    nationLe = new QLineEdit();
    nationPlaceLb = new QLabel(tr("籍贯"));
    nationPlaceLe = new QLineEdit();
    addressLb = new QLabel(tr("地址"));
    addressLe = new QLineEdit();
    birthdayLb = new QLabel(tr("出生日期"));
    birthdayDe = new QDateEdit();
    politicalLb = new QLabel(tr("政治面貌"));
    politicalLe = new QLineEdit();
    languageLevelLb = new QLabel(tr("外语等级"));
    languageLevelLe = new QLineEdit();
    qqNumberLb = new QLabel(tr("QQ号码"));
    qqNumberLe = new QLineEdit();
    emailLb = new QLabel(tr("电子邮件"));
    emailLe = new QLineEdit();
    remarkLb = new QLabel(tr("备注"));
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
    InfoLayout->addWidget(birthdayDe, 6, 3);
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

}

void DetailsInfo::repealBtnClicked()
{

}

void DetailsInfo::alterOkBtnClicked()
{

}

void DetailsInfo::cancelBtnClicked()
{

}
//----------------------------------------------------------------------------------------

