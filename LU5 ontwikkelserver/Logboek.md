# Logboek gomoku opdracht
## Ontwikkelserver opzetten
Het aanmaken van de ontwikkelserver
1. Open windows Dev Home
2. Ga naar environment
3. Klik op environment toevoegen
4. Selecteer windows WSL
5. Selecteer Ubuntu 22.04 LTS
6. Klik op Create environment.
Het openen van de ontwikkelserver
1. Open windows Dev Home
2. Ga naar environment
3. Klik op Launch
4. voer het command `cd ..` en `cd home` uit om in de home folder te komen
5. Ga nu naar de user folder, in mijn geval is dat `cd fmeer`
Server instellen
1. `mkdir docker` docker folder maken.
2. Volg de uitleg op deze pagina: https://docs.docker.com/engine/install/ubuntu/#install-using-the-repository
3. `apt install docker-compose` om docker compose int te stellen.
4. `sudo apt upgrade` en `sudo apt update`
5. `sudo apt install python3 python3-pip` om python te installeren
Voorbeeld project opzetten
1. `git clone https://github.com/HU-TI-DEV/VoorbeeldWebApp_Gomoku`
2. `cd VoorbeeldWebApp_Gomoku`
3. `docker-compose up --build` om de app te starten
4. Nu kan je bij de app door naar localhost:5001/gomoku/ te gaan.