# LEGYEN ÖN IS MILLIOMOS
## specifikáció
### Bánszky Koppány

## Alap működés

A játék egy terminálban futó, menüvezérelt program. A vezérlés a megfelelő billentyűk lenyomásával működik, vagyis ha a játékos lenyom egy kért billentyűt, az rögtön,
az `ENTER` billentyű lenyomása nélkül fejtsen ki hatást. Ha a felhasználó rossz billentyűt nyom le, vagyis olyat, ami a menü vezérléskor nem opció, ne történjen semmi.

A program indításkor a kérdéseket egy-egy fileból olvassa be.
```
source/loim.csv
source/sorok.csv
```
Előbbi feleletválasztós kérdéseket tartalmaz. Ennek struktúrája:
| Oszlop / Sor | A | B | C | D | E | F | G | H |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 1. | Nehézség | Kérdés | A | B | C | D | Válasz | Kategória |
| 2. | int | string | char | char | char | char |char | string |

A sorok a **`\n`** karakterrel, a sorokban az oszlopok, adatok a **`;`** karakterrel vannak elválasztva.


Utóbbi file (`sorok.csv`), sorkérdéseket tartalmaz. Ennek struktúrája:
| Oszlop / Sor | A | B | C | D | E | F | G |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 1. | Kérdés | A | B | C | D | Válasz | Kategória |
| 2.  | string | char | char | char | char | string | string |

A sorok a **`\n`** karakterrel, a sorokban az oszlopok, adatok a **`;`** karakterrel vannak elválasztva.

*Ha nem sikerül megnyitni az adattárolókat, a felhasználótól legyen bekérve az abszolút elérési útja a fileoknak és az alapján működjön.*

## Főmenü

Legyen látható a játék címe nagyban. **Ez a továbbiakban, minden menüre érvényes**
A menü az alábbi opciókat tartalmazza, az alábbi vezérlési billentyűkkel!

| Menüpont | Beállítások | Dicsőséglista | Indítás | Kilépés |
| --- | --- | --- | --- | --- |
| Billentyű | s | d | Enter | Esc |

## Beállítások

A beállítások menüpontban az alábbi funkciók lehessenek állíthatóak, a megfelelő billentyű lenyomásával.
Billentyű lenyomásakor, ha két opciós a beállítás, változtassa az ellenkezőre a beállítást, ha több lehetőség közül lehet választani, minden egyes lenyomáskor a következőre ugorjon, majd a végét elérve kezdje előröl.
Minden opció legyen kiírva, mikor a felhasználó fókuszál az adott menüpontra és az épp kiválasztott legyen kiemelve.
Fókuszálás: az adott menüponthoz tartozó billentyű lenyomása. Ebből kilépni vagy egy másik menüpont fókuszba helyezésével vagy a mentés/mégse opcióval lehet.

| Menüpont | Nehézség | Szavazás segítség esélye | Mentés | Mégse |
| --- | --- | --- | --- | --- |
| Billentyű | d | w | Enter | Esc |
| Típus/Válaszlehetőségek | 1-10 számok | 5-100%-ig, 5%al növelve | --- | --- |

A beállítások az adott sessionre érvényesek, vagyis ha a felhasználó kilép a játékból elveszhetnek a beállítasok.
Alap beállítások:
| Menüpont | Nehézség | Szavazás segítség esélye |
| --- | --- | --- | --- | --- |
| Beállítás | 5 | 75% |

A beállítások a dicsőség listán legyenek figyelembe véve!

## Dicsőség lista

Dicsőség lista lekérhető legyen a beállítások megadása szerint.
Úgy működjön ezek módosítása, ahogy a beállításokban. Menüpontok a következőek legyenek: 
| Menüpont | Nehézség | Szavazás segítség esélye | Összes | Lekérés | Vissza |
| --- | --- | --- | --- | --- | --- |
| Billentyű | d |  w | a | Enter | Esc |
| Típus/Válaszlehetőségek | 1-10 számok | 5-100%-ig, 5%al növelve | button | --- | --- |

Alapból a **Beállítások** menüpontban megadott beállítások szerint kérje le a dicsőség listát.
Ha üres az adott lista, jelezze a játékosnak.
Ha a játékos kiválasztja az *összes* menüpontot, rögtön kérje le az összes adatot, szűrés nélkül.

A lista így nézzen ki:
```
| Helyezés | Név | Pénz nyeremény | Játék idő |
```

Miután a játékos lekért egy listát, újra tudja állítani a szűrőket és kérhessen le újból.

A dicsőség lista file így nézzen ki:
```
source/rangsor.csv

| Név | Nyeremény | Játék idő | Nehézség | Szavazás segítség esélye |
```


## Játék menüje

A játéknév alatt jelenjen meg a kérdés, kötőjellel elválasztva utána a kategória.
Alatta pedig a 4 válasz lehetőség ebben a formában:
```
[] - válasz
```
A 4 válasz előtt, a `[]` karakterek helyett, `A`, `B`, `C` vagy `D` karakterek jelenjenek meg sorban, a beolvasás szerint.
### Sorkérdések esetén
A felhasználótól **4** egymás után lenyomott bilentyűt várunk. A sorrenden nem lehet módosítani, így továbbra sem szükséges az Enter lenyomása a végén.
A választ, az `a`, `b`, `c`, `d` billentyűk kombinációjával kell megadni.

## Feleletválasztós kérdés esetén
A felhasználótól egy billentyű lenyomást várunk. Ezek a következőek:

| Menüpont | A válasz | B válasz | C válasz | D válasz | Felezés | Szavazás |
| --- | --- | --- | --- | --- | --- | --- | --- |
| Billentyű | a | b | c | d | h | v |

Ha egy segítség már volt használva, ne jelenjen meg.

A válaszok alatt bal szélen legyen egymás alatt a nehézségi szint és az eddig gyűjtött nyeremény.
Ezekkel egy sorban jobb oldalt pedig egymás alatt legyen a két segítség közül az/azok ami/amik még nem volt/ak használva.

## Játékmenet

Indításkor kérje el a játékos nevét. Ez alapján legyen a dicsőség lista mentve.
Enter lenyomása után induljon a játék, ezzel együtt egy időmérés is.

Az első kérdés minden esetben egy random kiválasztott sorkérdés legyen. (`source/sorok.csv`)
Ha ezt sikertelen kérdés követi tegyen fel egy új, ilyen típusu kérdést.
Ezt addig ismételje, míg nem kap helyes választ.

Ha sikeres a válasz, innentől a kérdések feleletválasztósak legyenek. (`source/loim.csv`)
A beállított nehézség alapján válassza random a kérdéseket.
Minden sikeres válasz után adjon a nyereményhez 10.000Ft-ot (Ez legyen is megjelenítve)

Ha hibás a válasz, a játékos kiesett.
| Megválaszolt kérdések száma | Nyeremény |
| --- | --- |
| n < 5 | 0Ft |
| n < 10 | 50.000Ft |
| n < 15 | 100.000Ft |
| n = 15 | 150.000Ft |

Maximálisan megválaszolható kérdések száma: 15;
Minden kérdés után legyen egy választási lehetőség, melyben a játékos kiválaszthatja, hogy folytatja, vagy megáll a játékban.
Ha folytatja jöhet a következő kérdés, ha nem, az adott nyereményét kapja meg, ahol épp tartott.

Amikor vége a játéknak, a rendszer mentse el a megfelelő módon a dicsőség listába a statisztikát. Ha létezik már az adott név az adatbázisban, a jobbikat mentse el.
File felépítése a következő: 
```
source/rangsor.csv

| Név | Nyeremény | Játék idő | Nehézség | Szavazás segítség esélye |
```

Mutassa meg egy új menüpontban a satisztikát:
```
| Nyeremény | Játék idő |
```
A főmenübe ekkor az `Esc` billentyű lenyomásával lehessen.



### Bánszky Koppány


