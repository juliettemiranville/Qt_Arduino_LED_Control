# Qt_Arduino_LED_Control

## Description du Projet

Ce projet propose une **Interface** développée avec **Qt**, permettant de contrôler une LED RGB connectée à une Arduino nano. L'application utilise des sliders pour ajuster les composantes Rouge, Verte et Bleue (RVB) de la couleur, ainsi qu'un aperçu visuel de la couleur sélectionnée. Un simple clic sur un bouton envoie la couleur choisie à l'Arduino via une liaison série.

## Prérequis

Avant d'utiliser ce projet, assurez-vous d'avoir les éléments suivants :

1.  **Matériel :**
    * Une Arduino 
    * Une LED RGB (commune ou anode/cathode commune, ajustez le câblage et le code Arduino en conséquence).
    * Trois résistances.
    * Un câble USB pour connecter l'Arduino à votre ordinateur.

2.  **Logiciels :**
    * **Arduino IDE :** Pour téléverser le code sur votre Arduino.
    * **Qt Creator (avec un kit de développement C++) :** Pour compiler et exécuter l'application IHM.
    * **Git :** Pour cloner ce dépôt.

## Installation et Utilisation

Suivez les étapes ci-dessous pour mettre en place et utiliser le contrôleur de LED RGB.

### 1. Préparation de l'Arduino

1.  **Ouvrez le fichier `USB_led.ino`** situé à la racine du dépôt dans l'IDE Arduino.
2.  **Vérifiez et adaptez les broches (pins) de la LED RVB** dans le code Arduino (`pinR`, `pinG`, `pinB`) pour correspondre à votre câblage.
3.  **Assurez-vous que le `BAUD_RATE` dans le code Arduino (`Serial.begin(9600);`) corresponde à celui défini dans le code Qt** (qui est 9600 par défaut dans `usbled.h`).
4.  **Connectez votre Arduino à votre ordinateur** via USB.
5.  Dans l'Arduino IDE, sélectionnez la bonne carte (`Outils > Type de carte`) et le bon port série (`Outils > Port`).
6.  **Téléversez le sketch `USB_led.ino`** sur votre Arduino.

### 2. Compilation et Exécution de l'Application Qt

1.  **Clonez ce dépôt Git** sur votre machine locale :
    ```bash
    git clone https://github.com/juliettemiranville/Qt_Arduino_LED_Control.git
    ```
2.   **Ouvrez le dossier du projet Qt (`USB_led/`) dans Qt Creator.** Qt Creator détectera automatiquement le fichier `CMakeLists.txt` et configurera le projet.
3.  Dans le fichier `usbled.h`, **mettez à jour la constante `ARDUINO_PORT_NAME`** avec le nom du port série de votre Arduino.
    * Exemples : `"COM3"` (Windows), `"/dev/ttyACM0"` (Linux), `"/dev/tty.usbmodemXXXX"` (macOS).
    ```cpp
    const QString ARDUINO_PORT_NAME = "COMX"; // REMPLACEZ "COMX" PAR LE NOM DE VOTRE PORT
    ```
4.  **Assurez-vous que l'Arduino est connecté et que son sketch est téléversé.**
5.  Dans Qt Creator, **construisez le projet** (`Build > Build Project`) puis **exécutez l'application** (`Build > Run`).
6.  Une fois l'application lancée, utilisez les sliders pour choisir une couleur et cliquez sur le bouton "Envoyer Couleur" pour la transmettre à la LED RGB.
