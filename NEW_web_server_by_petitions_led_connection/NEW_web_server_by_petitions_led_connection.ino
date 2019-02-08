#include <ESP8266WiFi.h> //Incluimos la librería para del WiFi
#include <WiFiClientSecure.h>     //kbjcjdcbskdj
#define HOSTIFTTT "maker.ifttt.com"    //kbjcjdcbskdj
#define EVENTO "LED_ON"   //kbjcjdcbskdj
#define IFTTTKEY "mcj4DAdU2Lq3BDILuo840OK1xRloe1dRThchCyxF94d"   //kbjcjdcbskdj
WiFiClientSecure client;      //kbjcjdcbskdj
int contconexion = 0;
const char *ssid = "MO_espe";
const char *password = "Password1024";
int servo_1 = D6; // D0 is the LEDBUILDIN (Active LOW) pin 53 
int servo_2 = D5;//pin 52
int servo_3 = D8;//pin50
int mp3_1 = D2;
int mp3_2 = D1;
int mp3_3 = D3;
int var=0;
WiFiServer server(80);
void setup() {
  //klkdslckdslkclkld
  if (client.connect(HOSTIFTTT,443)) {
    Serial.println("Connected");
    // build the HTTP request
    String toSend = "GET /trigger/";
    toSend += EVENTO;
    toSend += "/with/key/";
    toSend += IFTTTKEY;
    toSend += " HTTP/1.1\r\n";
    toSend += "Host: ";
    toSend += HOSTIFTTT;
    toSend += "\r\n";
    toSend += "Connection: close\r\n\r\n";
    client.print(toSend);
  }
  //ajscbackslcnlasl
  Serial.begin(9600); //Inicio el puerto serie 
  delay(10);
  pinMode(mp3_1, OUTPUT);
  pinMode(mp3_2, OUTPUT);
  pinMode(mp3_3, OUTPUT);
  pinMode(servo_1, OUTPUT);
  pinMode(servo_2, OUTPUT);
  pinMode(servo_3, OUTPUT);
  digitalWrite(mp3_1, LOW);
  digitalWrite(mp3_2, LOW);
  digitalWrite(mp3_3, LOW);
  digitalWrite(servo_1, LOW);
  digitalWrite(servo_2, LOW);
  digitalWrite(servo_3, LOW);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED and contconexion <50) { //Cuenta hasta 50 si no se puede conectar lo cancela
    delay(500);
    Serial.print("Testing: ");
    Serial.print(".");
  }
  if (contconexion <50) {
      IPAddress ip(192,168,43,12); 
      IPAddress gateway(192,168,43,1); 
      IPAddress subnet(255,255,255,0); 
      WiFi.config(ip, gateway, subnet); 
      Serial.println("");
      Serial.println("WiFi conectado");
      Serial.println(WiFi.localIP());
  }
  else { 
     Serial.println("");
     Serial.println("Error de conexion");
  }
  server.begin();
}
void loop() {
  digitalWrite(mp3_1, LOW);
  digitalWrite(mp3_2, LOW);
  digitalWrite(mp3_3, LOW);
  digitalWrite(servo_1, LOW);
  digitalWrite(servo_2, LOW);
  digitalWrite(servo_3, LOW);
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("¡Nuevo cliente!");
  while(!client.available()){
    delay(1);
  }
  String request = client.readStringUntil('\r'); // Leo hasta retorno de carro
  Serial.println(request); //Imprimo la petición
  client.flush(); //Limpio el buffer
  if (request.indexOf("/mp3_1=ON") != -1)  { //mp3
    var = 1;
  }
  if (request.indexOf("/mp3_2=ON") != -1)  {  //mp3
    var = 2;
  }
  if (request.indexOf("/mp3_3=ON") != -1)  {  //mp3
    var = 3;
  }
  if (request.indexOf("/servo_1") != -1)  {  //servo
    var = 4;
  }
  if (request.indexOf("/servo_2") != -1)  {  //servo
    var = 5;
  }
  if (request.indexOf("/servo_3") != -1)  {  //servo
    var = 6;
  }
  switch(var){
    case 0:
    digitalWrite(mp3_1, LOW);
    digitalWrite(mp3_2, LOW);
    digitalWrite(mp3_3, LOW);
    digitalWrite(servo_1, LOW);
    digitalWrite(servo_2, LOW);
    digitalWrite(servo_3, LOW);
    case 1:
    digitalWrite(mp3_1, HIGH);
    delay(2000);
    digitalWrite(mp3_1, LOW);
    delay(10);
    Serial.print("Var: ");
    Serial.println(var);
    var =0;
    break;
    case 2:
    digitalWrite(mp3_2, HIGH);
    delay(2000);
    digitalWrite(mp3_2, LOW);
    delay(10);
    Serial.print("Var: ");
    Serial.println(var);
    var =0;
    break;
    case 3:
    digitalWrite(mp3_3, HIGH);
    delay(2000);
    digitalWrite(mp3_3, LOW);
    delay(10);
    var =0;
    Serial.print("Var: ");
    Serial.println(var);
    break;
    case 4:
    digitalWrite(D6, HIGH);
    delay(1000);
    digitalWrite(D6, LOW);
    delay(10);
    var =0;
    Serial.print("Var: ");
    Serial.println(var);
    break;
    case 5:
    digitalWrite(D5, HIGH);
    delay(100);
    digitalWrite(D5, LOW);
    delay(10);
    var =0;
    Serial.print("Var: ");
    Serial.println(var);
    break;
    case 6:
    digitalWrite(D8, HIGH);
    delay(100);
    digitalWrite(D8, LOW);
    delay(10);
    Serial.print("Var: ");
    Serial.println(var);
    var =0;
    break;
    default:
    var = 0;
    digitalWrite(mp3_3, LOW);
    digitalWrite(mp3_2, LOW);
    digitalWrite(mp3_1, LOW);
    digitalWrite(servo_1, LOW);
    digitalWrite(servo_2, LOW);
    digitalWrite(servo_3, LOW);
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>"); 
  client.println("<html>");
  client.println("<body>"); 
  client.println("<script type='text/javascript'>"); 
  client.println("function cerrar(){self.close();} var cierre = setTimeout('cerrar()',100)");
  client.println("</script>");
  client.println("</body>"); 
  client.println("</html>");
}
