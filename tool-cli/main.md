# Documentazione Progetto: Linux SysAdmin CLI Tool

## 1. Descrizione del Progetto
Il **Linux SysAdmin CLI Tool** è un'applicazione da riga di comando scritta in C++20 sviluppata per semplificare le operazioni fondamentali di amministrazione di sistema su distribuzioni Linux. Il progetto adotta un'architettura **modulare header-only**, separando la logica di ciascun ambito operativo in librerie dedicate all'interno della cartella `librerie/`.

---

## 2. Struttura del Progetto

```
.
├── librerie/
│   ├── gestore_pacchetti.h   # Modulo per la gestione dei pacchetti (multi-distro)
│   ├── menu_firewall.h       # Modulo per la gestione di UFW
│   ├── menu_principale.h     # Modulo per la generazione del menu di primo livello
│   └── menu_utenti.h         # Modulo per la gestione di utenti, gruppi e permessi
├── menu.h                    # Libreria base per l'interfaccia a menu
├── titoli.h                  # Modulo per stili grafici e formattazione ANSI
├── main.cpp                  # Entry point del programma in produzione
└── main_prova.cpp            # Sandbox di test e refactoring
```

---

## 3. Architettura e Strutture Dati

Per l'incapsulamento e la gestione dei dati tra i moduli vengono utilizzate due strutture principali:

### `comandi_linux`
Gestisce le informazioni relative agli utenti, ai permessi e all'esecuzione dei comandi di sistema.

```cpp
struct comandi_linux {
    std::string nomeUtente = "";
    std::string passwordUtente = "";
    std::string nomeGruppo = "";
    std::string targetFile = "";
    std::string comandoSistema = "";
};
```

### `Firewall`
Contiene la configurazione per l'apertura o la chiusura delle porte di rete.

```cpp
struct Firewall {
    int PORT = 0;
    std::string PROTOCOLLO = "";
};
```

---

## 4. Moduli e Librerie

### `librerie/menu_principale.h`
Definisce la struttura e le voci del menu di navigazione principale.
* **Voci:**
  1. `Tool utenti`
  2. `Impostazioni Firewall`
  3. `Gestione Pacchetti`
  4. `Esci`

### `librerie/menu_utenti.h` (`gestisciMenuUtenti`)
Incapsula tutta la logica interattiva per la gestione degli utenti e del file system.
* **Funzionalità:**
  * Creazione utente (`sudo adduser`)
  * Modifica password (`sudo passwd`)
  * Modifica permessi file/cartelle (`chmod`)
  * Assegnazione gruppi (`sudo usermod -aG`)
  * Elenco utenti registrati (`/etc/passwd`)
  * Eliminazione utente con rimozione home (`sudo userdel -r`)

### `librerie/menu_firewall.h` (`gestisciMenuFirewall`)
Gestisce la sicurezza di rete interagendo con **UFW** (Uncomplicated Firewall).
* **Funzionalità:**
  * Apertura porte specificando il protocollo (`sudo ufw allow <port>/<proto>`)
  * Visualizzazione dello stato attuale e delle porte aperte (`sudo ufw status`)

### `librerie/gestore_pacchetti.h` (`GestorePacchetti`)
Modulo universale multi-distro. Rileva automaticamente il package manager installato nel sistema (`apt`, `dnf`, `pacman`, `zypper`) ed esegue i comandi adattando i flag nativi.
* **Funzionalità:**
  * Inserimento / Installazione pacchetti
  * Rimozione / Disinstallazione pacchetti
  * Reinstallazione forzata pacchetti
  * Aggiornamento completo del sistema

---

## 5. Compilazione ed Esecuzione

Per compilare il progetto da terminale utilizzando `g++`:

### Compilazione del programma principale
```bash
g++ main.cpp -o main
./main
```

### Compilazione dell'ambiente di prova (`main_prova.cpp`)
```bash
g++ main_prova.cpp -o main_prova && ./main_prova
```

> **Nota:** Assicurarsi che le strutture `comandi_linux` e `Firewall` siano definite **prima** dell'inclusione degli header della cartella `librerie/` nei file punto di ingresso (`main.cpp` e `main_prova.cpp`) per garantire la corretta visibilità dello scope.