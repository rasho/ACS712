# ACS712 biblioteka

Ova biblioteka omogućava jednostavno korišćenje ACS712 strujnih senzora u Arduino projektima. Pruža funkcionalnosti za kalibraciju senzora, očitavanje trenutne vrednosti struje i podršku za različite modele senzora.

## Instalacija

1. Preuzmite biblioteku: kliknite na zeleno dugme "Code" na GitHub stranici biblioteke i izaberite "Download ZIP" opciju.
2. U Arduino IDE, idite na "Sketch" -> "Include Library" -> "Add .ZIP Library" i izaberite preuzeti ZIP fajl biblioteke.
3. Biblioteka će se dodati u vašu Arduino IDE.

## Upotreba

1. Uključite biblioteku dodavanjem `#include <ACS712.h>` na početak svog koda.
2. Kreirajte objekat senzora sa odgovarajućim parametrima: `ACS712 sensor(A0, ACS712_20A);`, gde je `A0` analogni pin na koji je senzor povezan, a `ACS712_20A` je model senzora.
3. Kalibrišite senzor:
   - Za kalibraciju offset napona, koristite `calibrateOffset(numSamples)` metodu, gde je `numSamples` broj uzoraka za kalibraciju.
   - Za kalibraciju osetljivosti senzora, koristite `calibrateSensitivity(knownCurrent, numSamples)` metodu, gde je `knownCurrent` poznata struja za kalibraciju.
4. Očitajte trenutnu vrednost struje: `float current = sensor.getCurrent();`.
   
## Primer koda

```cpp
#include <ACS712.h>

ACS712 sensor(A0, ACS712_20A);

void setup() {
  Serial.begin(9600);
  
  // Kalibracija senzora
  sensor.calibrateOffset(250);
  sensor.calibrateSensitivity(10.0, 250);
}

void loop() {
  float current = sensor.getCurrent();
  
  // Ispisivanje trenutne vrednosti struje na serijski monitor
  Serial.print("Trenutna vrednost struje: ");
  Serial.print(current);
  Serial.println(" A");
  
  delay(1000);
}
```
## Prilagođavanje osetljivosti senzora
U biblioteci su podržani različiti modeli senzora `ACS712`. Možete prilagoditi osetljivost senzora za određeni model koristeći metodu `setModel()`. Na primer: `sensor.setModel(ACS712_30A)`;. Molimo vas da proučite dokumentaciju ili specifikacije vašeg konkretnog modela senzora `ACS712` kako biste pravilno postavili osetljivost.
## Autor
Biblioteka ACS712 je razvijena od strane Radenko Bogdanovic za sopstvene potrebe.
## Licenca
Ova biblioteka je dostupna pod CREATIVE COMMONS ATTRIBUTION-NONCOMMERCIAL (CC BY-NC) Licencom.
