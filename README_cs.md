<div align="center">

```text
 _____   _____ _____  _    _ 
|  __ \ / ____|  __ \| |  | |
| |  | | (___ | |__) | |  | |
| |  | |\___ \|  _  /| |  | |
| |__| |____) | | \ \| |__| |
|_____/\_____/|_|  \_\\____/ 
                             
  Deep Space Repair Unit
```

</div>
Tento projekt vznikl v rámci předmětu ZOO (Základy Objektového Návrhu) a jeho hlavním cílem bylo vytvořit propracovanou hru s důrazem na čistý kód, objektově orientovaný návrh a využití návrhových vzorů.

## 👥 Autoři
[@radek-spilka](https://github.com/radek-spilka) <br>
[@martin-gabriel](https://github.com/IamNitramis)

## 🎮 O hře
Ve hře se ujímáte ovládání opravářského drona na palubě obří a postupně se rozpadající vesmírné stanice. Vnitřní schéma této modulární stanice bylo ztraceno, takže vás čeká pečlivý průzkum neznámého prostředí. 

Váš ultimátní cíl? Dostat se do zablokované části lodi, kde se nachází hlavní řídící centrum. Zde musíte na hlavním počítači spustit návratový program, který celou loď odnaviguje bezpečně domů. Cestou však budete muset opravovat kritické systémy (označené **!**) a vyhýbat se nebezpečím.

## ⚙️ Herní mechaniky
*   **Procedurální generování modulů:** Hra začíná v počáteční lokaci „Airlock“. Jakmile se vydáte do neprozkoumaného směru, náhodně se vygeneruje nový modul (celá hra je v gridu 50x50, každý modul je vždy 7x7 znaků).
*   **Logická návaznost:** Nové moduly jsou generovány tak, aby jejich přechodové komory (dveře == hatche) správně navazovaly na stávající chodby. Někdy narazíte na zamčené dveře, které je ale možné časem odemknout.
*   **Vylepšování a inventář:** Během průzkumu sbíráte součástky, baterie a dekódovací čipy. Tyto předměty lze následně využít :).
*   **Hrozby a souboje:** Moduly mohou skrývat úniky radiace, které postupně poškozují integritu drona (HP). Další překážkou jsou rogue-bezpečnostní boti, střety s nimiž lze řešit spotřebou energie nebo pomocí speciální hacking mini-hry.

## 🖥️ ASCII Vizualizace
Hra využívá přehlednou ASCII grafiku, která zobrazuje detail aktuálního modulu a propojení s objevenými sousedními moduly. 

Příklad vygenerovaného modulu (Laboratoř, kde `!` značí poruchu a `D` pozici drona):
```text
+-----+-----+--H--+
|     |     |     |
|        D     !  |
|     |     |     |
+--H--+-----+-----+
