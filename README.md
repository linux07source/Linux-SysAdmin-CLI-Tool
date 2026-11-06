# Documentazione Progetto: Linux SysAdmin CLI Tool

## 1. Descrizione del Progetto

Il **Linux SysAdmin CLI Tool** è un'applicazione da riga di comando scritta in C++20 sviluppata per semplificare e centralizzare le operazioni fondamentali di amministrazione di sistema su distribuzioni Linux.

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
├── menu.h                    # Componente base per il rendering e la selezione dei menu CLI
├── titoli.h                  # Helper per la formattazione grafica ANSI ed effetti terminale
├── main.cpp                  # Entry point del programma con gestione sessioni e flussi di autenticazione
├── .gitignore                # Regole di esclusione per file locali e database (.db)
└── README.md                 # Guida introduttiva e documentazione per la repository GitHub
```

---

## 3. Autenticazione, Persistenza e Sicurezza (SQLite3)

### 3.1 Database SQLite (`Database.hpp`)
Il sistema si interfaccia con il file SQLite `database/login.db` tramite la libreria wrapper `Database.hpp`, fornendo le seguenti funzionalità:
* **Generazione Automatica**: All'avvio dell'applicazione viene creata in automatico la directory `database/` e la tabella `registrazione` se non già esistenti.
* **Account Amministratore Predefinito**: Viene iniettato l'account primario di sistema:
  * **Username**: `root`
  * **Password**: `root`
* **Isolamento Repository (`.gitignore`)**: Per motivi di sicurezza e tutela della privacy, la cartella `database/` e qualsiasi file `.db` non vengono tracciati da Git né caricati su GitHub.

### 3.2 Struttura della Tabella `registrazione`

```sql
CREATE TABLE IF NOT EXISTS registrazione (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nome TEXT NOT NULL,
    cognome TEXT NOT NULL,
    email TEXT UNIQUE NOT NULL,
    username TEXT UNIQUE NOT NULL,
    password TEXT NOT NULL,
    data_registrazione TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```

### 3.3 Flusso di Autenticazione & Gestione Ruoli
1. **Verifica Iniziale**: Il sistema interroga il database per verificare la presenza di account utente oltre a quello di `root`.
2. **Primo Avvio**: Se non vi sono utenti registrati, la CLI forza la procedura di registrazione di un nuovo utente prima di concedere l'accesso.
3. **Avvii Successivi**: Presenta direttamente la schermata di Login.
4. **Routing Dinamico dei Menu**:
   * **Utente Standard**: Rediretto verso `creaMenuPrincipale()` (`menu_principale.h`).
   * **Utente Root**: Rediretto verso `creaMenuPrincipaleRoot()` (`menu_principale_root.h`), sbloccando la funzione avanzata `gestisciEliminazioneUtenti()`.
5. **Protezione Account Root**: L'account `root` è protetto da un blocco di sicurezza a livello di codice che ne impedisce l'auto-eliminazione dal database.

---

## 4. Strutture Dati Core

### `comandi_linux`
Struttura dati per il passaggio di contesto per l'esecuzione di comandi di sistema, utenti Linux e tracciamento sessione.

```cpp
struct comandi_linux {
    std::string nomeUtente = "";       // Username dell'utente attualmente connesso
    std::string passwordUtente = "";   // Credenziali/Password operativa
    std::string nomeGruppo = "";       // Target gruppo Linux
    std::string targetFile = "";       // Percorso file/directory per chmod
    std::string comandoSistema = "";   // Stringa di comando formattata per esecuzione shell
};
```

### `Firewall`
Struttura dati per i parametri di configurazione di UFW.

```cpp
struct Firewall {
    int PORT = 0;                      // Numero di porta (es. 80, 443, 22)
    std::string PROTOCOLLO = "";       // Protocollo di rete (TCP / UDP)
};
```

---

## 5. Moduli e Librerie del Sistema

### `Database.hpp`
Wrapper orientato agli oggetti per l'interazione con SQLite3.
* Metodo `execute()`: Esegue query di scrittura (`INSERT`, `UPDATE`, `DELETE`) trasmettendo parametri tipizzati.
* Metodo `query()`: Restituisce i record come vettori di mappe `std::vector<std::map<std::string, std::string>>`.

### `librerie/menu_principale.h` & `librerie/menu_principale_root.h`
Forniscono la definizione e il rendering grafico delle opzioni di navigazione in base al ruolo dell'utente:
* **Menu Standard**:
  1. `Tool utenti`
  2. `Impostazioni Firewall`
  3. `Gestione Pacchetti`
  4. `Gestione Dischi`
  5. `Stato Rete`
  6. `Genera Password`
  7. `Esci`
* **Menu Root (Amministratore)**:
  Contiene le stesse opzioni del menu standard più l'opzione riservata al caso 6:
  * `Elimina Utente (Root)`: Permette la selezione interattiva e la rimozione di un utente dal database SQLite.

### `librerie/menu_utenti.h` (`gestisciMenuUtenti`)
Gestisce le operazioni a livello di sistema operativo Linux per gli utenti:
* Creazione utenti (`sudo adduser`)
* Modifica password (`sudo passwd`)
* Assegnazione gruppi (`sudo usermod -aG`)
* Modifica permessi file/directory (`chmod`)
* Elenco utenti di sistema (`/etc/passwd`)
* Eliminazione utente Linux e della sua directory home (`sudo userdel -r`)

### `librerie/menu_firewall.h` (`gestisciMenuFirewall`)
Gestore per **UFW** (Uncomplicated Firewall):
* Abilitazione regole per specifiche porte e protocolli (`sudo ufw allow <port>/<proto>`)
* Ispezione stato e regole attive (`sudo ufw status`)

### `librerie/gestore_pacchetti.h` (`GestorePacchetti`)
Rileva dinamicamente il gestore pacchetti presente nel sistema operativo in uso (`apt`, `dnf`, `pacman`, `zypper`) ed esegue in trasparenza:
* Installazione, disinstallazione e reinstallazione pacchetti.
* Aggiornamento completo dei repository e del sistema.

### `librerie/gestore_dischi.h` (`GestoreDischi`)
Modulo di gestione storage:
* Elenco partizioni e blocchi fisici (`lsblk`)
* Smontaggio automatizzato e formattazione filesystem (`ext4`, `ntfs`, `vfat`, `exfat`).

### `librerie/stato_rete.h` (`GestisciMenuStatoRete`)
Modulo di diagnostica di rete:
* Visualizzazione interfacce e indirizzi IP (`ip addr show` / `ifconfig`).

### `librerie/generatore_password.h` (`GeneratorePassword`)
Modulo per la generazione di password sicure ad alta entropia (12 caratteri) basato sugli header `<random>` (`std::mt19937` e `std::random_device`).

---

## 6. Compilazione e Distribuzione

### Requisiti di Sistema
* Compilatore C++ abilitato allo standard C++20 (`g++` o `clang++`).
* Libreria di sviluppo SQLite3 (`libsqlite3-dev` su distribuzioni Debian/Ubuntu).

### Comando di Compilazione
```bash
g++ main.cpp -o apptools -lsqlite3
```

### Esecuzione
```bash
./apptools
```