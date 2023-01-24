#include "multimap.h"
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru");
    tree* _tree = 0;//указатель на объект класса
    tree wood;
    FILE* in = fopen("data.txt", "r");
    int t = 0, i = 0;//итератор и параметр цикла
    char* word = new char[maxline + 1];
    while (!feof(in))
    {
        fscanf(in, "%s", word);
        int tal = strlen(word);
        for (int i = 0; i < tal; i++)
        {
            wood.upp_lett(word, i);
            if (ispunct((unsigned char)word[i]) || word[i] == ' ' || word[i] == (char)(133) || word[i] == (char)(187) || word[i] == (char)(150) || word[i] == (char)(151) || word[i] == (char)(171)) for (int j = i; j < tal; j++) word[i] = word[j + 1];
        }
        if (strcmp(word, ""))
        {
            if (_tree == 0) _tree = wood.tree_insert(_tree, word);
            else wood.tree_insert(_tree, word);
        }
        strcpy(word, "");
    }
    fclose(in);
    t = wood.tree_amount(_tree);
    tree** arr = new tree * [t];
    wood.tree_point(_tree, arr, i);
    wood.point_sort(arr, t);
    wood.print_freq(arr, t);
    typedef multimap<string, string> strMap;
    strMap enru;
    strMap::iterator it;
    stringstream ss;
    string en, ru;
    ifstream fin("words.txt", ios::in | ios::binary);
    string buff;
    while (!fin.eof())
    {
        getline(fin, buff);
        ss << buff;
        ss >> en >> ru;
        enru.insert(make_pair(en, ru));
    }
    ofstream fout("engl-russ transl.txt", ios::app), output("russ-engl transl.txt", ios::app);
    int x = 0;//первый элемент цикла
    while (x < 3)
    {
        SetColor(2, 0);
        cout << "выбор перевода - 0=англо-русский перевод, 1=русско-английский перевод" << endl;
        int translation;
        cin >> translation;
        switch (translation)
        {
        case 0:
            SetColor(3, 0);
            cout << "ввод слова - ";
            cin >> buff;
            ru.clear();
            ss.clear();
            ss << buff;
            for (ss >> en; !en.empty(); ss >> en)
            {
                it = enru.find(en);
                if (it != enru.end()) ru += it->second;
                else ru += "ошибка";
                ru += " ";
                en.clear();
            }
            SetColor(4, 0);
            cout << "перевод - " << ru << endl;
            if (fout.is_open()) fout << buff << " " << ru << endl;
            break;
        case 1:
            SetColor(5, 0);
            cout << "ввод слова - ";
            cin >> buff;
            en.clear();
            ss.clear();
            ss << buff;
            for (ss >> ru; !ru.empty(); ss >> ru)
            {
                it = enru.find(ru);
                if (it != enru.end()) en += it->second;
                else en += "ошибка";
                en += " ";
                ru.clear();
            }
            SetColor(6, 0);
            cout << "перевод - " << en << endl;
            if (output.is_open()) output << buff << " " << en << endl;
            break;
        }
        x++;
    }
    SetColor(7, 0);
    cout << "добавление слов - ";
    ofstream out("words.txt", ios::app);
    if (out.is_open())
    {
        SetColor(8, 0);
        cout << "английское слово - ";
        cin >> en;
        SetColor(9, 0);
        cout << "русское слово - ";
        cin >> ru;
        out << en << " " << ru << endl;
    }
}