#include <ArduinoBLE.h>

BLEService ledService("180A"); // 180A se traduce como  Información del dispositivo

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic switchCharacteristic("2A57",  BLEWrite);// el 2a57 se 
// traduce como salida digital

void setup() {

    // Driver Motor
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  
  Serial.begin(9600);
  while (!Serial);

  // set built in LED pin to output mode
  pinMode(LED_BUILTIN, OUTPUT);

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("El blutú falló");
     digitalWrite(LED_BUILTIN, HIGH);         
    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName("Soy yo !!! No me ignores");
  BLE.setAdvertisedService(ledService);

  // add the characteristic to the service
  ledService.addCharacteristic(switchCharacteristic);

  // add service
  BLE.addService(ledService);

  // set the initial value for the characteristic:
  switchCharacteristic.writeValue(0);

  // start advertising
  BLE.advertise();

  Serial.println("Ya estoy por aquí...disponible, como si no tuviera nada que hacer... ");
}

void loop() {
  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Me conecté a este teléfono-> ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:
      if (switchCharacteristic.written()) {
        switch (switchCharacteristic.value()) {   // any value other than 0
          case 01:
            Serial.println(switchCharacteristic.value());
            //Avanza   
            avanza();        
            break;
          case 02:
              Serial.println(switchCharacteristic.value());
             //retrocede
             retrocede();
            break;
          case 03:
            Serial.println(switchCharacteristic.value());
           // Gira derecha
           giraDerecha();
            break;

            case 04:
              Serial.println(switchCharacteristic.value());
              // Gira izquierda
              giraIzquierda();
            break;
          default:
            Serial.println((switchCharacteristic.value()));
            detener();
            break;
        }
      }
    }

    // Cuando se desconecta...
    Serial.print(F("Me desconecté... buuuu: "));
    Serial.println(central.address());
   
  }
}




// CONDUCCIÓN

void avanza(){
  
  Serial.println("Avanza directo");
  //ENABLE ENCENDIDO
  analogWrite(3, 250);
  analogWrite(5, 250);
  //MOTOR 1
  digitalWrite(2, HIGH);
  digitalWrite(4, LOW);
  //MOTOR 2
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
}// 


void retrocede(){
  Serial.println("Retrocede línea recta");
  //ENABLE ENCENDIDO
  analogWrite(3, 150);
  analogWrite(5, 150);
  //MOTOR 1
  digitalWrite(2, LOW);
  digitalWrite(4, HIGH);
  //MOTOR 2
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}


void detener(){
  encenderRojoDer();
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  Serial.println("Detenido");
}

void giraDerecha(){
  analogWrite(3, 200);
  analogWrite(5, 200);
    //MOTOR 1
  digitalWrite(2, LOW);
  digitalWrite(4, HIGH);
  //MOTOR 2
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  
}

void giraIzquierda(){
    analogWrite(3, 200);
    analogWrite(5, 200);
    //MOTOR 1
  digitalWrite(2, HIGH);
  digitalWrite(4, LOW);
  //MOTOR 2
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
}
