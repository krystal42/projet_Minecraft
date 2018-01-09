#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "*********";// nom du reseau wifi
const char* password = "**********";//mdp du reseau wifi
IPAddress ip(192, 168, 0, 105); //set static ip
IPAddress gateway(192, 168, 0, 1); //set getteway
IPAddress subnet(255, 255, 255, 0);//set subnet
ESP8266WebServer server(80);

const int led_r = 14; //pin rouge connecté au pin D5 du NodeMcu
const int led_v = 12; //pin vert connecté au pin D6 du NodeMcu
const int led_b = 13; //pin bleu connecté au pin D7 du NodeMcu


// Fonction executée quand une requête arrive sur l'url "/urlColor"
void handleUrlColor() {
  
  Serial.println("Requête UrlColor");

  // Récupère les paramêtres de l'URL 
  String red = server.arg(0); // 1er paramètre : rouge
  String green = server.arg(1); // 2ème paramètre : vert
  String blue = server.arg(2); // 3ème paramètre : bleu

  // Affiche le composantes de couleur dans le moniteur série et pilote la LED
  Serial.print("red : ");
  Serial.println(red.toInt());
  digitalWrite(led_r, red.toInt());
  Serial.print("green : ");
  digitalWrite(led_v, green.toInt());
  Serial.println(green.toInt());
  Serial.print("blue : ");
  Serial.println(blue.toInt());
  digitalWrite(led_b, blue.toInt());

}

void handleNotFound(){
  delay(250);
  digitalWrite(led_r, 0);
  digitalWrite(led_v, 0);
  digitalWrite(led_b, 0);
  
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led_r, 0);
}

void setup(void){
  pinMode(led_r, OUTPUT);
  pinMode(led_v, OUTPUT);
  pinMode(led_b, OUTPUT);
  digitalWrite(led_r, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  //affichage de l'adresse ip du nodeMCU dans le bus serie
  Serial.println(WiFi.localIP());
  //si le wifi se connecte correctement clignotement de la led rouge
  digitalWrite(led_r, 1);
  delay(1000);
  digitalWrite(led_r, 0);

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }


  server.on("/inline", [](){

  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("Serveur démarré");
  // si le serveur démarre correctement clignotement de la led verte
  delay(1000);
  digitalWrite(led_v, 1);
  delay(1000);
  digitalWrite(led_v, 0);

  server.on("/urlColor", handleUrlColor);
  
}

void loop(void){
  server.handleClient();
  
}
