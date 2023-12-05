#include "incluirlivro.h"
#include "ui_incluirlivro.h"

IncluirLivro::IncluirLivro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirLivro)
{
    ui->setupUi(this);
}

IncluirLivro::~IncluirLivro()
{
    delete ui;
}

void IncluirLivro::clear()
{
    ui->lineEdit_nome->setText("");
    ui->lineEdit_preco->setText("");
    ui->lineEdit_autor->setText("");
}

void IncluirLivro::on_buttonBox_accepted()
{
    QString nome,preco,autor;

    nome = ui->lineEdit_nome->text();
    preco = ui->lineEdit_preco->text();
    autor = ui->lineEdit_autor->text();

    clear();

    emit signIncluirLivro(nome,preco,autor);
}
