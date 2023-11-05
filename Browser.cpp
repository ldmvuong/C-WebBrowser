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

class BookmarkEntry {
public:
    string url;
    BookmarkEntry* next;

    BookmarkEntry(const string& url) : url(url), next(nullptr) {}
};

class Browser {
public:
    Window* currentWindow;
    Tab* currentTab;
    int windowCounter;
    int tabCounter;
    HistoryEntry* history;
    BookmarkEntry* bookmarks;

    Browser() : currentWindow(nullptr), currentTab(nullptr), windowCounter(2), tabCounter(2), history(nullptr), bookmarks(nullptr) {
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
            while (currentTab->next) {
                currentTab = currentTab->next;
            }
        }
    }

    void backWindow() {
        if (currentWindow && currentWindow->prev) {
            currentWindow = currentWindow->prev;
            currentTab = currentWindow->tabList;
            while (currentTab->next) {
                currentTab = currentTab->next;
            }
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

    void addBookmark() {
        if (currentTab && currentTab->currentPage) {
            BookmarkEntry* newBookmark = new BookmarkEntry(currentTab->currentPage->url);
            if (bookmarks) {
                newBookmark->next = bookmarks;
            }
            bookmarks = newBookmark;
        }
    }

    void printBookmarks() {
        BookmarkEntry* current = bookmarks;
        cout << "Bookmarks:" << endl;
        while (current) {
            cout << "  - " << current->url << endl;
            current = current->next;
        }
    }

    void clearHistory() {
        HistoryEntry* current = history;
        while (current) {
            HistoryEntry* temp = current;
            current = current->next;
            delete temp;
        }
        history = nullptr;
    }

    void clearBookmarks() {
        BookmarkEntry* current = bookmarks;
        while (current) {
            BookmarkEntry* temp = current;
            current = current->next;
            delete temp;
        }
        bookmarks = nullptr;
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
    int choice;
    browser.printBrowser();
    while (true) {
        cout << "\n=== Simple Browser Menu ===" << endl;
        cout << "1. Add Window" << endl;
        cout << "2. Add Tab" << endl;
        cout << "3. Add Page" << endl;
        cout << "4. Next Tab" << endl;
        cout << "5. Back Tab" << endl;
        cout << "6. Next Window" << endl;
        cout << "7. Back Window" << endl;
        cout << "8. Next Page" << endl;
        cout << "9. Back Page" << endl;
        cout << "10. Add Bookmark" << endl;
        cout << "11. Print Bookmarks" << endl;
        cout << "12. Print Browser" << endl;
        cout << "13. Print History" << endl;
        cout << "14. Clear History" << endl;
        cout << "15. Clear Bookmarks" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            browser.addWindow();
            browser.printBrowser();
            break;
        case 2:
            browser.addTab();
            browser.printBrowser();
            break;
        case 3: {
            string url;
            cout << "Enter URL: ";
            cin >> url;
            browser.addPage(url);
            browser.printBrowser();
            break;
        }
        case 4:
            browser.nextTab();
            browser.printBrowser();
            break;
        case 5:
            browser.backTab();
            browser.printBrowser();
            break;
        case 6:
            browser.nextWindow();
            browser.printBrowser();
            break;
        case 7:
            browser.backWindow();
            browser.printBrowser();
            break;
        case 8:
            browser.nextPage();
            browser.printBrowser();
            break;
        case 9:
            browser.backPage();
            browser.printBrowser();
            break;
        case 10:
            browser.addBookmark();
            browser.printBrowser();
            browser.printBookmarks();
            break;
        case 11:
            browser.printBrowser();
            browser.printBookmarks();
            break;
        case 12:
            browser.printBrowser();
            break;
        case 13:
            browser.printBrowser();
            browser.printHistory();
            break;
        case 14:
            browser.clearHistory();
            cout << "Deleted !!! /n";
            break;
        case 15:
            browser.clearBookmarks();
            cout << "Deleted !!! /n";
            break;
        case 0:
            exit(0);
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
}
