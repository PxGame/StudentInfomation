#ifndef STACKVIEW_H
#define STACKVIEW_H

#include <QWidget>
# include <QStackedWidget>
# include <QSqlDatabase>
# include <QVBoxLayout>

# include "simpleinfo.h"
# include "detailsinfo.h"

class StackView : public QWidget
{
    Q_OBJECT
public:
    StackView(QSqlDatabase *base, QWidget *parent = 0);

public:
    SimpleInfo *simple;
    DetailsInfo *details;
    QStackedWidget *stack;
    QVBoxLayout *mainLayout;

signals:

public slots:

};

#endif // STACKVIEW_H
