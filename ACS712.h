#ifndef ACS712_h
#define ACS712_h

enum ACS712_Model {
  ACS712_5A,
  ACS712_20A,
  ACS712_30A
};

class ACS712 {
  private:
    int analogPin; // Analogni pin na koji je senzor povezan
    float sensitivity; // Osetljivost senzora
    float offsetVoltage; // Offset napona

  public:
    ACS712(int pin, ACS712_Model model) {
      analogPin = pin;
      setModel(model);
    }

    void setModel(ACS712_Model model) {
      switch (model) {
        case ACS712_5A:
          sensitivity = 0.185; // Osetljivost za model ACS712 5A
          break;
        case ACS712_20A:
          sensitivity = 0.100; // Osetljivost za model ACS712 20A
          break;
        case ACS712_30A:
          sensitivity = 0.066; // Osetljivost za model ACS712 30A
          break;
        default:
          sensitivity = 0.185; // Podrazumevana osetljivost za nedostajući model
          break;
      }
    }

    void calibrateOffset(int numSamples) {
      // Kalibracija offset napona
      float sum = 0.0;

      for (int i = 0; i < numSamples; i++) {
        int sensorValue = analogRead(analogPin);
        sum += (sensorValue / 1023.0) * 5.0;
        delay(10); // Pauza između uzoraka
      }

      offsetVoltage = sum / numSamples;
    }

    void calibrateSensitivity(float knownCurrent, int numSamples) {
      // Kalibracija osetljivosti senzora
      float sum = 0.0;

      for (int i = 0; i < numSamples; i++) {
        int sensorValue = analogRead(analogPin);
        float voltage = (sensorValue / 1023.0) * 5.0;
        sum += voltage;
        delay(10); // Pauza između uzoraka
      }

      float avgVoltage = sum / numSamples;
      sensitivity = knownCurrent / avgVoltage;
    }

    float getCurrent() {
      int sensorValue = analogRead(analogPin);
      float voltage = (sensorValue / 1023.0) * 5.0; // Pretvaranje analognog očitavanja u napon

      // Računanje struje na osnovu očitanog napona
      float current = (voltage - offsetVoltage) / sensitivity;
      return current;
    }
};

#endif