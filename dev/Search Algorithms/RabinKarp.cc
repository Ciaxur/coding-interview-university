#include <bits/stdc++.h>
using namespace std;


int main(int argc, char *argv[]) {
  if (argc < 3) {
    cout << "Provide a file path to read from and string to look for\n";
    cout << "app {string to search} {file path}\n";
    return 1;
  }

  // Open file
  ifstream inFile(argv[2], ios::in);
  if (!inFile.is_open()) {
    cout << "File doesn't exist!\n";
    return 1;
  }

  // Construct word and Hashes
  string word = argv[1];        // Word to Search for
  hash<string> stringHash;      // String Hash Object

  // Store Word searching for's Hash
  char buffer[word.length()];   // File Read Buffer
  char nextChar[1];
  size_t hashedWord = stringHash(word);
  inFile.read(buffer, word.length());

  string strWindow(buffer);
  for(size_t i=0; ;i++) {
    // Get next Window
    if(i != 0) {
      if (!inFile.read(nextChar, 1)) break;
      strWindow = strWindow.substr(1, strWindow.length()) + nextChar;
    }

    // Check window
    if ( stringHash(strWindow) == hashedWord ) {  // Found
      cout << "String '" << word << "' Found at character " << ((int)inFile.tellg() - word.length()) << " in file.\n";
      inFile.close();
      return 0;
    }
  }

  // Clean up
  inFile.close();
  cout << "Word not found\n";
  return 1;
}