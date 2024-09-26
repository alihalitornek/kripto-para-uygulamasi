/****************************************************************************
**					          SAKARYA ÜNİVERSİTESİ
**			         BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ
**				          BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ
**				             PROGRAMLAMAYA GİRİŞİ DERSİ
**
**				        ÖDEV NUMARASI....: 2.ÖDEV
**				        ÖĞRENCİ ADI......: Ali Halit Örnek
**				        ÖĞRENCİ NUMARASI.: B231210385
**				        DERS GRUBU.......: A
****************************************************************************/

#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;
int kacıncıhesap = 0;// en sonki hesabın kaçıncı indis olduğunu tutar

//genel olarak tarih ile ilgili ve tarih değişimine bağlı işlemlerin yapıldığı class
class Tarih
{
protected:
    int gun, ay, yil;// dinamik zaman değerleri
    int ilkgun, ilkay, ilkyil;// zamanın başlangıç değerlerini tutar
    int kacincigun = 0;//başlagıc tarihinden itibaren yani zamanın başlangıcından beri geçen toplam zaman
    int hesabınacıldıgıgun = 0;//hesabın açıldığı ilk gün
    int hesabınacıldıgıay = 0;//hesabın açıldığı ilk ay
    int hesabınacıldıgıyil = 0;//hesabın açıldığı ilk yıl
    int kacdefaartacak;//krpdegerdegisimi() fonksiyonu için kaçdefa artacağını söyler
    int kacdefaazalacak;//krpdegerdegisimi() fonksiyonu için kaçdefa azalacağını söyler
    float krpdeger = 1;//(KRP bizim borsamızın standart kripto para birimidir) krpdeger KRPnin borsadaki günlük fiyatlanan güncel değeridir ve tüm hesapların alıs satıs oranıdır(KRP/TL)
    float okrpdeger = 1;//(OKRP bizim borsamızın ozel kripto para birimidir) okrpdeger OKRPnin borsadaki günlük fiyatlanan güncel değeridir ve tüm hesapların alıs satıs oranıdır(OKRP/TL)
    float ilkguntoplamkrpdegeri;//hesabın açıldığı ilk günkü toplam kripto para değerini tutar KRP ve OKRP değerlerinin ikisi içinde geçerlidir
    float hesaptakikrp = 0;//hesaptaki KRP değerini tutar 
    float hesaptakiokrp = 0;//hesaptaki OKRP değerini tutar 
    int dususgunu1, dususgunu2, dususgunu3;//ozel hesaplar için rastgele 3 düşüş günü değerleridir
public:
    void tarihal()//kullanıcıdan bir tarih değeri alır
    {
        do
        {
            cout << "lutfen gun degerini girin(0-31) ";
            cin >> gun;

        } while (!(gun <= 31 && gun > 0));
        do
        {
            cout << "lutfen ay degerini girin(0-12) ";
            cin >> ay;

        } while (!(ay <= 12 && ay > 0));
        do
        {
            cout << "lutfen yil degerini girin(2000-2023) ";
            cin >> yil;

        } while (!(yil <= 2023 && yil >= 2000));
        ilkgun = gun;
        ilkay = ay;
        ilkyil = yil;
    }

    void tarihdegisimi()//tarihin ilerlemesini sağlar
    {
        int kacgunilerisar;
        cout << "zamani kac gun ileri sarmak istersiniz";
        cin >> kacgunilerisar;
        for (;0 < kacgunilerisar;kacgunilerisar--)
        {
            if (ay == 12 && gun == 31)
            {
                yil++;ay = 1;gun = 1; okrpdegerdegisimi();
            }
            else if (ay < 12 && gun == 31)
            {
                ay++; gun = 1; okrpicindususgunleri(); //her aylık değişim yeni değerler almamızı gerektirir
                okrpdegerdegisimi(); //her aylık değişimde çağırmamızın sebebi else if'in içine girince else'nin içine girmeyecek ama bunu her zaman değişiminde çağırmak zorundayız(aynısı yıl içinde geçerli)
            }

            else
            {
                gun++; okrpdegerdegisimi();//her gün düşüş günü mü değil mi kontrol edilmeli
            }
        }
        krpdegerdegisimi();//değerini tarih ilerledikçe güncellemek zorundayız
        karkrpicin();

    }
    void gettarih()//tarih değeri alır
    {
        cout << "Tarih :" << "(" << gun << "/" << ay << "/" << yil << ")\n";
    }
    int kacincigunhesapla()//bu başlagıc tarihinden itibaren yani zamanın başlangıcından beri geçen toplam zaman
    {
        kacincigun = 0;
        kacincigun += (t.gun - ilkgun);
        kacincigun += (31 * (t.ay - ilkay));
        kacincigun += (372 * (t.yil - ilkyil));
        return kacincigun;
    }
    void hesabınacıldıgıtarih()//hesabın açıldığı tarihi hesaplar
    {
        hesabınacıldıgıgun = t.gun;
        hesabınacıldıgıay = t.ay;
        hesabınacıldıgıyil = t.yil;
    }
    void krpdegerdegisimi()//KRP'nin günlük değişen piyasa kur oranını hesaplar
    {
        kacincigun = kacincigunhesapla();
        kacdefaartacak = (kacincigun - int(kacincigun / 15));
        kacdefaazalacak = int(kacincigun / 15);
        if (kacdefaartacak != 0)
        {
            krpdeger = pow((1.01), kacdefaartacak);
        }
        if (kacdefaazalacak != 0)
        {
            krpdeger = krpdeger * pow((0.95), kacdefaazalacak);
        }
    }
    void okrpdegerdegisimi()//OKRP'nin günlük değişen piyasa kur oranını hesaplar
    {

        if (gun == dususgunu1 || gun == dususgunu2 || gun == dususgunu3)
        {
            okrpdeger = okrpdeger * 0.9;
        }
        else
        {
            okrpdeger = okrpdeger * 1.05;
        }


    }
    void okrpicindususgunleri()//OKRP icin rastgele dudus gunleri belirler bunlar birbirlerinden farklı olmak zorunda
    {
        srand(time(0));
        while (!(dususgunu1 != dususgunu2 != dususgunu3))
        {
            dususgunu1 = (rand() % 31) + 1;
            dususgunu2 = (rand() % 31) + 1;
            dususgunu3 = (rand() % 31) + 1;
        }

    }
    float getkrpdeger()//KRP'nin değerini verir
    {
        return t.krpdeger;
    }
    float getokrpdeger()//OKRP'nin değerini verir
    {
        return t.okrpdeger;
    }
    float karkrpicin()//hesabın açıldığı ilk güne göre krpnin toplam değerindeki değişimi hesaplar
    {
        if (t.gun == hesabınacıldıgıgun && t.ay == hesabınacıldıgıay && t.yil == hesabınacıldıgıyil)
        {
            ilkguntoplamkrpdegeri = hesaptakikrp * t.krpdeger;
        }

        return (hesaptakikrp * t.krpdeger) - ilkguntoplamkrpdegeri;

    }
    float karokrpicin()//hesabın açıldığı ilk güne göre okrpnin toplam değerindeki değişimi hesaplar
    {
        if (t.gun == hesabınacıldıgıgun && t.ay == hesabınacıldıgıay && t.yil == hesabınacıldıgıyil)
        {
            ilkguntoplamkrpdegeri = hesaptakiokrp * t.okrpdeger;
        }

        return (hesaptakiokrp * t.okrpdeger) - ilkguntoplamkrpdegeri;

    }
}t;
// Hesap classı genel olarak herbir nesnesi ayrı bir hesap olan ve çoğu metodu barındıran classtır
class Hesap :private Tarih
{
private:
    string hesapNo = " ";//hesapların numaralarını tutar
    float hesaptakitl = 0;//hesaptaki güncel TL değeri
    float krptoplamdeger = 0;//hesaptaki KRP adediyle KRP değerinin çarpımı yani KRPnin anlık (KRP/TL) kuruna göre TL karşılığı
    float okrptoplamdeger = 0;//hesaptaki OKRP adediyle OKRP değerinin çarpımı yani OKRPnin anlık (OKRP/TL) kuruna göre TL karşılığı
    string hesaptur;// hesabın türünü tutar
public:
    void parayatir()//hesaba para yatırmamızı sağlar
    {

        float islemdekitl;//kullanıcının istediği değişim miktarı
        char ch;//konrol karakteri
        while (1)
        {
            ch = 'h';
            cout << "Hesaba kac TL eklemek istersiniz\n";
            cin >> islemdekitl;
            if (islemdekitl >= 0)
            {
                hesaptakitl += islemdekitl;
            }
            else
            {
                cout << "Negatif para yatirilamaz terkrar denemek istermisiniz(e/h)\n";
                cin >> ch;
            }

            system("cls");
            if (!(ch == 'e' || ch == 'E'))
            {
                break;
            }

        }
    }
    void parayacek()//hesaptan paraçekmemizi sağlar
    {
        float islemdekitl;//kullanıcının istediği değişim miktarı
        char ch;//konrol karakteri
        while (1)
        {
            ch = 'h';
            cout << "Hesaptan kac TL cekmek istersiniz\n";
            cin >> islemdekitl;
            if ((hesaptakitl - islemdekitl) >= 0 && islemdekitl >= 0)
            {
                hesaptakitl -= islemdekitl;
            }
            else if (islemdekitl < 0)
            {
                cout << "Negatif para cekilemez terkrar denemek istermisiniz(e/h)\n";
                cin >> ch;
            }
            else
            {
                cout << "Yetersiz bakiye terkrar denemek istermisiniz(e/h)\n";
                cin >> ch;
            }

            system("cls");
            if (!(ch == 'e' || ch == 'E'))
            {
                break;
            }

        }

    }
    void alkrpicin()//KRP satın almamızı sağlar
    {
        float islemdekitl;//kullanıcının istediği azalacak TL
        float islemdekikrp;//kullanıcının isteği sonucu artacak KRP
        char ch;//konrol karakteri
        while (1)
        {
            ch = 'h';
            cout << "KRP'nin degeri(KRP/TL) : " << getkrpdeger();
            cout << "\nKac TL'lik alis yapacaksiniz";
            cin >> islemdekitl;
            if ((hesaptakitl - islemdekitl) >= 0 && islemdekitl >= 0)
            {
                islemdekikrp = islemdekitl / getkrpdeger();
                hesaptakikrp += islemdekikrp;
                hesaptakitl -= islemdekitl;
            }
            else if (islemdekitl < 0)
            {
                cout << "Negatif alis yapilamaz terkrar denemek istermisiniz(e/h)\n";
                cin >> ch;
            }
            else
            {
                cout << "Yetersiz bakiye terkrar denemek istermisiniz(e/h)\n";
                cin >> ch;
            }

            system("cls");
            if (!(ch == 'e' || ch == 'E'))
            {
                break;
            }
        }


    }
    void alokrpicin()//OKRP satın almamızı sağlar
    {
        float islemdekitl;//kullanıcının istediği azalacak TL
        float islemdekiokrp;//kullanıcının isteği sonucu artacak OKRP
        char ch;//konrol karakteri
        while (1)
        {
            ch = 'h';
            cout << "OKRP'nin degeri(OKRP/TL) : " << getokrpdeger();
            cout << "\nKac TL'lik alis yapacaksiniz";
            cin >> islemdekitl;
            if ((hesaptakitl - islemdekitl) >= 0 && islemdekitl >= 0)
            {
                islemdekiokrp = islemdekitl / getokrpdeger();
                hesaptakiokrp += islemdekiokrp;
                hesaptakitl -= islemdekitl;
            }
            else if (islemdekitl < 0)
            {
                cout << "Negatif alis yapilamaz terkrar denemek istermisiniz(e/h)\n";
                cin >> ch;
            }
            else
            {
                cout << "Yetersiz bakiye terkrar denemek istermisiniz(e/h)\n";
                cin >> ch;
            }

            system("cls");
            if (!(ch == 'e' || ch == 'E'))
            {
                break;
            }
        }
    }
    void satkrpicin()//KRP satmamızı sağlar
    {
        float islemdekitl;//kullanıcının isteği sonucu artacak TL
        float islemdekikrp;//kullanıcının istediği azalacak KRP
        char ch;//konrol karakteri
        while (1)
        {
            ch = 'h';
            cout << "KRP'nin degeri(KRP/TL) : " << getkrpdeger();
            cout << "\nKac KRP'lik satis yapacaksiniz";
            cin >> islemdekikrp;
            if ((hesaptakikrp - islemdekikrp) >= 0 && islemdekikrp >= 0)
            {
                islemdekitl = islemdekikrp * getkrpdeger();
                hesaptakikrp -= islemdekikrp;
                hesaptakitl += islemdekitl;
            }
            else if (islemdekikrp < 0)
            {
                cout << "Negatif satis yapilamaz terkrar denemek istermisiniz(e/h)\n";
                cin >> ch;
            }
            else
            {
                cout << "Yetersiz bakiye terkrar denemek istermisiniz(e/h)\n";
                cin >> ch;
            }

            system("cls");
            if (!(ch == 'e' || ch == 'E'))
            {
                break;
            }
        }


    }
    void satokrpicin()//OKRP satmamızı sağlar
    {
        float islemdekitl;//kullanıcının isteği sonucu artacak TL
        float islemdekiokrp; //kullanıcının istediği azalacak OKRP
        char ch;//konrol karakteri
        while (1)
        {
            ch = 'h';
            cout << "OKRP'nin degeri(OKRP/TL) : " << getokrpdeger();
            cout << "\nKac OKRP'lik satis yapacaksiniz";
            cin >> islemdekiokrp;
            if ((hesaptakiokrp - islemdekiokrp) >= 0 && islemdekiokrp >= 0)
            {
                islemdekitl = islemdekiokrp * getokrpdeger();
                hesaptakiokrp -= islemdekiokrp;
                hesaptakitl += islemdekitl;
            }
            else if (islemdekiokrp < 0)
            {
                cout << "Negatif satis yapilamaz terkrar denemek istermisiniz(e/h)\n";
                cin >> ch;
            }
            else
            {
                cout << "Yetersiz bakiye terkrar denemek istermisiniz(e/h)\n";
                cin >> ch;
            }

            system("cls");
            if (!(ch == 'e' || ch == 'E'))
            {
                break;
            }
        }
    }
    void bakiye()//Hesap bilgilerini görüntüler
    {
        if (hesaptur == "genel hesap")
            cout << "Hesap numaraniz :" << hesapNo << "\nHesap turu :" << hesaptur << "\nMevcut KRP miktari :" << hesaptakikrp << "\nMevcut TL miktari :" << hesaptakitl << "\nKRP'nin toplam degeri :" << krptoplamdegerhesapla() << "\nHesabin ilk gune gore degisimi :" << karkrpicin() << endl << endl;
        else
            cout << "Hesap numaraniz :" << hesapNo << "\nHesap turu :" << hesaptur << "\nMevcut OKRP miktari :" << hesaptakiokrp << "\nMevcut TL miktari :" << hesaptakitl << "\nOKRP'nin toplam degeri :" << okrptoplamdegerhesapla() << "\nHesabin ilk gune gore degisimi :" << karokrpicin() << endl << endl;

    }

    void genelhesapac()//genel hesap açmamızı sağlar
    {
        string kontrol;
        cout << "lutfen bir hesap no giriniz";
        cin >> h[kacıncıhesap].hesapNo;
        do
        {
            for (int sayac = kacıncıhesap - 1;!(sayac == 0);sayac--)
            {
                if (h[sayac].hesapNo == h[kacıncıhesap].hesapNo)
                {
                    cout << "bu hesap no zaten kullaniliyor yeni bir tane girin";
                    cin >> h[kacıncıhesap].hesapNo;
                    kontrol = "kullanilmis";
                }
                else
                {
                    kontrol = "kullanilmamis";
                }



            }
        } while (kontrol == "kullanilmis");


        parayatir();//ilk parayi yatirmak icin
        hesaptur = "genel hesap";
        hesabınacıldıgıtarih();//hesabin acildigi tarihi tutmamızı sağlar
    }
    void ozelhesapac()//özel hesap açmamızı sağlar
    {
        string kontrol;
        cout << "lutfen bir hesap no giriniz";
        cin >> h[kacıncıhesap].hesapNo;
        do
        {
            for (int sayac = kacıncıhesap - 1;!(sayac == 0);sayac--)
            {
                if (h[sayac].hesapNo == h[kacıncıhesap].hesapNo)
                {
                    cout << "bu hesap no zaten kullaniliyor yeni bir tane girin";
                    cin >> h[kacıncıhesap].hesapNo;
                    kontrol = "kullanilmis";
                }
                else
                {
                    kontrol = "kullanilmamis";
                }



            }
        } while (kontrol == "kullanilmis");



        parayatir();//ilk parayi yatirmak icin
        hesaptur = "ozel hesap";
        hesabınacıldıgıtarih();//hesabin acildigi tarihi tutmamızı sağlar
    }

    float krptoplamdegerhesapla()// elimizdeki krpnin piyasa fiyatına göre tl ederini hesaplar
    {
        return krptoplamdeger = hesaptakikrp * getkrpdeger();
    }
    float okrptoplamdegerhesapla()// elimizdeki okrpnin piyasa fiyatına göre tl ederini hesaplar
    {
        return okrptoplamdeger = hesaptakiokrp * getokrpdeger();
    }
    string gethesaptur()// hesap turunu soyler
    {
        return hesaptur;
    }

    int nogirilenhesapkacinci(string secilenhesapno)//hesapno'sunu bildiğimiz bir hesabın h[?] olarak kaçıncı indiste depolandığını bulmamızı sağlar
    {
        char ch;
        while (1)
        {
            for (int sayac = kacıncıhesap;!(sayac == 0);sayac--)
            {
                if (h[sayac].hesapNo == secilenhesapno)
                {
                    return sayac;
                }
            }
            cout << "Sectiginiz hesap no bulunamadi terkrar denemek istermisiniz(e/h)";
            cin >> ch;
            system("cls");
            if (ch == 'e' || ch == 'E')
            {
                cout << "Lutfen yeni bir hesap no girin\n";
                cin >> secilenhesapno;
                system("cls");
            }
            else
            {
                break;
            }
        }


        return 0;//bulunamadı demek zaten hesaplar h[1]den tutulmaya baslıyor
    }


}h[100];

int main()
{
    system("color BD");
    cout << "Borsa baslatiliyor...\n";//borsa yukleme ekranı
    cout << "\t\t\t\t]";
    cout << "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b[";
    for (int i = 0;i < 31;i++)
    {

        cout << "$";
        Sleep(100);
    }

    system("cls");
    t.tarihal();
    t.okrpicindususgunleri();//ilk ay'a ait rastgele düşecek gün değerlerimizi hesaplayalım

    int secim;//kullanıcının secimi
    int secilenhesapkacinci;//hesap no'u secilen bir hesabın kaçıncı indiste tutulduğunu söyler h[?]
    for (;;)
    {
        system("color E1");
        system("cls");//ana menümüz
        cout << "1) Genel Hesap Ac\n" << "2) Ozel Hesap Ac\n" << "3) Hesaba TL ekle\n" << "4) Hesaptan TL cek\n" << "5) TL'yi Kripto Paraya cevir\n" << "6) Kripto Parayi TL'ye cevir\n" << "7) Tarihi ilerlet\n" << "8) Listele\n";
        cout << "lutfen bir islem secin\n";
        cin >> secim;
        string secilenhesapno;//indisini öğrenmek istediğimiz hesabın hesapno'su
        system("cls");
        switch (secim)
        {
        case 1:
            kacıncıhesap++;//herseferinde 1 artırıyoruz ki sonraki sefere yeni hesap açsın
            h[kacıncıhesap].genelhesapac();
            break;
        case 2:
            kacıncıhesap++;
            h[kacıncıhesap].ozelhesapac();
            break;
        case 3:
            system("color AD");
            cout << "Para yatirmak istediginiz hesabin numarasini girin";
            cin >> secilenhesapno;
            secilenhesapkacinci = h[0].nogirilenhesapkacinci(secilenhesapno);//burada h[0]ın kıllanılmasının özel bir sebebi yok sadece acılan hesapın kacıncı sırada olduğunu bulmamıza yarıyor zaten h[1]den tutulmaya başlıyor hesaplar(yani h[?] demek)
            if (secilenhesapkacinci != 0)
                h[secilenhesapkacinci].parayatir();//aslında secilenhesapkacinci ile istediğimiz hesabı elde ediyoruz
            break;
        case 4:
            system("color CB");
            cout << "Para cekmek istediginiz hesabin numarasini girin";
            cin >> secilenhesapno;
            secilenhesapkacinci = h[0].nogirilenhesapkacinci(secilenhesapno);
            if (secilenhesapkacinci != 0)
                h[secilenhesapkacinci].parayacek();
            break;
        case 5:
            cout << "Alis yapacaginiz hesap numarasini girin";
            cin >> secilenhesapno;
            secilenhesapkacinci = h[0].nogirilenhesapkacinci(secilenhesapno);
            if (secilenhesapkacinci != 0 && h[secilenhesapkacinci].gethesaptur() == "genel hesap")
                h[secilenhesapkacinci].alkrpicin();
            else if (secilenhesapkacinci != 0 && h[secilenhesapkacinci].gethesaptur() == "ozel hesap")
                h[secilenhesapkacinci].alokrpicin();
            break;
        case 6:
            cout << "Satis yapacaginiz hesap numarasini girin";
            cin >> secilenhesapno;
            secilenhesapkacinci = h[0].nogirilenhesapkacinci(secilenhesapno);
            if (secilenhesapkacinci != 0 && h[secilenhesapkacinci].gethesaptur() == "genel hesap")
                h[secilenhesapkacinci].satkrpicin();
            else if (secilenhesapkacinci != 0 && h[secilenhesapkacinci].gethesaptur() == "ozel hesap")
                h[secilenhesapkacinci].satokrpicin();
            break;
        case 7:
            t.gettarih();
            t.tarihdegisimi();//tarihi ilerletir
            break;
        case 8:
            for (int sayac = 1;sayac <= kacıncıhesap;sayac++)//en son açılan hesabın indisine kadar dönüyor
            {
                h[sayac].bakiye();
            }
            cout << "\nana menuye donmek icin herhangi bir tusa basin";
            _getch();
            break;



        }
    }




}

