#include<stdio.h>
#include<string.h> 
#include<stdlib.h>
#include<windows.h>

int bookKinds=0;//��ͬ�����鼮�������� 

typedef struct Node
{
	char libraryCard[12];//����֤�� 
	int year;//��� 
	int month;//�·� 
	int date;//���� 
	struct Node *Next;
	struct Node *Last;
}borrowInfo;//������Ϣ�� 

typedef struct node
{
	char bookNumber[16];//��� 
	char title[30];//���� 
	char author[30];//���� 
	int inventory;//��������� 
	int standingCrop;//�ɽ������� 
	borrowInfo *borrow;//������Ϣ�� 
	struct node *last;
	struct node *next;
}wareHouse;//�鼮��Ϣ 

void functionList(void);//ͼ�����ϵͳʹ��ָ���б�  
void storage(wareHouse *library);//���������� 
void borrowBooks(wareHouse *library);//�鼮���Ĺ��� 
void returnBooks(wareHouse *library);//�鼮�黹���� 
void infoBook(wareHouse *library);// �鼮�����Ϣ��ѯ��  
void writeToText(wareHouse *library); //�ⲿ.txt�ļ��洢��Ϣ�� 
int stringComparison(char *a,char *b);//�ַ����Աȣ�
wareHouse *search(wareHouse *library);//�鼮������
wareHouse *addFromText(void);//���ⲿ.txt�ļ���ȡ�洢��Ϣ ��

int main(void)
{
	wareHouse *library;//ͼ��� 
	library=addFromText();//��ȡ�ļ���Ϣ�� 
	printf("__________________________________________________________________________\n\n");
	printf("\n��ӭʹ��ͼ�����ϵͳ���밴����ʾ������\n\n");
	printf("__________________________________________________________________________\n\n");
	Sleep(1500);//һ���������棬������ȡ���� 
	system("cls");
	functionList();//����ָ�ϣ� 
	printf("��ȷ������Ҫʹ�õĹ��ܣ�");
	char functions;
	while(~scanf("%c",&functions))//����ѡ�� 
	{
		if(functions=='#')
		{
			system("cls");
			writeToText(library);//������Ϣ��.txt�ļ��У� 
        	printf("\n\n         ϵͳ�ɹ��˳�����л����ʹ��^_^\n");
        	break;
        }
		else
		{
			switch(functions)
			{
				case '1':storage(library);//���������� 
					break;
				case '2':borrowBooks(library);//�鼮���Ĺ��� 
					break;
				case '3':returnBooks(library);//�鼮�黹���� 
					break;
				case '4':infoBook(library);//�鼮�����Ϣ��ѯ��  
					break;
				default:printf("���棡���������������\n");//��������ѣ� 
			}
			if(functions=='1'||functions=='2'||functions=='3'||functions=='4'||functions=='#')	system("pause");
			system("cls");
			functionList(); 
			printf("����������Ҫʹ�õĹ��ܣ�");
		} 
	}
	return 0;
} 


void functionList(void)
{	
	printf("__________________________________________________________________________\n\n");
	printf("ͼ�����ϵͳʹ��ָ�ϣ�\n");
	printf("�鼮��⣺\t\t\t�밴��1��\n");
	printf("�鼮���ģ�\t\t\t�밴��2��\n");
	printf("�鼮�黹��\t\t\t�밴��3��\n");
	printf("�鼮���ң�\t\t\t�밴��4��\n");
	printf("�˳�ϵͳ��\t\t\t�밴��#��\n"); 
	printf("__________________________________________________________________________\n");
}

int stringComparison(char *a,char *b)
{
	int i,flag=1;
	for(i=0;i<strlen(a); i++)
		if(a[i]!=b[i])
		{
			flag=0;
			break;
		}
	return flag;
}

void storage(wareHouse *library)
{
	getchar();
	system("cls");
	printf("__________________________________________________________________________\n\n");
	printf("ͼ����鼮������\n");
	printf("__________________________________________________________________________\n\n");
	int flag=0;
	wareHouse *p,*news;
	p=library;
	news=(wareHouse *)malloc(sizeof(wareHouse));
	printf("��������������(15λ���ڣ�������)��");
	scanf("%s",news->bookNumber);
	printf("�����������������");
	scanf("%s",news->title);
	printf("��������������ߣ�");
	scanf("%s",news->author);
	printf("�����������������");
	scanf("%d",&news->inventory);
	news->standingCrop = news->inventory;
	news->borrow=NULL;
	news->next=NULL;
	while(p->next!=NULL) 
	{
		p=p->next;
		if(stringComparison(news->bookNumber,p->bookNumber)==1)
		{
			flag=1;
			break;
		}
	}
	if(flag==1)//�����Ѵ��ڣ����޸��鼮�Ŀ�������ִ����� 
	{
		p->inventory +=news->inventory;
		p->standingCrop += news->standingCrop;
	}
	else//����δ���ڣ�����⣬�������Ŀ�����ݣ� 
	{
		p->next = news;
		news->last =p;
		bookKinds++;
	}
	printf("\n�鼮�������ɹ�\n");
} 

wareHouse *search(wareHouse *library)//�鼮�������ɰ�����Ż������������鼮�Ƿ���ڣ� 
{
	wareHouse *p,*q;
	p=library;
	q=(wareHouse *)malloc(sizeof(wareHouse));
	q=NULL;
	int searchBy; 
	printf("���ò��ҷ�ʽ��\n"); 
	printf("����Ų����밴��1��\n"); 
	printf("�����������밴��2��\n"); 
	printf("����ѡ���ǣ�"); 
	scanf("%d",&searchBy);
	getchar();
	if(searchBy==1||searchBy==2)
	{
		if(searchBy==1)
		{
			char chose[16];
			printf("������Ҫ���ҵ���ţ�");
			scanf("%s",chose);
			while(p->next!=NULL)
			{
				p=p->next;
				if(stringComparison(chose,p->bookNumber)==1)
				{
					q=p;
					break;
				}
			}
		}
		else
		{
			char chose[30];
			printf("������Ҫ���ҵ�������");
			scanf("%s",chose);
			while(p->next!=NULL)
			{
				p=p->next;
				if(stringComparison(chose,p->title)==1)
				{
					q=p;
					break;
				}
			}
		}
		if(q==NULL) printf("���鲻���ڡ�\n");
	}
	else printf("���棡���������������\n");
	return q;
}

void borrowBooks(wareHouse *library)
/*�鼮����ʱ����Ҫ��д������Ϣ����������֤�š��ꡢ�¡��գ������浽�鼮��Ϣ�У�ͬʱ�޸ı����鼮���ִ�����*/ 
{
	getchar();
	system("cls");
	printf("__________________________________________________________________________\n\n");
	printf("ͼ����鼮���Ĺ���\n");
	printf("__________________________________________________________________________\n\n");
	wareHouse *p,*q;
	p=library;
	q=search(p); 
	if(q!=NULL) 
	{
		if(q->standingCrop==0)  printf("���鼮�ɽ�����Ϊ0���޷������ġ�\n");
		else
		{
			q->standingCrop--;
			getchar();
			borrowInfo *news,*s;
			news=(borrowInfo *)malloc(sizeof(borrowInfo));
			printf("���������Ľ���֤��(10λ):"); 
			scanf("%s",news->libraryCard); 
			printf("����д���Ĺ黹���ڣ�\n");
			printf("�꣺");
			scanf("%d",&news->year); 
			printf("�£�");
			scanf("%d",&news->month);
			printf("�գ�");
			scanf("%d",&news->date);
			news->Next=NULL;
			news->Last=NULL;
			if(q->borrow==NULL)	q->borrow=news;
			else
			{
				s=q->borrow;
				while(s->Next!=NULL) s=s->Next;
				s->Next = news;
				news->Last = s;	
			}
			printf("\n�鼮���Ĳ����ɹ���\n"); 
		}
	} 
}

void infoBook(wareHouse *library)
/*�ɲ鿴�鼮�Ŀ����Ϣ�������鱻���Ĺ�����ͬʱ�г�������Ϣ*/ 
{
	getchar();
	system("cls");
	printf("__________________________________________________________________________\n\n");
	printf("ͼ����鼮��Ϣ��������\n");
	printf("__________________________________________________________________________\n\n");
	wareHouse *p,*q;
	p=library;
	q=search(p); 
	if(q!=NULL) 
	{
		system("cls");
		printf("�Ȿ�鼮����ϢΪ��\n\n\n"); 
		printf("��ţ�%s\n",q->bookNumber);
		printf("������%s\n",q->title);
		printf("���ߣ�%s\n",q->author);
		printf("���������%d\n",q->inventory);
		printf("�ɽ�������%d\n",q->standingCrop);
		if(q->borrow!=NULL)
		{
			printf("\n");
			borrowInfo *s;
			s=q->borrow;
			int i=1;
			while(s!=NULL)
			{
				printf("��%d������֤��\n",i);
				printf("��֤���룺%s\n",s->libraryCard);
				printf("�黹���ڣ�%d��%d��%d��\n\n",s->year,s->month,s->date); 
				s=s->Next;
				i++;
			}
		}
	}
} 

void returnBooks(wareHouse *library)
/*�鼮�黹������������ڸ��鱾�Ľ�����Ϣ��ͬʱ�鼮���ִ���+1*/ 
{
	getchar();
	system("cls");
	printf("__________________________________________________________________________\n\n");
	printf("ͼ����鼮�黹����\n");
	printf("__________________________________________________________________________\n\n");
	wareHouse *p,*q;
	p=library;
	q=search(p); 
	if(q!=NULL)
	{
		getchar();
		borrowInfo *s,*r;
		char returns[12];
		s=q->borrow;
		r=NULL;
		printf("���������Ľ���֤��(10λ):"); 
		scanf("%s",returns); 
		while(s!=NULL)
		{
			if(stringComparison(returns,s->libraryCard)==1)
			{
				r=s;
				q->standingCrop++;
				break;
			}
			s=s->Next;
		}
		if(r!=NULL)
		{ 	
			if(r->Last==NULL&&r->Next==NULL) q->borrow=NULL;
			if(r->Last==NULL&&r->Next!=NULL) 
			{
				q->borrow=r->Next;
				q->borrow->Last=NULL;
			}
			if(r->Next==NULL&&r->Last!=NULL)  r->Last->Next=NULL;
			if(r->Last!=NULL&&r->Next!=NULL) 
			{
				r->Last->Next =r->Next;
				r->Next->Last =r->Last;
			}
			free(r);
			printf("\n�鼮�黹�����ɹ���\n"); 
		}
		else printf("û�д˽�����Ϣ��\n");
	} 
} 

wareHouse *addFromText(void)
/*��.txt�ļ��ж�ȡ��Ϣ��*/
{
	FILE *fp;
	fp=fopen("D:\\bookManagement.txt","rb");/*���ļ����ڣ����*/ 
	if(fp==NULL)	bookKinds=0;
	int i=0,j=0;
	wareHouse *p,*library;
	p=library=(wareHouse *)malloc(sizeof(wareHouse));
	library->next=NULL;
	library->last=NULL;
	fscanf(fp,"%d",&bookKinds); 
	i=bookKinds;
	while(i--)
	{
		wareHouse *q;
		q=(wareHouse *)malloc(sizeof(wareHouse));
		q->last=NULL;
		q->next=NULL;
		fscanf(fp,"%s %s %s %d %d",q->bookNumber,q->title,q->author,&q->inventory,&q->standingCrop);
		j=q->inventory - q->standingCrop;
		q->borrow=NULL;
		borrowInfo *r=NULL;
		while(j--)
		{
			borrowInfo *s;
			s=(borrowInfo *)malloc(sizeof(borrowInfo));
			s->Next=NULL;
			s->Last=NULL;
			fscanf(fp,"%s %d %d %d",s->libraryCard,&s->year,&s->month,&s->date);
			if(r==NULL) r=s;
			else
			{
				r->Next=s;
				s->Last=r;
				r=r->Next;
			}
		}
		if(r!=NULL)
		{
			while(r->Last!=NULL) r=r->Last;
			q->borrow=r;
		}
		p->next=q;
		q->last=p;
		p=p->next;
		
	}
	fclose(fp);/*�ر��ļ�*/ 
	return library;
}

void writeToText(wareHouse *library)
{
	FILE *fp;
	fp=fopen("D:\\bookManagement.txt","wb");/*���ļ����ڣ���򿪣������ڹ涨·���½�һ��ͬ�����ļ���*/ 
	int i=0,j=0;
	wareHouse *p;
	p=library;
	i=bookKinds;
	fprintf(fp,"%d\n",bookKinds);
	while(i--)
	{
		p=p->next;
		fprintf(fp,"%s %s %s %d %d\n",p->bookNumber,p->title,p->author,p->inventory,p->standingCrop);
		borrowInfo *s;
		s=p->borrow;		
		while(s!=NULL)
		{
			fprintf(fp,"%s %d %d %d\n",s->libraryCard,s->year,s->month,s->date);
			s=s->Next;
		}
	}
	printf("�����ѱ�����ļ��С�\n"); 
	fclose(fp);/*�ر��ļ�*/ 
}
