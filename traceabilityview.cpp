#include "traceabilityview.h"
#include "ui_traceabilityview.h"

TraceabilityView::TraceabilityView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TraceabilityView)
{
    ui->setupUi(this);
}

TraceabilityView::~TraceabilityView()
{
    delete ui;
}
