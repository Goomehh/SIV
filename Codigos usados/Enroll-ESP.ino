#include <SoftwareSerial.h>
#include <Adafruit_Fingerprint.h>

uint8_t id;
// pin 33 Input do sensor (fio verde) ou rx
// pin 32 Output que vem do arduino (fio amarelo ou branco) tx
//mySerial(rx,tx)
SoftwareSerial mySerial(33,32);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
void setup()
{
  Serial.begin(115200);
  Serial.println("Teste do sensor");
  // set the data rate for the sensor serial port
  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("O sensor foi encontrado!");
  } 
  else {
    Serial.println("O sensor não foi encontrado :(");
    while (1);
  }
}
uint8_t readnumber(void) {
  uint8_t num = 0;
  while (num == 0) {
    while (! Serial.available());
    num = Serial.parseInt();
  }
  return num;
}
void loop()
{
  Serial.println("Digite o número de ID que deseja salvar...");
  id = readnumber();
  if (id == 0) {// ID #0 !
    return;
  }

  Serial.print("Gravação ID #");
  Serial.println(id);
  while (! getFingerprintEnroll(id) );
}
uint8_t getFingerprintEnroll(int id) {
  int p = -1;
  Serial.println("Aguardando a leitura de uma nova digital");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
      Serial.println ("Impressão gravada");
      break;
      case FINGERPRINT_NOFINGER:
      Serial.println (".");
      break;
      case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println ("erro na comunicação");
      break;
      case FINGERPRINT_IMAGEFAIL:
      Serial.println ("erro na imagem");
      break;
      default:
      Serial.println ("erro desconhecido");
      break;
    }
  }
  // OK success!
  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
    Serial.println ("Imagem convertida");
    break;
    case FINGERPRINT_IMAGEMESS:
    Serial.println ("Imagem distorcida");
    return p;
    case FINGERPRINT_PACKETRECIEVEERR:
    Serial.println ("erro na comunicação");
    return p;
    case FINGERPRINT_FEATUREFAIL:
    Serial.println ("Não foi possível reconhecer a digital");
    return p;
    case FINGERPRINT_INVALIDIMAGE:
    Serial.println ("Não foi possível reconhecer a digital");

    return p;
    default:
    Serial.println ("erro desconhecido");
    return p;
  }
  Serial.println ("Remova o seu dedo");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  p = -1;
  Serial.println ("Coloque o mesmo dedo novamente");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
      Serial.println ("Imagem convertida");
      break;
      case FINGERPRINT_NOFINGER:
      Serial.print (".");
      break;
      case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println ("erro na comunicação");
      break;
      case FINGERPRINT_IMAGEFAIL:
      Serial.println ("erro na imagem");
      break;
      default:
      Serial.println ("erro desconhecido");
      break;
    }
  }
  // OK success!
  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
    Serial.println ("Imagem convertida");
    break;
    case FINGERPRINT_IMAGEMESS:
    Serial.println ("Imagem distorcida");
    return p;
    case FINGERPRINT_PACKETRECIEVEERR:
    Serial.println ("erro na comunicação");

    return p;
    case FINGERPRINT_FEATUREFAIL:
    Serial.println ("Não foi possível reconhecer a digital");
    return p;
    case FINGERPRINT_INVALIDIMAGE:
    Serial.println ("Não foi possível reconhecer a digital");
    return p;
    default:
    Serial.println ("erro desconhecido");
    return p;
  }
  // OK converted!
  Serial.print("Criando modelo para #"); Serial.println(id);
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println ("Digitais conferem!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println ("erro na comunicação");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println ("As impressões digitais não batem.");
    return p;
  } else {
    Serial.println ("erro desconhecido");
    return p;
  }
  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println ("A digital foi gravada!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println ("erro na comunicação");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println ("Não foi possível armazenar nesse local");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println ("Erro ao gravar na memória");
    return p;
  } else {
    Serial.println ("erro desconhecido");
    return p;
  }
}