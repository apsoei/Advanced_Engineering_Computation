#include <sstream>
#include <iostream>
#include <cstdio>
int main()
{
//    int score = 123;
//    std::stringstream str;
//    str << score;
//    std::string s;
//    s = "Score: ";
//    int score2 = 456;
//    str << score2;
//    s += str.str();

//    std::cout << s << std::endl;

    char text[80];
    int nameNum = 0;
    sprintf(text,"%d.png", nameNum);
    std::cout << text << std::endl;
    
    nameNum+=1;
    sprintf(text,"%d.png", nameNum);
    std::cout << text << std::endl;
    return 0;
}