#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
# include <QSqlDatabase>
# include <QMenuBar>
# include <QMenu>
# include <QAction>
# include <QMessageBox>

# include "simpleinfo.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public://simpleinfo
    SimpleInfo *info;
    QSqlDatabase base;

public://MenuBar
    QMenu *menuFile;
    QAction *actionFileQuit;

    QMenu *menuEdit;
    QAction *actionEditALter;

    QMenu *menuHelp;
    QAction *actionHelpInfo;

public:
    void loadMenuBar();

public slots:
    void actionFileQuitClicked();
    void actionHelpInfoClicked();
    void actionEditALterClicked();

};

#endif // MAINWINDOW_H
