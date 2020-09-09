#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFile>
#include <QString>
#include <QGraphicsView>
#include <QGraphicsScene>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    static const int MAX_COUNT = 6;
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_Sair_clicked();

    void on_Proxim_clicked();

    void on_Anterior_clicked();

private:
    void mostraAjuda();

    Ui::Dialog *ui;
    QGraphicsScene *mScene;
    uint count;
};

#endif // DIALOG_H
