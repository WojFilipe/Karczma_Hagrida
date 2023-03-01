#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <time.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>   

using namespace std;

struct MenuItem
{
    int id;
    string name;
    int cena;
    string ingredients;
    int suma = 0;
};





//menu karczmy
void welcome()
{

    cout << "                              _____      ~~                 " << endl;
    cout << "                             /     \   ~~                   " << endl;
    cout << "                           _/       \_|                     " << endl;
    cout << "                          /           \                     " << endl;
    cout << "                         /_____________\                    " << endl;
    cout << "                        /|   KARCZMA   |\                   " << endl;
    cout << "                         |      U      |                    " << endl;
    cout << "                         |   HAGRIDA   |                    " << endl;
    cout << "#########################|     [:]     |####################" << endl << endl;
    cout << "                                                            " << endl;
    cout << "                            ul.Smocza                       " << endl;
    cout << "                       Numer: 654 312 788                   " << endl;
    cout << "                             Witamy!!!                      " << endl << endl;
}

//godziny
//-----------------------------------------------------------------------------------------
//pobiera godzine systemowa
time_t nowdataint = time(0);
tm* timenow = localtime(&nowdataint);
char* nowdatastring = ctime(&nowdataint);
unsigned int hourstodelivery;

//-----------------------------------------------------------------------------------------

int numerstolika;
bool deliverystate;
string numertel;
string adres;
string nazwa;

//restautacja jest zamknieta
void closedinfo()
{
    if (timenow->tm_hour < 13 || timenow->tm_hour>24 || timenow->tm_wday == 1)
    {
        cout << "...... Karczmaa jest czynna od środy do niedzieli   od 13 do 24......" << endl;
        cout << "Data i godzina teraz: " << nowdatastring << endl;
        cout << "Niestty restauracja jest zamknięta" << endl;

        if (deliverystate == 0)
        {
            cout << "Dlaczego wszedles do zamknietej restauracji? Dzwonie po policje" << endl;
        }
    }
    else
    {
        if (deliverystate == 1)
        {
            cout << " Karczma jest czynna w środy, czwartki, piątki, soboty i niedziele " << endl;
            cout << "                           Karczma u Harida                        " << endl;
            cout << "                     Za ile godzin ma byc danie?                   " << endl;
            cout << "--------wybierz liczbe godzin za ile ma przyjechac wcisnij enter---" << endl;

            cin >> hourstodelivery;
            time_t laterdataint = nowdataint + hourstodelivery * 3600;
            char* laterdatastring = ctime(&laterdataint);
            cout << "Dostawa: " << laterdatastring << endl;
            tm* timelater = localtime(&laterdataint);
            if (timelater->tm_hour < 10 || timelater->tm_hour>22 || timelater->tm_wday == 1)
            {
                cout << " Bedzie zamkniete kawalerze" << endl;
            }
        }

    }
}
void exitask()
{

    cout << ">>>>>>>>>>>>>>>>>>>>>>Aby wyjść kliknij x <<<<<<<<<<<<<<<<<<" << endl;

}
//podanie imienia
//wybor na miejscu czy dostawa
void deliverychoose()
{
    cout << "\t\t  Daleko zaszedłeś podróżniku!" << endl << endl;
    cout << "\t\tNa pewno jesteś głodny jak wilk!" << endl << endl;
    cout << "\t\t  Powiedz mi jak się nazywasz!" << endl << endl;
    cin >> nazwa;
    if (nazwa.length() == 0) {
        cout << "Pusty to masz portfel, a nie imie spróbuj jeszcze raz.";
        deliverychoose();
    }
    cout << "\t\t" << nazwa << " chcesz zjeść na miejscu czy na dowóz?" << endl;
    cout << "\t\t                ???" << endl;
    cout << "\t [0] W Karczmie \t\t [1] Na dowóz" << endl;
    cout << "Wciśnij 0, jesli chesz zjeść w karczmie. Wciśnij 1, jeśli chcesz na dowóz" << endl;
    cin >> deliverystate;
    if (deliverystate == 0)
    {
        cout << "Wybrales jedzenie na miejscu " << endl;
        cout << "Wybierz stolik od 1 do 8" << endl;
        cin >> numerstolika;
        if ((numerstolika <= 0) || (numerstolika > 8)) {
            cout << "Mamy tylko 8 stolików" << endl;
            deliverychoose();
        }
        else
        {
            void closedinfo();
        }
    }
    else
    {
        cout << "Wybrałeś na dowóz " << endl;
        void closedinfo();
        cout << "Wpisz swój numer" << endl;
        cin >> numertel;

        if (numertel.length() != 9) {
            cout << "taki numer nie istnije, numery mają 9 cyfr!" << endl;

            deliverychoose();
        }

        cout << "Proszę wpisać adres " << endl;
        cin.ignore();
        getline(cin, adres);

        if (adres.empty()) {
            cout << "Nie dowozimy do nikąd!";
            deliverychoose();
        }
        closedinfo();

    }

}

//tworzy wektor danych menu jedna linia
vector<string> splitRawMenuItem(string rawMenuItemStr, char divider) {
    vector<string> temp;
    stringstream ss(rawMenuItemStr);
    string tok;

    while (getline(ss, tok, divider)) {
        temp.push_back(tok);
    }
    return temp;
}

//tworzy wektor danych menu wszystkie linie
vector<MenuItem> getMenuMapped() {
    vector<MenuItem> items;
    ifstream file("menu_karczmy.txt");
    string str;
    int i = 0;
    while (getline(file, str)) {
        vector<string> formattedStr = splitRawMenuItem(str, ';');
        MenuItem item;
        item.id = stoi(formattedStr[0]);
        item.name = formattedStr[1];
        item.cena = stoi(formattedStr[2]);
        item.ingredients = formattedStr[3];
        items.push_back(item);
        i++;
    }
    return items;
}

//dodaje odstepy do tabelki, by informacje byly rowno
string getBeautyStringFrom(MenuItem item) {
    string beautyName = item.name;
    for (int i = item.name.length(); beautyName.length() <= 18; i++)
        beautyName += ' ';

    string beautyIgridients = item.ingredients;
    if (item.ingredients == "None")
        beautyIgridients = "";

    for (int i = beautyIgridients.length(); beautyIgridients.length() <= 30; i++)
        beautyIgridients += ' ';

    string beautyId = to_string(item.id);
    if (item.id < 10)
        beautyId += " ";

    string beautyPrice = to_string(item.cena);
    for (int i = beautyPrice.length(); beautyPrice.length() <= 2; i++)
        beautyPrice += ' ';

    string beautyAmount = "";
    if (item.suma != 0)
        beautyAmount = "x" + to_string(item.suma);
    return beautyId + " " + beautyName + beautyPrice + "       " + beautyIgridients + beautyAmount;
}

vector<MenuItem> orderItems;

// kalkuluje cene
int getTotalPrice() {
    int totalPrice = 0;
    for (int i = 0; i < orderItems.size(); i++)
    {
        MenuItem orderItem = orderItems[i];
        totalPrice += (orderItem.suma * orderItem.cena);
    }
    return totalPrice;
}

//Jeżeli jest puste każe powtórzyć 
void printOrderSummary() {
    if (orderItems.empty())
    {
        cout << "Nic nie wybrałeś!" << endl;
        return;
    }
    
    cout << "Twoje zamówienie" << endl;
    cout << "Twoje produkty:" << endl;
    cout << "Nr    Nr w menu      Danie                             Cena               Składniki i ilość             " << endl;
    for (int i = 0; i < orderItems.size(); i++)
    {
        string orderitemstring = to_string(i + 1) + ".       " + getBeautyStringFrom(orderItems[i]);
        cout << orderitemstring << endl;
    }
   
    cout << "Suma: " + to_string(getTotalPrice()) + "zl" << endl;
}

//Dodaje element do zamowienia
void addToOrder(MenuItem item) {
    bool isOrderContainsItem = false;
    int amount;
    cout << "jaką ilość dodać?" << endl;
    cin >> amount;
    if (amount > 0)
    {
        for (int i = 0; i < orderItems.size(); i++)
        {
            if (orderItems[i].id == item.id)
            {
                orderItems[i].suma += amount;
                isOrderContainsItem = true;
                break;
            }
        }
        if (!isOrderContainsItem)
        {
            item.suma = amount;
            orderItems.push_back(item);
        }
    }
    else
        cout << "Nie mozesz podac takiej ilosci!";
}

//Usuwa element z zamowienia
void removeFromOrder(int id) {
    if (id <= orderItems.size()) {
        string amountStr;
        cout << "Ile porcji chesz usunąć? (jeżeli wszystkie wpisz all)" << endl;
        cin >> amountStr;
        if (amountStr == "all")
            orderItems.erase(orderItems.begin() + (id - 1));
        else
        {
            int amount = stoi(amountStr);
            if (orderItems[id - 1].suma <= amount)
            {
                orderItems.erase(orderItems.begin() + (id - 1));
            }
            else
            {
                orderItems[id - 1].suma = orderItems[id - 1].suma - amount;
            }
        }
    }
    else
        cout << "Ten element nie znajduje się w zamowieniu!" << endl;
}

//pokazuje menu wyboru
void printUserInterface() {
    cout << endl << "Aby dodać danie do listy wciśnij         [a]" << endl;
    cout << "Jeśli chesz coś usunąć wciśnij           [b]" << endl;
    cout << "Jeśli zamówienie jest gotowe wciśnij     [c]" << endl;
    cout << "Menu                                     [d]" << endl;
    cout << "Wyświetlenie zamówienia                  [e]" << endl;
    cout << "Aby wyjść wciśnij                        [x]" << endl;
  
}

//dodaje pozycje do zamowienia
void onAddOptionPicked(vector<MenuItem> menuItems) {
    int id;
    cout << "Wybierz danie/napój które chcesz" << endl;
    cin >> id;
    if (0 < id && id <= 15)
    {
        addToOrder(menuItems[id - 1]);
        cout << "Dodano produkt do zamowienia." << endl;
    }
    else
    {
        cout << "Wprowadzono błędną liczbę!!!" << endl;
    }
}

//usuwa pozycje z zamowienia
void onRemoveOptionPicked() {
    if (!orderItems.empty())
    {
        printOrderSummary();
        cout << "Wybierz numer dania, które chesz usunąć" << endl;
        int id;
        cin >> id;
        if (0 < id)
        {
            removeFromOrder(id);
            cout << "Usunięto wybrane produkty." << endl;
        }
        else
            cout << "Nie ma takiego numeru" << endl;
    }
    else
        cout << "Twoje zamowienie jest puste, sprobuj najpierw cos dodac! :D" << endl;
}

//pokazuje menu restauracji
void printMenu(vector<MenuItem> menuItems) {
    cout << " " << endl << endl;
    cout << "Nr Nazwa                                      Cena       Skladniki" << endl;
    for (int i = 0; i < menuItems.size(); i++)
    {
        string test = getBeautyStringFrom(menuItems[i]);
        cout << test << endl;
    }
}


void exit()
{
    cout << "                              _____      ~~                 " << endl;
    cout << "                             /     \   ~~                   " << endl;
    cout << "                           _/       \_|                     " << endl;
    cout << "                          /           \                     " << endl;
    cout << "                         /_____________\                    " << endl;
    cout << "                        /|   KARCZMA   |\                   " << endl;
    cout << "                         |      U      |                    " << endl;
    cout << "                         |   HAGRIDA   |                    " << endl;
    cout << "#########################|     [:]     |####################" << endl << endl;
    cout << "                                                            " << endl;
    cout << "                            ul.Smocza                       " << endl;
    cout << "                       Numer: 654 312 788                   " << endl;
    cout << "                             Papa!!!                      " << endl << endl;
}

void savefile()
{
    fstream save;
    save.open("bill.txt");
    save << "                                         Potwierdzenie                                   " << endl;
    save << "Karczma u Hagrida" << endl;
    time_t nowdataint = time(0);
    char* nowdatastring = ctime(&nowdataint);
    save << nowdatastring << endl;
    save << "                                       Twoje zamówienie                                  " << endl;
    save << "Twoje produkty:" << endl;
    save << "Nr  Nr w menu     Nazwa                     Cena               Składniki i ilość         " << endl;
    for (int i = 0; i < orderItems.size(); i++)
    {
        string orderitemstring = to_string(i + 1) + ".       " + getBeautyStringFrom(orderItems[i]);
        save << orderitemstring << endl;
    }
    save << "-----------------------------------------------------------------------------------------" << endl;
    save << "Suma twojego zamówienia: " + to_string(getTotalPrice()) + "zl" << endl;
    if (deliverystate = 0)
    {
        save << "Na miejscu" << endl;
        save << "Stolik numer" << numerstolika << endl;
    }
    else
    {
        save << "Dowóz     " << endl;
        save << "Telefon   ";
        save << numertel << endl;
        save << "Adres";
        save << adres << endl;

        time_t laterdataint = nowdataint + hourstodelivery * 3600;
        char* laterdatastring = ctime(&laterdataint);
        save << "Dostawa: " << laterdatastring << endl;

    }
    save << "Karczma u Hagrida zaprasza ponownie!!!" << endl;
    save.close();
    cout << "Zapisano kawalerze" << endl;

    exit();
}

void savefilechoose()
{
    bool choose;
  
    cout << "                                    Rachunek                                              " << endl;
    cout << "Aby zakonczyc wciśnij x" << endl;
    cout << "Aby wydrukować rachunek wciśnij b" << endl;
    cin >> choose;
    if (choose == 1)
    {
        savefile();
    }
    else
    {
        cout << "ok!" << endl;
        exit();
    }
}


void summary()
{
    if (!orderItems.empty()) {
        cout << "                                             Rachunek                                   " << endl;
        time_t nowdataint = time(0);
        char* nowdatastring = ctime(&nowdataint);
        cout << nowdatastring << endl;
      
        cout << "                              _____      ~~                 " << endl;
        cout << "                             /     \   ~~                   " << endl;
        cout << "                           _/       \_|                     " << endl;
        cout << "                          /           \                     " << endl;
        cout << "                         /_____________\                    " << endl;
        cout << "                        /|   KARCZMA   |\                   " << endl;
        cout << "                         |      U      |                    " << endl;
        cout << "                         |   HAGRIDA   |                    " << endl;
        cout << "#########################|     [:]     |####################" << endl << endl;
        cout << "                                                            " << endl;
        cout << "                            ul.Smocza                       " << endl;
        cout << "                       Numer: 654 312 788                   " << endl;
        cout << "                             Witamy!!!                      " << endl << endl;

        cout << nazwa << endl;
  
        if (deliverystate == 0)
        {
            cout << "Na miejscu" << endl;
            cout << "Stolik numer" << numerstolika << endl;
        }
        else
        {
            cout << "Dowóz     " << endl;
            cout << "Numer telefonu   ";
            cout << numertel << endl;
            cout << "Adres   ";
            cout << adres << endl;

            time_t laterdataint = nowdataint + hourstodelivery * 3600;
            char* laterdatastring = ctime(&laterdataint);
            cout << "Dostawa: " << laterdatastring << endl;

        }
        printOrderSummary();
        savefilechoose();
    }
    else
        cout << "Nic nie zostało zamówione!" << endl;
}



//funkcje w kompletowaniu zamówienia 
void buildUserInterface(vector<MenuItem> menuItems) {
    for (;;)
    {
        printUserInterface();
        char choice;
        cin >> choice;
        switch (choice)
        {
        case 'a': onAddOptionPicked(menuItems); break;
        case 'b': onRemoveOptionPicked(); break;
        case 'c': summary(); return;
        case 'd': printMenu(menuItems); break;
        case 'e': printOrderSummary(); break;
        case 'x': return;
        }
    }
}

//pokazuje menu restauracji i menu wboru
void buildMenu()
{
    vector<MenuItem> menuItems = getMenuMapped();
    printMenu(menuItems);
    buildUserInterface(menuItems);
}

int main()
{
    setlocale(LC_CTYPE, "Polish");
    welcome();
    deliverychoose();
    buildMenu();
    return 0;
}