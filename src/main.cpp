#include <Arduino.h>
#include <ESP8266WiFi.h>

const char* ssid = "Mondongo";
const char* password = "polloasado";

// Pines motor derecho
int IN1 = D4;
int IN2 = D5;

// Pines motor izquierdo (puedes usar otros pines si tienes segundo motor)
int IN3 = D3;
int IN4 = D2;

WiFiServer server(8144);

void moverMotor(int inA, int inB, int dir) {
  if (dir > 0) {
    digitalWrite(inA, HIGH);
    digitalWrite(inB, LOW);
  } else if (dir < 0) {
    digitalWrite(inA, LOW);
    digitalWrite(inB, HIGH);
  } else {
    digitalWrite(inA, LOW);
    digitalWrite(inB, LOW);
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.begin();
}



void loop() {
  WiFiClient client = server.available();
  String command = "";

  if (client) {
    Serial.println("Cliente conectado");

    while (client.connected()) {
      while (client.available() > 0) {
        char c = client.read();
        command += c;
      }

      if (command.length() > 0) {
        command.trim();
        Serial.println("Comando recibido: " + command);

        if (command == "forward") {
          moverMotor(IN1, IN2, 1);
          moverMotor(IN3, IN4, 1);
        } else if (command == "backward") {
          moverMotor(IN1, IN2, -1);
          moverMotor(IN3, IN4, -1);
        } else if (command == "left") {
          moverMotor(IN1, IN2, -1);
          moverMotor(IN3, IN4, 1);
        } else if (command == "right") {
          moverMotor(IN1, IN2, 1);
          moverMotor(IN3, IN4, -1);
        } else {
          moverMotor(IN1, IN2, 0);
          moverMotor(IN3, IN4, 0);
        }

        command = "";
      }
    }

    client.stop();
    Serial.println("Cliente desconectado");
  }
}
