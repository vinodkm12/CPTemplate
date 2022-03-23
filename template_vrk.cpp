#include <bits/stdc++.h>
using namespace std;
//Utilities

//1. Segment Tree
template <typename SEG_TYPE>
class Segtree {
    public:
        SEG_TYPE op(SEG_TYPE a, SEG_TYPE b) {
            return a+b;
        }
        SEG_TYPE id = 0;
        vector<SEG_TYPE> tree;
        int N; 
        void load(vector<int> &arr) {
            N = 1;
            while (N < arr.size()) {
                N <<= 1;
            }
            N = 2*N - 1;
            vector<int> temp(N, id);
            tree = temp;
            for (int i = 0; i < arr.size(); i++) {
                tree[i] = arr[i];
            }
            for (int i = N/2 + 1; i < N; i++) {
                tree[i] = op(tree[N-1-((N-1-i) * 2 + 1)], tree[N-1-((N-1-i) * 2 + 2)]);
            }
        }
        void print() {
            for (int i = 0; i < (N-1); i++) {
                cout << tree[i] << " ";
            }
            cout << tree[N-1] << "\n";
        }
        void update(int index, SEG_TYPE val) {
            int startIndex = index;
            while (index < (N-1)) {
                if (index == startIndex)
                    tree[index] = val;
                else
                    tree[index] = op(tree[N-1-((N-1-index) * 2 + 1)], tree[N-1-((N-1-index) * 2 + 2)]);
                index = N-1-(N-1-index - 1)/2;
            }
            tree[index] = op(tree[N-1-((N-1-index) * 2 + 1)], tree[N-1-((N-1-index) * 2 + 2)]);
        } 
        SEG_TYPE query(int start, int end) {
            SEG_TYPE recurs = id;
            int index = 0;
            while (start != end) {
                if (start % 2 == 1) {
                    recurs = op( recurs, tree[index+start]);
                    start++;
                }
                if ((start != end) && (end % 2 == 0)) {
                    recurs = op(recurs, tree[index + end]);
                    end--;
                }
                if (start != end) {
                    index = N-1-(N-3-index)/2;
                    start = start/2;
                    end = end/2;
                }
            }
            recurs = op( recurs, tree[index + start]);
            return recurs;
        }  
};

//Sieve of Erathostenes
class PrimeSieve {
    public:
        vector<int> data;
        int capacity;
        PrimeSieve(int my_capacity) {
            capacity = my_capacity;
            vector<int> temp(capacity);
            data = temp;
            data[0] = -1;
            for (int i = 2; i <= capacity; i++) {
                if (data[i-1] != -1) {
                    for (int j = 2*i; j <=capacity; j += i ) {
                        data[i-1] = -1;
                    }
                }
            }
        }

        bool isPrime(int num) {
            if (data[num-1] != -1)
                return true;
            else
                return false;
        }

        map<int,int> factorize(int num) {
            map<int,int> ans;
            for (int i = 2; i <= min(num,capacity); i++) {
                if ((data[i-1] != -1) && (num % i == 0)) {
                    if (ans.find(i) == ans.end())
                        ans.insert({i, 0});
                    while ((num % i) == 0) {
                        num /= i;
                        ans[i]++;
                    }
                }
            }
            return ans;
        }
};

//3. String split
vector<string> str_split(string s, char c) {
    vector<string> ans;
    int index = 0,prevIndex = 0;
    while (index < s.size()) {
        if (s[index] == c) {
            if (index > 0) 
                ans.push_back(s.substr(prevIndex,index-prevIndex));
            while ((index < s.size()) && (s[index] == c))
                index++; 
            prevIndex = index;
        }
        else 
            index++;
    }
    if (prevIndex < s.size()) {
        ans.push_back(s.substr(prevIndex, index-prevIndex));
    }
    return ans;
}


//4. GCD and mod inverse
int gcd(int a, int b) {
    if (a >= b) {
        if ((a%b) == 0)
            return b;
        else
            return gcd(b, a%b);
    }
    else {
        return gcd(b,a);
    }
}
int modInverse(int a, int m) {

}


//5. Union find data structure
class UnionFind {
    public:
        vector<int> data;
        UnionFind(int capacity) {
            vector<int> data(capacity);
            for (int i = 0; i < capacity; i++) {
                data[i] = i;
            }
        }

        void merge(int index1, int index2) {
            data[index2] = data[index1];
        }

        int nComponents() {
            set<int> s;
            for (int i =0; i < data.size(); i++) {
                s.insert(data[i]);
            }
            return s.size();
        }

        set<int> components() {
            set<int> s;
            for (int i =0; i < data.size(); i++) {
                s.insert(data[i]);
            }
            return s;           
        }

        int getComponent(int index) {
            int next = data[index];
            while (next != data[next]) {
                next = data[next];
            }
            return next;
        }

        int getComponentCompress(int index) {
            int next = data[index];
            vector<int> sets;
            while (next != data[next]) {
                sets.push_back(next);
                next = data[next];
            }
            for (int i = 0; i < sets.size(); i++) {
                data[sets[i]] = next;
            }
            return next;
        }
};