#include <iostream>
#include <string>
#include <stdio.h>
#include "src/db.h"

using namespace std;


bool console(string q, db *a){
	unsigned i=0, j=0;
	string tm1 = partial_partition(q,i,' ');
	string tm2 = partial_partition(q,j,';');

	if(tm2 == "q" or tm2 == "exit"){	a->save_table();	return false;	}
	else if(tm2 == "save")	a->save_table();
	else if(tm2 == "info")	a->show_table();
	else if(tm1 == "random")	a->random(q);
	else if(tm1 == "create")	a->create_table(q);
	else if(tm1 == "create|")	a->create_index(q);
	else if(tm1 == "insert")	a->insert_into(q);
	else if(tm1 == "select")	a->select_from(q);
	else if(tm1 == "select|")	a->select_from_index(q);
	else if(tm1 == "delete")	a->delete_from(q);
	else if(tm1 == "update")	a->update_where(q);
	else if(tm1 == "drop")	a->drop_table(q);
	return true;
}

int main(int argc, char const *argv[]){
	db *a = new db();
	a->load_table();

	bool t = true;
	string str;
	while(t){
		cout << "  [sarah-query]: "; getline(cin,str);
		t = console(str,a);
	}
	return 0;
}
