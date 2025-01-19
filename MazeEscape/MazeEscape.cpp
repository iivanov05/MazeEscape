#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
#include <vector>
#include <string>
using namespace std;


enum Ranks { 
    E,//E-rank = 0 maze levels complete
    D,//D-rank = 1 maze levels complete
    C,//C-rank = 2 maze levels complete
    B,//B-rank = 3 maze levels complete
    A,//A-rank = 4 maze levels complete
    S//S-rank = 5 maze levels complete
    };

void delay(unsigned int sec) {

    clock_t ticks1 = clock();

    clock_t ticks2 = ticks1;

    while ((ticks2 / CLOCKS_PER_SEC - ticks1 / CLOCKS_PER_SEC) < sec) {
    
        ticks2 = clock();
    
    }
}


void clearConsole() {

    system("cls");

}


int randMazeNumber() {

    srand(time(NULL));

    size_t randomMaze = (rand() % 3) + 1;
    
    return randomMaze;

}


bool playerExist(string username){

    string userFileLocation = "UsersNames/" + username;
    
    ifstream userFile(userFileLocation);
    
    if (userFile) {
    
        userFile.close();

        return true;
    
    }
    else {
    
        userFile.close();
        
        return false;
    
    }

}


void createPlayersAccount(string username) {

    string userFileLocation = "UsersNames/" + username;
    
    ofstream newFile(userFileLocation);
    
    if (newFile) {

        cout << "New user signed up! " << "\n";
    
        newFile << "Rank: E\nLevel: 1\nLives: 3\nCoins: 0\nKey: Not Found\nPositionInfo: ' '\nLevelStatus: Incompleted\n";
        
        newFile.close();
    
    }
    else {
    
        newFile.close();
        
        cout << "Error creating the file.\n";
    
    }

}


string getRank(string& filePath) {

    ifstream file(filePath);
    
    string line;
    
    if (file) {
    
        while (getline(file, line)) {
        
            if (line.find("Rank:") != string::npos) {
            
                return line.substr(6);
            
            }
        
        }
    
    }
    
    return "Unknown";

}


int getLevel(string& filePath) {
    
    ifstream file(filePath);
    
    string line;
    
    if (file) {
    
        while (getline(file, line)) {
        
            if (line.find("Level:") != string::npos) {
            
                return stoi(line.substr(7));
            
            }
        
        }
    
    }
    
    return 0;

}

int getLives(string& filePath) {
    
    ifstream file(filePath);
    
    string line;
    
    if (file) {
    
        while (getline(file, line)) {
        
            if (line.find("Lives:") != string::npos) {
            
                return stoi(line.substr(7)); 
            
            }
        
        }
    
    }
    
    return 0; 

}


int getCoins( string& filePath) {

    ifstream file(filePath);

    string line;

    if (file) {

        while (getline(file, line)) {

            if (line.find("Coins:") != string::npos) {

                return stoi(line.substr(7));

            }

        }

    }

    return 0; 

}


string getKey(string& filePath) {

    ifstream file(filePath);

    string line;

    if (file) {

        while (getline(file, line)) {

            if (line.find("Key:") != string::npos) {

                return line.substr(5); 

            }

        }

    }

    return "Not Found";

}


char getPlayerPositionInfo(string& filePath) {

    ifstream file(filePath);

    string line;

    string info = " ";

    if (file) {

        while (getline(file, line)) {

            if (line.find("PositionInfo:") != string::npos) {

                info = line.substr(14); 

            }

        }

    }

    if (info == "' '") {

        return ' ';

    }
    else if (info == "'%'") {

        return '%';

    }
    else if (info == "'C'") {

        return 'C';

    }
    else if (info == "'&'") {

        return '&';

    }

    return '0';

}


string getLevelStatus(string& filePath) {

    
    ifstream file(filePath);
    
    string line;
    
    if (file) {
    
        while (getline(file, line)) {
        
            if (line.find("LevelStatus:") != string::npos) {
            
                return line.substr(13);
            
            }
        
        }
    
    }
    
    return "Unknown";

}


string mazesFilePath(int level) {

    string mazeFilePathName;

    if (level == 1) {

        mazeFilePathName = "Mazes/easy_" + to_string(randMazeNumber()) + ".txt"; // Add file extension
    
    }
    else if (level == 2) {
    
        mazeFilePathName = "Mazes/mid_" + to_string(randMazeNumber()) + ".txt";

    }
    else if (level == 3) {

        mazeFilePathName = "Mazes/hard_" + to_string(randMazeNumber()) + ".txt";

    }
    else if (level == 4) {

        mazeFilePathName = "Mazes/very_hard_" + to_string(randMazeNumber()) + ".txt";

    }
    else if (level == 5) {

        mazeFilePathName = "Mazes/ultimate_" + to_string(randMazeNumber()) + ".txt";

    }
    else {

        cerr << "Error: Incorrect level number!" << endl;

        return "0";

    }

    return mazeFilePathName;

}


void rndMazeByLevel(string& username,int level) {
 
    string userFileLocation = "UsersNames/" + username;

    ifstream usersFile(userFileLocation);

    if (!usersFile) {

        cerr << "Error: Could not open file for reading." << endl;

        return;

    }

    string firstLine;

    getline(usersFile, firstLine);

    usersFile.close();

    string mazeFilePathName;

    mazeFilePathName = mazesFilePath(level);

    ifstream mazeFile(mazeFilePathName);

    if (!mazeFile) {

        cerr << "Error: Could not open maze file " << mazeFilePathName << endl;

        return;

    }

    ofstream updatedUsersFile(userFileLocation, ios::app);

    if (!updatedUsersFile) {
    
        cerr << "Error: Could not open file for writing." << endl;
        
        return;
    
    }

    string line;

    while (getline(mazeFile, line)) {

        updatedUsersFile << line << endl;

    }

    mazeFile.close();

    updatedUsersFile.close();

}


void updateUserLevelAndMaze(string& username, int level) {

    clearConsole();

    rndMazeByLevel(username, level);


}


void toLowerCase(string &word) {

    for (char& c : word) {
    
        if (c >= 'A' && c <= 'Z') {
        
            c = c + 32;
        
        }
    
    }

}


bool yes_or_no(string command) {

WRONG_INPUT_YES_OR_NO:

    toLowerCase(command);
    
    if (command == "yes") {
    
        return true;
    
    }
    else if (command == "no") {
    
        return false;
    
    }
    else {
    
        cerr << "Incorect input! Enter \"yes\" to start \"no\" to go back:" << endl;
        
        cin >> command;
        
        goto WRONG_INPUT_YES_OR_NO;
    
    }

}

void loadMazeFromFile(string& username, char maze[15][25]) {
    string userFileLocation = "UsersNames/" + username;

    // Open the file for reading
    ifstream inputFile(userFileLocation);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file!" << endl;
        return;
    }

    // Skip the first 7 lines
    string skipLine;
    for (int i = 0; i < 7; ++i) {
        if (!getline(inputFile, skipLine)) {
            cerr << "Error: File does not have enough lines!" << endl;
            inputFile.close();
            return;
        }
    }

    // Read the maze into the 2D array
    for (int i = 0; i < 15; ++i) {
        string line;
        if (getline(inputFile, line)) {
            for (int j = 0; j < 25; ++j) {
                if (j < line.size()) {
                    maze[i][j] = line[j];
                }
                else {
                    maze[i][j] = ' '; // Fill remaining spaces with blanks
                }
            }
        }
        else {
            // Fill remaining rows with blanks if file has fewer lines
            for (int j = 0; j < 25; ++j) {
                maze[i][j] = ' ';
            }
        }
    }

    // Close the file
    inputFile.close();

}


void saveMazeAndStast(string& username
    , char maze[15][25]
    , string& rank
    , int& currentLevel
    , int& livesLeft
    , int& coins
    , string& key
    , char& playerPositionInfo
    , string& levelStatus) {


    string userFileLocation = "UsersNames/" + username;

    ofstream outputFile(userFileLocation);
    
    if (!outputFile.is_open()) {
    
        cerr << "Error: Could not open the file for writing!" << endl;
        
        return;
    
    }
    
    outputFile << "Rank: " << rank << endl;
    outputFile << "Level: " << currentLevel << endl;
    outputFile << "Lives: " << livesLeft << endl;
    outputFile << "Coins: " << coins << endl;
    outputFile << "Key: " << key << endl;
    outputFile << "PositionInfo: '" << playerPositionInfo <<"'" << endl;
    outputFile << "LevelStatus: " << levelStatus << endl;

    for (int i = 0; i < 15; i++) {
   
        for (int j = 0; j < 25; j++) {
        
            outputFile << maze[i][j];
        
        }
        
        outputFile << endl;
    
    }

    outputFile.close();

}


void printMaze(char maze[15][25]) {

    for (int i = 0; i < 15; i++) {

        for (int j = 0; j < 25; j++) {
        
            cout << maze[i][j];
        
        }
        
        cout << endl;
    
    }

}



void getPlayerPosition(int& playerRowPosition,int& playerColPosition, char maze[15][25]) {


    for (int row = 0; row < 15; row++) {

        for (int col = 0; col < 25; col++) {

            if (maze[row][col] == '@') {

                playerRowPosition = row;
                playerColPosition = col;

            }
        }

    }
}


void movingCommandValidation(string& command) {
   
    
MOVE_COMMAND:

    if (command == "w" || command == "W") {

    }
    else if (command == "s" || command == "S") {

    }
    else if (command == "D" || command == "d") {

    }
    else if (command == "A" || command == "a") {

    }
    else
    {
        cerr << "Incorect input!\nType \"W/w\" for up , \"S/s\" for down, \"A/a\" for left ,\"D/d\" for right!" << endl;
        
        cin >> command;
        
        toLowerCase(command);
        
        if (command == "exit") {
        
            cout << "First move the character then exit!" << endl;
            
            cout << endl;
        
        }
       
        goto MOVE_COMMAND;
    
    }

}

void loseLive(int& livesLeft) {

    livesLeft--;

}

void playerNextMoveRowCol(int& playerNewRowPosition, int& playerNewColPosition, string& commandMove) {

    if (commandMove == "w" || commandMove == "W") {

        playerNewRowPosition--;

    }
    else if (commandMove == "s" || commandMove == "S") {

        playerNewRowPosition++;

    }
    else if (commandMove == "a" || commandMove == "A") {

        playerNewColPosition--;

    }
    else if (commandMove == "d" || commandMove == "D") {

        playerNewColPosition++;

    }

}

void validationOfArrStart(int& startRow, int& startCol) {

    if (startCol == 23 && startRow == 13) {
      
        startCol = 0;
        startRow = 0;

    }
    else if (startCol == 23) {

        startCol = 0;
        startRow++;

    }
    else {
        startCol++;
    }
}

void movePlayer(int& playerRowPosition
    , int& playerColPosition
    , char maze[15][25]
    , string& commandMove
    , string& rank
    , int& currentLevel
    , int& livesLeft
    , int& coins
    ,string& key
    ,char& playerPositionInfo
    ,string& levelStatus) {

    
    movingCommandValidation(commandMove);

    int playerNewRowPosition = playerRowPosition;
    int playerNewColPosition = playerColPosition;

    playerNextMoveRowCol(playerNewRowPosition, playerNewColPosition, commandMove);


        if (maze[playerNewRowPosition][playerNewColPosition] == '#') {

            livesLeft--;

        }
        else if (maze[playerNewRowPosition][playerNewColPosition] == ' ') {

            maze[playerNewRowPosition][playerNewColPosition] = '@';
            
            if (playerPositionInfo == '%') {

                maze[playerRowPosition][playerColPosition] = '%';

            }
            else
            {
                maze[playerRowPosition][playerColPosition] = ' ';
            }
            
            playerPositionInfo = ' ';
           
            playerRowPosition = playerNewRowPosition;
            playerColPosition = playerNewColPosition;

        }
        else if (maze[playerNewRowPosition][playerNewColPosition] == 'C') {

            maze[playerNewRowPosition][playerNewColPosition] = '@';
            
            coins++;
            
            if (playerPositionInfo == '%') {

                maze[playerRowPosition][playerColPosition] = '%';

            }
            else
            {
                maze[playerRowPosition][playerColPosition] = ' ';
            }

            playerPositionInfo = 'C';
           
            playerRowPosition = playerNewRowPosition;
            playerColPosition = playerNewColPosition;

        }
        else if (maze[playerNewRowPosition][playerNewColPosition] == '&') {

            key = "Found";
            
            maze[playerNewRowPosition][playerNewColPosition] = '@';

            if (playerPositionInfo == '%') {

                maze[playerRowPosition][playerColPosition] = '%';

            }
            else
            {
                maze[playerRowPosition][playerColPosition] = ' ';
            }
            
            playerPositionInfo = '&';
            
            playerRowPosition = playerNewRowPosition;
            playerColPosition = playerNewColPosition;

        }
        else if (maze[playerNewRowPosition][playerNewColPosition] == 'X') {
            
            playerPositionInfo = 'X';


            if (playerPositionInfo == '%') {

                maze[playerRowPosition][playerColPosition] = '%';

            }

            if (key == "Found") {
               
                levelStatus = "Complited";
                
                cout << "Level Complited!" << endl;
                
                delay(3);
                
                cout << "Next one!" << endl;
                
                delay(3);

            }
            else if (key == "Not Found") {
                
                cout << "Find Key!" << endl;
                
                delay(2);
            
            }

        }
        else if (maze[playerNewRowPosition][playerNewColPosition] == '%') {
            
            
            if (playerPositionInfo == '%') {

                maze[playerRowPosition][playerColPosition] = '%';

            }
            else
            {
                maze[playerRowPosition][playerColPosition] = ' ';
            }



            bool foundNextPortal = false;

            int startRow = playerNewRowPosition;
            int startCol = playerNewColPosition;

            int oldPortalRowPosititon = playerNewRowPosition;
            int oldPortalColPosititon = playerNewColPosition;

            validationOfArrStart(startRow, startCol);
            
            START_FROM_THE_BEGINNING:
            for (int row = startRow; row < 14; row++)
            {
            
                if (row == startRow + 1) {
                    
                    startCol = 1;
                
                }
                for (int col = startCol; col < 24; col++)
                {
                    

                    if (maze[row][col] == '%') {

                        //cout << row << " " << col << endl; //proverka

                        playerNewRowPosition = row;
                        playerNewColPosition = col;
                        
                        foundNextPortal = true;
                        
                        break;

                    }

                }

                if (foundNextPortal) {
                    
                    break;
                
                }

            }

            if (!foundNextPortal) {
               
                startRow = 1;
                startCol = 1;
                
                goto START_FROM_THE_BEGINNING;
            
            }

            playerRowPosition = playerNewRowPosition;
            playerColPosition = playerNewColPosition;
            
            maze[oldPortalRowPosititon][oldPortalColPosititon] = '%';
            maze[playerNewRowPosition][playerNewColPosition] = '@';
            
            playerPositionInfo = '%';

        }

}

void removeMazeFromFile(const string& username) {

    string userFileLocation = "UsersNames/" + username;

    ifstream inputFile(userFileLocation);
    
    if (!inputFile.is_open()) {
    
        cerr << "Error: Could not open the file for reading!" << endl;
        
        return;
    
    }

    string userInfo = "";

    string line;

    bool isMazeSection = false;

    while (getline(inputFile, line)) {

        if (!isMazeSection && line.find('#') == 0) {

            isMazeSection = true;
        
        }
        if (!isMazeSection) {
        
            userInfo += line + "\n";
        
        }
    }

    inputFile.close();

    ofstream outputFile(userFileLocation, ios::trunc);

    if (!outputFile.is_open()) {

        cerr << "Error: Could not open the file for writing!" << endl;
        return;

    }

    outputFile << userInfo;
    outputFile.close();

}


int levelChoosingByRank(string& rank) {
    
    int upToPlayableLevel;
    
    if (rank == "C") {
    
        upToPlayableLevel = C;
    
    }
    else if (rank == "B") {

        upToPlayableLevel = B;
    
    }
    else if (rank == "A") {

        upToPlayableLevel = A;
    
    }
    else if (rank == "S") {

        upToPlayableLevel = S;
    
    }

    cout << "Your rank is \"" + rank + "\"! You can аccess from level 1 to " + to_string(upToPlayableLevel) + "!" << endl;
    cout << "Which level would you like to choоse from?(number only)" << endl;

LEVEL_INPUT_C_RANK:

    int level;
    cin >> level;

    if (level < 1 || level > upToPlayableLevel) {

        cerr << "Incorect input!Try again." << endl;
    
        goto LEVEL_INPUT_C_RANK;

    }

    return level;

}

void logInSignUp(string& username,string& command) {

LOG_IN_SIGN_UP:

    cout << "Log in(1), Sign up(2) or Exit(3): " << endl;
    cin >> command;
    
    clearConsole();

    
    if (command == "1") {

        cout << "Enter your username: " << endl;
        cin >> username;
    
        clearConsole();

        if (playerExist(username)) {

            cout << "Wellcome " + username + "!" << endl;
        
        }
        else {
    
            cout << "User not found." << endl;
            
            goto LOG_IN_SIGN_UP;
        
        }

    }
    else if (command == "2") {

    ENTER_VALID_USERNAME_2:

        cout << "Enter a username: " << endl;
        cin >> username;

        if (playerExist(username)){

            cout << "Palyer " + username + " already exists!\nTry another one." << endl;
            
            goto ENTER_VALID_USERNAME_2;
        
        }

        clearConsole();
        
        createPlayersAccount(username);
        
        rndMazeByLevel(username, 1);

        cout << "Wellcome " + username + "!" << endl;
    }
    else if (command == "3") {
        
        command = "exit";
    
    }
    else {
       
        cout << "Incorrect input!\nWrite \"1\" to LOG IN, \"2\" to SIGN UP or \"3\" to EXIT!" << endl;
        
        goto LOG_IN_SIGN_UP;
    
    }

}

void playFromSaveOrNew(string& username, string& command,int& currentLevel) {

    string filePath = "UsersNames/" + username;
    
    ifstream usersFile(filePath);
    
    string firstLine;
    
    getline(usersFile, firstLine);
    
    usersFile.close();
    
    string rank = getRank(filePath);

    if (rank != "E") {

        cout << "Play from SAVE , start NEW game or EXIT profile: " << endl;
        cin >> command;
        
        toLowerCase(command);

        if (command == "save") {

        }
        else if (command == "new") {

            clearConsole();
            
            int level = 1;

            if (rank == "D") {
            
                cout << "Your rank is \"D\"! You can аccess level 1!" << endl;
                cout << "Would you like to start from level 1?" << endl;
                cin >> command;

                if (yes_or_no(command)) {

                    removeMazeFromFile(username);
                    updateUserLevelAndMaze(username, 1);

                }

            }
            else if (rank == "C") {

                level = levelChoosingByRank(rank);
                removeMazeFromFile(username);
                updateUserLevelAndMaze(username, level);

            }

            else if (rank == "B") {

                level = levelChoosingByRank(rank);
                removeMazeFromFile(username);
                updateUserLevelAndMaze(username, level);

            }
            else if (rank == "A") {

                level = levelChoosingByRank(rank);
                removeMazeFromFile(username);
                updateUserLevelAndMaze(username, level);

            }
            else if (rank == "S") {

                level = levelChoosingByRank(rank);
                removeMazeFromFile(username);
                updateUserLevelAndMaze(username, level);

            }

            currentLevel = level;

        }
        else if (command == "exit") {
            
        }
        else {

            cerr << "Incorect input! Enter \"save\" to start from save or \"new\" for new game" << endl;
       
        }
        
        


    }
}

void updateRank(string& rank) {
    if (rank == "E") {

        rank = "D";

    }
    else if (rank == "D") {

        rank = "C";

    }
    else if (rank == "C") {

        rank = "B";

    }
    else if (rank == "B") {

        rank = "A";

    }
    else if (rank == "A") {

        rank = "S";

    }
}

void updateLevel(int& level) {
    
    if (level != 5) {

        level++;
    
    }

}

void newLevelMaze(string& username
    , string& rank
    , int& currentLevel
    , int& livesLeft
    , int& coins
    , string& key
    , char& playerPositionInfo
    , string& levelStatus) {

    string userFileLocation = "UsersNames/" + username;


    ofstream updatedUsersFile(userFileLocation, ios::trunc); // `ios::trunc` clears the file first
    
    if (!updatedUsersFile.is_open()) {
    
        cerr << "Error: Could not open the file for writing!" << endl;
        return;
    
    }

    
    livesLeft = 3;
    key = "Not Found";
    playerPositionInfo = ' ';
    levelStatus = "Incompleted";

    updatedUsersFile << "Rank: " << rank << endl;
    updatedUsersFile << "Level: " << currentLevel << endl;
    updatedUsersFile << "Lives: " << livesLeft << endl;
    updatedUsersFile << "Coins: " << coins << endl;
    updatedUsersFile << "Key: " << key << endl;
    updatedUsersFile << "PositionInfo: '" << playerPositionInfo << "'" << endl;
    updatedUsersFile << "LevelStatus: " << levelStatus << endl;

    string mazeFilePathName = mazesFilePath(currentLevel);

    ifstream mazeFile(mazeFilePathName);

    if (!mazeFile.is_open()) {

        cerr << "Error: Could not open maze file " << mazeFilePathName << endl;
        updatedUsersFile.close();

        return;

    }

    string line;

    while (getline(mazeFile, line)) {

        updatedUsersFile << line << endl;

    }

    mazeFile.close();
    updatedUsersFile.close();

}

void printCommands() {

    cout << "Up - W/w\nDown - S/s\nLeft - A/a\nRigth - D/d\nExit and save - exit\n" << endl;

}
void playDungeonEscape() {

    string username;
    string command;

    while(true){

        printCommands();
        
        logInSignUp(username, command);
        
        if (command == "exit") {
        
            break;
        
        }

        while (true) {

           
            string filePath = "UsersNames/" + username;

            string rank = getRank(filePath);
            
            int currentLevel = getLevel(filePath);
            
            int livesLeft = getLives(filePath);
            
            int coins = getCoins(filePath);
            
            string key = getKey(filePath);
            
            char playerPositionInfo = getPlayerPositionInfo(filePath);
            
            string levelStatus = getLevelStatus(filePath);

            playFromSaveOrNew(username, command,currentLevel);

             if (command == "exit") {

                break;
             
             }


              START_GAME:
             

            char maze[15][25];
            int playerRowPosition = 0;
            int playerColPosition = 0;

            loadMazeFromFile(username, maze);
            getPlayerPosition(playerRowPosition, playerColPosition, maze);

            while (true) {

                clearConsole();

                cout << "Rank: " << rank << endl;
                cout << "Level: " << currentLevel << endl;
                cout << "Lives: " << livesLeft << endl;
                cout << "Coins: " << coins << endl;
                cout << "Key: " << key << endl;
                cout << "PlayerPosition: '" << playerPositionInfo << "'" << endl;
                cout << "LevelStatus: " << levelStatus << endl;

                printMaze(maze);

                if (livesLeft == 0) {
                    
                    cout << "No lives left! The level will restart automatically!" << endl;
                    
                    delay(5);
                    
                    livesLeft = 3;
                    
                    clearConsole();

                    goto START_GAME;
                   
                }
               
                cin >> command;  // W/w,A/a,S/s,D/d
               
                toLowerCase(command);

                if (command == "exit") {
                    break;
                }

                
                movePlayer(playerRowPosition
                    , playerColPosition
                    , maze
                    , command
                    , rank
                    , currentLevel
                    , livesLeft
                    , coins
                    , key
                    , playerPositionInfo
                    , levelStatus);

                if (levelStatus == "Complited") {

                    updateRank(rank);

                    updateLevel(currentLevel);
                    
                    newLevelMaze(username
                                , rank
                                , currentLevel
                                , livesLeft
                                , coins
                                , key
                                , playerPositionInfo
                                , levelStatus);
                   

                    goto START_GAME;

                }


                

            }
                
                clearConsole();

                cout << "Exited from level!" << endl;

                saveMazeAndStast(username, maze, rank, currentLevel, livesLeft, coins, key, playerPositionInfo, levelStatus);

                cout << "Progress saved!" << endl;

        }

        clearConsole();

        cout << "Exited from profile!" << endl;

    }

    clearConsole();

    cout << "Exited from game!" << endl;

}


int main() {

  playDungeonEscape();
  
}