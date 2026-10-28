# 🐧 Linux SysAdmin CLI Tool

Un potente tool a riga di comando scritto in **C++** per l'amministrazione di sistemi Linux, caratterizzato da un'architettura **modulare header-only** pulita ed estensibile.

---

## 🚀 Funzionalità Principali

*   👥 **Gestione Utenti:** Creazione, modifica password, gestione gruppi (`usermod`), modifica permessi (`chmod`), visualizzazione database utenti ed eliminazione sicura con rimozione della home.
*   🔥 **Configurazione Firewall (UFW):** Apertura porte (TCP/UDP) e visualizzazione in tempo reale dello stato delle regole attive.
*   📦 **Gestione Pacchetti Multi-Distro:** Rilevamento automatico del package manager di sistema (`apt`, `dnf`, `pacman`, `zypper`) per installare, disinstallare, reinstallare pacchetti e aggiornare l'intero sistema operativo.
*   🎨 **Interfaccia TUI Modulare:** Navigazione a menu interattivi e puliti, separati in moduli logici indipendenti.

---

## 📁 Architettura del Progetto

Il progetto adotta una struttura modulare basata su librerie `header-only` per mantenere il codice sorgente snello e facilmente manutenibile:

```text
.
├── librerie
│   ├── gestore_pacchetti.h   # Modulo di gestione pacchetti multi-distro
│   ├── menu.h                # Libreria base per la gestione dei menu interattivi
│   ├── menu_firewall.h       # Modulo logico e visivo per le impostazioni UFW
│   ├── menu_principale.h     # Definizione e voci del menu principale
│   └── menu_utenti.h         # Modulo logico e visivo per la gestione utenti
├── main.cpp                  # Entry point principale del programma
└── README.md
