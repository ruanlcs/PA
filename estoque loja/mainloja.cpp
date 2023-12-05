#include <QFileDialog>
#include <QMessageBox>

#include "mainloja.h"
#include "ui_mainloja.h"
#include "loja.h"
#include "incluirlivro.h"
#include "incluircd.h"
#include "incluirdvd.h"


MainLoja::MainLoja(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainLoja)
    , X()
    , inclLivro(nullptr)
    , inclCD(nullptr)
    , inclDVD(nullptr)
    , total_itens(nullptr)

{
    ui->setupUi(this);
    inclLivro = new IncluirLivro(this);
    inclCD = new IncluirCD(this);
    inclDVD = new IncluirDVD(this);
    total_itens = new QLabel(this);

    statusBar()->insertWidget(0,new QLabel("Total de itens: "));
    statusBar()->insertWidget(1,total_itens);

    //conexao dos sinais
    connect(inclLivro, &IncluirLivro::signIncluirLivro,
            this, &MainLoja::slotIncluirLivro);

    connect(inclCD, &IncluirCD::signIncluirCD,
            this, &MainLoja::slotIncluirCD);

    connect(inclDVD, &IncluirDVD::signIncluirDVD,
            this, &MainLoja::slotIncluirDVD);

    style();
    exibeListas();
    exibeStatus();

}

MainLoja::~MainLoja()
{
    delete ui;
    delete inclLivro;
    delete inclCD;
    delete inclDVD;
    delete total_itens;
}


void MainLoja::on_actionLer_triggered()
{
    QString nomeArquivo = QFileDialog::
        getOpenFileName(this,"Ler estoque",QString(),"Estoques (*.txt);;Estoques C++(*.cpp *.h)");

    if(!nomeArquivo.isEmpty()){
        QFile file(nomeArquivo);
        if(!file.open(QIODevice::ReadOnly)){
            QMessageBox::critical(this,"Erro","Erro ao abrir o arquivo");
            return;
        }
         X.ler(nomeArquivo.toStdString());
         file.close();
    }

    exibeListas();
    exibeStatus();
}


void MainLoja::on_actionSalvar_triggered()
{
    QString nomeArquivo = QFileDialog::
            getSaveFileName(this,"Salvar estoque",QString(),"Estoques (*.txt);;Estoques C++ (*.cpp *.h)");

    if(nomeArquivo.isEmpty()){
        QFile file(nomeArquivo);
        if(!file.open(QIODevice::WriteOnly)){
            QMessageBox::critical(this,"Erro","Nao foi possivel salvar o arquivo");
            return;
        }
    }
    X.salvar(nomeArquivo.toStdString());

}


void MainLoja::on_actionSair_triggered()
{
    QCoreApplication::quit();
}


void MainLoja::on_actionIncluir_livro_triggered()
{

    inclLivro->clear();
    inclLivro->show();
    exibeListaLivro();
}


void MainLoja::on_actionIncluir_CD_triggered()
{
    inclCD->clear();
    inclCD->show();
    exibeListaCD();
}


void MainLoja::on_actionIncluir_DVD_triggered()
{
    inclDVD->clear();
    inclDVD->show();
    exibeListaDVD();
}


void MainLoja::on_tableLivro_cellDoubleClicked(int row, int column)
{
    Q_UNUSED(column);

    QMessageBox aviso;
    int botao;
    aviso.setWindowTitle("Exclusao de item");
    aviso.setText("Realmente deseja excluir este livro?");
    aviso.setIcon(QMessageBox::Warning);
    aviso.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    botao = aviso.exec();

        if(unsigned(row)<X.getNumLivro()){
            if(botao==QMessageBox::Yes){
                X.excluirLivro(row);
                exibeListaLivro();
                exibeStatus();
            }
         else return;
        }

}


void MainLoja::on_tableCD_cellDoubleClicked(int row, int column)
{
    Q_UNUSED(column);
    QMessageBox aviso;
    int botao;
    aviso.setWindowTitle("Exclusao de item");
    aviso.setText("Realmente deseja excluir este CD?");
    aviso.setIcon(QMessageBox::Warning);
    aviso.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    botao = aviso.exec();

        if(unsigned(row)<X.getNumCD()){
            if(botao==QMessageBox::Yes){
                X.excluirCD(row);
                exibeListaCD();
                exibeStatus();
            }
         else return;
        }

}


void MainLoja::on_tableDVD_cellDoubleClicked(int row, int column)
{
    Q_UNUSED(column);
    QMessageBox aviso;
    int botao;
    aviso.setWindowTitle("Exclusao de item");
    aviso.setText("Realmente deseja excluir este DVD?");
    aviso.setIcon(QMessageBox::Warning);
    aviso.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    botao = aviso.exec();

        if(unsigned(row)<X.getNumDVD()){
            if(botao==QMessageBox::Yes){
                X.excluirDVD(row);
                exibeListaDVD();
                exibeStatus();
            }
         else return;
        }

}

void MainLoja::slotIncluirLivro(QString nome, QString preco, QString autor)
{
    Livro provL(nome.toStdString(),round(preco.toFloat()*100.0),autor.toStdString());

    if(provL.getNome() != " " && provL.getPreco()!=0 && provL.getAutor()!=" "){
        X.incluirLivro(provL);
        exibeListaLivro(); exibeStatus();
    }
    else{
        QMessageBox::critical(this,"Livro invalido",QString("Nao foi possivel incluir o livro:")+
                              "\nNome="+nome+"\nPreco="+preco+"\nAutor="+autor);
    }

}

void MainLoja::slotIncluirCD(QString nome, QString preco, QString numfaixas)
{
    CD provCD(nome.toStdString(),round(preco.toFloat()*100.0),numfaixas.toFloat());

    if(provCD.getNome()!=" " && provCD.getPreco()!=0 && provCD.getNumFaixas()!=0){
        X.incluirCD(provCD);
        exibeListaCD(); exibeStatus();
    }
    else{
        QMessageBox::critical(this,"CD invalido",QString("Nao foi possivel incluir o CD:")+
                              "\nNome="+nome+"\nPreco="+preco+"\nNum faixas="+numfaixas);
    }

}

void MainLoja::slotIncluirDVD(QString nome, QString preco, QString duracao)
{
    DVD provDVD(nome.toStdString(),round(preco.toFloat()*100.0),duracao.toFloat());

    if(provDVD.getNome()!=" " && provDVD.getPreco()!=0 && provDVD.getDuracao()!=0){
        X.incluirDVD(provDVD);
        exibeListaDVD(); exibeStatus();
    }
    else{
        QMessageBox::critical(this,"DVD invalido",QString("Nao foi possivel incluir o DVD:")+
                              "\nNome="+nome+"\nPreco="+preco+"\nDuracao="+duracao);
    }

}

void MainLoja::exibeListaLivro()
{
    ui->tableLivro->clearContents();
    ui->tableLivro->setRowCount(X.getNumLivro());

    QLabel* prov;

    for(unsigned i=0; i<X.getNumLivro(); i++)
    {
        for(unsigned j=0; j<3; j++)
        {
            Livro L = X.getLivro(i);
            if(j==0){
                prov = new QLabel(L.getNome().c_str());
                prov->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
                ui->tableLivro->setCellWidget(i,j,prov);
            }
            else if(j==1){
                prov = new QLabel(QString::number(L.getPreco(),'f',2));
                prov->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
                ui->tableLivro->setCellWidget(i,j,prov);
            }
            else{
                prov = new QLabel(L.getAutor().c_str());
                prov->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
                ui->tableLivro->setCellWidget(i,j,prov);
            }
        }
    }
}

void MainLoja::exibeListaCD()
{
    ui->tableCD->clearContents();
    ui->tableCD->setRowCount(X.getNumCD());

    QLabel* prov;

    for(unsigned i=0; i<X.getNumCD(); i++)
    {
        for(unsigned j=0; j<3; j++)
        {
            CD cd = X.getCD(i);
            if(j==0){
                prov = new QLabel(cd.getNome().c_str());
                prov->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
                ui->tableCD->setCellWidget(i,j,prov);
            }
            else if(j==1){
                prov = new QLabel(QString::number(cd.getPreco(),'f',2));
                prov->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
                ui->tableCD->setCellWidget(i,j,prov);
            }
            else{
                prov = new QLabel(QString::number(cd.getNumFaixas()));
                prov->setAlignment(Qt::AlignVCenter | Qt::AlignCenter);
                ui->tableCD->setCellWidget(i,j,prov);
            }
        }
    }
}

void MainLoja::exibeListaDVD()
{
    ui->tableDVD->clearContents();
    ui->tableDVD->setRowCount(X.getNumDVD());

    QLabel* prov;

    for(unsigned i=0; i<X.getNumDVD(); i++)
    {
        for(unsigned j=0; j<3; j++)
        {
            DVD dvd = X.getDVD(i);

            if(j==0){
                prov = new QLabel(dvd.getNome().c_str());
                prov->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
                ui->tableDVD->setCellWidget(i,j,prov);
            }
            else if(j==1){
                prov = new QLabel(QString::number(dvd.getPreco(),'f',2));
                prov->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
                ui->tableDVD->setCellWidget(i,j,prov);
            }
            else{
                prov = new QLabel(QString::number(dvd.getDuracao()));
                prov->setAlignment(Qt::AlignVCenter | Qt::AlignCenter);
                ui->tableDVD->setCellWidget(i,j,prov);
            }
        }
    }
}

void MainLoja::exibeListas()
{
    exibeListaLivro(); exibeListaCD(); exibeListaDVD();
}

void MainLoja::exibeStatus()
{
    total_itens->setNum(int(X.getNumLivro() + X.getNumCD() + X.getNumDVD()));
}

void MainLoja::style()
{
    ui->label_LIVROS->setStyleSheet("background-color: lightgray");
    ui->label_CDS->setStyleSheet("background-color: lightgray");
    ui->label_DVDS->setStyleSheet("background-color: lightgray");

    ui->tableLivro->setStyleSheet("QHeaderView::section{background-color: lightgray}");
    ui->tableCD->setStyleSheet("QHeaderView::section{background-color: lightgray}");
    ui->tableDVD->setStyleSheet("QHeaderView::section{background-color: lightgray}");

    ui->tableLivro->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tableLivro->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->tableLivro->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);

    ui->tableCD->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tableCD->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->tableCD->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);

    ui->tableDVD->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tableDVD->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
    ui->tableDVD->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);

    ui->tableLivro->setHorizontalHeaderLabels(QStringList()<<"NOME"<<"PRECO"<<"AUTOR");
    ui->tableCD->setHorizontalHeaderLabels(QStringList()<<"NOME"<<"PRECO"<<"N FAIXAS");
    ui->tableDVD->setHorizontalHeaderLabels(QStringList()<<"NOME"<<"PRECO"<<"DURACAO");
}

