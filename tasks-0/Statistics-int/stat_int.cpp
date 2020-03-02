#include "stat_int.h"

#include <iostream>

// Initialize static protected members
size_t StatisticsInt::global_ops_count_ = 0;
size_t StatisticsInt::global_assign_count_ = 0;
size_t StatisticsInt::global_arithm_count_ = 0;
size_t StatisticsInt::global_comp_count_ = 0;
size_t StatisticsInt::global_bin_count_ = 0;

void StatisticsInt::add_neighbours_counters(const StatisticsInt& robbed_obj) {
    *ops_count_ += *robbed_obj.ops_count_;
    *assign_count_ += *robbed_obj.assign_count_;
    *comp_count_ += *robbed_obj.comp_count_;
    *arithm_count_ += *robbed_obj.arithm_count_;
    *bin_count_ += *robbed_obj.bin_count_;
}

// Counters updaters
void StatisticsInt::single_arithm_increment(const StatisticsInt& lhs) {
    ++StatisticsInt::global_arithm_count_;
    ++StatisticsInt::global_ops_count_;

    ++(*lhs.arithm_count_);
    ++(*lhs.ops_count_);
}

void StatisticsInt::double_arithm_increment(const StatisticsInt& lhs, const StatisticsInt& rhs) {
    ++StatisticsInt::global_arithm_count_;
    ++StatisticsInt::global_ops_count_;

    ++(*lhs.arithm_count_);
    ++(*rhs.arithm_count_);

    ++(*lhs.ops_count_);
    ++(*rhs.ops_count_);
}

void StatisticsInt::double_comp_increment(const StatisticsInt& lhs, const StatisticsInt& rhs) {
    ++StatisticsInt::global_comp_count_;
    ++StatisticsInt::global_ops_count_;

    ++(*lhs.comp_count_);
    ++(*rhs.comp_count_);

    ++(*lhs.ops_count_);
    ++(*rhs.ops_count_);
}

void StatisticsInt::single_bin_increment(const StatisticsInt& lhs) {
    ++StatisticsInt::global_bin_count_;
    ++StatisticsInt::global_ops_count_;

    ++(*bin_count_);
    ++(*ops_count_);

    ++(*lhs.bin_count_);
    ++(*lhs.ops_count_);
}

void StatisticsInt::double_bin_increment(const StatisticsInt& lhs, const StatisticsInt& rhs) {
    ++StatisticsInt::global_bin_count_;
    ++StatisticsInt::global_ops_count_;

    ++(*lhs.bin_count_);
    ++(*rhs.bin_count_);

    ++(*lhs.ops_count_);
    ++(*rhs.ops_count_);
}

// Constructors, destructor and assign operators
StatisticsInt::StatisticsInt(int value_) :
    value_(value_),
    ops_count_(new size_t(0)),
    assign_count_(new size_t(0)),
    arithm_count_(new size_t(0)),
    bin_count_(new size_t(0)),
    comp_count_(new size_t(0)) {}

StatisticsInt::StatisticsInt(const StatisticsInt& init_obj) :
    value_(init_obj.value_),
    ops_count_(new size_t(*init_obj.ops_count_)),
    assign_count_(new size_t(*init_obj.assign_count_)),
    arithm_count_(new size_t(*init_obj.arithm_count_)),
    bin_count_(new size_t(*init_obj.bin_count_)),
    comp_count_(new size_t(*init_obj.comp_count_)) {}

StatisticsInt::StatisticsInt(StatisticsInt&& init_obj) :
    value_(std::move(init_obj.value_)),
    ops_count_(new size_t(std::move(*init_obj.ops_count_))),
    assign_count_(new size_t(std::move(*init_obj.assign_count_))),
    arithm_count_(new size_t(std::move(*init_obj.arithm_count_))),
    comp_count_(new size_t(std::move(*init_obj.comp_count_))),
    bin_count_(new size_t(std::move(*init_obj.bin_count_))) {}

StatisticsInt::~StatisticsInt() {
    delete ops_count_;
    delete assign_count_;
    delete arithm_count_;
    delete bin_count_;
    delete comp_count_;
}

StatisticsInt& StatisticsInt::operator=(const StatisticsInt& assign_obj) {
    value_ = assign_obj.value_;
    
    ++StatisticsInt::global_assign_count_;
    ++StatisticsInt::global_ops_count_;

    ++(*ops_count_);
    ++(*assign_count_);
    
    *ops_count_ = *assign_obj.ops_count_;
    *assign_count_ = *assign_obj.assign_count_;
    *comp_count_ = *assign_obj.comp_count_;
    *arithm_count_ = *assign_obj.arithm_count_;
    *bin_count_  = *assign_obj.bin_count_;

    return *this;
}

StatisticsInt& StatisticsInt::operator=(StatisticsInt&& assign_obj) {
    value_ = std::move(assign_obj.value_);
    
    ++StatisticsInt::global_assign_count_;
    ++StatisticsInt::global_ops_count_;

    ++(*ops_count_);
    ++(*assign_count_);
    
    *ops_count_ = std::move(*assign_obj.ops_count_);
    *assign_count_ = std::move(*assign_obj.assign_count_);
    *comp_count_ = std::move(*assign_obj.comp_count_);
    *arithm_count_ = std::move(*assign_obj.arithm_count_);
    *bin_count_  = std::move(*assign_obj.bin_count_);

    return *this;
}

StatisticsInt& StatisticsInt::operator=(const int& int_value) {
    value_ = int_value;
    
    ++(*ops_count_);
    ++(StatisticsInt::global_ops_count_);

    ++(*assign_count_);
    ++(StatisticsInt::global_assign_count_);

    return *this;
}

// Conversastions
StatisticsInt::operator int() const {
    return value_;
}

// Comparison operators
bool operator<(const StatisticsInt& lhs, const StatisticsInt& rhs) {
    StatisticsInt::double_comp_increment(lhs, rhs);
    return lhs.value_ < rhs.value_;
}

bool operator>(const StatisticsInt& lhs, const StatisticsInt& rhs) {
    StatisticsInt::double_comp_increment(lhs, rhs);
    return rhs.value_ < lhs.value_;
}

bool operator<=(const StatisticsInt& lhs, const StatisticsInt& rhs) {
    StatisticsInt::double_comp_increment(lhs, rhs);
    return lhs.value_ <= rhs.value_;
}

bool operator>=(const StatisticsInt& lhs, const StatisticsInt& rhs) {
    StatisticsInt::double_comp_increment(lhs, rhs);
    return lhs.value_ >= rhs.value_;
}

bool operator==(const StatisticsInt& lhs, const StatisticsInt& rhs) {
    StatisticsInt::double_comp_increment(lhs, rhs);
    return lhs.value_ == rhs.value_;
}

bool operator!=(const StatisticsInt& lhs, const StatisticsInt& rhs) {
    StatisticsInt::double_comp_increment(lhs, rhs);
    return (lhs.value_ == rhs.value_) ^ true;
}

// Unary arithmitic operators
StatisticsInt& StatisticsInt::operator+=(const StatisticsInt& rhs) {
    single_arithm_increment(rhs);
    value_ += rhs.value_;
    return *this;
}

StatisticsInt& StatisticsInt::operator-=(const StatisticsInt& rhs) {
    single_arithm_increment(rhs);
    value_ -= rhs.value_;
    return *this;
}

StatisticsInt& StatisticsInt::operator*=(const StatisticsInt& rhs) {
    single_arithm_increment(rhs);
    value_ *= rhs.value_;
    return *this;
}

StatisticsInt& StatisticsInt::operator/=(const StatisticsInt& rhs) {
    single_arithm_increment(rhs);
    value_ /= rhs.value_;
    return *this;
}

StatisticsInt& StatisticsInt::operator%=(const StatisticsInt& rhs) {
    single_arithm_increment(rhs);
    value_ %= rhs.value_;
    return *this;
}

StatisticsInt& StatisticsInt::operator<<=(const StatisticsInt& rhs) {
    single_bin_increment(rhs);
    value_ <<= rhs.value_;
    return *this;
}

StatisticsInt& StatisticsInt::operator>>=(const StatisticsInt& rhs) {
    single_bin_increment(rhs);
    value_ >>= rhs.value_;
    return *this;
}

StatisticsInt& StatisticsInt::operator&=(const StatisticsInt& rhs) {
    single_bin_increment(rhs);
    value_ &= rhs.value_;
    return *this;
}

StatisticsInt& StatisticsInt::operator|=(const StatisticsInt& rhs) {
    single_bin_increment(rhs);
    value_ |= rhs.value_;
    return *this;
}

StatisticsInt& StatisticsInt::operator^=(const StatisticsInt& rhs) {
    single_bin_increment(rhs);
    value_ ^= rhs.value_;
    return *this;
}

// Increments and decrements
StatisticsInt& StatisticsInt::operator++() {
    single_arithm_increment(*this);
    ++value_;
    return *this;
}

StatisticsInt StatisticsInt::operator++(int) {
    single_arithm_increment(*this);
    StatisticsInt self_copy(*this);
    ++value_;
    return self_copy;
}

StatisticsInt& StatisticsInt::operator--() {
    single_arithm_increment(*this);
    --value_;
    return *this;
}

StatisticsInt StatisticsInt::operator--(int) {
    single_arithm_increment(*this);
    StatisticsInt self_copy(*this);
    --value_;
    return self_copy;
}

// Arithmetic operators
StatisticsInt operator+(const StatisticsInt& lhs, const StatisticsInt& rhs) {
    StatisticsInt::double_arithm_increment(lhs, rhs);
    return StatisticsInt(lhs.value_ + rhs.value_);
}

StatisticsInt operator-(const StatisticsInt& lhs, const StatisticsInt& rhs) {
    StatisticsInt::double_arithm_increment(lhs, rhs);
    return StatisticsInt(lhs.value_ - rhs.value_);
}

StatisticsInt operator*(const StatisticsInt& lhs, const StatisticsInt& rhs) {
    StatisticsInt::double_arithm_increment(lhs, rhs);
    return StatisticsInt(lhs.value_ * rhs.value_);
}

StatisticsInt operator/(const StatisticsInt& lhs, const StatisticsInt& rhs) {
    StatisticsInt::double_arithm_increment(lhs, rhs);
    return StatisticsInt(lhs.value_ / rhs.value_);
}

StatisticsInt operator%(const StatisticsInt& lhs, const StatisticsInt& rhs) {
    StatisticsInt::double_arithm_increment(lhs, rhs);
    return StatisticsInt(lhs.value_ % rhs.value_);
}

StatisticsInt operator<<(const StatisticsInt& lhs, const StatisticsInt& rhs) {
    StatisticsInt::double_bin_increment(lhs, rhs);
    return StatisticsInt(lhs.value_ << rhs.value_);
}

StatisticsInt operator>>(const StatisticsInt& lhs, const StatisticsInt& rhs) {
    StatisticsInt::double_bin_increment(lhs, rhs);
    return StatisticsInt(lhs.value_ >> rhs.value_);
}

StatisticsInt operator&(const StatisticsInt& lhs, const StatisticsInt& rhs) {
    StatisticsInt::double_bin_increment(lhs, rhs);
    return StatisticsInt(lhs.value_ & rhs.value_);
}

StatisticsInt operator|(const StatisticsInt& lhs, const StatisticsInt& rhs) {
    StatisticsInt::double_bin_increment(lhs, rhs);
    return StatisticsInt(lhs.value_ | rhs.value_);
}

StatisticsInt operator^(const StatisticsInt& lhs, const StatisticsInt& rhs) {
    StatisticsInt::double_bin_increment(lhs, rhs);
    return StatisticsInt(lhs.value_ ^ rhs.value_);
}
