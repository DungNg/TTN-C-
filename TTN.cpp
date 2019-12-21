#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <windows.h>
#include "mylib.h"
#include <iomanip>
#include <time.h>
using namespace std;

const int so_item = 9;
const int dong =2;
const int cot = 10 ;
const int Up = 72;
const int Down = 80;

const int MAXLIST = 500;
const int MAXQ = 2000;
const int MAXSV = 50;
static int STT = 1;

const int KEY_ARROW_CHAR1 = 224;
const int KEY_ARROW_UP = 72;
//const int KEY_ARROW_DOWN = 80;
const int KEY_ARROW_LEFT = 75;
const int KEY_ARROW_RIGHT = 77;

string where ="D:\\Projects\\Cpp\\TTN\\data\\";
char filelop[80]="D:\\Projects\\Cpp\\TTN\\data\\dslop.txt";
//char filesv[80]="D:\\dssinhvien.txt";
char filemh[80]="D:\\Projects\\Cpp\\TTN\\data\\dsmonhoc.txt";
char filech[80]="D:\\Projects\\Cpp\\TTN\\data\\dscauhoi.txt";
char fileid[80]="D:\\Projects\\Cpp\\TTN\\data\\dsid.txt";
//--So ngau nhien
struct SNN{
	int n; // so phan tu trong mang
	int nodes[MAXQ+1];
};

//--End So ngau nhien

//--MonHoc "Cay nhi phan tim kiem"
struct MonHoc 
{
	char MAMH[15];
	char TENMH[50];
};
struct nodeMH{
	MonHoc data;
	nodeMH *left;
	nodeMH *right;
};
typedef struct nodeMH *Tree;
//--End MonHoc

//--CauHoiThi "Mang con tro"
struct CauHoi
{
	int id;
	char MAMH[15];
	char NOIDUNG[MAXQ];
	char A[MAXQ];
	char B[MAXQ];
	char C[MAXQ];
	char D[MAXQ];
	char DAPAN[2];
	char CHON[2];
};

struct DsCauHoi{ 
	int n;
	CauHoi *DS[MAXQ];
};
//--End CauHoiThi

//--DiemThi "Dslk don"
struct DiemThi 
{
	char MAMH[15];
	float DIEM;
	//DsCauHoi CT; //chi tiet bai thi
};
struct nodeDT{
	DiemThi data;
	nodeDT *next;
};
typedef struct nodeDT *DT_PTR;
//--End DiemThi

//--SinhVien "Dslk don"
struct SinhVien 
{
	char MASV[15];
	char HO[50];
	char TEN[10];
	char PHAI[4];
	char password[15];
	DT_PTR DT; //ds diem cac mon da thi
};
struct nodeSV{
	SinhVien data;
	nodeSV *next;
};
typedef struct nodeSV *SV_PTR;

//--End SinhVien

//--Lop  "Mang con tro"
struct Lop 
{
	char MALOP[15];
	char TENLOP[50];
	SV_PTR DSSV; //ds sinh vien thuoc lop
};

struct DsLop 
{
	int n;
	Lop *node[MAXLIST];
};
//--End Lop

char thucdon [so_item][50] = {
							  "1.   Nhap lop",
			                  "2.   In danh sach lop",
			                  "3.   Nhap sinh vien",
			                  "4.   Quan ly mon hoc",
			                  "5.   Nhap cau hoi thi",
			                  "6.   Thi trac nghiem",
			                  "7.   In chi tiet cac cau hoi da thi cua sinh vien",
							  "8.   In bang diem thi trac nghiem mon hoc cua lop",
							  "9.   Ket thuc chuong trinh"};
char quanly[so_item][50]={		"1.  Them",
					 			"2.  Sua",
								"3.  Xoa",
					 			"4.  Liet ke",
					 			"5.  Thoat",
					 			"","","",""};			                  
void Normal () {
	SetColor(15);
	SetBGColor(0);
}
void HighLight () {
	SetColor(15);
	SetBGColor(1);
}
int MenuDong(char td [so_item][50]){
  Normal();
  system("cls");   int chon =0;
  int i; 
  for ( i=0; i< so_item ; i++)
  { 
  	gotoxy(cot, dong +i);
    cout << td[i];
  }
  HighLight();
  gotoxy(cot,dong+chon);
  cout << td[chon];
  char kytu;
do {
  kytu = getch();
  if (kytu==0) kytu = getch();
  switch (kytu) {
    case Up :if (chon+1 >1)
  			  {
  		              	Normal();
              	gotoxy(cot,dong+chon);
              	cout << td[chon];
              	chon --;
              	HighLight();
              	gotoxy(cot,dong+chon);
              	cout << td[chon];
  				
  			  }
  			  break;
  	case Down :if (chon+1 <so_item)
  			  {
  		        Normal();
              	gotoxy(cot,dong+chon);
              	cout << td[chon];
              	chon ++;
              	HighLight();
              	gotoxy(cot,dong+chon);
              	cout << td[chon];
  				
  			  }
  			  break;
  	case 13 : return chon+1;
  	}  // end switch
  } while (1);
}	
void BaoLoi (char *s){
  int x=wherex() , y=wherey();
  gotoxy (10,24);
  cout <<s;
  Sleep(1500);
  gotoxy(10,24);
  clreol();
  gotoxy(x,y);
}

void NhapChuoi (char *tieude, char *S) {
	cout << tieude ;  
	fflush(stdin);
    do
	  gets(S);
    while (strcmp(S,"")==0)  ;
    strupr(S);
}

bool IsNumber(char * s) 
{ 
    for (int i = 0; i < strlen(s); i++) 
        if (isdigit(s[i]) == false) 
            return false; 
  
    return true; 
} 

int SearchLop(DsLop ds,char *x)
{
	for(int i=0;i<ds.n;i++)
	{
		if(strcmp(ds.node[i]->MALOP,x)==0)
		return i;
	}
	return -1;
}

SV_PTR SearchSV(DsLop &ds,char *x)
{
	for(int i=0;i<ds.n;i++)
	{
		SV_PTR p = ds.node[i]->DSSV;
		for(p;p!=NULL;p=p->next)
		{
			if(strcmp(p->data.MASV,x)==0)
			{
				return p; //tra ve vi tri cua lop
			}
		}
	}
	return NULL;
}

int SearchMh(Tree &t,char *mamh)
{
	 if(t==NULL)
	 {
	 	return 1;
	 }else{
	 	if(strcmp(mamh,t->data.MAMH)<0)
	 	{
	 		SearchMh(t->left,mamh);
		}
		else if(strcmp(mamh,t->data.MAMH)>0)
		{
			SearchMh(t->right,mamh);
		}else{
			return 0;
		}
	 }
}

DT_PTR SearchCT(DsLop &dslop,char *masv,char *mamh)
{
	SV_PTR sv = SearchSV(dslop,masv);
	DT_PTR dt = sv->data.DT;
	for(dt;dt!=NULL;dt=dt->next)
	{
		if(strcmp(dt->data.MAMH,mamh)==0)
		{
			return dt;
		}
	}
	return NULL; //sinh vien chua thi mon hoc nay
}

void NhapMh(Tree &t,MonHoc mh)
{	
	if(t==NULL)
	{
		nodeMH *p = new nodeMH;
		p->data = mh;
		p->left = NULL;
		p->right = NULL;
		t=p;
	}else {
		if(strcmp(mh.MAMH,t->data.MAMH)<0)
		{
			NhapMh(t->left,mh);
		}
		
		if(strcmp(mh.MAMH,t->data.MAMH)>0)
		{
			NhapMh(t->right,mh);
		}	
	}
}

void NhapDsMh (Tree &t)
{
	while(1)
	{
		MonHoc mh;
		NhapChuoi("Ma mon hoc (0 la ket thuc): ",mh.MAMH);
		if(strcmp(mh.MAMH,"0")==0) return;
		if(SearchMh(t,mh.MAMH)==0){
			BaoLoi("Ma mon hoc bi trung");
			continue;
		}else{
			NhapChuoi("Ten mon hoc: ",mh.TENMH);
			NhapMh(t,mh);
		}
		
	}
}
void SaveDiem(DT_PTR p,char *msv);
void NhapDiem(DT_PTR &First,nodeDT dt,char *masv)
{
	dt.next=NULL;
	DT_PTR p;
	p = new nodeDT;
	*p=dt;		
   	if (First==NULL)   First = p;
   	else
   	{ 
   		DT_PTR Last= First;
     	for ( ; Last->next !=NULL ; Last=Last->next) ;
     	Last->next=p;
   	}
   	SaveDiem(First,masv);
}

void NhapSv(SV_PTR &First,nodeSV sv)
{	
	sv.data.DT = NULL;
	sv.next=NULL;
	SV_PTR p;
	p = new nodeSV;
	*p=sv;		
   	if (First==NULL)   First = p;
   	else
   	{ 
   		SV_PTR Last= First;
     	for ( ; Last->next !=NULL ; Last=Last->next) ;
     	Last->next=p;
   	}
}
void SaveSv(SV_PTR p,char* malop);
void NhapDsSv(DsLop &ds)
{
	char malop[15];
	SV_PTR p;
	NhapChuoi("Ma lop: ",malop);
	int stt = SearchLop(ds,malop);
	if(stt>=0)
	{
		while(1)
		{
			p = new nodeSV;
  			NhapChuoi("Ma sinh vien(0 la ket thuc): ",p->data.MASV);
  			if(strcmp(p->data.MASV,"0") == 0 ) break;
  			if(SearchSV(ds,p->data.MASV)!=NULL) 
  			{
  				BaoLoi("Ma sinh vien bi trung") ;
  				delete p;
				continue;
			}			
   			NhapChuoi("Ho: ",p->data.HO);
   			NhapChuoi("Ten: ",p->data.TEN);
   			do{
				NhapChuoi("Phai(Nam/Nu): ",p->data.PHAI);
			}while(strcmp(p->data.PHAI,"NAM")!=0&&strcmp(p->data.PHAI,"NU")!=0);
   			strcpy(p->data.password,"123");
   			//p->data.DT = NULL;
   			//p->next = NULL;
   			NhapSv(ds.node[stt]->DSSV,*p);
		}
	}else{
		BaoLoi("Lop khong ton tai");
		return;
	}
	//string ml(malop);
	SaveSv(ds.node[stt]->DSSV,malop);
}

int NhapLop(DsLop &ds,Lop &lop)
{
	lop.DSSV=NULL;
   	ds.node[ds.n]=new Lop;
   	*ds.node[ds.n]=lop;
   	ds.n++;	
}

void NhapDsLop (DsLop &ds, int flag){
 Lop lop;
 if(flag==0)
 {
 	while(ds.n>0)
 	{
 		delete ds.node[ds.n-1];
		ds.n--;	
	}
 }
 while (ds.n<MAXLIST)
 { 
 		NhapChuoi("Nhap ma lop(0 la ket thuc): ",lop.MALOP);	
		if(strcmp(lop.MALOP,"0")==0) return;
		if(SearchLop(ds,lop.MALOP)>=0)
		{
			BaoLoi("Ma lop bi trung");
			continue;
		}
		NhapChuoi("Nhap ten lop: ",lop.TENLOP);
		//lop.DSSV = NULL;
		NhapLop(ds,lop);
 }
 
 if (ds.n==MAXLIST) BaoLoi ("Danh sach day");
}

void NhapCauHoi (DsCauHoi &ds,CauHoi ch){
	int j, k;
	for (j=0; j < ds.n && strcmp(ds.DS[j]->MAMH,ch.MAMH) != 0 ; j++ );
	for ( k = ds.n-1; k >=j  ; k--) ds.DS[k+1]= ds.DS[k];
	ds.DS[j] = new CauHoi;
	*ds.DS[j]= ch; 
	ds.n++;
}

void NhapChiTiet (DsCauHoi &dich,DsCauHoi &nguon){
	dich.n=0;
	for(int i=0;i<nguon.n;i++)
	{
		dich.DS[i] = new CauHoi;
 	    *dich.DS[i]=*nguon.DS[i]; 
	    dich.n++;
	    //cout<<nguon.DS[i]->id<<endl;
	}
	//getch();
}

void NhapDsCauHoi(DsCauHoi &ds,SNN &snn,Tree &t)
{
	if(ds.n<MAXQ)
	{
		int j,k;
		CauHoi ch;		
		while(1)
		{
			NhapChuoi("Nhap ma mon hoc(0 la ket thuc): ",ch.MAMH);
			if(strcmp(ch.MAMH,"0")==0) return;
			if(SearchMh(t,ch.MAMH)!=0) 
			{
				BaoLoi("Mon hoc khong ton tai");
				continue;
			}
			break;
		}
		while(1)
		{
			ch.id=snn.nodes[ds.n+1];
			NhapChuoi("Nhap noi dung(0 la ket thuc): ",ch.NOIDUNG);
			if(strcmp(ch.NOIDUNG,"0")==0) return;
			NhapChuoi("Cau A: ",ch.A);
			NhapChuoi("Cau B: ",ch.B);
			NhapChuoi("Cau C: ",ch.C);
			NhapChuoi("Cau D: ",ch.D);
			do{
				NhapChuoi("Dap an (A,B,C,D): ",ch.DAPAN);
			}while(strcmp(ch.DAPAN,"A")!=0&&strcmp(ch.DAPAN,"B")!=0&&strcmp(ch.DAPAN,"C")!=0&&strcmp(ch.DAPAN,"D")!=0);
			NhapCauHoi(ds,ch);
		}
	}else{
		BaoLoi("Danh sach day");
		return;
	}
}

void TimNodeThayThe(Tree &X,Tree &Y)
{
	if(Y->left!=NULL)
	{
		TimNodeThayThe(X,Y->left);
	}else{
		X->data = Y->data;
		X=Y;
		Y=Y->right;
	}
}

void SuaMh(Tree &t, char*mamh)
{
	if(t!=NULL)
	{
		if(strcmp(mamh,t->data.MAMH)<0)
		{
			SuaMh(t->left,mamh);
		}
		if(strcmp(mamh,t->data.MAMH)>0)
		{
			SuaMh(t->right,mamh);
		}
		if(strcmp(mamh,t->data.MAMH)==0)
		{
			cout<<"Ten mon hoc cu: "<<t->data.TENMH<<endl;
			NhapChuoi("Ten mon hoc moi: ",t->data.TENMH);
		}
	}
}
void XoaMh(Tree &t,char *mh,DsCauHoi dsch)
{
	for(int i=0;i<dsch.n;i++)
	{
		if(strcmp(dsch.DS[i]->MAMH,mh)==0)
		{
			BaoLoi("Khong the xoa mon hoc");
			return;
		}
	}
	if(t!=NULL)
	{
		if(strcmp(mh,t->data.MAMH)<0)
		{
			XoaMh(t->left,mh,dsch);
		}
		if(strcmp(mh,t->data.MAMH)>0)
		{
			XoaMh(t->right,mh,dsch);
		}
		if(strcmp(mh,t->data.MAMH)==0)
		{
			nodeMH *X = t;
			 if(t->left==NULL)
			 {
			 	t=t->right;
			 }
			 else if(t->right==NULL)
			 {
			 	t=t->left;
			 }
			 else
			 {
			 	TimNodeThayThe(X,X->right);
			 }
			 delete X;
		}
	}
}

void InDsCh(DsCauHoi &ds)
{
	for(int i=0;i<ds.n;i++)
	{
		cout<<ds.DS[i]->MAMH<<"	"<<ds.DS[i]->id<<"	"<<ds.DS[i]->NOIDUNG<<"	"<<ds.DS[i]->A<<"	"<<ds.DS[i]->B<<"	"<<ds.DS[i]->C<<"	"<<ds.DS[i]->D<<"	"<<ds.DS[i]->DAPAN<<endl;
	}
	getch();
}

void InDsMh(Tree &t)
{
	 if(t!=NULL)
	 {
	 	cout<<STT<<setw(15)<<t->data.MAMH<<setw(20)<<t->data.TENMH<<endl;
	 	STT++;
		InDsMh(t->left);
		InDsMh(t->right);
	 }
}

void InDsSv(SV_PTR &First)
{
	SV_PTR p = First;	
	cout<<"============================================================"<<endl;
	if(p!=NULL)
	{
		cout<<setw(10)<<"STT"<<setw(15)<<"MASV"<<setw(20)<<"HO va TEN"<<setw(30)<<"PHAI"<<endl;
		for(p;p!=NULL;p=p->next)
		{
			cout<<setw(10)<<STT<<setw(15)<<p->data.MASV<<setw(20)<<p->data.HO<<" "<<p->data.TEN<<setw(30)<<p->data.PHAI<<endl;
			STT++;
		}
	}
	cout<<"============================================================"<<endl;;
	STT=1;
}

void InDsLop(DsLop &ds) 
{
	cout<<setw(25)<<"DANH SACH LOP"<<endl;
	cout<<"STT"<<setw(15)<<"MA LOP"<<setw(20)<<"TEN LOP"<<endl;
	if(ds.n==0){
		BaoLoi("Danh sach rong");
	}
	for(int i=0;i<ds.n;i++)
	{
		cout<<i+1<<setw(15)<<ds.node[i]->MALOP<<setw(30)<<ds.node[i]->TENLOP<<endl;
		InDsSv(ds.node[i]->DSSV);	
	}
	getch();
}

void InBangDiem(DsLop ds,char *malop,char *mh)
{
	SV_PTR p;
	DT_PTR d;
	int x;
	system("cls");
		cout<<"Ma lop: "<<malop<<"	"<<"Ma mon hoc: "<<mh<<endl;
		cout<<endl;
	int i = SearchLop(ds,malop);
	if(i>=0)
	{
		for(p=ds.node[i]->DSSV;p!=NULL;p=p->next)
		{
			if(p->data.DT==NULL)
			{
				cout<<p->data.MASV<<"	"<<p->data.HO<<" "<<p->data.TEN<<"	"<<p->data.PHAI<<"	"<<"Chua thi"<<endl;
			}else{
				for(d=p->data.DT;d!=NULL;d=d->next)
				{
					//cout<<p->data.MASV<<"	"<<p->data.HO<<" "<<p->data.TEN<<"	"<<p->data.PHAI<<"	"<<d->data.DIEM<<endl;
					x = strcmp(d->data.MAMH,mh);
					if(x==0)
					{
						cout<<p->data.MASV<<"	"<<p->data.HO<<" "<<p->data.TEN<<"	"<<p->data.PHAI<<"	"<<d->data.DIEM<<endl;
						break;
					}else if(d->next==NULL&&x!=0)
					{
						cout<<p->data.MASV<<"	"<<p->data.HO<<" "<<p->data.TEN<<"	"<<p->data.PHAI<<"	"<<"Chua thi"<<endl;
					}
				}	
			}
			
		}
	}else{
		BaoLoi("Ma lop khong ton tai");
		return;
	}
	getch();
}

void InDsCT(DsCauHoi ds,char* masv,char* mamh)
{
	system("cls");
	if(ds.n<=0)
	{
		BaoLoi("Chi tiet rong");
		return;
	}else{
		cout<<"Ma sinh vien: "<<masv<<"	"<<"Ma mon hoc: "<<mamh<<endl;
		
		for(int i=0;i<ds.n;i++)
		{
			cout<<endl;
			cout<<"Cau "<<STT<<": "<<ds.DS[i]->NOIDUNG<<endl;
			cout<<"Cau A: "<<ds.DS[i]->A<<endl;
			cout<<"Cau B: "<<ds.DS[i]->B<<endl;
			cout<<"Cau C: "<<ds.DS[i]->C<<endl;
			cout<<"Cau D: "<<ds.DS[i]->D<<endl;
			cout<<"DAPAN: "<<ds.DS[i]->DAPAN<<endl;
			cout<<"CHON: "<<ds.DS[i]->CHON<<endl;
			STT++;
		}
	}
	STT=1;
	getch();
}

void Swap(int &a,int&b)
{
	int temp = a; a=b; b=temp;
}
void SaveSNN(SNN ds,char *filename);
void TaoDayNN (SNN &ds, int N , int max){

	int sonn ;
 	ds.n=0;
	int dem = 1; srand(time(NULL));
	for (int i=1; i<=max ; i++) 
	{
		ds.nodes [i]=i;
		ds.n++;
	}
	while (dem <= N) {
		sonn = dem+rand() % (max-dem + 1);
		swap(ds.nodes [dem], ds.nodes [sonn]);
		dem++;
  	}	
}

void TaoDayNN2 (SNN &ds, int N , int max,int min){
	int sonn ;
 	ds.n=0;
	int dem = 0; srand(time(NULL));

	for (int i=0; i<=max-min ; i++) 
	{
		ds.nodes [i]=min+i;
		ds.n++;
	}
	//max=max-1;
	while (dem <= N-min) {
		sonn = dem+rand() % ((max-min)-dem+1);
		swap(ds.nodes [dem], ds.nodes [sonn]);
		dem++;
   	}
}

int ViTriCauHoiDauTien(DsCauHoi &ds, char *mamh)
{
	int i;
	for(i=0;i<ds.n;i++)
	{
		if(strcmp(ds.DS[i]->MAMH,mamh)==0)
		{
			return i;
		}
	}
	return 0;
}

int ViTriCauHoiKetThuc(DsCauHoi &ds, char *mamh)
{
	int j;
	for(j=ds.n-1;j>=0;j--)
	{
		if(strcmp(ds.DS[j]->MAMH,mamh)==0)
		{
			return j;
		}
	}
	return -1;
}

int DemCauHoi(DsCauHoi &ds, char *mamh)
{
	int start,end;
	start = ViTriCauHoiDauTien(ds,mamh); //vi tri bat dau
	end = ViTriCauHoiKetThuc(ds,mamh);
	if(end == start)
	{
		return 1;
	}
	return end-start+1;
}

DsCauHoi LayDeThi(DsCauHoi &ds,char *mamh,int socauhoi)
{
	DsCauHoi bode;
	bode.n=0;
	SNN snn;	
	int min,max;
	snn.n=0;
	min = ViTriCauHoiDauTien(ds,mamh);
	max = ViTriCauHoiKetThuc(ds,mamh);
	TaoDayNN2(snn,max,max,min);
	for(int i=0;i<socauhoi;i++)
	{
		bode.DS[i] = ds.DS[snn.nodes[i]];
		bode.n++;
	}
	return bode;
}
SinhVien sinhvien_; //sinh vien da dang nhap

int CheckThi(DT_PTR dt,char * mh) //check mon hoc da thi chua
{
	for(dt;dt!=NULL;dt=dt->next)
	{
		if(strcmp(dt->data.MAMH,mh)==0)
		{
			return 1;
		}
	}
	return 0;
}



/*void XuLyCT(DsLop &dslop,char *masv,char *mamh,DsCauHoi &dsch)
{
	DT_PTR dt = SearchCT(dslop,masv,mamh);
	NhapChiTiet(dt->data.CT,dsch);
}*/
 void SaveCT(DsCauHoi ds,char *masv);
void Thi(DsCauHoi ds,int thoigianthi,int socauhoithi,DsLop &dslop,int status)
{	 
	nodeDT dt; //luu chi tiet bai thi
	int batdau,ketthuc,hientai,dem=0;
	double diem=0,diemmoicau;
	diemmoicau = (float)10 / socauhoithi;
	batdau = time(NULL);
	ketthuc = batdau + (thoigianthi * 60);
	int i=0;
	while(hientai<ketthuc)
	{	
		system("cls");
		cout<<"Cau "<<i+1<<" :"<<endl;
		cout<<ds.DS[i]->NOIDUNG<<endl;
		cout<<"Cau A: "<<ds.DS[i]->A<<endl;
		cout<<"Cau B: "<<ds.DS[i]->B<<endl;
		cout<<"Cau C: "<<ds.DS[i]->C<<endl;
		cout<<"Cau D: "<<ds.DS[i]->D<<endl;
		if(strcmp(ds.DS[i]->CHON,"")==0)
		{
			NhapChuoi("Chon (A,B,C,D): ",ds.DS[i]->CHON);	
		}else{
			cout<<"Da chon: "<<ds.DS[i]->CHON<<endl;
		}
		hientai = time(NULL);
		if(i==socauhoithi-1)
		{
			int nopbai;
			cout<<"Nop bai? (1 de nop bai, 0 de xem tiep): ";
			cin>>nopbai;
			if(nopbai==1)
			{
				hientai = ketthuc;
				continue;
			}else{
				hientai=time(NULL);
			}	
		}	
		if(hientai>ketthuc) break;
		cout<<"<- Previous - Next -> (Bam mui ten UP de tra loi lai)"<<endl;
		unsigned char ch1 = _getch();
		if(ch1==KEY_ARROW_CHAR1)
		{
			unsigned char ch2 = _getch();
			switch (ch2) 
    		{
   				case KEY_ARROW_LEFT:
        			if(i>0)
        			{
        				i--;
					}
        			break;
    			case KEY_ARROW_RIGHT:
        			if(i<socauhoithi-1)
        			{
        				i++;
					}
        			break;
        		case KEY_ARROW_UP:
        			NhapChuoi("Chon (A,B,C,D): ",ds.DS[i]->CHON);
        			break;
    		}
		}
	
	}
	for(int i=0;i<socauhoithi;i++) //cham diem
	{
		if(strcmp(ds.DS[i]->CHON,ds.DS[i]->DAPAN)==0)
		{
			dem++;
		}
	}
	diem = dem * diemmoicau;
	
	if(status != 0) //sinh vien -> luu diem -> luu chi tiet
	{
		strcpy(dt.data.MAMH,ds.DS[0]->MAMH);
		dt.data.DIEM=diem;
	
		NhapDiem(sinhvien_.DT,dt,sinhvien_.MASV); // luu diem
		SaveCT(ds,sinhvien_.MASV);	
	}	
	
	cout<<"Diem: "<<fixed<<setprecision(2)<<diem<<endl;
	
	getch();
	
}

void ChuanBiThi(DsCauHoi &ds,Tree &t,DsLop &dslop,int status)
{
	system("cls");
	cout<<"THI TRAC NGHIEM"<<endl;
	char socauhoithi_[15],thoigianthi_[15];
	int socauhoithi,thoigianthi;
	char mamh[15];
	NhapChuoi("Nhap mon hoc(0 la ket thuc): ",mamh);
	if(strcmp(mamh,"0")==0)return;	
	if(SearchMh(t,mamh)!=0)
	{
		BaoLoi("Mon hoc khong ton tai");
		return;
	}
	if(CheckThi(sinhvien_.DT,mamh)==1)
	{
		BaoLoi("Sinh vien da thi mon hoc nay roi");
		return;
	}
	do{
		NhapChuoi("Nhap so cau hoi thi: ",socauhoithi_);
	}while(!IsNumber(socauhoithi_));
	socauhoithi = atoi(socauhoithi_);
	if(socauhoithi > DemCauHoi(ds,mamh))
	{
		BaoLoi("Mon hoc khong co du so cau hoi");
		return;
	}
	do{
		NhapChuoi("Nhap thoi gian thi(phut): ",thoigianthi_);
	}while(!IsNumber(thoigianthi_));
	thoigianthi = atoi(thoigianthi_);
	DsCauHoi bode = LayDeThi(ds,mamh,socauhoithi);
	Thi(bode,thoigianthi,socauhoithi,dslop,status);
}

//------------------------------------------------SAVE + OPEN-------------------------------------------

void SaveDiem(DT_PTR p,char *msv) {
 	FILE * f; DT_PTR dt;
 	string masv = msv;
	string filename =where+ "dsdiem" + masv +".txt"; 
 	
	char file[filename.size() + 1];
	strcpy(file,filename.c_str());
 	
	if ((f=fopen(file,"wb"))==NULL)
 	{ 
	 	BaoLoi ("Loi mo file Sinh vien de ghi"); return ;
	}

 	for (dt=p;dt!=NULL;dt=dt->next)
 	{
   		fwrite (&dt->data, sizeof (DiemThi), 1, f);
	}
	
 	fclose(f);
 //BaoLoi ("Da ghi xong danh sach vao file");
}

void OpenDiem(DT_PTR &p,char *msv) {
 	FILE * f; nodeDT dt;
 	string masv = msv;
 	string filename =where+ "dsdiem" + masv +".txt"; 
 	
	char file[filename.size() + 1];
	strcpy(file,filename.c_str());
	
 	if ((f=fopen(file,"rb"))==NULL)
 	{ 
	 	//BaoLoi ("Loi mo file Sinh vien de doc"); 
		 return ;
 	}
 	while  (fread (&dt.data, sizeof (DiemThi), 1, f)!=0)
	{
		NhapDiem(p,dt,msv);
	}	
 	fclose(f);
 //BaoLoi ("Da load xong danh sach vao bo nho");
}

void SaveSv(SV_PTR p,char* ml) {
 	FILE * f; SV_PTR sv;
 	string malop = ml;
	string filename = where+"dssinhvien" + malop +".txt"; 
 	
	char file[filename.size() + 1];
	strcpy(file,filename.c_str());
 	
	if ((f=fopen(file,"wb"))==NULL)
 	{ 
	 	BaoLoi ("Loi mo file Sinh vien de ghi"); return ;
	}

 	for (sv=p;sv!=NULL;sv=sv->next)
 	{
   		fwrite (&sv->data, sizeof (SinhVien), 1, f);
	}
	
 	fclose(f);
 //BaoLoi ("Da ghi xong danh sach vao file");
}

void OpenDiem_(SV_PTR &p)
{
	SV_PTR sv;
	for(sv=p;sv!=NULL;sv=sv->next)
	{
		OpenDiem(sv->data.DT,sv->data.MASV);
	}
}

void OpenSv(SV_PTR &p,char* ml) {
 	FILE * f; nodeSV sv;
 	string malop = ml;
 	string filename = where+"dssinhvien" + malop +".txt"; 
 	
	char file[filename.size() + 1];
	strcpy(file,filename.c_str());
	
 	if ((f=fopen(file,"rb"))==NULL)
 	{ 
	 	//BaoLoi ("Loi mo file Sinh vien de doc"); 
		 return ;
 	}
 	while  (fread (&sv.data, sizeof (SinhVien), 1, f)!=0)
	{
		NhapSv(p,sv);
	}
	OpenDiem_(p);
 	fclose(f);
 //BaoLoi ("Da load xong danh sach vao bo nho");
}

void SaveLop(DsLop ds,char *filename) {
 	FILE * f;
 	if ((f=fopen(filename,"wb"))==NULL)
 	{ 
	 	BaoLoi ("Loi mo file LOP de ghi"); return ;
	}
 	for (int i=0; i < ds.n; i++)
   		fwrite (ds.node[i], sizeof (Lop), 1, f);
 	fclose(f);
 //BaoLoi ("Da ghi xong danh sach vao file");
}

void OpenLop(DsLop &ds, char *filename) {
 	FILE * f; Lop lop; string malop;
 	if ((f=fopen(filename,"rb"))==NULL)
 	{ 
	 	BaoLoi ("Loi mo file LOP de doc"); return ;
 	}
 	ds.n =0;
 	while  (fread (&lop, sizeof (Lop), 1, f)!=0)
    {
    	NhapLop(ds,lop);
    	//malop=lop.MALOP;
    	//OpenSv(lop.DSSV,malop);
	}
    for(int i=0;i<ds.n;i++)
    {
    	OpenSv(ds.node[i]->DSSV,ds.node[i]->MALOP);
	}
 	fclose(f);
 //BaoLoi ("Da load xong danh sach vao bo nho");
}

void SaveSNN(SNN ds,char *filename) {
	FILE * f;
 	if ((f=fopen(filename,"wb"))==NULL)
 	{  
	 	BaoLoi ("Loi mo file ID de ghi"); return ;
 	}
	for (int i=1; i <= ds.n; i++)
 	  	fwrite (&ds.nodes[i], sizeof (int), 1, f);
	fclose(f);
 //BaoLoi ("Da ghi xong danh sach vao file");
}

void OpenSNN(SNN &ds,char *filename) {
 	FILE * f; int num;
 	if ((f=fopen(filename,"rb"))==NULL)
 	{	  
	 	BaoLoi ("Loi mo file ID de doc"); return ;
 	}
 	ds.n =0;
 	while  (fread (&ds.nodes[ds.n], sizeof (int), 1, f)!=0)
    	ds.n++;
 	fclose(f);
 //BaoLoi ("Da load xong danh sach vao bo nho");
}

void SaveMh_(Tree t,char *filename,FILE *f)
{
	MonHoc mh;
	if(t!=NULL)
 	{
 		mh = t->data;
  		fwrite (&mh, sizeof (MonHoc), 1, f);
  		SaveMh_(t->left,filename,f);
  		SaveMh_(t->right,filename,f);
 	}
}

void SaveMh(Tree t,char *filename) {
 	FILE * f; 
 	if ((f=fopen(filename,"wb"))==NULL)
 	{  
 		BaoLoi ("Loi mo file Mon hoc de ghi"); return ;
 	}
	SaveMh_(t,filename,f);
 	fclose(f);
//BaoLoi ("Da ghi xong danh sach vao file");
}

void OpenMh(Tree &t,char *filename) {
 	FILE * f; MonHoc mh;
 	if ((f=fopen(filename,"rb"))==NULL)
 	{
	 	BaoLoi ("Loi mo file Mon hoc de doc"); return ;
 	}

 	while  (fread (&mh, sizeof (MonHoc), 1, f)!=0)
		NhapMh(t,mh);
 	
 	fclose(f);
 //BaoLoi ("Da load xong danh sach vao bo nho");
}

void SaveCh(DsCauHoi ds,char *filename) {
	FILE * f;
 	if ((f=fopen(filename,"wb"))==NULL)
 	{  
	 	BaoLoi ("Loi mo file Cau hoi de ghi"); return ;
 	}
	for (int i=0; i < ds.n; i++)
 	  	fwrite (ds.DS[i], sizeof (CauHoi), 1, f);
	fclose(f);
 //BaoLoi ("Da ghi xong danh sach vao file");
}

void OpenCh(DsCauHoi &ds,char *filename) {
 	FILE * f; CauHoi ch;
 	if ((f=fopen(filename,"rb"))==NULL)
 	{	  
	 	BaoLoi ("Loi mo file Cau hoi de doc"); return ;
 	}
 	ds.n =0;
 	while  (fread (&ch, sizeof (CauHoi), 1, f)!=0)
    {
    	ds.DS[ds.n] = new CauHoi;
    	*ds.DS[ds.n] = ch;
    	ds.n++;	
	}
 	fclose(f);
 //BaoLoi ("Da load xong danh sach vao bo nho");
}
 void SaveCT(DsCauHoi ds,char *masv)
 {
 
 	string masv_ = masv;
 	string mamh_ = ds.DS[0]->MAMH;
 	string filename = where + "CT" + masv_ + mamh_ + ".txt";
 	char file[filename.size() + 1];
	strcpy(file,filename.c_str());
 	
 	FILE * f;
 	if ((f=fopen(file,"wb"))==NULL)
 	{  
	 	BaoLoi ("Loi mo file chi tiet de ghi"); return ;
 	}
	for (int i=0; i < ds.n; i++)
	{
		fwrite (ds.DS[i], sizeof (CauHoi), 1, f);
	}
	fclose(f);
	BaoLoi("Luu chi tiet bai thi thanh cong");
 }

void OpenCT(DsCauHoi &ds,char* masv, char * mamh) {
 	FILE * f; CauHoi ch;
 	
 	string masv_ = masv;
 	string mamh_ = mamh;
 	string filename = where+"CT" + masv_+mamh_+".txt";
 	char file[filename.size() + 1];
	strcpy(file,filename.c_str());
	
 	if ((f=fopen(file,"rb"))==NULL)
 	{	  
	 	BaoLoi ("Loi mo file chi tiet de doc"); return ;
 	}
 	ds.n =0;
 	while  (fread (&ch, sizeof (CauHoi), 1, f)!=0)
    {
    	ds.DS[ds.n] = new CauHoi;
    	*ds.DS[ds.n] = ch;
    	ds.n++;	
	}
 	fclose(f);
 	//BaoLoi ("Da load xong danh sach vao bo nho");
 	InDsCT(ds,masv,mamh);
}

//END------------------------------------------------SAVE + OPEN-------------------------------------------
void Menu(DsLop &dslop,Tree &t,DsCauHoi &dsch,SNN dssnn)
{
	int chon,chucnang;
	char masv[15];
	char mamh[15];
	char malop[15]; 	
	DsCauHoi CT; 
	while(1)
	{
		system("cls");
		chon= MenuDong(thucdon);
		system("cls");
		switch (chon )
		{	
    		case 1: NhapDsLop(dslop,1); 
    				SaveLop(dslop,filelop);
					break;
   	 		case 2: InDsLop(dslop);
					break;
    		case 3: NhapDsSv(dslop);
					break;
			case 4:				
					while(1)
					{
						chucnang=MenuDong(quanly);
						system("cls");
						switch(chucnang)
						{
							case 1: system("cls"); //them
								NhapDsMh(t);
								SaveMh(t,filemh);
								break;
							case 2: //sua
								NhapChuoi("Ma mon hoc: ",mamh);
								if(SearchMh(t,mamh)==0)
								{
									SuaMh(t,mamh);
								}else{
									BaoLoi("Ma mon hoc khong ton tai");
								}
								break;
							case 3:	//xoa
								NhapChuoi("Nhap ma mon hoc can xoa : ",mamh);
								if(SearchMh(t,mamh)==0)
								{
									XoaMh(t,mamh,dsch);
								}else{
									BaoLoi("Ma mon hoc khong ton tai");
								} 
								break;
							case 4: 
								cout<<"STT"<<setw(15)<<"MA MON HOC"<<setw(20)<<"TEN MON HOC"<<endl;
								InDsMh(t); getch();
								STT = 1;
								break;
							case 5: break;
							default: break;
						}
						if(chucnang==5)
						{
							break;
						}
				}
					break;   
    		case 5: NhapDsCauHoi(dsch,dssnn,t);
    					SaveCh(dsch,filech);
					break;
    		case 6: ChuanBiThi(dsch,t,dslop,0);
					break;
    		case 7: //InDsCh(dsch);   					
						while(1)
						{
							NhapChuoi("Nhap ma sinh vien(0 la ket thuc): ",masv);
							if(strcmp(masv,"0")==0)
							{
								Menu(dslop,t,dsch,dssnn);
								return;
							}
							if(SearchSV(dslop,masv)==NULL)
    						{
    							BaoLoi("Ma sinh vien khong ton tai");
    							continue;
							}
							break;
						}
						while(1)
						{
							NhapChuoi("Nhap ma mon hoc(0 la ket thuc): ",mamh);
							if(strcmp(mamh,"0")==0)
							{
								Menu(dslop,t,dsch,dssnn);
								return;
							}
							if(SearchMh(t,mamh)==1)
    						{
    							BaoLoi("Mon hoc khong ton tai");
    							continue;
							}
							break;
						}
    					OpenCT(CT,masv,mamh);
    					
					break;
			case 8: 
						while(1)
						{
							NhapChuoi("Nhap ma lop(0 la ket thuc): ",malop);
							if(strcmp(malop,"0")==0)
							{
								Menu(dslop,t,dsch,dssnn);
								return;
							}
							if(SearchLop(dslop,malop)<0)
    						{
    							BaoLoi("Ma lop khong ton tai");
    							continue;
							}
							break;
						}
						while(1)
						{
							NhapChuoi("Nhap ma mon hoc(0 la ket thuc): ",mamh);
							if(strcmp(mamh,"0")==0)
							{
								Menu(dslop,t,dsch,dssnn);
								return;
							}
							if(SearchMh(t,mamh)==1)
    						{
    							BaoLoi("Mon hoc khong ton tai");
    							continue;
							}
							break;
						}
						
						InBangDiem(dslop,malop,mamh);
					break;
    		case so_item :return ; //status=DangNhap(dslop);    
					break;	
			}
		}
}

void LoadData(Tree &t,SNN &dssnn,DsCauHoi &dsch)
{
	OpenMh(t,filemh);
	OpenSNN(dssnn,fileid);
	OpenCh(dsch,filech);
}

SV_PTR CheckDangNhap(DsLop ds,char *tendangnhap, char *matkhau){
	SV_PTR p;
	for(int i=0;i<ds.n;i++)
	{
		for(p=ds.node[i]->DSSV;p!=NULL;p=p->next)
		{
			if(strcmp(tendangnhap,p->data.MASV)==0)
			{
				if(strcmp(matkhau,p->data.password)==0)
				{
					return p;
				}else{
					BaoLoi("Sai mat khau");
					return NULL;
				}
			}
		}
	}
	BaoLoi("Ten dang nhap khong ton tai");
	return NULL;
 	
}

void DangNhap()
{	
	Tree t = NULL; //Khoi tao cay nhi phan		
	DsCauHoi dsch; dsch.n=0; //Khoi tao ds cau hoi	
	DsLop dslop;
	OpenLop(dslop,filelop);	 //load ds lop
	SNN dssnn; dssnn.n=0; //Khoi tao ds so ngau nhien
	
	if(dssnn.n<=0)
	{
		TaoDayNN(dssnn,MAXQ,MAXQ);
		SaveSNN(dssnn,fileid);
	}
	int dem=1;
	while(dem<=3)
	{
		system("cls");
		char tendangnhap[15];
		char matkhau[15];
		NhapChuoi("Ten dang nhap: ",tendangnhap);
		cout<<"Mat khau: ";
		strcpy(matkhau,strupr(Pwd()));
		if(strcmp(tendangnhap,"GV")==0)
		{
			if(strcmp(matkhau,"GV")==0)
			{
				LoadData(t,dssnn,dsch);
				Menu(dslop,t,dsch,dssnn);
				return;
			}
		}
		if(CheckDangNhap(dslop,tendangnhap,matkhau)!=NULL)
		{
			LoadData(t,dssnn,dsch);
			sinhvien_ = CheckDangNhap(dslop,tendangnhap,matkhau)->data;
			ChuanBiThi(dsch,t,dslop,1);
		}
		cout<<endl;
		dem++;
	}
}


int main()
{
	DangNhap();
	return 0;	
}
