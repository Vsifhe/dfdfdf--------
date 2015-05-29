#include <iostream>
#include <string>
#include "abonent.h"
#include <conio.h>
#include <fstream>
#include <iomanip>


using namespace std;

abonent station(5); // создать статион (название переменной), хранит в себе объект класса, инициализованного цифрой 5 

void addSubscriber(){
	std::ofstream fout ("spisok.txt", std::ofstream::app);
	string name;
    string surname;
    string number;
    cout<<"\nДобавление нового абонента"<<endl;
    cout<<"Введите имя: ";
    cin>>name;
    fout<<name<<" ";	
	cout<<"Введите фамилию: ";
    cin>>surname;
	fout<<surname<<" ";	
    cout<<"Введите номер: ";
    cin>>number;	
    fout<<number<<endl;	 
	station.add_subscriber(name, surname, number);
    cout<<"Абонент создан!"<<endl;
    cout<<"Нажмите Enter чтобы продолжить"<<endl;
	getch();
	fout.close();
}

void editSubscriber(){

    string number;
    cout<<"\nРедактирование абонента"<<endl;
    cout<<"Введите номер абонента: ";
    cin>>number;
    abonent* sb; //создаём указатель на subscriber. subscriber* - указатель на место в памяти
    if(station.fill_subscriber(number, &sb)!=0){ // передали указатель на этот указатель в функцию(т.е адрес места в памяти, по которому записан этот указатель), функция изнутри берёт и в указатель по переданному указателю записывает указатель на объект из мапы. функция fill ищет абонента и записывает в sb указатель на найденного абонента
        cout<<"Абонент с таким номером не найден"<<endl;
        return;
    } 
    while(true){
        cout<<"\nвведите число:"<<endl;
        cout<<"1: изменить имя"<<endl;
        cout<<"2: изменить фамилию"<<endl;
        cout<<"3: пополнить счёт"<<endl;
        cout<<"4: удалить абонента"<<endl;
        cout<<"0: вернуться назад"<<endl;
        int num;
        cin>>num;//вводим число
        if(num==0){
           return;
        }
        switch(num){
            case 1:
                {
                    string name;
                    cout<<"Введите новое имя: ";
                    cin>>sb->name;
                    cout<<"Имя изменено!"<<endl;
                    break;
                }
            case 2:
                {
                    string surname;
                    cout<<"Введите новую фамилию: ";
                    cin>>sb->surname;
                    cout<<"Фамилия измененa!"<<endl;
                    break;
                }
            case 3:
                {
                    int amount;
                    cout<<"Введите сумму: ";
                    cin>>amount;
                    sb->money_income(amount);
                    cout<<"Баланс изменен!"<<endl;
                    break;
                }
            case 4:
                {
                    station.delete_subscriber(number);
                    cout<<"Абонент удалён"<<endl;
                    return;
                    break;
                }
            default:
                cout<<"Извините, вы ошиблись :("<<endl;
                break;
        }
    }
}

void showSubscriber(){

    string number;
    cout<<"\nВведите номер абонента: ";
    cin>>number;
    abonent* sb;
    if(station.fill_subscriber(number, &sb)!=0){
        cout<<"Абонент с таким номером не найден"<<endl;
        return;
    } 
    cout<<sb->get_description(number, true)<<endl;
    cout<<"Детализация звонков: "<<endl;
    for( auto callee: sb->get_recent_calls()){
        cout<<callee.get_description(number, false )<<endl;
    } 
	getch();
}

void showAllSubscribers(){

    cout<<"\nВот текущий список абонентов:"<<endl;
    cout<<"\n Имя       Фамилия      Номер"<<endl<<endl;
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
    cout<<"Нажмите Enter чтобы продолжить"<<endl; */
	    getch();
		fin.close();
    }

void makeCall(){

    string number;
    cout<<"\nВведите номер вызывающего: ";
    cin>>number;
    abonent* sb1;
    abonent* sb2;
    if(station.fill_subscriber(number, &sb1)!=0){
        cout<<"Абонент с таким номером не найден"<<endl;
        return;
    } 
    cout<<"Введите номер вызываемого: ";
    cin>>number;
    if(station.fill_subscriber(number, &sb2)!=0){
        cout<<"Абонент с таким номером не найден"<<endl;
        return;
    } 
    int duration = 0;
    cout<<"Введите продолжительность вызова: ";
    cin>>duration;
    int result = station.make_call(*sb1, *sb2, duration);
    cout<<"Результат: ";
    switch(result){
        case 0: 
            {
                cout<<"успех!";
                break;
            }
        case 1: 
            {
                cout<<"недостаточно денег у вызывающего :(";
                break;
            }
        default:
            {
                cout<<"случилось нечто страшное";
                break;
            }
    }
    cout<<endl;
    cout<<"Нажмите Enter чтобы продолжить"<<endl;
	getch();
    return;
}

void run(){ //главный цикл общения с пользователем


    while(true){ 
		system("cls");
        cout<<"\nПриветствую Вас в компании РудаФон!"<<endl;
        cout<<"введите число:"<<endl;
        cout<<"1: добавить абонента"<<endl;
        cout<<"2: редактировать абонента"<<endl;
        cout<<"3: просмотреть информацию абонента"<<endl;
        cout<<"4: вывести всех абонентов"<<endl;
        cout<<"5: сделать звонок"<<endl;
        cout<<"0: завершить программу"<<endl;
        int num;
        cin>>num;//вводим число
        if(num==0){
           cout<<"С вами было приятно иметь дело! Ждём вас снова"<<endl;
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
                cout<<"Извините, вы ошиблись :("<<endl;
                break;
        }
    }
}

int main(){
	setlocale(LC_ALL, "Russian");
	run();
    return 0;
}