#include <iostream>     // Oh my god this is so bad
#include <string>
#include <vector>
void ascii(int num);
void menu();

std::string base64_encode(const std::string& in) {                 
    std::string out;
    int val = 0;
    int valb = -6;

    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }

    if (valb > -6) {
        out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[((val << 8) >> (valb + 8)) & 0x3F]);
    }

    while (out.size() % 4) {
        out.push_back('=');
    }

    return out;
}

std::string base64_decode(const std::string& in) {
    std::string out;
    std::vector<int> T(256, -1);

    for (int i = 0; i < 64; i++) {
        T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;
    }

    int val = 0;
    int valb = -8;

    for (unsigned char c : in) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }

    return out;
}                                                


void clearbuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
}

void waitenter() {
    std::cout << "\nPress Enter to retun to menu: ";
    clearbuffer();
    std::cin.get();
    menu();
}

void enc() {

    std::string text, password;

    std::cout << "Text: ";
    clearbuffer();
    std::getline(std::cin, text);

    std::cout << "Password: ";
    std::getline(std::cin, password);

    std::string result = text;
    size_t pass_len = password.length();
    std::cout << "\nCrypting...\n";
    for (size_t i = 0; i < result.size(); i++) {
        unsigned char tbyte = result[i];
        unsigned char pbyte = password[i % pass_len];
        result[i] = tbyte ^ pbyte;
    }
    std::string base64_result = base64_encode(result);
    std::cout << "[" << base64_result << "]\n";
    waitenter();
}

void dec() {

    std::string text, password;

    std::cout << "Text: ";
    clearbuffer();
    std::getline(std::cin, text);

    std::cout << "Password: ";
    std::getline(std::cin, password);

    int pass_len = password.length();
    std::string result = base64_decode(text);

    std::cout << "\nCyphering..\n";

    for (size_t i = 0; i < result.size(); i++) {
        unsigned char tbyte = result[i];
        unsigned char pbyte = password[i % pass_len];
        result[i] = tbyte ^ pbyte;
    }

    std::cout << "[" << result << "]\n";
    waitenter();
}

void help();

int main(){                                    // int main 3 lines in 200+ lines of code lol

    system("cls");
    menu();
    return 0;
}

void menu() {
    std::string text;
    std::string dtext;
    std::string password;
    system("cls");
    char input = 0;
    ascii(1);
    std::cin >> input;
    input = toupper(input);
    switch (input) {
    case 'E':
        ascii(2);
        enc();
        break;
    case 'D':
        ascii(3);
        dec();
        break;
    case 'H':
        help();
        break;
    case 'X':
        system("exit");
        break;
    default:
        menu();
        break;
    }

}





void help() {
    ascii(4);
}




void ascii(int num) {
    switch (num) {
    case 1:
        system("cls");
        std::cout << R"(
                                                
     _____ ____  _____                    _____ 
    |__   |    \|  |  |   ___ ___ _ _ ___|_   _|
    |   __|  |  |  |  |  |  _|  _| | | . | | |  
    |_____|____/ \___/   |___|_| |_  |  _| |_|  
                                 |___|_|
    
    [ [E] Encrypt ]
    [ [D] Decrypt ]
    [ [H] Help    ]
    [ [X] Exit    ]
    )" << '\n';
        std::cout << "  Pick whatever you want: ";
        break;
    case 2:
        system("cls");
        std::cout << R"(
___________                                   __   
\_   _____/ ____   ___________ ___.__._______/  |_ 
 |    __)_ /    \_/ ___\_  __ <   |  |\____ \   __\
 |        \   |  \  \___|  | \/\___  ||  |_> >  |  
/_______  /___|  /\___  >__|   / ____||   __/|__|  
        \/     \/     \/       \/     |__|         
    )" << '\n';
        break;
    case 3:
        system("cls");
        std::cout << R"(
    .___                                  __   
  __| _/____   ___________ ___.__._______/  |_ 
 / __ |/ __ \_/ ___\_  __ <   |  |\____ \   __\
/ /_/ \  ___/\  \___|  | \/\___  ||  |_> >  |  
\____ |\___  >\___  >__|   / ____||   __/|__|  
     \/    \/     \/       \/     |__|         
    )" << '\n';
        break;
    case 4:
        system("cls");
        std::cout << R"(
   ______                   
 .' ___  |  .-.      .-.    
/ .'   \_|__| |__  __| |__  
| |      |__   __||__   __| 
\ `.___.'\  | |      | |    
 `.____ .'  '-'      '-'    
                            
    )" << "\n\n\n\n\n" << " Help to do what?\n Seems like this app can be used by a toddler or something\n\n\n This is a little program to encrypt and decrypt text written in C++\n I know it sucks...\n Made by Zdvonix\n Visit zdvonix.github.io or do whatever you want with this piece of crap :)\n\n\n\n\n";
        waitenter();
    }
}