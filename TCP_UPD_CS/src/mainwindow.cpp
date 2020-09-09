#include "mainwindow.h"
#include "cliente.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    servidor1 = NULL;
    cliente1 = NULL;
    servidorUdp1 = NULL;
    _porta = 0;
    _protocol = "NULL";
    _host = "NULL";
    ui->setupUi(this);


    QGraphicsScene *scene = new QGraphicsScene(this);
    QPixmap pix(":/images/Files/ufsc-logo-3.png");
    QPixmap tamanhoPix = pix.scaled(QSize(this->LOGO_W,this->LOGO_H), Qt::KeepAspectRatio);
    scene->addPixmap(tamanhoPix);

    ui->logo->setScene(scene);

    ui->lineEdit->setReadOnly(true);
    ui->lineEdit_2->setReadOnly(true);
    ui->textEdit->setReadOnly(true);
    ui->textEdit_2->setReadOnly(true);


    ui->Enviar->setDisabled(true);
    ui->Parar->setDisabled(true);
    ui->comear->setDisabled(true);

    ui->Escutar->setDisabled(true);
    ui->Encerrar->setDisabled(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}


QString MainWindow::metodoChecagem()
{
    QString checagem = NULL;

    if(ui->CRC->isChecked())
        checagem = "CRC";
    else if(ui->CheckSum->isChecked())
        checagem = "checkSum";
    else if(ui->Naochecar->isChecked())
        checagem = "naoChecar";
    else
        checagem = "naoChecar";

    return checagem;
}

void MainWindow::servidorFalhaConexao()
{
    ui->Enviar->setDisabled(true);
    ui->comear->setDisabled(true);

}


void MainWindow::clienteFalhaConexao()
{
    ui->Enviar->setDisabled(true);
}

void MainWindow::clienteEnviando()
{
    ui->Enviar->setDisabled(true);
}

void MainWindow::clienteEnviado()
{
    ui->Enviar->setEnabled(true);
}

void MainWindow::on_start_clicked()
{
    QString texto = NULL;
    QString Ip_servidor = NULL;
    QString porta = NULL;
    QString portac = NULL;
    QString Ip_cliente = NULL;

    QGraphicsScene *scene2 = new QGraphicsScene();

    QByteArray full_data = NULL;
    texto = _filename;

    porta = ui->Porta->text();
    if(porta.isEmpty() || porta.isNull()) porta = "1234";

    portac = ui->PortaCliente->text();
    if(portac.isEmpty() || portac.isNull()) portac = "1234";
    Ip_cliente = ui->IPcliente->text();
    if(Ip_cliente.isEmpty() || Ip_cliente.isNull()) Ip_cliente = "127.0.0.1";

    if(ui->TCP->isChecked())
        _protocol = "TCP";
    else if(ui->UDP->isChecked())
        _protocol = "UDP";
    else
        _protocol = "TCP";

    _porta = porta.toInt();
    _host = Ip_servidor;

    _portac = portac.toInt();
    _hostc = Ip_cliente;

    QFileInfo fileInfo(texto);
    QFile f(texto);

    _formato = fileInfo.completeSuffix();
    if(_formato.isEmpty() ||( _formato != "png" && _formato != "jpeg" && _formato != "jpg"))
    {
        _formato = "txt";
    }


    if(!f.open(QIODevice::ReadOnly))
    {
        return;
    }

    full_data = f.readAll();

    if(_formato == "txt")
    {
        QVariant strFull_data(full_data);
        scene2->addText(strFull_data.toString());
    }

    else if(_formato == "png" || _formato == "jpeg" || _formato == "jpg")
    {
        QPixmap p2;
        p2.loadFromData(full_data,"PNG");
        p2 = p2.scaled(QSize(MThread::INTERFACE_W,MThread::INTERFACE_H),Qt::KeepAspectRatio);
        scene2->addPixmap(p2);

    }

    _dados = full_data;

    ui->start->setDisabled(true);
    ui->comear->setEnabled(true);

    ui->Escutar->setEnabled(true);

    ui->graphicsView->setScene(scene2);
}


void MainWindow::on_Sair_2_clicked()
{
    QApplication::quit();
}

void MainWindow::on_Limpa_clicked()
{
    ui->IPcliente->clear();
    ui->Porta->clear();
    ui->PortaCliente->clear();

    ui->lineEdit->setText("Desativado");
    ui->lineEdit_2->setText("Desativado");

    ui->textEdit_2->clear();
    ui->textEdit->clear();


    if(!ui->start->isEnabled())
        ui->start->setEnabled(true);

    if(ui->Enviar->isEnabled())
        ui->Enviar->setDisabled(true);
    if(ui->Parar->isEnabled())
        ui->Parar->setDisabled(true);
    if(ui->comear->isEnabled())
        ui->comear->setDisabled(true);
    if(ui->Escutar->isEnabled())
        ui->Escutar->setDisabled(true);
    if(ui->Encerrar->isEnabled())
        ui->Encerrar->setDisabled(true);

    emit on_Encerrar_clicked();
    emit on_Parar_clicked();

}

void MainWindow::on_Enviar_clicked()
{
}

void MainWindow::on_Parar_clicked()
{
    if(cliente1 != NULL)
        ui->comear->setEnabled(true);
}

void MainWindow::on_Encerrar_clicked()
{
}

void MainWindow::on_Escutar_clicked()
{
    ui->Encerrar->setEnabled(true);
    if(_protocol == "TCP")
    {
        servidor1 = new Servidor(ui->graphicsView_2,ui->textEdit_2, ui->lineEdit, ui->Encerrar, this,_formato, _host, _porta);
        connect(servidor1, SIGNAL(falhaConexao()), this, SLOT(servidorFalhaConexao()));
        servidor1->startServer();
    }
    else if(_protocol == "UDP")
    {
        servidorUdp1 = new ServidorUDP(ui->textEdit_2, ui->lineEdit, ui->Encerrar, ui->graphicsView_2,
                                       metodoChecagem(),_formato,this, _host, _porta);
        servidorUdp1->criaSocket();
    }
    else
        return;

    ui->Escutar->setDisabled(true);

}

void MainWindow::on_comear_clicked()
{
    cliente1 = new Cliente(_hostc,_portac,_protocol,_dados, ui->graphicsView,ui->textEdit,
                           ui->lineEdit_2, ui->Enviar, ui->Parar, _formato, metodoChecagem());
    connect(cliente1,SIGNAL(falhaConexao()),this,SLOT(clienteFalhaConexao()));
    connect(cliente1,SIGNAL(enviando()),this,SLOT(clienteEnviando()));
    connect(cliente1,SIGNAL(enviado()),this,SLOT(clienteEnviado()));

    cliente1->start();
    ui->lineEdit_2->setText("Cliente Iniciado");

    ui->Enviar->setEnabled(true);
    ui->Parar->setEnabled(true);
    ui->comear->setDisabled(true);

    connect(cliente1, SIGNAL(finished()), cliente1, SLOT(deleteLater()));

    if(_protocol == "UDP")
        connect(servidorUdp1, SIGNAL(leituraTerminada()),cliente1, SLOT(enviarCheckSum()));

}

void MainWindow::on_Ajuda_clicked()
{
    Dialog help;

    help.show();

    help.exec();
}

void MainWindow::on_File_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                ":/images/",
                "All files (*.*);;Text File (*.txt);; Music File(*.mp3);; Image File(*.png)"
                );

    _filename = filename;

    if(_filename.isEmpty() || _filename.isNull())
        _filename = ":/images/Files/ufsc-logo-3.png";

    QMessageBox::information(this,tr("File Name"), filename);
}
