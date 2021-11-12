/*
  This example connects to an encrypted WiFi network (WPA/WPA2).
  Then it prints the MAC address of the board,
  the IP address obtained, and other network details.
  Then it continuously pings given host specified by IP Address or name.

  Circuit:
  * Board with NINA module (Arduino MKR WiFi 1010, MKR VIDOR 4000 and UNO WiFi Rev.2)

  created 13 July 2010
  by dlf (Metodo2 srl)
  modified 09 June 2016
  by Petar Georgiev
*/
#include <SPI.h>
#include <WiFiNINA.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;     // the WiFi radio's status

char INSERT_SQL[] = "INSERT INTO db_pretpi.test (abc) VALUES ('Salut')";


// Specify IP address or hostname
String hostName = "192.168.1.1";
int pingResult;

IPAddress server_addr(192,168,1,36);  // IP of the MySQL *server* here
char user[] = "arduino";              // MySQL user login username
char password[] = "arduino";        // MySQL user login password

String ardMacAddress;

WiFiClient client;  
MySQL_Connection conn((Client *)&client);


void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);

    // wait 5 seconds for connection:
    delay(5000);
  }

  // you're connected now, so print out the data:
  Serial.println("You're connected to the network");

  String ardMacAddress = getMacAddress();
  Serial.println(mac);
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
