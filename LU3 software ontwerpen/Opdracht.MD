# De opdracht
Via deze aanvullende opdracht kun je je software ontwerp vaardigheden nog eens oefenen en
demonstreren door een klein apparaatje te ontwerpen. Je kunt in deze excel sheet er eentje
kiezen door als eerste je naam er achter te zetten: apparaatjes.
Lever je ontwerp in als link en commit-link naar een ontwikkeldocument in markdown format.
Het ontwikkeldocument bevat een kleine subset van de hoofdstukken van het
ontwikkeldocument-template dat je eerder met het team hebt gebruikt. De hoofdstukken
voldoen aan dezelfde eisen, voor zover onderstaand niet anders is aangegeven.

- Use case beschrijvingen
    - Twee stuks
Schrijf ze vanuit het oogpunt van het apparaatje. ("wacht op knop" ipv "gebruiker drukt
op knop" etc)
- Object model
- Klasse diagram
    - Listener pattern toegepast op sensors.
    - Handler toegepast wanneer meerdere sensors van hetzelfde type zijn.
- State transition diagram
    - Voor de taak van het control-object van elk van beide use case beschrijvingen het bijbehorende std.
- Code
Bij elk van beide STD's de code die daaruit voortvloeit:
Declaraties van de gebruikte variabelen en objecten.
De code van de interface functies.
De code van de main functie.
Verder belangrijk: voeg begeleidende tekst buiten de diagrammen toe, zodat het een logisch
geheel vormt.

# Slimme Veestal
UC1: Als een koe door het ingangspoortje loopt, wordt de koe geidentificeerd, gemolken en
wordt de melkproductie van die koe gemeten en naar een server gestuurd.

UC2: Tijdens het melken wordt de Koe geentertained met een spelletje: Het begint na een
knik van zijn kop: Er klinken 3 piepjes. Binnen 1 seconde na het derde piepje moet de koe
een van zijn beide voorpoten (opnieuw) neerzetten. Als het de linkerpoot is, wordt er een
portie droogvoer in een bak voor hem gedeponeerd. Als het de rechterpoot is, wordt een
waterbak wat bijgevuld.