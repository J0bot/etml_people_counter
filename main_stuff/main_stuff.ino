
/*
 * Auteur : José Carlos Gasser
 * Date : 12.12.2021
 * Description : programme qui va être flash sur l'arduino et qui commande tout
 */

#include <SPI.h>
#include <WiFiNINA.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>


//Toutes les infos sensibles sont dans le arduino_secrets.h
//en l'occurence, sur github, ça sert à rien, mais sur le site d'arduino c'est pratique
#include "arduino_secrets.h" 

//Tout ce qui concerne le wifi
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;     // le status du wifi

//Tout ce qui concerne le mysql
IPAddress server_addr(192,168,1,36);  // IP of the MySQL *server* here
char user[] = "arduino";              // MySQL user login username
char password[] = "arduino";        // MySQL user login password

//Ici on va définir toutes les choses qu'on va devoir inserer avec mysql
String ardMacAddress; //c'est la mac address de l'arduino
char recType[]; //c'est le type d'info qu'on envoie, entry ou exit
char INSERT_SQL[] = "INSERT INTO db_pretpi.test (abc) VALUES ('Salut')";

//je sais pas ce que ces deux lignes font, mais si je les enlève ça marche pas du coup voilà
WiFiClient client;  
MySQL_Connection conn((Client *)&client);


void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);

    // wait 5 seconds for connection:
    delay(5000);
  }
  
  ardMacAddress = getMacAddress();
}

void loop() {
  
  Serial.println("Connecting...");
  if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
    Serial.println("nice");
    // Initiate the query class instance
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    // Execute the query
    delay(10000);
    cur_mem->execute(INSERT_SQL);
    // Note: since there are no results, we do not need to read any data
    // Deleting the cursor also frees up memory used
    delete cur_mem;
  }
  else
    Serial.println("Connection failed.");
  conn.close();
}

//Cette fonction va retourner la mac address :)
//c'est la seule fonction qui a été prise de l'ancien projet x) 
String getMacAddress() {
  byte mac[6];
  WiFi.macAddress(mac);
  String cMac = "";
  for (int i = 0; i < 6; ++i) {
  if (String(mac[i],HEX).length() < 2)
  {
  cMac += 0;
  }
  cMac += String(mac[i],HEX);
  }
  cMac.toUpperCase();
  return cMac;
}
