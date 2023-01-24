#include "multimap.h"
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru");
    tree* _tree = 0;//��������� �� ������ ������
    tree wood;
    FILE* in = fopen("data.txt", "r");
    int t = 0, i = 0;//�������� � �������� �����
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
    int x = 0;//������ ������� �����
    while (x < 3)
    {
        SetColor(2, 0);
        cout << "����� �������� - 0=�����-������� �������, 1=������-���������� �������" << endl;
        int translation;
        cin >> translation;
        switch (translation)
        {
        case 0:
            SetColor(3, 0);
            cout << "���� ����� - ";
            cin >> buff;
            ru.clear();
            ss.clear();
            ss << buff;
            for (ss >> en; !en.empty(); ss >> en)
            {
                it = enru.find(en);
                if (it != enru.end()) ru += it->second;
                else ru += "������";
                ru += " ";
                en.clear();
            }
            SetColor(4, 0);
            cout << "������� - " << ru << endl;
            if (fout.is_open()) fout << buff << " " << ru << endl;
            break;
        case 1:
            SetColor(5, 0);
            cout << "���� ����� - ";
            cin >> buff;
            en.clear();
            ss.clear();
            ss << buff;
            for (ss >> ru; !ru.empty(); ss >> ru)
            {
                it = enru.find(ru);
                if (it != enru.end()) en += it->second;
                else en += "������";
                en += " ";
                ru.clear();
            }
            SetColor(6, 0);
            cout << "������� - " << en << endl;
            if (output.is_open()) output << buff << " " << en << endl;
            break;
        }
        x++;
    }
    SetColor(7, 0);
    cout << "���������� ���� - ";
    ofstream out("words.txt", ios::app);
    if (out.is_open())
    {
        SetColor(8, 0);
        cout << "���������� ����� - ";
        cin >> en;
        SetColor(9, 0);
        cout << "������� ����� - ";
        cin >> ru;
        out << en << " " << ru << endl;
    }
}