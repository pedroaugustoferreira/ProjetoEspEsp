#include <ESP8266WiFi.h>//Biblioteca do WiFi.
#include <WiFiUdp.h>//Biblioteca do UDP.

#define RELAY 13

WiFiUDP udp;//Cria um objeto da classe UDP.
String req;//String que armazena os dados recebidos pela rede.

 

void setup() {

Serial.begin(115200);
  delay(10);

  pinMode(RELAY,OUTPUT);
  digitalWrite(RELAY, HIGH);  

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");

   WiFi.setAutoConnect(true);
   WiFi.begin("ESP32-Access-Point", "123456789");//Conecta à rede do host.
IPAddress ip(192,168,4,10);   
IPAddress gateway(192,168,4,1);   
IPAddress subnet(255,255,255,0); 




while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

WiFi.config(ip, gateway, subnet);
   
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
 
   udp.begin(555);//Inicializa a recepçao de dados UDP na porta 555
  

}

void loop() {
  
  read_pacotes();
  valida_wifi();

}

void valida_wifi() {

  while (WiFi.status() != WL_CONNECTED || WiFi.localIP() == IPAddress(0,0,0,0)) {
    Serial.println("WiFi reconnect"); 
    //WiFi.reconnect();
    delay(1000);
  }
}
  





void read_pacotes() {
if (udp.parsePacket() > 0)//Se houver pacotes para serem lidos
   {
       req = "";//Reseta a string para receber uma nova informaçao
       if (udp.available() > 0)//Enquanto houver dados para serem lidos
       {
           char z = udp.read();//Adiciona o byte lido em uma char
           req += z;//Adiciona o char à string
           Serial.println(">>> :" +req);
       }
 
       //Após todos os dados serem lidos, a String estara pronta.

        if ( req == "1"  ){
          digitalWrite(RELAY,LOW);
          Serial.println("Ligando");
        }
        if ( req == "0"  ){
          digitalWrite(RELAY,HIGH);
          Serial.println("Desligando");
        }
       Serial.println(req);//Printa a string recebida no Serial monitor.
        
      
    }

}



