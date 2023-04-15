#include"DoHoa.h"
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FORASCEN(i, min, max) for(int i = min; i <= max; i++)
#define FORDESCEN(i, max, min) for(int i = max; i >= min; i--)
char deletedChar = '@';
int iTurn = 0;
const int BOARD_SIZE = 4;
const int TEMP_SIZE = 8;
struct Selected
{
    char temp;
    int x, y;
};
Selected temp1 = { '@',-1,-1 };
Selected temp2 = { '@',-1,-1 };
//2D Pointer
char** createBoard() 
{
    char** board = NULL;
    board = new char* [BOARD_SIZE];
    FOR(i, BOARD_SIZE) {
        board[i] = new char[BOARD_SIZE];
    }
    return board;
}
//Delete Pointer
void delBoard(char** board) 
{
    FOR(i, BOARD_SIZE) {
        delete[] board[i];
    }
    delete[] board;
}
//Random board
void initBoard(char** board)
{
    srand(time(NULL));

    vector<char> character(TEMP_SIZE);
    for (int i = 0; i < TEMP_SIZE; i++)
    {
        character[i] = 'A' + rand() % 8;
    }
    random_shuffle(character.begin(), character.end());
    int Temp = 0;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j] = character[Temp];
            Temp++;
            if (Temp >= TEMP_SIZE)
            {
                Temp = 0;
            }
        }
    }
}

bool checkValid(char** board) {
    FOR(i, BOARD_SIZE) {
        FOR(j, BOARD_SIZE) {
            if (board[i][j] != '@') {
                return 1;
            }
        }
    }
    return 0;
}

bool checkNear(int x1, int x2) {
    return ((++x1 == x2) ? 1 : 0);
}

bool iMatching(char** board, Selected temp1, Selected temp2) {
    bool checkValid = 1;
    if (temp1.x == temp2.x && temp1.y == temp2.y)
        return checkValid;
    else if (temp1.x == temp2.x) {
        if (temp1.y < temp2.y) {
            if (checkNear(temp1.y, temp2.y)) {
                return checkValid = 1;
            }
            FORASCEN(i, temp1.y + 1, temp2.y - 1) {
                if (board[temp1.x][i] != '@') {
                    checkValid = 0;
                    break;
                }
            }
        }
        else {
            if (checkNear(temp2.y, temp1.y)) {
                return checkValid = 1;
            }
            FORASCEN(i, temp2.y + 1, temp1.y - 1) {
                if (board[temp2.x][i] != '@') {
                    checkValid = 0;
                    break;
                }
            }
        }
        return checkValid;
    }
    else if (temp1.y == temp2.y) {
        if (temp1.x < temp2.x) {
            if (checkNear(temp1.x, temp2.x)) {
                return checkValid = 1;
            }
            FORASCEN(i, temp1.x + 1, temp2.x - 1) {
                if (board[i][temp1.y] != '@') {
                    checkValid = 0;
                    break;
                }
            }
        }
        else {
            if (checkNear(temp2.x, temp1.x)) {
                return checkValid = 1;
            }
            FORASCEN(i, temp2.x + 1, temp1.x - 1) {
                if (board[i][temp2.y] != '@') {
                    checkValid = 0;
                    break;
                }
            }
        }
        return checkValid;
    }
    else return checkValid = 0;
}

bool lMatching(char** board) {
    Selected temp3, temp4;
    bool checkValid;
    temp3.x = temp2.x; temp3.y = temp1.y; temp3.temp = board[temp3.x][temp3.y];
    temp4.x = temp1.x; temp4.y = temp2.y; temp4.temp = board[temp4.x][temp4.y];

    if (temp3.temp != '@' && temp4.temp != '@')
        return false;
    else if ((iMatching(board, temp2, temp3) && iMatching(board, temp3, temp1)) ||
        (iMatching(board, temp2, temp4) && iMatching(board, temp4, temp1)))
        return true;
    else return false;
    return checkValid;
}

bool zMatching(char** board, Selected temp1, Selected temp2) {
    bool checkValid = 0;
    Selected temp3, temp4;
    if (temp1.x > temp2.x) {
        temp3.y = temp2.y; temp4.y = temp1.y;
        FORASCEN(i, temp2.x + 1, temp1.x - 1) {
            temp3.x = temp4.x = i;
            if (board[i][temp3.y] != '@' || board[i][temp4.y] != '@')
                continue;
            if (iMatching(board, temp3, temp4)) {
                if (iMatching(board, temp2, temp3) && iMatching(board, temp4, temp1)) {
                    checkValid = 1;
                    break;
                }
            }
        }
    }
    else {
        temp3.y = temp1.y; temp4.y = temp2.y;
        FORASCEN(i, temp1.x + 1, temp2.x - 1) {
            temp3.x = temp4.x = i;
            if (board[i][temp3.y] != '@' || board[i][temp4.y] != '@')
                continue;
            if (iMatching(board, temp3, temp4)) {
                if (iMatching(board, temp1, temp3) && iMatching(board, temp4, temp2)) {
                    checkValid = 1;
                    break;
                }
            }
        }
    }

    if (temp1.y > temp2.y) {
        temp3.x = temp2.x; temp4.x = temp1.x;
        FORASCEN(i, temp2.y + 1, temp1.y - 1) {
            temp3.y = temp4.y = i;
            if (board[temp3.x][i] != '@' || board[temp4.x][i] != '@')
                continue;
            if (iMatching(board, temp3, temp4)) {
                if (iMatching(board, temp2, temp3) && iMatching(board, temp4, temp1)) {
                    checkValid = 1;
                    break;
                }
            }
        }
    }
    else {
        temp3.x = temp1.x; temp4.x = temp2.x;
        FORASCEN(i, temp1.y + 1, temp2.y - 1) {
            temp3.y = temp4.y = i;
            if (board[temp3.x][i] != '@' || board[temp4.x][i] != '@')
                continue;
            if (iMatching(board, temp3, temp4)) {
                if (iMatching(board, temp1, temp3) && iMatching(board, temp4, temp2)) {
                    checkValid = 1;
                    break;
                }
            }
        }
    }
    return checkValid;
}


bool uMatchingBorder(char** board, Selected temp1, Selected temp2) {
    bool checkValid = 1;
    Selected temp;
    if ((temp1.x == 0 && temp2.x == 0) || (temp1.x == BOARD_SIZE - 1 && temp2.x == BOARD_SIZE - 1)) {
        return  1;
    }
    else if ((temp1.y == 0 && temp2.y == 0) || (temp1.y == BOARD_SIZE - 1 && temp2.y == BOARD_SIZE - 1)) {
        return  1;
    }
    if (temp1.x == 0 || temp1.x == BOARD_SIZE - 1) {
        temp.x = temp1.x; temp.y = temp2.y;
        if (board[temp.x][temp.y] != '@') {
            checkValid = 0;
        }
        else {
            if (iMatching(board, temp, temp2) && uMatchingBorder(board, temp, temp1)) {
                return  1;
            }
        }
    }
    if (temp2.x == 0 || temp2.x == BOARD_SIZE - 1) {
        temp.x = temp2.x; temp.y = temp1.y;
        if (board[temp.x][temp.y] != '@') {
            checkValid = 0;
        }
        else {
            if ((iMatching(board, temp, temp1)) && (uMatchingBorder(board, temp, temp2))) {
                return 1;
            }
        }
    }
    if (temp1.y == 0 || temp1.y == BOARD_SIZE - 1) {
        temp.x = temp2.x; temp.y = temp1.y;
        if (board[temp.x][temp.y] != '@') {
            checkValid = 0;
        }
        else {
            if (iMatching(board, temp, temp2) && uMatchingBorder(board, temp, temp1)) {
                return 1;
            }
        }
    }
    if (temp2.y == 0 || temp2.y == BOARD_SIZE - 1) {
        temp.x = temp1.x; temp.y = temp2.y;
        if (board[temp.x][temp.y] != '@') {
            checkValid = 0;
        }
        else {
            if (iMatching(board, temp, temp1) && uMatchingBorder(board, temp, temp2)) {
                return 1;
            }
        }
    }
    return checkValid;
}

bool uMatching(char** board, Selected temp1, Selected temp2) {
    bool checkValid = 0;
    Selected temp3, temp4;
    if (uMatchingBorder(board, temp1, temp2)) {
        return checkValid = 1;
    }
    if (temp1.x > temp2.x) {
        temp3.y = temp2.y; temp4.y = temp1.y;
        FORDESCEN(i, temp2.x - 1, 0) {
            temp3.x = temp4.x = i;
            if (board[i][temp3.y] != '@' || board[i][temp4.y] != '@')
                continue;
            if (iMatching(board, temp3, temp4)) {
                if (iMatching(board, temp3, temp2) && iMatching(board, temp4, temp1)) {
                    checkValid = 1;
                    break;
                }
            }
            if (i == 0) {
                if (iMatching(board, temp3, temp2) && iMatching(board, temp4, temp1))
                    checkValid = 1;
            }
        }
        FORASCEN(i, temp1.x + 1, BOARD_SIZE - 1) {
            temp3.x = temp4.x = i;
            if (board[i][temp3.y] != '@' || board[i][temp4.y] != '@')
                continue;
            if (iMatching(board, temp3, temp4)) {
                if (iMatching(board, temp3, temp2) && iMatching(board, temp4, temp1)) {
                    checkValid = 1;
                    break;
                }
            }
            if (i == BOARD_SIZE - 1) {
                if (iMatching(board, temp3, temp2) && iMatching(board, temp4, temp1))
                    checkValid = 1;
            }
        }
    }
    else {
        temp3.y = temp2.y; temp4.y = temp1.y;
        FORASCEN(i, temp2.x + 1, BOARD_SIZE - 1) {
            temp3.x = temp4.x = i;
            if (board[i][temp3.y] != '@' || board[i][temp4.y] != '@')
                continue;
            if (iMatching(board, temp3, temp4)) {
                if (iMatching(board, temp3, temp2) && iMatching(board, temp4, temp1)) {
                    checkValid = 1;
                    break;
                }
            }
            if (i == BOARD_SIZE - 1) {
                if (iMatching(board, temp3, temp2) && iMatching(board, temp4, temp1))
                    checkValid = 1;
            }
        }
        FORDESCEN(i, temp1.x - 1, 0) {
            temp3.x = temp4.x = i;
            if (board[i][temp3.y] != '@' || board[i][temp4.y] != '@')
                continue;
            if (iMatching(board, temp3, temp4)) {
                if (iMatching(board, temp3, temp2) && iMatching(board, temp4, temp1)) {
                    checkValid = 1;
                    break;
                }
            }
            if (i == 0) {
                if (iMatching(board, temp3, temp2) && iMatching(board, temp4, temp1))
                    checkValid = 1;
            }
        }
    }
    if (temp1.y > temp2.y) {
        temp3.x = temp2.x; temp4.x = temp1.x;
        FORDESCEN(i, temp2.y - 1, 0) {
            temp3.y = temp4.y = i;
            if (board[temp3.x][i] != '@' || board[temp4.x][i] != '@')
                continue;
            if (iMatching(board, temp3, temp4)) {
                if (iMatching(board, temp3, temp2) && iMatching(board, temp4, temp1)) {
                    checkValid = 1;
                    break;
                }
            }
            if (i == 0) {
                if (iMatching(board, temp3, temp2) && iMatching(board, temp4, temp1))
                    checkValid = 1;
            }
        }
        FORASCEN(i, temp1.y + 1, BOARD_SIZE - 1) {
            temp3.y = temp4.y = i;
            if (board[temp3.x][i] != '@' || board[temp4.x][i] != '@')
                continue;
            if (iMatching(board, temp3, temp4)) {
                if (iMatching(board, temp3, temp2) && iMatching(board, temp4, temp1)) {
                    checkValid = 1;
                    break;
                }
            }
            if (i == BOARD_SIZE - 1) {
                if (iMatching(board, temp3, temp2) && iMatching(board, temp4, temp1))
                    checkValid = 1;
            }
        }
    }
    else {
        temp3.x = temp2.x; temp4.x = temp1.x;
        FORASCEN(i, temp2.y + 1, BOARD_SIZE - 1) {
            temp3.y = temp4.y = i;
            if (board[temp3.x][i] != '@' || board[temp4.x][i] != '@')
                continue;
            if (iMatching(board, temp3, temp4)) {
                if (iMatching(board, temp3, temp2) && iMatching(board, temp4, temp1)) {
                    checkValid = 1;
                    break;
                }
            }
            if (i == BOARD_SIZE - 1) {
                if (iMatching(board, temp3, temp2) && iMatching(board, temp4, temp1))
                    checkValid = 1;
            }
        }
        FORDESCEN(i, temp1.y - 1, 0) {
            temp3.y = temp4.y = i;
            if (board[temp3.x][i] != '@' || board[temp4.x][i] != '@')
                continue;
            if (iMatching(board, temp3, temp4)) {
                if (iMatching(board, temp3, temp2) && iMatching(board, temp4, temp1)) {
                    checkValid = 1;
                    break;
                }
            }
            if (i == 0) {
                if (iMatching(board, temp3, temp2) && iMatching(board, temp4, temp1))
                    checkValid = 1;
            }
        }
    }
    return checkValid;
}

int play()
{   
    char** board = createBoard();
    initBoard(board);
    int tt = 0, tt1 = 0;
    int mau[4][4];
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            mau[i][j] = MAUCHU;
        }
    mau[0][0] = MAUNEN;
    while (1)
    {
        clrscr();

        if (iTurn == 2)
        {
            if ((iMatching(board,temp1,temp2) == true || lMatching(board) == true || zMatching(board,temp1,temp2) == true || uMatching(board,temp1,temp2) == true)
                &&temp1.temp==temp2.temp)
            {
                PlaySound(TEXT("C:\\Users\\dinht\\source\\repos\\MatchingGame\\MatchingGame\\Correct.wav"), NULL, SND_FILENAME);
                cout << "Nice bro" << endl;
                board[temp1.x][temp1.y] = '@';
                board[temp2.x][temp2.y] = '@';
                bool check = true;
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        if (board[i][j] != '@')
                        {
                            check = false;
                        }
                    }
                }
                if (check == true)
                {
                    cout << "You win" << endl;
                    fstream new_file;
                    new_file.open("input.txt", ios::in);
                    if (new_file.is_open())
                    {
                        string str;
                        while (getline(new_file, str))
                        {
                            cout << str<<endl;
                        }
                    }
                    PlaySound(TEXT("C:\\Users\\dinht\\source\\repos\\MatchingGame\\MatchingGame\\victory.wav"), NULL, SND_FILENAME);
                    new_file.close();
                    exit(1);
                }
            }
            else
            {
                cout << "That is a wrong number" << endl;
                PlaySound(TEXT("C:\\Users\\dinht\\source\\repos\\MatchingGame\\MatchingGame\\wrong.wav"), NULL, SND_FILENAME);
            }
            iTurn = 0;
        }

        for (int i = 0; i < BOARD_SIZE; i++)
        {
            cout << "\n";

            for (int j = 0; j < BOARD_SIZE; j++)
            {
                TextColor(mau[i][j]);
                cout << "  " << board[i][j] << "  ";
            }
            cout << endl;
        }
        int z = _getch();
        TRANGTHAI trangthai = key(z);
        switch (trangthai)
        {
        case UP:
        {
            if (tt == 0)
            {
                tt = BOARD_SIZE - 1;
            }
            else
                tt -= 1;
            break;

        }
        case DOWN:
        {
            if (tt == BOARD_SIZE - 1)
            {
                tt = 0;
            }
            else
                tt += 1;
            break;

        }
        case LEFT:
        {
            if (tt1 == 0)
            {
                tt1 = BOARD_SIZE - 1;
            }
            else
                tt1 -= 1;
            break;
        }
        case RIGHT:
        {
            if (tt1 == BOARD_SIZE - 1)
            {
                tt1 = 0;
            }
            else
                tt1 += 1;
            break;
        }
        case SPACE:
        {
            gotoXY(0, 1);

            for (int i = 0; i < BOARD_SIZE; i++)
            {
                cout << "\n";

                for (int j = 0; j < BOARD_SIZE; j++)
                {
                    TextColor(mau[i][j]);
                    cout << "  " << board[i][j] << "  ";
                }
                cout << endl;
            }
            switch (iTurn)
            {
            case 0:
            {
                temp1.temp = board[tt][tt1];
                temp1.x = tt;
                temp1.y = tt1;
                iTurn = 1;
                break;
            }
            case 1:
            {
                temp2.temp = board[tt][tt1];
                temp2.x = tt;
                temp2.y = tt1;
                iTurn = 2;
                break;
            }
            }

            break;
        }

        case ENTER:return tt;
        }
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                mau[i][j] = MAUCHU;
            }
        mau[tt][tt1] = MAUNEN;
    }
    delBoard(board);
}