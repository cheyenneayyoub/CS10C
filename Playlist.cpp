#include "Playlist.h"
#include <iostream>
#include <string>

PlaylistNode::PlaylistNode(){
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = 0;
}

PlaylistNode::PlaylistNode(string id, string song, string artist, int length){
    uniqueID = id;
    songName = song;
    artistName = artist;
    songLength = length;
    nextNodePtr = 0;
}

void PlaylistNode::InsertAfter(PlaylistNode* ptr){
    if (ptr == 0){
      return;
    }
    SetNext(ptr->GetNext()); //getting the pointer we want to set the song after
    ptr->SetNext(ptr); //setting the song

    
    return;
}

void PlaylistNode::SetNext(PlaylistNode* ptr){
    nextNodePtr = ptr;
    
    return;
}

string PlaylistNode::GetID() const{
    return uniqueID;
}

string PlaylistNode::GetSongName() const{
    return songName;
}

string PlaylistNode::GetArtistName() const{
    return artistName;
}

int PlaylistNode::GetSongLength() const{
    return songLength;
}

PlaylistNode* PlaylistNode::GetNext() const{
    return nextNodePtr;
}

void PlaylistNode::PrintPlaylistNode(PlaylistNode *data) const{
    cout << "Unique ID: " << data->GetID() << endl;
    cout << "Song Name: " << data->GetSongName() << endl;
    cout << "Artist Name: " << data->GetArtistName() << endl;
    cout << "Song Length (in seconds): " << data->GetSongLength() << endl;
    
    return;
}