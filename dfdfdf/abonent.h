#ifndef ABONENT_H // ����� ���-�� �������� ������, ������ ��� ���� � �������� � ��� �����. �� �� �����, ���� �� ����������� � ��� ����� ��������� ���, ������ ������ ����. ���������� ��� ����� ����� �� ���� ����� � ���������� ��� ����, ��� ���������� ��� �������, ������� #ifndef if not define ���� ��� ����� ��� �� ���������, �.� ����� � �� ��������, ����� ������ ��� ��������� � ����������, � ����� ���� ���� ����� #ifndef � #endif �� ������ ��� � ������ �� �����������. ���� ��� ���� �� ���� ������ ������ ������� ������ ����� �����, �� ����� ���������� ����� ������������ ������ ����, �� �� ��� ������� � �� �����, � ����� ������, �� �� �������. 
#define ABONENT_H

#include <unordered_map>
#include <string>
#include <list>
#include <conio.h>
#include <iostream>
using namespace std;

class abonent { //���������� �������, � �� ���� ����� � ������������� ������ �� ������ � ��������

       
public:  
	string name;
    string surname; // ������ 4 - ����
    int balance;
	unordered_map<string,abonent*> subscribers;
    //������������� ������ �� ������ � ��������. ��������� ������ �����. ������� ��������� �������� �� ����� ��������, ��� � � �, ��������� �������� �� � - �. ���� - ������, ������� - ��������. ����� �������� �� ������� ������ - ������� � �� �������� ����� ������, � ��� �� ����������� ��������� ��������� �������� �� ��� ���� �����  
   
	//  ������
    void add_subscriber(string& name, string& surname, string& number); // �������� ��������. & ��� ���������, ������ ��� ����������. �.� �� ����� ������ ���, ���� ������, � ������ ������� ����. ����� ��� ����, ����� ��� �������� ���� �������, ��� �� ������������, � ������������ �� ������. � ������ �� ������� �� ����������. ������ - ���� ���������, ������ ��� ������� � ����� ����������. ������ ������
    
    unordered_map<string,abonent*> get_all_subscribers(); //�������, ������� ���������� ���� ���������, ����� ����� ���� ������� ����������
    int fill_subscriber(string& number, abonent** sb); // ** � �������� � �����-�� ������� ��������� � ������� ��������� �� ���� ��������� � fill_subscriber � ��� � ��� ���������, ������� ��� �������� ����������� ������ ���������
    int delete_subscriber(string& number);
	list<string> recent_calls;//������� FIFO (������ �����, ������ �����. � ����� ������� �����������, � ����� � �������) � ��������� �������� ������ ��� �������. �������� �������, ���� � ������� ���� ������ �������
    abonent(string& name, string& surname); 
    abonent(); // ��� ��� ������� ���������, �������� ����� � ������ ��� ������-�� ��������, ����� ������� ��������� �� ��� ����� � ������ ������� � ��� ������ ������� ��� ������ �� ����� ��������� ��������� 
    list<string> get_recent_calls(); //����� ������� ���������� ��� ������
    string get_description(string& number, bool balance); //  �������� ��������. ���������� ��� �������� ��������. (� �������� ��� ���)
    void money_income(int amount); // �������� ����� �� ����
    void money_withdraw(int amount); //����� �����
    int get_balance();

	virtual int make_call(string& fr, string& to, int duration) // ������ �� ����� ������� 
	{	
    abonent* from;
	fill_subscriber(fr, &from);
    from->recent_calls.push_back(to);//list "�������� � ����� ������" 
    return 0;
	}
	
	abonent::abonent(int x)
  {
     this->x = x; //����� �������� �� ������� ��� ����, ����� ��������� �� ���� (�.� this)
  }

       private: 
         
		   int x;
};


class abonent_pay : public abonent 
{  
     public: 
		 
		int make_call(string& fr, string& to, int duration)
		 { 
		   int cost = duration*tariff; // cost - ���������
		   abonent* from;
		   fill_subscriber(fr, &from);
           if(from->balance<cost) return 1; // from - ������, � from.balance - �������� ���� balance � ����� �������
	       from->money_withdraw(cost);
		   from->recent_calls.push_back(to);//list "�������� � ����� ������" 
           return 0;
		}

abonent_pay::abonent_pay(int tariff)
  {
     this->tariff = tariff; //����� �������� �� ������� ��� ����, ����� ��������� �� ���� (�.� this)
  }

       private: 
         
		   int tariff;
};

#endif