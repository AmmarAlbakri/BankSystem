/* Object Orinted Programming
	Odev 2 by Ammar Albakri-160504100*/
#include<iostream>
#include<string>	
#include<iomanip>	//for setw method
#include<fstream>	//for reading data from file
#include<sstream>	//used in convering from string to int
using namespace std;
int convert(string &str){	//for converting string to int
	int num;
	stringstream ss;
	ss<<str;
	ss>>num;
	return num;
}
class Musteri {
	protected:
		int ID,tuketim_miktari,izin_verilen_kota;
		string Ad,Soyad;
	public: 
		Musteri(int id,string ad,string soyad,int miktar,int kota){
			ID=id;
			tuketim_miktari=miktar;
			izin_verilen_kota=kota;
			Ad=ad;
			Soyad=soyad;}
		float kalani_hesapla(){	return izin_verilen_kota-tuketim_miktari;}	//calculate the remaining balance
		virtual void yazdir()=0;	//pure virtual function for printing
		virtual string musteri_tipini_getir()=0;	//pure virtual function for retriving customer type
};
class Bireysel:public Musteri{
	private :
		string opsiyon_kodu;	//individual account type
	public:
		Bireysel(int id,string ad,string soyad,int miktar,int kota):Musteri( id, ad, soyad, miktar, kota){
			if(kota==100) //deciding customer type based on his allowenss
				opsiyon_kodu="IT";
			else if(kota==400)
				opsiyon_kodu="IN";
			else
				opsiyon_kodu="IP";
		}
		void yazdir(){	//printing customer information in a formatted style
			cout<<left<<setw(8)<<ID<<setw(12)<<Ad<<setw(12)<<Soyad<<setw(10)<<kalani_hesapla()<<endl;
		}
		string musteri_tipini_getir(){return opsiyon_kodu;}
};
class Kurumsal:public Musteri{
	private :
		string kurum_adi;	//company name
	public:
		Kurumsal(int id,string ad,string soyad,int miktar,int kota,string k_adi):Musteri( id, ad, soyad, miktar, kota),kurum_adi(k_adi){
			}
		string musteri_tipini_getir(){return "S";}
		void yazdir(){
				cout<<left<<setw(8)<<ID<<setw(12)<<Ad<<setw(12)<<Soyad<<setw(15)<<kurum_adi<<setw(10)<<kalani_hesapla()<<endl;
			}
};
int main(){
	int id,miktar,kota,i=0,j,k,flag=0;	//i,j,k counters, flag used for a decision making
	string ad,soyad,k_adi,tip,temp;		//temporary variables to be read from the file and into the object
	Musteri *p[200];	//200 pointer that will point to subclass's of Musteri
	string s("S"),ip("IP"),it("IT"),in("IN");	//types of accounts
	ifstream file;	//file to read data from
	file.open("MUSTERILER.TXT");
	if(file.is_open()){	//making sure the file opened properly
		while(!file.eof()){	//until file is over do the following
			flag=0;	//the customer type is Kurumsal until otherwise is specified
			for(j=0;j<6;j++){	//loop 6 for institutional or 5 for individual times in line 
			file>>temp;	//read one word from file 
			switch(j){	//detirmine which word has been read and act accordingly 
				case 0:tip=temp;break;	//first word (type)
				case 1:id=convert(temp);break;	//second word(id)
				case 2:ad=temp;break;	//third word(name)
				case 3:soyad=temp;break;	//fourth word(surname)
				case 4:miktar=convert(temp);	//fifth word(left balance)
						if(tip.compare(s)!=0){	//if customer type is not institutional
						j++;flag=1;			//skip to next line and rise the flag
						}
						break;
				case 5:k_adi=temp;break;	//if didn't skip in previous step then read the institutione name
				}
			}
			if(flag==1){	//if flag is risen make an indivisual accounnt
					if(tip.compare(it)==0)	//detirmine allowenss according to account type
						kota=100;
					else if(tip.compare(ip)==0)
						kota=2000;
					else if(tip.compare(in)==0)
						kota=400;
			    	p[i]=new Bireysel(id,ad,soyad,miktar,kota);
			}
			else{	//if flag is not risen then make an institutional account
				p[i]=new Kurumsal(id,ad,soyad,miktar,5000,k_adi);
			}
			i++;	// move to next pointer
		}//end of while
	}//end of if
	for(j=0;j<4;j++){	//printing the information in order of 4 category
		switch(j){
			case 0:temp=s;
					cout<<"Kurumsal Musteri Listesi:"<<endl<<endl;
					cout<<left<<setw(8)<<"ID"<<setw(12)<<"Ad"<<setw(12)<<"Soyad"<<setw(15)<<"Kurum Adi"<<setw(10)<<"Kalan Miktar"<<endl;break;
			case 1:temp=it;
					cout<<"Bireysel Deneme Musteri Listesi:"<<endl<<endl;
					cout<<left<<setw(8)<<"ID"<<setw(12)<<"Ad"<<setw(12)<<"Soyad"<<setw(10)<<"Kalan Miktar"<<endl;break;
			case 2:temp=in;
					cout<<"Bireysel Normal Musteri Listesi:"<<endl<<endl;
					cout<<left<<setw(8)<<"ID"<<setw(12)<<"Ad"<<setw(12)<<"Soyad"<<setw(10)<<"Kalan Miktar"<<endl;break;
			case 3:temp=ip;
					cout<<"Bireysel Premium Musteri Listesi:"<<endl<<endl;
					cout<<left<<setw(8)<<"ID"<<setw(12)<<"Ad"<<setw(12)<<"Soyad"<<setw(10)<<"Kalan Miktar"<<endl;break;
		}
		for(k=0;k<i-1;k++){	//printing customer information based on their type
		    tip=p[k]->musteri_tipini_getir();	//getting the type
			if(tip.compare(temp)==0)	//if type match the wanted category
				p[k]->yazdir();	//print
		}
		cout<<"................................................."<<endl;	//seperate categorys for a better view
	}
	file.close();		//close the file
	return 0;
}

