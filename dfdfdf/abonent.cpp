#include "abonent.h"
#include <utility> // ��� ����� tostring ������� �� ����� �������� �������. ��������������� ����� � �������

using namespace std;



void abonent::add_subscriber(string& name, string& surname, string& number){ // subscribers ����� �������� ���� ������� �� ������ �� ��������� this (this ��� ����������)
    subscribers.insert(  //subscribers �������� � ������� ���� ������� ��� ����. ������ � ��� ���� ���� �� ���������� ������ � ������ �������� � �����-�� ������ � �����-�� ��������
            make_pair(number,&abonent(name,surname))
            );        
}


unordered_map<string,abonent*> abonent::get_all_subscribers(){
    return subscribers;
}

int abonent::fill_subscriber(string& number, abonent** sb){ //���������. 
    if(subscribers.find(number)!=subscribers.end()){ // find end at ������ ����. ����� � ���� �������� �� �����. �������� ��������� ����������� �� ���� ��������� ����. ����� find ���������� ��������, �.� ��������� �� ����� � ����, ��� ��� ����� ���������, � ���� � ���, �� �� ���������� ��������� �� ����� ��� ����. �� ��� ����������. �  ��� ������ �������� ��� ���� � ���� ���� ����� �����
        *sb = subscribers.at(number); // � ��� ���������, ������� ����� �� ��������� sb ���������� ����� ���������� ��������, � ������ ��������� �� ������
        return 0;
    } else {
        return 1; // �� ������
    }
}

int abonent::delete_subscriber(string& number){
    subscribers.erase(number); // erase - �������. � ���� �������.
return 0;}

abonent::abonent(string& name, string& surname){ // ����������� ������
    setlocale(LC_ALL, "Russian");
	this->name = name; // �� ��������� 2 ��������� - ��� � �������, � ���� � ����� ������ ���� ��� ��������� - ��� � �������. ������� ��� - ����� ����� ���� ������ ��� ������� �� ������� ��� � ��� �������. this - ��������� �� ���� � ��� ������ ��������, �.� ������ this = ����-�� ���
    this->surname = surname;
    this->balance = 0;
}

abonent::abonent(){ //������ �������� ������ ��� ���� ������ 
}

list<string> abonent::get_recent_calls(){
    return recent_calls;
}

string abonent::get_description(string& number, bool balance){ //����� ������� ���������� �������� ��������
    //���� ������ - �������� � �������� ���������� � �������
    string result =  "Abonent "+name+" "+surname + 
        "; " + "Nomer: " +number+"; " ;
    if(balance)
        result+= "Balans: " + to_string(this->balance); //include -> ���� ������ � ��������� �� ����. ����� �������� ���� �������, ���� ��������� �� ����, � �� ��� ������ ������������ ��� ���������
    return result;
}

void abonent::money_income(int amount){ // ���-�� �����
	  this->balance +=amount; 
		}

void abonent::money_withdraw(int amount){
    this->balance -= amount;
}

int abonent::get_balance(){
    return balance;
}

