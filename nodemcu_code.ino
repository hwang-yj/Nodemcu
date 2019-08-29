#include <ESP8266WiFi.h>
#include <DHT.h>

#define PIN_DHT D4
#define PIN_BL D0
#define PIN_DC D1
#define PIN_T D2
#define PIN_200 D6

const char* ssid = "AndroidHotspot7981";
const char* password = "1234567890";



WiFiServer server(80);
WiFiClient client;
DHT DHTsensor(PIN_DHT, DHT11);

void setup() {
  DHTsensor.begin();
  pinMode(PIN_BL, OUTPUT);
  digitalWrite(PIN_BL, HIGH);
  pinMode(PIN_DC, OUTPUT);
  digitalWrite(PIN_DC, HIGH);
  pinMode(PIN_T, OUTPUT);
  digitalWrite(PIN_T, HIGH);
  pinMode(PIN_200, OUTPUT);
  digitalWrite(PIN_200, HIGH);

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.println("Server started");
}

void loop() {
  client = server.available();
  if(!client) return;

  Serial.println("새로운 클라이언트");
  client.setTimeout(10000);

  String request = client.readStringUntil('\r');
  Serial.println("request: ");
  Serial.println(request);

  if(request.indexOf("/Back_left_on") != -1) {

   if (digitalRead(PIN_BL) == 1){
    digitalWrite(PIN_BL, LOW);
    }

    else{
    digitalWrite(PIN_BL, HIGH);
    }
    }

  //else if(request.indexOf("/Back_left_off") != -1) {
  //  digitalWrite(PIN_BL, HIGH);
  //}
  else if(request.indexOf("/Back_right_on") != -1) {
    if (digitalRead(PIN_DC) == 1){
        digitalWrite(PIN_DC, LOW);
        }

        else{
        digitalWrite(PIN_DC, HIGH);
        }
        }
  //else if(request.indexOf("/Back_right_off") != -1) {
  //  digitalWrite(PIN_DC, HIGH);
  //}
  else if(request.indexOf("/Arm_left_on") != -1) {
    if (digitalRead(PIN_T) == 1){
        digitalWrite(PIN_T, LOW);
        }

        else{
        digitalWrite(PIN_T, HIGH);
        }
        }
  //else if(request.indexOf("/Arm_left_off") != -1) {
  //  digitalWrite(PIN_T, HIGH);
  //}
  else if(request.indexOf("/Arm_right_on") != -1) {
    if (digitalRead(PIN_200) == 1){
        digitalWrite(PIN_200, LOW);
        }

        else{
        digitalWrite(PIN_200, HIGH);
        }
        }
  //else if(request.indexOf("/Arm_right_off") != -1) {
  //  digitalWrite(PIN_200, HIGH);
  //}
  else if(request.indexOf("/reset") != -1) {
    digitalWrite(PIN_BL, HIGH);
    digitalWrite(PIN_DC, HIGH);
    digitalWrite(PIN_T, HIGH);
    digitalWrite(PIN_200, HIGH);
  }
  else {
    Serial.println("invalid request");
    digitalWrite(PIN_BL, digitalRead(PIN_BL));
    digitalWrite(PIN_DC, digitalRead(PIN_DC));
    digitalWrite(PIN_T, digitalRead(PIN_T));
    digitalWrite(PIN_200, digitalRead(PIN_200));
  }

  while(client.available()) {
    client.read();
  }

  float humidity = DHTsensor.readHumidity();
  float temp = DHTsensor.readTemperature();
  const char* warning = "off";
  Serial.print("Humidity : ");
  Serial.print(humidity);
  Serial.print(" Temperature : ");
  Serial.print(temp);
  Serial.println(" ºC");

  if(humidity>90 || temp>33){

  digitalWrite(PIN_BL, HIGH);
  digitalWrite(PIN_DC, HIGH);
  digitalWrite(PIN_T, HIGH);
  digitalWrite(PIN_200, HIGH);
  warning = "on";
  }
  else{
  warning = "off";
  }

  client.print("HTTP/1.1 200 OK");
  client.print("Content-Type: text/html\r\n\r\n");
  client.print("<!doctype html><html lang=\"en\"><head><title>Move your Mobility</title><meta charset=\"utf-8\"><meta name=\"viewport\"content=\"width=device-width, initial-scale=1, shrink-to-fit=no\"><meta name=\"description\"content=\"Mobland - Mobile App Landing Page Template\"><meta name=\"keywords\"content=\"HTML5, bootstrap, mobile, app, landing, ios, android, responsive\"><link rel=\"dns-prefetch\"href=\"//fonts.googleapis.com\"><link href=\"https://fonts.googleapis.com/css?family=Rubik:300,400,500\"rel=\"stylesheet\"><link rel=\"stylesheet\"href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\"><style>@charset\"UTF-8\";body{font-family:'Rubik',sans-serif;position:relative}a{color:#e38cb7}a:hover,a:focus{color:#d6619c}h1{font-size:60px;font-weight:300;letter-spacing:-1px;margin-bottom:1.5rem}h2{font-size:45px;font-weight:300;color:#633991;letter-spacing:-1px;margin-bottom:1rem}h3{color:#633991;font-size:33px;font-weight:500}h4{font-size:20px;font-weight:500;color:#633991}p{color:#959094}.light-bg{background-color:#faf6fb}.section{padding:80px 0}.section-title{text-align:center;margin-bottom:3rem}header{padding:100px 0 0;text-align:center;color:#FFF}.bg-gradient{background-image:-moz-linear-gradient(135deg,rgba(60,8,118,0.8)0%,rgba(250,0,118,0.8)100%);background-image:-webkit-linear-gradient(135deg,rgba(60,8,118,0.8)0%,rgba(250,0,118,0.8)100%);background-image:-ms-linear-gradient(135deg,rgba(60,8,118,0.8)0%,rgba(250,0,118,0.8)100%);background-image:linear-gradient(135deg,rgba(60,8,118,0.8)0%,rgba(250,0,118,0.8)100%)}.tagline{font-size:23px;font-weight:300;color:#ffb8f6;max-width:800px;margin:0 auto}.gradient-fill:before{color:#fc73b4;background:-moz-linear-gradient(top,#9477b4 0%,#fc73b4 100%);background:-webkit-linear-gradient(top,#9477b4 0%,#fc73b4 100%);background:linear-gradient(to bottom,#9477b4 0%,#fc73b4 100%);-webkit-background-clip:text;background-clip:text;-webkit-text-fill-color:transparent}.card.features{border:0;border-radius:3px;box-shadow:0px 5px 7px 0px rgba(0,0,0,0.04);transition:all 0.3s ease}.card.features:before{content:\"\";position:absolute;width:3px;color:#fc73b4;background:-moz-linear-gradient(top,#9477b4 0%,#fc73b4 100%);background:-webkit-linear-gradient(top,#9477b4 0%,#fc73b4 100%);background:linear-gradient(to bottom,#9477b4 0%,#fc73b4 100%);top:0;bottom:0;left:0}.card.features:hover{transform:translateY(-3px);-moz-box-shadow:0px 5px 30px 0px rgba(0,0,0,0.08);-webkit-box-shadow:0px 5px 30px 0px rgba(0,0,0,0.08);box-shadow:0px 5px 30px 0px rgba(0,0,0,0.08)}.myButton{-moz-box-shadow:inset 0px 1px 0px 0px#fbafe3;-webkit-box-shadow:inset 0px 1px 0px 0px#fbafe3;box-shadow:inset 0px 1px 0px 0px#fbafe3;background:-webkit-gradient(linear,left top,left bottom,color-stop(0.05,#ff5bb0),color-stop(1,#ef027d));background:-moz-linear-gradient(top,#ff5bb0 5%,#ef027d 100%);background:-webkit-linear-gradient(top,#ff5bb0 5%,#ef027d 100%);background:-o-linear-gradient(top,#ff5bb0 5%,#ef027d 100%);background:-ms-linear-gradient(top,#ff5bb0 5%,#ef027d 100%);background:linear-gradient(to bottom,#ff5bb0 5%,#ef027d 100%);filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#ff5bb0',endColorstr='#ef027d',GradientType=0);background-color:#ff5bb0;-moz-border-radius:6px;-webkit-border-radius:6px;border-radius:6px;border:1px solid#ee1eb5;display:inline-block;cursor:pointer;color:#ffffff;font-family:Arial;font-size:16px;font-weight:bold;font-style:italic;padding:7px 13px;text-decoration:none;text-shadow:0px 1px 0px#c70067}.myButton:hover{background:-webkit-gradient(linear,left top,left bottom,color-stop(0.05,#ef027d),color-stop(1,#ff5bb0));background:-moz-linear-gradient(top,#ef027d 5%,#ff5bb0 100%);background:-webkit-linear-gradient(top,#ef027d 5%,#ff5bb0 100%);background:-o-linear-gradient(top,#ef027d 5%,#ff5bb0 100%);background:-ms-linear-gradient(top,#ef027d 5%,#ff5bb0 100%);background:linear-gradient(to bottom,#ef027d 5%,#ff5bb0 100%);filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#ef027d',endColorstr='#ff5bb0',GradientType=0);background-color:#ef027d}.myButton:active{position:relative;top:1px}.centered{display:table;margin-left:auto;margin-right:auto}}</style></head><body data-spy=\"scroll\"data-target=\"#navbar\"data-offset=\"30\"><header class=\"bg-gradient\"id=\"home\"><div class=\"container mt-5\"><h1>Move Your Aqua Mobility</h1><p class=\"tagline\">Press the button to start each thruster</p></div></header><div class=\"section light-bg\"id=\"features\"><div class=\"centered\"><div class=\"row pb-1\"><div class=\"col-xs-3 mr-3\"><a href='/Arm_left_on'class=\"myButton\">Arm _ Left</a></div><div class=\"col-xs-3\"><a href='/Arm_right_on'class=\"myButton\">Arm _Right</a></div></div><div class=\"row pb-5\"><div class=\"col-xs-3 mr-3\"><a href='/Back_left_on'class=\"myButton\">Back_ Left</a></div><div class=\"col-xs-3\"><a href='/Back_right_on'class=\"myButton\">Back_Right</a></div></div></div></div><div class=\"section light-bg\"id=\"features\"><div class=\"container\"><div class=\"section-title\"><h3>STATUS<br>Arm_Left:");
  client.print((digitalRead(PIN_T)) ? "OFF" : "ON");
  client.print("<br>Arm_Right:");
  client.print((digitalRead(PIN_200)) ? "OFF" : "ON");
  client.print("<br>Back_Left:");
  client.print((digitalRead(PIN_BL)) ? "OFF" : "ON");
  client.print("<br>Back_Right:");
  client.print((digitalRead(PIN_DC)) ? "OFF" : "ON");
  client.print("<br> Temperature:");
  client.print(temp);
  client.print("°C");
  client.print("<br>Humidity:");
  client.print(humidity);
  client.print("%");
  client.print("</h3></div><div class=\"row\"><div class=\"col-12 col-lg-4\"><div class=\"card features\"><div class=\"card-body\"><h4 class=\"card-title\"><a href='/reset'>Turn off all</h4></div></div></div></div><div class=\"row\"><div class=\"col-12 col-lg-4\"><div class=\"card features\"><div class=\"card-body\"><h4 class=\"card-title\"><a href='/reset'>warnig_system</h4><p class=\"card-text\">:");
  client.print(warning);
  client.print("</p></div></div></div></div></div></div></div><script src=\"https://cdnjs.cloudflare.com/ajax/libs/jquery/3.2.1/jquery.min.js\"></script><script src=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.bundle.min.js\"></script></body></html>");
  }
