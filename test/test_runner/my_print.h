//
// Created by General on 30.07.2020.
//
#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

template<class T>
ostream& operator << (ostream& os, const set<T>& s);
template <class T>
ostream& operator << (ostream& os, const vector<T>& s);
template<class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m);

template<class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& item : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << item;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template<class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}
