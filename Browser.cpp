#include "Browser.h"

Browser::Browser() {
    windows.append(Window());
}

void Browser::newWindow() {
    windows.prepend(Window());
}

void Browser::closeWindow() {

    if (windows.isEmpty()) return;
    
    while (!windows.getFirstNode()->data.isEmpty()) windows.getFirstNode()->data.closeTab(); 

    windows.removeNodeAtIndex(0);
}

void Browser::switchToWindow(int index) {

    if ((index >= windows.getSize()) || (index < 0)) return;

    /* may be different */
    windows.moveToIndex(index,0);
}

Window &Browser::getWindow(int index) {
    return windows.getNodeAtIndex(index) -> data;
}

void Browser::moveTab(Window &from, Window &to) {
    
    Node<Tab> thetab(from.getActiveTab());

    if (from.isEmpty()) return;

    from.closeTab();
    to.newTab(thetab.data);

}

void Browser::mergeWindows(Window &window1, Window &window2) {
    
    window2.changeActiveTabTo(0);
    while (!window2.isEmpty()){
        moveTab(window2,window1);
    }
    
}

void Browser::mergeAllWindows() {
    
    int size = windows.getSize();
    
    if (size == 0) return;
    if (size == 1) return;


    Node<Window> *Window1 = windows.getFirstNode();
    Node<Window> *windowfrom = Window1->next;

    for(int i = 0; i < size-1; i++){
        mergeWindows(Window1->data,windowfrom->data);
        windowfrom = windowfrom->next;
    }


}

void Browser::closeAllWindows() {
    
    windows.removeAllNodes();

}

void Browser::closeEmptyWindows() {
    
    bool allclosed = false;
    Node<Window> *curr;
    int i;
    while(!allclosed){
        allclosed = true;
        int size = windows.getSize();
        curr = windows.getFirstNode();
        
        for (i = 0; i<size; i++){
            if (curr->data.isEmpty()){
                windows.removeNodeAtIndex(i);
                allclosed = false;
                break;
            }
            curr = curr->next;
        }
        
    }
    
}

void Browser::print() {
    Node<Window> *head = windows.getFirstNode();
    if(head == NULL) {
        std::cout << "The browser is empty" << std::endl;
    } else {
        (head -> data).print();
        head = head -> next;
        while(head != windows.getFirstNode()) {
            (head -> data).print();
            head = head -> next;
        }
    }
}
