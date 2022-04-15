#include <bits/stdc++.h>

using namespace std;

class Pair
{
public:
    int pageId;
    int slotId;
};

class Page
{
public:
    Page *prev;
    Page *next;
    int numRecords;
    int freeSpace;
    int emptySpace;
    vector<int> dir;
    vector<int> data;
};

class HeapFile
{
public:
    HeapFile();
    HeapFile(int);
    ~HeapFile();
    void insert(int, int);
    Pair search(int);
    void print();
    void display();

private:
    Page *head;
    int pageSize;
    int numPages;
};

int main()
{
    int n; // Page size
    cin >> n;

    HeapFile H(n);

    int o;
    while (cin >> o)
    {
        if (o == 1)
        {
            // insert
            int s, key;
            cin >> s >> key;

            H.insert(s, key);
        }

        if (o == 2)
        {
            // status
            // H.print();
            H.display();
        }

        if (o == 3)
        {
            // search
            int val;
            cin >> val;

            Pair p = H.search(val);
            cout << p.pageId << " " << p.slotId << endl;
        }

        if (o == 4)
            break;
    }

    return 0;
}

HeapFile::HeapFile()
{
}

HeapFile::HeapFile(int n)
{
    head = NULL;
    pageSize = n;
    numPages = 0;
}

void HeapFile::insert(int s, int key)
{
    if (s <= 0)
        return;

    // File is empty
    if (head == NULL)
    {
        Page *p = new Page();
        p->prev = NULL;
        p->next = NULL;
        p->freeSpace = s;
        p->numRecords = 1;
        p->dir.push_back(s);
        p->data.push_back(key);

        p->emptySpace = pageSize - 16 - s - 4;

        head = p;
        numPages++;
        return;
    }

    // File is not empty
    Page *t = head;
    Page *l;
    while (t != NULL)
    {
        // Page has space for the record
        if (t->emptySpace >= (s + 4))
        {
            t->freeSpace += s;
            t->numRecords++;
            t->dir.push_back(s);
            t->data.push_back(key);

            t->emptySpace = t->emptySpace - s - 4;

            break;
        }

        // Page does not have enough space
        l = t;
        t = t->next;
    }

    if (t == NULL)
    {
        // New page is required
        t = new Page();
        t->prev = l;
        l->next = t;
        t->next = NULL;
        t->freeSpace = s;
        t->numRecords = 1;
        t->dir.push_back(s);
        t->data.push_back(key);

        t->emptySpace = pageSize - 16 - s - 4;
        numPages++;
    }

    return;
}

Pair HeapFile::search(int val)
{
    Pair p;
    Page *t = head;
    int pg = 0;

    while (t != NULL)
    {
        int k = t->data.size();
        for (int i = 0; i < k; i++)
        {
            if (t->data[i] == val)
            {
                p.pageId = pg;
                p.slotId = i;

                return p;
            }
        }

        pg++;
        t = t->next;
    }

    p.pageId = -1;
    p.slotId = -1;

    return p;
}

void HeapFile::print()
{
    int p = 0;
    cout << numPages << endl;

    Page *t = head;
    while (t != NULL)
    {
        cout << "Page" << p << ": ";
        int k = t->data.size();
        for (int i = 0; i < k; i++)
            cout << t->data[i] << " ";
        cout << endl;

        p++;
        t = t->next;
    }

    return;
}

void HeapFile::display()
{
    cout << numPages;

    Page *t = head;
    while (t != NULL)
    {
        cout << " " << t->numRecords;

        t = t->next;
    }
    cout << endl;

    return;
}

HeapFile::~HeapFile()
{
}