#include "avisolivro.h"
#include "ui_avisolivro.h"

AvisoLivro::AvisoLivro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AvisoLivro)
{
    ui->setupUi(this);
}

AvisoLivro::~AvisoLivro()
{
    delete ui;
}
