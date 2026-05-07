# IOT-ESP32

Ce projet consiste a comprendre comment un microcontrôleur ESP32 peut envoyer une donnée vers un serveur web et comment cette donnée peut être affichée sur une page web.

ETAPE 1: Connexion de l'ESP32 au WiFi.

Dans un permier temps il faut connecter l'ESP32 au wifi du lycée avec Arduino IDE. Nous avons configuré le SSID, le mot de passe et sélectionné le bon port COM. Une fois le programme téléversé, l’ESP32 s’est connecté au réseau et a affiché son adresse IP dans le moniteur série. Cette adresse permet à la carte de communiquer avec le serveur Ubuntu.

Étape 2 – Préparation du serveur Ubuntu

Dans cette étape, nous avons préparé un serveur web Apache sur la machine virtuelle Ubuntu. Nous avons créé une page dynamique en PHP appelée data.php dans le dossier du serveur web. Cette page sert à recevoir les données envoyées par l’ESP32. Nous avons ensuite testé le fonctionnement du serveur depuis un navigateur web.

Étape 3 – Envoi des données avec l’ESP32

Dans cette étape, l’ESP32 envoie une valeur au serveur grâce à une requête HTTP POST. Le programme génère une donnée puis la transmet au fichier data.php via le réseau WiFi. Le moniteur série affiche la donnée envoyée ainsi que la réponse du serveur. Cette étape montre comment un objet connecté peut communiquer avec un serveur web.


Étape 4 – Réception et stockage des données

Dans cette étape, le serveur reçoit les données envoyées par l’ESP32 et les enregistre dans des fichiers. Le fichier valeur.txt contient la dernière valeur reçue tandis que valeur.csv conserve un historique avec la date et l’heure. Nous avons aussi utilisé plusieurs commandes Linux pour créer et gérer les fichiers. Cette étape permet de comprendre comment stocker des données sur un serveur.


Étape 5 – Affichage des données sur une page web

Dans cette dernière étape, nous avons créé une page web qui affiche les données envoyées par l’ESP32. Le fichier index.php lit la dernière valeur enregistrée dans valeur.txt. La page se met automatiquement à jour toutes les trois secondes pour afficher les nouvelles données. Cela permet de visualiser les informations de l’ESP32 en temps réel depuis un navigateur web.
