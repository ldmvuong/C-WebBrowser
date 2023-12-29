#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <limits> 
using namespace std;

struct NodePage
{
    string url;
    NodePage* next;
    NodePage* prev;

    NodePage(string val)
    {
        url = val;
        next = nullptr;
        prev = nullptr;
    }
};

class Tab
{
public:
    NodePage* head;
    NodePage* tail;
    NodePage* currentPage;
    int count = 0;

    Tab()
    {
        head = nullptr;
        tail = nullptr;
        currentPage = new NodePage("Tim kiem Goggle hoac Nhap mot URL");
    }

    void addTail(string url)
    {
        NodePage* newNode = new NodePage(url);

        if (tail == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            NodePage* currentNext = currentPage->next;
            while (currentNext != nullptr)
            {
                NodePage* temp = currentNext;
                currentNext = currentNext->next;
                delete temp;
                count--;
            }

            tail = currentPage;
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        currentPage = newNode;
        count++;
    }

      bool nextPage()
    {
        if (currentPage->next == nullptr)
        {
            return false;
        }
        else
            currentPage = currentPage->next;
        return true;
    }

    bool backPage()
    {
        if (currentPage->prev == nullptr)
        {
            return false;
        }
        else
            currentPage = currentPage->prev;
        return true;
    }

    
    bool isEmpty()
    {
        return head == nullptr;
    }
};

struct NodeTab
{
    Tab tab;
    NodeTab* next;
    NodeTab* prev;

    NodeTab(Tab tab)
    {
        tab = tab;
        next = nullptr;
        prev = nullptr;
    }
};

class Window
{
public:
    NodeTab* head;
    NodeTab* tail;
    NodeTab* currentTab;
    int count = 0;

    Window()
    {
        head = nullptr;
        tail = nullptr;
    }

    void addTail(Tab tab)
    {
        NodeTab* newNode = new NodeTab(tab);
        currentTab = newNode;
        if (tail == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    void deleteHead()
    {
        if (head != nullptr)
        {
            NodeTab* temp = head;
            head = head->next;

            if (head != nullptr)
            {
                head->prev = nullptr;
            }
            else
            {
                tail = nullptr;
            }

            currentTab = head;
            delete temp;
            count--;
        }
        // else exit
    }

    void deleteTail()
    {
        if (tail != nullptr)
        {
            NodeTab* temp = tail;
            tail = tail->prev;

            if (tail != nullptr)
            {
                tail->next = nullptr;
            }
            else
            {
                head = nullptr;
            }
            currentTab = tail;
            delete temp;
            count--;
        }
        // else exit
    }

    bool deleteCurrent()
    {
        if (head->next == nullptr)
        {
            return false;
        }
        if (currentTab == head)
        {
            currentTab = currentTab->next;
            deleteHead();
        }
        else if (currentTab == tail)
        {
            currentTab = currentTab->prev;
            deleteTail();
        }
        else
        {
            NodeTab* temp = currentTab;

            currentTab = currentTab->prev;
            currentTab->next = temp->next;
            temp->next->prev = currentTab;

            delete temp;
            count--;
        }
        return true;
    }

    
    bool nextTab()
    {
        if (currentTab->next == nullptr)
        {
            return false;
        }
        else
            currentTab = currentTab->next;
        return true;
    }

    bool backTab()
    {
        if (currentTab->prev == nullptr)
            return false;
        else
            currentTab = currentTab->prev;
        return true;
    }

    int getCurrentIndex()
    {
        int i = 1;
        for (NodeTab* p = head; p != nullptr; p = p->next)
        {
            if (p == currentTab)
            {
                return i;
            }
            i++;
        }
    }

    bool isEmpty()
    {
        return head == nullptr;
    }
};

struct NodeWindow
{
    Window window;
    NodeWindow* next;
    NodeWindow* prev;

    NodeWindow(Window wd)
    {
        window = wd;
        next = nullptr;
        prev = nullptr;
    }
};

class ListWindow
{
public:
    NodeWindow* head;
    NodeWindow* tail;
    NodeWindow* currentWindow;
    int count = 0;

    ListWindow()
    {
        head = nullptr;
        tail = nullptr;
    }

    void addTail(Window window)
    {
        NodeWindow* newNode = new NodeWindow(window);
        currentWindow = newNode;
        if (tail == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    void deleteHead()
    {
        if (head != nullptr)
        {
            NodeWindow* temp = head;
            head = head->next;

            if (head != nullptr)
            {
                head->prev = nullptr;
            }
            else
            {
                tail = nullptr;
            }

            currentWindow = head;
            delete temp;
            count--;
        }
        // else exit
    }

    void deleteTail()
    {
        if (tail != nullptr)
        {
            NodeWindow* temp = tail;
            tail = tail->prev;

            if (tail != nullptr)
            {
                tail->next = nullptr;
            }
            else
            {
                head = nullptr;
            }

            currentWindow = tail;
            delete temp;
            count--;
        }
        // else exit
    }

    bool deleteCurrent()
    {
        if (head->next == nullptr)
        {           
            return false;
        }

        if (currentWindow == head)
        {
            currentWindow = currentWindow->next;
            deleteHead();
        }
        else if (currentWindow == tail)
        {
            currentWindow = currentWindow->prev;
            deleteTail();
        }
        else
        {
            NodeWindow* temp = currentWindow;

            currentWindow = currentWindow->prev;
            currentWindow->next = temp->next;
            temp->next->prev = currentWindow;

            delete temp;
            count--;
        }
        return true;
    }

    bool nextWindow()
    {
        if (currentWindow->next == nullptr)
        {
            return false;
        }
        else
            currentWindow = currentWindow->next;
        return true;

    }
    bool backWindow()
    {
        if (currentWindow->prev == nullptr)
        {
            return false;
        }
        else
            currentWindow = currentWindow->prev;
        return true;
    }

    int getCurrentIndex()
    {
        int i = 1;
        for (NodeWindow* p = head; p != nullptr; p = p->next)
        {
            if (p == currentWindow)
            {
                return i;
            }
            i++;
        }
    }
};

struct NodeBookmark
{
    string url;
    NodeBookmark* next;
    NodeBookmark* prev;

    NodeBookmark(string page)
    {
        url = page;
        next = nullptr;
        prev = nullptr;
    }
};

class ListBookmark
{
public:
    NodeBookmark* head;
    NodeBookmark* tail;
    NodeBookmark* currentPage;
    int count = 0;


    ListBookmark()
    {
        head = nullptr;
        tail = nullptr;
    }

    void addTail(string url)
    {

        NodeBookmark* newNode = new NodeBookmark(url);
        currentPage = newNode;
        if (tail == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    void deleteHead()
    {
        if (head != nullptr)
        {
            NodeBookmark* temp = head;
            head = head->next;

            if (head != nullptr)
            {
                head->prev = nullptr;
            }
            else
            {
                tail = nullptr;
            }

            delete temp;
            count--;
        }
        else
        {
            cout << "Khong co danh dau trang nao !!!" << endl;
        }
    }

    void deleteTail()
    {
        if (tail != nullptr)
        {
            NodeBookmark* temp = tail;
            tail = tail->prev;

            if (tail != nullptr)
            {
                tail->next = nullptr;
            }
            else
            {
                head = nullptr;
            }

            delete temp;
            count--;
        }
        else
        {
            cout << "Khong co danh dau trang nao !!!" << endl;
        }
    }

    void deleteCurrent()
    {
        if (head == nullptr)
        {
            return;
        }

        if (currentPage == head)
        {
            currentPage = currentPage->next;
            deleteHead();
        }
        else if (currentPage == tail)
        {
            currentPage = currentPage->prev;
            deleteTail();
        }
        else
        {
            NodeBookmark* temp = currentPage;
            currentPage = currentPage->prev;
            currentPage->next = temp->next;
            temp->next->prev = currentPage;
            delete temp;
            count--;
        }
    }

    void display()
    {
        NodeBookmark* current = head;
        int i = 1;
        cout << "Bookmark: ";
        while (current != nullptr)
        {
            cout << i << "|" << current->url << "\t";
            i++;
            current = current->next;
        }
        cout << endl << endl;
    }

    int getCurrentIndex()
    {
        int i = 1;
        for (NodeBookmark* p = head; p != nullptr; p = p->next)
        {
            if (p == currentPage)
            {
                return i;
            }
            i++;
        }
    }

    bool isEmpty()
    {
        return head == nullptr;
    }

    int getIndex(string value) {
        NodeBookmark* current = head;
        int index = 0;

        while (current != nullptr) {
            if (current->url == value) {
                return index;
            }
            current = current->next;
            index++;
        }
        return -1;
    }

    string getDataAtIndex(int index) {
        if (index < 0 || index >= count || count == 0) {
            cerr << "Khong tim thay thong tin tai vi tri nay..." << endl;
            return "Error";
        }

        NodeBookmark* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        return current->url;
    }

    void deleteNode(int index) {
        if (index < 0 || index >= count || count == 0) {
            return;
        }

        NodeBookmark* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        if (current == currentPage)
        {
            deleteCurrent();
            return;
        }
        if (current == head) {
            head = current->next;
            if (head) {
                head->prev = nullptr;
            }
        }
        else if (current == tail) {
            tail = current->prev;
            tail->next = nullptr;
        }
        else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        delete current;
        count--;
    }
    void checkMap(string url) {
        NodeBookmark* current = head;

        while (current != nullptr)
        {
            if (current->url == url)
            {
                return;
            }
            current = current->next;
        }
        addTail(url);
    }
};

struct NodeHistory
{
    string his;
    NodeHistory* next;
    NodeHistory* prev;

    NodeHistory(string url)
    {
        his = url;
        next = nullptr;
        prev = nullptr;
    }
};

class ListHistory
{
public:
    NodeHistory* head;
    NodeHistory* tail;
    NodeHistory* currentHistory;
    int count = 0;

    ListHistory()
    {
        head = nullptr;
        tail = nullptr;
    }

    void addTail(string url)
    {
        NodeHistory* newNode = new NodeHistory(url);
        currentHistory = newNode;
        if (tail == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    void deleteHead()
    {
        if (head != nullptr)
        {
            NodeHistory* temp = head;
            head = head->next;

            if (head != nullptr)
            {
                head->prev = nullptr;
            }
            else
            {
                tail = nullptr;
            }

            currentHistory = head;
            delete temp;
            count--;
        }
        else
        {
            cout << "Lich su truy cap trong..." << endl;
        }
    }

    void deleteTail()
    {
        if (tail != nullptr)
        {
            NodeHistory* temp = tail;
            tail = tail->prev;

            if (tail != nullptr)
            {
                tail->next = nullptr;
            }
            else
            {
                head = nullptr;
            }
            currentHistory = tail;
            delete temp;
            count--;
        }
        else
        {
            cout << "Lich su truy cap trong..." << endl;
        }
    }

    void clearHistory()
    {
        while (head != nullptr)
        {
            deleteHead();
        }
    }

    void display()
    {
        cout << "History browser:"; cout << endl;
        NodeHistory* current = head;
        int i = 1;
        while (current != nullptr)
        {
            cout << i++ << "| " << current->his << endl;
            current = current->next;
        }
        cout << endl;
    }

    void deleteCurrent()
    {
        if (head == nullptr)
        {
            cout << "Khong co Page nao de xoa." << endl << endl;
            return;
        }
        if (currentHistory == head)
        {
            currentHistory = currentHistory->next;
            deleteHead();
        }
        else if (currentHistory == tail)
        {
            currentHistory = currentHistory->prev;
            deleteTail();
        }
        else
        {
            NodeHistory* temp = currentHistory;
            currentHistory = currentHistory->prev;
            currentHistory->next = temp->next;
            temp->next->prev = currentHistory;
            delete temp;
            count--;
        }
    }
    void deleteNode(int index) {
        if (index < 0 || index >= count || count == 0) {
            return;
        }

        NodeHistory* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        if (current == currentHistory)
        {
            deleteCurrent();
            return;
        }
        if (current == head) {
            head = current->next;
            if (head) {
                head->prev = nullptr;
            }
        }
        else if (current == tail) {
            tail = current->prev;
            tail->next = nullptr;
        }
        else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        delete current;
        count--;
    }
    string getDataAtIndex(int index)
    {
        if (index < 0 || index >= count || count == 0) {
            cerr << "Khong tim thay thong tin tai vi tri nay..." << endl;
            return "Error";
        }

        NodeHistory* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        return current->his;
    }
    bool isEmpty()
    {
        return head == nullptr;
    }

};

void SET_COLOR(int color)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

void gotoXY(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x, y };
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

void menuBrowser(ListWindow listWindow, ListBookmark listBookmark, ListHistory listHistory)
{
    
    
    SET_COLOR(3);

    string pageName;
    if (listWindow.currentWindow->window.isEmpty())
    {
        pageName = "Tim kiem Goggle hoac Nhap mot URL";
    }
    else
    {
        pageName = listWindow.currentWindow->window.currentTab->tab.currentPage->url;
    }

    cout << char(218);      for (int i = 0; i < 150; i++) { cout << char(196); }      cout << char(191) << endl;
    cout << char(179) << "                                                                      WINDOW " << listWindow.getCurrentIndex() << "                                                        Press 0. Exit   "; gotoXY(151, 1);     cout << char(179) << endl;
    cout << char(179) << "                                                                                                                                                      "; gotoXY(151, 2); cout << char(179) << endl;
    cout << char(179) << "   TAB|  " << listWindow.currentWindow->window.getCurrentIndex() << "                                                                                 "; gotoXY(151, 3); cout << char(179) << endl;
    cout << char(179) << "  PAGE|  " << pageName << "                                                                                                                           "; gotoXY(151, 4); cout << char(179) << endl;
    cout << char(179); listBookmark.display();
    gotoXY(151, 5); cout << char(179) << endl;
    cout << char(179) << "                                                                                                                                                      "; gotoXY(151, 6); cout << char(179) << endl;
    cout << char(179) << "                                                                                                                                                      "; gotoXY(151, 7); cout << char(179) << endl;
    cout << char(179) << "                                             ________ ________    ________  ________.____     ___________                                             "; gotoXY(151, 8); cout << char(179) << endl;
    cout << char(179) << "                                            /  _____/ \\_____  \\  /  _____/ /  _____/|    |    \\_   _____/                                          "; gotoXY(151, 9); cout << char(179) << endl;
    cout << char(179) << "                                           /   \\  ___  /   |   \\/   \\  ___/   \\  ___|    |     |    __)_                                          "; gotoXY(151, 10); cout << char(179) << endl;
    cout << char(179) << "                                           \\    \\_\\  \\/    |    \\    \\_\\  \\    \\_\\  \\    |___  |        \\                                 "; gotoXY(151, 11); cout << char(179) << endl;
    cout << char(179) << "                                            \\______  /\\_______  /\\______  /\\______  /_______ \\/_______  /                                        "; gotoXY(151, 12); cout << char(179) << endl;
    cout << char(179) << "                                                   \\/         \\/        \\/        \\/        \\/        \\/                                        "; gotoXY(151, 13); cout << char(179) << endl;
    cout << char(179) << "                                                                                                                                                      "; gotoXY(151, 14); cout << char(179) << endl;
    cout << char(179) << "                                                                                                                                                      "; gotoXY(151, 15); cout << char(179) << endl;
    cout << char(179) << "                                                                                                                                                      "; gotoXY(151, 16); cout << char(179) << endl;
    cout << char(179) << "                                                                                                                                                      "; gotoXY(151, 17); cout << char(179) << endl;
    cout << char(179) << "                                                                                                                                                      "; gotoXY(151, 18); cout << char(179) << endl;
    cout << char(179) << "                                                                                                                                                      "; gotoXY(151, 19); cout << char(179) << endl;
    cout << char(179) << "                                                                                                                                                      "; gotoXY(151, 20); cout << char(179) << endl;
    cout << char(179) << "                       Press 1. New Page                                                      Press 8. Next Window                                    "; gotoXY(151, 21); cout << char(179) << endl;
    cout << char(179) << "                       Press 2. Next Page                                                     Press 9. Back Window                                    "; gotoXY(151, 22); cout << char(179) << endl;
    cout << char(179) << "                       Press 3. Back Page                                                     Press 10. Add Page To Bookmark                          "; gotoXY(151, 23); cout << char(179) << endl;
    cout << char(179) << "                       Press 4. New Tab                                                       Press 11. Delete Current Tab                            "; gotoXY(151, 24); cout << char(179) << endl;
    cout << char(179) << "                       Press 5. Back Tab                                                      Press 12. Delete Current Window                         "; gotoXY(151, 25); cout << char(179) << endl;
    cout << char(179) << "                       Press 6. Next Tab                                                      Press 13. Show History                                  "; gotoXY(151, 26); cout << char(179) << endl;
    cout << char(179) << "                       Press 7. New Window                                                    Press 14. Show Bookmark                                 "; gotoXY(151, 27); cout << char(179) << endl;
    cout << char(179) << "                                                                                                                                                      " << char(179) << endl;
    cout << char(179) << "                                                                                                                                                      " << char(179) << endl;
    cout << char(179) << "                                                                                                                                                      " << char(179) << endl;
    cout << char(192);      for (int i = 0; i < 150; i++) { cout << char(196); }      cout << char(217) << endl;

}

void menuHistory() {
    
    cout << "------------HISTORY MENU-------------" << endl;
    cout << "|                                   |" << endl;
    cout << "|  Press 1. Truy cap lich su        |" << endl;
    cout << "|  Press 2. Xoa mot mot lich su     |" << endl;
    cout << "|  Press 3. Xoa toan bo lich su     |" << endl;
    cout << "|  Press 0. Thoat khoi xem lich su  |" << endl;
    cout << "|                                   |" << endl;
    cout << "-------------------------------------" << endl;
    cout << "Moi nhap lua chon: ";
}

void menuHistoryEmpty() {
    
    cout << "--------------HISTORY---------------" << endl;
    cout << "|                                  |" << endl;
    cout << "|  Lich su trong ...               |" << endl;
    cout << "|  Press 0. Thoat khoi xem lich su |" << endl;
    cout << "|                                  |" << endl;
    cout << "------------------------------------" << endl;
    cout << "Moi nhap lua chon: ";
}

void menuBookmark() {
    cout << "-------------BOOKMARK MENU--------------" << endl;
    cout << "|                                      |" << endl;
    cout << "|  Press 1. Truy cap mot bookmark      |" << endl;
    cout << "|  Press 2. Delete Bookmark            |" << endl;
    cout << "|  Press 0. Exit Menu Bookmark         |" << endl;
    cout << "|                                      |" << endl;
    cout << "----------------------------------------" << endl;
    cout << " Moi nhap lua chon: ";
}
int main() {

    ListWindow listWindow;
    ListHistory listHistory;
    ListBookmark listBookmark;

    Window newWindow;
    listWindow.addTail(newWindow);

    Tab newTab;
    listWindow.currentWindow->window.addTail(newTab);
    int choose;
    do
    {
        menuBrowser(listWindow, listBookmark, listHistory);
        cout << "Moi nhap lua chon: ";
        cin >> choose;       
        
        switch (choose) 
        {

        case 1:
        {
            string url;
            cout << "Moi nhap URL: ";
            cin >> url;
            listWindow.currentWindow->window.currentTab->tab.addTail(url);
            listHistory.addTail(url);
            system("cls");
            break;
        }

        case 2:
        {
            system("cls");
            bool check = listWindow.currentWindow->window.currentTab->tab.nextPage();
            break;
        }
        case 3:
        {
            system("cls");
            bool check = listWindow.currentWindow->window.currentTab->tab.backPage();
            break;
        }

        case 4:
        {
            system("cls");
            Tab newTab;
            listWindow.currentWindow->window.addTail(newTab);
            break;
        }

        case 5:
        {
            system("cls");
            bool check = listWindow.currentWindow->window.backTab();
            break;
        }

        case 6:
        {
            system("cls");
            bool check = listWindow.currentWindow->window.nextTab();
            break;
        }

        case 7:
        {
            system("cls");
            Window newWindow;
            listWindow.addTail(newWindow);

            Tab newTab;
            listWindow.currentWindow->window.addTail(newTab);
            break;
        }

        case 8:
        {
            system("cls");
            bool check = listWindow.nextWindow();
            break;
        }

        case 9:
        {
            system("cls");
            bool check = listWindow.backWindow();
            break;
        }

        case 10:
        {
            system("cls");
            string url = listWindow.currentWindow->window.currentTab->tab.currentPage->url;
            listBookmark.checkMap(url);
            break;
        }

        case 11:
        {
            system("cls");
            bool checktab = listWindow.currentWindow->window.deleteCurrent();
            if (!checktab)
            {
                bool check = listWindow.deleteCurrent();
                if (!check) {
                    choose = 0;
                    system("cls");
                }
            }
            system("cls");
            break;

        }

        case 12:
        {
            system("cls");
            bool check = listWindow.deleteCurrent();
            if (!check)
            {
                choose = 0;
                system("cls");
            }
            break;
        }

        case 13:
        {
            system("cls");
            int chon = 0;
            do
            {
                               
                bool check = listHistory.isEmpty();
                if (check) {
                    menuHistoryEmpty();                    
                }
                else {
                    listHistory.display();
                    menuHistory();
                }                
                cin >> chon;

                switch (chon)
                {
                case 1:
                {

                    system("cls");
                    listHistory.display();
                    int num;
                    cout << endl;
                    cout << "Chon vi tri page ban muon truy cap : ";
                    cin >> num;
                    string url = listHistory.getDataAtIndex(num - 1);
                    while (url == "Error")
                    {
                        
                        cout << "Vui long chon lai : ";
                        cin >> num;
                        url = listHistory.getDataAtIndex(num - 1);
                    }
                    listWindow.currentWindow->window.currentTab->tab.addTail(url);
                    listHistory.addTail(url);
                    chon = 0;
                    system("cls");
                    break;
                }
                case 2:
                {
                    system("cls");
                    listHistory.display();
                    int num;
                    cout << endl;
                    cout << "Chon vi tri page trong lich su ma ban muon xoa: ";
                    cin >> num;
                    string url = listHistory.getDataAtIndex(num - 1);
                    while (url == "Error")
                    {
                        
                        cout << "Vui long chon lai : ";
                        cin >> num;
                        url = listHistory.getDataAtIndex(num - 1);
                    }
                    listHistory.deleteNode(num - 1);
                    system("cls");
                    break;
                }
                case 3:
                {
                    system("cls");
                    listHistory.clearHistory();
                    system("cls");
                    break;
                }
                default:
                    if (chon != 0)
                    {
                        system("cls");
                        cout << "Dong lenh cua ban khong hop le !!!" << endl; Sleep(1000);
                        system("cls");
                    }
                    break;
                }
            } while (chon != 0);
            system("cls");
            break;
        }

        case 14:
        {
            system("cls");
            bool isempty = listBookmark.isEmpty();
            if (isempty)
            {
                cout << "Khong co danh dau trang nao !!!" << endl;
                Sleep(1000);
                menuBrowser(listWindow, listBookmark, listHistory);
                cout << "Moi nhap lua chon: ";
            }
            else
            {
                int option = 0;
                do
                {
                    listBookmark.display();
                    menuBookmark();
                    cin >> option;

                    switch (option)
                    {
                    case 1:
                    {
                        system("cls");
                        listBookmark.display();
                        int num;
                        cout << endl;
                        cout << "Chon vi tri thanh dau trang ma ban muon truy cap ngay: ";
                        cin >> num;
                        string url = listBookmark.getDataAtIndex(num - 1);
                        while (url == "Error")
                        {
                            
                            cout << "Vui long chon lai : ";
                            cin >> num;
                            url = listBookmark.getDataAtIndex(num - 1);
                        }

                        listWindow.currentWindow->window.currentTab->tab.addTail(url);
                        listHistory.addTail(url);
                        option = 0;
                        system("cls");
                        break;
                    }
                    case 2:
                    {
                        system("cls");
                        listBookmark.display();
                        int num;
                        cout << endl;
                        cout << "Chon vi tri thanh dau trang ma ban muon xoa: ";
                        cin >> num;
                        string url = listBookmark.getDataAtIndex(num - 1);
                        while (url == "Error")
                        {
                            
                            cout << "Vui long chon lai : ";
                            cin >> num;
                            string url = listBookmark.getDataAtIndex(num - 1);
                        }

                        listBookmark.deleteNode(num - 1);
                        bool isempty = listBookmark.isEmpty();
                        if (isempty)
                        {
                            system("cls");
                            cout << "Khong co danh dau trang nao !!!" << endl;                                 
                            Sleep(1000);
                            system("cls");  
                            option = 0;
                            break;
                        }
                        else
                        {
                            system("cls");
                            break;
                        }
                    }                          
                    
                    default:
                        if (option != 0)
                        {
                            system("cls");
                            cout << "Dong lenh cua ban khong hop le !!!" << endl; Sleep(1000);
                            system("cls");
                        }
                        break;
                    }
                } while (option != 0);
            }
            system("cls");
            break;
        }

        default:
            if (choose != 0)
            {
                system("cls");
                cout << "Dong lenh cua ban khong hop le !!!" << endl; Sleep(1000);
                system("cls");
            }
            break;
    }       

    } while (choose != 0);
    return 0;
}
