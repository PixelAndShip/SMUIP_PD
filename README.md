# Studiju priekšmeta "Sistēmu modelēšanas un imitācijas pamati" patstāvīgais darbs variants 4-61 (U_4-61)

## **Programmas funkcionalitātes apraksts**

### Programmas uzdevums
1.Jāmodelē sistēmas darbs līdz momentam, kad beigsies ceturtā pieprasījuma apkalpošana
kanālā K2.

2.Jāaprēķina šādi izejas raksturojumi:
• vidējais rindas R1 garums
• vidējais gaidīšanas laiks rindā R1
• kanāla K1 noslodzes koeficients
• kanāla K2 noslodzes koeficients

3.Dot reālas sistēmas, kuras darbība līdzīga jūsu modeļa darbībai, piemēru un grafisko attēlu.

### Programmas funkcionalitāte

Programmas funkcijas iedalās procesos:  


### Izmantotās bibliotēkas

## **Programmas izmantošanas ceļvedis**
 
## Programmas struktūras un koda apraksts
`main.cpp`:
<details>
<summary></summary>
<ul>
<li>
</ul>
</details>



## *Iespējamās programmas kļūmes*
* Output.h faila metode printOutputSimStates() izvada nokopētus R1 statusus, kas var novest pie nepatiesi parādītiem datiem, piemēram ja n-tajā SimState stringR1 bija 1 0, tad arī iespējams n+1-tajā SimState stringR1 būs 1 0, lai gan ir jābūt 1.
## Potenciālie programmas uzlabojumi
