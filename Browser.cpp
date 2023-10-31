#include <iostream>
#include <string>
using namespace std;

struct Page {
    string url;
    Page* next;
    Page* prev;

    Page(const string& url) : url(url), next(nullptr), prev(nullptr) {}
};

struct Tab {
    string tabName;
    Tab* next;
    Tab* prev;
    Page* currentPage;

    Tab(const string& name) : tabName(name), next(nullptr), prev(nullptr), currentPage(nullptr) {}
};

struct Window {
    string windowName;
    Window* next;
    Window* prev;
    Tab* tabList;

    Window(const string& name) : windowName(name), next(nullptr), prev(nullptr), tabList(nullptr) {}
};

struct HistoryEntry {
    string url;
    HistoryEntry* next;
    HistoryEntry* prev;

    HistoryEntry(const string& url) : url(url), next(nullptr), prev(nullptr) {}
};

struct BookmarkEntry {
    string url;
    BookmarkEntry* next;
    BookmarkEntry* prev;

    BookmarkEntry(const string& url) : url(url), next(nullptr), prev(nullptr) {}
};

struct Browser {
    Window* currentWindow;
    Tab* currentTab;
    int windowCounter;
    int tabCounter;
    HistoryEntry* history;
    BookmarkEntry* bookmark;

    Browser() : currentWindow(nullptr), currentTab(nullptr), windowCounter(1), tabCounter(1), history(nullptr), bookmark(nullptr) {
        currentWindow = new Window("Window 1");
        currentTab = new Tab("Tab 1");
        currentWindow->tabList = currentTab;
        currentTab->currentPage = nullptr;
    }

    void addWindow() {
        Window* newWindow = new Window("Window " + to_string(windowCounter++));
        if (!currentWindow) {
            currentWindow = newWindow;
        } else {
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
            } else {
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
            } else {
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
            addPageToHistory(currentTab->currentPage->url);
            currentTab->currentPage = currentTab->currentPage->next;
        }
    }

    void backPage() {
        if (currentTab && currentTab->currentPage && currentTab->currentPage->prev) {
            addPageToHistory(currentTab->currentPage->url);
            currentTab->currentPage = currentTab->currentPage->prev;
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
            } else {
                history = new HistoryEntry(url);
            }
        }
    }

    void addPageToBookmark() {
        if (currentTab && currentTab->currentPage) {
            string url = currentTab->currentPage->url;
            if (bookmark) {
                BookmarkEntry* bookmarkEntry = new BookmarkEntry(url);
                if (bookmark->next) {
                    bookmark->next->prev = bookmarkEntry;
                }
                bookmarkEntry->next = bookmark;
                bookmark = bookmarkEntry;
            } else {
                bookmark = new BookmarkEntry(url);
            }
        }
    }

    void showBookmarks() {
        BookmarkEntry* current = bookmark;
        cout << "Bookmarks:" << endl;
        while (current) {
            cout << "  - " << current->url << endl;
            current = current->next;
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
	browser.printBrowser();
	browser.printHistory();
    return 0;
}
