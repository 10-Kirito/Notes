#include<mysql.h>
#include<cstdio>//mysql �ļ�
#include<cstdlib>

int main()
{
	MYSQL mysql;//���ݿ���
	MYSQL_RES* res;//��ѯ�����
	MYSQL_ROW row;//��¼�ṹ��


	//��ʼ�����ݿ�
	mysql_init(&mysql);

	//�����ַ�����
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");

	//�������ݿ�
	//������Ҫ�����Լ��ı����������룬��ȫΪĬ�ϣ�ֻ�����*��Ϊ�Լ��������Լ���xsgl�����ĳ��Լ����������ݿ⼴��
	if (mysql_real_connect(&mysql, "127.0.0.1", "root",
		"123456", "school", 3306, NULL, 0) == NULL) {
		printf("����ԭ��: %s\n", mysql_error(&mysql));
		printf("����ʧ�ܣ�\n");
		exit(-1);
	}

	//��ѯ����
    //studentΪxsgl���ݿ��д��ڵı�
	int ret = mysql_query(&mysql, "select * from student;");
	printf("ret: %d\n", ret);

	//��ȡ�����
	res = mysql_store_result(&mysql);

	//��ROW��ֵ,�ж�ROW�Ƿ�Ϊ�գ���Ϊ�վʹ�ӡ���ݡ�
	while (row = mysql_fetch_row(res))
	{
		printf("%s ", row[0]);//ѧ��
		printf("%s ", row[1]);//����
		printf("%s ", row[2]);//�Ա�
		printf("%s ", row[3]);//��������
		printf("%s ", row[4]);//����
		printf("%s ", row[5]);//�绰��
		printf("%s ", row[6]);//Ժϵ
		printf("%s \n", row[7]);//״̬
	}
	//�ͷŽ����
	mysql_free_result(res);

	//�ر����ݿ�
	mysql_close(&mysql);

	system("pause");
	return 0;
}