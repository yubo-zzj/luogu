/*
写猪国杀，锻炼自己的代码能力，以及面向对象编程能力
*/
#include <bits/stdc++.h>
using namespace std;
queue<char> dui;
class _PIG_ {
  private:
    int HP = 4;
    int maxHP = 4;
    string card_in_hand;
    string status;
    bool near_dead() {
        return HP <= 0;
    }
    int peach_in_hand() {
        int res = 0;
        for (auto x : card_in_hand) {
            res += x == 'P';
        }
        return res;
    }
    void eat_peach() {
        string a;
        for (auto x : card_in_hand) {
            if (HP >= 1)
                break;
            if (x != 'P') {
                a.push_back(x);
            } else {
                HP++; 
            }
        }
        this->card_in_hand = a;
        return; 
    }
    void init_status() {
        cin >> this->status;
        return; 
    } 
    void init_card() {
        char ch; 
        for (int i = 1; i <= 4; ++i) {
            cin >> ch;
            this->card_in_hand += ch; 
        }
        return; 
    }

  public:
    void out_card_in_hand() {
        cout << card_in_hand << endl;
        return;
    }
    bool dead() {
        if (!near_dead())
            return false;
        else {
            if (HP + peach_in_hand() >= 1) {
                eat_peach();
                return false; 
            } else {
                return true; 
            }
        }
    }
    void init() {
        init_status();
        init_card();
        return; 
    }
};
int main() {
    
    return 0;
}