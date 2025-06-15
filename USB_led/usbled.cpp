#include "usbled.h"
#include "./ui_usbled.h"
#include <QMessageBox>     // Pour les boîtes de dialogue d'information/erreur
#include <QDebug>

USBLed::USBLed(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::USBLed)
{
    ui->setupUi(this);
    // --- Initialisation de QSerialPort et connexion à l'Arduino ---
    serial = new QSerialPort(this); // Crée une nouvelle instance de QSerialPort. 'this' assure que l'objet sera détruit avec la fenêtre.

    // Configure le port série (nom, baud rate, etc.)
    serial->setPortName(ARDUINO_PORT_NAME); // Utilise la constante que tu as définie dans usbled.h (par ex. "COM5")
    serial->setBaudRate(BAUD_RATE);         // Utilise la constante BAUD_RATE (9600)
    serial->setDataBits(QSerialPort::Data8); // 8 bits de données (standard)
    serial->setParity(QSerialPort::NoParity); // Pas de parité (standard)
    serial->setStopBits(QSerialPort::OneStop); // 1 bit d'arrêt (standard)
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (!serial->open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le port série " + ARDUINO_PORT_NAME);
         qDebug() << "Erreur connexion port: " << serial->errorString();

    }
    // --- Connexions des signaux et slots ---
    connect(ui->horizontalSliderRed, &QSlider::valueChanged, this, &USBLed::updateColorDisplay);
    connect(ui->horizontalSliderGreen, &QSlider::valueChanged, this, &USBLed::updateColorDisplay);
    connect(ui->horizontalSliderBlue, &QSlider::valueChanged, this, &USBLed::updateColorDisplay);

    connect(ui->pushButtonSendColor, &QPushButton::clicked, this, &USBLed::sendColorButtonClicked);

    // --- Initialisation des valeurs de l'UI au démarrage ---
    ui->horizontalSliderRed->setValue(0);
    ui->horizontalSliderGreen->setValue(0);
    ui->horizontalSliderBlue->setValue(0);

    updateColorDisplay(0);

}

void USBLed::updateColorDisplay(int /*value*/){

    // Récupère les valeurs actuelles de tous les sliders
    int r = ui->horizontalSliderRed->value();
    int g = ui->horizontalSliderGreen->value();
    int b = ui->horizontalSliderBlue->value();

    // Met à jour le texte des QLabel pour les valeurs numériques
    ui->labelRedValue->setText(QString::number(r));
    ui->labelGreenValue->setText(QString::number(g));
    ui->labelBlueValue->setText(QString::number(b));

     // Met à jour la couleur de fond du QFrame d'aperçu
    ui->ColorPreview->setStyleSheet(QString("background-color: rgb(%1, %2, %3);")
                                        .arg(r)
                                        .arg(g)
                                        .arg(b));
}

void USBLed::sendColorButtonClicked()
{
    // Vérifie si le port série est bien ouvert avant d'envoyer des données
    if (serial->isOpen()) {

        // Récupère les valeurs actuelles des sliders
        int red = ui->horizontalSliderRed->value();
        int green = ui->horizontalSliderGreen->value();
        int blue = ui->horizontalSliderBlue->value();

        // Construit la chaîne à envoyer à l'Arduino (format "R,G,B\n")
        QString dataToSend = QString("%1,%2,%3\n")
                                 .arg(red)
                                 .arg(green)
                                 .arg(blue);

        // Envoie les données au port série
        serial->write(dataToSend.toUtf8());

        // Affiche la chaîne envoyée dans la console de débogage de Qt Creator
        qDebug() << "Envoi vers Arduino: " << dataToSend;
    } else {
        QMessageBox::warning(this, "Port non connecté", "Le port serie n'est pas connecte. Impossible d'envoyer la couleur.");
        qDebug() << "Port serie non ouvert, couleur non envoyee a l'Arduino.";
    }
}

USBLed::~USBLed()
{
    if (serial->isOpen()) {
        serial->close();
    }
    delete ui;
}
