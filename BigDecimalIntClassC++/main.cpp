#include <bits/stdc++.h>
using namespace std;

class BigDecimalInt{
private:
    string digits;
    bool negative = false;
    string addition(BigDecimalInt& x, bool flag){
        string s, s1 = digits, s2 = x.digits;
        reverse(s1.begin(), s1.end()); reverse(s2.begin(), s2.end());
        int carry = 0;
        for(int i = 0; i < min(s1.size(), s2.size()); i++){
            if((s1[i] - '0') + (s2[i] - '0') + carry > 9){
                s += to_string((s1[i] - '0') + (s2[i] - '0') + carry - 10);
                carry = 1;
            }else{
                s += to_string((s1[i] - '0') + (s2[i] - '0') + carry);
                carry = 0;
            }
        }
        if(s1.size() != s2.size()){
            for(int i = min(s1.size(), s2.size()); i < max(s1.size(), s2.size()); i++){
                if(s1.size() > s2.size()){
                    if(carry){
                        if(s1[i] - '0' + 1 > 9){
                            s += to_string(s1[i] - '0' + 1 - 10);
                            carry = 1;
                        }else{
                            s += to_string(s1[i] - '0' + 1);
                            carry = 0;
                        }
                    }else{
                        s += s1[i];
                    }
                }else{
                    if(carry){
                        if(s2[i] - '0' + 1 > 9){
                            s += to_string(s2[i] - '0' + 1 - 10);
                            carry = 1;
                        }else{
                            s += to_string(s2[i] - '0' + 1);
                            carry = 0;
                        }
                    }else{
                        s += s2[i];
                    }
                }
            }
        }
        if(carry){
            s += '1';
        }
        reverse(s.begin(), s.end());
        if(flag){
            s = "-" + s;
        }
        return s;
    }
    string subtraction(BigDecimalInt& x){
        string s, s1, s2;
        if(digits.size() > x.digits.size()){
            s1 = digits; s2 = x.digits;
        }else if(digits.size() < x.digits.size()){
            s1 = x.digits; s2 = digits;
        }else{
            bool flag = false;
            for(int i = 0; i < digits.size(); i++){
                if(digits[i] > x.digits[i]){
                    s1 = digits; s2 = x.digits;
                    flag = true;
                    break;
                }else if(digits[i] < x.digits[i]){
                    s1 = x.digits; s2 = digits;
                    flag = true;
                    break;
                }
            }
            if(!flag){
                s1 = digits; s2 = x.digits;
            }
        }
        reverse(s1.begin(), s1.end()); reverse(s2.begin(), s2.end());
        for(int i = 0; i < min(s1.size(), s2.size()); i++){
            if(s1[i] - '0' >= s2[i] - '0'){
                s += to_string((s1[i] - '0') - (s2[i] - '0'));
            }else{
                bool flag = false;
                int idx = i + 1;
                while(idx < s1.size()){
                    if(s1[idx] - '0' > 0){
                        s1[idx] = s1[idx] - '0' - 1 + '0';
                        s += to_string((s1[i] - '0') + 10 - (s2[i] - '0'));
                        flag = true;
                        break;
                    }
                }
                if(!flag){
                    s += "1";
                }
            }
        }
        if(s1.size() != s2.size()){
            for(int i = min(s1.size(), s2.size()); i < max(s1.size(), s2.size()); i++){
                s += s1[i];
            }
        }
        reverse(s.begin(), s.end());
        reverse(s2.begin(), s2.end());
        if(s2 != x.digits){
            s = "-" + s;
        }
        return s;
    }
public:
    BigDecimalInt(){
        digits.resize(0);
    }
    BigDecimalInt(const string& decStr){
        for(char i : decStr){
            if (i == '-'){
                negative = true;
            }else{
                digits += i;
            }
        }
    }
    BigDecimalInt(int decInt){
        string temp = to_string(decInt);
        for(char i : temp){
            if (i == '-'){
                negative = true;
            }else{
                digits += i;
            }
        }
    }
    BigDecimalInt operator+ (BigDecimalInt& x){
        if(!negative && !x.negative){
            BigDecimalInt temp(addition(x, false));
            return temp;
        }else if(negative && x.negative){
            BigDecimalInt temp(addition(x, true));
            return temp;
        }else if(!negative && x.negative){
            BigDecimalInt temp(subtraction(x));
            return temp;
        }else if(negative && !x.negative){
            swap(digits, x.digits);
            BigDecimalInt temp(subtraction(x));
            return temp;
        }
    }
    BigDecimalInt operator- (BigDecimalInt& x){
        if(!negative && !x.negative){
            BigDecimalInt temp(subtraction(x));
            return temp;
        }else if(negative && x.negative){
            BigDecimalInt temp(subtraction(x));
            if(stoi(digits) > stoi(x.digits)){
                temp.negative = true;
            }else{
                temp.negative = false;
            }
            return temp;
        }else if(!negative && x.negative){
            BigDecimalInt temp(addition(x, false));
            return temp;
        }else if(negative && !x.negative){
            BigDecimalInt temp(addition(x, true));
            return temp;
        }
    }
    BigDecimalInt operator= (BigDecimalInt& anotherDec){
        BigDecimalInt temp;
        temp.digits = anotherDec.digits;
        return temp;
    }
    int size(){
        return digits.size();
    }
    friend ostream& operator << (ostream& out, BigDecimalInt b);
};

ostream& operator << (ostream& out, BigDecimalInt b){
    if(b.negative){
        out << "-";
    }
    for(int i = 0; i < b.digits.size(); i++){
        out << b.digits[i];
    }
    return out;
}

int main() {
    //freopen("input.in", "r", stdin);
    cout << "Welcome to FCI Calculator\n----------------------------------------\n";
    while(true){
        cout << "1- Perform Addition\n2- Perform Subtraction\n3- Exit\n";
        int n; cin >> n;
        if(n == 1){
            cout << "Please input the two numbers\n";
            string x, y; cin >> x >> y;
            BigDecimalInt num1(x);
            cout << "num1 = " << num1 << endl;
            BigDecimalInt num2(y);
            cout << "num2 = " << num2 << endl;
            cout << "num1 + num2 = " << num1 + num2 << endl;
        }else if(n == 2){
            cout << "Please input the two numbers\n";
            string x, y; cin >> x >> y;
            BigDecimalInt num1(x);
            cout << "num1 = " << num1 << endl;
            BigDecimalInt num2(y);
            cout << "num2 = " << num2 << endl;
            cout << "num1 - num2 = " << num1 - num2 << endl;
        }else{
            cout << "Exiting now...";
            break;
        }
    }
}