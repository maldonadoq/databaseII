#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include "../../Algoritmos/aed/src/cmp.h"
#include "src/redblack.h"

using namespace std;

typedef rbtree<int,cmg<int> > RB;
int main(int argc, char const *argv[]){
	RB *t = new RB();
	unsigned r = 500000;

	struct timeval ti, tf;
    double tiempo;

    gettimeofday(&ti, NULL);
	for(unsigned i=0; i<r; i++)	t->insert(rand()%100,i);
	gettimeofday(&tf, NULL);

	tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
	printf("time: %.8lf\n",tiempo/1000);

	cout << t->size() << endl;
	//t->print();
	//t->inorden(t->m_root);	cout << endl;
	delete t;
	return 0;
}