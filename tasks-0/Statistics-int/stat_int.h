#pragma once
#include <cstddef>
#include <utility>

class StatisticsInt {
public:
    StatisticsInt(int value_ = 0);

    StatisticsInt(const StatisticsInt& init_obj);

    StatisticsInt(StatisticsInt&& init_obj);

    StatisticsInt& operator=(const StatisticsInt& assign_obj);

    StatisticsInt& operator=(StatisticsInt&& assign_obj);

    StatisticsInt& operator=(const int& int_value);

    ~StatisticsInt();

    operator int() const;

    friend bool operator<(const StatisticsInt& lhs, const StatisticsInt& rhs);
    friend bool operator>(const StatisticsInt& lhs, const StatisticsInt& rhs);
    friend bool operator<=(const StatisticsInt& lhs, const StatisticsInt& rhs);
    friend bool operator>=(const StatisticsInt& lhs, const StatisticsInt& rhs);
    friend bool operator==(const StatisticsInt& lhs, const StatisticsInt& rhs);
    friend bool operator!=(const StatisticsInt& lhs, const StatisticsInt& rhs);

    friend StatisticsInt operator+(const StatisticsInt& lhs, const StatisticsInt& rhs);
    friend StatisticsInt operator-(const StatisticsInt& lhs, const StatisticsInt& rhs);
    friend StatisticsInt operator*(const StatisticsInt& lhs, const StatisticsInt& rhs);
    friend StatisticsInt operator/(const StatisticsInt& lhs, const StatisticsInt& rhs);
    friend StatisticsInt operator%(const StatisticsInt& lhs, const StatisticsInt& rhs);
    friend StatisticsInt operator<<(const StatisticsInt& lhs, const StatisticsInt& rhs);
    friend StatisticsInt operator>>(const StatisticsInt& lhs, const StatisticsInt& rhs);
    friend StatisticsInt operator&(const StatisticsInt& lhs, const StatisticsInt& rhs);
    friend StatisticsInt operator|(const StatisticsInt& lhs, const StatisticsInt& rhs);
    friend StatisticsInt operator^(const StatisticsInt& lhs, const StatisticsInt& rhs);

    StatisticsInt& operator+=(const StatisticsInt& rhs);
    StatisticsInt& operator-=(const StatisticsInt& rhs);
    StatisticsInt& operator*=(const StatisticsInt& rhs);
    StatisticsInt& operator/=(const StatisticsInt& rhs);
    StatisticsInt& operator%=(const StatisticsInt& rhs);
    StatisticsInt& operator<<=(const StatisticsInt& rhs);
    StatisticsInt& operator>>=(const StatisticsInt& rhs);
    StatisticsInt& operator&=(const StatisticsInt& rhs);
    StatisticsInt& operator|=(const StatisticsInt& rhs);
    StatisticsInt& operator^=(const StatisticsInt& rhs);

    StatisticsInt& operator++();
    StatisticsInt operator++(int);
    StatisticsInt& operator--();
    StatisticsInt operator--(int);

    size_t GetOperationsCount() const {return *ops_count_;}
    size_t GetAssigningsCount() const {return *assign_count_;}
    size_t GetComparisonsCount() const {return *comp_count_;}
    size_t GetArithmeticsCount() const {return *arithm_count_;}
    size_t GetBinsCount() const {return *bin_count_;}

    // Class static methods
    static size_t GetGlobalOpsCount() {return global_ops_count_;}
    static size_t GetGlobalAssignCount() {return global_assign_count_;}
    static size_t GetGlobalArithmCount() {return global_arithm_count_;}
    static size_t GetGlobalCompCount() {return global_comp_count_;}
    static size_t GetGlobalBinCount() {return global_bin_count_;}

protected:
    int value_;

    size_t* ops_count_;
    size_t* assign_count_;
    size_t* comp_count_;
    size_t* arithm_count_;
    size_t* bin_count_;

    static size_t global_ops_count_;
    static size_t global_assign_count_;
    static size_t global_arithm_count_;
    static size_t global_comp_count_;
    static size_t global_bin_count_;

private:
    // Utility functions for blending counters
    void add_neighbours_counters(const StatisticsInt& robbed_obj);

    static void double_arithm_increment(const StatisticsInt& lhs, const StatisticsInt& rhs);
    void single_arithm_increment(const StatisticsInt& lhs);

    static void double_comp_increment(const StatisticsInt& lhs, const StatisticsInt& rhs);

    static void double_bin_increment(const StatisticsInt& lhs, const StatisticsInt& rhs);
    void single_bin_increment(const StatisticsInt& lhs);
};

bool operator<(const StatisticsInt& lhs, const StatisticsInt& rhs);