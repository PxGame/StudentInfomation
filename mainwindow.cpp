#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setMinimumSize(800, 600);//初始化大小
    this->loadMenuBar();//初始化菜单

    base = QSqlDatabase::addDatabase(tr("QSQLITE"));
    base.setDatabaseName(tr("mainDb.db"));

    stackView = new  StackView(&base);
    this->setCentralWidget(stackView);

    connect(stackView->simple->tableView, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(simpleDoubleClicked(QModelIndex)));
    connect(stackView->details->returnBtn, SIGNAL(clicked()),
            this, SLOT(detailsReturnBtnClicked()));

}

MainWindow::~MainWindow()
{
    base.close();
}
//---------------------------------------------------------------------
void MainWindow::loadMenuBar()
{
    //------------------------------------------------------
    menuFile = this->menuBar()->addMenu(tr("文件"));
    actionFileQuit = new QAction(tr("退出"), this);
    menuFile->addAction(actionFileQuit);
    connect(actionFileQuit, SIGNAL(triggered()),
            this, SLOT(actionFileQuitClicked()));
    //------------------------------------------------------
    menuEdit = this->menuBar()->addMenu(tr("编辑"));
    actionEditALter = new QAction(tr("修改"), this);
    menuEdit->addAction(actionEditALter);
    connect(actionEditALter, SIGNAL(triggered()),
            this, SLOT(actionEditALterClicked()));
    //------------------------------------------------------
    menuHelp = this->menuBar()->addMenu(tr("帮助"));
    actionHelpInfo = new QAction(tr("关于"), this);
    menuHelp->addAction(actionHelpInfo);
    connect(actionHelpInfo, SIGNAL(triggered()),
            this, SLOT(actionHelpInfoClicked()));
}

void MainWindow::actionFileQuitClicked()
{
    this->close();
}

void MainWindow::actionHelpInfoClicked()
{
    QMessageBox::about(this, tr("关于"),tr(
                           "学生信息管理系统\n"
                           "制作人：向牧\n"
                           "时间：2014年9月30日\n"
                           "使用技巧：\n"
                           "（1）双击列表中的选项可以查看详细信息\n"
                           "（2）添加学生信息需要在显示列表时，在编辑菜单中选择\"修改\"选项。\n"
                           "（3）列表中的信息和详细信息的修改均单击编辑菜单中的\"修改\"选项。\n"
                           "（4）可通过选择搜索类型来执行不同类型的搜索。"
                           ));
}

void MainWindow::actionEditALterClicked()
{
    switch(stackView->stack->currentIndex())
    {
    case 0:
        stackView->simple->alterSimpleInfo();
        break;
    case 1:
        stackView->details->alterDetailsInfo();
        break;
    }
}

void MainWindow::simpleDoubleClicked(QModelIndex index)
{
    if (!stackView->simple->readOnly)
    {
        return;
    }
    QString number;
    QAbstractItemModel *model = stackView->simple->tableView->model();
    QModelIndex dex;
    dex = model->index(index.row(), 0);
    number = model->data(dex).toString();

    if(number.isEmpty())
    {
        return;
    }
    stackView->details->setInfo(number);
    stackView->stack->setCurrentIndex(1);
}

void MainWindow::detailsReturnBtnClicked()
{
    stackView->simple->tableMode->setTable(tr("studentInfo"));
    stackView->simple->tableMode->select();
    stackView->stack->setCurrentIndex(0);
}
//---------------------------------------------------------------------
