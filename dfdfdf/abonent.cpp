#include "abonent.h"
#include <utility> // был метод tostring который по числу получает строчку. преобразовывает число в строчку

using namespace std;



void abonent::add_subscriber(string& name, string& surname, string& number){ // subscribers можно получать поля объекта не только по указателю this (this для повторяшек)
    subscribers.insert(  //subscribers хранится в объекте фоун стэйшен как поле. вставь в эту мапу пару из пришедшего номера и нового абонента с таким-то именем и такой-то фамилией
            make_pair(number,&abonent(name,surname))
            );        
}


unordered_map<string,abonent*> abonent::get_all_subscribers(){
    return subscribers;
}

int abonent::fill_subscriber(string& number, abonent** sb){ //заполнить. 
    if(subscribers.find(number)!=subscribers.end()){ // find end at внутри мапы. найти в мапе значение по ключу. итератор позволяет пробежаться по всем значениям мапы. метод find возвращает итератор, т.е указатель на место в мапе, где эта фигня находится, и если её нет, то он возвращает указатель на конец это мапы. он так реализован. и  эта строка означает что если в мапе есть такая фигня
        *sb = subscribers.at(number); // в тот указатель, который лежит по указателю sb записывает адрес найденного абонента, в смысле указатель на память
        return 0;
    } else {
        return 1; // не найден
    }
}

int abonent::delete_subscriber(string& number){
    subscribers.erase(number); // erase - стереть. в мапе указано.
return 0;}

abonent::abonent(string& name, string& surname){ // конструктор класса
    setlocale(LC_ALL, "Russian");
	this->name = name; // он принимает 2 параметра - имя и фамилию, и типа у этого класса есть его параметры - имя и фамилия. говорим что - пусть будет моим именем имя которое ты передал мне в мою функцию. this - указатель на себя и его нельзя поменять, т.е нельзя this = чему-то там
    this->surname = surname;
    this->balance = 0;
}

abonent::abonent(){ //только выделяет память под этот объект 
}

list<string> abonent::get_recent_calls(){
    return recent_calls;
}

string abonent::get_description(string& number, bool balance){ //метод который возвращает описание абонента
    //если правда - добавить в описание информацию о балансе
    string result =  "Abonent "+name+" "+surname + 
        "; " + "Nomer: " +number+"; " ;
    if(balance)
        result+= "Balans: " + to_string(this->balance); //include -> есть объект и указатель на него. чтобы получить поле объекта, имея указатель на него, а не сам объект используется эта стрелочка
    return result;
}

void abonent::money_income(int amount){ // кол-во денег
	  this->balance +=amount; 
		}

void abonent::money_withdraw(int amount){
    this->balance -= amount;
}

int abonent::get_balance(){
    return balance;
}

