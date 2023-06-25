#include <iostream>
#include <windows.h>

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

/* Inisialisasi */
User *userHeadInData = NULL;

Barang *head = NULL,
       *tail = NULL;

/* Function struktur data double linked list */
void addNode(string *data);

/* Function user karyawan */
void userManager();
void addUser(string name, string password, User **head), listUser(), ubahPasswordAdmin(), deleteUser();
User *searchUser(string query);

/* Function utama */
bool loginKaryawan(string username, string password);
bool loginAdmin(string username, string password);
void menuAdmin(), menuKaryawan();
void sortingBarang();
Barang *searchBarang(string query);
void addBarang(string nama, string harga, string stok), showBarang(), updateBarang(), deleteBarang();
void createSampleDataBarang();

/* Function tambahan */
void gotoxy(int x, int y);

int main()
{
    /* Membuat user default. admin dan 1 karyawan */
    addUser("admin", "123", &userHeadInData);
    addUser("faeruz", "123", &userHeadInData);
    // listUser(); <- buat testing

    /* membuat 10 data barang dimasukan ke node double linked list */
    createSampleDataBarang();

    string username, password;
    do
    {
        system("cls");
        cout << ">>> SELAMAT DATANG DI APLIKASI ADMIN TOKO MURAH JAYA <<<" << endl
             << endl;
        cout << ">>> Silahkan lakukan login terlebih dahulu <<<" << endl;
        cout << "----------------------------------------------" << endl;
        cout << ">>> Username : ";
        getline(cin, username);
        cout << ">>> Password : ";
        getline(cin, password);

        if (loginAdmin(username, password))
        {
            menuAdmin();
        }
        else if (loginKaryawan(username, password))
        {
            menuKaryawan();
        }
        else
        {
            cout << "Username atau Password-mu Salah." << endl;
        }

    } while (!loginAdmin(username, password) || !loginKaryawan(username, password));

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

void menuAdmin()
{
    int pilihan;
    string data[3];
    do
    {
        cout << ">>> SELAMAT DATANG ADMIN <<<" << endl;
        cout << "----------------------------" << endl;
        cout << "1. Menambahkan barang baru" << endl;
        cout << "2. Menampilkan barang" << endl;
        cout << "3. Mengubah barang" << endl;
        cout << "4. Menghapus barang" << endl;
        cout << "5. User Manager" << endl;
        cout << "6. Logout" << endl;
        cout << "----------------------------" << endl;

        cout << "Masukan pilihan : ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            cout << "Masukan data barang:" << endl;
            cout << "--------------------" << endl;
            cout << "Nama  : ";
            cin.ignore();
            getline(cin, data[0]);
            cout << "Harga : ";
            cin >> data[1];
            cout << "Stok  : ";
            cin >> data[2];
            addBarang(data[0], data[1], data[2]);
            break;
        case 2:
            showBarang();
            break;
        case 3:
            updateBarang();
            break;
        case 4:
            deleteBarang();
            break;
        case 5:
            userManager();
            break;
        case 6:
            cout << "Bye!." << endl;
            break;
        default:
            cout << "Menu tidak tersedia!" << endl;
        }
    } while (pilihan != 6 || pilihan == 5);
}

void menuKaryawan()
{
    cout << "Kamu karyawan" << endl;
}

void sortingBarang()
{
    /* masih belum dibagian sorting
       rencana bisa sorting sesuai abjad a-z ~ z-a ~ stok paling sedikit ~ stok paling banyak
    */
    Barang *barangBeforeSorted = head;
    while (barangBeforeSorted != NULL)
    {
        // code
    }
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

void addBarang(string nama, string harga, string stok)
{
    string data[3] = {nama, harga, stok};

    /* Cek barang duplicate. Jika iya, maka tambah quantity-nya saja */
    Barang *duplicate = searchBarang(nama);
    if (duplicate == NULL)
    {
        addNode(data);
    }
    else
    {
        int newStok = stoi(duplicate->data[2]) + stoi(data[2]);
        duplicate->data[2] = to_string(newStok);
    }
}

/* Membuat fungsi untuk membuat data barang default */
void createSampleDataBarang()
{
    addBarang("Indomie Soto", "3000", "30");
    addBarang("Minyak Goreng", "16000", "13");
    addBarang("Beras 1kg", "15000", "5");
    addBarang("Kecap Bango", "3000", "12");
    addBarang("Tepung Terigu", "11000", "17");
    addBarang("Telor 1kg", "29000", "15");
    addBarang("Indomie Goreng", "3500", "40");
    addBarang("Aqua Galon", "20000", "10");
    addBarang("Gas 3kg", "20000", "15");
    addBarang("Ladaku", "1000", "100");
}

void showBarang()
{
    Barang *print = new Barang;
    print = head;

    if (head != NULL)
    {
        cout << "Daftar Barang: " << endl
             << endl;
        while (print != NULL)
        {
            /* Kode show disesuaikan */
            cout << print->data[0] << " " << print->data[1] << " " << print->data[2] << endl;

            print = print->next;
        }
        cout << endl;
    }
    else
    {
        cout << "\nBarang masih kosong!" << endl
             << endl;
    }
}
void updateBarang()
{
    if (head == NULL)
    {
        cout << "Tidak ada barang dalam daftar." << endl;
        return;
    }

    string nama;
    cout << "Masukkan nama barang yang ingin diubah: ";
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
        cout << "Masukkan data baru untuk barang \"" << nama << "\":" << endl;
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
    // showBarang(); <- buat testing
}

void deleteBarang()
{
    if (head == NULL)
    {
        cout << "Tidak ada barang dalam daftar." << endl;
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

    // showBarang(); <- buat testing
}

void userManager()
{
    int pilihan;
    string name, password;
    do
    {
        system("cls");
        cout << ">>> User manager <<<" << endl;
        cout << "----------------------" << endl;
        cout << "1. Tambah User untuk Karyawan" << endl;
        cout << "2. Hapus User Karyawan" << endl;
        cout << "3. Ubah password admin" << endl;
        cout << "4. List User Karyawan" << endl;
        cout << "5. Kembali ke menu utama" << endl;
        cout << "----------------------" << endl;

        cout << "Masukan pilihan : ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            cout << "Masukan data karyawan:" << endl;
            cin.ignore();
            cout << "Username : ";
            getline(cin, name);
            cout << "Password : ";
            getline(cin, password);

            addUser(name, password, &userHeadInData); // pointer next belum jadi
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
            cout << "Menu tidak tersedia!" << endl;
            break;
        }

    } while (pilihan != 4 || pilihan == 5);
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

void addUser(string name, string password, User **head)
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
        return;
    }

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
}

void deleteUser()
{
    string query;
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
        }
    }
}

void ubahPasswordAdmin()
{
    string newPassword;
    cin.ignore();
    cout << "Masukan password baru : ";
    getline(cin, newPassword);

    User *admin = userHeadInData;
    admin->password = newPassword;
}

void listUser()
{
    User *current = userHeadInData;
    while (current != NULL)
    {
        // list user tampilan disesuaikan
        cout << current->name << " " << current->password << endl;

        current = current->next;
    }
}

void gotoxy(int x, int y)
{
    COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
