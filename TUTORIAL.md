# LEGYEN ÖN IS MILLIOMOS
## Felhasználó útmutató
### Bánszky Koppány

Belépéskor, amennyiben a program nem ismeri fel, meg kell adni a csatolt loim.csv fájl útvonalát, illetve a sorok.csv fájl útvonalát.

## Főmenü
A főmenüben 4 interakciós lehetőség van

| Billentyű | Funkció |
| --- | --- |
| `s` | Beállítások |
| `d` | Dicsőséglista |
| `Enter` | Indítás (Játék indítása) |
| `Esc` | Kilépés (a programból) |

A megfelelő gomb egyszeri lenyomásával az adott menüponthoz fogja dobni a felhasználót

## Beállítások
A beállításokon belül 4 interakciós lehetőség van

| Billentyű | Funkció |
| --- | --- |
| `d` | Nehézség |
| `w` | Szavazás segítség esélye |
| `Enter` | Mentés (és visszalépés) |
| `Esc` | Mégse (és vissza) |

A `d` billentyű lenyomásával a kérdések nehézségének fokát lehet módosítani. Minden gombnyomásnál 1-el növekszik a nehézség. 10 után visszatér 1-hez

A `w` billentyű lenyomásával a -közönség szavazata- segítség pontosságát lehet beállítani. Minél nagyobbra van állítva, annál nagyobb az esélye, hogy a közönség helyesen szavaz és jó választ ad. Minden gombnyomásra 5%-al növekszik az esély. 100% után visszaugrik 10%-ra

Az `Enter` lenyomásával elmenti a beállításokat és visszatér a **Főmenübe**

Az `Esc` lenyomásakor nem menti a beállításokat és visszatér a **Főmenübe**

## Dicsőséglista
A dicsőséglistán belül 5 interakciós lehetőség van

| Billentyű | Funkció |
| --- | --- |
| `d` | Nehézség |
| `w` | Szavazás segítség esélye |
| `a` | Összes |
| `Enter` | Ok (Listázás) |
| `Esc` | Vissza |

A `d` és `w` billentyűk hasonlóan működnek a **Beállítások**ban leírtakhoz, csak itt a szűrőt adják meg.

Ezeket kiválasztva és az `Enter`-t lenyomva a szűrők alapján lehet listázni az adatokat.

Az `a` billentyűt lenyomva az összes adatot kiírja.

Az `Esc` lenyomásakor visszatér a **Főmenübe**

## Kilépés
Ezt választva a program bezár

## Indítás
Kiválasztva, amennyiben még nem adott meg a felhasználó, kér egy játékos nevet. Ennek hossza maximum 50 karakter.

Név beírása után és `Enter`-t nyomva, megkérdezi a program hogy *Jöhet-e a sorkérdés?*. Ha már korábban megadott a játékos nevet, az előző rész kimarad.

Amennyiben készenáll a játékos, nyomja le az `Enter`-t.
Ezután elindul a játékidő. A kérdésre a megfelelő karakterek egymás utáni lenyomásával kell változtatni. Egy karaktert csak egyszer lehet bevinni és nem lehet változtatni a már beütött karakterek sorrendjén. 

Amennyiben a válasz rossz, azt a program tudatja a játékossal és egy `Enter` lenyomásával új sorbarendezendő kérdést kap.

Ha a válasz helyes, a program tudatja ezt a játékossal és a feleletválasztós kérdések következnek. Ha készenáll a játékos, az `Enter` lenyomásával kezdheti a játék ezen részét.

Ekkor a válaszadáshoz egyedül a megfelelő karakter billentyűjét kell lenyomni. Helyes válasz esetén a játékos dönthet, hogy tovább megy-e, vagy megáll. Ha megáll, az addig összegyűjtött összeget nyeri. Ha továbbmegy, jön a következő kérdés.

A `h` billentyűt lenyomva a válasz lehetőségek megfeleződnek.
A `v` billentyűt lenyomva a *közönség szavaz* és megjelöl sárgával egy válaszlehetőséget. Ekkor a játékos dönthet, hogy "hisz-e" a közönségnek. A szokott módon adhatja meg végleges válaszát.

Figyelem! Ezeket a segítségeket 1 meneten belül egyszer lehet felhasználni.

Hibás válasz esetén, minden összegyűjtött pénzt elveszít a játékos.

Összesen 15 kérdésre adhat választ, ha mindegyikre helyesen felel, megnyeri a főnyereményt.
