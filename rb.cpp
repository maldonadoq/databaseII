#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include "../../Algoritmos/aed/src/cmp.h"
#include "src/redblack.h"

using namespace std;

typedef rbtree<int,cmg<int> > RB;
int main(int argc, char const *argv[]){
	/*RB *t = new RB();
	unsigned r = stoi(argv[1]);
	rbnode<int> *n = new rbnode<int>(1,'B');

	struct timeval ti, tf;
    double tiempo;

    gettimeofday(&ti, NULL);
	for(unsigned i=0; i<r; i++)	t->insert(i,i);
	gettimeofday(&tf, NULL);

	tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
	printf("time: %.8lf\n",tiempo/1000);

	cout << t->size() << endl;
	delete t;*/

	vector<int> tmp(400000000);
	cout << tmp.size() << endl;
	return 0;
}