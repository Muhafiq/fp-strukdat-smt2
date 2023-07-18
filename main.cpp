#include <iostream>
#include <conio.h>
#include <ctime>

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
    string data[4];
    Barang *next;
    Barang *prev;
};
/* Struct untuk menyimpan data riwayat transaksi */
struct Transaksi
{
    string daftarBarang[100][3];
    string username;
    int totalHarga;
    string created_at;
};

/* Inisialisasi */
User *userHeadInData = NULL;

Barang *head = NULL,
       *tail = NULL;

Transaksi daftarRiwayatTransaksi[100];
int nomorTransaksi = 0;
int idBarang = -1;

/* Function struktur data double linked list */
void addNode(string *data);

/* Function user karyawan */
void userManager();
void addUser(string name, string password, User **head, bool isMessageTrue), listUser(bool isGetCh), ubahPasswordAdmin(), deleteUser();
User *searchUser(string query);

/* Function login */
bool loginKaryawan(string username, string password);
bool loginAdmin(string username, string password);
void menuAdmin(), menuKaryawan(string username);

/* Function untuk barang (double linked list) */
void sortingBarang(Barang *head, string method);
Barang *searchBarang(string query, string method);
void addBarang(string nama, string harga, string stok, bool isMessageTrue), showBarang(bool isGetCh), updateBarang(), deleteBarang();
void createSampleDataBarang();

/* Function utama karyawan */
void createTransaksi(string username);
void riwayatTransaksi(string transaksi[][4], int totalHarga, string username, int jumlahData);
void showRiwayatTransaksi();
void showBarangInTransaksi(string transaksi[][4], int jumlahTransaksi);

/* Function tambahan */
int isDup(string transaksi[][4], Barang *barang, int jumlahTransaksi);
string getTimeNow();
string toLowerCase(string data);
string createIdBarang();

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
        cout << "-------------------------------------------------" << endl;
        cout << "---------->>> APLIKASI ADMIN TOKO <<<------------" << endl;
        cout << "-------------------------------------------------" << endl;
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
    newBarang->data[0] = createIdBarang();
    newBarang->data[1] = data[0];
    newBarang->data[2] = data[1];
    newBarang->data[3] = data[2];

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

string createIdBarang()
{
    idBarang++;
    if(to_string(idBarang).length() == 1)
    {
        return "00" + to_string(idBarang);
    }
    else if(to_string(idBarang).length() == 2)
    {
        return "0" + to_string(idBarang);
    }
    else if(to_string(idBarang).length() == 3)
    {
        return to_string(idBarang);
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
        cout << "-------------------------------------------------" << endl;
        cout << "---------->>> SELAMAT DATANG ADMIN <<<-----------" << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "|                                               |" << endl;
        cout << "|    1. Menambahkan barang baru                 |" << endl;
        cout << "|    2. Menampilkan barang                      |" << endl;
        cout << "|    3. Mengubah barang                         |" << endl;
        cout << "|    4. Menghapus barang                        |" << endl;
        cout << "|    5. User Manager                            |" << endl;
        cout << "|    6. Logout                                  |" << endl;
        cout << "|                                               |" << endl;
        cout << "-------------------------------------------------" << endl;

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
            system("cls");
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
            cout << "------------------------" << endl;
            cout << "----->>> Bye!. <<<------" << endl;
            cout << "------------------------" << endl;
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
    
        cout << "-------------------------------------------------" << endl;
        cout << "|          Selamat datang " << username << "               |" << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "|                                               |" << endl;
        cout << "|      1. Buat transaksi                        |" << endl;
        cout << "|      2. Lihat riwayat transaksi               |" << endl;
        cout << "|      3. Logout                                |" << endl;
        cout << "|                                               |" << endl;
        cout << "-------------------------------------------------" << endl;
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
            cout << "------------------------" << endl;
            cout << "----->>> Bye!. <<<------" << endl;
            cout << "------------------------" << endl;
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
    string temp[4];
    temp[0] = node1->data[0];
    temp[1] = node1->data[1];
    temp[2] = node1->data[2];
    temp[3] = node1->data[3];

    node1->data[0] = node2->data[0];
    node1->data[1] = node2->data[1];
    node1->data[2] = node2->data[2];
    node1->data[3] = node2->data[3];

    node2->data[0] = temp[0];
    node2->data[1] = temp[1];
    node2->data[2] = temp[2];
    node2->data[3] = temp[3];
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
                if (current->data[1] > current->next->data[1])
                {
                    swapData(current, current->next);
                    swapped = true;
                }
            }
            else if (method == "descending")
            {
                if (current->data[1] < current->next->data[1])
                {
                    swapData(current, current->next);
                    swapped = true;
                }
            }
            else if (method == "stok-kecil")
            {
                if (stoi(current->data[3]) > stoi(current->next->data[3]))
                {
                    swapData(current, current->next);
                    swapped = true;
                }
            }
            else if (method == "stok-besar")
            {
                if (stoi(current->data[3]) < stoi(current->next->data[3]))
                {
                    swapData(current, current->next);
                    swapped = true;
                }
            }
            else if (method == "id")
            {
                if (stoi(current->data[0]) > stoi(current->next->data[0]))
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
Barang *searchBarang(string query, string method)
{
    if (head == NULL)
        return NULL;
    Barang *current = head;

    while (current != NULL)
    {
        if(method == "id")
        {
            if (toLowerCase(current->data[0]) == toLowerCase(query))
            {
                return current;
            }
        }
        else if(method == "name")
        {
            if (toLowerCase(current->data[1]) == toLowerCase(query))
            {
                return current;
            }
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
    Barang *duplicate = searchBarang(nama, "name");
    if (duplicate == NULL)
    {
        addNode(data);
        if(isMessageTrue)
            cout << "Barang " << nama << " berhasil ditambahkan" << endl;
    }
    else
    {
        duplicate->data[2] = data[1];                           // ubah harga
        int newStok = stoi(duplicate->data[3]) + stoi(data[2]); // tambah stok
        duplicate->data[3] = to_string(newStok);

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
        {"Gas 5 kilo", "60000", "30"},
        {"Gas 3 kilo", "20000", "15"},
        {"Mrica Ladaku", "1000", "100"}};
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
        cout << "---------------------------------------------------------" << endl;
        cout << "------------------>>> DAFTAR BARANG <<<------------------" << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << "| ID  | NAMA BARANG\t |\tHARGA\t |   JUMLAH \t|"<< endl;
        cout << "---------------------------------------------------------" << endl;
        while (print != NULL)
        {            
            cout <<  "| " << print->data[0] << " |\t" << print->data[1] << "\t |\t" << print->data[2] << "\t |\t" << print->data[3] << "\t|" << endl;
            print = print->next;
        }
        
        cout << "---------------------------------------------------------" << endl;
    }
    else
    {
        cout << "------------------------" << endl;
        cout << ">>Barang masih kosong!<<" << endl;
        cout << "------------------------" << endl
             << endl;
    }
    if(isGetCh)
        getch();
}

void updateBarang()
{
    if (head == NULL)
    {
        cout << "-------------------------" << endl;
        cout << "->>Barang masih kosong<<-" << endl;
        cout << "-------------------------" << endl;
        getch();
        return;
    }

    string id;
    system("cls");
    showBarang(false);
    cout << "Masukan id barang yang ingin diubah : ";
    cin.ignore();
    getline(cin, id);

    Barang *barang = searchBarang(id, "id");

    if (barang == NULL)
    {
        cout << "Barang tidak ditemukan." << endl;
    }
    else
    {
        string dataUpdate[3];
        cout << "Masukan data baru untuk barang \"" << barang->data[1] << "\"" << endl;
        cout << "Nama  : ";
        getline(cin, dataUpdate[0]);
        cout << "Harga : ";
        cin >> dataUpdate[1];
        cout << "Stok  : ";
        cin >> dataUpdate[2];

        barang->data[1] = dataUpdate[0];
        barang->data[2] = dataUpdate[1];
        barang->data[3] = dataUpdate[2];
        cout << "Data barang telah diperbarui." << endl
             << endl;
    }
    showBarang(true);
}

void deleteBarang()
{
    if (head == NULL)
    {
        cout << "-------------------------" << endl;
        cout << "->>Barang masih kosong<<-" << endl;
        cout << "-------------------------" << endl;
        getch();
        return;
    }
    string id;
    system("cls");
    showBarang(false);
    cout << "Masukkan id barang yang ingin dihapus: ";
    cin.ignore();
    getline(cin, id);

    Barang *barang = searchBarang(id, "id");
    string namaBarang = barang->data[1];
    if (barang == NULL)
    {
        cout << "Barang tidak ditemukan." << endl;
    }
    else
    {
        string namaBarang = barang->data[1];
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

        cout << "Barang \"" << namaBarang << "\" telah dihapus." << endl;
    }
    showBarang(true);
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
            listUser(true);
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

    listUser(false);

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
            cout << "\nWARNING!!! User admin tidak boleh dihapus!" << endl << endl;
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
            
            cout << "\nUser " << query << " berhasil dihapus " << endl;
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

void listUser(bool isGetCh)
{
    User *current = userHeadInData;
    cout << "--------------------------" << endl;
    cout << "| NAMA USER  \t | PASS  |" << endl;
    cout << "--------------------------" << endl;
    while (current != NULL)
    {
        // list user tampilan disesuaikan
        cout << "| " << current->name << " \t | " << current->password << "\t | " << endl;

        current = current->next;
    }
    cout << "--------------------------" << endl;
    if(isGetCh)
        getch();
}

/* Function untuk membuat transaksi dan riwayat transaksi */
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
        case 'u':
            sortingBarang(head, "id");
            break;
    }
}

void createTransaksi(string username)
{
    string query;
    int jumlah, totalHarga = 0;
    char input;
    string transaksi[100][4];
    int jumlahTransaksi = 0;

    do
    {
        system("cls");
        cin.ignore();
        showBarang(false);
        cout << "\nMasukan id barang : ";
        getline(cin, query);
        cout << "\n";
        Barang *barang = searchBarang(query, "id");
        if(barang == NULL)
        {
            cout << "Barang tidak ditemukan!" << endl;
        }
        else
        {
            cout << "-------------------------------------------------" << endl;
            cout << "<<<--------------Barang Ditemukan------------->>>" << endl;
            cout << "-------------------------------------------------" << endl;
            cout << ">>> Nama barang : " << barang->data[1] << endl;
            input_jumlah:
            cout << ">>> Jumlah : ";
            cin >> jumlah;

            if(jumlah > stoi(barang->data[3]))
            {
                cout << "Stok tidak tersedia!" << endl;
                goto input_jumlah;
            }

            int total = jumlah * stoi(barang->data[2]);
            int dup = isDup(transaksi, barang, jumlahTransaksi);

            if(dup != -1)
            {
                transaksi[dup][2] = to_string(stoi(transaksi[dup][2]) + jumlah);
                transaksi[dup][3] = to_string(stoi(transaksi[dup][3]) + total);
                cout << "Barang sudah ada di list, hanya ditambah jumlah barang dan harga." << endl;
            }
            else
            {
                transaksi[jumlahTransaksi][0] = barang->data[0];
                transaksi[jumlahTransaksi][1] = barang->data[1];
                transaksi[jumlahTransaksi][2] = to_string(jumlah);
                transaksi[jumlahTransaksi][3] = to_string(total);
                cout << "Total harga : " << total << endl;
                jumlahTransaksi++;
            }
            // kurangi stok dengan jumlah barang yang diambil
            barang->data[3] = to_string(stoi(barang->data[3]) - jumlah);

        }
        cout << endl;
        showBarangInTransaksi(transaksi, jumlahTransaksi);
        cout << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << "| q = sorting a-z | e = sorting < stok | u = sort by id |" << endl;
        cout << "| w = sorting z-a | r = sorting > stok |                |" << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << "|   t = selesai   |    apa saja = tambah barang lagi    |" << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << "Tekan keyboard...";
        input = getch();

        menuSorting(input);

    } while(input != 't');
    system("cls");
    cout << "Transaksi selesai, berikut datanya." << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "| ID  | NAMA BARANG\t |\tHARGA\t |   JUMLAH \t|"<< endl;
    cout << "---------------------------------------------------------" << endl;
    for (int j = 0; j < jumlahTransaksi; j++)
    {
        cout <<  "| " << transaksi[j][0] << " |\t" << transaksi[j][1] << "\t |\t" << transaksi[j][3] << "\t |\t" << transaksi[j][2] << "\t|" << endl;
        totalHarga += stoi(transaksi[j][3]);
    }
    cout << "---------------------------------------------------------" << endl;
    cout << "Total harga transaksi : Rp" << totalHarga << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "Transaksi Selesai." << endl << endl;

    riwayatTransaksi(transaksi, totalHarga, username, jumlahTransaksi);

    cout << "Tekan enter untuk kembali....";
    getch();
}

void riwayatTransaksi(string transaksi[][4], int totalHarga, string username, int jumlahData)
{
    daftarRiwayatTransaksi[nomorTransaksi].totalHarga = totalHarga;
    daftarRiwayatTransaksi[nomorTransaksi].username = username;
    daftarRiwayatTransaksi[nomorTransaksi].created_at = getTimeNow();
    for (int x=0 ; x <= jumlahData; x++)
    {
        for (int y=0 ; y < 4; y++)
        {
            daftarRiwayatTransaksi[nomorTransaksi].daftarBarang[x][y] = transaksi[x][y];
        }
    }
    nomorTransaksi++;
}

void showRiwayatTransaksi()
{
    int index = nomorTransaksi-1, jumlahBarang = 0;
    system("cls");
    cout << "---------------------------------------------------------" << endl;
    cout << "---------------->>> RIWAYAT TRANSAKSI <<<----------------" << endl;
    cout << "---------------------------------------------------------" << endl;
    while(index >= 0)
    {
        cout << "=========================================================" << endl;
        cout << "Nomor transaksi : " << index+1 << endl;
        cout << "---------------------------------------------------------" << endl;
        cout << "| ID  | NAMA BARANG\t |\tHARGA\t |   JUMLAH \t|"<< endl;
        cout << "---------------------------------------------------------" << endl;
        while(!daftarRiwayatTransaksi[index].daftarBarang[jumlahBarang][0].empty())
        {
            jumlahBarang++;
        }
        for (int i = 0; i < jumlahBarang; i++)
        {
            cout <<  "| " << daftarRiwayatTransaksi[index].daftarBarang[i][0] << " |\t" << daftarRiwayatTransaksi[index].daftarBarang[i][1] << "\t |\t" << daftarRiwayatTransaksi[index].daftarBarang[i][3] << "\t |\t" << daftarRiwayatTransaksi[index].daftarBarang[i][2] << "\t|" << endl;
        }
        cout << "---------------------------------------------------------" << endl;
        cout << "\nTotal harga : Rp" <<daftarRiwayatTransaksi[index].totalHarga << endl;
        cout << "Dibuat oleh " << daftarRiwayatTransaksi[index].username << ", pada " << daftarRiwayatTransaksi[index].created_at << endl;
        cout << "=========================================================" << endl;
        index--;
    }
    getch();
}

string getTimeNow()
{
    time_t now = time(nullptr);
    tm *date = localtime(&now);
    int year = date->tm_year + 1900; 
    int month = date->tm_mon + 1;     
    int day = date->tm_mday;          
    int hour = date->tm_hour;
    int minute = date->tm_min;
    int second = date->tm_sec;

    string timeNow = to_string(day) + "/" + to_string(month) + "/" + to_string(year) + "_" + to_string(hour) + ":" + to_string(minute) + ":" + to_string(second);
    return timeNow;
}

int isDup(string transaksi[][4], Barang *barang, int jumlahTransaksi)
{
    for(int i = 0; i <= jumlahTransaksi; i++)
    {
        if(barang->data[0] == transaksi[i][0])
        {
           return i;
        }
    }
    return -1;
}

void showBarangInTransaksi(string transaksi[][4], int jumlahTransaksi)
{
    if(jumlahTransaksi == 0)
        return;
    system("cls");
    cout << "---------------------------------------------------------" << endl;
    cout << "-------->>> Daftar barang yang sudah dipilih <<<---------" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "| ID  | NAMA BARANG\t |\tHARGA\t |   JUMLAH \t|"<< endl;
    cout << "---------------------------------------------------------" << endl;
    for (int i = 0; i < jumlahTransaksi; i++)
    {
        cout <<  "| " << transaksi[i][0] << " |\t" << transaksi[i][1] << "\t |\t" << transaksi[i][3] << "\t |\t" << transaksi[i][2] << "\t|" << endl;
    }
    cout << "---------------------------------------------------------" << endl;
}

string toLowerCase(string data) {
    for(int i=0;i<data.length();i++) {
        data[i] = tolower(data[i]);
    }
    return data;
}