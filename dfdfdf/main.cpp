#include <iostream>
#include <string>
#include "abonent.h"
#include <conio.h>
#include <fstream>
#include <iomanip>


using namespace std;

abonent station(5); // ������� ������� (�������� ����������), ������ � ���� ������ ������, ����������������� ������ 5 

void addSubscriber(){
	std::ofstream fout ("spisok.txt", std::ofstream::app);
	string name;
    string surname;
    string number;
    cout<<"\n���������� ������ ��������"<<endl;
    cout<<"������� ���: ";
    cin>>name;
    fout<<name<<" ";	
	cout<<"������� �������: ";
    cin>>surname;
	fout<<surname<<" ";	
    cout<<"������� �����: ";
    cin>>number;	
    fout<<number<<endl;	 
	station.add_subscriber(name, surname, number);
    cout<<"������� ������!"<<endl;
    cout<<"������� Enter ����� ����������"<<endl;
	getch();
	fout.close();
}

void editSubscriber(){

    string number;
    cout<<"\n�������������� ��������"<<endl;
    cout<<"������� ����� ��������: ";
    cin>>number;
    abonent* sb; //������ ��������� �� subscriber. subscriber* - ��������� �� ����� � ������
    if(station.fill_subscriber(number, &sb)!=0){ // �������� ��������� �� ���� ��������� � �������(�.� ����� ����� � ������, �� �������� ������� ���� ���������), ������� ������� ���� � � ��������� �� ����������� ��������� ���������� ��������� �� ������ �� ����. ������� fill ���� �������� � ���������� � sb ��������� �� ���������� ��������
        cout<<"������� � ����� ������� �� ������"<<endl;
        return;
    } 
    while(true){
        cout<<"\n������� �����:"<<endl;
        cout<<"1: �������� ���"<<endl;
        cout<<"2: �������� �������"<<endl;
        cout<<"3: ��������� ����"<<endl;
        cout<<"4: ������� ��������"<<endl;
        cout<<"0: ��������� �����"<<endl;
        int num;
        cin>>num;//������ �����
        if(num==0){
           return;
        }
        switch(num){
            case 1:
                {
                    string name;
                    cout<<"������� ����� ���: ";
                    cin>>sb->name;
                    cout<<"��� ��������!"<<endl;
                    break;
                }
            case 2:
                {
                    string surname;
                    cout<<"������� ����� �������: ";
                    cin>>sb->surname;
                    cout<<"������� �������a!"<<endl;
                    break;
                }
            case 3:
                {
                    int amount;
                    cout<<"������� �����: ";
                    cin>>amount;
                    sb->money_income(amount);
                    cout<<"������ �������!"<<endl;
                    break;
                }
            case 4:
                {
                    station.delete_subscriber(number);
                    cout<<"������� �����"<<endl;
                    return;
                    break;
                }
            default:
                cout<<"��������, �� �������� :("<<endl;
                break;
        }
    }
}

void showSubscriber(){

    string number;
    cout<<"\n������� ����� ��������: ";
    cin>>number;
    abonent* sb;
    if(station.fill_subscriber(number, &sb)!=0){
        cout<<"������� � ����� ������� �� ������"<<endl;
        return;
    } 
    cout<<sb->get_description(number, true)<<endl;
    cout<<"����������� �������: "<<endl;
    for( auto callee: sb->get_recent_calls()){
        cout<<callee.get_description(number, false )<<endl;
    } 
	getch();
}

void showAllSubscribers(){

    cout<<"\n��� ������� ������ ���������:"<<endl;
    cout<<"\n ���       �������      �����"<<endl<<endl;
	std::ofstream fout ("spisok.txt", std::ofstream::app);
	fout<<"- - -";
	fout.close();
	cout.setf(ios::left);
	std::ifstream fin("spisok.txt"); 
    string name, surname, number;
    while (! fin.eof()){
        fin >> name >> surname >> number;
        cout<<setw(8)<<name<<" ";
        cout<<setw(11)<<surname<<" ";
        cout<<setw(11)<<number;
        cout<<endl;}
/*  for(auto pair: station.get_all_subscribers()){
        string number = pair.first;
        subscriber& sb = pair.second;
        cout<<sb.name<<" "<< sb.surname<<" "<<number<<" "<<sb.get_balance();
        cout<<endl;
    }
    cout<<"������� Enter ����� ����������"<<endl; */
	    getch();
		fin.close();
    }

void makeCall(){

    string number;
    cout<<"\n������� ����� �����������: ";
    cin>>number;
    abonent* sb1;
    abonent* sb2;
    if(station.fill_subscriber(number, &sb1)!=0){
        cout<<"������� � ����� ������� �� ������"<<endl;
        return;
    } 
    cout<<"������� ����� �����������: ";
    cin>>number;
    if(station.fill_subscriber(number, &sb2)!=0){
        cout<<"������� � ����� ������� �� ������"<<endl;
        return;
    } 
    int duration = 0;
    cout<<"������� ����������������� ������: ";
    cin>>duration;
    int result = station.make_call(*sb1, *sb2, duration);
    cout<<"���������: ";
    switch(result){
        case 0: 
            {
                cout<<"�����!";
                break;
            }
        case 1: 
            {
                cout<<"������������ ����� � ����������� :(";
                break;
            }
        default:
            {
                cout<<"��������� ����� ��������";
                break;
            }
    }
    cout<<endl;
    cout<<"������� Enter ����� ����������"<<endl;
	getch();
    return;
}

void run(){ //������� ���� ������� � �������������


    while(true){ 
		system("cls");
        cout<<"\n����������� ��� � �������� �������!"<<endl;
        cout<<"������� �����:"<<endl;
        cout<<"1: �������� ��������"<<endl;
        cout<<"2: ������������� ��������"<<endl;
        cout<<"3: ����������� ���������� ��������"<<endl;
        cout<<"4: ������� ���� ���������"<<endl;
        cout<<"5: ������� ������"<<endl;
        cout<<"0: ��������� ���������"<<endl;
        int num;
        cin>>num;//������ �����
        if(num==0){
           cout<<"� ���� ���� ������� ����� ����! ��� ��� �����"<<endl;
           getch();
		   return;
        }
        switch(num){
            case 1:
                addSubscriber();
                break;
            case 2:
                editSubscriber();
                break;
            case 3:
                showSubscriber();
                break;
            case 4:
                showAllSubscribers();
                break;
            case 5:
                makeCall();
                break;
            default:
                cout<<"��������, �� �������� :("<<endl;
                break;
        }
    }
}

int main(){
	setlocale(LC_ALL, "Russian");
	run();
    return 0;
}