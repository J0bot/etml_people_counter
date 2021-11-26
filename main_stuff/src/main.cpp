/*
 * Auteur : José Carlos Gasser, Maxime Andrieux
 * Date : 12.12.2021
 * Description : programme qui va être flash sur l'arduino et qui commande tout
 */
#include <Arduino.h>

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
//IPAddress server_addr(192,168,1,36);  // IP of the MySQL *server* here
IPAddress server_addr(172,20,110,96);  // IP of the MySQL *server* here
char user[] = USER_MYSQL;              // MySQL user login username
char password[] = PASS_MYSQL;        // MySQL user login password

char* ardMacAddress; //c'est la mac address de l'arduino, faut la mettre ici pck on en a besoin partout

//Variable client de la classe WiFiClient
WiFiClient client;
//L'objet conn de la classe mysql_connection fait référence à l'objet WifiClient
MySQL_Connection conn((Client *)&client);

//define de states of the lasers
#define R 1
#define L 2
#define LR 3
int treshold = 70;
static int state_index = 0;
int states[4];

///
/// DECLARATION DE TOUTES LES FONCTIONS
///

//Cette fonction va retourner la mac address
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

  //On va allouer string_length de place dans la mémoire pour notre string de query
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
  free(request); //Ne pas oublier de libérer notre requete de la mémoire, sinon tout va être utilisé et ça ne marchera plus
}

int getState()
{
  int state;
  //Si les deux lasers sont detectés
  if(analogRead(A5)<treshold && analogRead(A6)<treshold )
    state = LR;

  //si on detecte que le laser de gauche
  if(analogRead(A5)<treshold && analogRead(A6)>treshold )
    state = L;
    
  //Si on detecte que le laser de droite
  if(analogRead(A5)>treshold && analogRead(A6)<treshold )
    state = R;

  //Si on detecte aucun des deux lasers
  if(analogRead(A5)>treshold && analogRead(A6)>treshold )
    state = 0;

  return state;
}

// Cette fonction va checker si des gens entrent ou sortent
int checklasers()
{
  
int state = getState();
  int prev_state;
  Serial.print("state = ");
  Serial.println(state);
  if (state >= 4) {
    Serial.println("ERROR! index out of array! Giving up.");
    state_index = 0;
    return 0;
  }
  //if the index is 0, add the value to the index and return.
  if (state_index == 0) {
    //but not if it's an LR value (both lasers are not being intersected). index 0 should always be
    //an L or an R.
    if (state != LR) {
      states[state_index] = state;
      state_index++;
    }
    return 0;
  }
  //if the state is the same as the old one, return.
  if (states[state_index - 1] == state) {
    return 0;
  }
  //if were at the end of the array and the lasers are unblocked, someone entered/exited.
  if (state == LR && state_index >= 3) {
    Serial.println("ENTRANCE/EXIT");
    if (states[2] == L) {
      Serial.println("ENTRANCE");
      state_index = 0;
      return L;
      } else if (states[2] == R) {
      Serial.println("EXIT");
      state_index = 0;
      return R;
    } else {
      Serial.println("What? it's not an entrance nor an exit!");
      state_index = 0;
      return 0;
    }

    //normally the index 1 should always be at 0 if someone crossed the lasers, but
    //this is sometimes not the case. We still consider valid the entrance, but warn
    //that it MAY be incorrect.
    if (states[1] != 0)
      Serial.println("BUG?");
    state_index = 0;
    return 0;
    //if only the lasers are unblocked, it's not valid. if an LR happens before index 3,
    //it's not a valid entry (the person walked away?)
  } else if (state == LR) {
    Serial.println("GIVING UP");
    //resetting the index
    state_index = 0;
    return 0;
  }

  //if the index is at least 2, we check if the value from two steps ago is the same as the
  //current one (smth like L,0,L). It means the person is backing away, so it is not written in
  //the index. (it will only be if it's a R in this example.)
  if (state_index >= 2) {
    prev_state = states[state_index - 2];
    if (state == prev_state) {
      Serial.println("UNDECIDED?");
      return 0;
    }
    //if we're at the index 3 and the starting state is the same as the current one, we can just
    //stop and start from the index 0 again, like nothing happened. (ex: L,0,R,L)
    //note: in a dream world, this state should not happen, but if it does we will be out of
    //the array and the program will crash. And we're not in a dream world.
    if (state_index >= 3 && states[0] == state) {
      state_index = 0;
      states[state_index] = state;
      state_index++; // could just put state_index = 1;, but for clarity's sake...
      Serial.println("RESET");
    }
    //if the values are different, we can safely put the current state in the array.
    states[state_index] = state;      
    state_index++;
    return 0;
  }

  //if nothing above applies to the current state, add it to the array and increment the
  //index.
  states[state_index] = state;
  state_index++;
  return 0;


}


//Cette fonction va allumer ou eteindre selon la valeur du capteur
void blink_leds()
{
  Serial.print("Pin A5 : ");
  Serial.println(analogRead(A5));
  Serial.print("Pin A6 : ");
  Serial.println(analogRead(A6));

  if(analogRead(A5)<treshold)
    digitalWrite(0, HIGH);  
  else
    digitalWrite(0, LOW);

  if(analogRead(A6)<treshold)
    digitalWrite(1, HIGH);  
  else
    digitalWrite(1, LOW);

  return;
}


///
/// FONCTIONS DE SETUP ET LOOP
///


//La fonction setup va se lancer une seule fois
void setup() {
  //Initialisation du bail pour avoir le port console série
  Serial.begin(9600);
  
  pinMode(1, OUTPUT);
  pinMode(0, OUTPUT);

  memset(states, 0, sizeof(int) * 4); //////////////////////////

  // Ici on va essayer de se connecter au wifi
  while ( status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    Serial.println("Trying connection to wifi...");
    // wait 5 seconds for connection to the wifi
    delay(5000);
  }

  //Connection to mysql database
  Serial.println("Connecting...");
  if (conn.connect(server_addr, 3306, user, password)) {

    //Petit delay de 1 secondes pour laisser le temps de se connecter
    delay(2000);
    Serial.println("Connection successful !");
    
    
    ///Rajouter son addresse mac si elle n'existe pas dans la table t_arduino
    
    //On va attraper l'addresse mac de l'arduino
    ardMacAddress = getMacAddress();
    

    //On va afficher l'addresse mac pour du debug
    Serial.println(ardMacAddress);
    delay(1000);
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
    delay(1000);
    //On execute la query
    executeQuery(request);
    free(request);
  }
  else
  {
    // Si la connection a vraiment fail on va afficher qu'elle a fail
    Serial.println("Connection failed.");
    delay(5000);
  }
}

// Cette fonction va tourner tout le temps
void loop() {
 
  blink_leds();
  int result = checklasers();

  //Si le resultat de nos tests est de L, nous allons envoyer une entry
  if(result == L)
  {
    char* recType = "entry"; //c'est le type d'info qu'on envoie, entry ou exit
    Serial.println("entry");
    insert_record(ardMacAddress, recType);
  }

  //Si le resultat de nos tests est de R, nous allons envoyer une exit
  if(result == R)
  {
    char* recType = "exit"; //c'est le type d'info qu'on envoie, entry ou exit
    Serial.println("exit");
    insert_record(ardMacAddress, recType);
  }    
  delay(500);

}