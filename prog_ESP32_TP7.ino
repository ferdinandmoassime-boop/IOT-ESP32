#include <WiFi.h>              // Bibliothèque pour gérer la connexion WiFi
#include <HTTPClient.h>        // Bibliothèque pour envoyer des requêtes HTTP

const char* ssid = "TPSN035";  // Nom du réseau WiFi
const char* password = "BTSSN2022"; // Mot de passe du réseau WiFi
const char* serverName = "http://192.168.100.76/btsciel/data.php"; // Adresse du serveur PHP

void setup() {

  Serial.begin(115200); // Démarre la communication série à 115200 bauds

  WiFi.begin(ssid, password); // Connexion au réseau WiFi avec le SSID et le mot de passe

  // Boucle tant que l'ESP32 n'est pas connecté au WiFi
  while (WiFi.status() != WL_CONNECTED) {

    delay(500); // Attente de 500 ms

    Serial.print("."); // Affiche un point dans le moniteur série pour montrer la tentative de connexion

    Serial.println(WiFi.localIP()); // Affiche l'adresse IP locale obtenue par l'ESP32
  }
}

void loop() {

  // Vérifie si le WiFi est toujours connecté
  if (WiFi.status() == WL_CONNECTED) {

    int valeur = random(0,100); // Génère une valeur aléatoire entre 0 et 99

    HTTPClient http; // Création d'un objet HTTPClient

    http.begin(serverName); // Démarre la connexion HTTP avec le serveur

    // Ajoute l'en-tête HTTP indiquant le type de données envoyées
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Prépare les données à envoyer sous forme "valeur=XX"
    String donnee = "valeur=" + String(valeur);

    Serial.print("donnee transmise "); // Message affiché avant l'envoi
    Serial.println(donnee); // Affiche les données envoyées

    // Envoie une requête POST avec les données
    int httpReponse = http.POST(donnee);

    Serial.print("HTTP Reponse code: "); // Affiche le code de réponse HTTP
    Serial.println(httpReponse);

    // Vérifie si la requête a réussi
    if (httpReponse > 0) {

      String payload = http.getString(); // Récupère la réponse du serveur

      Serial.print("Réponse serveur: "); // Affiche le message du serveur
      Serial.println(payload);

    } else {

      // Affiche un message d'erreur si la requête POST échoue
      Serial.print("Erreur lors de la requête POST: ");

      // Affiche le détail de l'erreur HTTP
      Serial.println(http.errorToString(httpReponse).c_str());
    }

    http.end(); // Ferme la connexion HTTP
  }

  delay(5000); // Attend 5 secondes avant le prochain envoi
}
