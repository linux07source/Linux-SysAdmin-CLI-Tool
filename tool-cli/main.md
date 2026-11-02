# Documentazione Progetto: Linux SysAdmin CLI Tool

## 1. Descrizione del Progetto

Il **Linux SysAdmin CLI Tool** è un'applicazione da riga di comando scritta in C++20 sviluppata per semplificare le operazioni fondamentali di amministrazione di sistema su distribuzioni Linux. Il progetto adotta un'architettura **modulare header-only**, separando la logica di ciascun ambito operativo in librerie dedicate all'interno della cartella `librerie/`.

## 2. Struttura del Progetto

```text
.
├── librerie/
│   ├── gestore_dischi.h      # Modulo per l'ispezione e formattazione dischi
│   ├── gestore_pacchetti.h   # Modulo per la gestione dei pacchetti (multi-distro)
│   ├── menu_firewall.h       # Modulo per la gestione di UFW
│   ├── menu_principale.h     # Modulo per la generazione del menu di primo livello
│   └── menu_utenti.h         # Modulo per la gestione di utenti, gruppi e permessi
├── test/
│   └── main_prova.cpp        # Sandbox per test e sviluppo modulare
├── menu.h                    # Libreria base per l'interfaccia a menu
├── titoli.h                  # Modulo per stili grafici e formattazione ANSI
├── main.cpp                  # Entry point del programma in produzione
└── README.md                 # Documentazione repository GitHub
```

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

> **Nota di compilazione:** Assicurarsi sempre che le strutture `comandi_linux` e `Firewall` vengano dichiarate **prima** di includere gli header dei menu per evitare errori di scope (`not declared in this scope`).

## 4. Moduli e Librerie

### `librerie/menu_principale.h`

Definisce la struttura e le voci del menu di navigazione principale.

* **Voci del menu:**
  1. `Tool utenti`
  2. `Impostazioni Firewall`
  3. `Gestione Pacchetti`
  4. `Gestione Dischi`
  5. `Esci`

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
  * Installazione pacchetti
  * Rimozione pacchetti
  * Reinstallazione forzata pacchetti
  * Aggiornamento completo del sistema

### `librerie/gestore_dischi.h` (`GestoreDischi`)

Modulo per la gestione dell'hardware di archiviazione e delle partizioni.

* **Funzionalità:**
  * Visualizzazione dischi e partizioni con `lsblk`
  * Smontaggio automatico ed esecuzione della formattazione con supporto a filesystem `ext4`, `ntfs`, `vfat` e `exfat`

## 5. Compilazione ed Esecuzione

### Compilazione del sorgente in `test/`

Se si compila dalla cartella radice del progetto:

```bash
g++ -I. test/main_prova.cpp -o apptools && ./apptools
```

### Compilazione del sorgente di produzione (`main.cpp`)

```bash
g++ main.cpp -o apptools && ./apptools
```

> **Risoluzione errori carattere non valido (NBSP):** Se si presentano errori di tipo `extended character \xA0 is not valid in an identifier`, ripulire il sorgente tramite:
> ```bash
> sed -i 's/\xA0/ /g' test/main_prova.cpp
> ```
