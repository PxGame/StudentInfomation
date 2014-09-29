#include "stackview.h"

StackView::StackView(QSqlDatabase *base, QWidget *parent) :
    QWidget(parent)
{
    simple = new SimpleInfo(base);
    details = new DetailsInfo(base);
    stack = new QStackedWidget();
    stack->addWidget(simple);
    stack->addWidget(details);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stack);
    mainLayout->setMargin(0);

    stack->setCurrentIndex(0);
}
