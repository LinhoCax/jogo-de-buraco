#include <iostream>
#include <string>

using namespace std;

enum Suit {
    HEART, SPADE, CLUB, DIAMOND
};

struct Card {
    int value;
    Suit suit;
};

struct Deck {
    int size;
    Card cards[14];
};

Suit strToSuit(string str) {
    if (str == "♥") return HEART;
    if (str == "♦") return DIAMOND;
    if (str == "♣") return CLUB;
    return SPADE;
}

string suitToStr(Suit suit) {
    if (suit == HEART) return "♥";
    if (suit == DIAMOND) return "♦";
    if (suit == CLUB) return "♣";
    return "♠";
}

int strToValue(string str) {
    if (str == "A") return 1;
    if (str == "J") return 11;
    if (str == "Q") return 12;
    if (str == "K") return 13;
    return stoi(str);
}

string valueToStr(int value) {
    if (value == 11) return "J";
    if (value == 12) return "Q";
    if (value == 13) return "K";
    if (value == 1 || value == 14) return "A";
    return to_string(value);
}

Card strToCard(string str) {
    Card card;
    string valueStr, suitStr;
    if (str[0] == '1') {
        valueStr = str.substr(0,2);
        suitStr = str.substr(2);
    }
    else {
        valueStr = str.substr(0,1);
        suitStr = str.substr(1);
    }
    card.value = strToValue(valueStr);
    card.suit = strToSuit(suitStr);
    return card;
}

string cardToStr(Card c) {
    return valueToStr(c.value) + suitToStr(c.suit);
}

void print_deck(Deck deck) {
    cout << "[ ";
    for(int i = 0; i < deck.size; i++) {
        cout << cardToStr(deck.cards[i]) << " ";
    }
    cout << "]";
}


Deck read_deck() {
    Deck deck;
    string str;
    cin >> str;
    cin >> str;
    deck.size = 0;
    while(str != "]") {
        Card card = strToCard(str);
        if (deck.size > 1 && card.value == 1) {
            card.value = 14;
        }
        deck.cards[deck.size] = card;
        deck.size++;
        cin >> str;
    }
    return deck;
}


bool check_deck(Deck deck, Card &joker, Card &replaced) {
    int count_jokers = 0;
    Card card, next;
    for(int i = 0; i < deck.size - 1; i++) {
        card = deck.cards[i];
        next = deck.cards[i+1];
        if (card.value == 2) {
            if (next.value != 3 || next.suit != card.suit) {
                count_jokers++;
                if (count_jokers > 1 || next.value == 1 || next.value == 14) {
                    return false;
                }
                joker = card;
                replaced.value = next.value - 1;
                replaced.suit = next.suit;
            }
        }
        else if (next.value != 2 && (card.value != next.value - 1 || card.suit != next.suit)) {
            return false;
        }
    }
    if (next.value == 2) {
        count_jokers++;
        if (count_jokers > 1) {
            return false;
        }
        joker = next;
        replaced.value = card.value + 1;
        replaced.suit = card.suit;
    }
    return true;
}

bool isValidCard(Card c) {
    return c.value >= 1 && c.value <= 14;
}


void check_cards() {
    Card joker{0, DIAMOND};
    Card replaced{0, DIAMOND};

    Deck deck = read_deck();
    cout << "Jogo ";
    print_deck(deck);

    if (check_deck(deck, joker, replaced)) {
        cout << " é válido";
        if (isValidCard(joker)) {
            cout << ", " << cardToStr(joker);
            cout << " no lugar de " << cardToStr(replaced);
        }
    }
    else {
        cout << " é inválido";
    }
    cout << endl;
}

int main() {
    int qty;
    cin >> qty;

    for(int i = 0; i < qty; i++) {
        check_cards();
    }
    return 0;
}
