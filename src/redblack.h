#ifndef _REDBLACK_H_
#define _REDBLACK_H_

#include <iostream>
#include <assert.h>
#include <vector>
#define space  4

using namespace std;

template<class T>
class rbnode{
public:
	char m_color;
	T m_dato;
	vector<int> pointer;
	rbnode<T> *m_parent;
	rbnode<T> *m_nodes[2];
	rbnode(T _m_dato, char _m_color){
		this->m_dato = _m_dato;
		this->m_color = _m_color;
		this->m_nodes[0] = this->m_nodes[1] = this->m_parent = NULL;
	}
};

template<class T, class C>
class rbtree{
public:
	unsigned sz;
	rbnode<T> *m_root;
	C cmp;
	rbtree(){	
		this->m_root = NULL;
		this->sz = 0;
	}
	char color(rbnode<T> *);
	rbnode<T>* uncle(rbnode<T>*);
	rbnode<T>* sibling(rbnode<T>*);
	void replace(rbnode<T> *, rbnode<T> *);
	void rotate_left(rbnode<T> *);
	void rotate_right(rbnode<T> *);
	void insert_1(rbnode<T> *);
	void insert_2(rbnode<T> *);
	void insert_3(rbnode<T> *);
	void insert_4(rbnode<T> *);
	rbnode<T>* search(T);
	bool find(T, rbnode<T> **&, rbnode<T> **&);
	bool insert(T, unsigned);
	void remove_1(rbnode<T> *);
	void remove_2(rbnode<T> *);
	void remove_3(rbnode<T> *);
	void remove_4(rbnode<T> *);
	void remove_5(rbnode<T> *);
	void rew(rbnode<T> **&);
	bool remove(T);
	void print_h(rbnode<T> *, int);
	void print();
	void inorden(rbnode<T> *p);
	unsigned size();
};

template<class T, class C>
char rbtree<T,C>::color(rbnode<T> *a){
	return (a==NULL)?	'B':	a->m_color;
}

template<class T, class C>
rbnode<T>* rbtree<T,C>::uncle(rbnode<T> *a){
	return sibling(a->m_parent);
}

template<class T, class C>
rbnode<T>* rbtree<T,C>::sibling(rbnode<T> *a){
	return (a==a->m_parent->m_nodes[0])?	a->m_parent->m_nodes[1]:	a->m_parent->m_nodes[0];
}

template<class T, class C>
void rbtree<T,C>::replace(rbnode<T> *a, rbnode<T> *b){
	if(a->m_parent == NULL)	this->m_root = b;
	else if(a == a->m_parent->m_nodes[0])	a->m_parent->m_nodes[0] = b;
	else a->m_parent->m_nodes[1] = b;
	if(b!=NULL)	b->m_parent = a->m_parent;
	//m_root->m_color = 'B';
}

template<class T, class C>
void rbtree<T,C>::rotate_left(rbnode<T> *a){
	rbnode<T> *tm = a->m_nodes[1];
	replace(a,tm);
	a->m_nodes[1] = tm->m_nodes[0];
	if(tm->m_nodes[0] != NULL)	tm->m_nodes[0]->m_parent = a;
	tm->m_nodes[0] = a;
	a->m_parent = tm;
}

template<class T, class C>
void rbtree<T,C>::rotate_right(rbnode<T> *a){
	rbnode<T> *tm = a->m_nodes[0];
	replace(a,tm);
	a->m_nodes[0] = tm->m_nodes[1];
	if(tm->m_nodes[1] != NULL)	tm->m_nodes[1]->m_parent = a;
	tm->m_nodes[1] = a;
	a->m_parent = tm;
}

template<class T, class C>
void rbtree<T,C>::insert_1(rbnode<T> *a){
	if(a->m_parent == NULL)	a->m_color = 'B';
	else if(color(a->m_parent)=='B')	return;
	else	insert_2(a);
}

template<class T, class C>
void rbtree<T,C>::insert_2(rbnode<T> *a){
	assert (a != NULL);
    assert (a->m_parent != NULL);
    assert (a->m_parent->m_parent != NULL);

	if(color(uncle(a))=='R'){
		a->m_parent->m_color = 'B';
		uncle(a)->m_color = 'B';
		a->m_parent->m_parent->m_color = 'R';
		insert_1(a->m_parent->m_parent);
	}
	else	insert_3(a);
}

template<class T, class C>
void rbtree<T,C>::insert_3(rbnode<T> *a){
	if((a==a->m_parent->m_nodes[1]) and
	(a->m_parent==a->m_parent->m_parent->m_nodes[0])){
		rotate_left(a->m_parent);
		a = a->m_nodes[0];
	}
	else if((a==a->m_parent->m_nodes[0]) and
	(a->m_parent==a->m_parent->m_parent->m_nodes[1])){
		rotate_right(a->m_parent);
		a = a->m_nodes[1];
	}
	insert_4(a);
}

template<class T, class C>
void rbtree<T,C>::insert_4(rbnode<T> *a){
	a->m_parent->m_color = 'B';
	a->m_parent->m_parent->m_color = 'R';
	if((a==a->m_parent->m_nodes[0]) and 
	(a->m_parent == a->m_parent->m_parent->m_nodes[0])){
		rotate_right(a->m_parent->m_parent);
	}
	else{	rotate_left(a->m_parent->m_parent);	}

}

template<class T, class C>
bool rbtree<T,C>::find(T x,rbnode<T> **&p, rbnode<T> **&q){
	q = NULL;
	for(p=&(this->m_root); *p and ((*p)->m_dato!=x); p=&((*p)->m_nodes[cmp((*p)->m_dato,x)]))	q = p;
	return !!(*p);
}

template<class T, class C>
rbnode<T>* rbtree<T,C>::search(T x){
	rbnode<T> **p, **q;
	if(!find(x,p,q))	return NULL;
	return *p;
}

template<class T, class C>
bool rbtree<T,C>::insert(T dato, unsigned idx){
	rbnode<T> **p, **q;
	if(find(dato,p,q)){
		(*p)->pointer.push_back(idx);
		return false;
	}
	*p = new rbnode<T>(dato,'R');
	(*p)->pointer.push_back(idx);
	this->sz++;
	(q == NULL)?	(*p)->m_parent = NULL:	(*p)->m_parent = *q;

	insert_1(*p);
	//cout << "insert:	" << dato << endl;
	return true;
}

template<class T, class C>
void rbtree<T,C>::remove_1(rbnode<T> *a){
	if(a->m_parent == NULL)	return;
	else if(color(sibling(a))=='R'){
		a->m_parent->m_color = 'R';
		sibling(a)->m_color = 'B';
		if(a==a->m_parent->m_nodes[0])	rotate_left(a->m_parent);
		else rotate_right(a->m_parent);
	}
	remove_2(a);
}

template<class T, class C>
void rbtree<T,C>::remove_2(rbnode<T> *a){
	if((color(a->m_parent) == 'B') and
	(color(sibling(a))=='B') and 
	(color(sibling(a)->m_nodes[0])=='B') and
	(color(sibling(a)->m_nodes[1])=='B')){
		sibling(a)->m_color = 'R';
		remove_1(a->m_parent);
	}
	else remove_3(a);
}

template<class T, class C>
void rbtree<T,C>::remove_3(rbnode<T> *a){
	if ((color(a->m_parent) == 'R') and
	(color(sibling(a)) == 'B') and
	(color(sibling(a)->m_nodes[0]) == 'B') and 
	(color(sibling(a)->m_nodes[1]) == 'B')){
        sibling(a)->m_color = 'R';
        a->m_parent->m_color = 'B';
    }
    else    remove_4(a);
}

template<class T, class C>
void rbtree<T,C>::remove_4(rbnode<T> *a){
	if((a == a->m_parent->m_nodes[0]) and
	(color(sibling(a))=='B') and 
	(color(sibling(a)->m_nodes[0])=='R') and
	(color(sibling(a)->m_nodes[1])=='B')){
		sibling(a)->m_color = 'R';
		sibling(a)->m_nodes[0]->m_color = 'B';
		rotate_right(sibling(a));
	}
	else if((a == a->m_parent->m_nodes[1]) and
	(color(sibling(a))=='B') and 
	(color(sibling(a)->m_nodes[1])=='R') and
	(color(sibling(a)->m_nodes[0])=='B')){
		sibling(a)->m_color = 'R';
		sibling(a)->m_nodes[1]->m_color = 'B';
		rotate_left(sibling(a));
	}
	remove_5(a);
}

template<class T, class C>
void rbtree<T,C>::remove_5(rbnode<T> *a){
	sibling(a)->m_color = color(a->m_parent);
	a->m_parent->m_color = 'B';
	if(a == a->m_parent->m_nodes[0]){
		sibling(a)->m_nodes[1]->m_color = 'B';
		rotate_left(a->m_parent);
	}
	else{
		sibling(a)->m_nodes[0]->m_color = 'B';
		rotate_right(a->m_parent);
	}
}

template<class T, class C>
void rbtree<T,C>::rew(rbnode<T> **&q){
	for(q=&((*q)->m_nodes[0]); (*q)->m_nodes[1]!=NULL; q=&((*q)->m_nodes[1]));
}

//revisar borrado
template<class T, class C>
bool rbtree<T,C>::remove(T dato){
	rbnode<T> **p, **q;
	if(!find(dato,p,q))	return false;

	rbnode<T> *n = *p;
	if(n->m_nodes[0]!=NULL and n->m_nodes[1]!=NULL){
		q = p;	rew(q);
		n->m_dato = (*q)->m_dato;
		n = *q;
	}
	q = (n->m_nodes[1]==NULL)?	&n->m_nodes[0]:	&n->m_nodes[1];
	if(color(n) == 'B'){
		n->m_color = color(*q);
		remove_1(n);
	}
	replace(n,*q);
	this->sz--;
	//this->m_root->m_color = 'B';
	delete n;
	return true;
}


// cerpa print
template<class T, class C>
void rbtree<T,C>::print_h(rbnode<T> *n, int indent){
	int i;
    if (n == NULL){
        cout << "NULL" << endl;
        return;
    }

    if (n->m_nodes[1] != NULL)   print_h(n->m_nodes[1], indent + space);
    for(i = 0; i < indent; i++)	cout << " ";

    if (n->m_color == 'B')  cout << n->m_dato << endl;
    else    cout << "[" << n->m_dato << "]" << endl;
    
    if (n->m_nodes[0] != NULL)    print_h(n->m_nodes[0], indent + space);
}

template<class T, class C>
void rbtree<T,C>::print(){
	print_h(m_root,0);
	cout << "----------" << endl;
}

template<class T, class C>
void rbtree<T,C>::inorden(rbnode<T> *p){
	if(!p)	return;
	inorden(p->m_nodes[0]);
	cout << p->m_dato << ":\t";
	for(unsigned i=0; i<p->pointer.size(); i++)
		cout << p->pointer[i] << " ";
	cout << endl;
	inorden(p->m_nodes[1]);
}

template<class T, class C>
unsigned rbtree<T,C>::size(){
	return this->sz;
}

#endif
//https://www.fossmint.com/flat-plat-theme-for-ubuntu-linux/?utm_content=bufferd1828&utm_medium=social&utm_source=facebook.com&utm_campaign=buffer