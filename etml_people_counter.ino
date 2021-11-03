//Auteur : José Carlos Gasser
//Date : 02.11.2021
//Description : tout ce qu'il faut se trouve là dedans


// ---------------------------------------------------------------- //
// Arduino Ultrasoninc Sensor HC-SR04
// Re-writed by José Carlos Gasser
// Using Arduino IDE 1.8.16
// Using HC-SR04 Module
// Tested on 2 Novembre 2021
// ---------------------------------------------------------------- //


//le pin 10 s'attache au pin ECHO du sensor
int echoPin =  10;

//la pin 8 s'attache au pin Trig du sensor
int trigPin =  8;

//variable de la mesure du temps de voyage des ondes
long duration;

//variable de la distance mesurée
int distance;

//Cette fonction va s'executer une seule fois
void setup()
{
  pinMode(trigPin, OUTPUT); //faut setter le pin de trigger en output pour le trigger
  pinMode(echoPin, INPUT); //Faut setter le pin d'echo en input

  //Juste pour le debug, pour voir la mesure du capteur dans la console série
  Serial.begin(9600);
}

//Cette fonction s'execute tout le temps
void loop()
{
  digitalWrite(trigPin,LOW);//On va mettre en low le pin du trigger
  delayMicroseconds(2); //On attend deux microsecondes

  //On allume le pin pendant 10 microsecondes, en gros ici on va lancer des ultrasons
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  //Ici on va lire les infos du pin d'echo, cette fonction va nous retourner 
  //le travel time de l'onde de son qui a été lancée juste avant en microsecondes
  duration = pulseIn(echoPin, HIGH);

  //Calcul de la distance, la distance est égale au temps pour l'onde de partir et rebondir
  //fois la vitesse du son, le tout divisé par deux
  distance= duration * 0.034 / 2;
  
  //Ici pour le debug on va print sur la console les données de distance en cm
  Serial.print(distance);
  Serial.println(" cm");
}
