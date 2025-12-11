# Studiju priekšmeta "Sistēmu modelēšanas un imitācijas pamati" patstāvīgais darbs variants 4-61 (U_4-61)


## Programmas uzdevums

1.Jāmodelē sistēmas darbs līdz momentam, kad beigsies ceturtā pieprasījuma apkalpošana
kanālā K2.

2.Jāaprēķina šādi izejas raksturojumi:
• vidējais rindas R1 garums
• vidējais gaidīšanas laiks rindā R1
• kanāla K1 noslodzes koeficients
• kanāla K2 noslodzes koeficients

3.Simulācijas iterācijas momenti jāvizualizē un jāsaglabā.
 
### Izmantotās c++ bibliotēkas
* string
* vector
* iostream
* chrono

## **Programmas izmantošanas ceļvedis**
1. Lai palaistu programmu, jāpalaiž fails SMUIP_PD.exe, kurš palaidīs pamatsistēmas termināli.
2. Lai beigtu programmas izpildi, terminālī jāievada no klavietūras CTRL+C.
3. Programmas izsauktajā terminālī būs instrukcija ievadīt maksimālo procesējamo pieprasījumu skaitu simulācijai, to jāievada kā veselu skaitli, bez papildus zīmēm un simboliem.
4. Ievadot skaitli un nospiežot klavietūras taustiņu "Enter", simulācija tiks palaista, un tiks izvadīti dotā uzdevuma dati, kā arī faila nosaukumi, kur atrodamas iterāciju parametru vizualizācijas.
5. Dotie faili ar iterāciju vizualizācijām atrodami tajā pašā direktorijā kur atrodas SMUIP_PD.exe fails.
6. Programma ir beigusi izpildi kad terminālī tiek izvadīts teksts "Simulation finished, you can now exit".

## Programmas struktūras un galvenās funkcionalitātes apraksts
1.Programma tiek palaista caur `main.cpp` faila `main()` funkciju, kura pamatsaskarnē terminālī iegūst maksimālo procesējamo pieprasījumu skaitu no lietotāja. </br>

2.1.Simulācija tiek uzsākta izveidojot pirmo un otro iterāciju klases `ManageSimStates` objekta konstruktorā, un `main.cpp` faila funkcijā `main()` izsauktā metodē `Simulate_U_4_61()`.</br>

2.2.Metodē `Simulate_U_4_61()` tiek izsaukta jaunas iterācijas ģenerēšana `generateIteration()` kamēr nav procesēts sasniedzamais pieprasījumu skaits.</br>

2.3.`generateIteration()` izveido jaunu iterāciju balsoties uz iepriekšējās datiem, tiek noteikts tuvākā procesa moments un izsaukta metode `manageNextIteration()`.</br>

2.4.`manageNextIteration()` modificē nākamo iterāciju atbilstoši iterācijas notikumu momentam un notikumu segmentu prioritāžu secībai.</br>

3.Kad tiek sasniegts maksimālais procesējamo pieprasījumu skaits, iegūtās iterācijas tiek izvadītas .csv failā klases `Output` objekta metodē printToExcelCSV(), tiek izrēķinātas uzdevumā dotās vērtības metodē `printOutputSimStates()`, kā arī izvadītas .txt failā notikumu momentu un starp-momentu iterācijas parametri.

Failu apraksti:

<details>
<summary>main.cpp</summary>

<ul>
main()
<ul>
Izsauc simulācijas uzsākšanas funkciju Simulate_U_4_61(), kur ievada termināli, no lietotāja ievades, iegūto maksimālo procesējamo pieprasījumu skaitu.
</ul>
</details>

<details>
<summary>A1.h</summary>
class A1 objetki
<ul>
Saglabā simulācijas pieprasījuma avota A1 statusu katrā iterācijā klases SimState objektā.
</ul>
</details>

<details>
<summary>K1.h</summary>
class K1 objekti
<ul>
Saglabā simulācijas pieprasījuma procesēšanas kanāla K1 statusu katrā iterācijā klases SimState objektā.
</ul>
</details>

<details>
<summary>R1.h</summary>
class R1 objekti
<ul>
Saglabā simulācijas pieprasījuma rindas R1 statusu katrā iterācijā klases SimState objektā.
</ul>
</details>

<details>
<summary>K2.h</summary>
class K2 objekti
<ul>
Saglabā simulācijas pieprasījuma procesēšanas kanāla K2 statusu katrā iterācijā klases SimState objektā.
</ul>
</details>

<details>
<summary>ManageSimStates.h</summary>
<ul>
class ManageSimStates objekti
<ul>
Veic simulācijas iterāciju ģenerēšanu, procesēšanu līdz pēdējā iterācija ir sasniegusi maksimālo procesējamo pieprasījumu skaitu un iegūto iterācijas datu izvadi ar klases Output objekta metodēm.
</ul>
</ul>
</details>

<details>
<summary>SimStates.h</summary>
class SimStates objekti
<ul>
Saglabā visas simulācijas iterācijas un aprēķināmo parametru statusus.
</ul>
</details>

<details>
<summary>SimState.h</summary>
class SimState objekti
<ul>
Saglabā iterācijas parametrus.
</ul>
</details>

<details>
<summary>R1QueueState.h</summary>
class R1QueueState objekti
<ul>
Saglabā katra pieprasījuma gaidīšanas laiku rindā R1 un sasaisti ar citiem pieprasījumiem atbilstoši FIFO principam.
</ul>
</details>

<details>
<summary>Output.h</summary>
class Output objekti
<ul>
Izvada visu iterāciju parametru statusus .txt failā, simulācijas procesu momentus apkopo .csv failā un aprēķina uzdevumā prasītās vērtības.
</ul>
</details>

<details>
<summary>GST.h</summary>
<ul>
Glabā simulācijas gadījuma skaitļus, izmantotos gadījuma skaitļus un ģenerējamo laiku varbūtības sadalījumus.
</ul>
</details>

## *Iespējamās programmas kļūmes*
* Lietotāju ievades datu tipi netiek pārbaudīti
* .txt faila izvadītās notikumu starp-momentu iterācijas iespējami rāda dublētus datus.
## Potenciālie programmas uzlabojumi
* Sadalīt faila ManageSimStates klases ManageSimStates metodes manageNextIteration() prioritātes segmentu procesēšanu atsevišķās metodēs.
* Pārveidot iterācijas procesēšanas procesu sistēmu no atsevišķiem statusa parametriem uz vienu string parametru, kas jau tiek izmantots datu izvadei. Lai to paveiktu nepieciešams izveidot papildus metodes katrai parametra klasei. Tas var samazināt izmantoto datu lielumu, bet potenciāli palielināt programmas izpildes laiku.
