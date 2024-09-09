#include "connectdialogsin.h"
#include "ui_connectdialogsin.h"
#include <QFileDialog>
#include <QMessageBox>

ConnectDialogsin::ConnectDialogsin(QString *ip1, quint16 *port1, QString *savepath, bool *sended, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialogsin),ip1(ip1), savepath(savepath),port1(port1), sended(sended)
{
    ui->setupUi(this);
    setWindowTitle("连接请求");
    if(ui->lineEdit_recpath->text().isEmpty())
    {
        ui->pushButton_connect->setEnabled(false);
    }
    if(!(ui->lineEdit_recpath->text() == NULL))
    {
        isConfiged = true;
        *savepath = ui->lineEdit_recpath->text();
    }
}

ConnectDialogsin::~ConnectDialogsin()
{
    delete ui;
}


void ConnectDialogsin::on_pushButton_recssave_clicked()
{
    *savepath = QFileDialog::getExistingDirectory(this, "保存路径", "./", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->lineEdit_recpath->setText(*savepath);
    if(!(ui->lineEdit_recpath->text() == NULL))
     {
        isConfiged = true;
        ui->pushButton_connect->setEnabled(true);
     }
    else
        isConfiged = false;
}

void ConnectDialogsin::on_pushButton_connect_clicked()
{


    if(isConfiged || !(ui->lineEdit_recpath->text() == NULL))
    {
        QString iptemp1 = ui->lineEdit_ip->text();
        QString porttemp1 = ui->lineEdit_port->text();


        *ip1 = iptemp1;
        *port1 = porttemp1.toInt();


        *sended = true;
        accept();
    }
    else
    {
        QMessageBox::warning(this, "警告", "未填写接收地址！");
    }
}
