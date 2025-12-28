#pragma once

#include <iostream>
#include <string>

using namespace std;

const double moms = 0.25;

class Commodity {
    public: 
    Commodity (string name, long id, double price);
    const string &get_name() const;
    long get_id() const;

    double get_price() const;
    double get_price(double quantity) const;

    void set_price(double new_price);

    double get_price_with_sales_tax() const;
    double get_price_with_sales_tax(double quantity) const;
    
    private: string name; long id; double price;
};