#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

struct cell
{
    char letter;
    bool used = false;
};

bool checkForward(string password, vector<vector<cell>>& board, int letter_index, int x, int y, int array_size_x)
{
    if (password[letter_index] == board[y][x].letter)
    {
        //cout << "Right Letter found: " << board[y][x].letter << endl;
        if (x + 1 < array_size_x && letter_index != password.length()-1)
        {
            if (checkForward(password, board, letter_index+1, x + 1, y, array_size_x) == true)
            {
                board[y][x].used = true;
                //cout << "1." << endl;
                return true;
            }
            else
            {
                //cout << "2." << endl;
                return false;
            }
        }
        else if (x+1 >= array_size_x && letter_index != password.length()-1)
        {
            //cout << "3." << endl;
            return false;
        }
        else if (letter_index == password.length()-1)
        {
            //cout << "4." << endl;
            board[y][x].used = true;
            return true;
        }
        else
        {
            //cout << "5." << endl;
            return true;
        }
    }
    else
    {
        //cout << "Wrong letter found: " << board[y][x].letter << endl;
        return false;
    }
}

bool checkBackward(string password, vector<vector<cell>>& board, int letter_index, int x, int y, int array_size_x)
{
    if (password[letter_index] == board[y][x].letter)
    {
        //cout << "Right Letter found: " << board[y][x].letter << endl;
        if (x - 1 >= 0 && letter_index != password.length() - 1)
        {
            if (checkBackward(password, board, letter_index + 1, x - 1, y, array_size_x) == true)
            {
                board[y][x].used = true;
                //cout << "1." << endl;
                return true;
            }
            else
            {
                //cout << "2." << endl;
                return false;
            }
        }
        else if (x - 1 < 0 && letter_index != password.length() - 1)
        {
            //cout << "3." << endl;
            return false;
        }
        else if (letter_index == password.length() - 1)
        {
            //cout << "4." << endl;
            board[y][x].used = true;
            return true;
        }
        else
        {
            //cout << "5." << endl;
            return true;
        }
    }
    else
    {
        //cout << "Wrong letter found: " << board[y][x].letter << endl;
        return false;
    }
}

bool checkDown(string password, vector<vector<cell>>& board, int letter_index, int x, int y, int array_size_y)
{
    if (password[letter_index] == board[y][x].letter)
    {
        //cout << "Right Letter found: " << board[y][x].letter << endl;
        if (y + 1 < array_size_y && letter_index != password.length() - 1)
        {
            if (checkDown(password, board, letter_index + 1, x, y+1, array_size_y) == true)
            {
                board[y][x].used = true;
                //cout << "1." << endl;
                return true;
            }
            else
            {
                //cout << "2." << endl;
                return false;
            }
        }
        else if (y + 1 >= array_size_y && letter_index != password.length() - 1)
        {
            //cout << "3." << endl;
            return false;
        }
        else if (letter_index == password.length() - 1)
        {
            //cout << "4." << endl;
            board[y][x].used = true;
            return true;
        }
        else
        {
            //cout << "5." << endl;
            return true;
        }
    }
    else
    {
        //cout << "Wrong letter found: " << board[y][x].letter << endl;
        return false;
    }
}

bool checkUp(string password, vector<vector<cell>>& board, int letter_index, int x, int y, int array_size_y)
{
    if (password[letter_index] == board[y][x].letter)
    {
        //cout << "Right Letter found: " << board[y][x].letter << endl;
        if (y - 1 >= 0 && letter_index != password.length() - 1)
        {
            if (checkUp(password, board, letter_index + 1, x, y - 1, array_size_y) == true)
            {
                board[y][x].used = true;
                //cout << "1." << endl;
                return true;
            }
            else
            {
                //cout << "2." << endl;
                return false;
            }
        }
        else if (y - 1 < 0 && letter_index != password.length() - 1)
        {
            //cout << "3." << endl;
            return false;
        }
        else if (letter_index == password.length() - 1)
        {
            //cout << "4." << endl;
            board[y][x].used = true;
            return true;
        }
        else
        {
            //cout << "5." << endl;
            return true;
        }
    }
    else
    {
        //cout << "Wrong letter found: " << board[y][x].letter << endl;
        return false;
    }
}

bool checkForwardDown(string password, vector<vector<cell>>& board, int letter_index, int x, int y, int array_size_x, int array_size_y)
{
    if (password[letter_index] == board[y][x].letter)
    {
        //cout << "Right Letter found: " << board[y][x].letter << endl;
        if (y + 1 < array_size_y && x+1 < array_size_x && letter_index != password.length() - 1)
        {
            if (checkForwardDown(password, board, letter_index + 1, x+1, y + 1, array_size_x, array_size_y) == true)
            {
                board[y][x].used = true;
                //cout << "1." << endl;
                return true;
            }
            else
            {
                //cout << "2." << endl;
                return false;
            }
        }
        else if (y + 1 >= array_size_y && x+1 >=array_size_x && letter_index != password.length() - 1)
        {
            //cout << "3." << endl;
            return false;
        }
        else if (letter_index == password.length() - 1)
        {
            //cout << "4." << endl;
            board[y][x].used = true;
            return true;
        }
        else
        {
            //cout << "5." << endl;
            return false;
        }
    }
    else
    {
        //cout << "Wrong letter found: " << board[y][x].letter << endl;
        return false;
    }
}

bool checkForwardUp(string password, vector<vector<cell>>& board, int letter_index, int x, int y, int array_size_x, int array_size_y)
{
    if (password[letter_index] == board[y][x].letter)
    {
        //cout << "Right Letter found: " << board[y][x].letter << endl;
        if (y - 1 >= 0 && x + 1 < array_size_x && letter_index != password.length() - 1)
        {
            if (checkForwardUp(password, board, letter_index + 1, x + 1, y - 1, array_size_x, array_size_y) == true)
            {
                board[y][x].used = true;
                //cout << "1." << endl;
                return true;
            }
            else
            {
                //cout << "2." << endl;
                return false;
            }
        }
        else if (y + 1 < 0 && x + 1 >= array_size_x && letter_index != password.length() - 1)
        {
            //cout << "3." << endl;
            return false;
        }
        else if (letter_index == password.length() - 1)
        {
            //cout << "4." << endl;
            board[y][x].used = true;
            return true;
        }
        else
        {
            //cout << "5." << endl;
            return false;
        }
    }
    else
    {
        //cout << "Wrong letter found: " << board[y][x].letter << endl;
        return false;
    }
}

bool checkBackwardDown(string password, vector<vector<cell>>& board, int letter_index, int x, int y, int array_size_x, int array_size_y)
{
    if (password[letter_index] == board[y][x].letter)
    {
        //cout << "Right Letter found: " << board[y][x].letter << endl;
        if (y + 1 < array_size_y && x - 1 >= 0 && letter_index != password.length() - 1)
        {
            if (checkBackwardDown(password, board, letter_index + 1, x - 1, y + 1, array_size_x, array_size_y) == true)
            {
                board[y][x].used = true;
                //cout << "1." << endl;
                return true;
            }
            else
            {
                //cout << "2." << endl;
                return false;
            }
        }
        else if (y + 1 >= array_size_y && x - 1 < 0 && letter_index != password.length() - 1)
        {
            //cout << "3." << endl;
            return false;
        }
        else if (letter_index == password.length() - 1)
        {
            //cout << "4." << endl;
            board[y][x].used = true;
            return true;
        }
        else
        {
            //cout << "5." << endl;
            return false;
        }
    }
    else
    {
        //cout << "Wrong letter found: " << board[y][x].letter << endl;
        return false;
    }
}

bool checkBackwardUp(string password, vector<vector<cell>>& board, int letter_index, int x, int y, int array_size_x, int array_size_y)
{
    if (password[letter_index] == board[y][x].letter)
    {
        //cout << "Right Letter found: " << board[y][x].letter << endl;
        if (y - 1 >= 0 && x - 1 >= 0 && letter_index != password.length() - 1)
        {
            if (checkBackwardUp(password, board, letter_index + 1, x - 1, y - 1, array_size_x, array_size_y) == true)
            {
                board[y][x].used = true;
                //cout << "1." << endl;
                return true;
            }
            else
            {
                //cout << "2." << endl;
                return false;
            }
        }
        else if (y - 1 <  0 && x - 1 < 0  && letter_index != password.length() - 1)
        {
            //cout << "3." << endl;
            return false;
        }
        else if (letter_index == password.length() - 1)
        {
            //cout << "4." << endl;
            board[y][x].used = true;
            return true;
        }
        else
        {
            //cout << "5." << endl;
            return false;
        }
    }
    else
    {
        //cout << "Wrong letter found: " << board[y][x].letter << endl;
        return false;
    }
}

int main()
{
    int array_size_x=0, array_size_y=0;

    string input = "a";
    vector<string>passwords;

    fstream f_passwords ("passwords.txt");
    while (f_passwords >> input)
    {
        passwords.push_back(input);
    }
    f_passwords.close();

    int a_s_x_temp = 0;
    fstream f_board("board.txt");
    while (f_board >> input)
    {
        array_size_x = input.length();
        if (array_size_x == 0 || (a_s_x_temp != array_size_x && array_size_y != 0))
        {
            cout << "Wrong size" << endl;
            return 0;
        }
        a_s_x_temp = array_size_x;
        array_size_y++;
    }

    f_board.clear();
    f_board.seekg(0);
    vector<vector<cell>> board(array_size_y, vector<cell>(array_size_x));
    {
        int y = 0;
        while (f_board >> input)
        {
            for (int x = 0; x < array_size_x; x++)
            {
                board[y][x].letter = input[x];
            }

            y++;
        }
    }
    f_board.close();

    cout << "The Board" << endl;
    for (int y = 0; y < array_size_y; y++)
    {
        for (int x = 0; x < array_size_x; x++)
        {
            cout << board[y][x].letter << " ";
        }
        cout << endl;
    }

   
    for (int password_index = 0; password_index < passwords.size(); password_index++)
    {
        int password_length = passwords[password_index].length();
        //cout << "\t\t\t\t\tSearching for password " << passwords[password_index] << endl;
        bool password_found = false;
        for (int y = 0; y < array_size_y; y++)
        {
            for (int x = 0; x < array_size_x; x++)
            {
                if (board[y][x].letter == passwords[password_index][0])
                {
                    //cout << "First letter found" << endl;
                    
                    //cout << "\t\tChecking forward" << endl;
                    password_found = checkForward(passwords[password_index], board, 0, x, y, array_size_x); //forward
                    if (password_found == false)
                    {
                        //cout << "\t\tChecking backward" << endl;
                        password_found = checkBackward(passwords[password_index], board, 0, x, y, array_size_x); //backward
                    }
                    if (password_found == false)
                    {
                        //cout << "\t\tChecking down" << endl;
                        password_found = checkDown(passwords[password_index], board, 0, x, y, array_size_y);  //down
                    }
                    if (password_found == false)
                    {
                        //cout << "\t\tChecking up" << endl;
                        password_found = checkUp(passwords[password_index], board, 0, x, y, array_size_y);  //up
                    }
                    if (password_found == false)
                    {
                        //cout << "\t\tChecking forward down" << endl;
                        password_found = checkForwardDown(passwords[password_index], board, 0, x, y, array_size_x, array_size_y);  //cross forward-down
                    }
                    if (password_found == false)
                    {
                        //cout << "\t\tChecking forward up" << endl;
                        password_found = checkForwardUp(passwords[password_index], board, 0, x, y, array_size_x, array_size_y); //cross forward- up
                    }
                    if (password_found == false)
                    {
                        //cout << "\t\tChecking backward down" << endl;
                        password_found = checkBackwardDown(passwords[password_index], board, 0, x, y, array_size_x, array_size_y); //cross backward down
                    }
                    if (password_found == false)
                    {
                        //cout << "\t\tChecking backward up" << endl;
                        password_found = checkBackwardUp(passwords[password_index], board, 0, x, y, array_size_x, array_size_y); //cross backward up
                    }
                    if (password_found == true)
                    {
                        x = array_size_x;
                        y = array_size_y;
                    }
                }
            }
        }
        if (password_found == true)
        {        
            cout << "\t\t\t\t\tPassword " << passwords[password_index] << " found" << endl;
        }
        else
        {
            cout << "\t\t\t\t\tPassword " << passwords[password_index] << " not found" << endl;
        }
    }

    string final_password = "";
    for (int y = 0; y < array_size_y; y++)
    {
        for (int x= 0; x < array_size_x; x++)
        {
            if (board[y][x].used == false)
            {
                final_password += board[y][x].letter;
            }
        }
    }
    cout << "Password: " << final_password << endl << endl;

    cout << " ";
    for (int tmp = 0; tmp < array_size_x; tmp++) cout << "_ ";
    cout << endl;
    for (int y = 0; y < array_size_y; y++)
    {
        for (int x = 0; x < array_size_x; x++)
        {
            
                if (board[y][x].used == false)
                {
                    cout << "|" << board[y][x].letter;
                }
                else
                {
                    cout << "|_";
                }
            

       
        }
        cout <<"|" << endl;
    }
}
