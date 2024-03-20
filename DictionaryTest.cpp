// --------------------------------------------------------------
// Nicolas Corfmat
// CruzID: ncorfmat
// Assignment: pa8
// --------------------------------------------------------------

#include <iostream>
#include <string>
#include <stdexcept>

#include "Dictionary.h"

using namespace std;

int main() {

    string S[] = { // words to insert
        "truck",
        "building",
        "construction",
        "taxes",
        "federal",
        "fountain",
        "supposed",
        "tree",
        "giant",
        "cook",
        "sprint",
        "leap",
        "cabbage",
        "eat",
        "swamp",
        "quiet",
        "quail",
        "archery",
        "teapot",
        "melon",
        "market",
        "triumph",
        "nectar",
        "xylophone",
        "yacht",
        "millionaire",
        "helicopter",
        "deer",
        "elephant",
        "forest",
        "treaure",
        "jungle",
        "cobra",
        "canyon",
        "glacier",
        "volcano",
        "island"
    };
    string T[] = { // words to delete
        "elephant",
        "yacht",
        "jungle",
        "triumph",
        "quiet",
        "quail",
        "melon",
        "market",
        "canyon",
        "volcano",
        "teapot",
        "deer",
        "millionaire"
    };

    Dictionary A;
    Dictionary B;

    cout << endl;

    for (int i = 0; i < 35; i++) {
        A.setValue(S[i], i + 1);
    }

    B = A;

    B.setValue("glacier", 53);
    B.setValue("market", 284);
    B.setValue("eat", 189);
    B.setValue("forest", 174);
    B.setValue("tree", 533);

    Dictionary C = B;

    cout << "A.size() = " << A.size() << endl << A << endl;
    cout << "B.size() = " << B.size() << endl << B << endl;
    cout << "C.size() = " << C.size() << endl << C << endl;

    cout << "Copy constructor creates identical trees: " << endl;
    cout << ((C.pre_string() == B.pre_string()) ? "true" : "false") << endl;
    cout << endl;

    cout << "A == B is " << (A == B ? "true" : "false") << endl;
    cout << "B == C is " << (B == C ? "true" : "false") << endl;
    cout << "C == A is " << (C == A ? "true" : "false") << endl << endl;

    B = A;
    C = A;

    cout << "A == A is " << (A == A ? "true" : "false") << endl;
    cout << "A == B is " << (A == B ? "true" : "false") << endl;
    cout << "A == C is " << (A == C ? "true" : "false") << endl << endl;

    cout << "A.getValue(\"archery\") = " << A.getValue("archery") << endl;
    A.getValue("archery") += 294;
    cout << "A.getValue(\"archery\") = " << A.getValue("archery") << endl << endl;

    cout << "A.size() = " << A.size() << endl << A << endl;
    cout << "A pre-order: " << endl << A.pre_string() << endl;

    for (int i = 0; i < 7; i++) {
        A.remove(T[i]);
    }

    cout << "A.size() = " << A.size() << endl << A << endl;
    cout << "A pre-order: " << endl << A.pre_string() << endl;

    cout << "Forward iteration on A, changing values:" << endl;
    for (A.begin(); A.hasCurrent(); A.next()) {
        cout << "(" + A.currentKey() + ", " << A.currentVal() << ") ";
        A.currentVal()++;
        cout << "(" + A.currentKey() + ", " << A.currentVal() << ")\n";
    }
    cout << endl;

    cout << "Forward iteration on B, changing values:" << endl;
    for (B.begin(); B.hasCurrent(); B.next()) {
        cout << "(" + B.currentKey() + ", " << B.currentVal() << ") ";
        B.currentVal()++;
        cout << "(" + B.currentKey() + ", " << B.currentVal() << ")\n";
    }
    cout << endl;

    cout << "Reverse iteration on C, changing values" << endl;
    for (C.end(); C.hasCurrent(); C.prev()) {
        cout << "(" + C.currentKey() + ", " << C.currentVal() << ") ";
        C.currentVal()++;
        cout << "(" + C.currentKey() + ", " << C.currentVal() << ")\n";
    }
    cout << endl;

    cout << "Test pre-condition errors:" << endl;
    try {
        A.getValue("speedboat");
    }
    catch (logic_error& e) {
        cout << e.what() << endl;
        cout << "Continuing without interruption" << endl;
    }
    try {
        A.remove("gecko");
    }
    catch (logic_error& e) {
        cout << e.what() << endl;
        cout << "Continuing without interruption" << endl;
    }
    try {
        A.currentKey();
    }
    catch (logic_error& e) {
        cout << e.what() << endl;
        cout << "Continuing without interruption" << endl;
    }
    try {
        A.currentVal();
    }
    catch (logic_error& e) {
        cout << e.what() << endl;
        cout << "Continuing without interruption" << endl;
    }
    try {
        A.next();
    }
    catch (logic_error& e) {
        cout << e.what() << endl;
        cout << "Continuing without interruption" << endl;
    }
    try {
        A.prev();
    }
    catch (logic_error& e) {
        cout << e.what() << endl;
        cout << "Continuing without interruption" << endl;
    }
    try {
        B.getValue("squirrel");
    }
    catch (logic_error& e) {
        cout << e.what() << endl;
        cout << "Continuing without interruption" << endl;
    }
    try {
        B.remove("potato");
    }
    catch (logic_error& e) {
        cout << e.what() << endl;
        cout << "Continuing without interruption" << endl;
    }
    try {
        B.currentKey();
    }
    catch (logic_error& e) {
        cout << e.what() << endl;
        cout << "Continuing without interruption" << endl;
    }
    try {
        B.currentVal();
    }
    catch (logic_error& e) {
        cout << e.what() << endl;
        cout << "Continuing without interruption" << endl;
    }
    try {
        B.next();
    }
    catch (logic_error& e) {
        cout << e.what() << endl;
        cout << "Continuing without interruption" << endl;
    }
    try {
        B.prev();
    }
    catch (logic_error& e) {
        cout << e.what() << endl;
        cout << "Continuing without interruption" << endl;
    }

    cout << endl;

    return (EXIT_SUCCESS);
}


