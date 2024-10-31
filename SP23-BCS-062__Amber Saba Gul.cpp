#include <iostream>
#include <string>

using namespace std;

// Node structure for linked list implementation of a stack
struct Node {
    string page;
    Node* next;  // Pointer to the next node
};

// Stack structure
struct Stack {
    Node* top; // Pointer to the top node of the stack
};

// Function to push a page onto the stack
void push(Stack stack, string page) {
    Node* newNode = new Node; // Create a new node
    newNode->page = page;     // Set the page for the new node
    newNode->next = stack.top; 
    stack.top = newNode;      
}

// Function to pop a page from the stack
string pop(Stack stack) {
    if (stack.top == NULL) { 
        cout << "Stack is empty." << endl;
        return ""; 
    }
    Node* temp = stack.top;       
    string poppedPage = temp->page; // Get the page from the top node
    stack.top = stack.top->next;  // Move the top pointer to the next node
    delete temp;                  // Free the memory of the popped node
    return poppedPage;            // Return the popped page
}

// Function to check if the stack is empty
bool isEmpty(Stack stack) {
    return stack.top == NULL; // Returns true if the stack is empty
}

Stack backStack;    // Stack for back history
Stack forwardStack; // Stack for forward history
string currentPage = "Home"; // Start with a home page

// Function to visit a new page
void visitPage(string page) {
    if (currentPage != "") {
        push(backStack, currentPage); // Push the current page to the back stack
    }
    currentPage = page;

    // Clear the forward stack when visiting a new page
    while (!isEmpty(forwardStack)) {
        pop(forwardStack);
    }

    cout << "Visited: " << currentPage << endl;
}

// Function to go back to the previous page
void goBack() {
    if (isEmpty(backStack)) {
        cout << "No pages in the back history." << endl;
    } else {
        push(forwardStack, currentPage); 
        currentPage = pop(backStack);     
        cout << "Back to: " << currentPage << endl;
    }
}

// Function to go forward to the next page
void goForward() {
    if (isEmpty(forwardStack)) {
        cout << "No pages in the forward history." << endl;
    } else {
        push(backStack, currentPage);      // Move current page to back stack
        currentPage = pop(forwardStack);    // Get the next page from the forward stack
        cout << "Forward to: " << currentPage << endl;
    }
}

// Function to show the current page
void showCurrentPage() {
    cout << "Current page: " << currentPage << endl;
}

int main() {
    int choice;
    string page;

    backStack.top = NULL;
    forwardStack.top = NULL;

    do {
        cout << "\n1. Visit Page\n2. Go Back\n3. Go Forward\n4. Show Current Page\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter page name: ";
                cin >> page;
                visitPage(page);
                break;
            case 2:
                goBack();
                break;
            case 3:
                goForward();
                break;
            case 4:
                showCurrentPage();
                break;
            case 5:
                cout << "Exiting browser history..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 5);

    return 0;
}

