//Selim Gul
//29200
//31.07.2021

#include <iostream>
#include <string>
#include <algorithm> // to make strings uppercase
#include <sstream>

using namespace std;


void welcomeMessage() { //displays the welcome message
    cout << "This program helps to create a music list and suggest you songs that you might like!" << endl;
    cout << "---" << endl;
}

void showMenu() { //shows the menu
    cout << "MENU" << endl;
    cout << "1. Add a song to the list" << endl;
    cout << "2. Delete a song from the list" << endl;
    cout << "3. Print the song list" << endl;
    cout << "4. Print the song list in reverse order" << endl;
    cout << "5. Show total duration of the list" << endl;
    cout << "6. Print songs from the same genre" << endl;
    cout << "7. Print songs from the same singer" << endl;
    cout << "8. Exit" << endl;
}

struct node { //created a node that includes required information about the songs and pointers to prev and next nodes
    string songName;
    string genre;
    string singer;
    int listenerCount;
    int duration;
    node* next;
    node* prev;
    node() {}
    node(string& sN, string& g, string& s, int& l, int& d, node* link, node* link2Prev) { //constructor
        songName = sN;
        genre = g;
        singer = s;
        listenerCount = l;
        duration = d;
        next = link;
        prev = link2Prev;
    }
}*start, *last;

int songCount = 0;

class LinkedList { //linkedlist class, which includes the functions
    public:
        node* create_node(string, string, string, int, int);
        void addSong(string, string, string, int, int);
        void deleteSong();
        void displayList();
        void deleteSong(node* toBeDeleted);
        void deleteSong(node);
        int showDuration();
        void displayGenre(string reqGenre);
        void displaySinger(string reqSinger);
        bool checkEmpty();
        void deleteList();
        void getInput(string&, string&, string&, int&, int&);
        //void addReverse(string, string, string, int, int);
        node getDeletion(node*& toBeDeleted, string& reqDelete);
        LinkedList()
        {
            start = NULL;
            last = NULL;
        }
};


node* LinkedList::create_node(string songName, string singer, string genre, int listenerCount, int duration) { //the function here creates a node with the entries of user input
    songCount++; //increase counter
    node* temp = new node; //create new node
    temp->songName = songName; 
    temp->singer = singer;
    temp->genre = genre;
    temp->listenerCount = listenerCount;
    temp->duration = duration; //until this line add the required information to the node
    temp->next = NULL;
    temp->prev = NULL;
    return temp; //return the newly created node
}

void LinkedList::addSong(string songName, string singer, string genre, int listenerCount, int duration) { //this function inserts the created node to the beginning of the list
    node* temp;
    temp = create_node(songName, singer, genre, listenerCount, duration); //the newly created node is inserted to the list
    if (start == last && start == NULL) { //if the list is empty insert it as both head and tail
        start = last = temp; //make the new node equal to both head and tail
        start->next = last->next = NULL; //node's next and prevs points to null
        start->prev = last->prev = NULL;
    }
    else { //if the list is not empty insert it as head
        temp->next = start; 
        start->prev = temp; 
        start = temp;
        start->prev = last;
        last->next = start;
    }
}


bool LinkedList::checkEmpty() { //check if the list is empty
    if (start == last && start == NULL) {
        return true; // return true if the list is empty
    }
    else {
        return false; // return false if the list is not empty
    }
}


void LinkedList::displayList() { //this function displays the list starting from beginning to the end
    int i;
    node* s;
    if (start == last && start == NULL) { //same as the checkEmpty function, checks if the list is empty and returns if it is empty
        cout << "---" << endl;
        cout << "The song list is empty." << endl;
        return;
    }
    s = start;
    for (i = 0; i < songCount-1; i++){ //go over nodes until we reach the songcount - 1, because we start i from 0
        cout << "---" << endl;
        cout << "Song Name: " << s->songName << endl;
        cout << "Singer Name: " << s->singer << endl;
        cout << "Genre: " << s->genre << endl;
        cout << "Duration: " << s->duration << endl;
        cout << "Listener Count: " << s->listenerCount << endl;

        s = s->next;
    }
    cout << "---" << endl;
    cout << "Song Name: " << s->songName << endl;
    cout << "Singer Name: " << s->singer << endl;
    cout << "Genre: " << s->genre << endl;
    cout << "Duration: " << s->duration << endl;
    cout << "Listener Count: " << s->listenerCount << endl;

}
/*
void LinkedList::addReverse(string songName, string singer, string genre, int listenerCount, int duration) { //I wasn't able to succesfully implement this function
    node* temp;
    temp = create_node(songName, singer, genre, listenerCount, duration); //the newly created node is inserted to the list
    if (start == last && start == NULL)
    {
        start = last = temp;
        start->next = last->next = NULL;
        start->prev = last->prev = NULL;
    }
    else
    {
        last->next = temp;
        temp->prev = last;
        last = temp;
        start->prev = last;
        last->next = start;
    }
}
*/
void LinkedList::deleteSong(node *toBeDeleted) { //deletes the node that is returned from getDelete function
    node* ptr;
    if (start->next == NULL) { //if the list contains only one element
        delete toBeDeleted;
        songCount--;
    }
    else { //if there are more than one elements
        if (toBeDeleted == start) {
            start = start->next;
            delete toBeDeleted;
            songCount--;
        }
        else {
            ptr = start;
            while (ptr->next != toBeDeleted) {
                ptr = ptr->next;
            }
            ptr->next = toBeDeleted->next;
            delete toBeDeleted;
            songCount--;
        }
    }
}


void LinkedList::deleteList() { // dealloactes all the memory location before exiting the program
    node* ptr, *tmp;
    ptr = start; //sets pointer to start
    if (start == NULL) { //if the list is empty, return
        return;
    }
    else { // if the list is not empty
        for (int i = 0; i < songCount; i++) {  //do this statement until the the next points to NULL
            tmp = ptr; //set temp equal to ptr
            ptr = ptr->next; //set ptr equal to next node
            delete tmp; //delete tmp (previous node)
        }
    }
}

int LinkedList::showDuration() { //this fucntions sums up the values of durations and return the total duration
    node* ptr;
    int totalDuration = 0; //initialize counter as 0
    if (start->next == NULL) { //if there is only one song return it's duration as total duration.
        ptr = start;
        totalDuration += ptr->duration;
        return totalDuration;
    }
    else { //if there are more than one songs
        ptr = start; 
        totalDuration += ptr->duration; //add first nodes duration to total time
        ptr = ptr->next;
        while (ptr != start) { //until we reach the beginning of the list do this satement
            totalDuration += ptr->duration; //add nodes duration to total time
            ptr = ptr->next; //go to next node
        }
        return totalDuration;
    }

}

void makeUpper(string& input) { //this function makes the strings all uppercase
    for (int i = 0; i < input.size(); i++) {
        input[i] = (toupper(input[i])); //toupper is a built-in function
    }
}

void LinkedList::displayGenre(string reqGenre) { //function that displays all songs from the same genre
    node* ptr;
    cout << "---" << endl;
    cout << "List of All the Songs from Genre " << reqGenre << endl;
    cout << "---" << endl;
    if (start->next == NULL) { //if there is only one element in the list
        ptr = start;
        if (ptr->genre == reqGenre) { //if the genre matches with the requested genre
            cout << "- " << ptr->songName << " from " << ptr->singer << endl; //print the song info
        }
        else {
            return;
        }
    }
    else { //if there are more than one elements in the list
        ptr = start;
        if (ptr->genre == reqGenre) { //if the genre matches with the requested genre
            cout << "- " << ptr->songName << " from " << ptr->singer << endl; //print the song info
        }
        ptr = ptr->next; //go to next node
        while (ptr != start) { //until it comes to beginning
            if (ptr->genre == reqGenre) { //if the genre matches with the requested genre
                cout << "- " << ptr->songName << " from " << ptr->singer << endl; //print the song info
            }
            ptr = ptr->next; //go to next node
        }
    }
}

void LinkedList::displaySinger(string reqSinger) { //function that displays all songs from the same singer
    node* ptr;
    cout << "---" << endl;
    cout << "List of All the Songs from Singer " << reqSinger << endl;
    cout << "---" << endl;
    if (start->next == NULL) { //if there is only one element in the list
        ptr = start;
        if (ptr->singer == reqSinger) {
            cout << "- " << ptr->songName << endl;
        }
    }
    else {
        ptr = start;
        if (ptr->singer == reqSinger) { //if the singer matches with the requested singer
            cout << "- " << ptr->songName << endl; 
        }
        ptr = ptr->next; // go to next node
        while (ptr != start) {
            if (ptr->singer == reqSinger) { //if the singer matches with the requested singer
                cout << "- " << ptr->songName << endl;
            }
            ptr = ptr->next; // go to next node
        }
    }
}


void takeOption(string& input) { //function gets the users choice as string
    cout << "---" << endl;
    cout << "Enter your choice: ";
    cin >> input;
}

void LinkedList::getInput(string& songName, string& singer, string& genre, int& listenerCount, int& duration) { 
    node* ptr;
    ptr = start;
    cout << "Enter the name of the song: ";
    cin.ignore();
    getline(cin, songName);
    makeUpper(songName); //function to conver uppercase
    if (ptr != NULL) { //if this is not the first node that will be created
        if (songName == ptr->songName) { //if the song
            cout << "---" << endl;
            cout << "The song " << songName << " is already in the song list." << endl;
            return;
        }
        ptr = ptr->next;
    }
    cout << "Enter singer name of the song: "; getline(cin, singer);
    cout << "Enter genre of the song: "; getline(cin, genre);
    cout << "Enter the listener count of the song: "; cin >> listenerCount;
    cout << "Enter the duration of the song: "; cin >> duration;
}

node LinkedList::getDeletion(node*& toBeDeleted, string& reqDelete) { //gets the input of deletion
    cout << "---" << endl;
    cout << "Enter the song name that you want to delete: ";
    cin.ignore();
    getline(cin, reqDelete);
    makeUpper(reqDelete);
    node* temp;
    toBeDeleted = start;
    if (start->next == NULL) { //if the list includes one node
        if (reqDelete == start->songName) {
            return *toBeDeleted; //returns the node if the songnames match
        }
        else {
            toBeDeleted = NULL; //return node as NULL if the songname doesn't match
            return *toBeDeleted;
        }
    }
    else { //if the list has more than one node
        if (reqDelete == start->songName) {
            return *toBeDeleted;
        }
        else {
            temp = start->next;
            while (temp != start) { //until it comes to beginning
                if (reqDelete == temp->songName) {
                    toBeDeleted = temp;
                    return *toBeDeleted; //returns the node if the songnames match
                }
                temp = temp->next; //search for next node
            }
            toBeDeleted = NULL;
            return *toBeDeleted; //return node as NULL if the songname doesn't match
        }
    }

}


bool checkInput(string input) { //checking if the input is valid
    if (input == "1" || input == "2" || input == "3" || input == "4" || input == "5" || input == "6" || input == "7" || input == "8") {
        return true; // return true if input is correct
    }
    else
        return false; //return false if the input is incorrect
}

int main() {
    LinkedList MyList, reverseList;
    string songName, genre, singer, reqGenre, reqSinger, input, reqDelete;
    int listenerCount, duration;
    node* tail, * head = NULL;
    node* temp = NULL;
    node* toBeDeleted = NULL;
    welcomeMessage(); //display the welcome message
    showMenu(); //show the menu
    takeOption(input); //get the user choice
    while (checkInput(input) == false) { //if the input is incorrect get input until corrected
        cout << "---" << endl;
        cout << "Not a valid option." << endl;
        takeOption(input);
    }
    while (input != "8") {
        if (input == "1") { 
            cout << "---" << endl;
            singer = ""; //initialize singer to empty string
            MyList.getInput(songName, singer, genre, listenerCount, duration); //get input for song information
            if (singer != "") { //this will remain empty string if the names match therefore adding will not be executed
                makeUpper(singer);
                makeUpper(genre);
                MyList.addSong(songName, singer, genre, listenerCount, duration);
                //reverseList.addReverse(songName, singer, genre, listenerCount, duration); //I wasn't able to succesfully implement this function
                cout << "---" << endl;
                cout << "The song " << songName << " from " << singer << " is added to the song list." << endl;
            }
        }
        if (input == "2") {
            if (MyList.checkEmpty()) {
                cout << "---" << endl;
                cout << "The song list is empty." << endl;
            }
            else {
                MyList.getDeletion(toBeDeleted, reqDelete);
                if (toBeDeleted == NULL) {
                    cout << "---" << endl;
                    cout << "The song " << reqDelete << " could not be found in the list." << endl;
                }
                else {
                    cout << "---" << endl;
                    cout << "The song " << reqDelete << " is deleted from the list." << endl;
                    MyList.deleteSong(toBeDeleted);
                }
            }
        }
        if (input == "3") { //print the list
            MyList.displayList();
        }
        if (input == "4") { //print as reversed
            if (MyList.checkEmpty()) {
                cout << "---" << endl;
                cout << "The song list is empty." << endl;
            }
            /*else {
                reverseList.displayList();
            }
            */

        }
        if (input == "5") { //count total duration
            if (MyList.checkEmpty()) {
                cout << "---" << endl;
                cout << "The song list is empty." << endl;
            }
            else {
                cout << "---" << endl;
                cout << "Enjoy your next " << MyList.showDuration() << " minutes with the songs in the list." << endl;
            }
           
        }
        if (input == "6") { //display songs from same genre
            if (MyList.checkEmpty()) {
                cout << "---" << endl;
                cout << "The song list is empty." << endl;
            }
            else {
                cout << "---" << endl;
                cout << "Please enter the genre of the songs you want to list: ";
                cin >> reqGenre;
                makeUpper(reqGenre);
                MyList.displayGenre(reqGenre);
            }
        }
        if (input == "7") { //display songs from same singer
            if (MyList.checkEmpty()) {
                cout << "---" << endl;
                cout << "The song list is empty." << endl;
            }
            else {
                cout << "---" << endl;
                cout << "Please enter the singer name of the songs you want to list: ";
                cin.ignore();
                getline(cin, reqSinger);
                makeUpper(reqSinger);
                MyList.displaySinger(reqSinger);
            }

        }
        takeOption(input); //get input again
        checkInput(input);
        while (checkInput(input) == false) { //get input until it is corrected
            cout << "Not a valid option." << endl;
            takeOption(input);
        }
    } //if input is selected as 8 exit the loop
    cout << "---" << endl;
    cout << "Deleting song list..." << endl;
    cout << "Exiting the program..." << endl;
    MyList.deleteList(); //deallocate memory and terminate the program

    return 0;
}
