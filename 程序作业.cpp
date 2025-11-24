#include<stdio.h>
#include<string.h>
struct Student {
    char institute[50];  // 本科院校
    char major[50];      // 报考专业
    char exam_type[20];  // 考试类型（学硕/专硕）
    float exam_id[20];    // 准考证号
    char sex[10];        //性别
    char name[50];       // 姓名
    char password[50];   //密码
    float interview_score;   // 复试面试成绩
    float written_score;     // C语言复试笔试成绩
};
//算法区
void initializeStudents(struct Student students[])//定义空白数组
 {
    for (int i = 0; i < 100; i++) {
        strcpy(students[i].institute, "");
        strcpy(students[i].major, "");
        strcpy(students[i].exam_type, "");
        strcpy(students[i].exam_id, "");
        strcpy(students[i].sex,"");
        strcpy(students[i].name, "");
        strcpy(students[i].password, "");
        students[i].interview_score = 0;
        students[i].written_score = 0;
    }
}


float ave(float a[],int num)
{
    int i,ave,m;
    for(i=0;i<num;i++)
        ave=ave+a[i];
    m=ave/num;
    return m;
	}////////////////求平均值

float all(float a[],int num)
{
	int i,j,m=0;
	for(i=0;i<num;i++)
	{
		m+=a[i];
	}
	return m;
}///求和函数

void input(struct Student students[], int num,int No) {
    int i=0;
    printf("请输入考生个人信息：\n");
    if (No >= 100) {
        printf("学生数量已达上限，无法添加。\n");
        return;
    }
    struct Student newStudent;
    printf("输入本科院校：");
    scanf("%s", newStudent.institute);
    printf("输入报考专业：");
    scanf("%s", newStudent.major);
    printf("输入考试类型(学硕/专硕)：");
    scanf("%s", newStudent.exam_type);
    printf("输入准考证号：");
    scanf("%s", newStudent.exam_id);
    printf("输入姓别：");
    scanf("%s",newStudent.sex);
    printf("输入姓名：");
    scanf("%s", newStudent.name);
    printf("输入考生密码：");
    scanf("%s", newStudent.password);
    students[No] = newStudent;
}



////////////管理员区域

void manager(struct Student students[],int num)
{
    int choice;
    int i,j;
    printf("<进入管理员模式>");
    do {
        printf("\n研究生招生复试成绩管理员功能\n");
        printf("1. 按报考专业、招生类别完成对学生成绩的录入和修改\n");
        printf("2. 按专业统计学生的成绩,求学生的总分及平均分\n");
        printf("3. 查询学生成绩，低于国家线科目及学生名单\n");
        printf("4. 按专业，输出学生的成绩单\n");
        printf("5. 通过姓名或者准考证号查询学生的专业排名\n");
        printf("0. 退出系统\n");
        printf("请选择操作：");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                input_score(students,num);
                break;
            case 2:
            	guanlitwo(students,num);

                break;
            case 3:

                break;
            case 4:
                guanlifour(students,num);
            	break;

			case 5:
				guanlifive(students,num);
				break;

            case 0:
                printf("退出系统。\n");
                break;
            default:
                printf("无效选择，请重新选择。\n");
            }
        }while (choice!=0);
}

void input_score(struct Student students[],int num)//专业成绩录入//管理1
{
    char p_m[50];
    printf("输入录入成绩的报考专业或者招生类别：");
    scanf("%s",p_m);
    for(int i=0;i<num;i++)
    {
            if(strcmp(students[i].major,p_m)==0)
            {
                printf("请输入%s考生的面试和C语言笔试成绩",students[i].name);
                scanf("%f",&students[i].interview_score);
                scanf("%f",&students[i].written_score);
            }
            if(strcmp(students[i].exam_type,p_m)==0)
            {
                printf("请输入%s考生的面试和C语言笔试成绩",students[i].name);
                scanf("%f %f",&students[i].interview_score,&students[i].written_score);
            }
    }
}


void paixu(float a[][2],int num)
{
    int i,j,max1,max2,k=0,t;
    max1=a[0][1];
    max2=a[0][0];
    for(i=0;i<num;i++)
    {
        if(a[i][1]>max1)
        {
        	j=a[i][1];
        	a[i][1]=max1;
        	max1=j;///第二列排序
        	t=a[i][0];
        	a[i][0]=max2;
        	max2=t;///第一列排序
        }
    }
}//////////////////排序后的成绩单

void chengjipaixu(struct Student students[],int num)
{
	float a[num][2],b[num][2],c[num][2];
	float d[num],e[num],f[num];
	int i,j,k,m,n;
	for(i=0;i<num;i++)
        {
       		if(students[i].major=="rengong")
       		{
       			a[i][1]=students[i].interview_score+students[i].written_score;
       			
			   }


            if(students[i].major=="dianqi")
            {
            	b[i][1]=students[i].interview_score+students[i].written_score;
			}

            if(students[i].major=="jike")
            {
            	c[i][1]=students[i].interview_score+students[i].written_score;
			}

        }
        paixu(a,num);
        paixu(b,num);
        paixu(c,num);

 } //////////////////用二维数组

void guanlitwo(struct Student students[],int num)///管理员2
{
    int i,j=0;
    float score,avers[100];
    char temp[100];
    printf("输入专业名称：");
    scanf("%s",temp);
    for(i=0;i<num;i++)
    {
        score=students[i].interview_score+students[i].written_score;
        if(strcmp(students[i].major,temp)==0)
        {
            avers[i]=score;
            j++;
            printf("%s专业学生%s的总成绩为%6.1f\n",temp,students[i].name,score);
        }
    }
    printf("%s专业的平均分是%6.2f",temp,ave(avers,j));
 }


void guanlifour(struct Student students[],int num)///管理员4
{
	float a[num][2],b[num][2],c[num][2];
	
	int i,j,k,m,n;
	for(i=0;i<num;i++)
        {
       		if(students[i].major=="rengong")
       		{
       			a[i][1]=students[i].interview_score+students[i].written_score;
       			a[i][0]=students[i].exam_id[20];
			   }


            if(students[i].major=="dianqi")
            {
            	b[i][1]=students[i].interview_score+students[i].written_score;
            	b[i][0]=students[i].exam_id[20];
			}

            if(students[i].major=="jike")
            {
            	c[i][1]=students[i].interview_score+students[i].written_score;
            	c[i][0]=students[i].exam_id[20];
            	
			}

        }
        paixu(a,num);
        paixu(b,num);
        paixu(c,num);
        printf("人工的面试成绩成绩单是：\n");
        for(j=0;j<num;j++)
        {
        	for(k=0;k<1;k++)
        	{
        		printf("%f",a[j][k]);
			}printf("\n");
        	
		}
		printf("电气的面试成绩成绩单是：\n");
		for(k=0;k<num;k++)
        {
        	for(j=0;j<1;j++)
        	{
        		printf("%f\n",b[k][j]);
			}printf("\n");
        	}
        printf("计科的面试成绩成绩单是：\n");
        for(m=0;m<num;m++)
        {
        	for(k=0;k<1;k++)
        	{
        		printf("%f\n",c[m][k]);
			}printf("\n");
        	}

}

void guanlifive(struct Student students[],int num)
{
	int m,n,i,j,k=0;
	char a[100],b,c,d;
	printf("请输入考生姓名或准考证号：\n");
	scanf("%s",&a);
	for(i=0;i<num;i++)
	{
		if(a==students[i].name||a==students[i].exam_id)
		{
			k=1;
			break;
		}
	}
	if(k==0)
	{
		printf("错误！！该用户不存在\n");
	}

	if(k==1)
	{
		  ///排序图表
		printf("该生的专业排名是：%d",n);

	}
}



void rearch(struct Student students[],int num)
{
    int i=0;
    printf("请输入你要查询的学号");
}

//学生专区
void stu(struct Student students[],int num)
{
	int choice;
    char zhanghao[100],pass[100];//账号/密码
    printf("<进入学生系统>");
    printf("请输入准考证号或身份证号:\n") ;
    scanf("%s",zhanghao);
    printf("请输入密码：\n",pass);
    scanf("%s",pass);
	for(int j=0;j<num;j++)
	{
		if(strcmp(students[j].exam_type,zhanghao)==0)
		{
            if(strcmp(students[j].password,pass)==0)
                {
                    printf("<登录成功>......\n");
                    break;
                }
            else
                {
                    printf("<登录失败>...\n"密码错误"");
                    break;
                }
		}
	 }
		//准考证号或者身份证号和密码进行登录；
        //能通过姓名或者准考证号查询自己的成绩和专业排名


}

int main()//主函数
{
    int i,cho,choice,num=0,No=0;
    struct Student students[100],*p=students;
    void input(struct Student students[], int num,int NO);
    void rearch(struct Student students[],int num);
    void manager(struct Student students[],int num);
    void score_input(struct Student students[],int num);
    void guanlifour(struct Student students[],int num);///管理员4
    void allscore(struct Student students[],int num);

    printf("<研究生招生复试成绩管理系统>\n");
        printf("\n输入学生人数:");
        scanf("%d",&num);

        do {
        printf("\n研究生招生复试成绩管理系统\n");
        printf("1. 添加学生信息\n");
        printf("2. 进入管理员模式\n");
        printf("3. 进入考生模式\n");
        printf("0. 退出系统\n");
        printf("请选择操作：");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                input(p, num,No);
                No++;
                break;
            case 2:
                manager(p,num);
                break;
            case 3:
                stu(p,num);
                break;
            case 0:
                printf("退出系统。\n");
                break;
            default:
                printf("无效选择，请重新选择。\n");
            }

            } while (choice!= 0);

    return 0;
}

