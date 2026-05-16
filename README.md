# 💧 Consdeau — Gestion intelligente de la consommation d'eau (2025)

Application embarquée et graphique permettant de surveiller, analyser et limiter
la consommation d'eau d'un foyer en temps réel.

---

## 🎯 Objectif

Sensibiliser les utilisateurs à leur consommation d'eau grâce à :
- Un suivi en temps réel par débitmètre
- Des graphiques de consommation personnalisés
- Des alertes automatiques en cas de dépassement de seuil
- Une coupure automatique d'eau si nécessaire

---

## 🏗️ Architecture du système
Débitmètre (Hall) → ESP32/NodeMCU → WebSocket → Raspberry Pi
↓
MySQL (WampServer)
↓
Application Qt/QML (C++)

---

## ⚙️ Technologies utilisées

### Application
- **C++ / Qt 6** — logique métier
- **QML / Qt Quick** — interface utilisateur
- **Qt Charts** — graphiques de consommation
- **Qt WebSocket** — communication temps réel
- **Qt SQL** — connexion base de données

### Serveur & données
- **MySQL** — stockage des utilisateurs et historiques
- **WampServer / phpMyAdmin** — gestion de la base de données

### Matériel
- **ESP32 / NodeMCU** — acquisition des données capteur
- **Débitmètre à effet Hall** — mesure du débit d'eau

---

## ✨ Fonctionnalités

- 🔐 Identification de l'utilisateur par avatar
- 📊 Graphiques de consommation (vue jour / vue mois)
- 🔔 Alertes visuelles et sonores sur seuil dépassé
- 🚰 Coupure automatique de l'électrovanne
- 🌐 Communication WebSocket entre ESP32 et Raspberry Pi
- 🗃️ Historique de consommation par utilisateur en base de données

---

## 👥 Équipe

Projet réalisé en équipe de 3 étudiants dans le cadre d'un BTS CIEL :
- **Étudiant n°1** — Interface web & serveur (PHP, MySQL)
- **Étudiant n°2 (moi)** — IHM utilisateur (Qt/QML/C++)
- **Étudiant n°3** — Partie matérielle (ESP32, débitmètres, électrovannes)

---

## 📸 Aperçu
<img width="795" height="592" alt="width_795" src="https://github.com/user-attachments/assets/795aa56a-51fc-42ff-91dd-dcb3bad3b611" />
<img width="790" height="600" alt="width_790" src="https://github.com/user-attachments/assets/3ff63fd8-71ef-4376-b03a-2e3a811a9da5" />
