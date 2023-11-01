#include <iostream>
#include <string>
using namespace std;

class Page {
public:
    string url;
    Page* next;
    Page* prev;

    Page(const string& url) : url(url), next(nullptr), prev(nullptr) {}
};

class Tab {
public:
    string tabName;
    Tab* next;
    Tab* prev;
    Page* currentPage;

    Tab(const string& name) : tabName(name), next(nullptr), prev(nullptr), currentPage(nullptr) {}
};

class Window {
public:
    string windowName;
    Window* next;
    Window* prev;
    Tab* tabList;

    Window(const string& name) : windowName(name), next(nullptr), prev(nullptr), tabList(nullptr) {}
};

class HistoryEntry {
public:
    string url;
    HistoryEntry* next;
    HistoryEntry* prev;

    HistoryEntry(const string& url) : url(url), next(nullptr), prev(nullptr) {}
};

class Browser {
public:
    Window* currentWindow;
    Tab* currentTab;
    int windowCounter;
    int tabCounter;
    HistoryEntry* history;

    Browser() : currentWindow(nullptr), currentTab(nullptr), windowCounter(1), tabCounter(1), history(nullptr) {
        // Khởi tạo ban đầu với một cửa sổ và một tab
        currentWindow = new Window("Window 1");
        currentTab = new Tab("Tab 1");
        currentWindow->tabList = currentTab;
        currentTab->currentPage = nullptr;
    }

    void addWindow() {
        Window* newWindow = new Window("Window " + to_string(windowCounter++));
        if (!currentWindow) {
            currentWindow = newWindow;
        }
        else {
            newWindow->prev = currentWindow;
            currentWindow->next = newWindow;
            currentWindow = newWindow;
        }

        // Khởi tạo một tab mới trong cửa sổ mới
        currentTab = new Tab("Tab " + to_string(tabCounter++));
        currentWindow->tabList = currentTab;
        currentTab->currentPage = nullptr;
    }

    void addTab() {
        if (currentWindow) {
            Tab* newTab = new Tab("Tab " + to_string(tabCounter++));
            if (!currentWindow->tabList) {
                currentWindow->tabList = newTab;
            }
            else {
                newTab->prev = currentTab;
                currentTab->next = newTab;
            }
            currentTab = newTab;
            currentTab->currentPage = nullptr;
        }
    }

    void addPage(const string& url) {
        if (currentTab) {
            Page* newPage = new Page(url);
            if (currentTab->currentPage) {
                newPage->prev = currentTab->currentPage;
                currentTab->currentPage->next = newPage;
            }
            currentTab->currentPage = newPage;

            // Thêm vào lịch sử
            if (history) {
                HistoryEntry* historyEntry = new HistoryEntry(url);
                if (history->next) {
                    history->next->prev = historyEntry;
                }
                historyEntry->next = history;
                history = historyEntry;
            }
            else {
                history = new HistoryEntry(url);
            }
        }
    }

    void nextTab() {
        if (currentTab && currentTab->next) {
            currentTab = currentTab->next;
        }
    }

    void backTab() {
        if (currentTab && currentTab->prev) {
            currentTab = currentTab->prev;
        }
    }

    void nextWindow() {
        if (currentWindow && currentWindow->next) {
            currentWindow = currentWindow->next;
            currentTab = currentWindow->tabList;
        }
    }

    void backWindow() {
        if (currentWindow && currentWindow->prev) {
            currentWindow = currentWindow->prev;
            currentTab = currentWindow->tabList;
        }
    }

    void nextPage() {
        if (currentTab && currentTab->currentPage && currentTab->currentPage->next) {
            currentTab->currentPage = currentTab->currentPage->next;
            addPageToHistory(currentTab->currentPage->url);
        }
    }

    void backPage() {
        if (currentTab && currentTab->currentPage && currentTab->currentPage->prev) {
            currentTab->currentPage = currentTab->currentPage->prev;
            addPageToHistory(currentTab->currentPage->url);
        }
    }

    void addPageToHistory(const string& url) {
        if (currentTab) {
            if (history) {
                HistoryEntry* historyEntry = new HistoryEntry(url);
                if (history->next) {
                    history->next->prev = historyEntry;
                }
                historyEntry->next = history;
                history = historyEntry;
            }
            else {
                history = new HistoryEntry(url);
            }
        }
    }

    void printHistory() {
        HistoryEntry* current = history;
        cout << "Browser History:" << endl;
        while (current) {
            cout << "  - " << current->url << endl;
            current = current->next;
        }
    }

    void printBrowser() {
        if (currentWindow) {
            cout << "Current Window: " << currentWindow->windowName << endl;
            if (currentTab) {
                cout << "  Current Tab: " << currentTab->tabName << endl;
                if (currentTab->currentPage) {
                    cout << "    - Page: " << currentTab->currentPage->url << endl;
                }
            }
        }
    }
};

int main() {
    Browser browser;

    cout << "Initial Browser:" << endl;
    browser.printBrowser();
    browser.addWindow();
    browser.backWindow();
    browser.printBrowser();



    return 0;
}
