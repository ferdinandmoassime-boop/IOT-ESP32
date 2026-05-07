<?php

// Active l'affichage de toutes les erreurs PHP
error_reporting(E_ALL);

// Affiche les erreurs directement dans la page
ini_set('display_errors', 1);

// ================== Fuseau horaire ==================

// Définit le fuseau horaire sur Nouméa
date_default_timezone_set("Pacific/Noumea");

// ================== Fichiers ==================

// Chemin du fichier texte contenant la dernière valeur reçue
$txtFile = __DIR__ . "/valeur.txt";

// Chemin du fichier CSV contenant l'historique des valeurs
$csvFile = __DIR__ . "/valeur.csv";

// ================== POST (ESP32 envoie la donnée) ==================

// Vérifie si la requête reçue est une requête POST
if ($_SERVER['REQUEST_METHOD'] === 'POST') {

    // Vérifie si la variable "valeur" existe dans les données POST
    if (isset($_POST['valeur'])) {

        // Récupère la valeur envoyée par l'ESP32
        $valeur = $_POST['valeur'];

        // ================== Sauvegarde TXT ==================

        // Enregistre la valeur dans le fichier valeur.txt
        file_put_contents($txtFile, $valeur);

        // ================== Sauvegarde CSV ==================

        // Récupère la date actuelle
        $date = date("Y-m-d");

        // Récupère l'heure actuelle
        $heure = date("H:i:s");

        // Ouvre le fichier CSV en mode ajout
        $fichier = fopen($csvFile, "a");

        // Ajoute une ligne dans le CSV : date, heure, valeur
        fputcsv($fichier, [$date, $heure, $valeur]);

        // Ferme le fichier CSV
        fclose($fichier);

        // Envoie "OK" comme réponse à l’ESP32
        echo "OK";

    } else {

        // Message d'erreur si aucune valeur n'est reçue
        echo "Erreur : pas de valeur reçue";
    }

    // IMPORTANT : arrête le script ici pour ne pas afficher le HTML
    exit;
}

// ================== GET (navigateur affiche la valeur) ==================

// Texte affiché par défaut si aucune donnée n'existe
$valeurAffiche = "Aucune valeur reçue";

// Vérifie si le fichier valeur.txt existe
if (file_exists($txtFile)) {

    // Lit le contenu du fichier texte
    $valeur = file_get_contents($txtFile);

    // Sécurise l'affichage HTML
    $valeurAffiche = htmlspecialchars($valeur);
}
?>

<!DOCTYPE html>
<html lang="fr">

<head>

    <!-- Encodage UTF-8 -->
    <meta charset="UTF-8">

    <!-- Titre de la page -->
    <title>Donnée ESP32</title>

    <!-- Rafraîchissement automatique toutes les 2 secondes -->
    <meta http-equiv="refresh" content="2">

    <style>

        /* Style général de la page */
        body {
            font-family: Arial; /* Police d'écriture */
            text-align: center; /* Centre le texte */
            margin-top: 50px;   /* Marge en haut */
        }

        /* Style de la boîte contenant la valeur */
        .box {
            font-size: 30px;               /* Taille du texte */
            border: 2px solid black;       /* Bordure noire */
            padding: 20px;                 /* Espacement intérieur */
            display: inline-block;         /* Affichage en bloc */
            border-radius: 10px;           /* Coins arrondis */
            background-color: #f2f2f2;    /* Couleur de fond */
        }

    </style>
</head>

<body>

    <!-- Titre affiché dans la page -->
    <h1>Valeur reçue depuis l'ESP32</h1>

    <!-- Affiche la valeur reçue -->
    <div class="box"><?php echo $valeurAffiche; ?></div>

</body>
</html>