
// Some information received from steventfan via github

//Cheyenne Ayyoub ID: 862090280


#include "Playlist.h"
#include <iostream>
#include <string>

using namespace std;

void PrintMenu(string);

int main()
{
    string playlistTitle = " ";
    
    cout << "Enter playlist's title:" << endl;
    getline(cin, playlistTitle);
    //cout << endl;
    
    PrintMenu(playlistTitle);
    
    return 0;
}

void PrintMenu(string title)
{
    char input = ' ';
    string newID = " ";
    string newSong = " ";
    string newArtist = " ";
    int duration = 0;
    int songPosition = 0;
    int i = 0;
    PlaylistNode playlist;
    PlaylistNode* head = 0;
    PlaylistNode* tail = 0;
    PlaylistNode* newNode = 0;
    PlaylistNode* temp = 0;
    
    while (input != 'q'){
            cout << title << " PLAYLIST MENU" << endl;
            cout << "a - Add song" << endl;
            cout << "d - Remove song" << endl;
            cout << "c - Change position of song" << endl;
            cout << "s - Output songs by specific artist" << endl;
            cout << "t - Output total time of playlist (in seconds)" << endl;
            cout << "o - Output full playlist" << endl;
            cout << "q - Quit" << endl << endl;
            cout << "Choose an option:";
            cin >> input;
            cout << endl;
            cin.ignore();
        
        if (input == 'a'){
            cout << "ADD SONG" << endl;
            cout << "Enter song's unique ID:";
            getline(cin, newID);
            cout << endl;
            cout << "Enter song's name:";
            getline(cin, newSong);
            cout << endl;
            cout << "Enter artist's name:";
            getline(cin, newArtist);
            cout << endl;
            cout << "Enter song's length (in seconds):";
            cin >> duration;
            cout << endl << endl;
            
            newNode = new PlaylistNode(newID, newSong, newArtist, duration);
            
            if (head == 0){
                head = newNode;
                tail = newNode;
            }
            else{
                tail->SetNext(newNode);
                tail = newNode;
            }
        }
        else if (input == 'd'){
            cout << "REMOVE SONG" << endl;
            cout << "Enter song's unique ID: ";
            getline(cin, newID);
            cout << endl;
          
            if (head == 0){
              return;
            }
            PlaylistNode* curr = head;
            PlaylistNode* prev = 0;
          
            while (curr != NULL){ //looping thru playlist from the beginning
                if (curr->GetID() == newID){ //when it finds the correct id, it will break from the loop
                    break;
                }
                prev = curr;
                curr = curr->GetNext();
            }
          
            if (head == curr){ //if the id is the first song
              head = 0;
            }
            if (tail == curr){ //if the id is the last song
              tail = 0;
            }
          
            if (prev != NULL){ //linking the song before the removed one to the song after the removed one
              prev->SetNext(curr->GetNext());
            }
            else{
              head = curr->GetNext();
            }
            
            delete curr;
        }
        else if (input == 'c'){
            cout << "CHANGE POSITION OF SONG" << endl;
            cout << "Enter song's current position: ";
            cin >> songPosition;
            newNode = head;
            temp = head;
            i = 1;
            while (i < songPosition){ //going thru the songs in the list from the beginning
                temp = newNode;
                newNode = newNode->GetNext();
                i++;
            }
            newSong = newNode->GetSongName();
            if (head == newNode){ //if it's the first song
                head = newNode->GetNext();
            }
            else if (tail == newNode){ //if it's the last song
                temp->SetNext(tail->GetNext());
                tail = temp;
            }
            else{
                temp->SetNext(newNode->GetNext());
            }
            cout << "Enter new position for song: ";
            cin >> songPosition;
            cout << endl;
            temp = head;
            i = 2;
            while (i < songPosition){ //going thru the songs in the list
                temp = temp->GetNext();
                ++i;
            }
            if (songPosition <= 1){ //setting the song to the first song in the list
                newNode->SetNext(head);
                head = newNode;
            }
            else if (songPosition > (songPosition - 1) ){ //setting the song as the last song if the position is too big
                tail = newNode;
                temp->InsertAfter(newNode);
            }
            else{
                temp->InsertAfter(newNode);
            }
            cout << "\"" << newSong << "\" moved to position " << songPosition << endl << endl;
        }
        else if (input == 's'){
            cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
            cout << "Enter artist's name: ";
            getline(cin, newArtist);
            cout << endl << endl;
            newNode = head;
            i = 1;
            for (newNode = head; newNode != 0; newNode = newNode->GetNext()){ //looping thru the list
              if (newNode->GetArtistName() == newArtist){ //if it matches the artist then it will output it
                    cout << i << '.' << endl;
                    playlist.PrintPlaylistNode(newNode);
                }
                i++;
            }
        }
        else if (input == 't'){
            newNode = head;
            duration = 0;
            while (newNode != 0){ //adding the durations
                duration = duration + newNode->GetSongLength();
                
                newNode = newNode->GetNext();
            }
            cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
            cout << "Total time: " << duration << " seconds" << endl << endl;
        }
        else if (input == 'o'){
            cout << title << " - OUTPUT FULL PLAYLIST" << endl;

            if (head == NULL){
              cout << "Playlist is empty" << endl << endl;
             }
            else{
              PlaylistNode* ptr = NULL;
              int i = 1;
              for (ptr = head; ptr != 0; ptr=ptr->GetNext()){ //looping thru the playlist and outputting everything using PrintPlaylistNode()
                cout <<  i << "." << endl;
                ptr->PrintPlaylistNode(ptr);
                cout << endl;
                i++;
              }
            }
        }
    }
    
    return;
}

