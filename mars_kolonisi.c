#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Degerleri 0-100 araliginda tutan yardimci fonksiyon */
int sinirla(int deger) {
    if (deger < 0) {
        return 0;
    }
    if (deger > 100) {
        return 100;
    }
    return deger;
}

/* Giris tamponunu temizleyen yardimci fonksiyon */
void tamponTemizle(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* Tampondaki fazla karakterleri temizle */
    }
}

int main(void) {
    int saglik = 100;
    int enerji = 100;
    int oksijen = 100;
    int su = 0;
    int yedekParca = 0;
    int modulHasari = 0;
    int kilitMuhurlu = 0;

    int gun = 1;
    int tur = 0;
    int kazandi = 0;
    int cikisIstendi = 0;

    /* Zorluk seviyesine bagli firtina parametreleri */
    int firtinaTuru = 5;
    int firtinaTemelHasar = 8;

    char zorluk;
    int zorlukSecildi = 0;

    srand((unsigned int)time(NULL));

    printf("============================================================\n");
    printf("       MARS KOLONISI YASAM DESTEK SIMULATORU (v1.0)         \n");
    printf("============================================================\n");
    printf("Gorev: Kurtarma ekibi gelene kadar 15 gun hayatta kal.\n\n");

    /* Zorluk seviyesi secimi */
    do {
        printf("Zorluk Seviyesi Secin [K: Kolay | N: Normal | Z: Zor]: ");
        if (scanf(" %c", &zorluk) != 1) {
            tamponTemizle();
            continue;
        }
        tamponTemizle();

        switch (zorluk) {
            case 'k':
            case 'K':
                saglik = 100;
                enerji = 100;
                oksijen = 100;
                su = 24;
                yedekParca = 6;
                modulHasari = 5;
                firtinaTuru = 3;
                firtinaTemelHasar = 6;
                zorlukSecildi = 1;
                printf("\n[BILGI] KOLAY zorluk secildi. Baslangic kaynaklari yuksek.\n");
                break;

            case 'n':
            case 'N':
                saglik = 90;
                enerji = 90;
                oksijen = 90;
                su = 16;
                yedekParca = 4;
                modulHasari = 15;
                firtinaTuru = 5;
                firtinaTemelHasar = 9;
                zorlukSecildi = 1;
                printf("\n[BILGI] NORMAL zorluk secildi. Standart koloni kosullari aktif.\n");
                break;

            case 'z':
            case 'Z':
                saglik = 80;
                enerji = 80;
                oksijen = 80;
                su = 10;
                yedekParca = 2;
                modulHasari = 25;
                firtinaTuru = 7;
                firtinaTemelHasar = 12;
                zorlukSecildi = 1;
                printf("\n[BILGI] ZOR zorluk secildi. Kaynaklar kisitli, firtinalar siddetli!\n");
                break;

            default:
                printf("[UYARI] Gecersiz zorluk secimi! Lutfen K, N veya Z giriniz.\n\n");
                break;
        }
    } while (!zorlukSecildi);

    /* Ana komut dongusu */
    do {
        char komut;
        int turIlerledi = 0;

        printf("\n------------------------------------------------------------\n");
        printf("GUN: %d / 15 | TUR: %d | Kilit: %s\n",
               gun, tur, kilitMuhurlu ? "MUHURLU" : "ACIK");
        printf("Saglik: %d | Enerji: %d | Oksijen: %d | Su: %d | Parca: %d | Hasar: %d\n",
               saglik, enerji, oksijen, su, yedekParca, modulHasari);
        printf("------------------------------------------------------------\n");
        printf("Komutlar: [G] Kesif  [O] Oksijen  [T] Tamir  [D] Durum\n");
        printf("          [U] Uyu    [K] Firtina  [H] Kilit  [Q] Cikis\n");
        printf("Komutunuz: ");

        if (scanf(" %c", &komut) != 1) {
            tamponTemizle();
            continue;
        }
        tamponTemizle();

        switch (komut) {
            case 'g':
            case 'G': {
                int zar;
                int kaynakEsigi;
                int kazaZar;

                if (enerji < 15) {
                    printf("[IPTAL] Kesif icin yeterli enerji yok! (Gereken: 15, Mevcut: %d)\n", enerji);
                    break;
                }

                enerji -= 15;
                oksijen -= 10;

                zar = rand() % 100;
                kaynakEsigi = (enerji > 40 && oksijen > 30) ? 70 : 45;

                printf("[KESIF] Yuzey taramasi baslatildi...\n");
                printf("Kaynak Zari: %d / Esik: %d -> %s\n",
                       zar, kaynakEsigi, (zar < kaynakEsigi) ? "BASARILI" : "BASARISIZ");

                if (zar < kaynakEsigi / 2) {
                    int bulunanSu = 6 + (zar % 5);
                    su += bulunanSu;
                    printf("[SONUC] Buz damari bulundu! +%d birim su elde edildi.\n", bulunanSu);
                } else if (zar < kaynakEsigi) {
                    int bulunanParca = 1 + (zar % 2);
                    yedekParca += bulunanParca;
                    printf("[SONUC] Eski uydu enkazi bulundu! +%d yedek parca elde edildi.\n", bulunanParca);
                } else {
                    printf("[SONUC] Col firtinasi izleri disinda bir sey bulunamadi (Eli bos donuldu).\n");
                }

                kazaZar = rand() % 100;
                printf("Guvenlik Zari: %d / Esik: 10 -> %s\n",
                       kazaZar, (kazaZar < 10 || modulHasari > 70) ? "TEHLIKE!" : "GUVENLI");

                /* Odevde belirtilen kosul: zar < 10 veya modulHasari > 70 */
                if (kazaZar < 10 || modulHasari > 70) {
                    int hasarMiktari = 12;
                    saglik -= hasarMiktari;
                    printf("[TEHLIKE] Yuzey kazasi veya yuksek modul hasari nedeniyle -%d saglik kaybi!\n",
                           hasarMiktari);
                }

                turIlerledi = 1;
                break;
            }

            case 'o':
            case 'O': {
                int harcanacakSu = 0;
                int islenecekCiftSu;
                int uretilenOksijen;
                int maksimumCiftSu;

                if (enerji < 10) {
                    printf("[IPTAL] Oksijen elektrolizi icin yeterli enerji yok! (Gereken: 10, Mevcut: %d)\n", enerji);
                    break;
                }
                if (su < 2) {
                    printf("[IPTAL] Oksijen uretimi icin en az 2 birim su gereklidir! (Mevcut: %d)\n", su);
                    break;
                }
                if (oksijen >= 100) {
                    printf("[IPTAL] Oksijen tanklari zaten tamamen dolu (100)!\n");
                    break;
                }

                printf("Kullanilacak su miktarini girin (Mevcut: %d): ", su);
                if (scanf("%d", &harcanacakSu) != 1) {
                    tamponTemizle();
                    printf("[IPTAL] Gecersiz sayi girisi!\n");
                    break;
                }
                tamponTemizle();

                if (harcanacakSu < 2) {
                    printf("[IPTAL] En az 2 birim su kullanmalisiniz.\n");
                    break;
                }
                if (harcanacakSu > su) {
                    printf("[IPTAL] Mevcut sudan fazla miktar girilemez! (Mevcut: %d)\n", su);
                    break;
                }

                /* Her 2 su 3 oksijen uretir; oksijen 100'u asamaz.
                   Tank kapasitesi yetmezse kullanilmayan su depoda kalir. */
                maksimumCiftSu = (100 - oksijen) / 3;
                islenecekCiftSu = harcanacakSu / 2;

                if (islenecekCiftSu > maksimumCiftSu) {
                    islenecekCiftSu = maksimumCiftSu;
                }

                uretilenOksijen = islenecekCiftSu * 3;

                if (islenecekCiftSu == 0) {
                    printf("[IPTAL] Tank kapasitesi yeni oksijen uretmek icin yeterli degil.\n");
                    break;
                }

                su -= islenecekCiftSu * 2;
                enerji -= 10;
                oksijen += uretilenOksijen;

                printf("[OKSIJEN] %d birim su islendi -> +%d birim oksijen uretildi (-10 enerji).\n",
                       islenecekCiftSu * 2, uretilenOksijen);

                if (harcanacakSu % 2 == 1 && harcanacakSu == islenecekCiftSu * 2 + 1) {
                    printf("[BILGI] Girilen miktar tek sayi oldugu icin 1 birim su artik olarak depoda birakildi.\n");
                }
                if (islenecekCiftSu * 2 < harcanacakSu - (harcanacakSu % 2)) {
                    printf("[BILGI] Tank kapasitesi nedeniyle kullanilmayan su depoda birakildi.\n");
                }

                turIlerledi = 1;
                break;
            }

            case 't':
            case 'T': {
                if (enerji < 10) {
                    printf("[IPTAL] Tamir islemi icin yeterli enerji yok! (Gereken: 10, Mevcut: %d)\n", enerji);
                    break;
                }
                if (yedekParca <= 0) {
                    printf("[IPTAL] Tamir icin yedek parca bulunmuyor!\n");
                    break;
                }
                if (modulHasari == 0) {
                    printf("[IPTAL] Modulde onarilacak hasar bulunmuyor (Hasar: 0).\n");
                    break;
                }

                if (modulHasari <= 30) {
                    yedekParca -= 1;
                    enerji -= 10;
                    modulHasari -= 15;
                    printf("[TAMIR - HAFIF] 1 yedek parca kullanildi. Modul hasari 15 birim azaltildi.\n");
                } else if (modulHasari <= 70) {
                    if (yedekParca >= 2) {
                        yedekParca -= 2;
                        enerji -= 10;
                        modulHasari -= 30;
                        printf("[TAMIR - ORTA] 2 yedek parca kullanildi. Modul hasari 30 birim azaltildi.\n");
                    } else {
                        yedekParca -= 1;
                        enerji -= 10;
                        modulHasari -= 15;
                        printf("[TAMIR - ORTA/KISMI] Yalnizca 1 parca vardi. Hasar 15 birim azaltildi.\n");
                    }
                } else {
                    if (yedekParca >= 3) {
                        yedekParca -= 3;
                        enerji -= 10;
                        modulHasari -= 45;
                        printf("[TAMIR - AGIR] 3 yedek parca kullanildi. Kritik hasar 45 birim onarildi.\n");
                    } else {
                        int harcanan = yedekParca;
                        int onarim = harcanan * 15;
                        yedekParca = 0;
                        enerji -= 10;
                        modulHasari -= onarim;
                        printf("[TAMIR - AGIR/KISMI] Mevcut %d parca ile hasar %d birim azaltildi.\n",
                               harcanan, onarim);
                    }
                }

                turIlerledi = 1;
                break;
            }

            case 'd':
            case 'D': {
                printf("\n================ DETAYLI SISTEM RAPORU ================\n");
                printf("Gun            : %d / 15\n", gun);
                printf("Toplam Tur     : %d\n", tur);
                printf("Saglik         : %d / 100\n", saglik);
                printf("Enerji         : %d / 100\n", enerji);
                printf("Oksijen        : %d / 100\n", oksijen);
                printf("Su Stogu       : %d birim\n", su);
                printf("Yedek Parca    : %d adet\n", yedekParca);
                printf("Modul Hasari   : %d / 100\n", modulHasari);
                printf("Hava Kilidi    : %s\n", kilitMuhurlu ? "MUHURLU (Guvenli)" : "ACIK (Savunmasiz)");
                printf("-------------------------------------------------------\n");

                if (oksijen < 25) {
                    printf("[KRITIK UYARI] Oksijen seviyesi tehlikeli duzeyde dusuk (< 25)!\n");
                }
                if (saglik < 30) {
                    printf("[KRITIK UYARI] Personel sagligi kritik seviyede (< 30)!\n");
                }
                if (enerji < 20) {
                    printf("[KRITIK UYARI] Enerji rezervi tukenmek uzere (< 20)!\n");
                }
                if (modulHasari > 70) {
                    printf("[KRITIK UYARI] Istasyon govde hasari agir (> 70)!\n");
                }
                if (su < 4) {
                    printf("[KRITIK UYARI] Su stogu kritik seviyede (< 4)!\n");
                }

                if (oksijen >= 25 && saglik >= 30 && enerji >= 20 &&
                    modulHasari <= 70 && su >= 4) {
                    printf("TUM SISTEMLER NORMAL\n");
                }
                printf("=======================================================\n");
                break;
            }

            case 'u':
            case 'U': {
                printf("[DINLENME] Istasyon kabininde dinlenmeye cekildiniz...\n");
                enerji += 25;
                oksijen -= 10;

                if (oksijen < 20) {
                    saglik -= 10;
                    if (oksijen <= 0) {
                        saglik -= 10;
                        printf("[TEHLIKE] Oksijen tukendi! Uyku sirasinda agir hipoksi yasandi (-20 saglik).\n");
                    } else {
                        printf("[UYARI] Dusuk oksijen (< 20) nedeniyle dinlenme saglik kazandirmadi (-10 saglik).\n");
                    }
                } else {
                    saglik += 15;
                    printf("[BILGI] Enerji +25, Saglik +15 yenilendi (-10 oksijen).\n");
                }

                turIlerledi = 1;
                break;
            }

            case 'k':
            case 'K': {
                int i;
                int hasarAlinanTur = 0;
                int toplamSaglikKaybi = 0;
                int toplamOksijenKaybi = 0;
                int toplamModulHasari = 0;

                if (enerji < 5) {
                    printf("[IPTAL] Firtina kalkanlarini yonetmek icin yeterli enerji yok! (Gereken: 5, Mevcut: %d)\n", enerji);
                    break;
                }

                enerji -= 5;
                printf("\n[KUM FIRTINASI] %d turluk siddetli Mars kum firtinasi basladi!\n", firtinaTuru);

                for (i = 1; i <= firtinaTuru; i++) {
                    int zar = rand() % 100;
                    int carpan = (i % 2 == 0) ? 2 : 1;

                    printf("  Tur %d/%d %sZar: %d / Esikler: 20, 40, 60 -> ",
                           i, firtinaTuru,
                           (carpan == 2) ? "[SIDDETLI RUZGAR 2x] " : "",
                           zar);

                    if (zar < 20) {
                        printf("OKSIJEN SIZINTISI ");
                        if (kilitMuhurlu == 1) {
                            printf("-> Hava kilidi muhurlu oldugu icin atlandi (continue)!\n");
                            continue;
                        }
                        {
                            int kayip = 6 * carpan;
                            oksijen -= kayip;
                            toplamOksijenKaybi += kayip;
                            hasarAlinanTur++;
                            printf("-> -%d oksijen!\n", kayip);
                        }
                    } else if (zar < 40) {
                        int kayip = firtinaTemelHasar * carpan;
                        saglik -= kayip;
                        toplamSaglikKaybi += kayip;
                        hasarAlinanTur++;
                        printf("YARALANMA -> -%d saglik!\n", kayip);
                    } else if (zar < 60) {
                        int hasar = (firtinaTemelHasar + 2) * carpan;
                        modulHasari += hasar;
                        toplamModulHasari += hasar;
                        hasarAlinanTur++;
                        printf("MODUL HASARI -> +%d hasar!\n", hasar);
                    } else {
                        printf("BASARILI KORUNMA -> Hasar alinmadi.\n");
                    }

                    saglik = sinirla(saglik);
                    oksijen = sinirla(oksijen);
                    modulHasari = sinirla(modulHasari);

                    if (saglik == 0 || oksijen == 0) {
                        printf("  [KRITIK] Yasamsal deger sifirlandi! Firtina simulasyonu erken sonlandiriliyor.\n");
                        break;
                    }
                }

                printf("[FIRTINA OZETI] Hasar Alinan Tur: %d/%d | Saglik Kaybi: -%d | Oksijen Kaybi: -%d | Modul Hasari: +%d\n",
                       hasarAlinanTur, firtinaTuru, toplamSaglikKaybi,
                       toplamOksijenKaybi, toplamModulHasari);

                turIlerledi = 1;
                break;
            }

            case 'h':
            case 'H': {
                char dogruSifre;
                int deneme = 0;
                int sifreCozuldu = 0;
                int ucDenemeBasarisiz = 0;
                char tahmin;

                if (kilitMuhurlu == 1) {
                    printf("[BILGI] Hava kilidi zaten muhurlu durumda!\n");
                    break;
                }
                if (enerji < 5) {
                    printf("[IPTAL] Hava kilidi terminalini acmak icin yeterli enerji yok! (Gereken: 5, Mevcut: %d)\n", enerji);
                    break;
                }

                dogruSifre = (char)('A' + (gun % 26));

                printf("\n[HAVA KILIDI] Guvenlik terminali aktif. Maksimum 3 deneme hakkiniz var.\n");
                printf("IPUCU: Sifre, Ingiliz alfabesinde 'A' harfinden bugunun gun sayisi (%d) kadar ilerideki harftir.\n",
                       gun);

                do {
                    deneme++;
                    printf("Deneme %d/3 - Tek karakterlik sifreyi girin (A-Z): ", deneme);
                    if (scanf(" %c", &tahmin) != 1) {
                        tamponTemizle();
                        continue;
                    }
                    tamponTemizle();

                    if (tahmin >= 'a' && tahmin <= 'z') {
                        tahmin = (char)(tahmin - ('a' - 'A'));
                    }

                    if (tahmin == dogruSifre) {
                        sifreCozuldu = 1;
                        kilitMuhurlu = 1;
                        printf("[BASARILI] Sifre dogrulandi (%c)! Hava kilidi muhurlendi.\n",
                               dogruSifre);
                    } else {
                        enerji -= 5;
                        if (tahmin < dogruSifre) {
                            printf("[HATALI] Yanlis sifre! (-5 enerji) -> Ipucu: Alfabede ILERI git.\n");
                        } else {
                            printf("[HATALI] Yanlis sifre! (-5 enerji) -> Ipucu: Alfabede GERI git.\n");
                        }

                        if (deneme < 3 && enerji < 5) {
                            printf("[IPTAL] Yeni deneme icin yeterli enerji kalmadi.\n");
                            break;
                        }
                    }
                } while (!sifreCozuldu && deneme < 3);

                if (!sifreCozuldu && deneme == 3) {
                    ucDenemeBasarisiz = 1;
                }

                if (ucDenemeBasarisiz) {
                    modulHasari += 20;
                    printf("[ALARM] 3 deneme basarisiz! Kilit mekanizmasi zorlandi (+20 modul hasari).\n");
                }

                turIlerledi = 1;
                break;
            }

            case 'q':
            case 'Q':
                cikisIstendi = 1;
                printf("\n[CIKIS] Komutan oturumu sonlandirdi. Tahliye beklenmeden simulasyon kapatiliyor...\n");
                break;

            default:
                printf("[UYARI] Tanimsiz komut ('%c')! Gecerli komutlar: G, O, T, D, U, K, H, Q (Tur harcanmadi).\n",
                       komut);
                break;
        }

        /* Her komuttan sonra 0-100 sinirlandirma */
        saglik = sinirla(saglik);
        enerji = sinirla(enerji);
        oksijen = sinirla(oksijen);
        modulHasari = sinirla(modulHasari);

        /* Gecerli her komut tur sayacini artirir; her 3 turda yeni gun baslar */
        if (turIlerledi && !cikisIstendi) {
            tur++;
            if (tur % 3 == 0) {
                gun++;
                if (gun <= 15) {
                    oksijen -= 8;
                    printf("\n[YENI GUN - GUN %d] Gece dongusu tamamlandi: -8 oksijen tuketildi.\n",
                           gun);
                    if (modulHasari > 70) {
                        saglik -= 5;
                        printf("[KRITIK] Yuksek modul hasari (> 70) nedeniyle gece boyunca -5 saglik kaybi!\n");
                    }
                    saglik = sinirla(saglik);
                    oksijen = sinirla(oksijen);
                }
            }
        }

        /* Oyun sonu kosullarini kontrol et */
        if (saglik == 0 || oksijen == 0) {
            printf("\n[OLUM] Yasamsal degerler sifira dustu! Koloni gorevi basarisiz oldu.\n");
            break;
        }

        if (gun > 15) {
            gun = 15;
            kazandi = 1;
            printf("\n[ZAFER] 15. gun tamamlandi! Kurtarma ekibi Mars yorungesinden inis yapti!\n");
            break;
        }

    } while (!cikisIstendi);

    /* Oyun sonu raporu ve puan hesabi */
    {
        int puan = (gun * 100) + saglik + oksijen - modulHasari;
        if (puan < 0) {
            puan = 0;
        }

        printf("\n============================================================\n");
        printf("                  SIMULASYON SONUC RAPORU                   \n");
        printf("============================================================\n");
        printf("Sonuc Durumu     : %s\n",
               kazandi ? "KAZANILDI (Kurtarma Basarili)" :
               (cikisIstendi ? "SONLANDIRILDI (Kullanici Cikisi)" :
                "KAYBEDILDI (Hayatta Kalinamadi)"));
        printf("Hayatta Kalinan  : %d Gun\n", gun);
        printf("Toplam Tur       : %d Tur\n", tur);
        printf("Son Saglik       : %d / 100\n", saglik);
        printf("Son Enerji       : %d / 100\n", enerji);
        printf("Son Oksijen      : %d / 100\n", oksijen);
        printf("Kalan Su / Parca : %d birim su | %d yedek parca\n", su, yedekParca);
        printf("Son Modul Hasari : %d / 100\n", modulHasari);
        printf("------------------------------------------------------------\n");
        printf("TOPLAM PUAN      : %d\n", puan);
        printf("============================================================\n");
    }

    return 0;
}
