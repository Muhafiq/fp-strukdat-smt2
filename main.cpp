#include <iostream>
#include <windows.h>
#include <conio.h>
#include <limits>

using namespace std;
/* Struct untuk user dengan single linked list */
struct User
{
    string name;
    string password;
    User *next;
};
/* Struct barang pake double linked list */
struct Barang
{
    string data[3];
    Barang *next;
    Barang *prev;
};
/* Struct untuk menyimpan data riwayat transaksi */
struct Transaksi
{
    string daftarBarang[100][3];
    string username;
    int totalHarga;
};

/* Inisialisasi */
User *userHeadInData = NULL;

Barang *head = NULL,
       *tail = NULL;

Transaksi daftarRiwayatTransaksi[100];
int nomorTransaksi = 0;

/* Function struktur data double linked list */
void addNode(string *data);

/* Function user karyawan */
void userManager();
void addUser(string name, string password, User **head, bool isMessageTrue), listUser(), ubahPasswordAdmin(), deleteUser();
User *searchUser(string query);

/* Function login */
bool loginKaryawan(string username, string password);
bool loginAdmin(string username, string password);
void menuAdmin(), menuKaryawan(string username);

/* Function untuk barang (double linked list) */
void sortingBarang(Barang *head, string method);
Barang *searchBarang(string query);
void addBarang(string nama, string harga, string stok, bool isMessageTrue), showBarang(bool isGetCh), updateBarang(), deleteBarang();
void createSampleDataBarang();

/* Function utama karyawan */
void createTransaksi(string username);
void riwayatTransaksi(string transaksi[][3], int totalHarga, string username, int jumlahData);
void showRiwayatTransaksi();

/* Function tambahan */
void gotoxy(int x, int y);

int main()
{
    /* Membuat user default. admin dan 1 karyawan */
    addUser("admin", "123", &userHeadInData, false);
    addUser("faeruz", "123", &userHeadInData, false);

    /* membuat 10 data barang dimasukan ke node double linked list */
    createSampleDataBarang();

login:
    string username, password;
    do
    {
        system("cls");
        cout << "-------------------------------------------" << endl;
        cout << "------->>> APLIKASI ADMIN TOKO <<<---------" << endl;
        cout << "-------------------------------------------" << endl;
        cout << ">>> Username : ";
        cin >> username;
        cout << ">>> Password : ";
        cin >> password;

        if (loginAdmin(username, password))
        {
            menuAdmin();
        }
        else if (loginKaryawan(username, password))
        {
            menuKaryawan(username);
        }
        else
        {
            cout << "Username atau Password-mu Salah." << endl << endl;
            cout << "Tekan enter untuk login kembali....";
            getch();
        }

    } while (!loginAdmin(username, password) || !loginKaryawan(username, password));

    goto login;
    return 0;
}

/* Function untuk menambah data ke node dipisah dengan function addBarang
   INI BUAT YANG BARANG (DOUBLE LINKED LIST)
*/
void addNode(string *data)
{
    Barang *newBarang = new Barang;
    newBarang->data[0] = data[0];
    newBarang->data[1] = data[1];
    newBarang->data[2] = data[2];

    newBarang->next = NULL;

    if (head == NULL || tail == NULL)
    {
        head = newBarang;
        head->next = NULL;
        head->prev = NULL;
        tail = head;
    }
    else
    {
        tail->next = newBarang;
        newBarang->prev = tail;
        tail = newBarang;
    }
}

/* Function untuk auth, untuk proses login admin dan karyawan */

bool loginAdmin(string username, string password)
{
    User *admin = userHeadInData;
    if (username == admin->name && password == admin->password)
    {
        return true;
    }
    return false;
}

bool loginKaryawan(string username, string password)
{
    User *current = userHeadInData;
    while (current != NULL)
    {
        if (username == current->name && password == current->password)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

/* Function untuk tampilan menu */
void menuAdmin()
{
    bool condition = true;
    int pilihan;
    string data[3];

    do
    {
    system("cls");
        cout << "-------------------------------------------" << endl;
        cout << "------->>> SELAMAT DATANG ADMIN <<<--------" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "|                                         |" << endl;
        cout << "|    1. Menambahkan barang baru           |" << endl;
        cout << "|    2. Menampilkan barang                |" << endl;
        cout << "|    3. Mengubah barang                   |" << endl;
        cout << "|    4. Menghapus barang                  |" << endl;
        cout << "|    5. User Manager                      |" << endl;
        cout << "|    6. Logout                            |" << endl;
        cout << "|                                         |" << endl;
        cout << "-------------------------------------------" << endl;

        cout << ">>> Masukan pilihan : ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            cout << "-----------------------" << endl;
            cout << "| Masukan data barang |" << endl;
            cout << "-----------------------" << endl;
            cout << ">>> Nama  : ";
            cin.ignore();
            getline(cin, data[0]);
            cout << ">>> Harga : ";
            cin >> data[1];
            cout << ">>> Stok  : ";
            cin >> data[2];
            addBarang(data[0], data[1], data[2], true);
            break;
        case 2:
            showBarang(true);
            break;
        case 3:
            updateBarang();
            break;
        case 4:
            deleteBarang();
            break;
        case 5:
            condition = false;
            userManager();
            break;
        case 6:
            condition = false;
            cout << "Bye!." << endl;
            break;
        default:
            cout << "------------------------" << endl;
            cout << "| Menu tidak tersedia! |" << endl;
            cout << "------------------------" << endl << endl;
            cout << "Tekan enter untuk kembali....";
            getch();
        }
    } while (condition);
}

void menuKaryawan(string username)
{
    int pilihan;
    // string data[][5]; 
    int jumlahData;

    do
    {
    system("cls");
    
        cout << "------------------------------------" << endl;
        cout << "|  Selamat datang " << username << "|" << endl;
        cout << "------------------------------------" << endl;
        cout << "|                                  |" << endl;
        cout << "|      1. Buat transaksi           |" << endl;
        cout << "|      2. Lihat riwayat transaksi  |" << endl;
        cout << "|      3. Logout                   |" << endl;
        cout << "|                                  |" << endl;
        cout << "------------------------------------" << endl;
        cout << ">>> Masukan pilihan : ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            createTransaksi(username);
            break;
        case 2:
            showRiwayatTransaksi();
            break;
        case 3:
            cout << "Bye." << endl;
            break;
        default:
            cout << "------------------------" << endl;
            cout << "| Menu tidak tersedia! |" << endl;
            cout << "------------------------" << endl << endl;
            cout << "Tekan enter untuk kembali....";
            getch();
        }
    } while (pilihan != 3);
}

/* Function sorting dan searching barang */

void swapData(Barang *node1, Barang *node2)
{
    string temp[3];
    temp[0] = node1->data[0];
    temp[1] = node1->data[1];
    temp[2] = node1->data[2];

    node1->data[0] = node2->data[0];
    node1->data[1] = node2->data[1];
    node1->data[2] = node2->data[2];

    node2->data[0] = temp[0];
    node2->data[1] = temp[1];
    node2->data[2] = temp[2];
}
/* Sorting pake bubble sort */
void sortingBarang(Barang *head, string method)
{
    if (head == NULL || head->next == NULL)
    {
        return;
    }

    bool swapped;
    Barang *current;
    Barang *last = NULL;

    do
    {
        swapped = false;
        current = head;

        while (current->next != last)
        {
            if (method == "ascending")
            {
                if (current->data[0] > current->next->data[0])
                {
                    swapData(current, current->next);
                    swapped = true;
                }
            }
            else if (method == "descending")
            {
                if (current->data[0] < current->next->data[0])
                {
                    swapData(current, current->next);
                    swapped = true;
                }
            }
            else if (method == "stok-kecil")
            {
                if (stoi(current->data[2]) > stoi(current->next->data[2]))
                {
                    swapData(current, current->next);
                    swapped = true;
                }
            }
            else if (method == "stok-besar")
            {
                if (stoi(current->data[2]) < stoi(current->next->data[2]))
                {
                    swapData(current, current->next);
                    swapped = true;
                }
            }

            current = current->next;
        }

        last = current;
    } while (swapped);
}

/* Search disesuaikan biar bisa dipake berulang-ulang
   dipake di addBarang, updateBarang, sama deleteBarang */
Barang *searchBarang(string query)
{
    if (head == NULL)
        return NULL;
    Barang *current = head;

    while (current != NULL)
    {
        if (current->data[0] == query)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/* Function operasi CRUD pada barang (double linked list) */
void addBarang(string nama, string harga, string stok, bool isMessageTrue)
{
    string data[3] = {nama, harga, stok};

    /* Cek barang duplicate. Jika iya, maka ubah harga dan tambah quantity-nya saja */
    Barang *duplicate = searchBarang(nama);
    if (duplicate == NULL)
    {
        addNode(data);
        if(isMessageTrue)
            cout << "Barang " << nama << " berhasil ditambahkan" << endl;
    }
    else
    {
        duplicate->data[1] = data[1];                           // ubah harga
        int newStok = stoi(duplicate->data[2]) + stoi(data[2]); // tambah stok
        duplicate->data[2] = to_string(newStok);

        if(isMessageTrue)
            cout << "Barang " << nama << " duplikat, hanya diubah harga dan stok saja!" << endl;
    }
    if(isMessageTrue)
        getch();
}

/* Membuat fungsi untuk membuat data barang default */
void createSampleDataBarang()
{
    string data[][3] = {
        {"Indomie Soto", "3000", "30"},
        {"Minyak Goreng", "16000", "13"},
        {"Beras 1kg", "15000", "5"},
        {"Kecap Bango", "3000", "12"},
        {"Tepung Terigu", "11000", "17"},
        {"Telor 1kg", "29000", "15"},
        {"Indomie Kari", "3500", "40"},
        {"Aqua Galon", "20000", "10"},
        {"Gas 5kg", "60000", "30"},
        {"Gas 3kg", "20000", "15"},
        {"Ladaku", "1000", "100"}};
    for (int i = 0; i < (sizeof(data) / sizeof(data[0])); i++)
    {
        addBarang(data[i][0], data[i][1], data[i][2], false);
    }
}

void showBarang(bool isGetCh)
{
    Barang *print = new Barang;
    print = head;

    if (head != NULL)
    {
        cout << "-------------------------------------------------" << endl;
        cout << "-------------->>> DAFTAR BARANG <<<--------------" << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "| NAMA BARANG\t |\tHARGA\t |   JUMLAH \t|"<< endl;
        cout << "-------------------------------------------------" << endl;
        while (print != NULL)
        {            
            cout <<  "| " << print->data[0] << "\t |\t" << print->data[1] << "\t |\t" << print->data[2] << "\t|"<< endl;
            print = print->next;
        }
        
        cout << "-------------------------------------------------" << endl;
    }
    else
    {
        cout << "\nBarang masih kosong!" << endl
             << endl;
    }
    if(isGetCh)
        getch();
}
void updateBarang()
{
    if (head == NULL)
    {
        cout << "Tidak ada barang dalam daftar." << endl;
        getch();
        return;
    }

    string nama;
    cout << "Masukan nama barang yang ingin diubah : ";
    cin.ignore();
    getline(cin, nama);

    Barang *barang = searchBarang(nama);

    if (barang == NULL)
    {
        cout << "Barang tidak ditemukan." << endl;
    }
    else
    {
        string dataUpdate[3];
        cout << "Masukan data baru untuk barang \"" << nama << "\":" << endl;
        cout << "Nama  : ";
        getline(cin, dataUpdate[0]);
        cout << "Harga : ";
        cin >> dataUpdate[1];
        cout << "Stok  : ";
        cin >> dataUpdate[2];

        barang->data[0] = dataUpdate[0];
        barang->data[1] = dataUpdate[1];
        barang->data[2] = dataUpdate[2];
        cout << "Data barang telah diperbarui." << endl
             << endl;
    }
    getch();
    // showBarang(); <- buat testing
}

void deleteBarang()
{
    if (head == NULL)
    {
        cout << "Tidak ada barang dalam daftar." << endl;
        getch();
        return;
    }
    string nama;
    cout << "Masukkan nama barang yang ingin dihapus: ";
    cin.ignore();
    getline(cin, nama);

    Barang *barang = searchBarang(nama);

    if (barang == NULL)
    {
        cout << "Barang tidak ditemukan." << endl;
    }
    else
    {
        if (barang == head)
        {
            head = head->next;
            if (head != NULL)
                head->prev = NULL;
            delete barang;
        }
        else if (barang == tail)
        {
            tail = tail->prev;
            tail->next = NULL;
            delete barang;
        }
        else
        {
            barang->prev->next = barang->next;
            barang->next->prev = barang->prev;
            delete barang;
        }

        cout << "Barang \"" << nama << "\" telah dihapus." << endl;
    }
    getch();
    // showBarang(); <- buat testing
}

/* Function untuk mengelola user (single linked list) */
void userManager()
{
    int pilihan;
    string name, password;
    do
    {
        system("cls");
        cout << "-------------------------------------------" << endl;
        cout << "------------->>> USER MANAGER <<<----------" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "|                                         |" << endl;
        cout << "|      1. Tambah User untuk Karyawan      |" << endl;
        cout << "|      2. Hapus User Karyawan             |" << endl;
        cout << "|      3. Ubah password admin             |" << endl;
        cout << "|      4. List User Karyawan              |" << endl;
        cout << "|      5. Kembali ke menu utama           |" << endl;
        cout << "|                                         |" << endl;
        cout << "-------------------------------------------" << endl;
        cout << ">>> Masukan pilihan : ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            cout << "-----------------------------------" << endl;
            cout << "--->>> Masukan data karyawan <<<---" << endl;
            cout << "-----------------------------------" << endl;
            cin.ignore();
            cout << ">>> Username : ";
            getline(cin, name);
            cout << ">>> Password : ";
            getline(cin, password);

            addUser(name, password, &userHeadInData, true);
            break;
        case 2:
            deleteUser();
            break;
        case 3:
            ubahPasswordAdmin();
            break;
        case 4:
            listUser();
            break;
        case 5:
            menuAdmin();
            break;
        default:
            cout << "------------------------" << endl;
            cout << "| Menu tidak tersedia! |" << endl;
            cout << "------------------------" << endl << endl;
            cout << "Tekan enter untuk kembali....";
            getch();
            break;
        }

    } while (pilihan != 5);
}

User *searchUser(string query)
{
    User *user = userHeadInData;
    while (user != NULL)
    {
        if (query == user->name)
        {
            return user;
        }
        user = user->next;
    }
    return NULL;
}

void addUser(string name, string password, User **head, bool isMessageTrue)
{
    User *user = new User;
    user->name = name;
    user->password = password;
    user->next = NULL;
    // cek user duplicate
    User *isDuplicate = searchUser(name);
    if (isDuplicate != NULL)
    {
        cout << "User sudah terdaftar, gunakan nama lain." << endl;
        getch();
        return;
    }
    // operasi penghapusan
    if (*head == NULL)
    {
        *head = user;
    }
    else
    {
        User *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = user;
    }
    if(isMessageTrue)
    {
        cout << "User " << name << " berhasil ditambahkan!" << endl;
        getch();
    }
}

void deleteUser()
{
    string query;

    listUser();

    cout << "Masukan nama user yang akan di hapus : ";
    cin.ignore();
    getline(cin, query);

    User *userToDelete = searchUser(query);

    if (userToDelete == NULL)
    {
        cout << "User " << query << " Tidak ditemukan" << endl;
    }
    else
    {
        if (userToDelete == userHeadInData)
        {
            cout << "WARNING!!! User admin tidak boleh dihapus!" << endl;

            /* Kode dibawah ini nonaktif, karena user admin ada pada urutan pertama dalam list
               dan user admin tidak boleh dihapus.
             */
            // userHeadInData = userToDelete->next;
            // delete userToDelete;
        }
        else if (userToDelete != userHeadInData)
        {
            /* Mencari data user dalam list yang urutannya sebelum data yang akan di delete */
            User *userBeforeDeletedUser = userHeadInData;
            while (userBeforeDeletedUser->next != userToDelete)
            {
                userBeforeDeletedUser = userBeforeDeletedUser->next;
            }
            userBeforeDeletedUser->next = userToDelete->next;
            delete userToDelete;
            
            cout << "User " << query << " berhasil dihapus " << endl;
        }
        getch();
    }
}

void ubahPasswordAdmin()
{
    User *admin = userHeadInData;
    string newPassword, oldPassword;
    cout << "-----------------------------------" << endl;
    cout << "---->>> UBAH PASSWORD ADMIN <<<----" << endl;
    cout << "-----------------------------------" << endl;
    cin.ignore();
    cout << "Masukan password sekarang : ";
    getline(cin, oldPassword);
    if (admin->password == oldPassword)
    {
        cout << "Masukan password baru : ";
        getline(cin, newPassword);

        admin->password = newPassword;

        cout << "Password admin berhasil diubah!" << endl;
    }
    else
    {
        cout << "Password salah!! Tidak bisa mengubah password baru!" << endl;
    }
    getch();
}

void listUser()
{
    User *current = userHeadInData;
    cout << "------------------------" << endl;
    cout << "| NAMA USER | PASSWORD |" << endl;
    cout << "------------------------" << endl;
    gotoxy(2,2);
    while (current != NULL)
    {
        // list user tampilan disesuaikan
        cout << "| " << current->name << "\t | " << current->password << "\t | " << endl;

        current = current->next;
    }
    cout << "------------------------" << endl;
    getch();
}

/* Function untuk karyawan */
void menuSorting(char input)
{
    switch(input)
    {
        case 'q':
            sortingBarang(head, "ascending");
            break;
        case 'w':
            sortingBarang(head, "descending");
            break;
        case 'e':
            sortingBarang(head, "stok-kecil");
            break;
        case 'r':
            sortingBarang(head, "stok-besar");
            break;
    }
}

void createTransaksi(string username)
{
    string query;
    int jumlah, totalHarga = 0;
    char input;
    string transaksi[100][3];
    int jumlahTransaksi = 0;

    do
    {
        system("cls");
        cin.ignore();
        showBarang(false);
        cout << "\nMasukan nama barang : ";
        getline(cin, query);
        cout << "\n";
        Barang *barang = searchBarang(query);
        if(barang == NULL)
        {
            cout << "Barang tidak ditemukan!" << endl;
        }
        else
        {
            cout << "--------------------------------Barang Ditemukan-------------------------------" << endl;
            cout << "Nama barang : " << barang->data[0] << endl;
            input_jumlah:
            cout << "Jumlah : ";
            cin >> jumlah;

            if(jumlah > stoi(barang->data[2]))
            {
                cout << "Stok tidak tersedia!" << endl;
                goto input_jumlah;
            }

            int total = jumlah * stoi(barang->data[1]);
            cout << "Total harga : " << total << endl;

            transaksi[jumlahTransaksi][0] = barang->data[0];
            transaksi[jumlahTransaksi][1] = to_string(jumlah);
            transaksi[jumlahTransaksi][2] = to_string(total);

            // kurangi stok denga jumlah barang yang diambil
            barang->data[2] = to_string(stoi(barang->data[2]) - jumlah);

            jumlahTransaksi++;
        }
        cout << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << "| q = sorting a-z | w = sorting z-a | e = sorting < stok | r = sorting > stok |" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << "|                |   t = selesai   | y = tambah barang lagi |                 |" << endl;
        cout << "-------------------------------------------------------------------------------" << endl;
        cout << "Input : ";
        input = getch();

        menuSorting(input);

    } while(input != 't');

    cout << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "| NAMA BARANG\t |\tHARGA\t |   JUMLAH \t|"<< endl;
    cout << "-------------------------------------------------" << endl;
    for (int j = 0; j < jumlahTransaksi; j++)
    {
        cout <<  "| " << transaksi[j][0] << "\t |\t" << transaksi[j][2] << "\t |\t" << transaksi[j][1] << "\t|"<< endl;
        totalHarga += stoi(transaksi[j][2]);
    }
    cout << "-------------------------------------------------" << endl;
    cout << "Total harga transaksi : Rp" << totalHarga << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Transaksi Selesai." << endl << endl;

    riwayatTransaksi(transaksi, totalHarga, username, jumlahTransaksi);

    cout << "Tekan enter untuk kembali....";
    getch();
}

void riwayatTransaksi(string transaksi[][3], int totalHarga, string username, int jumlahData)
{
    daftarRiwayatTransaksi[nomorTransaksi].totalHarga = totalHarga;
    daftarRiwayatTransaksi[nomorTransaksi].username = username;

    for (int x=0 ; x < jumlahData; x++)
    {
        for (int y=0 ; y < jumlahData; y++)
        {
            daftarRiwayatTransaksi[nomorTransaksi].daftarBarang[x][y] = transaksi[x][y];
        }
    }
    nomorTransaksi++;
}

void showRiwayatTransaksi()
{
    int index = nomorTransaksi;
    while(index > 0)
    {
        int jumlahBarang = sizeof(daftarRiwayatTransaksi[index].daftarBarang) / sizeof(daftarRiwayatTransaksi[index].daftarBarang[0]);
        for (int i = 0; i < jumlahBarang; i++)
        {
            cout << daftarRiwayatTransaksi[index].daftarBarang[i][0] << " " <<daftarRiwayatTransaksi[index].daftarBarang[i][1] << " " << daftarRiwayatTransaksi[index].daftarBarang[i][2] << endl;
            if(daftarRiwayatTransaksi[index].daftarBarang[i][0] == "")
                break;
        }
        cout << daftarRiwayatTransaksi[index].totalHarga << " " << daftarRiwayatTransaksi[index].username << endl;
        cout << "--------------------------------------------------------" << endl;
        index--;
    }
    getch();
}


/* Function untuk tampilan */
void gotoxy(int x, int y)
{
    COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
