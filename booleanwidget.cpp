#include "booleanwidget.h"

QImage* BooleanWidget::backicon = new QImage(":/row-pre.png");
QImage* BooleanWidget::foricon = new QImage(":/row-pos.png");
QImage* BooleanWidget::noneicon = new QImage(":/white.png");

BooleanWidget::BooleanWidget(QWidget * parent) : QWidget(parent)
{

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QHBoxLayout * layout = new QHBoxLayout(this);
    checkBox = new MyButton(this);
    state =0;
    //checkBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    checkBox->setIcon(QIcon(QPixmap::fromImage(*noneicon)));
    checkBox->setFlat(true);
    checkBox->setIconSize(QSize(50,50));

    QObject::connect(checkBox, SIGNAL(pressed()), this, SLOT(nextState()));
}

void  BooleanWidget::setState(int st) {
    if(st == 1){
        state = 1;
        checkBox->setIcon(QIcon(QPixmap::fromImage(*backicon)));
    }else if (st == 2){
        state = 2;
        checkBox->setIcon(QIcon(QPixmap::fromImage(*foricon)));
    } else {
        state = 0;
        checkBox->setIcon(QIcon(QPixmap::fromImage(*noneicon)));
    }
}

void  BooleanWidget::nextState() {
    if(state == 0){
        state = 1;
        checkBox->setIcon(QIcon(QPixmap::fromImage(*backicon)));
    }else if (state == 1){
        state = 2;
        checkBox->setIcon(QIcon(QPixmap::fromImage(*foricon)));
    } else{
        state = 0;
        checkBox->setIcon(QIcon(QPixmap::fromImage(*noneicon)));
    }
}
