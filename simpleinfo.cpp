#include "simpleinfo.h"

SimpleInfo::SimpleInfo(QSqlDatabase *base,QWidget *parent) :
    QWidget(parent)
{
    this->base = base;

    loadInfoWidget();//1
    loadBtnWidget();//2
    loadDataBase();//3
    loadSelectWidget();//4

    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(selectLayout);
    mainLayout->addLayout(infoLayout);
    mainLayout->addLayout(btnLayout);

    connect(this, SIGNAL(alterSimpleInfo()),
            this, SLOT(actionAlterClicked()));
}

SimpleInfo::~SimpleInfo()
{

}

//----------------------------------------------------------------------------------
void SimpleInfo::loadSelectWidget()
{
    selectLb = new QLabel(tr("查询："));
    selectCb = new QComboBox();
    selectLe = new QLineEdit();
    selectBtn = new QPushButton(tr("确定"));
    selectQuitBtn = new QPushButton(tr("取消"));
    selectLayout = new QHBoxLayout();

    selectLayout->addWidget(selectLb);
    selectLayout->addWidget(selectCb);
    selectLayout->addWidget(selectLe);
    selectLayout->addWidget(selectBtn);
    selectLayout->addWidget(selectQuitBtn);
    selectLayout->addStretch(1);

    QStringList itemList;
    itemList << "学号" << "姓名" << "性别"
             << "学校" << "系" << "专业"
             << "班级" << "教育等级" << "电话号码";
    selectCb->addItems(itemList);

    connect(selectBtn, SIGNAL(clicked()),
            this, SLOT(selectBtnClicked()));
    connect(selectQuitBtn, SIGNAL(clicked()),
            this, SLOT(selectQuitBtnClicked()));
}

void SimpleInfo::selectBtnClicked()
{
    tableMode->setFilter(tr("%1 = '%2'").
                         arg(selectCb->currentText()).
                         arg(selectLe->text()));
    tableMode->select();
}

void SimpleInfo::selectQuitBtnClicked()
{
    tableMode->setTable(tr("studentInfo"));
    tableMode->select();
}
//----------------------------------------------------------------------------------
void SimpleInfo::loadInfoWidget()
{
    tableView = new QTableView();
    tableMode = new QSqlTableModel();
    infoLayout = new QHBoxLayout();

    photoLb = new QLabel();
    photoNameLb = new QLabel();
    photoNumberLb = new QLabel();
    photoAlterBtn = new QPushButton(tr("选择"));
    photolayout = new QVBoxLayout();
    photolayout->addWidget(photoLb);
    photolayout->addWidget(photoNumberLb);
    photolayout->addWidget(photoNameLb);
    photolayout->addWidget(photoAlterBtn);
    photolayout->addStretch(1);

    infoLayout->addWidget(tableView);
    infoLayout->addLayout(photolayout);

    photoLb->setFixedSize(120, 160);//设置图片大小
    photoLb->setFrameStyle(QFrame::Sunken | QFrame::Panel);//设置图片边框
    photoNameLb->setAlignment(Qt::AlignCenter);
    photoNumberLb->setAlignment(Qt::AlignCenter);
    photoAlterBtn->setHidden(true);

    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(tableView, SIGNAL(pressed(QModelIndex)),
            this, SLOT(tableViewSelect(QModelIndex)));
    connect(tableView, SIGNAL(activated(QModelIndex)),
            this, SLOT(tableViewSelect(QModelIndex)));
    connect(photoAlterBtn, SIGNAL(clicked()),
            this, SLOT(photoAlterBtnClicked()));
}

void SimpleInfo::photoAlterBtnClicked()
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


void SimpleInfo::tableViewSelect(QModelIndex index)
{
    QString number;
    QString name;
    QPixmap photo;

    QAbstractItemModel *model = tableView->model();
    QModelIndex dex;
    dex = model->index(index.row(), 0);
    number = model->data(dex).toString();
    dex = model->index(index.row(), 1);
    name = model->data(dex).toString();

    photoNumberLb->setText(number);
    photoNameLb->setText(name);

    QSqlQuery query;
    bool ok = query.exec(tr("select 照片 from studentImage where 学号 = %1").arg(number));
    if (ok == false || !query.next())
    {
        return;
    }
    photo.loadFromData(query.value(0).toByteArray());
    photoLb->setPixmap(photo);
}

//----------------------------------------------------------------------------------
void SimpleInfo::loadBtnWidget()
{
    btnAdd = new QPushButton(tr("添加"));
    btnDelete = new QPushButton(tr("删除"));
    btnRepeal = new QPushButton(tr("撤销"));
    btnALterOk = new QPushButton(tr("提交"));
    btnCancel = new QPushButton(tr("取消"));
    btnLayout = new QHBoxLayout();

    btnLayout->addStretch(1);
    btnLayout->addWidget(btnAdd);
    btnLayout->addWidget(btnDelete);
    btnLayout->addWidget(btnRepeal);
    btnLayout->addWidget(btnALterOk);
    btnLayout->addWidget(btnCancel);

    btnAdd->setHidden(true);
    btnDelete->setHidden(true);
    btnRepeal->setHidden(true);
    btnALterOk->setHidden(true);
    btnCancel->setHidden(true);

    connect(btnAdd, SIGNAL(clicked()),
            this, SLOT(btnAddClicked()));
    connect(btnDelete, SIGNAL(clicked()),
            this, SLOT(btnDeleteClicked()));
    connect(btnRepeal, SIGNAL(clicked()),
            this, SLOT(btnRepealClicked()));
    connect(btnALterOk, SIGNAL(clicked()),
            this, SLOT(btnAlterOkClicked()));
    connect(btnCancel, SIGNAL(clicked()),
            this, SLOT(btnCancelClicked()));
}

void SimpleInfo::btnRepealClicked()
{
    tableMode->revertAll();

    tableMode->setTable(tr("studentInfo"));
    tableMode->select();
}

void SimpleInfo::btnCancelClicked()
{

    tableMode->setTable(tr("studentInfo"));
    tableMode->select();

    photoAlterBtn->setHidden(true);
    btnAdd->setHidden(true);
    btnDelete->setHidden(true);
    btnRepeal->setHidden(true);
    btnALterOk->setHidden(true);
    btnCancel->setHidden(true);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void SimpleInfo::btnAddClicked()
{
    tableMode->insertRow(tableMode->rowCount());
}

void SimpleInfo::btnDeleteClicked()
{
    QItemSelectionModel *model = tableView->selectionModel();
    QModelIndexList list = model->selectedIndexes();
    for (int r = 0; r < list.size(); r++)
    {
        tableMode->removeRow(list[r].row());
    }
}

void SimpleInfo::btnAlterOkClicked()
{
    if(QMessageBox::No == QMessageBox::information(this, tr("提示"), tr("确认提交"), QMessageBox::Yes, QMessageBox::No))
    {
        return;
    }

    if(tableMode->submitAll())
    {

        photoAlterBtn->setHidden(true);
        btnAdd->setHidden(true);
        btnDelete->setHidden(true);
        btnRepeal->setHidden(true);
        btnALterOk->setHidden(true);
        btnCancel->setHidden(true);
        tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

        const QPixmap *pix = photoLb->pixmap();
        if(pix != NULL && !pix->isNull())
        {
            QByteArray byte;
            QBuffer buf(&byte);
            buf.open(QIODevice::WriteOnly);
            if (!pix->save(&buf, "JPG"))
            {
                QMessageBox::about(this, tr("error"), tr("SimpleInfo::btnAlterOkClicked is error\n%1").arg("photo is save fail 01"));
            }
            buf.close();

            QSqlQuery query;
            int ok = query.prepare(tr("update studentImage set 照片 = :byte where 学号 = '%1'").arg(photoNumberLb->text()));
            if (ok == true && !byte.isEmpty())
            {
                query.bindValue(":byte", byte);
                if (!query.exec())
                {
                    QMessageBox::about(this, tr("error"), tr("SimpleInfo::btnAlterOkClicked is error\n%1").arg("photo is save fail 02"));
                }
            }
            else
            {
                QMessageBox::about(this, tr("error"), tr("SimpleInfo::btnAlterOkClicked is error\n%1").arg("photo is save fail 03"));
            }
        }
    }
    else
    {
        QMessageBox::about(this, tr("error"), tr("SimpleInfo::btnAlterOkClicked is error\n%1").arg(tableMode->lastError().text()));
    }

    photoLb->clear();
    photoNumberLb->clear();
    photoNameLb->clear();
}

//----------------------------------------------------------------------------------
void SimpleInfo::loadDataBase()
{
    if(!base->isOpen())
    {
        QMessageBox::about(this, tr("error"), tr("SimpleInfo::loadDataBase is error"));
        return;
    }

    tableMode = new QSqlTableModel(this, *base);
    tableMode->setTable(tr("studentInfo"));
    tableMode->select();
    tableMode->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableView->setModel(tableMode);//设置表视图模式
}
//----------------------------------------------------------------------------------

void SimpleInfo::actionAlterClicked()
{
    photoAlterBtn->setHidden(false);
    btnAdd->setHidden(false);
    btnDelete->setHidden(false);
    btnRepeal->setHidden(false);
    btnALterOk->setHidden(false);
    btnCancel->setHidden(false);
    tableView->setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked);
    tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
}
