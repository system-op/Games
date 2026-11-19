#include <iostream>
#include <string>
#include <random>
#include <vector>

std::vector<std::string> Default_list = {
        "монолит", "Саня","линукс","1000",
        "школа","егэ","программирование",
        "сестра","бумага","мачета", "киша"
    };
std::vector<std::string> list;

std::string word; //слово
bool Delete_words; //удалять ли слова
int X_Symbol; // количество скрываемых букв кроме одной
int Num_Game = 1; // номер игры 

int word_success =0; // кол-во отгаданных слов с первой попытки
int word_nosuccess =0; // номер игры 

int generate_int(int plimit, int mlimit) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(mlimit, plimit);
    //std::cout << "[number]: " << dist(gen) << '\n';
    return dist(gen);
}
int num_list() {
    int max_index = static_cast<int>(list.size() - 1);
    int number_lists = generate_int(max_index, 0);
    std::cout << "[numlist]: " << number_lists << '\n';
    return number_lists;
}

std::string charge_element_words(std::string words) {
    word = words; 

    int length_count = words.length() / 2; // полученние длины строки
    //if (X_Symbol >= length_count) {
    //    length_count = X_Symbol - 2;
    //}
    std::cout << "[length_count]: " << length_count << "\n";
    if (X_Symbol < length_count) { length_count = X_Symbol;} else { length_count -= 2;}
    std::cout << "[length_count]: " << length_count << "\n";
    
    int array[length_count]; // создание массива длиной строки

    for (int i = 0; i != length_count; i++) {
        array[i] = generate_int(length_count - 1, 0) * 2; 
    }

    Verify_Arrays: //переборка массива для проверки отсутствия обинавковых номеров
    for (int i = 0; i != length_count; ++i) {
        for (int j = 0; j < i; ++j) {
            if (array[i] == array[j]) {
                array[i] = generate_int(length_count - 1, 0) * 2; 
                //std::cout << "Regenerate array[" << i << "]" << "\n";
                goto Verify_Arrays;
            }
        }
        //std::cout << "array["<< i << "] = " << array[i] << "\n";
    }
    std::cout << "Regenerate seccess full" << "\n";
    
    // Заменяем 2 байта старой буквы на 2 байта русской "Х"
    for (int i = 0; i != length_count; ++i) {
       words.replace(array[i], 2, "Х");
    }
    
    std::cout << "[words]: " << word << '\n';
    std::cout << "[Edit_words]: " << words << '\n';
    return words;
}


int main() {
    setlocale(LC_ALL, "");

    std::string input;
    int INT_input;
    list = Default_list;

        // игровой цикл
        goto GSP;

        GSI: //инфорамция о игре
        std::cout << "\n" 
                  <<"Game Settings Info (GSI): \n"
                  << "Delet using word: " << 
                  ((Delete_words == true) ? "Yes" : "No") << "\n" 
                  << "Number X symbol: " << X_Symbol <<"\n" 
                  << "Game Instance: " << Num_Game  << "\n"
                  << "Word success: " << word_success  << "\n"
                  << "Word no success: " << word_nosuccess  << "\n"
                  << "\n"; 

        std::cin.ignore(10000, '\n');
        std::cin.get();
        goto Game;


        GSP:     // настройки правил игры
        std::cout << "\n";
        std::cout << "Game Settings Parametrs [GSP]\n";
        std::cout << "Delet usings word? (Y\\N): \n";
        std::cin >> input;
        Delete_words = (input == "N"|| input == "n") ? false : true;
            GSP_X:
            std::cout << "Number X symbol (number 1-14) (dafault - 2): \n";
            std::cin >> input;
            try {
                int temp = std::stoi(input);
                if (temp > 0 && temp < 15) {
                    X_Symbol = temp;
                    std::cout << "\n";
                    goto Game; } 
                
                else {  std::cout << "[GSP_X] Cin < 0 else Cin > 14. \n"
                        << "please, cin number 1-14.\n"; goto GSP_X; }

            } catch(...) {std::cout << "[GSP_X] Error, cin no number, please";
                          std::cout << "cin numbre.\n"; goto GSP_X;}
        std::cout << "\n";
        goto Game;
        //goto GSI;


        Game: // по сути сама игра
        Num_Game+=1;
        std::cout << "Game start! (Game instance: " << Num_Game << " )\n";
        int nl = num_list();
        std::string words = list[nl];
        charge_element_words(words);

        if (Delete_words == true) { list.erase(list.begin() + nl); }


        Check_word:
        std::cin >> input;
        if (word == input) {
            word_success += 1;
            if (list.empty()) {
                std::cout << "All word on list no exitsts! New game? (Game Instance save, N - exit, progres zero) (Y\\N)).\n";
                std::cin >> input;
                if (input == "Y" || input == "y") {
                    list = Default_list;
                    goto Game;
                } else { exit(0); }
            }
                
            Input_Menu: // выбр дествия
            std::cout << "\n" 
                        << "New Game? (Y\\N)\n" 
                        << "Show Game Info (GSI) (I)\n" 
                        << "Edit Game Parametrs (GSP) (P): ";
                        
            std::cin >> input;
            if (input == "N" || input == "n") { std::cout << "Goodbay! brother progmammest\n"; 
                exit(0);}
            if (input == "Y" || input == "y") {
                std::cout << "Okey!\n"; goto Game;}  
            if (input == "I" || input == "i") {
                goto GSI; }
            if (input == "P" || input == "p") {
                goto GSP; }
            std::cout << "FTF bro... :/\n";
            goto Input_Menu;
        }
        word_nosuccess += 1;
        goto Check_word;
    return 0;
}