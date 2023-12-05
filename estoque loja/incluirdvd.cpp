#include "incluirdvd.h"
#include "ui_incluirdvd.h"

IncluirDVD::IncluirDVD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirDVD)
{
    ui->setupUi(this);
}

IncluirDVD::~IncluirDVD()
{
    delete ui;
}

void IncluirDVD::clear()
{
    ui->lineEdit_nome->setText("");
    ui->lineEdit_preco->setText("");
    ui->lineEdit_duracao->setText("");
}

void IncluirDVD::on_buttonBox_accepted()
{
    QString nome,preco,duracao;

    nome = ui->lineEdit_nome->text();
    preco = ui->lineEdit_preco->text();
    duracao = ui->lineEdit_duracao->text();

    clear();

    emit signIncluirDVD(nome,preco,duracao);
}
