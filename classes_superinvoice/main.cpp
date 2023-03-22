#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Item {
public:
    Item(const string& name, double price, char tax, int quantity) :
        name(name), price(price), tax(tax), quantity(quantity) {}

    double get_net_price() const {
        return price * quantity;
    }

    double get_tax_amount() const {
        switch (tax) {
            case 'A':
                return 0.23 * get_net_price();
            case 'B':
                return 0.08 * get_net_price();
            case 'C':
                return 0.0;
            default:
                return 0.0;
        }
    }

    double get_total_price() const {
        return get_net_price() + get_tax_amount();
    }

    friend ostream& operator<<(ostream& os, const Item& item) {
        os << setw(16) << left << item.name << "| "
           << fixed << setprecision(2)
           << setw(4) << item.price << "  " << item.tax << " |"
           << setw(5) << item.quantity << " |"
           << setw(6) << item.get_net_price() << " |"
           << setw(6) << item.get_total_price();
        return os;
    }

private:
    string name;
    double price;
    char tax;
    int quantity;
};

class Invoice {
public:
    Invoice(long long seller_nip, long long buyer_nip) :
        seller_nip(seller_nip), buyer_nip(buyer_nip) {}

    void add_item(const Item& item) {
        items.push_back(item);
    }

    double get_total_net_price() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += item.get_net_price();
        }
        return total;
    }

    double get_total_tax_amount() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += item.get_tax_amount();
        }
        return total;
    }

    double get_total_price() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += item.get_total_price();
        }
        return total;
    }

    friend ostream& operator<<(ostream& os, const Invoice& invoice) {
        os << "------------------VAT invoice------------------" << endl;
        os << "===============================================" << endl;
        os << "Seller: " << setw(10) << setfill('0') << invoice.seller_nip
           << "      Buyer: " << setw(10) << setfill('0') << invoice.buyer_nip << endl;
        os << endl;
        os << setw(16) << left << "Name" << "| c.j. VAT il. net   total" << endl;
        os << string(51, '-') << endl;
        for (const auto& item : invoice.items) {
            os << item << endl;
        }
        os << string(51, '-') << endl;
        os << setw(51) << left << "TOTAL" << "|"
           << setw(6) << invoice.get_total_net_price() << " |"
           << setw(6) << invoice.get_total_tax_amount() << " |"
           << setw(6) << invoice.get_total_price();
        return os;
    }

private:
    long long seller_nip;
    long long buyer_nip;
    vector<Item> items;
};

int main()
{
    Invoice inv(7770003699, 123456789);
    inv.add_item(Item("M3 screw", 0.37, 'A', 100));
    inv.add_item(Item("2 mm drill", 2.54, 'B', 2));
    cout << inv << endl;
}
