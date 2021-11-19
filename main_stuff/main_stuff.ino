/*
 * Auteur : José Carlos Gasser, Maxime Andrieux
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

char* ardMacAddress; //c'est la mac address de l'arduino, faut la mettre ici pck on en a besoin partout

//Variable client de la classe WiFiClient
WiFiClient client;
//L'objet conn de la classe mysql_connection fait référence à l'objet WifiClient
MySQL_Connection conn((Client *)&client);

//pins 
//redPin c'est la 1
//yellow c'est la A1


//La fonction setup va se lancer une seule fois
void setup() {
  //Initialisation du bail pour avoir le port console série
  Serial.begin(9600);

  pinMode(1, OUTPUT);
  pinMode(0, OUTPUT);


  // Ici on va essayer de se connecter au wifi
  while ( status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);

    // wait 5 seconds for connection to the wifi
    delay(5000);
  }

  //Connection to mysql database
  Serial.println("Connecting...");
  if (conn.connect(server_addr, 3306, user, password)) {

    //Petit delay de 1 secondes pour laisser le temps de se connecter
    delay(1000);
    Serial.println("Connection successful !");

    //Rajouter son addresse mac si elle n'existe pas dans la table t_arduino
    
    //On va attraper l'addresse mac de l'arduino
    ardMacAddress = getMacAddress();
    

    //On va afficher l'addresse mac pour du debug
    Serial.println(ardMacAddress);

    // Formater toute la query
    char* mysql_query = "INSERT IGNORE INTO db_pretpi.t_arduino SET ardMacAddress=\'"; //On va ecrire la query dans les values
    int string_length = sizeof(char)*1024; //on set la longeur du string à 1024 bytes
    char* request = (char*)malloc(string_length);  //On va allouer le string_length à notre requete
    int index = 0;
    while(mysql_query[index]!='\0') {
      request[index++] = mysql_query[index];
    }
    int index2 = 0;
    while(ardMacAddress[index2] != '\0') {
      request[index++] = ardMacAddress[index2++];
    }
    request[index++] = '\'';
    request[index] = '\0';

    //on va print la requete mysql sur la console série pour le debug
    Serial.println(request);

    //On execute la query
    executeQuery(request);
    free(request);
  }
  else
  {
    // Si la connection a vraiment fail on va afficher qu'elle a fail
    Serial.println("Connection failed.");
  }


}

// Cette fonction va tourner tout le temps
void loop() {
  
  while (true)
  {
    //Ici on va check si les gens rentrent ou sortent
    Serial.print("Pin A5 : ");
    Serial.println(analogRead(A5));
    if(analogRead(A5)<70)
    {
      digitalWrite(0, HIGH);  
    }
    else
    {
      digitalWrite(0, LOW);
    }
    Serial.print("Pin A6 : ");
    Serial.println(analogRead(A6));
    if(analogRead(A6)<70)
    {
      digitalWrite(1, HIGH);  
    }
    else
    {
      digitalWrite(1, LOW);
    }

    //Si laser : 31, si pas laser : 1023
    
    char* recType = "exit"; //c'est le type d'info qu'on envoie, entry ou exit

      delay(1000); //delai de 10 secondes entre chaque entry pour le debug
    if (recType == "exit" || recType == "entry")
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
//Au final on est allé sur du char avec emixam
char* getMacAddress() {
  byte mac[6]; //c'est un tableau de byte de taille 6 de la librairie arduino
  WiFi.macAddress(mac); //Cette fonction assigne la mac address à mon tableau de byte
  String cMac = ""; //On set notre string à une valeur nulle
  for (int i = 0; i < 6; ++i) { //On va créer une boucle for pour itérer dans el tableau de bytes
    if (String(mac[i],HEX).length() < 2)
      {
        cMac += 0;
      }
    cMac += String(mac[i],HEX); //On va incrémenter notre string avec les données du tableau de byte et les transformer en hexadecimal
  }
  cMac.toUpperCase(); //On met toutes nos données en majuscule
  
  int string_length = sizeof(char)*1024; //On définit la taille de notre buffer
  char* macChar = (char*)malloc(string_length); //On implémente la taille de notre buffer au charr array de la mac address
  cMac.toCharArray(macChar,string_length); //on va transformer les String de la librarie arduino en char array accepté par la librarie mysql
  
  return macChar; //On retourne notre mac addresse sous forme de char*
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
void insert_record(char* ardMacAddress, char* recType)
{
  //tout ce code ne respecte rien, mais il marche, c'est l'important
  int string_length = sizeof(char)*1024;
  char* query_str = "INSERT INTO db_pretpi.t_record (recDate,ardMacAddress, recType ) VALUES (NOW(), \'"; //Design de la query

  char* request = (char*)malloc(string_length);
  
  int index = 0;
  while(query_str[index]!='\0') {
    request[index] = query_str[index];
    index++;
  }
  int index2 = 0;
  while(ardMacAddress[index2] != '\0') {
    request[index++] = ardMacAddress[index2];
    index2++;
  }
  request[index++] = '\''; request[index++] = ','; request[index++] = '\'';
  int index3 = 0;
  while(recType[index3] != '\0') {
    request[index++] = recType[index3];
    index3++;
  }
  
  request[index++] = '\'';
  request[index++] = ')';
  request[index] = '\0';

  Serial.println(request); //On print la requete dans la console pour le debug

  executeQuery(request); //On execute la fonction executeQuery
  free(request);
}
