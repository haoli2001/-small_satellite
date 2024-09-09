#ifndef CONNECTDIALOGSIN_H
#define CONNECTDIALOGSIN_H

#include <QDialog>

namespace Ui {
class ConnectDialogsin;
}

class ConnectDialogsin : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialogsin(QString *ip1, quint16 *port1, QString *savepath, bool *sended, QWidget *parent = nullptr);
    ~ConnectDialogsin();

private slots:
    void on_pushButton_recssave_clicked();

    void on_pushButton_connect_clicked();

private:
    Ui::ConnectDialogsin *ui;
    QString *ip1, *savepath;
    quint16 *port1;
    bool *sended;
    bool isConfiged = false;
    bool RecSuccessed = false;
};

#endif // CONNECTDIALOGSIN_H
