### Kocaeli University AirportDatabase Project

**Projenin Amacı:**
Ulusal bir havayolu acentesi için bir veri tabanı tasarlanması istenmektedir.

**Veri tabanı yapısı:**
1. Yolcular için yolcu ismi, adresi ve e-posta adresi saklanacaktır. Her yolcu için ayrıca TCKN tutulacak ve bu bilgi anahtar olacaktır. Adres bilgisinde yolcunun yaşadığı şehir ayrı bir alan olarak saklanacaktır.
2. Uçaklar için modeli ve kapasitesi saklanacaktır. Her uçak için kuyruk numarası (Alfanumeric) saklanacaktır ve bu numara uçağın anahtarı olacaktır. 
3. Seferler için seferin başlangıç noktası, bitiş noktası, tarih ve saat bilgisi (string :1345 gibi yazılacaktır) saklanacaktır. Her uçuş için uçuşun tarihi (string: 13052017 gibi yazılacaktır)  ve uçağın kuyruk numarasından oluşan bir anahtar tanımlanacaktır. Başlangıç ve bitiş noktaları şehirlerin plaka kodları ile ifade edilecektir. 
4. Yolcular için oluşturulacak yolcu tablosu için alan adları tarih, uçuşun anahtarı (uçak kuyruk no (ukn) ),yolcunun TCKN, başlangıç noktası (bn) ve bitiş noktası (bin) şeklinde tutulacaktır. 5 alanda (tarih, ukn, TCKN, bn, bin) yolcu tablosunda hepsi birer key şeklinde tutulacaktır
    
    
**Veri tabanı için yapılabilen işlemler:**
1. Yeni sefer tanımlama (sefer tablosu): Bu işlemde uçağın kuyruk numarası, tarih, başlangıç noktası ve bitiş noktası bilgileri istenecektir.
2. Bilet satma: Başlangıç ve bitiş noktaları, tarih ve bilet sayısı sorulacaktır. Bu bilgilere göre uygun olan uçuşlardan öncelikle direk uçuşlar, sonra 1 aktarmalı ve son olarak da 2 aktarmalı uçuşlar listelenecektir. Seçilen uçuş numarası için bir önceki aşamada sorulan bilet sayısı kadar TCKN istenecektir. Eğer TCKN yolcu tablosunda yoksa bu TCKN ile ilgili bilgiler istenecektir. Bilet satma işlemi gerçekleştirildiğinde yolcu tablosuna direkt ekleme işlemi yapılacaktır.
3. Yolcu sorgulama: TCKN göre kişinin yaptığı uçuşlar listelenecektir.
4. Uçuş iptali: İptal edilen uçuş ya da uçuşlar olursa bilet tablosunda o uçuşla ilgili tüm bilgiler silinecektir. Bu işlem on deletecascadeopsiyonu ile sağlanmalıdır. Cascade işlemi ile eğer bir uçuş silinirse bu uçuşa bağlı olan başka bir bağlantılı uçuş (yani bu uçuş aktarmalı uçuşsa) bulunuyorsa bu uçuşunda silinmesi gerekmektedir.
5. Bilet iptali: TCKN, tarih ve uçak kuyruk numarası için gerekli silme işlemi yapılacaktır.
6. Sefer sorgulama: Verilen tarih ve kuyruk numarasına göre o uçuşta yer alacak yolcuların tüm bilgileri listelenecektir.
7. Doluluk oranı en fazla olan uçuşlar listelenecektir. Bu işlem için yolcu tablosundan yararlanmanız gerekmektedir.
8. Tanımlı olmayan uçak için sefer bilgisi, tanımlı olmayan yolcu için uçuş bilgisi oluşturulamayacaktır. Eğer uçak kapasitesi yeterli değilse bilet satışı yapılamayacaktır.     
