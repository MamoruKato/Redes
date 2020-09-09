#include "host.h"
#include "ui_host.h"

Host::Host(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Host)
{
    ui->setupUi(this);
}

Host::~Host()
{
    delete ui;
}

QTextEdit* Host::interfaceServidor()
{
    return ui->textEdit_2;
}

QLineEdit* Host::statusServidor()
{
    return ui->statusServidor;
}

QPushButton* Host::encerrarServidor()
{
    return ui->Encerrar;
}

QTextEdit* Host::interfaceCliente()
{
    return  ui->textEdit;
}

QLineEdit* Host::statusCliente()
{
    return ui->statusCliente;
}

QPushButton* Host::enviarCliente()
{
    return ui->Enviar;
}

QPushButton* Host::encerrarCliente()
{
    return ui->Parar;
}


void Host::on_Enviar_clicked()
{

}

void Host::on_Parar_clicked()
{

}

void Host::on_Encerrar_clicked()
{

}
