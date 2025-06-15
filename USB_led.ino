//----Pin RGB----
const int pinR = 3;
const int pinG = 5;
const int pinB = 6;

char inputBuffer[16]; 
uint8_t idx = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);
  Serial.println("Arduino prêt. Envoyez R,G,B (ex: 255,0,128)");
}

void setColor(int r, int g, int b) {
  analogWrite(pinR, r);
  analogWrite(pinG, g);
  analogWrite(pinB, b);
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();

    // Quand on atteint un retour à la ligne, on traite
    if (c == '\n') {
      inputBuffer[idx] = '\0'; // Fin de chaîne

      int r, g, b;
      // On lit 3 entiers séparés par des virgules
      if (sscanf(inputBuffer, "%d,%d,%d", &r, &g, &b) == 3) {
        r = constrain(r, 0, 255);
        g = constrain(g, 0, 255);
        b = constrain(b, 0, 255);
        setColor(r, g, b);
        Serial.print("Couleur définie : R=");
        Serial.print(r);
        Serial.print(" G=");
        Serial.print(g);
        Serial.print(" B=");
        Serial.println(b);
      } else {
        Serial.println("Format invalide, utiliser R,G,B");
      }

      idx = 0; // on remet le buffer à zéro
    }
    else if (c != '\r') {
      if (idx < sizeof(inputBuffer) - 1) {
        inputBuffer[idx++] = c;
      }
    }
  }
}
