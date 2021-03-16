#include <stdio.h>
#include <stdlib.h>
struct n{
	char harf;
	int frequency;
	struct n *left,*right,*next;
};
typedef struct n  NODE;

void find_frequency(char *str ,int *frequency){
	int i;
	for(i=0;str[i];i++){                 
		if(str[i]!=32)	            // dizinin elaman� bo�luk mu diye kontrol ediyoruz ��nk� bo�luk ben�m algoritma tasar�m�m icin istisna bi durum 
		frequency[(str[i]-'a')]++;	// k�c�k harfli elamanlardan  'a' c�kard���m�zda bo�luk haric dizide yerle�ice�i yerlerden 'a'+i �eklinde bir geri d�n�� sa�layabilece�imden
		 								               // frekans� bu �ekilde buluyorum bo�luk icin asc�� kar��l���  32 yi ayr� tutup ifle kontrol ediyorum
		else{
		frequency[26]++;}
	}
}
NODE * create_node(){
	NODE *x;
	x=(NODE*)malloc(sizeof(NODE));
	if(x==NULL)	                         //Malloc sonucu ramde yer ac�lmamas� durumu
	printf("memoryde yeterli alan yok ");
	x->left=NULL;
	x->harf=NULL;               // standart ilklendirmeler
	x->next=NULL;
	x->right=NULL;
	return x;
}
void frequency_to_linklisted(int *frequency,NODE*head){
		NODE *temp;
		int i;
		for(i=0;i<26;i++){         //bo�luk dahil de�il
			if(frequency[i]!=0){            // frekans� dizisinde sadece  0  farkl� olan indis kar��l��� harf texte ge�iyor demektir 
				if(head->next==NULL){        // linkli liste daha olu�mu� mu diye kontrol ediyorum
					NODE *temp =create_node();
					head->next=temp;                    
					temp->harf='a'+i;             // yukarda bahsetti�im gibi geri d�n�� sa�l�yorum
					temp->frequency=frequency[i];
					
				}
				else{
				
				temp=head;         
				while(temp->next!=NULL){
					temp=temp->next;
				}
				temp->next=create_node();
				temp->next->harf='a'+i;
				temp->next->frequency=frequency[i];
				}
				}
			
	}
	if(frequency[26]!=0){      // bo�luk icin en son kontrol ediyorum
		temp=head;
		while(temp->next!=NULL){
			temp=temp->next;
			}
		temp->next=create_node();
		temp->next->harf=' ';
		temp->next->frequency=frequency[i];
		}
				
		
	
}
void printlist(NODE *head){        //link listeyi ba�tan sonra yazd�rmak i�in yazd���m basit fonksiyon
	head=head->next;
	while(head!=NULL){
		printf("%c: %d  " ,head->harf,head->frequency);
		head=head->next;
	}
	printf("\n");
}

	
void swap(NODE *min,NODE *temp){   //insertion sort ile linked listi s�ralarken  yerlerinin de�i�imi icin kullan�lan fonksiyon	
	char s;                     // adreslerini birbiriyle de�i�tirmektense sadece harf isimlerini ve s�kl�klar�n� de�i�tiriyorum
	int x;                      // frekans ve harf ismini tutabilmek icin temp de�i�kenler
	s=min->harf;
	x=min->frequency;
	min->harf=temp->harf;
	min->frequency=temp->frequency;
	temp->harf=s;
	temp->frequency=x;
}
void insertion_sort_for_linkedlist(NODE*head){ //linked list s�ralam fonskiyonu
	NODE *min,*temp,*temp1;    // temp  array dizisinin i si  temp1 arrayin j si olarak d���n�lebilir farkl� bi�ey yok 
	for(temp=head->next;temp->next!=NULL;temp=temp->next){
		min=temp;
		for(temp1=temp->next;temp1!=NULL;temp1=temp1->next){
			
			if(temp1->frequency<min->frequency){        // link listed sonuna kadar en k�c�k elaman� bulmak icin 
				min=temp1;
			}
		}
		swap(min,temp);        // bulunan k�c�k frekansl� node yer de�i�imi icin yollan�yor 
		
	}
	
}
void insert(NODE *head,NODE *new_node){ //  birle�en frekans nodelari icin
	head=head->next;
	int flag=1;
	
	while(new_node->frequency>=head->next->frequency && head->next->next!=NULL ){ //new node un frekans� eklenecege node un frekans�ndan k�c�k olana kadar gidicez
			head=head->next;                                                                	// bunu yaparken listenin sonuna gelip gelmedi�imizi anlamak icin 2. bir kontrol yap�yoruz 
	
	}
	if(head->next->next!=NULL){     //��k�� sebebimize bak�yoruz
	new_node->next=head->next;
	head->next=new_node;}
	else if(new_node->frequency > head->next->frequency ){   // next->next null ise son elaman kontrolunu yapmadan c�k�yoruz onu kontrol ediyoruz
		head->next->next=new_node;   
		
		
	}
	else{
		  new_node->next=head->next;
		head->next=new_node;      // yukardaki durumlar ger�ekle�mediyse bu de�er en sondaki elamandan k�c�k demektir
	}
	
	

}
void last_shoot(NODE *head){
	NODE*temp=head;  
	head=head->next;
	while(head->next!=NULL){
		
		NODE *q=create_node();     
		q->left=head;                   //ilk elaman� sola al�yoruz  
		q->right=head->next;	//2.elaman� saga al�yoruz 
		q->frequency=head->frequency+head->next->frequency;     // frekans toplamlar�n� s�yle e�itlyirouz
		insert(temp,q);                  // bu  elaman�n yerini bulmak icin copy bi headten yollyuruz ki d�zeni bozmas�n asil headi yollarsak d�zen bozulmas�n
		head=head->next->next;
	}
}
int find_h(NODE* head)  // agac�n maksumun yuksekli�ini bulan fonks�yon
{  
    if (head == NULL){
			
        return 0;  }
    else
    {  

        int l_h = find_h(head->left);  // en sola gidiyoruz 
        int r_h = find_h(head->right);  // en soldan en sa�a yukar� do�ru d�nerek gidiyoruz
      
        if (l_h > r_h)                // a��a��dan yukara�ya en derin nodedan  geri d�nerken node seviyesi derin olan�n y�ksekli�ini bast�r�yoruz
            return(l_h + 1);  
        else return(r_h + 1); 
	}
}

int find_height_of_tree(NODE *head){ // agac�n son elaman�na  Roota kadar gidip rootu find_h fonks�yonuna yollayan fonskiyon cok basit 
	while(head->next!=NULL){                   
		head=head->next;
	}
	int height;
	NODE *temp=head;
	height=find_h(head);
	return height;
}

void printGivenLevel( NODE* head, int level)        // level level dolanarak  nodelar�n de�erlerini ve tuttuklar� harfleri bast�ran fonksiyon
{ 
    if (head == NULL ){     // eger null bir node a denk geldiysek null  bastiriyoruz
    	int i=1,sinir=2;
    	if(level<3){
		
    	for(i;i<=level;i++) // nulla denk geldi�imizde daha son node de�ilse alt�ndaki leveldeyse onun adedince null basmak icin i den levele gidene kadar null bas�yoruz
    	printf("nl ");}
		else{
			for(i=1;i<=level-2;i++) // eger null geldiyse ve level 3ten fazlaysa cocuklar� i�in 2* �eklinde artmas� laz�m 
			sinir*=2;
			for(i=1;i<=sinir;i++)
			printf("nl ");
		};
        return; }
    if (level == 1){
		if(head->harf!=NULL)
        printf("%d-%c ", head->frequency,head->harf);    // level 1 e geldiysek istenilen derinlikteyiz demektir  nodu yazd�r�yoruz  harfi varsa onu da yazd�r�yozu
        else
		printf("%d ",head->frequency);
	}
    else if (level > 1) 
    { 
    	
        printGivenLevel(head->left, level-1);   // gerekli node a ula�mak icin sola  ve sa��na gidiyoruz level d���re d���re
        printGivenLevel(head->right, level-1); 
    } 
} 
void printLevelOrder( NODE* head,int h) 
{  
    int i; 
    for (i=1; i<=h; i++) 
    { 
        printGivenLevel(head, i);   
        printf("\n"); 
    } 
} 
  
int main(){
	
	NODE *head;
	NODE *heat[60];
	head=create_node();
	int i,j,frequency[27]={0},h;
	char str[300];
	printf("Enter the text : ");
	gets(str);
	find_frequency(str,frequency);
	frequency_to_linklisted(frequency,head);
	printf("\n\nMetnin harf frekansi \n \n");
	printlist(head);
	insertion_sort_for_linkedlist(head);
	printf("\n\nAfter sort \n \n");
	printlist(head);
	last_shoot(head);
	printf("\n\nAFTER HUFFMAN\n ");
	printlist(head);
	printf("\n\n");
	h=find_height_of_tree(head);
	while(head->next!=NULL){
		head=head->next;
	}
	printf("Agac hali \n\n");
	printLevelOrder(head,h);	
 	

	

	
	return 1;
}
