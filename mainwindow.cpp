#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setMinimumSize(800, 600);//初始化大小
    this->loadMenuBar();//初始化菜单

    base = QSqlDatabase::addDatabase(tr("QSQLITE"));
    base.setDatabaseName(tr("mainDb.db"));

    info = new SimpleInfo(&base);
    this->setCentralWidget(info);
}

MainWindow::~MainWindow()
{

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
                           "时间：2014年9月30日"
                           ));
}

void MainWindow::actionEditALterClicked()
{
    emit info->alterSimpleInfo();
}
//---------------------------------------------------------------------
