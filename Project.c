#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
 
typedef struct ders{
	
	char kod[10];
	char ad[50];
	char kredi;
	short kontenjan;
	struct ders* next;
	char **dersialan;
	
	
	
}DERS;

typedef struct ogrenci{
	
	char ono[10];
	char oad[20];
	char osoyad[20];
	char tkredi;
	char tders;
	struct ogrenci* prev;
	struct ogrenci* next;
	
	
}OGRENCI;

void DersOlustur(DERS **head);
void yazdir(DERS *head);
void DersSil(DERS **head,OGRENCI *ohead);
void load_menu(DERS* head,OGRENCI* ohead,int *ptr,int maxkredi,int maxders,char *tarih);
void dosyadanOku(DERS **head,OGRENCI** ohead,char delimeter[2]);
void dersleridosyayaYazdir(DERS *head);
void ogrencileridosyayaYazdir(OGRENCI *ohead);
void ogrenciEkle(OGRENCI **ohead);
void ogrenciyazdir(OGRENCI *ohead);
void dersKayit(DERS*head,OGRENCI*ohead,int *ptr,int maxkredi,int maxders,char *tarih);
int comparator(const void* str1, const void* str2);
void sinifdizisiyazdir(DERS *tmp);
void sinifdizisioku(DERS *tmp);
void dersSil(DERS *head,OGRENCI *ohead);
void ogrenciderskayit(DERS *tmp,OGRENCI *tmp2,int *ptr,char* tarih);
void derssilyazdir(char *gelenkod,char *gelenno);
void ogrencidersprogrami(DERS *tmp,OGRENCI *otmp);
void derskapandiyazdir(char *derskod);
void derssilindikrediguncelle(DERS *tmp,OGRENCI *ohead);
void OgrenciSil(DERS *head,OGRENCI **ohead);
void ogrencisilindiyazdir(char *gelenno);
void derskoduveryazdir(DERS *head);
int main(void){
	setlocale(LC_ALL, "Turkish");
	char tarih[15],yedektarih[15];
	int id=10000,maxkredi,maxders,gecerlimi;
	DERS* head=NULL;
	OGRENCI* ohead=NULL;
	printf("Bir Öðrencinin Alabileceði Max. Kredi Sayýsýný Giriniz : ");
	scanf("%d",&maxkredi);
	printf("Bir Öðrencinin Alabileceði Max. Ders Sayýsýný Giriniz : ");
	scanf("%d",&maxders);
	
	do{
	
	printf("Islemin Yapildigi Tarihi Giriniz(GG.AA.YYYY) : ");
	scanf("%s",tarih);
	strcpy(yedektarih,tarih);
	gecerlimi=tarihgecerlimi(tarih);
}	while(gecerlimi==-1);
	
	dosyadanOku(&head,&ohead,",\0");	
	id=idbul(head,ohead);
	if(id==0){
		id=10000;
	}
	id++;		
	load_menu(head,ohead,&id,maxkredi,maxders,yedektarih);		
			
	return 0;
}
void DersOlustur(DERS **head){
	setlocale(LC_ALL, "Turkish");
	DERS* tmp=NULL;
	DERS* tmp2;
	char kopya[]="son";
	tmp=(DERS*)malloc(sizeof(DERS));
	
	fgetc(stdin);

	printf("Dersin Kodunu Giriniz : ");
	scanf ("%[^\n]%*c", tmp->kod);
	printf("Dersin Adini Giriniz : ");
	scanf ("%[^\n]%*c", tmp->ad);
	printf("Dersin Kredisini Giriniz : ");
	scanf("%d",&tmp->kredi);
	printf("Dersin Kontenjanini Giriniz : ");
	scanf("%d", &tmp->kontenjan);
	
	tmp->dersialan=(char**)malloc(1*sizeof(char*));
	tmp->dersialan[0]=(char*)malloc(10*sizeof(char));
	strcpy(tmp->dersialan[0],kopya);
		
	tmp->next=NULL;
	
	if(*head==NULL){
		*head=tmp;
		
	}else{
	 	tmp2=*head;
		int c;	
	 	c=strcmp(tmp->kod,tmp2->kod);
	 	if(c==0){
			printf("Ayni Kodlu Ders Eklenemez...\n");
		 	return;
		}
		if(tmp2->next==NULL&&c>0){
			tmp2->next=tmp;
			return;
		}
		
	 	if(c<0){
	 		tmp->next=*head;
	 		*head=tmp;
	 		
		 }else{
		c=strcmp(tmp->kod,tmp2->next->kod); 
	 	while((tmp2->next->next!=NULL)&&(c>0)){
	 		
	 		tmp2=tmp2->next;
	 		c=strcmp(tmp->kod,tmp2->next->kod);
		 }
		
		if(c==0){
			printf("Ayni Kodlu Ders Eklenemez...\n");
		 	return;
		}
		
		if(tmp2->next->next==NULL&&c>0){
			tmp2->next->next=tmp;
		}
		else{
			
			tmp->next=tmp2->next;
			tmp2->next=tmp;	
	}}	
}
}

void yazdir(DERS *head){
	DERS *tmp;
	tmp=head;
	while(tmp!=NULL){
		printf("%s ",tmp->kod);
		printf("%s ",tmp->ad);
		printf("%d ",tmp->kredi);
		printf("%d ",tmp->kontenjan);
		printf("\n");
		tmp = tmp->next;
	}
	printf("\n");
}

void ogrenciyazdir(OGRENCI *ohead){
	OGRENCI *tmp;
	tmp=ohead;
	while(tmp!=NULL){
		printf("%s ",tmp->ono);
		printf("%s ",tmp->oad);
		printf("%s ",tmp->osoyad);
		printf("%d ",tmp->tders);
		printf("%d",tmp->tkredi);
		printf("\n");
		tmp = tmp->next;
	}
	printf("\n");
}

void DersSil(DERS **head,OGRENCI *ohead){
	char tmpkod[15];
	DERS* tmp;
	DERS* tmp2;
	char file[15];
	
	tmp=*head;
	char c;
	if(tmp==NULL){
		printf("Dersler Dosyasý Boþ!!!\n");
		return;
	}
	
	printf("Silmek Istedigini Dersin Kodunu Giriniz : ");
	scanf("%s",tmpkod);
	
	c=strcmp(tmpkod,tmp->kod);
	if(c==0){
		derssilindikrediguncelle(tmp,ohead);
		
		tmp=(*head)->next;
		derskapandiyazdir(tmpkod);
		printf("%s Kodlu Ders Silindi...\n",(*head)->kod);
		free(*head);
		*head=tmp;		
	}else{
			
	if(tmp->next==NULL){
		printf("%s Kodlu Ders Bulunamadý",tmpkod);
		return;
	}	
	c=strcmp(tmpkod,tmp->next->kod);
	while(tmp->next->next!=NULL&&c!=0){
		tmp=tmp->next;
		c=strcmp(tmpkod,tmp->next->kod);
	}
	if(c!=0){
		printf("%s Kodlu Ders Bulunamadi...\n",tmpkod);
		return;
	}
	else{
		derssilindikrediguncelle(tmp->next,ohead);		
		tmp2=tmp->next;
		derskapandiyazdir(tmpkod);
		tmp->next=tmp->next->next;
		printf("%s Kodlu Ders Silindi...\n",tmp2->kod);
		free(tmp2);
		tmp2=NULL;
	}
}	
	strcpy(file,tmpkod);
	strcat(file, ".txt");
	remove(file);	
}

void load_menu(DERS* head,OGRENCI* ohead,int *ptr,int maxkredi,int maxders,char *tarih)
{
    int choice;
 	
    do
    {
    	DERS *nal=head;
        printf("Menu\n\n");
        printf("1. Yeni Ders Ekle\n");
        printf("2. Açýk Dersleri Yazdýr\n");
        printf("3. Ders Kapat\n");
        printf("4. Öðrenci Sil\n");
        printf("5. Öðrenci Ekle\n");
        printf("6. Öðrenci Yazdýr\n");
        printf("7. Öðrenci Derse  Kayýt Et\n");
        printf("8. Öðrenci Ders Kayýt Sildir\n");
        printf("9. Öðrenci Ders Programý Oluþtur\n");
        printf("10.DERSKODU.txt'leri Yazdýr.'\n");
        printf("11.Sýnýf Listesi Yazdýr.\n");
        printf("12.Çýkýþ\n");
        printf("Yapmak istediginiz islemi giriniz: ");
        scanf("%d",&choice);
 
        switch(choice)
        {
            case 1: DersOlustur(&head);
            		dersleridosyayaYazdir(head);
                	break;
            case 2: yazdir(head);
               		break;
            case 3: DersSil(&head,ohead);
            		dersleridosyayaYazdir(head);
            		ogrencileridosyayaYazdir(ohead);
            		break;
            case 4: OgrenciSil(head,&ohead);
            		dersleridosyayaYazdir(head);
            		ogrencileridosyayaYazdir(ohead);
            		break;
           
            case 5: ogrenciEkle(&ohead);
            		ogrencileridosyayaYazdir(ohead);
            	break;
            case 6: ogrenciyazdir(ohead);
            	break;
            case 7: dersKayit(head,ohead,ptr,maxkredi,maxders,tarih);
            		dersleridosyayaYazdir(head);
            		ogrencileridosyayaYazdir(ohead);
            	break;
            case 8: dersSil(head,ohead);
            		dersleridosyayaYazdir(head);
            		ogrencileridosyayaYazdir(ohead);
            	
            	break;
            case 9: ogrencidersprogrami(head,ohead);
            	break;
            	
            case 10: 
            
				while(nal!=NULL){
				sinifdizisiyazdir(nal);
				nal=nal->next;
			}
            	break;          	
            case 11:
            	derskoduveryazdir(head);
            	break;            	
            case 12: printf("Programdan Cikildi...\n");
                exit(0);
                break;
            default: printf("Gecersiz Giris!\n");
                break;
        }
 
    } while (choice != 12);
 
}

void dosyadanOku(DERS** head,OGRENCI** ohead,char delimiter[2]){
	DERS* tmp=NULL;
	DERS* tmp2=NULL;
	char *token;
	
	char maske[]="son";
	FILE *fp;
	char buff[255];
	if(fp=fopen("dersler.txt","r")){
		
	
	

		
	while(fgets(buff,255,fp)!=NULL){
		
		tmp=(DERS*)malloc(sizeof(DERS));
		if(*head==NULL){
		
		*head=tmp;
	}
		token=strtok(buff,delimiter);
		strcpy(tmp->kod,token);
		token=strtok(NULL,delimiter);
		strcpy(tmp->ad,token);
		token=strtok(NULL,delimiter);
		tmp->kredi=atoi(token);
		token=strtok(NULL,delimiter);
		tmp->kontenjan=atoi(token);
		tmp->dersialan=(char**)calloc(1,sizeof(char*));
		tmp->dersialan[0]=(char*)calloc(10,sizeof(char));
		strcpy(tmp->dersialan[0],maske);
					
	if(tmp2!=NULL){
	
	tmp2->next=tmp;
}
	tmp2=tmp;
	tmp->next=NULL;
}	
	fclose(fp);	}
	else{
		printf("Dersler.txt dosyasi bulunamadi.\n");
	}
	
	OGRENCI* tmp3=NULL;
	OGRENCI* tmp4=NULL;
		
	FILE *fp2;
	
	if(fp2=fopen("ogrenciler.txt","r")){
			
	while(fgets(buff,255,fp)!=NULL){
		
		tmp3=(OGRENCI*)malloc(sizeof(OGRENCI));
		if(*ohead==NULL){
		*ohead=tmp3;
	}
		token=strtok(buff,delimiter);
		strcpy(tmp3->ono,token);
		token=strtok(NULL,delimiter);
		strcpy(tmp3->oad,token);
		token=strtok(NULL,delimiter);
		strcpy(tmp3->osoyad,token);
		token=strtok(NULL,delimiter);
		tmp3->tkredi=atoi(token);
		token=strtok(NULL,delimiter);
		tmp3->tders=atoi(token);
		
	if(tmp4!=NULL){
		
	tmp4->next=tmp3;
}
	tmp4=tmp3;
	tmp3->next=NULL;
}	
	fclose(fp2);}
	else{
		printf("Ogrenciler.txt dosyasi bulunamadi.\n");
	}	
}

void dersleridosyayaYazdir(DERS *head){
	
	DERS *tmp;
	tmp=head;	
	FILE *fp;	
	fp=fopen("dersler.txt","w");
		
	while(tmp!=NULL){
		
	fprintf(fp, "%s,%s,%d,%d  \n",tmp->kod,tmp->ad,tmp->kredi,tmp->kontenjan);
	tmp=tmp->next;		
}	
	fclose(fp);		
}
void ogrencileridosyayaYazdir(OGRENCI *ohead){
	
	OGRENCI *tmp2;
	tmp2=ohead;	
	FILE *fp;	
	fp=fopen("ogrenciler.txt","w");		
	while(tmp2!=NULL){
		
	fprintf(fp, "%s,%s,%s,%d,%d  \n",tmp2->ono,tmp2->oad,tmp2->osoyad,tmp2->tkredi,tmp2->tders);
	tmp2=tmp2->next;			
}	
	fclose(fp);		
}

void ogrenciEkle(OGRENCI **ohead){
	OGRENCI *tmp=NULL;
	OGRENCI *tmp2;
	tmp=(OGRENCI*)malloc(sizeof(OGRENCI));
	printf("Ogrencinin Nosunu Giriniz : ");
	scanf("%s",&tmp->ono);
	printf("Ogrencinin Adini Giriniz : ");
	scanf_s("%s",&tmp->oad);
	printf("Ogrencinin Soyadini Giriniz : ");
	scanf("%s",&tmp->osoyad);
	tmp->tders=0;
	tmp->tkredi=0;
	tmp->next=NULL;
	tmp->prev=NULL;
	
	if(*ohead==NULL){
		*ohead=tmp;
		
	}else{
		
		tmp2=(*ohead);
		int c;	
	 	c=strcmp(tmp->ono,tmp2->ono);
	 	if(c==0){
			printf("Ayni Kodlu Ogrenci Eklenemez...\n");
		 	return;
		}
		if(tmp2->next==NULL&&c>0){
			tmp->prev=tmp2;
			tmp2->next=tmp;
			return;
		}
	 	if(c<0){
	 		tmp->next=*ohead;
	 		(*ohead)->prev=tmp;
	 		*ohead=tmp;
	 		return;
	 		
		}else{
		 	
		 	c=strcmp(tmp->ono,tmp2->next->ono); 
	 		while((tmp2->next->next!=NULL)&&(c>0)){
	 		
	 			tmp2=tmp2->next;
	 			c=strcmp(tmp->ono,tmp2->next->ono);
		 	}
		 	
		 	if(c==0){
			printf("Ayni Kodlu Ogrenci Eklenemez...\n");
		 	return;
			}
		
			if(tmp2->next->next==NULL&&c>0){
				tmp2->next->next=tmp;
				tmp->prev=tmp2->next;
				
			}
			else{
			
			tmp->next=tmp2->next;
			tmp2->next=tmp;
			tmp->next->prev=tmp;
			tmp->prev=tmp2;	
	}		 	
		 }
	}
}

void dersKayit(DERS*head,OGRENCI*ohead,int *ptr,int maxkredi,int maxders,char *tarih){
	
	DERS *tmp=head;
	OGRENCI *otmp=ohead;
	
	if(tmp==NULL || otmp==NULL){
		printf("Liste(ler) boþ kayýt iþlemi yapýlamaz ");
		return ;
	}
	
	char tmpno[10];
	char tmpkod[10];
	int n=0;
	char kopya[]="son";
	
	printf("Ders kayit islemi yapmak istediginiz ogrenci no girin : ");
	scanf("%s",tmpno);
	printf("Ders kayit islemi yapmak istediginiz ders kodu girin : ");
	scanf("%s",tmpkod);
	int i;
	int a,b;
	a=strcmp(tmpkod,tmp->kod);
	b=strcmp(tmpno,otmp->ono);
	while(a!=0 && tmp->next!=NULL){
		tmp=tmp->next;
		a=strcmp(tmpkod,tmp->kod);
	}
	if(tmp->next==NULL && a!=0){
		printf("%s kodlu ders bulunamadi.\n ",tmpkod);
		return;
	}
	while(b!=0 && otmp->next!=NULL){
		
		otmp=otmp->next;
		b=strcmp(tmpno,otmp->ono);
	}
	if(otmp->next==NULL && b!=0){
		printf("%s no.lu ogrenci bulunamadi.\n ",tmpno);
		return;
	}
		
	while((tmp->kontenjan)>=n && strcmp((tmp->dersialan[n]),kopya)){
		if(!(strcmp((tmp->dersialan[n]),tmpno))){
			printf("Ogrenci Derse Zaten Kayitli.\n");
			return;
		}
		n++;
	}
	if(tmp->kontenjan==n){
		printf("Dersin kontenjani dolu!\n");
		return ;
	}
	if(otmp->tders==maxders){
		printf("Öðrenci Ýzin Verilen Toplam Ders Sayýsýný Geçemez!!!\n");
		return ;
	}
	int z=otmp->tkredi+tmp->kredi;
	if(z>maxkredi){
		printf("Öðrenci Ýzin Verilen Toplam Kredi Sayýsýný Geçemez!!!\n");
		return ;
	}

	char **mattmp=NULL;
	DERS *newtmp=NULL;
	
	mattmp=(char**)realloc((tmp->dersialan),sizeof(char*)*(n+2));
		if(mattmp==NULL){
		return;
			}
			
	tmp->dersialan=mattmp;
	
	tmp->dersialan[n]=(char*)malloc(10*sizeof(char));				
	strcpy(tmp->dersialan[n],tmpno);		
	tmp->dersialan[n+1]="son";
	otmp->tkredi+=tmp->kredi;
	otmp->tders++;	
	ogrenciderskayit(tmp,otmp,ptr,tarih);

	for (i = 0; i < n+1; i++) {
	
      qsort(tmp->dersialan, n+1, sizeof(const char*), comparator);
}

	


			
}
int comparator(const void* str1, const void* str2) {
   if(strcmp(*(const char**)str1, *(const char**)str2) >= 0)
      return 1;
   else return 0;
}

void sinifdizisiyazdir(DERS* tmp){
	int n=0;
	while(strcmp(tmp->dersialan[n],"son")){
		n++;
	}
	char file[20];
	int i;
	FILE *fp;
	strcpy(file,tmp->kod);
	strcat(file,".txt");
	fp=fopen(file,"w");
	
	for(i=0;i<n;i++){
		fprintf(fp,"%s \n",(tmp->dersialan[i]));
	}
	fclose(fp);	
	
}


void ogrenciderskayit(DERS *tmp,OGRENCI *tmp2,int *ptr,char *tarih){
	
	FILE *fp2;
	char text[10]="kayitli";
	int gecerlimi=-1;
	char yedektarih[15];
	char checker=1;

	fp2=fopen("OgrenciDersKayit.txt","a");
	fprintf(fp2,"%d,%s,%s,%s,%s\n",*ptr,tmp->kod,tmp2->ono,tarih,text);
	fclose(fp2);
	(*ptr)++;
}

DERS* kodlaDersBul(DERS *head,char* derskod){
	DERS *tmp=head;
	
	while(tmp!=NULL && strcmp(tmp->kod,derskod)){
		tmp=tmp->next;
	}
	if(tmp==NULL){
		return NULL;
	}
	return tmp;	
}
OGRENCI* kodlaOgrenciBul(OGRENCI *ohead,char* ogrencino){
	OGRENCI *tmp=ohead;
	
	while(tmp!=NULL && strcmp(tmp->ono,ogrencino)){
		tmp=tmp->next;
	}
	if(tmp==NULL){
		return NULL;
	}
	return tmp;
}
void dersSil(DERS *head,OGRENCI *ohead){
	DERS *tmp=head;
	OGRENCI *otmp=ohead;
	
	char tmpno[10];
	char tmpkod[10];
	char kopya[]="son";
	int n=0;
	int a=0,i;
	
	printf("Ders Kayýt silme islemi yapmak istediginiz ogrenci no girin : ");
	scanf("%s",tmpno);
	printf("Ders kayit silme islemi yapmak istediginiz ders kodu girin : ");
	scanf("%s",tmpkod);
	tmp=kodlaDersBul(head,tmpkod);
	if(tmp==NULL){
		printf("%s Kodlu Ders Bulunamadý!!\n",tmpkod);
		return ;
	}
	otmp=kodlaOgrenciBul(ohead,tmpno);
	if(otmp==NULL){
		printf("%s Kodlu Ders Bulunamadý!!\n",tmpno);
		return ;
	}
	
	while(strcmp((tmp->dersialan[n]),kopya)){
		n++;
	}

	
	while(strcmp(tmp->dersialan[a],tmpno)){
		a++;
		if(a>n){
			printf("Kayýt olmadýðý dersten silinemez.\n");
			return;
		}
	}
	if(a>n){
		printf("Kayýtlý olmadýðý dersten silinemez!!");
		return ;
	}
	for (i=a;i<n;i++){
		strcpy(tmp->dersialan[i],tmp->dersialan[i+1]);
	}
	derssilyazdir(tmpkod,tmpno);
	otmp->tders--;
	otmp->tkredi-=tmp->kredi;
	for(i=0;i<n;i++){
		
		}
}
void derssilyazdir(char *gelenkod,char *gelenno){
	FILE *fp;
	FILE *fp2;
	FILE *fp3,*fp4;
	char delimiter[2]=",\0";
	int idtmp;
	char kodtmp[10];
	char notmp[10];
	char durum[20];
	char tarihtmp[15];
	char buff[255];
	char *token;
	
	fp=fopen("OgrenciDersKayit.txt", "r");
	fp2=fopen("OgrenciDersKayit2.txt","w");
	while(fgets(buff,255,fp)!=NULL){
	token=strtok(buff,delimiter);
	idtmp=atoi(token);
	token=strtok(NULL,delimiter);
	strcpy(kodtmp,token);
	token=strtok(NULL,delimiter);
	strcpy(notmp,token);
	token=strtok(NULL,delimiter);
	strcpy(tarihtmp,token);
	token=strtok(NULL,delimiter);
	strcpy(durum,token);
	
	if(strcmp(gelenkod,kodtmp) || strcmp(gelenno,notmp)){
		fprintf(fp2,"%d,%s,%s,%s,%s",idtmp,kodtmp,notmp,tarihtmp,durum);	
	}else{
		fprintf(fp2,"%d,%s,%s,%s,\n",idtmp,kodtmp,notmp,tarihtmp);
	}
}
	fclose(fp);
	fclose(fp2);
	
	fp3=fopen("OgrenciDersKayit.txt","w");
	fp4=fopen("OgrenciDersKayit2.txt","r");
	while(fgets(buff,255,fp4)!=NULL){
	
	token=strtok(buff,delimiter);
	idtmp=atoi(token);
	token=strtok(NULL,delimiter);
	strcpy(kodtmp,token);
	token=strtok(NULL,delimiter);
	strcpy(notmp,token);
	token=strtok(NULL,delimiter);
	strcpy(tarihtmp,token);
	
	if(strcmp(gelenkod,kodtmp) || strcmp(gelenno,notmp)){
		token=strtok(NULL,delimiter);
		strcpy(durum,token);
		
		fprintf(fp3,"%d,%s,%s,%s,%s",idtmp,kodtmp,notmp,tarihtmp,durum);
	}else{

		fprintf(fp3,"%d,%s,%s,%s,sildi\n",idtmp,kodtmp,notmp,tarihtmp);
		
	}
	

}
	fclose(fp3);
	fclose(fp4);
	remove("OgrenciDersKayit2.txt");
}


int idbul(DERS* tmp,OGRENCI *otmp){
	FILE *fp ;
	DERS *head=tmp;
	fp = fopen("OgrenciDersKayit.txt","r");
	
	if(fp==NULL){
		
		return;
	}
	int a;
	int i=0;
	char kodtmp[10];
	char notmp[10];
	char durum[20];
	char tarihtmp[20];
	char delimiter[2]=",\0";
	char buff[255];
	char maske[20];
	char tmpmaske[20]="kayitli";
	strcpy(maske,tmpmaske);
	char maske2[]="son";
	char *token;

	while(fgets(buff,255,fp)!=NULL){
	token=strtok(buff,",");
	a=atoi(token);
	token=strtok(NULL,delimiter);
	strcpy(kodtmp,token);
	token=strtok(NULL,delimiter);
	strcpy(notmp,token);
	token=strtok(NULL,delimiter);
	strcpy(tarihtmp,token);
	token=strtok(NULL,delimiter);
	strcpy(durum,token);
	
	if(durum[0]==maske[0]){
		
		while(strcmp(tmp->kod,kodtmp)){
			tmp=tmp->next;
		}
		while(strcmp(tmp->dersialan[i],maske2)){
			i++;
		}
		char **mattmp;
		mattmp=(char**)realloc((tmp->dersialan),sizeof(char*)*(i+2));
		if(mattmp==NULL){
		return;
			}
		tmp->dersialan=mattmp;
		tmp->dersialan[i+1]=(char*)calloc(10,sizeof(char));
		strcpy(tmp->dersialan[i],notmp);
		strcpy(tmp->dersialan[i+1],maske2);
	}
	tmp=head;
	i=0;
}
	fclose(fp);
	
	return a;
}
void ogrencidersprogrami(DERS *tmp,OGRENCI *otmp){
	char tmpno[10];
	char file[20];
	char kopya[]="son";
	int i=0;
	printf("Ders Programini Cikartmak Istediginiz O.NO giriniz : ");
	scanf("%s",tmpno);
	while(otmp!=NULL && strcmp(otmp->ono,tmpno)){
		
		
		otmp=otmp->next;
		
	}
	if(otmp==NULL){
		printf("Olmayan Öðrencinin Ders Prog Çýkartýlamaz!!\n");
		return ;
	}
	FILE *fp;
	sprintf(file, "%s_DERSPROGRAMI.txt",tmpno);
	fp=fopen(file,"w");
	while(tmp!=NULL){
		
		while(strcmp(tmp->dersialan[i],tmpno) && strcmp(tmp->dersialan[i],kopya)){
			i++;
		}	
		if(strcmp(tmp->dersialan[i],tmpno)==0){
			fprintf(fp,"%s\n",tmp->kod);
		}
		tmp=tmp->next;
		i=0;
	}
	fclose(fp);
}
int tarihgecerlimi(char *tarih){
	char delimiter[2]=".\0";
	char *token;
	int dd,mm,yy;
	token=strtok(tarih,delimiter);
	dd=atoi(token);
	token=strtok(NULL,delimiter);
	mm=atoi(token);
	token=strtok(NULL,delimiter);
	yy=atoi(token);
	
	if(yy>=1900 && yy<=9999)
    {
        if(mm>=1 && mm<=12)
        {
            if((dd>=1 && dd<=31) && (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12)){
                return 1;}
            else if((dd>=1 && dd<=30) && (mm==4 || mm==6 || mm==9 || mm==11)){
                return 1;}
            else if((dd>=1 && dd<=28) && (mm==2)){			
                return 1;}
            else if(dd==29 && mm==2 && (yy%400==0 ||(yy%4==0 && yy%100!=0))){		
                return 1;}
            else{			
                printf("Gecersiz Gun Girdiniz!!!\n");
                return -1;}
        }
        else
        {
            printf("Gecersiz Ay Girdiniz!!!\n");
            return-1;
        }
    }
    else
    {
        printf("Gecersiz Yil Girdiniz!!!\n");
        return-1;
    }
	return 1;	
}
void derskapandiyazdir(char *derskod){
	FILE *fp;
	FILE *fp2;
	FILE *fp3,*fp4;
	char delimiter[2]=",\0";
	char kopya[]="DersKapandi";
	int idtmp;
	char kodtmp[10];
	char notmp[10];
	char durum[20];
	char tarihtmp[15];
	char buff[255];
	char *token;
	
	fp=fopen("OgrenciDersKayit.txt", "r");
	fp2=fopen("OgrenciDersKayit2.txt","w");
	while(fgets(buff,255,fp)!=NULL){
	token=strtok(buff,delimiter);
	idtmp=atoi(token);
	token=strtok(NULL,delimiter);
	strcpy(kodtmp,token);
	token=strtok(NULL,delimiter);
	strcpy(notmp,token);
	token=strtok(NULL,delimiter);
	strcpy(tarihtmp,token);
	token=strtok(NULL,delimiter);
	strcpy(durum,token);
	
	if(strcmp(derskod,kodtmp)){
		fprintf(fp2,"%d,%s,%s,%s,%s",idtmp,kodtmp,notmp,tarihtmp,durum);	
	}else{
		fprintf(fp2,"%d,%s,%s,%s,\n",idtmp,kodtmp,notmp,tarihtmp);
	}
}
	fclose(fp);
	fclose(fp2);
	
	fp3=fopen("OgrenciDersKayit.txt","w");
	fp4=fopen("OgrenciDersKayit2.txt","r");
	while(fgets(buff,255,fp4)!=NULL){
	
	token=strtok(buff,delimiter);
	idtmp=atoi(token);
	token=strtok(NULL,delimiter);
	strcpy(kodtmp,token);
	token=strtok(NULL,delimiter);
	strcpy(notmp,token);
	token=strtok(NULL,delimiter);
	strcpy(tarihtmp,token);
	
	
	
	if((strcmp(derskod,kodtmp))){
		token=strtok(NULL,delimiter);
		strcpy(durum,token);
		
		fprintf(fp3,"%d,%s,%s,%s,%s",idtmp,kodtmp,notmp,tarihtmp,durum);
	}else{
		fprintf(fp3,"%d,%s,%s,%s,DersKapandý\n",idtmp,kodtmp,notmp,tarihtmp);		
	}
}
	fclose(fp3);
	fclose(fp4);
	remove("OgrenciDersKayit2.txt");	
}
void derssilindikrediguncelle(DERS *tmp,OGRENCI *ohead){
	OGRENCI *otmp=ohead;
	char kopya[]="son";	
	int i=0;
	
	while(strcmp(tmp->dersialan[i],kopya)){
		otmp=ohead;
	
	while(strcmp(tmp->dersialan[i],otmp->ono) && otmp!=NULL){
		otmp=otmp->next;
		
	}
	otmp->tders--;
	otmp->tkredi-=tmp->kredi;
	i++;	
}	
}
void OgrenciSil(DERS *head,OGRENCI **ohead){
	
	DERS *tmp=head;
	OGRENCI *otmp=*ohead;
	OGRENCI* otmp2;
	char kopya[10]="son";
	int n=0,a=0;
	char c;
	int i;
	char tmpno[10];
	printf("Silmek Ýstediðiniz Öðrenci Numarasý Giriniz : ");
	scanf("%s",tmpno);
	if(*ohead==NULL){
		printf("Öðrenciler.txt boþ silme yapýlamaz\n");
		return;
	}
	while(tmp!=NULL){
	n=0;
	a=0;
	
	while(strcmp((tmp->dersialan[n]),kopya)){
		n++;
	}
	
	while(strcmp(tmp->dersialan[a],tmpno) && strcmp(tmp->dersialan[a],kopya)){
		a++;
	}
	for (i=a;i<n;i++){
		strcpy(tmp->dersialan[i],tmp->dersialan[i+1]);
	}
	if((strcmp(tmp->dersialan[a],kopya))){
}
	tmp=tmp->next;
}

	
	c=strcmp(tmpno,otmp->ono);
	if(c==0){
		
		
		otmp=(*ohead)->next;
		printf("%s No.lu Öðrenci Silindi...\n",(*ohead)->ono);
		free(*ohead);
		*ohead=otmp;
		otmp->prev=(*ohead);
		
	}else{
	
	c=strcmp(tmpno,otmp->next->ono);
	while(otmp->next->next!=NULL&&c!=0){
		otmp=otmp->next;
		c=strcmp(tmpno,otmp->next->ono);
	}
	if(c!=0){
		printf("%s No.lu Öðrenci Bulunamadi...\n",tmpno);
		
	}
	else{	
		otmp2=otmp->next;
		otmp->next=otmp->next->next;
		if(otmp2->next!=NULL){
		
		otmp2->next->prev=otmp;
		
	}
		printf("%s No.lu Öðrenci Silindi...\n",otmp2->ono);
		free(otmp2);
		otmp2=NULL;
	}
}	

	ogrencisilindiyazdir(tmpno);
}

void ogrencisilindiyazdir(char *gelenno){
	FILE *fp;
	FILE *fp2;
	FILE *fp3,*fp4;
	char delimiter[2]=",\0";
	char kopya[]="OgrenciSilindi";
	int idtmp;
	char kodtmp[10];
	char notmp[10];
	char durum[20];
	char tarihtmp[15];
	char buff[255];
	char *token;
	
	fp=fopen("OgrenciDersKayit.txt", "r");
	fp2=fopen("OgrenciDersKayit2.txt","w");
	while(fgets(buff,255,fp)!=NULL){
	token=strtok(buff,delimiter);
	idtmp=atoi(token);
	token=strtok(NULL,delimiter);
	strcpy(kodtmp,token);
	token=strtok(NULL,delimiter);
	strcpy(notmp,token);
	token=strtok(NULL,delimiter);
	strcpy(tarihtmp,token);
	token=strtok(NULL,delimiter);
	strcpy(durum,token);
	
	if(strcmp(gelenno,notmp) ){
		fprintf(fp2,"%d,%s,%s,%s,%s",idtmp,kodtmp,notmp,tarihtmp,durum);	
	}else{
		fprintf(fp2,"%d,%s,%s,%s,\n",idtmp,kodtmp,notmp,tarihtmp);
	}


}
	fclose(fp);
	fclose(fp2);
	
	fp3=fopen("OgrenciDersKayit.txt","w");
	fp4=fopen("OgrenciDersKayit2.txt","r");
	while(fgets(buff,255,fp4)!=NULL){
	
	token=strtok(buff,delimiter);
	idtmp=atoi(token);
	token=strtok(NULL,delimiter);
	strcpy(kodtmp,token);
	token=strtok(NULL,delimiter);
	strcpy(notmp,token);
	token=strtok(NULL,delimiter);
	strcpy(tarihtmp,token);
	
	if(strcmp(gelenno,notmp) ){
		token=strtok(NULL,delimiter);
		strcpy(durum,token);		
		fprintf(fp3,"%d,%s,%s,%s,%s",idtmp,kodtmp,notmp,tarihtmp,durum);
	}else{
		fprintf(fp3,"%d,%s,%s,%s,silindi\n",idtmp,kodtmp,notmp,tarihtmp);		
	}
}
	fclose(fp3);
	fclose(fp4);
	remove("OgrenciDersKayit2.txt");
}

void derskoduveryazdir(DERS *head){
	DERS *tmp=head;
	char tmpkod[15];
	char maske[]="son";

	int i=0;
	printf("Sinif Listesini Yazdýrmak Ýçin Ders Kodunu Giriniz :");
	scanf("%s",tmpkod);
	
	while(tmp!=NULL && strcmp(tmp->kod,tmpkod)){
		tmp=tmp->next;
	}
	if(tmp==NULL){
		printf("Ders Bulunamadi!!");
		return;
	}
	
	while(strcmp(tmp->dersialan[i],maske)){
		printf("%s\n",tmp->dersialan[i]);
		i++;
	}
	
}

