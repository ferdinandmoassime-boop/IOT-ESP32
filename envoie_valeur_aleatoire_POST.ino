#include <WiFi.h>              // Bibliothèque permettant la connexion au WiFi
#include <HTTPClient.h>        // Bibliothèque pour envoyer des requêtes HTTP

// Nom du réseau WiFi
const char* ssid = "TPSN035";

// Mot de passe du réseau WiFi
const char* password = "BTSSN2022";

// Adresse du serveur PHP qui recevra les données
const char* serverName = "http://192.168.100.68/btsciel/data.php";

void setup() {

  // Démarre la communication série à 115200 bauds
  Serial.begin(115200);

  // Connexion au réseau WiFi avec le SSID et le mot de passe
  WiFi.begin(ssid, password);

  // Boucle tant que l'ESP32 n'est pas connecté au WiFi
  while (WiFi.status() != WL_CONNECTED) {

    // Attend 500 millisecondes
    delay(500);

    // Affiche un point dans le moniteur série pour montrer la tentative de connexion
    Serial.print(".");
  }
}

void loop() {

  // Vérifie si l'ESP32 est connecté au WiFi
  if (WiFi.status() == WL_CONNECTED) {

    // Génère une valeur aléatoire entre 0 et 99
    int valeur = random(0,100);

    // Création de l'objet HTTPClient
    HTTPClient http;

    // Démarre la connexion HTTP vers le serveur
    http.begin(serverName);

    // Ajoute l'en-tête HTTP pour indiquer le type de données envoyées
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Prépare les données à envoyer sous la forme "valeur=XX"
    String donnee = "valeur=" + String(valeur);

    // Affiche le texte "donnee transmise"
    Serial.print("donnee transmise ");

    // Affiche les données envoyées au serveur
    Serial.println(donnee);

    // Envoie une requête POST avec les données
    int httpReponse = http.POST(donnee);

    // Affiche le texte du code de réponse HTTP
    Serial.print("HTTP Reponse code: ");

    // Affiche le code de réponse du serveur
    Serial.println(httpReponse);

    // Vérifie si la requête HTTP a réussi
    if (httpReponse > 0) {

      // Récupère la réponse envoyée par le serveur
      String payload = http.getString();

      // Affiche le texte "Réponse serveur"
      Serial.print("Réponse serveur: ");

      // Affiche la réponse du serveur
      Serial.println(payload);

    } else {

      // Affiche un message d'erreur si la requête POST échoue
      Serial.print("Erreur lors de la requête POST: ");

      // Affiche le détail de l'erreur HTTP
      Serial.println(http.errorToString(httpReponse).c_str());
    }

    // Ferme la connexion HTTP
    http.end();
  }

  // Attend 5 secondes avant le prochain envoi
  delay(5000);
}
