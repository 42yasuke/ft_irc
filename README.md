# 💬 ft_irc

**ft_irc** est un projet réseau de l’école 42 dont l’objectif est de créer un **serveur IRC** basique (Internet Relay Chat), capable de gérer plusieurs clients simultanément, avec support des commandes essentielles du protocole IRC.

## 🎯 Objectif

Créer un **serveur IRC** conforme à la RFC 2812 (IRC Protocol), supportant :

- Connexions multiples via **sockets TCP**
- Gestion de canaux et d’utilisateurs
- Transmission de messages privés et de groupe
- Commandes de base IRC
- Permissions et modération

## 📦 Fonctionnalités

- 🧱 Serveur TCP multi-clients
- 🤝 Authentification (via password)
- 💬 Support des commandes :
  - `NICK`, `USER`, `JOIN`, `PART`
  - `PRIVMSG`, `NOTICE`
  - `TOPIC`, `KICK`, `INVITE`, `MODE`
  - `QUIT`
- 📡 Communication client ↔ client via le serveur
- 🧠 Gestion des canaux, utilisateurs et droits
- ⚠️ Gestion des erreurs & protocoles
- 🔐 Modes de canal (privé, topic restreint, etc.)

## 🧠 Stack & concepts utilisés

- 📡 Sockets TCP (C / POSIX)
- ⏳ `poll()` pour multiplexage d’I/O
- 🔄 Protocoles & parsing
- 🧵 Pas de thread : tout en single-thread non-bloquant
- 🧹 Memory management et gestion fine des ressources
- 🧼 Respect de la norme IRC & gestion d’erreurs propre

## 🛠️ Compilation

```bash
make
```

## ▶️ Lancement

```bash
./ircserv <port> <password>
```

Exemple :
```bash
./ircserv 6667 password42
```

## 💻 Connexion avec un client IRC

Tu peux utiliser un client IRC existant (comme irssi, weechat, HexChat, ou même telnet) :
```bash
telnet localhost 6667
```
Puis entrer manuellement :
```bash
NICK testuser
USER testuser 0 * :Real Name
JOIN #general
PRIVMSG #general :Hello world!
```

