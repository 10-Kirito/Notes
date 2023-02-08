#include <functional>
#include <iostream>
#include <set>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

using namespace std ;

int main()
{
	multiset<int,greater<int>> greadterSet;
	multiset<int,less<int>> lessSet;
	multiset<int> defaultSet;


	for (int i = 0; i < 10; i++) {
		int v = int (10 * rand());
		greadterSet.insert(v);
		lessSet.insert(v);
		defaultSet.insert(v);
	}

	for (int v: greadterSet) {
		printf("%d ",v);
	}

	printf("\n");

	for (int v : lessSet) {
		printf("%d ",v);
	}
	
	printf("\n");

	for (int v : defaultSet) {
		printf("%d ",v);
	}


	printf("\n");
	return 0;
}
