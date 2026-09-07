#include <bits/stdc++.h>
using namespace std;

// linked list với data dạng Anh:Viet
struct Node {
    string eng, vie;
    Node* next;
};

// Tao nhanh 26 linked list tuong ung voi 26 chu cai, moi linked list se luu tru tu bat dau bang chu cai do
Node* table[26] = {nullptr};

// Bien char thanh ma ASCII de lam key chinh cho bang bam, theo dang int : linked list 
int idx(char c) {
    return tolower(c) - 'a';
}

Node* find(const string& eng) {
    Node* p = table[idx(eng[0])];
    while (p) {
        if (p->eng == eng) return p;
        p = p->next;
    }
    return nullptr;
}

bool addWord(const string& eng, const string& vie) {
    if (find(eng)) {
        cout << "Tu da ton tai\n";
        return false;
    }
    int i = idx(eng[0]);
    Node* n = new Node{eng, vie, table[i]};
    table[i] = n;
    return true;
}

void editWord(const string& eng, const string& vie) {
    Node* p = find(eng);
    if (!p) {
        cout << "Khong tim thay tu\n";
        return;
    }
    string prev_vie = p->vie;
    p->vie = vie;
    cout << "Da thay the "<<p->eng<<":"<<prev_vie<<" thanh "<<p->eng<<":"<<p->vie<<"\n";
}

void writeFile(const string& filename) {
    ofstream fout(filename);
    for (int i = 0; i < 26; i++) {
        Node* p = table[i];
        while (p) {
            fout << p->eng << " : " << p->vie << "\n";
            p = p->next;
        }
    }
    fout.close();
}

bool deleteWord(const string& eng) {
    if (eng.empty()) return false;
    int i = idx(eng[0]);
    Node* p = table[i];
    Node* prev = nullptr;
    while (p) {
        if (p->eng == eng) {
            if (prev) prev->next = p->next;
            else table[i] = p->next;
            delete p;
            cout << "Da xoa\n";
            return true;
        }
        prev = p;
        p = p->next;
    }
    cout << "Khong tim thay tu\n";
    return false;
}

void searchWord(const string& eng) {
    Node* p = find(eng);
    if (p) cout << p->eng << " : " << p->vie << "\n";
    else cout << "Khong tim thay tu\n";
}

void displayGroup(char c) {
    Node* p = table[idx(c)];
    if (!p) {
        cout << "Nhom rong\n";
        return;
    }
    while (p) {
        cout << p->eng << " : " << p->vie << "\n";
        p = p->next;
    }
}

void displayAll() {
    for (int i = 0; i < 26; i++) {
        Node* p = table[i];
        while (p) {
            cout << p->eng << " : " << p->vie << "\n";
            p = p->next;
        }
    }
}

bool parsePair(const string& line, string& eng, string& vie) {
    size_t pos = line.find(':');
    if (pos == string::npos) return false;
    eng = line.substr(0, pos);
    vie = line.substr(pos + 1);
    while (!eng.empty() && eng.back() == ' ') eng.pop_back();
    size_t start = vie.find_first_not_of(' ');
    vie = (start == string::npos) ? "" : vie.substr(start);
    return !eng.empty() && !vie.empty();
}

void readFile(const string& filename) {
    ifstream fin(filename);
    string line, eng, vie;
    int count = 0;
    while (getline(fin, line)) {
        if (parsePair(line, eng, vie)) {
            if (addWord(eng, vie)) count++;
        }
    }
    fin.close();
    cout << "Da nap " << count << " tu tu file\n";
}

int main() {
    int choice;
    string eng, vie;
    char c;
    // Sua ten cac file test neu can thiet o day
    string fileName = "testData_2.txt"; 
    
    readFile(fileName);
    do {
        cout << "\n========================Tu dien Anh Viet=======================\n";
        cout << " 1.Them\n 2.Tra cuu\n 3.Hien thi tu vung theo nhom\n 4.Hien thi tat ca\n 5.Xoa\n 6.Sua\n 0.Thoat\n";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                cout << "Vui long nhap dung dinh dang Anh:Viet\n";
                cout << "Nhap tu (Vi du book:sach): ";
                string line;
                getline(cin, line);
                if (parsePair(line, eng, vie)) {
                    if (addWord(eng, vie)){
                        writeFile(fileName); 
                        cout<<"Da them tu: "<<eng<<":"<<vie<<" vao tu dien!\n" ;
                    }
                }
                else cout << "Sai dinh dang\n";
                break;
            }
            case 2:
                cout << "Nhap tu can tra: "; cin >> eng;
                searchWord(eng);
                break;
            case 3:
                cout << "Nhap chu cai nhom: "; cin >> c;
                displayGroup(c);
                break;
            case 4:
                displayAll();
                break;
            case 5:
                cout << "Nhap tu can xoa: "; cin >> eng;
                if (deleteWord(eng)) { 
                    writeFile(fileName);
                }
                break;
            case 6: {
                cout << "Nhap tu can sua (Vi du book:sach): ";
                string line;
                getline(cin, line);
                if (parsePair(line, eng, vie)) {
                    if (find(eng)) { 
                        editWord(eng, vie);
                        writeFile(fileName);
                    } else {
                        cout << "Khong tim thay tu\n";
                    }
                }
                else cout << "Sai dinh dang\n";
                break;
            }
        }
    } while (choice != 0);
    return 0;
}