#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "include/mysql.h"

MYSQL *mysql;
MYSQL *baglan;
int sorgu;

int main()
{
    mysql=mysql_init(NULL);
    baglan=mysql_real_connect(mysql, "localhost", "root", "root", NULL, 0, NULL, 0);
    mysql_query(baglan,("use airport"));

    mysql_query(baglan,("CREATE TABLE IF NOT EXISTS `airport`.`musteri` ( `tc` VARCHAR(11) NOT NULL , `isim` VARCHAR(30) NOT NULL , `adres` VARCHAR(45) NOT NULL , `eposta` VARCHAR(30) NOT NULL ,`sehir` VARCHAR(30) NOT NULL, PRIMARY KEY (`tc`)) ENGINE = InnoDB;"));
    mysql_query(baglan,("CREATE TABLE IF NOT EXISTS `airport`.`ucak` ( `kuyrukno` VARCHAR(10) NOT NULL , `model` VARCHAR(10) NOT NULL , `kapasite` INT(3) NOT NULL , PRIMARY KEY (`kuyrukno`)) ENGINE = InnoDB;"));
    mysql_query(baglan,("CREATE TABLE IF NOT EXISTS `airport`.`sefer` ( `tarih` VARCHAR(8) NOT NULL , `saat` VARCHAR(4) NOT NULL , `kuyrukno` VARCHAR(8) NOT NULL , `kapasite` INT(3) NOT NULL , `doluluk` INT(3) NOT NULL , `basno` INT(2) NOT NULL , `bitno` INT(2) NOT NULL , PRIMARY KEY (`kuyrukno`,`saat`,`tarih`)) ENGINE = InnoDB;"));
    mysql_query(baglan,("CREATE TABLE IF NOT EXISTS `airport`.`bilet` (`kuyrukno` VARCHAR(11) NOT NULL,`tarih` VARCHAR(8) NOT NULL,`saat` VARCHAR(4) NOT NULL,`tc` VARCHAR(11) NOT NULL, `basno` INT(2) NOT NULL , `bitno` INT(2) NOT NULL, PRIMARY KEY (`saat`,`tarih`, `kuyrukno`, `tc`, `basno`, `bitno`)) ENGINE = InnoDB;"));

    //UCAK LISTESI
    mysql_query(baglan, ("INSERT INTO `airport`.`ucak` (`kuyrukno`, `model`, `kapasite`) VALUES ('100', 'boeing', '200');"));
    mysql_query(baglan, ("INSERT INTO `airport`.`ucak` (`kuyrukno`, `model`, `kapasite`) VALUES ('010', 'boeing', '400');"));
    mysql_query(baglan, ("INSERT INTO `airport`.`ucak` (`kuyrukno`, `model`, `kapasite`) VALUES ('001', 'boeing', '600');"));
    mysql_query(baglan, ("INSERT INTO `airport`.`ucak` (`kuyrukno`, `model`, `kapasite`) VALUES ('200', 'super', '100');"));
    mysql_query(baglan, ("INSERT INTO `airport`.`ucak` (`kuyrukno`, `model`, `kapasite`) VALUES ('020', 'super', '300');"));
    mysql_query(baglan, ("INSERT INTO `airport`.`ucak` (`kuyrukno`, `model`, `kapasite`) VALUES ('002', 'super', '500');"));
    mysql_query(baglan, ("INSERT INTO `airport`.`ucak` (`kuyrukno`, `model`, `kapasite`) VALUES ('300', 'mega', '300');"));
    mysql_query(baglan, ("INSERT INTO `airport`.`ucak` (`kuyrukno`, `model`, `kapasite`) VALUES ('030', 'mega', '600');"));
    mysql_query(baglan, ("INSERT INTO `airport`.`ucak` (`kuyrukno`, `model`, `kapasite`) VALUES ('003', 'mega', '750');"));

        STEP:
        {
            system("CLS");
            char X[500], XX[500];
            int secim;
            int kapasite, basno, bitno, bilet, seferi;
            int tarih[8], saat[6], tc[11], isim[20], sehir[50], adres[50], eposta[20], doluluk[20];
            char kuyrukno[10];
            int sayac=0, i=0, k=0, val, val2;

            printf("\n--------------------------------------------------------------------------------\n\t\t\tta'la AIRPORT\n");
            printf("\n1)YENI SEFER TANIMLAMA\t\t2)BILET SATISI\n3)SORGULAMA ISLEMLERI\t\t4)IPTAL ISLEMLERI\n5)LISTELEME\t\t\t6)YENI KAYIT");
            printf("\n   ISLEMINIZI SECINIZ:");
            scanf("%d", &secim);
            switch(secim)
                {
                    case 1:
                        STEP1:  // SEFER EKLEME
                        {
                            printf("\nTARIH(ORN. 20170306): ");                        scanf("%s", &tarih);
                                {
                                    val=(int)strtol(tarih, (char**) NULL, 10);
                                        if( val/10000==2017)
                                        {
                                            if(((val%10000)/100)<6 || ((val%10000)/100)>12 || (val%100)>31)
                                               {
                                                    printf("\t\t!!LUTFEN HAZIRAN SONRASI AY VEYA 30'DAN KUCUK GUN GIRINIZ!!");
                                                    goto STEP1;
                                                }
                                            else printf("");
                                        }
                                        else
                                        {
                                            printf("\t\t!!LUTFEN 2017 YILI ICINDE BIR TARIH GIRINIZ!!");
                                            goto STEP1;
                                        }
                                }

                            printf("SAAT(ORN. 204500): ");                             scanf("%s", &saat);
                                {
                                    val=(int)strtol(saat, (char**) NULL, 10);
                                        if(val%100==00 && (val%10000)/100<60 && val/10000<24)
                                        {
                                            printf("");
                                        }
                                        else
                                        {
                                            printf("\t!!LUTFEN GECERLI BIR SAAT GIRINIZ(SANIYE 00 OLMALI)!!");
                                            goto STEP1;
                                        }
                                }

                            printf("UCAK KUYRUK NO(ORN. 300): ");                 scanf("%s", &kuyrukno);
                                {
                                    sprintf(X, "SELECT * FROM `ucak` WHERE `kuyrukno`=%s", kuyrukno);
                                    mysql_query(baglan, X);
                                    MYSQL_RES *sonuc=mysql_store_result(baglan);
                                    MYSQL_ROW satir;
                                        while((satir=mysql_fetch_row(sonuc)))
                                            {
                                                sayac++;
                                                kapasite=satir[2];
                                            }
                                        if(sayac<=0)
                                            {
                                                printf("\t\tYANLIS KUYRUKNO, LUTFEN DOGRU GIRINIZ!!");
                                                goto STEP1;
                                            }
                                }
                            printf("UCAK KALKIS NOKTASI(SEHIR PLAKASI-ORN. 41): ");  scanf("%d", &basno);
                            printf("UCAK INIS NOKTASI(SEHIR PLAKASI-ORN. 41): ");    scanf("%d", &bitno);
                            sprintf(X, "INSERT INTO `airport`.`sefer` (`tarih`, `saat`, `kuyrukno`, `kapasite`, `doluluk`, `basno`, `bitno`) VALUES (%s, %s, %s, %s, '0', %d,%d);",tarih, saat, kuyrukno, kapasite, basno, bitno);
                            mysql_query(baglan, X);
                            printf("\n\t   YENI SEFER BASARIYLA EKLENDI");

                            printf("\n\n\t1)YENI ISLEM\n\t2)YENI SEFER TANIMLAMA\n\t3)CIKIS");
                            printf("\n\t   ISLEMINIZI SECINIZ:");
                            scanf("%d", &secim);
                                if(secim==1)
                                    goto STEP;
                                else if(secim==2)
                                    goto STEP1;
                                else
                                    exit(1);
                        }
                        break;
                    case 2:     // BILET SATIN ALMA
                       STEP2:
                        {
                            printf("UCAK KALKIS NOKTASI(SEHIR PLAKASI-ORN. 41): ");     scanf("%d", &basno);
                            printf("UCAK INIS NOKTASI(SEHIR PLAKASI-ORN. 41): ");       scanf("%d", &bitno);
                                if(bitno==basno)
                                    {
                                        printf("\t\tAYNI SEHIRDEN AYNI SEHIRE SEFERIMIZ YOKTUR!!\n");
                                        goto STEP2;
                                    }
                            printf("TARIH(ORN. 20170202): ");                           scanf("%s", &tarih);
                            printf("BILET SAYISI: ");                                   scanf("%d", &bilet);

                            MYSQL_RES *sonuc2;
                            MYSQL_ROW satir2;
                            sprintf(X, "SELECT * FROM `sefer` WHERE `basno`=%d AND `bitno`=%d AND `tarih`=%s", basno, bitno, tarih);
                            sorgu=mysql_query(baglan, X);
                            sonuc2 = mysql_store_result(baglan);
                            i=0;
                                while((satir2=mysql_fetch_row(sonuc2)))
                                    {
                                        printf("\n%d.  tarih: %s, saat: %s, kapasite:%s",i+1, satir2[0], satir2[1], satir2[3]);
                                        i++;
                                    }
                                if(i<=0)
                                    {
                                        printf("\t\tBOYLE BIR SEFERIMIZ YOKTUR, LUTFEN TEKRAR DENEYIN!!\n");
                                        goto STEP2;
                                    }
                            printf("\nLUTFEN SEFER SECINIZ: ");   scanf("%d", &seferi);
                            {
                                MYSQL_RES *sonuc2;
                                MYSQL_ROW satir2;
                                sprintf(X, "SELECT * FROM `sefer` WHERE `basno`=%d AND `bitno`=%d AND `tarih`=%s", basno, bitno, tarih);
                                sorgu=mysql_query(baglan, X);
                                sonuc2 = mysql_store_result(baglan);
                                k=0;
                                while((satir2=mysql_fetch_row(sonuc2)))
                                    {
                                        if(i==(seferi))
                                        {
                                            strcpy(tarih, satir2[0]);
                                            strcpy(saat, satir2[1]);
                                            strcpy(kuyrukno, satir2[2]);
                                            strcpy(doluluk, satir2[4]);
                                            val=(int)strtol(doluluk, (char**) NULL, 10);
                                            for(k=0; k<bilet; k++)
                                            {
                                                printf("\nBILET ICIN TC GIRINIZ: ");    scanf("%s", &tc);
                                                {
                                                    val2=(int)strtol(tc, (char**) NULL, 10);
                                                    if(val2<1000000000)
                                                        {

                                                            printf("\n\t\tLUTFEN 11 HANELI TC GIRINIZ!! ");
                                                            goto STEP2;
                                                        }
                                                    sprintf(X, "SELECT * FROM `musteri` WHERE `tc`=%s", tc);
                                                    mysql_query(baglan, X);
                                                    int say=0;
                                                    MYSQL_RES *sonuc=mysql_store_result(baglan);
                                                    MYSQL_ROW satir;
                                                        while((satir=mysql_fetch_row(sonuc)))
                                                            {
                                                                say++;
                                                                strcpy(tc, satir[0]);
                                                                strcpy(isim, satir[1]);
                                                                strcpy(adres, satir[2]);
                                                                strcpy(eposta, satir[3]);
                                                            }

                                                        if(say<=0)
                                                            {
                                                                printf("\nKULLANICI KAYDI OLUSTURMA:");
                                                                printf("\nISIM SOYISIM:");  scanf("%s", &isim);
                                                                printf("\nADRES:");         scanf("%s", &adres);
                                                                printf("\nEPOSTA:");        scanf("%s", &eposta);
                                                                printf("\nSEHIR:");         scanf("%s", &sehir);
                                                                sprintf(X, "INSERT INTO `airport`.`musteri` (`tc`, `isim`, `adres`, `eposta`, `sehir`) VALUES (%s, %s, %s, %s, %s);",tc, isim, adres, eposta, sehir);
                                                                sorgu=mysql_query(baglan, X);
                                                            }
                                                }
                                                sprintf(X, "INSERT INTO `airport`.`bilet` (`kuyrukno`, `tarih`, `saat`, `tc`, `basno`, `bitno`) VALUES (%s, %s, %s, %s, %d,%d);",kuyrukno, tarih, saat, tc, basno, bitno);
                                                sorgu=mysql_query(baglan, X);
                                                val+=1;
                                                sprintf(XX, "UPDATE `airport`.`sefer` SET `doluluk` = %d WHERE `sefer`.`kuyrukno` =%s", val, kuyrukno);
                                                mysql_query(baglan, XX);
                                            }
                                        }
                                        i++;
                                    }
                            }
                            printf("\n\n\t1)YENI ISLEM\n\t2)YENI BILET SATISI\n\t3)CIKIS");
                            printf("\n\t   ISLEMINIZI SECINIZ:");
                            scanf("%d", &secim);
                            if(secim==1)
                                goto STEP;
                            else if(secim==2)
                                goto STEP2;
                            else
                                exit(1);
                        }
                        break;
                    case 3:     // SORGULAMA ISLEMLERI
                        STEP3:
                        {
                            printf("\n\t1)YOLCU SORGULAMA\n\t2)SEFER SORGULAMA\n\t3");
                            printf("LUTFEN SORGU TIPINI SECINIZ:");
                            scanf("%d", &secim);
                                switch(secim)
                                {
                                    case 1:

                                       STEP31:// YOLCU SORGULAMA
                                        {
                                            printf("\nTC ILE BILET SORGULAMA ");
                                            printf("LUTFEN TC GIRINIZ: ");                 scanf("%s", &tc);
                                            {
                                                sprintf(X, "SELECT * FROM `bilet` WHERE `tc`=%s", tc);
                                                mysql_query(baglan, X);
                                                MYSQL_RES *sonuc=mysql_store_result(baglan);
                                                MYSQL_ROW satir;
                                                i=0;
                                                    while((satir=mysql_fetch_row(sonuc)))
                                                        {
                                                            printf("\n%d.",i+1);
                                                            printf("  tarih: %s\tsaat: %s\ttc:%s\tbaslangic noktasi:%s\tbitis noktasi:%s", satir[1], satir[2], satir[3], satir[4],satir[5]);

                                                            i++;
                                                            sayac++;
                                                        }
                                                    if(sayac<=0)
                                                        {
                                                            printf("\t\tTC BULUNAMADI, LUTFEN DOGRU TC GIRINIZ!!");
                                                            goto STEP31;
                                                        }
                                            }
                                        }
                                        printf("\n\n\t1)YENI ISLEM\n\t2)YENI SORGULAMA\n\t3)CIKIS");
                                        printf("\n\t   ISLEMINIZI SECINIZ:");
                                        scanf("%d", &secim);
                                            if(secim==1)
                                                goto STEP;
                                            else if(secim==2)
                                                goto STEP3;
                                            else
                                                exit(1);
                                        break;
                                    case 2:
                                        STEP32:// SEFER YOLCU BILGISI
                                        {
                                            printf("\nSEFER SORGULAMA ");
                                            printf("LUTFEN TARIH GIRINIZ: ");                 scanf("%s", &tarih);
                                            printf("LUTFEN KUYRUK NO GIRINIZ: ");                 scanf("%s", &kuyrukno);
                                            {
                                                sprintf(X, "SELECT * FROM `bilet` WHERE `tarih`=%s AND `kuyrukno`=%s", tarih, kuyrukno);
                                                mysql_query(baglan, X);
                                                MYSQL_RES *sonuc=mysql_store_result(baglan);
                                                MYSQL_ROW satir;
                                                    while((satir=mysql_fetch_row(sonuc)))
                                                        {
                                                            strcpy(tc, satir[3]);
                                                            sayac++;
                                                            sprintf(XX, "SELECT * FROM `musteri` WHERE `tc`=%s", tc);
                                                            mysql_query(baglan, XX);
                                                            MYSQL_RES *sonuc2=mysql_store_result(baglan);
                                                            MYSQL_ROW satir2;
                                                            i=1;
                                                                while((satir2=mysql_fetch_row(sonuc2)))
                                                                    {
                                                                        printf("%d. tc: %s\tisim: %s\tadres:%s\teposta:%s",i, satir2[0],satir2[1], satir2[2], satir2[3]);
                                                                        i++;
                                                                    }
                                                        }
                                                    if(sayac<=0)
                                                        {
                                                            printf("\t\tHATALI BILGI!!");
                                                            goto STEP32;
                                                        }
                                            }
                                        }
                                        printf("\n\n\t1)YENI ISLEM\n\t2)YENI SORGULAMA\n\t3)CIKIS");
                                        printf("\n\t   ISLEMINIZI SECINIZ:");
                                        scanf("%d", &secim);
                                            if(secim==1)
                                                goto STEP;
                                            else if(secim==2)
                                                goto STEP3;
                                            else
                                                exit(1);
                                        break;
                                    default:
                                        printf("\tYANLIS SECIM!!");
                                        printf("\n\n\t1)YENI ISLEM\n\t2)YENI SORGULAMA\n\t3)CIKIS");
                                        printf("\n\t   ISLEMINIZI SECINIZ:");
                                        scanf("%d", &secim);
                                            if(secim==1)
                                                goto STEP;
                                            else if(secim==2)
                                                goto STEP3;
                                            else
                                                exit(1);
                                }
                        }
                        break;
                    case 4:
                       STEP4:   // IPTAL ISLEMLERI
                        {
                            printf("\n\t1)UCUS IPTALI\n\t2)BILET IPTALI\n\t3");
                            printf("LUTFEN IPTAL TIPINI SECINIZ:");
                            scanf("%d", &secim);

                            switch(secim)
                            {
                                case 1:
                                    STEP41:
                                    {
                                        printf("UCUS IPTALI");
                                        printf("\nBILET IPTALI");
                                        printf("\nLUTFEN IPTAL EDILCEK SEFER ICIN:");
                                        printf("\nTARIH: "); scanf("%s", &tarih);
                                        printf("\nKUYRUK NO: "); scanf("%s", &kuyrukno);
                                        printf("\nSAAT: "); scanf("%s", &saat);
                                        {
                                                sprintf(X, "SELECT * FROM `sefer` WHERE `kuyrukno`=%s AND `tarih`=%s AND `saat`=%s", kuyrukno, tarih, saat);
                                                mysql_query(baglan, X);
                                                MYSQL_RES *sonuc=mysql_store_result(baglan);
                                                MYSQL_ROW satir;
                                                    while((satir=mysql_fetch_row(sonuc)))
                                                        {
                                                            sayac++;
                                                            strcpy(tarih, satir[0]);
                                                            strcpy(saat, satir[1]);
                                                            strcpy(kuyrukno, satir[2]);
                                                        }
                                                    if(sayac<=0)
                                                        {
                                                            printf("\t\tYANLIS KUYRUKNO/TARIH/SAAT, LUTFEN DOGRU GIRINIZ!!");
                                                            goto STEP41;
                                                        }
                                                sprintf(X, "DELETE FROM `sefer` WHERE `saat` = %s AND `kuyrukno`=%s AND `tarih`=%s", saat, kuyrukno, tarih);
                                                mysql_query(baglan, X);
                                                sprintf(XX, "DELETE FROM `bilet` WHERE `saat` = %s AND `kuyrukno`=%s AND `tarih`=%s", saat, kuyrukno, tarih);
                                                mysql_query(baglan, XX);
                                        }
                                    }
                                    printf("\n\n\t1)YENI ISLEM\n\t2)YENI SORGULAMA\n\t3)CIKIS");
                                    printf("\n\t   ISLEMINIZI SECINIZ:");
                                    scanf("%d", &secim);
                                        if(secim==1)
                                            goto STEP;
                                        else if(secim==2)
                                            goto STEP4;
                                        else
                                            exit(1);
                                    break;
                                case 2:
                                    STEP42:
                                    {
                                        printf("\nBILET IPTALI");
                                        printf("\nLUTFEN IPTAL EDILCEK BILET ICIN:");
                                        printf("\nTARIH: "); scanf("%s", &tarih);
                                        printf("\nKUYRUK NO: "); scanf("%s", &kuyrukno);
                                        printf("\nTC: "); scanf("%s", &tc);
                                        {
                                            sprintf(X, "SELECT * FROM `bilet` WHERE `kuyrukno`=%s AND `tarih`=%s AND `tc`=%s", kuyrukno, tarih, tc);
                                            mysql_query(baglan, X);
                                            MYSQL_RES *sonuc=mysql_store_result(baglan);
                                            MYSQL_ROW satir;
                                                while((satir=mysql_fetch_row(sonuc)))
                                                    {
                                                        sayac++;
                                                    }
                                                if(sayac<=0)
                                                    {
                                                        printf("\t\tYANLIS KUYRUKNO/TARIH/TC, LUTFEN DOGRU GIRINIZ!!");
                                                        goto STEP42;
                                                    }
                                            sprintf(X, "DELETE FROM `bilet` WHERE `tc` = %s AND `kuyrukno`=%s AND `tarih`=%s", tc, kuyrukno, tarih);
                                            mysql_query(baglan, X);
                                        }
                                    }
                                    printf("\n\n\t1)YENI ISLEM\n\t2)YENI SORGULAMA\n\t3)CIKIS");
                                        printf("\n\t   ISLEMINIZI SECINIZ:");
                                        scanf("%d", &secim);
                                            if(secim==1)
                                                goto STEP;
                                            else if(secim==2)
                                                goto STEP4;
                                            else
                                                exit(1);

                                    break;
                                default:
                                        printf("\tYANLIS SECIM!!");
                                        printf("\n\n\t1)YENI ISLEM\n\t2)YENI SORGULAMA\n\t3)CIKIS");
                                        printf("\n\t   ISLEMINIZI SECINIZ:");
                                        scanf("%d", &secim);
                                            if(secim==1)
                                                goto STEP;
                                            else if(secim==2)
                                                goto STEP3;
                                            else
                                                exit(1);

                            }
                            printf("\n\t1)YENI ISLEM\n\t2)YENI IPTAL ISLEMI\n\t3)CIKIS");
                            printf("\n\t   ISLEMINIZI SECINIZ:");
                            scanf("%d", &secim);
                            if(secim==1)
                                goto STEP;
                            else if(secim==2)
                                goto STEP4;
                            else
                                exit(1);
                        }
                        break;
                    case 5:
                        STEP5:
                        {
                            // LISTELEME ISLEMLERI
                            printf("DOLULUK ORANINA GORE UCUSLAR:\n");
                            sprintf(X, "SELECT * FROM `sefer` ORDER BY `doluluk` DESC");
                            mysql_query(baglan, X);
                            MYSQL_RES *sonuc=mysql_store_result(baglan);
                            MYSQL_ROW satir;
                                while((satir=mysql_fetch_row(sonuc)))
                                    {
                                        strcpy(doluluk, satir[4]);
                                        val=(int)strtol(doluluk, (char**) NULL, 10);
                                        if(val!=0)
                                            printf("\ntarih=%s\tsaat=%s\tkuyrukno=%s\tkapasite=%s\tdoluluk=%s\tbaslangic noktasi=%s\tbitis noktasi=%s", satir[0], satir[1], satir[2], satir[3], satir[4], satir[5], satir[6]);
                                    }

                            printf("\n\t1)YENI ISLEM\n\t2)CIKIS");
                            printf("\n\t   ISLEMINIZI SECINIZ:");
                            scanf("%d", &secim);
                            if(secim==1)
                                goto STEP;
                            else
                                exit(1);
                        }
                        break;
                    case 6:
                        STEP6:
                        {
                            printf("\nKAYDOLACAK KULLANICI TC GIRINIZ: ");    scanf("%s", &tc);
                            val2=(int)strtol(tc, (char**) NULL, 10);
                                if(val2<1000000000)
                                    {
                                        printf("\n\t\tLUTFEN 11 HANELI TC GIRINIZ!! ");
                                        goto STEP6;
                                    }

                            sprintf(X, "SELECT * FROM `musteri` WHERE `tc`=%s", tc);
                            mysql_query(baglan, X);
                            int say=0;
                            MYSQL_RES *sonuc=mysql_store_result(baglan);
                            MYSQL_ROW satir;
                                while((satir=mysql_fetch_row(sonuc)))
                                    {
                                        say++;
                                        strcpy(tc, satir[0]);
                                        strcpy(isim, satir[1]);
                                        strcpy(adres, satir[2]);
                                        strcpy(eposta, satir[3]);
                                    }

                                if(say<=0)
                                    {
                                        printf("\nKULLANICI KAYDI OLUSTURMA:");
                                        printf("\nISIM SOYISIM:");  scanf("%s", &isim);
                                        printf("\nADRES:");         scanf("%s", &adres);
                                        printf("\nEPOSTA:");        scanf("%s", &eposta);
                                        printf("\nSEHIR:");         scanf("%s", &sehir);
                                        sprintf(X, "INSERT INTO `airport`.`musteri` (`tc`, `isim`, `adres`, `eposta`, `sehir`) VALUES (%s, %s, %s, %s, %s);",tc, isim, adres, eposta, sehir);
                                        sorgu=mysql_query(baglan, X);
                                    }
                            printf("\n\t1)YENI ISLEM\n\t2)CIKIS");
                            printf("\n\t   ISLEMINIZI SECINIZ:");
                            scanf("%d", &secim);
                            if(secim==1)
                                goto STEP;
                            else
                                exit(1);
                        }
                        break;
                    default:
                        printf("YANLIS SECIM!!");
                        goto STEP;
                }
       }
    return 0;
}
