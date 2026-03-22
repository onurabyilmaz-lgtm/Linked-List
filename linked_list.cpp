#include <iostream>
#include <limits>
#include <string>

using namespace std;


// ============================================================
//  Node — özel iç yapı (LinkedList dışına sızmaz)
// ============================================================
template <typename T>
class LinkedList {
private:

    struct Node {
        T     data;
        Node* next;
        Node(const T& val) : data(val), next(nullptr) {}
    };

    Node* head;
    Node* tail;   // O(1) ekleme için kuyruk işaretçisi


public:

    // --------------------------------------------------------
    //  Varsayılan kurucu
    // --------------------------------------------------------
    LinkedList() : head(nullptr), tail(nullptr) {}


    // --------------------------------------------------------
    //  Kopya kurucusu  (Rule of Three — 1/3)
    // --------------------------------------------------------
    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr) {
        Node* current = other.head;
        while (current != nullptr) {
            Add(current->data);
            current = current->next;
        }
    }


    // --------------------------------------------------------
    //  Atama operatörü  (Rule of Three — 2/3)
    // --------------------------------------------------------
    LinkedList& operator=(const LinkedList& other) {
        if (this == &other) return *this;   // öz atamayı engelle
        Clear();                             // mevcut listeyi temizle
        Node* current = other.head;
        while (current != nullptr) {
            Add(current->data);
            current = current->next;
        }
        return *this;
    }


    // --------------------------------------------------------
    //  Destructor  (Rule of Three — 3/3)
    // --------------------------------------------------------
    ~LinkedList() {
        Clear();
    }


    // --------------------------------------------------------
    //  Clear — tüm düğümleri sil, baş/kuyruk sıfırla
    // --------------------------------------------------------
    void Clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
    }


    // --------------------------------------------------------
    //  Add — O(1) ekleme (tail işaretçisi sayesinde)
    // --------------------------------------------------------
    void Add(const T& data) {
        Node* newNode = new Node(data);
        if (tail == nullptr) {          // liste boşsa
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail       = newNode;
        }
        cout << "'" << data << "' listeye eklendi." << endl;
    }


    // --------------------------------------------------------
    //  Delete — değeri bulup sil; bool döndür
    // --------------------------------------------------------
    bool Delete(const T& data) {
        if (head == nullptr) {
            cout << "Liste boş. Silme işlemi yapılamaz." << endl;
            return false;
        }

        // Baş düğüm eşleşiyor mu?
        if (head->data == data) {
            Node* temp = head;
            head = head->next;
            if (head == nullptr) tail = nullptr;   // liste boşaldı
            delete temp;
            cout << "'" << data << "' silindi." << endl;
            return true;
        }

        // Ortada / sonda ara
        Node* prev    = head;
        Node* current = head->next;
        while (current != nullptr) {
            if (current->data == data) {
                prev->next = current->next;
                if (current == tail) tail = prev;  // kuyruk güncelle
                delete current;
                cout << "'" << data << "' silindi." << endl;
                return true;
            }
            prev    = current;
            current = current->next;
        }

        cout << "'" << data << "' listede bulunamadı." << endl;
        return false;
    }


    // --------------------------------------------------------
    //  Search — değeri bul; bool döndür
    // --------------------------------------------------------
    bool Search(const T& data) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == data) {
                cout << "'" << data << "' listede bulundu." << endl;
                return true;
            }
            current = current->next;
        }
        cout << "'" << data << "' listede bulunamadı." << endl;
        return false;
    }


    // --------------------------------------------------------
    //  Print — listeyi konsola yaz
    // --------------------------------------------------------
    void Print() const {
        if (head == nullptr) {
            cout << "Liste boş." << endl;
            return;
        }
        cout << "Liste içeriği: ";
        Node* current = head;
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) cout << " -> ";
            current = current->next;
        }
        cout << " -> NULL" << endl;
    }


    // --------------------------------------------------------
    //  Size — eleman sayısını döndür
    // --------------------------------------------------------
    int Size() const {
        int count = 0;
        Node* current = head;
        while (current != nullptr) { ++count; current = current->next; }
        return count;
    }
};


// ============================================================
//  Menü
// ============================================================
void showMenu() {
    cout << "\n ===============By Onur================" << endl;
    cout << "    ~~ WELCOME to Linked List program ~~  " << endl;
    cout << " =============================================" << endl;
    cout << "    1. Ekle   2. Sil   3. Ara   4. Yazdır   5. Boyut   6. Çıkış" << endl;
    cout << " =============================================" << endl;
    cout << "Seçiminizi girin: ";
}


// ============================================================
//  main — int listesi (template sayesinde string veya double
//          ile de kolayca değiştirilebilir)
// ============================================================
int main() {
    LinkedList<int> myList;
    int choice, value;

    while (true) {
        showMenu();

        if (!(cin >> choice)) {
            cout << "Geçersiz giriş. Lütfen bir sayı girin." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Eklenecek değeri girin: ";
                if (cin >> value) myList.Add(value);
                else { cout << "Geçersiz değer." << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
                break;

            case 2:
                cout << "Silinecek değeri girin: ";
                if (cin >> value) myList.Delete(value);
                else { cout << "Geçersiz değer." << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
                break;

            case 3:
                cout << "Aranacak değeri girin: ";
                if (cin >> value) myList.Search(value);
                else { cout << "Geçersiz değer." << endl; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
                break;

            case 4:
                myList.Print();
                break;

            case 5:
                cout << "Liste boyutu: " << myList.Size() << endl;
                break;

            case 6:
                cout << "Programdan çıkılıyor. Hoşçakalın!" << endl;
                return 0;

            default:
                cout << "Geçersiz seçim. Lütfen 1 ile 6 arasında bir sayı girin." << endl;
        }
    }
}
