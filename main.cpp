#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <iomanip>
using namespace std;


const double katsayi = 0.8;
const int iterasyon = 3000;

int mevcutDurum;

int main(){

	ifstream oku;//DOSYA OKUMAK ÝÇÝN NESNE

	oku.open("input44.txt");//DOSYAYI AÇMA

	string line ;

	int boyut = -1;

	int baslangic,hedef;

	cout<<"Baslangic Odacik Numarasini Giriniz:";
	cin>>baslangic;

	int ilk = baslangic;

	cout<<"Hedef Odacik Numarasini Giriniz:";
	cin>>hedef;

//BOYUT HESAPLAMA
	while(oku){
		getline(oku , line);
		boyut ++;
	}

	oku.clear();

	oku.seekg(0 , ios::beg);//IMLECI DOSYANIN BAÞINA GETÝR

	int R[boyut][boyut];

	int index[boyut ][boyut ];

	for(int i = 0 ; i < boyut ; i++){
		for(int j = 0 ; j < boyut ; j ++){

			index[i][j] = -1;
			R[i][j]=-1;
		}
	}

	int sayi;

	int z=0 ,t=0;

	while(oku){

		if(oku.peek() == ',')
			oku.ignore();

		if(oku.peek() == '\n'){

			z ++;
			t = 0;

		}

		oku>>sayi;

		index[z][t] = sayi;

		t++;

	}


	for(int i = 0 ; i < boyut ; i++){
		for(int j = 0 ; j < boyut ; j ++){

			if(index[i][j] != -1)
				R[i][index[i][j]] = 0;

			if(index[i][j] == hedef)
				R[i][index[i][j]] = 100;

			if(i == hedef && j == hedef )
				R[i][j] = 100;
		}
	}


	cout<< "R Matrisi :"<<endl<<endl;

	for(int i = 0 ; i < boyut ; i++){
		for(int j = 0 ; j < boyut ; j ++){

			cout << setw(5) << R[i][j];
			if(j < boyut - 1)
				cout << ",";

		}
	cout<<endl;
	}

//// Q MATRÝSÝ
	int Q[boyut][boyut];

	int yeniDurum;

	srand((unsigned)time(0));

    for(int i = 0; i < boyut ; i++){
        for(int j = 0; j < boyut ; j++){
            Q[i][j] = 0;
		}
	}

    for(int j = 0; j < iterasyon ; j++){

				mevcutDurum = ilk;

				while(mevcutDurum == hedef){
			        int sonrakiDurum;

					int rastgele;
					bool secim = false;
					int aralik = boyut + 1;


				   while(secim == false)  {

				        rastgele = int(aralik * rand() / (RAND_MAX + 1.0));
						if(R[mevcutDurum][rastgele] > -1)
				            secim = true;

					}


					sonrakiDurum =  rastgele;


					if(R[mevcutDurum][sonrakiDurum] >= 0){

						int secilen;
						bool bul;
						bool secildi = false;

					    secilen = 0;

						while(secildi == false){
					        bul = false;
					        for(int i = 0; i < boyut ; i++){
								if((i < secilen) || (i > secilen)){
									if(Q[sonrakiDurum][i] > Q[sonrakiDurum][secilen]){
					                    secilen = i;
					                    bul = true;
									}
								}
							}

							if(bul == false)
					            secildi = true;


					    }

						Q[mevcutDurum][sonrakiDurum] = 	R[mevcutDurum][sonrakiDurum] + (katsayi * Q[sonrakiDurum][secilen]);
				        mevcutDurum = sonrakiDurum;
					}
				}


			    for(int i = 0; i < boyut ; i++){
			        int sonrakiDurum;


				    int rastgele;
					bool secim = false;
					int aralik = (boyut - 0) + 1;


				    while(secim == false){

				        rastgele = int(aralik * rand() / (RAND_MAX + 1.0));
						if(R[mevcutDurum][rastgele] > -1)
				            secim = true;

				    }

				    sonrakiDurum =  rastgele;

					if(R[mevcutDurum][sonrakiDurum] >= 0){

												int secilen;
						bool bul;
						bool secildi = false;

					    secilen = 0;

						while(secildi == false){
					        bul = false;
					        for(int i = 0; i < boyut ; i++){
								if((i < secilen) || (i > secilen)){
									if(Q[sonrakiDurum][i] > Q[sonrakiDurum][secilen]){
					                    secilen = i;
					                    bul = true;
									}
								}
							}

							if(bul == false)
					            secildi = true;


					    }

						Q[mevcutDurum][sonrakiDurum] = 	R[mevcutDurum][sonrakiDurum] + (katsayi * Q[sonrakiDurum][secilen]);
				        mevcutDurum = sonrakiDurum;
				 }
			}
	}


	cout<<endl<<endl;

	cout<<"Q Matrisi:"<<endl<<endl;

	for(int i = 0; i < boyut ; i++){
        for(int j = 0; j < boyut ; j++){
            cout << setw(5) << Q[i][j];
			if(j < boyut - 1){
				cout << ",";
			}
		}
        cout << endl;
	}
    cout << endl;

	ofstream yaz1,yaz2;

	FILE * dosya =fopen("OutPath.txt","w");

     mevcutDurum = ilk;

	yeniDurum = 0;


		cout<< "Gidis Yolu : ";
		fprintf(dosya,"Gidis Yolu : ");

	while(mevcutDurum < hedef) {

	int secilen;
	bool bul;
	bool secildi = false;

    secilen = 0;


	while(secildi == false) {

		bul = false;

		for(int i = 0; i < boyut ; i++){
			if((i < secilen) || (i > secilen)){
				if(Q[mevcutDurum][i] > Q[mevcutDurum][secilen]){
                    secilen = i;
                    bul = true;
				}
			}
		}

		if(bul == false)
            secildi = true;


	 }

		yeniDurum = secilen;

		fprintf(dosya,"%d , ",mevcutDurum);
		 cout << mevcutDurum << ", ";
        mevcutDurum = yeniDurum;

	    }
        cout << hedef << endl;
        fprintf(dosya,"%d",hedef);


	fclose(dosya);
    oku.close();

	yaz1.open("OutR.txt");

    for(int i = 0 ; i < boyut ; i++){
		for(int j = 0 ; j < boyut ; j ++){

			yaz1<<R[i][j] << " ";

		}
	yaz1<<endl;
	}


	cout<<endl<<"OutR.txt dosyasi olusturuldu"<<endl;


	yaz2.open("OutQ.txt");


   	for(int i = 0 ; i < boyut ; i++){
		for(int j = 0 ; j < boyut ; j ++){

			yaz2<<Q[i][j] << " ";

		}
	yaz2<<endl;
	}

yaz1.close();
yaz2.close();

	 cout<<endl<<"OutQ.txt dosyasi olusturuldu"<<endl<<endl;

	cout<<"Programi sonlandirip olusan dosyalari silmek icin ENTER a basin /n";

	cin.get();
	cin.get();

	cout<<"Dosyalar Silindi"<<endl<<endl;


	system("del OutR.txt");
	system("del OutQ.txt");
system("del OutPath.txt");
	cout<<endl;

	return 0;
}
