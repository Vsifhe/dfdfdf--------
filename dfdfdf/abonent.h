#ifndef ABONENT_H // когда где-то написано инклюд, возьми тот файл и скопируй в это место. мы не хотим, чтоб он копировался в это место несколько раз, больше одного раза. компилятор уже будет знать об этом файле и обработает как надо, все объявления там считает, поэтому #ifndef if not define если эта фигня ещё не объявлено, т.е никто её не инклюдил, тогда объяви эту константу и проинклюдь, а иначе этот блок между #ifndef и #endif не увидит его и ничего не проинклюдит. если два раза из двух разных файлоф делаешь инклюд этого файла, то когда компилятор будет обрабатывать первый файл, то он его вставит в то место, а когда второй, то не вставит. 
#define ABONENT_H

#include <unordered_map>
#include <string>
#include <list>
#include <conio.h>
#include <iostream>
using namespace std;

class abonent { //телефонная станция, у неё есть тариф и ассоциативный массив из номера и абонента

       
public:  
	string name;
    string surname; // первые 4 - поля
    int balance;
	unordered_map<string,abonent*> subscribers;
    //ассоциативный массив из номера и абонента. структура данных такая. которая позволяет получать по ключу значение, как х и у, позволяет получать по х - у. ключ - строка, абонент - значение. иначе пришлось бы хранить массив - абонент и за линейное время искать, а так за константное обращение позволяет получать то что тебе нужно  
   
	//  методы
    void add_subscriber(string& name, string& surname, string& number); // добавить абонента. & как указатели, только они безопасные. т.е не может такого что, есть ссылка, а самого объекта нету. нужно для того, чтобы при передаче этих строчек, они не копировались, а передавались по ссылке. в плюсах по дефолту всё копируется. стринг - тоже структура, только она описана в своей библиотеке. инклюд сверху
    
    unordered_map<string,abonent*> get_all_subscribers(); //функция, которая возвращает всех абонентов, чтобы можно было снаружи посмотреть
    int fill_subscriber(string& number, abonent** sb); // ** я объявляю в какой-то функции указатель и передаю указатель на этот указатель в fill_subscriber и она в тот указатель, который там объявлен подставляет нужный указатель
    int delete_subscriber(string& number);
	list<string> recent_calls;//очередь FIFO (первый вошёл, первый вышел. в каком порядке засовываешь, в таком и достаёшь) с абонентом хранится список его звонков. свойство объекта, типа у объекта есть список звонков
    abonent(string& name, string& surname); 
    abonent(); // где был двойной указатель, выделяем место в памяти под какого-то абонента, потом передаю указатель на это место в другую функцию и эта другая функция эту память по этому указателю заполняет 
    list<string> get_recent_calls(); //метод который возвращает тот список
    string get_description(string& number, bool balance); //  получить описание. сгенерируй мне описание абонента. (с балансом или без)
    void money_income(int amount); // положить денег на счёт
    void money_withdraw(int amount); //снять денег
    int get_balance();

	virtual int make_call(string& fr, string& to, int duration) // ссылка на класс абонент 
	{	
    abonent* from;
	fill_subscriber(fr, &from);
    from->recent_calls.push_back(to);//list "добавить в конец списка" 
    return 0;
	}
	
	abonent::abonent(int x)
  {
     this->x = x; //чтобы получить из объекта его поля, нужен указатель на себя (т.е this)
  }

       private: 
         
		   int x;
};


class abonent_pay : public abonent 
{  
     public: 
		 
		int make_call(string& fr, string& to, int duration)
		 { 
		   int cost = duration*tariff; // cost - стоимость
		   abonent* from;
		   fill_subscriber(fr, &from);
           if(from->balance<cost) return 1; // from - объект, а from.balance - значение поля balance у этого объекта
	       from->money_withdraw(cost);
		   from->recent_calls.push_back(to);//list "добавить в конец списка" 
           return 0;
		}

abonent_pay::abonent_pay(int tariff)
  {
     this->tariff = tariff; //чтобы получить из объекта его поля, нужен указатель на себя (т.е this)
  }

       private: 
         
		   int tariff;
};

#endif