#ifndef USBLED_H
#define USBLED_H

#include <QMainWindow>
#include <QSerialPort>
#include <QFrame>

QT_BEGIN_NAMESPACE
namespace Ui {
class USBLed;
}
QT_END_NAMESPACE

class USBLed : public QMainWindow
{
    Q_OBJECT

public:
    USBLed(QWidget *parent = nullptr); //Constructeur de la fenetre
    ~USBLed(); //Destructeur de la fenetre

private slots:
    void sendColorButtonClicked();  //envoyer la couleur à l'Arduino
    void updateColorDisplay(int value);


private:
    Ui::USBLed *ui;
    QSerialPort *serial;
    static const long BAUD_RATE = 9600;
    const QString ARDUINO_PORT_NAME = "COM5";
};
#endif // USBLED_H
