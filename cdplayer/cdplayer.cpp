// cdplayer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cctype>
#include <cassert>
#include <iostream>
#include <string>


using namespace std;

bool isValidCDPlayerString(string cdstring);
bool isOpen(string cdstring);
bool hasCD(string cdstring);
int totalTracksPlayed(string cdstring);
int currentTrack(string cdstring);



//these functions should not read anything cin or cout

bool isValidCDPlayerString(string cdstring)   //this is the hardest, longest, most difficult function; should do the work all by itself
{

    bool result = true;

    if (cdstring[0] != 'O') {
        result = false;
    }

    //Require O followed by any number of Cs and Os, as long as the player is open when it is tried to be closed and closed when it is tried to be opened

    string t;

    for (size_t k = 0; k < cdstring.size(); k++)
    {
        if (cdstring[k] == 'O' || cdstring[k] == 'C')
        {
            t += cdstring[k];
        }
    }
    for (size_t k = 1; k < t.size(); k++)   // before C, there needs to be O
    {
        if (t[k] == 'C')
        {
            if (t[k - 1] != 'O')
            {
                result = false;
            }
        }
        else if (t[k] == 'O')              // before O, there needs to be C (except for the beginning)
        {
            if (t[k - 1] != 'C')
            {
                result = false;
            }
        }
    }

    //Require O followed by Cs and Os along with any number of Is and Rs, as long as the player is open when a cd is inserted and as long as the player is open and holds a cd when a cd is removed

    string n;

    for (size_t k = 0; k < cdstring.size(); k++)
    {
        if (cdstring[k] == 'O' || cdstring[k] == 'R' || cdstring[k] == 'I')
        {
            n += cdstring[k];
        }
    }
    for (size_t k = 1; k < n.size(); k++)   // before I, there needs to be O or R
    {
        if (n[k] == 'I')
        {
            if (!(n[k - 1] == 'O' || n[k - 1] == 'R'))
            {
                result = false;
            }
        }
    }

    for (size_t k = 2; k < n.size(); k++)     // before R, IO or OI needs to exist
    {
        if (n[1] == 'R')    // to account for when R is in index lower than 2 in string n
        {
            result = false;
        }
        else if (n[k] == 'R')
        {
            if (!(n.substr(k - 2, 2) == "IO" || n.substr(k - 2, 2) == "OI"))
            {
                result = false;
            }
        }
    }
    // Allow for a P once a cd is inserted and the player is closed.At this point, the current track should be 1
   
    string m;

    for (size_t k = 0; k < cdstring.size(); k++)
    {
        if (cdstring[k] == 'P' || cdstring[k] == 'I' || cdstring[k] == 'C' || cdstring[k] == 'S' || cdstring[k] == 'O')
        {
            m += cdstring[k];
        }
    }
    for (size_t k = 3; k < m.size(); k++)     
    {
        if (m[1] == 'P' || m[2] == 'P'|| m[0] == 'P')                    //to account for when P is in index lower than 3 in string m
        {
            result = false;
        }
        else if (m[k] == 'P')
        {
            if (!(m.substr(k - 2, 2) == "IC" || m[k - 1] == 'S' || m.substr(k - 3, 3) == "SOC"))   //before P, IC or S or SOC must exist
            {
                result = false;
            }
            
        }
    }
    // Allow for a P followed by a sequence of a few digits 1 thru 9 in numerical order

    for (size_t k = 3; k < cdstring.size(); k++)     // before 1, ICP needs to exist
    {
        if (cdstring[0] == '1' || cdstring[1] == '1' || cdstring[2] == '1')    // to account for when 1 is in index lower than 3 in cdstring
        {
            result = false;
        }
        else if (cdstring[k] == '1')
        {
            if (cdstring.substr(k - 3, 3) != "ICP")
            {
                result = false;
            }
        }
        else if (cdstring[k] == '2' || cdstring[k] == '3' || cdstring[k] == '4' || cdstring[k] == '5' || cdstring[k] == '6' || cdstring[k] == '7' || cdstring[k] == '8' || cdstring[k] == '9')
        {
            if (cdstring.substr(k - 3, 3) == "ICP")       // before digits other than 1, ICP cannot exist
            {
                result = false;
            }
        }
    }

  
    
    
    // if there are digits, numerical order 
    string r;

    for (size_t k = 0; k < cdstring.size(); k++)     
    {
        if (isdigit(cdstring[k]))
        {
            r += cdstring[k];
        }
    }
    for (size_t k = 1; k < r.size(); k++)   // before 2, there needs to be 1
    {
        if (r[k] == '2')
        {
            if (r[k - 1] != '1')
            {
                result = false;
            }
        }
    }
    for (size_t k = 1; k < r.size(); k++)   // before 3, there needs to be 2
    {
        if (r[k] == '3')
        {
            if (r[k - 1] != '2')
            {
                result = false;
            }
        }
    }
    for (size_t k = 1; k < r.size(); k++)   // before 4, there needs to be 3
    {
        if (r[k] == '4')
        {
            if (r[k - 1] != '3')
            {
                result = false;
            }
        }
    }
    for (size_t k = 1; k < r.size(); k++)   // before 5, there needs to be 4
    {
        if (r[k] == '5')
        {
            if (r[k - 1] != '4')
            {
                result = false;
            }
        }
    }
    for (size_t k = 1; k < r.size(); k++)   // before 6, there needs to be 5
    {
        if (r[k] == '6')
        {
            if (r[k - 1] != '5')
            {
                result = false;
            }
        }
    }
    for (size_t k = 1; k < r.size(); k++)   // before 7, there needs to be 6
    {
        if (r[k] == '7')
        {
            if (r[k - 1] != '6')
            {
                result = false;
            }
        }
    }
    for (size_t k = 1; k < r.size(); k++)   // before 8, there needs to be 7
    {
        if (r[k] == '8')
        {
            if (r[k - 1] != '7')
            {
                result = false;
            }
        }
    }
    for (size_t k = 1; k < r.size(); k++)   // before 9, there needs to be 8
    {
        if (r[k] == '9')
        {
            if (r[k - 1] != '8')
            {
                result = false;
            }
        }
    }

    // Allows for an S at some point after a P. // some test cases make O after P possible too
    for (size_t k = 1; k < cdstring.size(); k++)
    {
        if (cdstring[k-1] == 'P')
        {
            if (!(cdstring[k] == 'S' || cdstring[k] == 'P'|| cdstring[k] == 'O' || cdstring[k] == '1' || cdstring[k] == '2' || cdstring[k] == '3' || cdstring[k] == '4' || cdstring[k] == '5' || cdstring[k] == '6' || cdstring[k] == '7' || cdstring[k] == '8' || cdstring[k] == '9'))
            {
                result = false;
            }
        }
        // before any digit, must be either P or another digit
        if (cdstring[k] == '1' || cdstring[k] == '2' || cdstring[k] == '3' || cdstring[k] == '4' || cdstring[k] == '5' || cdstring[k] == '6' || cdstring[k] == '7' || cdstring[k] == '8' || cdstring[k] == '9')
        {
            if (!(cdstring[k - 1] == 'P' || cdstring[k-1] == '1' || cdstring[k-1] == '2' || cdstring[k-1] == '3' || cdstring[k-1] == '4' || cdstring[k-1] == '5' || cdstring[k-1] == '6' || cdstring[k-1] == '7' || cdstring[k-1] == '8' || cdstring[k-1] == '9'))
            {
                result = false;
            }
        }
    }

    

   //Build a loop to process all the letters in a string.  
   //For the cd player string to valid, the entire string must be consumed with no extra ending white space or other characters.
    
    for (size_t a = 0; a < cdstring.size(); a++)
    {
        if (!(cdstring[a] == 'O' || cdstring[a] == 'I' || cdstring[a] == 'C' || cdstring[a] == 'P' || cdstring[a] == 'S' || cdstring[a] == 'R' || cdstring[a] == '1' || cdstring[a] == '2' || cdstring[a] == '3' || cdstring[a] == '4' || cdstring[a] == '5' || cdstring[a] == '6' || cdstring[a] == '7' || cdstring[a] == '8' || cdstring[a] == '9'))
        {
            result = false;
        }
    }

  

    return (result);
}


bool isOpen(string cdstring)        //should reuse code from previous function; isOpen only returns true if string is valid  & at the end of the player, it's open
{
    bool result = true;
    int a = 0;
    int b = 0;

    if (isValidCDPlayerString(cdstring) == true) {                //as long as there is more O's than C's, should be true (another way to implement it)
        for (size_t i = 0; i < cdstring.size(); i++) {
            if (cdstring.at(i) == 'C') {
                a++; //increase count of C's
            }
            if (cdstring.at(i) == 'O') {
                b++; //increase count of O's 
            }
        }
    }
    if (b > a) 
    {
       result = true;
    }
    else 
    {
       result = false;
    }
    
    return(result);
}


bool hasCD(string cdstring)
{
    bool result = true;
    int a = 0;
    int b = 0;

    if (isValidCDPlayerString(cdstring) == true) {                //as long as there is more I's than R's, should be true (another way to implement it)
        for (size_t i = 0; i < cdstring.size(); i++) {
            if (cdstring.at(i) == 'I') {
                a++; //increase count of I's
            }
            if (cdstring.at(i) == 'R') {
                b++; //increase count of R's 
            }
        }
    }
    if (a > b)
    {
        result = true;
    }
    else
    {
        result = false;
    }

    return(result);
}


int totalTracksPlayed(string cdstring)
{
    string h;
    
    if (isValidCDPlayerString(cdstring) == true)
    {
        for (size_t k = 0; k < cdstring.size(); k++)
        {
            if (isdigit(cdstring[k]))
            {
                h += cdstring[k];
            }
        }
    }
    
    int c = 0;
    
    if (h.size() > 0)
    {
        c = h.size();
    }
    else
    {
        c = -1;
    }
    
    return (c);

}



int currentTrack(string cdstring)
{
    int a = 0;
    int b = 0;

    string n;
    if (isValidCDPlayerString(cdstring) == true)
    {
        for (size_t k = 0; k < cdstring.size(); k++)
        {
            if (isdigit(cdstring[k]) || cdstring[k] == 'I' || cdstring[k] == 'R')
            {
                n += cdstring[k];
            }
        }
    }
    

    a = n.size() - 1;

    if (n.size() == 0)
    {
        b = -1;
    }

    else {

        if (n[a] == 'I')
        {
            b = 1;
        }
        if (n[a] == 'R')
        {
            b = -1;
        }
        if (isdigit(n[a]))
        {
            if (n[a] == '1')
            {
                b = 2;
            }
            if (n[a] == '2')
            {
                b = 3;
            }
            if (n[a] == '3')
            {
                b = 4;
            }
            if (n[a] == '4')
            {
                b = 5;
            }
            if (n[a] == '5')
            {
                b = 6;
            }
            if (n[a] == '6')
            {
                b = 7;
            }
            if (n[a] == '7')
            {
                b = 8;
            }
            if (n[a] == '8')
            {
                b = 9;
            }   
        }
    }
    
    return(b);
}




int main()
{
    cout.setf(ios::boolalpha);

    assert(isValidCDPlayerString("") == false);
    assert(isValidCDPlayerString("    ") == false);
    assert(isOpen("    ") == false);
    assert(hasCD("      ") == false);
    assert(totalTracksPlayed("      ") == -1);
    assert(currentTrack("      ") == -1);

    cerr << "All tests succeeded" << endl;
    return (0);
}


