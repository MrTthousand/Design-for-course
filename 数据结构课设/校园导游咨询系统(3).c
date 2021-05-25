#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#define INFINITY 10000
#define M 40                                                    /*��󶥵���*/
typedef struct {
	int num;                                                    /*�������*/
	char name[20];                                              /*��������*/
	char intro[200];                                            /*������*/
}information;

typedef int edgtype;                                            /*Ȩֵ����*/
typedef struct {                                                /*У԰����ͼ�ṹ��*/
	information vexs[M];                                         /*������Ϣ��*/
	edgtype edge[M][M];                                         /*�ڽӾ���*/
	int vexNum, edgNum;                                         /*�������ͱ���*/
}matrix;

int menu();                                                     /*���˵�*/
void Createmap(matrix *g);                                 /*���ļ���ȡ��Ϣ����ͼ*/
void Print_Map();                                               /*��ʾУ԰�����ͼ*/
int Judge(int num);                                       /*�ж�����ı���Ƿ����*/
void searchinfo(matrix *g);                            /*������Ϣ��ѯ*/
void shortPath(matrix *g);                                  /*�󾰵�����·��*/
void Floydprint(matrix *g, int s, int e);            		/*�ݹ��ӡ��������·��*/
void shortpath_Print(matrix *g);                            /*�������ӡ���������·��*/
void Dfs(matrix *g, int s, int e);             		/*������ȱ�����ѯ�����������·��*/
void Allpath_Print(matrix *g);                              /*��ѯ������������·������ӡ*/
void BestPath(matrix *g);                                   /*�ඥ��������·��*/
void Exit();                                      				 /*�˳�ϵͳ*/
void Information_print();					/*�������Ĵ�ӡ*/ 
void Manager();							/*����Ա����*/ 
int Login_system();							/*ϵͳ������*/ 
void scenicManager(matrix *g); /*�Ծ���Ĺ���*/ 
int Login();   /*����Ա��¼*/ 
void searchinfo(matrix *g);  /*������Ϣ��ѯ*/ 
 
/*У԰����ͼ�Ķ�ȡ�봴��*/
void Createmap(matrix *g)
{
	int i, j, k, e;
	FILE *rf;
	rf = fopen("map.txt", "r");
	if (rf)
	{
		fscanf(rf, "%d%d", &g->vexNum, &g->edgNum);
		for (i = 0; i < g->vexNum; i++)
			fscanf(rf, "%d%s%s", &g->vexs[i].num, g->vexs[i].name, g->vexs[i].intro);
		for (i = 0; i < g->vexNum; i++)
			for (j = 0; j < g->vexNum; j++)
			{
				if (i == j)
					g->edge[i][j] = 0;
				else
					g->edge[i][j] = INFINITY;
			}
		for (k = 0; k < g->edgNum; k++)
		{
			fscanf(rf, "%d%d%d", &i, &j, &e);
			g->edge[i-1][j-1] = g->edge[j-1][i-1] = e;
		}
		fclose(rf);
	}
	else
		g->edgNum = 0;
}

/*У԰����ͼ����ʾ*/
void Dis_Map() {
	printf("\n                                                                      ���㶫�����ѧУ԰�����ͼһ����                                                  \n\n");
	printf("            *200*                           *200*                      *150*           *100*                   *100*                                                    \n"); 
	printf("(34)��������=============(33)���ķ���====================(32)����������====(29)УҽԺ=============(30)�ֹ�¥===========(31)����ѵ������====================                   \n");
	printf("       ||                                                                     *200*||                                                              ||*250*                        \n");	
	printf("       ||                                                                          ||        *80*                                                  ||                        \n");
	printf("       ||                                                                         (27)����¥====(28)����ʵ��¥                                     ||                        \n");
	printf("       || *300*                                                                    ||                                                              ||						   \n");
	printf("       ||                                                                     *50* ||                                                               ==============					   \n");
	printf("       ||                                                         *150*       (26)�Ƽ�¥                                                            ||    ��    ||					   \n");
	printf("       ||                                          (25)����ʳ��================|| *80*                                                              ||    ��    ||				       \n");
	printf("       ||        *300*                                *100*  ||	   *150*(22)�Ӻ�¥A    *50*               *50*              *30*             *100*  ||          ||*100*					   \n");
	printf("(35)����¥===========================================(24)�ڶ���ѧ¥ ===========||*10*=======(16)���Ĺ㳡========(17)ͼ���========(18)������========||          ||=======(20)�ڶ����� \n");
	printf("       ||                                                   ||	       (23)�Ӻ�¥B            ||              	||                 ||               ||   (19)   ||               ||    \n");
	printf("       ||                                              *100*||                                ||*30*            ||                 ||*40*           ||          ||          *150*||    \n");
	printf("       ||                                           (13)�̹�ʳ��                       (14)����ѧ¥             ||*50*             ||               ||          ||               ||    \n");
	printf("       || *300*                                             ||                                ||                ||                 ||               ||    ��    ||         (21)������  \n");
	printf("       ||                                                   ||*100*             *5*       *40*||     *5*        ||    *30*         ||       *80*    ||    ��    ||               ||    \n");
	printf("       ||         *200 *                     (12)�̹�����=========(7)��ũ¥===========(9)����㳡=======(8)�˺�¥===========��һ����(15)=========================                ||     \n");
	printf("(36)������====================================/             ||            ||                                    ||             ��ҵ����(15)                                 *200*||    \n");
	printf("       ||                            *200                   ||*150*       ||*20*        *50*                *30*||     *20*              ||*30*                                  ||  \n");
	printf("       ||===================================(11)ˮ�������===========(5)����¥=============================(6)�˽�¥==================(10)ˮ��¥                                 ||   \n");
	printf("       ||                                      ||          *200*                     *50*  || *50*                         *60* || *10*        || *30*                           ||\n");
	printf("       ||                                      || *250*                                    ||=======================================================||=============================                              \n");
	printf("       ||=======================================================================(2)������  || ������     *80*               (3)��Ӿ��   *50*       (4) ����                              \n");
	printf("         *400*                                                                        *10* ||                                                                                     \n");
	printf("                                                                                   (1) �㶫�����ѧ���ſ�                                                                          \n\n");

  

}

/*������Ϣ��ѯ*/
void searchinfo(matrix *g) {
	int s;
	do {
		printf("\n��������Ҫ���ҵľ����ţ�");
		scanf("%d", &s);
	} while (Judge(s));
	printf("\n�������ƣ�[%s]\n\n", g->vexs[s - 1].name);
	printf("�����飺 %s\n\n", g->vexs[s - 1].intro);
}

/*Floyd�㷨����������һ����̵�·��*/
int dist[M][M];                                                    /*��������*/
int path[M][M];                                                    /*·������*/
void shortPath(matrix *g) {
	int i, j, k;
	for (i = 0; i < g->vexNum; i++)                                /*��ʼ����������������·����������*/
		for (j = 0; j < g->vexNum; j++) {
			dist[i][j] = g->edge[i][j];
			if (i != j && dist[i][j] < INFINITY) path[i][j] = i;
			else path[i][j] = -1;                                  /*-1����ǰ���㲻�ɴ�*/
		}
	for (k = 0; k < g->vexNum; k++)                                /*�������ÿ����������·��*/
		for (i = 0; i < g->vexNum; i++)
			for (j = 0; j < g->vexNum; j++)                        /*����dist[i][j]��ֵ*/
				if (dist[i][j] >(dist[i][k] + dist[k][j])) {
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = k;                                /*path���ڼ�¼���·���ϵľ����*/
				}
}

/*�ݹ�ʵ�ִ�ӡ���������·��*/
void Floydprint(matrix *g, int s, int e) {
	if (path[s][e] == -1 || path[s][e] == e || path[s][e] == s)
		return;
	else {
		Floydprint(g, s, path[s][e]);                 /*���м����Ϊ�յ������ӡ·��*/
		printf("%s->", g->vexs[path[s][e]].name);         /*��ӡ�м侰������*/
		Floydprint(g, path[s][e], e);                 /*���м����Ϊ��������ӡ·��*/
	}
}

/*�������ӡ���������·��*/
void shortpath_Print(matrix *g) {
	int s, e;                                             /*����ţ��յ���*/
	do {
		printf("\n����������ţ�");
		scanf("%d", &s);
	} while (Judge(s));
	do {
		printf("\n�������յ��ţ�");
		scanf("%d", &e);
	} while (Judge(e));
	printf("\n%s��%s����̾����ǣ�%dm\n", g->vexs[--s].name, g->vexs[--e].name, dist[s-1][e-1]);
	printf("\n�����������·�ߣ�");
	printf("%s->", g->vexs[s].name);                                       /*���·���ϵ����*/
	Floydprint(g, s, e);                                               /*���·���ϵ��м��*/
	printf("%s\n\n", g->vexs[e].name);                                     /*���·���ϵ��յ�*/
}


/*������ȱ�����ѯ������������֮�������·��*/
int pathstack[M];                                                             /*·��ջ���洢·����Ϣ*/
int top;                                                                      /*ջ��*/
int visited[M];                                                               /*��ջ��ǣ���ֹ�γɻ�·*/
int count;                                                                    /*·��������*/
void Dfs(matrix *g, int s, int e) {
	int dis = 0;                                                              /*���ڼ�¼·������*/
	pathstack[top] = s;                                                    /*�����������ջ*/
	top++;
	visited[s] = 1;
	int i;                                                        /*����ջ����Ϊ����ջ*/
	for ( i = 0; i < g->vexNum; i++) {
		if (g->edge[s][i] > 0 && g->edge[s][i] != INFINITY && !visited[i]) {
			/*����ǰһ����ջ����õ�ɴ�Ҹõ�δ��ջ��δ�����ʣ�*/
			if (i == e) {                                                  /*�����ȱ����ѵ����յ㣬������ղŵ�·��*/
				if(count==4){
					return;
				} 
				printf("��%d��·:", count++);
				int j;
				for ( j = 0; j < top; j++) {
					printf("%s->", g->vexs[pathstack[j]].name);
					if (j < top - 1)
						dis = dis + g->edge[pathstack[j]][pathstack[j + 1]];        /*ͳ��·������*/
				}
				dis = dis + g->edge[pathstack[top - 1]][e];                      /*���һ��·������������Ϊe������ջ*/
				printf("%s\n", g->vexs[e].name);
				printf("�ܳ����ǣ�%dm\n\n", dis);
			}
			else {
				Dfs(g, i, e);                                              /*����õ㲻���յ�,�����������*/
				top--;                                                              /*֧·ȫ������һ��󣬶����ջ*/
				visited[i] = 0;                                                     /*����ջ����Ϊ�ѳ�ջ�������´η���*/
			}
		}
	}
			
}

/*��ѯ������������֮�������·������ӡ*/
void Allpath_Print(matrix *g) {
	int s, e;
	count = 1;                                                       /*·��������*/
	top = 0;                                                         /*ջ��*/
	memset(pathstack, 0, sizeof(pathstack));                         /*·��ջ��ʼ��*/
	memset(visited, 0, sizeof(visited));                             /*��ջ��ǳ�ʼ��*/
	do {
		printf("\n����������ţ�");
		scanf("%d", &s);
	} while (Judge(s));
	do {
		printf("\n�������յ��ţ�");
		scanf("%d", &e);
	} while (Judge(e));
	printf("\n");
	Dfs(g, s - 1, e - 1);
}

/*�ྰ��������·��*/
void BestPath(matrix *g) {
	int vNum[M] = { 0 }, j = 1;                                       /*��¼�û�����ı����Ϣ*/
	int d = 0;                                                        /*ͳ��ȫ���ܳ�*/
	printf("\n��������Ҫ�����ĵ�%d������ı�ţ�����-1�������룩��", j);
	scanf("%d", &vNum[j - 1]);
	while (vNum[j - 1] != -1 && j < 12) {
		while (Judge(vNum[j - 1])) {
			printf("\n��������Ҫ�����ĵ�%d�������ţ�", j);
			scanf("%d", &vNum[j - 1]);
		}
		if (vNum[j - 1] == -1) break;
		printf("\n��������Ҫ�����ĵ�%d�������ţ�", ++j);
		scanf("%d", &vNum[j - 1]);
	}
	printf("\n������ѷ���·����");
	int i=0;
	for ( i = 0; vNum[i] > 0 && vNum[i + 1] > 0; i++) {
		printf("%s->", g->vexs[vNum[i] -1].name);                   /*���·���ϵ����*/
		Floydprint(g, vNum[i]-1 , vNum[i + 1]-1 );                /*����Floyd�㷨*/
		d += dist[vNum[i] ][vNum[i + 1] -1];
	}
	printf("%s\n\n", g->vexs[vNum[j - 2] - 1].name);                 /*���·���ϵ��յ�*/
	printf("ȫ���ܳ�Ϊ��%d\n\n", d);
}

/*���˵�*/
 int menu() {
	int s;
	printf("\t\t��              ��--------------------------------------��                \n");
	printf("\t\t��--------------�� ��ӭʹ�ù㶫�����ѧУ԰������ѯϵͳ ��-----------------��\n");
	printf("\t\t��              ��--------------------------------------��              \t��\n");
	printf("\t\t��                                                                      \t��\n");
	printf("\t\t��                                                                      \t��\n");
	printf("\t\t��   ��------------------------��        ��------------------------��   \t��\n");
	printf("\t\t��   ��1.����У԰������Ϣ��ѯ  ��        �� 2.����������·����ѯ ��   \t��\n");
	printf("\t\t��   ��------------------------��        ��------------------------��   \t��\n");
	printf("\t\t��                                                                      \t��\n");
	printf("\t\t��   ��------------------------��        ��------------------------��   \t��\n");
	printf("\t\t��   �� 3.�ྰ������·�߲�ѯ ��        �� 4.������               ��   \t��\n");
	printf("\t\t��   ��------------------------��        ��------------------------��   \t��\n");
	printf("\t\t��                                                                      \t��\n");
	printf("\t\t��   ��------------------------��        ��------------------------��   \t��\n");
	printf("\t\t��   �� 5.����֮�������·��   ��        �� 6.�˳�У԰������ѯϵͳ ��   \t��\n");
	printf("\t\t��   ��------------------------��        ��------------------------��   \t��\n");
	printf("\t\t��                                                                      \t��\n");
	printf("\t\t��----------------------------------------------------------------------\t��\n\n");
	printf("\t\t������������ѡ�������");
	scanf("%d", &s);
	printf("\n\n");
	return s;
}

/*�������*/
struct 
{
	int close;                                            //����رյı��
	char name[20];                                         //��ž��������
	char reason[100];                                      //��ž���رյ�ԭ��
}scenic_Manager[M];

void scenicManager(matrix *g)
{
	int n, i, no;
	system("cls"); Dis_Map();
	int num;
	printf("��������Ҫ�رյľ���������");
	scanf("%d",&num);
	for(i=0;i<num;i++){
		printf("������Ҫ�رյľ�����: ");
		scanf("%d", &no);
		if (no < 1 || no > 36)
	{
		printf("����ı�Ų���ȷ������������\n");
	}
	else
	{
		scenic_Manager[no].close = INFINITY;
		strcpy(scenic_Manager[no].name, g->vexs[no].name);
		printf("\n");
		printf("�����뾰��رյ�ԭ��: \n");
		scanf("%s", scenic_Manager[no].reason);
		printf("����رճɹ���\n");
	}
	}

}

/*�ж�����ı���Ƿ����*/
int Judge(int num)
{
	int i = 0;
	if (num == -1)
		return i;
	if (num < 1 || num>36)
	{
		printf("\n����ı������������1-36֮������֣�\n");
		i = 1;
	}
	else if(scenic_Manager[num].close == INFINITY)
	{
		printf("\n�þ�����ʱ�رգ��޷�������\n");
		printf("\n");
		printf("�ر�ԭ��: %s\n", scenic_Manager[num].reason);
		i = 1;
	}

	return i;
}

/*����Ա����*/
void Manager()
{
	int n, num, no, i;
	matrix *g;
	int quit = 0;
	FILE * rf;
	rf = fopen("Information.txt", "a");
	char info[200];
	printf("\t\t               ��------------��         ��------------��   ��------------��            \n");
	printf("\t\t               �� 1.�������� ��         �� 2.������� ��   �� 3.�˳�     ��           \n");
	printf("\t\t               ��------------��         ��------------��   ��------------��           \n");
	printf("������Ҫѡ��ı��:\n");
	scanf("%d", &n);
		switch (n)
		{
		case 1:
			if (rf)
			{
				printf("����Ҫ�����Ĺ�����Ϣ��Ŀ: ");
				scanf("%d", &no);
				printf("\n");
				for (i = 1; i <= no; i++)
				{
					printf("�������%d��������Ϣ���: ", i);
					scanf("%d", &num);
					//fputc(num,rf);
					printf("\n");
					printf("�������%d��������Ϣ����: ", i);
					scanf("%s", info);
					//fputs(info,rf);
					printf("\n");
					fprintf(rf, "%d\n%s\n",num,info);
					fflush(rf);
					printf("���淢���ɹ�!\n\n");
					printf("\n");
				}
			}
			fclose(rf);
			Manager();
			break;
		case 2:
			scenicManager(&g);
			break;
		case 3:
			break;
		default:
			printf("\t\t\t\t\t����û�и�ѡ���Ӧ�Ĳ�����\n\n");
			break;
		}
}

/*�û���¼*/
int Login()
{
	int n = 1, num;
	char count[20] = "A212";
	char password[20] = "212";
	char count_input[20], password_input[20];
	printf("�������˺�:");
	scanf("%s", count_input);
	printf("\n");
	printf("����������:");
	scanf("%s", password_input);
	printf("\n");
	if ((strcmp(count, count_input) == 0) && (strcmp(password, password_input) == 0))
	{
		printf("��¼�ɹ�!\n");
		return n;
	}
	else printf("������˺Ż���������,����������!\n\n");
	Login();
}

/*�����ѧУ԰������ѯϵͳ��¼ϵͳ*/
int Login_system()
{
	int num = 0;
	printf("\t\t                      ��---------------------------------------��                \n");
	printf("\t\t                      �� ��ӭʹ�ù㶫�����ѧУ԰������ѯϵͳ  ��              \n");
	printf("\t\t                      ��---------------------------------------��                \n");
	printf("\t\t                                       ���¼                                   \n");
	printf("\t\t             ��----------------------��       ��--------------------------��  ��----------------------��        \n");
	printf("\t\t             ��     1.����Ա��¼     ��       ��2.�ο�(�������������)    ��  �� 3.�˳�               ��     \n");
	printf("\t\t             ��----------------------��       ��--------------------------��  ��----------------------��    \n");
	printf("������Ҫѡ��ı��:\n");
	scanf("%d", &num);
	switch (num)
	{
	case 1:
		system("cls"); Login(); Manager();system("cls"); Login_system(); break;
	case 2:
		system("cls") ;break;
	case 3:
		system("cls");Exit();return 0;break;
	default:
;		return 0;
		break;
	}
	return 1;
}

/*������*/
void Information_print()
{
	FILE *rf;
	char a[100];
	int n,i;
	rf = fopen("Information.txt", "r");
	if (rf)
	{
		printf("������������:\n\n");
    while(!feof(rf) )//�ж��ļ��Ƿ���� 
    {
        int ch;
        if( (ch = fgetc(rf)) != EOF ) //��ȡ���ַ���������� 
		putchar(ch);
    }
	}
	fclose(rf);
}

/*�˳��˵���*/
void Exit() {
	printf("\t\t                ��----------------------------------------��             \n");
	printf("\t\t                ��        ��ӭ�´�ʹ�ã�лл��            ��             \n");
	printf("\t\t                ��----------------------------------------��             \n");
	printf("\t\t                  * * * *            *            * * * *                \n");
	printf("\t\t                        *            *                  *                \n");
	printf("\t\t                  * * * *            *            * * * *                \n");
	printf("\t\t                  *                  *            *                      \n");
	printf("\t\t                  * * * *            *            * * * *                \n");
}

/*������*/
void main() {
	int quit = 0;
	matrix g;
	Createmap(&g);                                                              /*���ļ���ȡ��Ϣ����ͼ*/
	shortPath(&g);                                                               /*Floyd���dist��path*/
	while(Login_system()){
		while (!quit) {                              						/*ϵͳ�˳����������ж�*/
			switch (menu()) {                                                    /*��ӡ���˵�*/
			case 1:system("cls"); Dis_Map();searchinfo(&g); break;         /*�б�У԰������Ϣ��ѯ*/
			case 2:system("cls"); Dis_Map();shortpath_Print(&g); break;         /*����������·����ѯ*/
			case 3:system("cls"); Dis_Map();BestPath(&g); break;                /*�ྰ������·�߲�ѯ*/
			case 4:system("cls"); Dis_Map();Information_print(); break;         /*�������鿴*/
			case 6:system("cls");quit=1; Login_system();break;                         /*�˳�У԰������ѯϵͳ*/
			case 5: system("cls"); Dis_Map(); Allpath_Print(&g);break;
			default:printf("\t\t\t\t\t����û�и�ѡ���Ӧ�Ĳ�����\n\n");
			}
			system("pause");
			system("cls");                                                           /*����*/
		}
	}
}
