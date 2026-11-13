# Mars Kolonisi Yaşam Destek Simülatörü (C)

C programlama dilinin temel yapıları (koşullu ifadeler, döngüler, aritmetik/mantıksal operatörler ve sözde rastgele sayı üretimi) kullanılarak geliştirilmiş, metin tabanlı ve tek karakterli komutlarla yönetilen hayatta kalma simülasyonudur.

## Senaryo ve Amaç
Oyuncu, Mars'taki küçük bir araştırma istasyonunda tek başına kalan bir mühendisi yönetir. Amaç; sağlık, enerji, oksijen, su, yedek parça ve modül hasarı değişkenlerini dengede tutarak kurtarma ekibi gelene kadar **15 gün** hayatta kalmaktır.

## Zorluk Seviyeleri
Program başlangıcında `do-while` ve `switch-case` yapılarıyla zorluk seviyesi seçilir:
* **K (Kolay):** Yüksek başlangıç kaynakları, düşük modül hasarı ve 3 turluk kum fırtınaları.
* **N (Normal):** Dengeli başlangıç kaynakları ve 5 turluk kum fırtınaları.
* **Z (Zor):** Kısıtlı kaynaklar, yüksek başlangıç hasarı ve 7 turluk şiddetli kum fırtınaları.

## Komut Listesi
Komutlar büyük/küçük harf duyarsızdır (`fall-through` `switch-case`). Tanımsız komutlar tur harcamaz.

| Komut | İşlev | Temel Mekanik |
| :---: | :--- | :--- |
| **G** | Keşif Görevi | Enerji (-15) ve oksijen (-10) harcar; su bulma, yedek parça bulma veya eli boş dönme sonuçları üretir. |
| **O** | Oksijen Üret | Her 2 birim suyu 3 birim oksijene dönüştürür (`%` mod operatörü ile tek/çift su kontrolü yapar). |
| **T** | Tamir | Hasar seviyesini 3 kademede (`<=30`, `<=70`, `>70`) değerlendirip yedek parça ile onarım yapar. |
| **D** | Durum Raporu | Kritik uyarıları listeler; tüm değerler güvenliyse `TUM SISTEMLER NORMAL` çıktısı verir (tur harcamaz). |
| **U** | Uyu / Dinlen | Enerji yeniler; oksijen 20'nin altındaysa sağlık artışı yerine sağlık kaybı yaşanır. |
| **K** | Kum Fırtınası | `for` döngüsüyle fırtına simüle eder; çift turlarda 2x hasar uygular, kilit mühürlüyse sızıntıyı `continue` ile atlar. |
| **H** | Hava Kilidi | `do-while` döngüsü ve en fazla 3 denemeyle o güne ait dinamik harf şifresini (`'A' + (gun % 26)`) çözer. |
| **Q** | Çıkış | Simülasyonu sonlandırır ve sonuç puan raporunu gösterir. |

## Kurulum ve Çalıştırma
Derlemek ve çalıştırmak için:

    gcc mars_kolonisi.c -o mars_kolonisi
    ./mars_kolonisi

Windows Dev-C++ üzerinde `mars_kolonisi.c` dosyasını açıp **F11** tuşu ile doğrudan derleyip çalıştırabilirsiniz.

## Puanlama Formülü
Oyun sonunda (kazanma, kaybetme veya çıkış) ekrana aşağıdaki formülle hesaplanan toplam puan yazdırılır:

    Puan = (gun * 100) + saglik + oksijen - modulHasari
