#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    count = 0;
    mScene = new QGraphicsScene();

    this->mostraAjuda();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_Sair_clicked()
{
    this->close();
}

void Dialog::on_Proxim_clicked()
{
    if(count == MAX_COUNT)
        count = 0;
    else
        count++;

    mostraAjuda();
}

void Dialog::mostraAjuda()
{

    mScene->clear();
    mScene->clearFocus();

    if(count == 0)
    {
        this->resize(500,350);
        QString texto(":/images/Files/ufsc-logo-3.png");
        QPixmap bTexto;

        bTexto.load(texto);
        bTexto = bTexto.scaled(QSize(380,250), Qt::KeepAspectRatio);

        if(!bTexto.isNull())
            mScene->addPixmap(bTexto);
    }

    else if(count == 1)
    {
        QString texto(":/images/Files/instrucoes.txt");
        QByteArray bTexto;
        QFile f(texto);

        if(!f.open(QIODevice::ReadOnly))
        {
            return;
        }
        bTexto = f.readAll();
        mScene->addText(bTexto);
    }
    else if(count == 2)
    {

        this->resize(500,350);
        QString texto(":/images/Files/ajuda.txt");
        QByteArray bTexto;
        QFile f(texto);

        if(!f.open(QIODevice::ReadOnly))
        {
            return;
        }
        bTexto = f.readAll();
        mScene->addText(bTexto);

    }

    else if(count == 3)
    {
        QString texto(":/images/Files/Example1.png");
        QPixmap bTexto;

        this->resize(1366,700);
        bTexto.load(texto);
        bTexto = bTexto.scaled(QSize(1366,768), Qt::KeepAspectRatio);

        if(!bTexto.isNull())
            mScene->addPixmap(bTexto);
    }
    else if(count == 4)
    {
        QString texto(":/images/Files/Example2.png");
        QPixmap bTexto;

        bTexto.load(texto);
        bTexto = bTexto.scaled(QSize(1366,768), Qt::KeepAspectRatio);

        if(!bTexto.isNull())
            mScene->addPixmap(bTexto);
    }
    else if(count == 5)
    {
        QString texto(":/images/Files/Example3.png");
        QPixmap bTexto;

        bTexto.load(texto);
        bTexto = bTexto.scaled(QSize(1366,768), Qt::KeepAspectRatio);

        if(!bTexto.isNull())
            mScene->addPixmap(bTexto);
    }
    else if(count == 6)
    {
        QString texto(":/images/Files/Example4.png");
        QPixmap bTexto;

        bTexto.load(texto);
        bTexto = bTexto.scaled(QSize(1366,768), Qt::KeepAspectRatio);

        if(!bTexto.isNull())
            mScene->addPixmap(bTexto);
    }


    ui->graphicsView->setScene(mScene);

}

void Dialog::on_Anterior_clicked()
{
    if(count == 0)
        count = count;
    else
        count--;

    this->mostraAjuda();
}
