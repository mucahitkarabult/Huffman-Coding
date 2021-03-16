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
		if(str[i]!=32)	            // dizinin elamaný boþluk mu diye kontrol ediyoruz çünkü boþluk beným algoritma tasarýmým icin istisna bi durum 
		frequency[(str[i]-'a')]++;	// kücük harfli elamanlardan  'a' cýkardýðýmýzda boþluk haric dizide yerleþiceði yerlerden 'a'+i þeklinde bir geri dönüþ saðlayabileceðimden
		 								               // frekansý bu þekilde buluyorum boþluk icin ascýý karþýlýðý  32 yi ayrý tutup ifle kontrol ediyorum
		else{
		frequency[26]++;}
	}
}
NODE * create_node(){
	NODE *x;
	x=(NODE*)malloc(sizeof(NODE));
	if(x==NULL)	                         //Malloc sonucu ramde yer acýlmamasý durumu
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
		for(i=0;i<26;i++){         //boþluk dahil deðil
			if(frequency[i]!=0){            // frekansý dizisinde sadece  0  farklý olan indis karþýlýðý harf texte geçiyor demektir 
				if(head->next==NULL){        // linkli liste daha oluþmuþ mu diye kontrol ediyorum
					NODE *temp =create_node();
					head->next=temp;                    
					temp->harf='a'+i;             // yukarda bahsettiðim gibi geri dönüþ saðlýyorum
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
	if(frequency[26]!=0){      // boþluk icin en son kontrol ediyorum
		temp=head;
		while(temp->next!=NULL){
			temp=temp->next;
			}
		temp->next=create_node();
		temp->next->harf=' ';
		temp->next->frequency=frequency[i];
		}
				
		
	
}
void printlist(NODE *head){        //link listeyi baþtan sonra yazdýrmak için yazdýðým basit fonksiyon
	head=head->next;
	while(head!=NULL){
		printf("%c: %d  " ,head->harf,head->frequency);
		head=head->next;
	}
	printf("\n");
}

	
void swap(NODE *min,NODE *temp){   //insertion sort ile linked listi sýralarken  yerlerinin deðiþimi icin kullanýlan fonksiyon	
	char s;                     // adreslerini birbiriyle deðiþtirmektense sadece harf isimlerini ve sýklýklarýný deðiþtiriyorum
	int x;                      // frekans ve harf ismini tutabilmek icin temp deðiþkenler
	s=min->harf;
	x=min->frequency;
	min->harf=temp->harf;
	min->frequency=temp->frequency;
	temp->harf=s;
	temp->frequency=x;
}
void insertion_sort_for_linkedlist(NODE*head){ //linked list sýralam fonskiyonu
	NODE *min,*temp,*temp1;    // temp  array dizisinin i si  temp1 arrayin j si olarak düþünülebilir farklý biþey yok 
	for(temp=head->next;temp->next!=NULL;temp=temp->next){
		min=temp;
		for(temp1=temp->next;temp1!=NULL;temp1=temp1->next){
			
			if(temp1->frequency<min->frequency){        // link listed sonuna kadar en kücük elamaný bulmak icin 
				min=temp1;
			}
		}
		swap(min,temp);        // bulunan kücük frekanslý node yer deðiþimi icin yollanýyor 
		
	}
	
}
void insert(NODE *head,NODE *new_node){ //  birleþen frekans nodelari icin
	head=head->next;
	int flag=1;
	
	while(new_node->frequency>=head->next->frequency && head->next->next!=NULL ){ //new node un frekansý eklenecege node un frekansýndan kücük olana kadar gidicez
			head=head->next;                                                                	// bunu yaparken listenin sonuna gelip gelmediðimizi anlamak icin 2. bir kontrol yapýyoruz 
	
	}
	if(head->next->next!=NULL){     //çýkýþ sebebimize bakýyoruz
	new_node->next=head->next;
	head->next=new_node;}
	else if(new_node->frequency > head->next->frequency ){   // next->next null ise son elaman kontrolunu yapmadan cýkýyoruz onu kontrol ediyoruz
		head->next->next=new_node;   
		
		
	}
	else{
		  new_node->next=head->next;
		head->next=new_node;      // yukardaki durumlar gerçekleþmediyse bu deðer en sondaki elamandan kücük demektir
	}
	
	

}
void last_shoot(NODE *head){
	NODE*temp=head;  
	head=head->next;
	while(head->next!=NULL){
		
		NODE *q=create_node();     
		q->left=head;                   //ilk elamaný sola alýyoruz  
		q->right=head->next;	//2.elamaný saga alýyoruz 
		q->frequency=head->frequency+head->next->frequency;     // frekans toplamlarýný söyle eþitlyirouz
		insert(temp,q);                  // bu  elamanýn yerini bulmak icin copy bi headten yollyuruz ki düzeni bozmasýn asil headi yollarsak düzen bozulmasýn
		head=head->next->next;
	}
}
int find_h(NODE* head)  // agacýn maksumun yuksekliðini bulan fonksýyon
{  
    if (head == NULL){
			
        return 0;  }
    else
    {  

        int l_h = find_h(head->left);  // en sola gidiyoruz 
        int r_h = find_h(head->right);  // en soldan en saða yukarý doðru dönerek gidiyoruz
      
        if (l_h > r_h)                // aþþaðýdan yukaraýya en derin nodedan  geri dönerken node seviyesi derin olanýn yüksekliðini bastýrýyoruz
            return(l_h + 1);  
        else return(r_h + 1); 
	}
}

int find_height_of_tree(NODE *head){ // agacýn son elamanýna  Roota kadar gidip rootu find_h fonksýyonuna yollayan fonskiyon cok basit 
	while(head->next!=NULL){                   
		head=head->next;
	}
	int height;
	NODE *temp=head;
	height=find_h(head);
	return height;
}

void printGivenLevel( NODE* head, int level)        // level level dolanarak  nodelarýn deðerlerini ve tuttuklarý harfleri bastýran fonksiyon
{ 
    if (head == NULL ){     // eger null bir node a denk geldiysek null  bastiriyoruz
    	int i=1,sinir=2;
    	if(level<3){
		
    	for(i;i<=level;i++) // nulla denk geldiðimizde daha son node deðilse altýndaki leveldeyse onun adedince null basmak icin i den levele gidene kadar null basýyoruz
    	printf("nl ");}
		else{
			for(i=1;i<=level-2;i++) // eger null geldiyse ve level 3ten fazlaysa cocuklarý için 2* þeklinde artmasý lazým 
			sinir*=2;
			for(i=1;i<=sinir;i++)
			printf("nl ");
		};
        return; }
    if (level == 1){
		if(head->harf!=NULL)
        printf("%d-%c ", head->frequency,head->harf);    // level 1 e geldiysek istenilen derinlikteyiz demektir  nodu yazdýrýyoruz  harfi varsa onu da yazdýrýyozu
        else
		printf("%d ",head->frequency);
	}
    else if (level > 1) 
    { 
    	
        printGivenLevel(head->left, level-1);   // gerekli node a ulaþmak icin sola  ve saðýna gidiyoruz level düþüre düþüre
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
