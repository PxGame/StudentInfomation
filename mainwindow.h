#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
# include <QSqlDatabase>
# include <QMenuBar>
# include <QMenu>
# include <QAction>
# include <QMessageBox>
# include <QAbstractItemModel>
# include <QModelIndex>

# include "stackview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    QSqlDatabase base;
    StackView *stackView;

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
public slots://stackView.simple
    void simpleDoubleClicked(QModelIndex index);
public slots://stackView.details
    void detailsReturnBtnClicked();

};

#endif // MAINWINDOW_H
