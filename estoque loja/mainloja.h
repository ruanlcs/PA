#ifndef MAINLOJA_H
#define MAINLOJA_H

#include <QMainWindow>
#include <QLabel>
#include "loja.h"
#include "incluirlivro.h"
#include "incluircd.h"
#include "incluirdvd.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainLoja; }
QT_END_NAMESPACE

class MainLoja : public QMainWindow
{
    Q_OBJECT

public:
    MainLoja(QWidget *parent = nullptr);
    ~MainLoja();

private slots:
    void on_actionLer_triggered();

    void on_actionSalvar_triggered();

    void on_actionSair_triggered();

    void on_actionIncluir_livro_triggered();

    void on_actionIncluir_CD_triggered();

    void on_actionIncluir_DVD_triggered();

    void on_tableLivro_cellDoubleClicked(int row, int column);

    void on_tableCD_cellDoubleClicked(int row, int column);

    void on_tableDVD_cellDoubleClicked(int row, int column);

    void slotIncluirLivro(QString nome, QString preco, QString autor);

    void slotIncluirCD(QString nome, QString preco, QString numfaixas);

    void slotIncluirDVD(QString nome, QString preco, QString duracao);

private:
    Ui::MainLoja *ui;

    Loja X;
    IncluirLivro* inclLivro;
    IncluirCD* inclCD;
    IncluirDVD* inclDVD;
    QLabel* total_itens;

    void exibeListaLivro();
    void exibeListaCD();
    void exibeListaDVD();
    void exibeListas();
    void exibeStatus();
    void style();



};
#endif // MAINLOJA_H
