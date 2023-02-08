// 该程序的目的是为了测试自定义类和自定义排序规则在multiset中的应用测试，已测试其泛型
#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>
#include <string.h>

using namespace std;

struct Student
{
	char name[20];
	int id;
	double gpa;
};

Student student[] = {
	{"Jack",112,3.4},{"Mary",102,3.8},
	{"Mary",117,3.9},{"Ala",333,3.5},
	{"Zero",101,4.0},{"Cindy",102,4.8}
};

struct Rule {
	bool operator()(const Student & s1,const Student & s2) {
		if(s1.gpa != s2.gpa)
			return s1.gpa > s2.gpa;
			// 按照分数进行排序
		else
			return (strcmp(s1.name, s2.name) < 0);
			// 分数相等的话，按照姓名排序
	}
};

int main()
{
	multiset<Student,Rule> st;

	for(int i = 0;i < 5;++i)
		st.insert(student[i]);

	multiset<Student,Rule>::iterator p;

	for (p = st.begin() ; p != st.end() ;p++) {
		cout << p->gpa << " " << p->name
			 << " " << p->id <<endl;
	}
	Student s = {"Mary",1000,3.9};
	p = st.find(s);
	
	if(p != st.end())
		cout << "find sucessfully!" <<endl;
	return 0;
}
