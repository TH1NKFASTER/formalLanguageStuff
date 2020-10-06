#include <iostream>
#include <set>
#include <map>
#include <queue>

using namespace std;

class Automat {
public:
    Automat() {
//      for (char c = 'a'; c <= 'z'; ++c) {
//        alphabet.insert(c);
//      }
    }

    void full_dka() {
      map<set<int>, int> new_numbers;
      new_numbers[{0}] = 0;
      map<pair<int, char>, set<int>> new_state_transition_function; // but set with one number
      set<int> new_final;
      int next = 1;
      queue<set<int>> q;
      q.push({0});
      while (!q.empty()) {
        auto top = q.front();
        q.pop();

        for (auto &t : top) {
          if (final.count(t)) {
            new_final.insert(new_numbers[top]);
            break;
          }
        }

        for (auto c : alphabet) {
          set<int> for_this_vertex_by_this_letter;
          for (auto &t : top) {
            if (state_transition_function.find({t, c}) != state_transition_function.end()) {
              for (auto &h : state_transition_function[{t, c}]) {
                for_this_vertex_by_this_letter.insert(h);
              }
            }
          }
          if (new_numbers.find(for_this_vertex_by_this_letter) == new_numbers.end()) {
            new_numbers[for_this_vertex_by_this_letter] = next;
            ++next;
            q.push(for_this_vertex_by_this_letter);
            new_state_transition_function[{new_numbers[top], c}] = {new_numbers[for_this_vertex_by_this_letter]};
          } else {
            new_state_transition_function[{new_numbers[top], c}] = {new_numbers[for_this_vertex_by_this_letter]};
          }
        }
      }
      vertex.clear();
      for (int i = 0; i < next; ++i) {
        vertex.insert(i);
      }
      final = new_final;
      state_transition_function = new_state_transition_function;
      begin = 0;
      for (auto &t : new_numbers) {
        cout << t.second << ": ";
        for (auto &h : t.first) {
          cout << h << " ";
        }
        cout << endl;
      }
    }


    void min_full_dka() {
      map<int, int> cur_class;
      for (auto &t : vertex) {
        if (final.count(t)) {
          cur_class[t] = 1;
        } else {
          cur_class[t] = 0;
        }
      }
    }

    void print() {
      cout << "final: ";
      for (auto &t : final) {
        if (final.count(t)) {
          cout << t << " ";
        }
      }
      cout << endl;
      for (auto &t : state_transition_function) {
        cout << "from: " << t.first.first << "   symbol: " << t.first.second << "   to: ";
        for (auto &h : t.second) {
          cout << h << " ";
        }
        cout << endl;
      }
    }

    set<char> alphabet = {'a', 'b'};
    set<int> vertex;
    set<int> final; // <= vertex
    int begin = 0; // default value
    map<pair<int, char>, set<int>> state_transition_function;
};


int main() {
  Automat x;
  x.vertex = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
  x.final = {0, 9};
  x.state_transition_function.insert({{{0, 'a'}, {1, 3}}});
  x.state_transition_function.insert({{{0, 'b'}, {2, 4}}});
  x.state_transition_function.insert({{{1, 'a'}, {0}}});
  x.state_transition_function.insert({{{2, 'b'}, {0}}});
  x.state_transition_function.insert({{{3, 'b'}, {5}}});
  x.state_transition_function.insert({{{4, 'a'}, {5}}});
  x.state_transition_function.insert({{{5, 'a'}, {6}}});
  x.state_transition_function.insert({{{5, 'b'}, {6}}});
  x.state_transition_function.insert({{{6, 'a'}, {7}}});
  x.state_transition_function.insert({{{6, 'b'}, {8, 9}}});
  x.state_transition_function.insert({{{7, 'b'}, {6}}});
  x.state_transition_function.insert({{{8, 'a'}, {6}}});
  x.state_transition_function.insert({{{9, 'a'}, {3, 10}}});
  x.state_transition_function.insert({{{9, 'b'}, {4, 11}}});
  x.state_transition_function.insert({{{10, 'a'}, {9}}});
  x.state_transition_function.insert({{{11, 'b'}, {9}}});


  x.full_dka();
  x.print();
}
