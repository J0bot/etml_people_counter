
/*
 * Auteur : José Carlos Gasser
 * Date : 12.12.2021
 * Description : programme qui va être flash sur l'arduino et qui commande tout
 */
#include <iostream>
#include <string>
#include <algorithm>
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
char user[] = USER_MYSQL;              // MySQL user login username
char password[] = PASS_MYSQL;        // MySQL user login password

std::string ardMacAddress; //c'est la mac address de l'arduino, faut la mettre ici pck on en a besoin partout

//Variable client de la classe WiFiClient
WiFiClient client;
//L'objet conn de la classe mysql_connection fait référence à l'objet WifiClient
MySQL_Connection conn((Client *)&client);


void setup() {
  //Initialisation du bail pour avoir le port console série
  Serial.begin(9600);

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);

    // wait 5 seconds for connection:
    delay(5000);
  }

  //Connection to mysql database
  Serial.println("Connecting...");
  if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
    Serial.println("Connection successful !");
  }
  else
  {
    Serial.println("Connection failed.");
  }

  //Rajouter son addresse mac si elle n'existe pas dans la table t_arduino
  ardMacAddress = getMacAddress();
  std::string query_str = "INSERT IGNORE INTO db_pretpi.t_arduino SET ardMacAddress = "; //On va ecrire la query dans les values
  query_str.append(ardMacAddress); //Cette ligne c'est pour ajouter la mac address à la query
  const char *mysql_query = query_str.c_str(); //Ici faut transformer le string en char[], pck sinon la classe mysql accepte pas
  executeQuery(mysql_query);

}

void loop() {
  while (true)
  {
    std::string recType = "entry"; //c'est le type d'info qu'on envoie, entry ou exit

      delay(10000);
    if (recType == "entry")
    {
      insert_record(ardMacAddress, recType);
    }
  }
  conn.close(); //Si on a tout finit, on ferme la connection
  Serial.println("finished my job");
}

//Cette fonction va retourner la mac address :)
//c'est la seule fonction qui a été prise de l'ancien projet x) 
//Bon j'ai refait la fonction avec std::string, j'ai fait un peu au hasard mais ça compile du coup jsp
std::string getMacAddress() {
  byte mac[6];
  WiFi.macAddress(mac);
  std::string cMac = "";
  for (int i = 0; i < 6; ++i) {
  if (std::string(mac[i],HEX).length() < 2)
  {
  cMac.append(0);
  }
  cMac.append(std::string(mac[i],HEX));
  }
  std::transform(cMac.begin(), cMac.end(),cMac.begin(), ::toupper);
  return cMac;
}

//C'est la fonction qui nous permet d'executer une query
void executeQuery(const char mysql_query[])
{
  //Initiate the query class instance
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  // Execute the query
  cur_mem->execute(mysql_query);
  // Note: since there are no results, we do not need to read any data
  // Deleting the cursor also frees up memory used
  delete cur_mem;
}

//cette fonction permet d'inserer une donnée dans la table t_record
void insert_record(std::string ardMacAddress, std::string recType)
{
  std::string query_str = "INSERT INTO db_pretpi.t_record (recDate,ardMacAddress, recType ) VALUES (NOW(), "; //Design de la query
  query_str.append(ardMacAddress); //on ajoute la mac address dans le string
  query_str.append(", "); //on rajoute une virgule pour separer les value
  query_str.append(recType); //on rajoute le type de donnée qui doit renter
  query_str.append(")"); //On rajoute la parentèse de fin de query

  const char *mysql_query = query_str.c_str(); //transformer notre std::string en char array
  executeQuery(mysql_query); //On execute la fonction executeQuery
}
