#include <iostream> // Input output
#include <ctime>
#include <time.h>
#include "encryptions/sha256.h"
#include <random>
#include <fstream>
#include <unistd.h>
#include <string>
#include <cstdlib>


using namespace std;

int fn, choosen_seats[30];
string choosen_bus, choosen_dest, price, username1, token, tokenized_token;
char ulang, pesan_kembali;;

void retry(){
    cout << "[*] Error, mengulang\n";
    sleep(1);
}

void green(string a){
    cout << "\033[1;32m" << a << "\033[0m\n";
}

void loginSuccess(){
    cout << "[*] You are logged in" << endl;
}

void successCreateAcc(){
    cout << "[*] Your account successfully created...!!" << endl;
}

void showMenu(){
    system("clear");
    cout << "[*] ---------------------------------- [*]\n";
    cout << "[*]      LET'S BOOK YOUR TICKET !!     [*]\n";
    cout << "[*]         BUS TICKETING SYSTEM       [*]\n";
    cout << "[*] ---------------------------------- [*]\n";
}

void proses_ticketing(int jml_seat){
    cout << "[*] ---------- Pesanan Anda -------------\n";
    cout << "[*] Bus: \033[1;32m" << choosen_bus << "\033[0m\n";
    cout << "[*] Tujuan: \033[1;32m" << choosen_dest << "\033[0m\n";
    cout << "[*] Tarif: \033[1;32m" << price << "\033[0m\n";
    for (int i = 0; i < jml_seat; i++){
        cout << "[*] Seat " << choosen_seats[i] << endl;
    }
    cout << "[*] Apakah Anda setuju?(y/t) ";
    cin >> ulang;
    if (tolower(ulang) == 't'){
        cout << "[*]\033[1;31m !!! Semua bus yang tersedia beserta trayeknya akan terhapus !!!\033[0m\n";
        cout << "[*] Apakah Anda yakin?(y/n) ";
        cin >> ulang;
    } else {
        ulang = 'n';
        
        // string token = username1_encrypted + choosen_bus + choosen_dest + price;

        // string token = 

        fstream ticket_id;
        ifstream ticket_id_IN;
        ofstream ticket_id_OUT;

        ticket_id_IN.open("TICKETING");
        ticket_id_OUT.open("TICKETING",ios::app);
        if(ticket_id_IN.is_open()){
            ticket_id_OUT << "Token: " << tokenized_token << "\n";
            ticket_id_OUT << "Bus: " << choosen_bus << "\n";
            ticket_id_OUT << "Tujuan: " << choosen_dest << "\n";
        }
        cout << "[*] Terimakasih atas pesanan Anda\n";
        cout << "[*] Ingin memesan kembali?(y/n) ";
        cin >> pesan_kembali;
        if (pesan_kembali == 'n'){
            cout << "Keluar program\n";
            sleep(3);
            exit(0);
        }
    }
}

void AvailBus(){
    int counter4,pilihan;
    int arrayAcak[9] = {0,1,2,3,4,5,6,7,8};
    string tersedia[9] = {
        "Harapan Jaya",
        "Gunung Harta",
        "Prima Jasa",
        "Bejeu",
        "ALS",
        "Efisiensi",
        "Sinar Jaya", 
        "Sumber Alam",
        "PO. Haryanto"
    };
    string tujuan[9] = {
        "Jogja-Jakarta",
        "Lampung-Purwokerto",
        "Jakarta-Bandung",
        "Jogja-Cilacap",
        "Cirebon-Surabaya",
        "Medan-Jakarta",
        "Pemalang-Semarang",
        "Malang-Jakarta",
        "Banten-Indramayu"
    };

    string harga[9] = {
        "Rp. 50.000",
        "Rp. 60.000",
        "Rp. 70.000",
        "Rp. 80.000",
        "Rp. 90.000",
        "Rp. 100.000",
        "Rp. 110.000",
        "Rp. 120.000",
        "Rp. 130.000",
    };

    fn = sizeof(arrayAcak) / sizeof(arrayAcak[0]);
    unsigned seed = 0;
    srand(time(0)); 
    for (int i = 0; i < fn; i++){
        int index = rand() % fn;
        string temp = tersedia[i];
        tersedia[i] = tersedia[index];
        tersedia[index] = temp;
    }

    // Untuk memilih sejumlah x kursi
    srand(time(0));
    int a = rand() % 500, tempVar;
    bool check;
    char check_yakin = 'Y';

    // Komputer bakal nyariin nilai acak dari 0 - 30
    while (!check){
        a = a / 2;
        if (a > 0 and a <= fn){
            tempVar = a;
            check = true;
        }
    }
    menu3:
    showMenu();
    loginSuccess();
    cout << "[No.] Bus Tersedia:\n";

    for (int i = 0; i < a; i++){
        cout << "[" << i+1 <<"] \033[1;32m" << tersedia[i] << "\033[0m - " << harga[i] << "\n" << "(" << tujuan[i] << ")\n" << "\n";
    }
    cout << "[*] ctrl+c untuk exit\n";
    cout << "[*] ---------------------------\n";
    cout << "[*] Pilih Nomor Bus: ";
    cin >> pilihan;
    if(pilihan<=a){
        choosen_bus = tersedia[pilihan-1];
        choosen_dest = tujuan[pilihan-1];
        price = harga[pilihan-1];
        cout << "[*] Sudah yakin?(Y/n) ";
        cin >> check_yakin;
        if (tolower(check_yakin) == 'n'){
            goto menu3;
        }
    } else {
        retry();
        goto menu3;
    }
}

void BusFunc(int arr[], int n){
    int AvailableBus[30];
    bool check = false;
    int counter2 = 0;
    unsigned seed = 0;
    srand(time(0)); 
    // Untuk mengacak kursi

    for (int i = 0; i < n; i++){
        int index = rand() % n;
        int temp = arr[i];
        arr[i] = arr[index];
        arr[index] = temp;
    }

    // Untuk memilih sejumlah x kursi
    srand(time(0));
    int a = rand() % 500, b;

    // Komputer bakal nyariin nilai acak dari 0 - 30
    while (!check){
        a = a / 2;
        if (a > 0 and a <= n){
            b = a;
            check = true;
        }
    }
    for (int i = 0; i < b; i++){
        AvailableBus[i] = arr[i];
    }

    menu2:
    showMenu();
    int seats, seatsSum, counter3 = 0, TempSeats[1000], kl;
    cout << "[*] Bus: \033[1;32m" << choosen_bus << "\033[0m\n";
    cout << "[*] Trayek: \033[1;32m" << choosen_dest << "\033[0m\n";
    cout << "[*] Tarif: \033[1;32m" << price << "\033[0m\n";
    cout << "[*] Kursi Tersedia:" << endl;
    cout << "[*] -----------------------------------------\n" << "[*] ";
    for (int i = 0; i <= b/2; i++){
        cout << AvailableBus[i] << " ";
    }
    cout << endl << "[*] ";
    for (int i = (b/2)+1; i < b; i++){
        cout << AvailableBus[i] << " ";
    }
    cout << "\n[*] -----------------------------------------";
    cout << "\n[*] Pilih sejumlah kursi. max (" << b << ") ";
    cin >> seatsSum;
    if (seatsSum <= b) {
        for (int i = 0, j; i < seatsSum; i++){
            cout << "[*] Kursi [" << i+1 << "] ";
            cin >> seats;
            choosen_seats[i] = seats;
            if (i > 0){
                if (seats == choosen_seats[i-1]){
                    cout << "[*] Tidak bisa memilih kursi yang sama..." << endl;
                    sleep(1);
                    system("clear");
                    goto menu2;
                }
            }
            for (j = 0; j < b; j++){
                // cout << seats << " " << AvailableBus[j] << endl;
                if (seats == AvailableBus[j]){
                    cout << "[*] OK\n";
                    counter3++;
                    break;
                } else if (seats != AvailableBus[j]){
                    counter3 = 0;
                }
            }
            if (counter3 == 0){
                cout << "[*] Kursi Tidak Tersedia...\n";
                sleep(2);
                goto menu2;
            }
        }
        // cout << "\n[*] Here's Your Choosen Seat/s:\n";
        // for (int i = 0; i < seatsSum; i++){
        //     cout << "[*] Seat-" << i+1 << ": " << TempSeats[i] << endl;
        // }
        proses_ticketing(seatsSum);
    } else {
        cout << "[*] You Are Exceeding Available Seats. Try Again...\n";
        sleep(1);
        goto menu2; 
    }
}

int main(int argc, char *argv[])
{   
    bool validate1, validate2;
    int counter = 0, busSeats[30] = 
    {
    1, 2, 3, 4, 5, 
    6, 7, 8, 9, 10, 
    11, 12, 13, 14, 15, 
    16, 17, 18, 19, 20, 
    21, 22, 23, 24, 25, 
    26, 27, 28, 29, 30
    },

    busSeatsLen = sizeof(busSeats) / sizeof(busSeats[0]), choose;

    string username, password, encryptedPassword;

    menu1:
    showMenu();
    cout << "[1] Login" << endl;
    cout << "[2] Register" << endl;
    cout << "[x] Exit" << endl;
    cout << "[*] Choose> ";
    cin >> choose;

    if (choose == 1){
        showMenu();
        cout << "[*] ------------[ Login ]------------- [*]\n";
        cout << "[*] ---------------------------------- [*]\n";
        cout << "[*] Username: ";
        cin >> username;
        username1 = username;
        token = sha256(username1) + sha256(choosen_bus) + sha256(choosen_dest);
        tokenized_token = sha256(token);
        cout << "[*] Password: ";
        cin >> password;
        encryptedPassword = sha256(password);

        fstream file;
        ifstream filein;
        filein.open("Database");
        if(filein.is_open()){
            string word;
            file.open("Database");
            while (file >> word) {
                counter++; // counter = 1
                if (counter % 2 == 0){
                    if (word == encryptedPassword){
                        validate1 = true;
                    }
                } else {
                    if (word == username){
                        validate2 = true;
                    }
                }
            }
            filein.close();
        }
        if (validate1 == true and validate2 == true){
            // Date_and_Destination();
            AvailBus();
            BusFunc(busSeats, busSeatsLen);
        } else {
            cout << "[*] Try again, from start" << endl;
            sleep(2);
            goto menu1;
        }
    }

    else if (choose == 2) {
        menu4:
        showMenu();
        cout << "[*] ---------[ Registration ]--------- [*]\n";
        cout << "[*] ---------------------------------- [*]\n";
        cout << "[*] Username: ";
        cin >> username;
        
        fstream usernameCheck;
        ifstream usernameCheckIn;

        usernameCheckIn.open("Database");
        if(usernameCheckIn.is_open()){
            string raw_username;
            usernameCheck.open("Database");
            while(usernameCheck >> raw_username){
                if (raw_username == username){
                    cout << "[*] Username sudah ada sebelumnya...\n";
                    sleep(2);
                    goto menu4;
                }
            }
            usernameCheckIn.close();
        }

        cout << "[*] Password: ";
        cin >> password;
        
        if (password.length() > 8 and password.length() < 100){
            encryptedPassword = sha256(password);
        } else {
            cout << "[*] Password harus lebih dari 8 huruf\n";
            sleep(2);
            goto menu4;
        }

        // Password = 1234
        // Tambahan = "AB"
        // Tambahan(Password) = A1234B
        // Output = Tambahan(Password)
        // Output = A1234B
        
        ofstream fileout;
        ifstream filein;

        // File in = Read
        // File out = Write

        filein.open("Database");
        fileout.open("Database",ios::app); // app = append = menambahkan ke dalam file
        if(filein.is_open()){
            fileout<< username << "\n";
            fileout<< encryptedPassword << "\n";
            fileout.close();
        }
        successCreateAcc();
        sleep(2);
        goto menu1;
    }
    else {
        return 0;
    }
    if (tolower(pesan_kembali) == 'y'){
        goto menu1;
    }
    return 0;
}