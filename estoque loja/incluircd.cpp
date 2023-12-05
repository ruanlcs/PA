#include "incluircd.h"
#include "ui_incluircd.h"

IncluirCD::IncluirCD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirCD)
{
    ui->setupUi(this);
}

IncluirCD::~IncluirCD()
{
    delete ui;
}

void IncluirCD::clear()
{
    ui->lineEdit_nome->setText("");
    ui->lineEdit_preco->setText("");
    ui->lineEdit_numfaixas->setText("");
}

void IncluirCD::on_buttonBox_accepted()
{
    QString nome,preco,numfaixas;

    nome = ui->lineEdit_nome->text();
    preco = ui->lineEdit_preco->text();
    numfaixas = ui->lineEdit_numfaixas->text();

    clear();

    emit signIncluirCD(nome,preco,numfaixas);
}
