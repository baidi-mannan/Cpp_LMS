#include <bits/stdc++.h>
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

class book
{
public:
    string file_name;
    string type;
    string author;
    string title;
    int found = 0;
};
class novel // a new structure to store both the chapter name and count of the novel
{
public:
    int chapter_number;
    int count = 0;
};

book books[10000];
int n = 0;
void removeElement(int x)
{
    int i;
    for (i = 0; i < n; i++)
        if (i == x)
            break;

    if (i < n)
    {

        n = n - 1;
        for (int j = i; j < n; j++)
            books[j] = books[j + 1];
    }
}

void print_index()
{
    ofstream fi("index.txt");

    for (int i = 0; i < n; i++)
    {
        if (books[i].found == 1)
            fi << books[i].file_name << " " << books[i].type << " " << endl;
        if (books[i].found == 0)
        {
            removeElement(i);
        }
    }
}
void read_index()

{
    string index = "index.txt";
    int i = 0;
    ifstream fi(index);

    if (!fi.is_open())
    {
        cout << "File not found" << endl;
        return;
    }
    string word;
    fi >> word;
    while (fi.good())
    {
        if ((i % 2) == 0)
        {
            books[n].file_name = word;
        }
        if ((i % 2) == 1)
        {
            books[n].type = word;
            n++;
        }
        i++;
        fi >> word;
    }
}
int is_present(string str)
{
    for (int i = 0; i < n; i++)
    {
        if (books[i].file_name.compare(str) == 0)
        {
            books[i].found = 1;
            return 1;
        }
    }
    return 0;
}
void exp(char *dir_name)
{
    DIR *dir;

    struct dirent *entry;
    struct stat info;
    ofstream file("index.txt", ios::app);
    dir = opendir(dir_name);
    if (dir == NULL)
    {
        cout << "DIrectory not found" << endl;
        return;
    }
    int i = n;
    while ((entry = readdir(dir)) != NULL)
    {
        if (is_present(entry->d_name) == 0)
        {
            if (entry->d_name[0] != '.')
            {
                int x;
                books[i].file_name = entry->d_name;
                books[i].found = 1;
                n++;
                file << entry->d_name << " ";
                cout << "Enter thr type of file " << entry->d_name << endl;
                cout << "1. Novel" << endl;
                cout << "2. Play" << endl;
                cin >> x;
                if (x == 1)
                    books[i].type = "Novel";
                if (x == 2)
                    books[i].type = "Play";
                file << books[i].type << endl;

                i++;
            }
        }
    }
    //cout << n << endl;
}
void inp(string file_name, int k)
{
    ifstream fl(file_name);

    if (!fl.is_open())
    {
        cout << "File not found" << endl;
        return;
    }
    string word;
    fl >> word;
    while (fl.good())
    {
        if (word.compare("Title:") == 0)
        {
            //cout << word << endl;
            getline(fl, word);

            books[k].title = word;
            // cout << books[k].title << endl;
        }
        if (word.compare("Author:") == 0)
        {
            //cout << word << endl;
            getline(fl, word);

            books[k].author = word;
            //  cout << books[k].author << endl;

            break;
        }

        fl >> word;
    }
}
void read_folder(char *dir_name)
{
    for (int i = 0; i < n; i++)
    {
        string filename = dir_name;
        filename.append("/");
        filename.append(books[i].file_name);

        inp(filename, i);
    }
}
void print_data()
{
    cout << "The books in the directory are:" << endl;
    for (int i = 0; i < n; i++)
    {

        cout << "-----------------------------------------------" << endl;
        cout << "File Name: " << books[i].file_name << endl;
        cout << "Title:" << books[i].title << endl;
        cout << "Type: " << books[i].type << endl;
        cout << "Author:" << books[i].author << endl;
    }
    cout << "-------------------------------------------------" << endl;
}
void search_book(string inp)
{
    cout << "The list of books with the given input is:" << endl;
    for (int i = 0; i < n; i++)
    {
        int q = 0;
        int found_t = books[i].title.find(inp);
        int found_a = books[i].author.find(inp);

        if (found_t != string::npos)
        {
            cout << "-----------------------------------------------" << endl;
            cout << "File Name: " << books[i].file_name << endl;
            cout << "Title:" << books[i].title << endl;
            cout << "Type: " << books[i].type << endl;
            cout << "Author:" << books[i].author << endl;
            q = 1;
        }
        if (found_a != string::npos && q != 1)
        {
            cout << "-----------------------------------------------" << endl;
            cout << "File Name: " << books[i].file_name << endl;
            cout << "Title:" << books[i].title << endl;
            cout << "Type: " << books[i].type << endl;
            cout << "Author:" << books[i].author << endl;
            q = 1;
        }
    }
    cout << "-----------------------------------------------" << endl;
}

int choose_book()
{
    int option;

    cout << "Choose the book you want to see: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << ". " << books[i].title << endl;
    }
    cin >> option;
    return option;
}
void display_book(int x)
{
    string search_string;

    string filename = "./Books";
    filename.append("/");
    filename.append(books[x - 1].file_name);
    if (books[x - 1].type.compare("Novel") == 0)
    {
        int i = 0;
        ifstream fr(filename);
        if (!fr.is_open())
        {
            cout << "File not found" << endl;
            return;
        }
        string word;
        fr >> word;
        int start = 0;
        while (fr.good())
        {
            if (word.compare("CHAPTER") == 0)
            {
                start = 1;
            }
            if (start)
            {
                cout << word << " ";
                i++;
            }
            if (i >= 1000)
                break;
            fr >> word;
        }
    }
    if (books[x - 1].type.compare("Play") == 0)
    {
        int i = 0;
        ifstream fr(filename);
        if (!fr.is_open())
        {
            cout << "File not found" << endl;
            return;
        }
        string word;
        fr >> word;
        int start = 0;
        while (fr.good())
        {
            if (word.compare("ACT") == 0)
            {
                start = 1;
            }
            if (start)
            {
                cout << word << " ";
                i++;
            }
            if (i >= 1000)
                break;
            fr >> word;
        }
    }

    cout << endl
         << "---------------------------" << endl;
}
int comp(novel x, novel y)
{
    return x.count > y.count;
}
int is_upper(string str)

{
    for (int i = 0; i < str.size(); i++)
    {
        if (islower(str[i]))
            return 0;
    }
    return 1;
}
int finder(vector<string> str, string x)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (x.compare(str[i]) == 0)
            return 1;
    }
    return 0;
}
void case_3(int x)
{
    string search_string;

    string filename = "./Books";
    filename.append("/");
    filename.append(books[x - 1].file_name);

    if (books[x - 1].type.compare("Novel") == 0)
    {
        cout << "Enter the string you want to search: " << endl;
        cin >> search_string;

        vector<novel> counting(100000); // new structure so that we can store chapter_number while sorting

        ifstream fr(filename);
        if (!fr.is_open())
        {
            cout << "File not found" << endl;
            return;
        }
        string word;
        fr >> word;
        int j = 0;
        int start = 0; // to start from chaptr 1 and avoid the above part
        while (fr.good())
        {
            // cout << word << " ";

            if (word.compare(search_string) == 0 && start)
            {
                counting[j].chapter_number = j;
                counting[j].count++;
            }
            if (word.compare("CHAPTER") == 0)
            {
                j++;
                start = 1;
            }
            fr >> word;
        }

        sort(counting.begin(), counting.end(), comp);
        if (counting[0].count != 0)
        {
            cout << "List of Chapters with most frequency of the word " << search_string << " is:" << endl;
            for (int i = 0; i < 5; i++)
            {
                if (counting[i].count != 0)
                    cout << "CHAPTER " << counting[i].chapter_number << " with " << counting[i].count << " frequency" << endl;
            }
        }
        else
            cout << "No such word as " << search_string << " found" << endl;
    }
    if (books[x - 1].type.compare("Play") == 0)
    {
        cout << "Enter the Character you want to search: (in upper case)" << endl;
        cin >> search_string;
        transform(search_string.begin(), search_string.end(), search_string.begin(), ::toupper);
        search_string = search_string.append(".");
        // cout << search_string << endl;
        vector<string> characters;
        vector<string> output;
        ifstream fr(filename);

        if (!fr.is_open())
        {
            cout << "File not found" << endl;
            return;
        }
        string word;
        fr >> word;
        int j = 0;
        int start = 0; // to start from scene 1 and avoid the above part
        int name_there = 0;
        while (fr.good())
        {
            if (is_upper(word) && start && word.compare("ACT") != 0 && word.compare("SCENE") != 0 && word.size() >= 5) // word size to avoid roman numbers
            {
                characters.push_back(word);

                // cout << word << " ";
            }
            if (word.compare("SCENE") == 0)
            {
                start = 1;
                if (name_there)
                {

                    for (int i = 0; i < characters.size(); i++)
                    {
                        if (finder(output, characters[i]) != 1)
                            output.push_back(characters[i]);
                    }
                }

                characters.clear();
                name_there = 0;
            }
            if (word.compare(search_string) == 0 && start)
            {
                name_there = 1;
            }

            fr >> word;
        }

        for (int i = 0; i < output.size(); i++)
        {
            cout << output[i] << endl;
        }
    }

    cout << endl
         << "--------------------------------------------------------------" << endl;
    // cout << count.size() << endl;
}
int main()
{
    read_index();
    exp("./Books");

    read_folder("./Books");
    print_index();
    int option = 1;
    while (option)
    {
        cout << "CHOOSE ANY OPERATION FROM THE FOLLOWING" << endl;
        cout << "1.PRINT ALL THE BOOKS WITH AUTHOR AND TITLE" << endl;
        cout << "2.SEARCH A BOOK" << endl;
        cout << "3.DISPLAY A BOOK" << endl;
        cout << "4.SELECT A BOOK" << endl;
        cout << "0. Exit" << endl;

        cin >> option;

        if (option == 1)

        {
            print_data();

            cout << n << endl;
        }
        if (option == 2)
        {
            string input;

            cout << "Enter the name of title or author you want to search" << endl;
            cin >> input;
            search_book(input);
        }
        if (option == 3)
        {
            int input;
            input = choose_book();
            display_book(input);
        }
        if (option == 4)
        {
            int inp;
            inp = choose_book();

            case_3(inp);
        }
    }
}
// Case 1 ka aage ka karna hai  XXXX
// Case 2 m while loop lagana hai  XXXx
// Case 3 i. Novel XXXXX
//   ii. Play XXXXXX
// book disply karana hai