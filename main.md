# Documentazione Progetto: Linux SysAdmin CLI Tool

## 1. Descrizione del Progetto

Il **Linux SysAdmin CLI Tool** (progettato in stile *Lubuntu Swag Style*) è un'applicazione da riga di comando scritta in C++20 sviluppata per semplificare e centralizzare le operazioni fondamentali di amministrazione di sistema su distribuzioni Linux. 

Il progetto adotta un'architettura **modulare header-only** combinata con un motore di autenticazione e persistenza dati basato su **SQLite3**. Il sistema distingue i privilegi tra utenti standard e l'utente amministratore **`root`**, garantendo sicurezza, isolamento dei dati ed esecuzione controllata dei comandi di sistema.

---

## 2. Struttura del Repository e dell'Architettura

```text
.
├── database/
│   └── login.db              # Database SQLite locale (Generato automaticamente al primo avvio, ignorato da Git)
├── librerie/
│   ├── generatore_password.h # Modulo per la generazione automatica di password ad alta entropia
│   ├── gestore_dischi.h      # Modulo per l'ispezione e la formattazione avanzata dei dischi (lsblk, mkfs)
│   ├── gestore_pacchetti.h   # Modulo universale per la gestione pacchetti (apt, dnf, pacman, zypper)
│   ├── menu_firewall.h       # Modulo per la configurazione e il monitoraggio di UFW
│   ├── menu_principale.h     # Menu di navigazione di primo livello per gli utenti standard
│   ├── menu_principale_root.h # Menu riservato all'amministratore (include modulo gestione utenti DB)
│   ├── menu_utenti.h         # Modulo per la gestione utenti di sistema Linux, gruppi e chmod
│   └── stato_rete.h          # Modulo per l'ispezione di schede e interfacce di rete (ip, ifconfig)
├── test/
│   └── main_prova.cpp        # Sandbox per test unitari e sviluppo modulare
├── Database.hpp              # Wrapper C++ OOP per l'interazione con SQLite3 tramite Prepared Statements
├── menu.h                    # Componente base per la rendering e selezione dei menu CLI
├── titoli.h                  # Helper per la formattazione grafica ANSI ed effetti terminale
├── main.cpp                  # Entry point del programma con gestione sessioni e flussi di autenticazione
├── .gitignore                # Regole di esclusione per file locali e database (.db)
└── README.md                 # Guida introduttiva e documentazione per la repository GitHub