#include "Window.h"

Window::Window() {
    this->activeTab = 0;
    tabs.append(Tab());
}

Tab Window::getActiveTab() {
  if (isEmpty()){
       Tab a;
       return a;
   }

   return (tabs.getNodeAtIndex(activeTab)->data);
}

bool Window::isEmpty() const {
    return tabs.isEmpty();
}

void Window::newTab(const Tab &tab) {

    if(isEmpty()){
        tabs.append(tab);
        activeTab++;
    }

    else {
        tabs.insertAfterNode(tab,tabs.getNodeAtIndex(activeTab));
        activeTab++;
    }

}

void Window::closeTab() {
    if (activeTab == -1) return;

    int tabcount = tabs.getSize();

    if (tabcount == 1){
        tabs.removeNodeAtIndex(0);
        activeTab = -1;
        return;
    }

    /* if last tab */
    if ((tabcount - 1) == activeTab){ 
        tabs.removeNodeAtIndex(activeTab);
        activeTab--;
        return;
    }

    /* else */
    tabs.removeNodeAtIndex(activeTab);

}

void Window::moveActiveTabTo(int index) {
    if(activeTab == -1) return;
    
    int size = tabs.getSize();
    tabs.moveToIndex(activeTab,index);
    if (index >= size) index = size-1;
    activeTab = index;

}

void Window::changeActiveTabTo(int index) {
    
    if ((index >= tabs.getSize()) || (index < 0)) return;

    activeTab = index;

}

void Window::addTab(Node<Tab> &tab) {
    if (activeTab == -1) activeTab = 0;

    tabs.append(tab.data);
    
}

void Window::print() {
    if(tabs.isEmpty()) std::cout << "Window is empty" << std::endl;
    else std::cout << "The active tab is tab " << activeTab << std::endl;
    tabs.print();
}
