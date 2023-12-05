#ifndef AVISOLIVRO_H
#define AVISOLIVRO_H

#include <QDialog>

namespace Ui {
class AvisoLivro;
}

class AvisoLivro : public QDialog
{
    Q_OBJECT

public:
    explicit AvisoLivro(QWidget *parent = nullptr);
    ~AvisoLivro();

private:
    Ui::AvisoLivro *ui;
};

#endif // AVISOLIVRO_H
