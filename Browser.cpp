#include <iostream>
#include <string>

struct Node {
    std::string data;
    Node* next;
    Node* prev;

    Node(const std::string& value) : data(value), next(NULL), prev(NULL) {}
};

struct DoublyLinkedList {
    Node* head;
    Node* tail;

    DoublyLinkedList() : head(NULL), tail(NULL) {}

    void addTail(const std::string& value) {
        Node* newNode = new Node(value);
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        }
        else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    std::string display() {
        std::string result;
        Node* current = head;
        while (current != NULL) {
            result += current->data + "\n";
            current = current->next;
        }
        return result;
    }

    void clear() {
        Node* current = head;
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = NULL;
        tail = NULL;
    }
};

struct Tab {
    DoublyLinkedList webPages;
    Node* currentPage;

    Tab() : webPages(), currentPage(NULL) {}

    void addWebPage(const std::string& webpage, DoublyLinkedList& history) {
        webPages.addTail(webpage);
        history.addTail(webpage);
        currentPage = webPages.tail;
    }

    void displayCurrentPage() {
        if (currentPage) {
            std::cout << "Current Page: " << currentPage->data << std::endl;
        }
        else {
            std::cout << "No current page available." << std::endl;
        }
    }

    void nextPage(DoublyLinkedList& history) {
        if (currentPage && currentPage->next) {
            currentPage = currentPage->next;
            history.addTail(currentPage->data);
        }
    }

    void previousPage(DoublyLinkedList& history) {
        if (currentPage && currentPage->prev) {
            currentPage = currentPage->prev;
            history.addTail(currentPage->data);
        }
    }

    void addCurrentPageToBookmarks(DoublyLinkedList& bookmarks) {
        if (currentPage) {
            bookmarks.addTail(currentPage->data);
        }
    }
};

struct Window {
    DoublyLinkedList tabs;
    DoublyLinkedList history;
    DoublyLinkedList bookmarks;
    Tab* currentTab;

    Window() : tabs(), history(), bookmarks(), currentTab(NULL) {}

    Tab* addTab(const std::string& tabName) {
        Tab* newTab = new Tab();
        tabs.addTail(tabName);
        currentTab = newTab; 
        return newTab;
    }


    void displayHistory() {
        std::cout << "Window History:\n" << history.display();
    }

    void displayBookmarks() {
        std::cout << "Window Bookmarks:\n" << bookmarks.display();
    }

    void displayListOfTabs() {
        std::cout << "Window Tabs:\n" << tabs.display();
    }

    void clearHistory() {
        std::cout << "Windows are deleted...\n";
        history.clear();
    }

    void clearBookmarks() {
        std::cout << "Bookmarks are deleted...\n";
        bookmarks.clear();
    }
};

struct Browser {
    DoublyLinkedList windows;
    Window* currentWindow;

    Browser() : windows(), currentWindow(NULL) {}

    Window* addWindow(const std::string& windowName) {
        Window* newWindow = new Window();
        windows.addTail(windowName);
        currentWindow = newWindow; 
        return newWindow;
    }

    std::string getCurrentWindowName() {
        if (currentWindow) {
            return windows.display();
        }
        return "No current window.";
    }

    void displayAllWindows() {
        std::cout << "All Windows:\n" << windows.display();
    }

    void deleteClearWindows() {
        std::cout << "Windows are deleted...\n";
        windows.clear();
        currentWindow = NULL;
    }
};

void displayMenuBrowser() {
    std::cout << "===== Menu Browser =====" << std::endl;
    std::cout << "1. Add New Window" << std::endl;
    std::cout << "2. Add New Tab" << std::endl;
    std::cout << "3. Add New Page" << std::endl;
    std::cout << "4. Next Page" << std::endl;
    std::cout << "5. Previous Page" << std::endl;
    std::cout << "6. Add Current Page to Bookmarks" << std::endl;
    std::cout << "7. Display List of Windows" << std::endl;
    std::cout << "8. Display List of Tabs" << std::endl;
    std::cout << "9. Display History" << std::endl;
    std::cout << "10. Display Bookmarks" << std::endl;
    std::cout << "11. Delete Window" << std::endl;
    std::cout << "12. Delete History" << std::endl;
    std::cout << "13. Delete Bookmarks" << std::endl;
    std::cout << "14. Exit" << std::endl;
    std::cout << "===== Menu Browser =====" << std::endl;
}

int main() {
    Browser browser;
    std::string windowName;
    std::string tabName;
    std::string page;

    bool quit = false;

    while (!quit) {
        int choice;
        displayMenuBrowser();

        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter window name: ";
            std::cin >> windowName;
            browser.addWindow(windowName);
            std::cout << windowName + " has been created!\n";
            std::cout << "You are on " + windowName + "\n";
            break;

        case 2:
            if (browser.currentWindow) {
                std::cout << "Enter tab name: ";
                std::cin >> tabName;
                browser.currentWindow->addTab(tabName);
                std::cout << "You are on " + windowName + ", tab: " + tabName + "\n";
            }
            else std::cout << "Please Add New Window !!!\n";
            break;
        case 3:

            if (browser.currentWindow && browser.currentWindow->currentTab) {
                std::cout << "Enter page URL: ";
                std::cin >> page;
                browser.currentWindow->currentTab->addWebPage(page, browser.currentWindow->history);
                std::cout << "You are on " + windowName + ", tab: " + tabName + " " + page + "\n";
            }
            else std::cout << "Please Add New Tab !!!\n";
            break;

        case 4:
            if (browser.currentWindow && browser.currentWindow->currentTab) {
                browser.currentWindow->currentTab->nextPage(browser.currentWindow->history);
                std::cout << "You are on " + windowName + ", tab: " + tabName + " " + page + "\n";

            }
            else std::cout << "Please Add New Tab !!!\n";
            break;

        case 5:
            if (browser.currentWindow && browser.currentWindow->currentTab) {
                browser.currentWindow->currentTab->previousPage(browser.currentWindow->history);
            }
            else std::cout << "Please Add New Tab !!!\n";
            break;

        case 6:
            if (browser.currentWindow && browser.currentWindow->currentTab) {
                browser.currentWindow->currentTab->addCurrentPageToBookmarks(browser.currentWindow->bookmarks);
            }
            else std::cout << "Please Add New Tab !!!\n";
            break;

        case 7:
            if (browser.currentWindow) {
                browser.displayAllWindows();
            }
            else std::cout << "Empty \n";
            break;

        case 8:
            if (browser.currentWindow && browser.currentWindow->currentTab) {
                browser.currentWindow->displayListOfTabs();
            }
            else std::cout << "Please Add New Tab !!!\n";
            break;

        case 9:
            if (browser.currentWindow) {
                browser.currentWindow->displayHistory();
            }
            else std::cout << "Please Add New Window !!!\n";
            break;

        case 10:
            if (browser.currentWindow) {
                browser.currentWindow->displayBookmarks();
            }
            else std::cout << "Please Add New Window !!!\n";
            break;
        case 11:
            browser.deleteClearWindows();
            std::cout << "All windows have been deleted!\n";
            break;

        case 12:
            if (browser.currentWindow) {
                browser.currentWindow->clearHistory();
            }
            break;

        case 13:
            if (browser.currentWindow) {
                browser.currentWindow->clearBookmarks();
            }
            break;        

        case 14:
            quit = true;
            break;
        }
    }
    return 0;
}
