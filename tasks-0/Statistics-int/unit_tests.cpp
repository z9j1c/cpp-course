#include "stat_int.h"
#include <assert.h>
#include <iostream>
#include <utility>

// TODO: make convinient test macro

int main(int argc, char** argv) {
    
    // Basic tests
    {
        // Int-cast and default constructor tests
        StatisticsInt num1(42);
        assert(static_cast<int>(num1) == 42);

        StatisticsInt num2(-5);
        assert(static_cast<int>(num2) == -5);

        // Copy constructor test
        StatisticsInt num1_copy(num1);
        assert(static_cast<int>(num1) == static_cast<int>(num1_copy));

        // Assign constructor test
        StatisticsInt num2_assign = num2;
        assert(static_cast<int>(num2) == static_cast<int>(num2_assign));

        // Int assign operator
        num2 = -4;
        assert(static_cast<int>(num2) == -4);

        // Move copy constructor test
        StatisticsInt num1_move_copy(std::move(num1));
        assert(static_cast<int>(num1) == static_cast<int>(num1_move_copy));

        // Move assign constructor test
        StatisticsInt num2_move_assign = std::move(num2);
        assert(static_cast<int>(num2) == static_cast<int>(num2_move_assign));
    }

    // Comparisons tests
    {
        StatisticsInt num1(42);
        StatisticsInt num2(-3);
        StatisticsInt num3(42);

        assert(num2 < num1);
        assert(num1 > num2);
        
        assert(num1 == num3);
        assert(num1 != num2);
        
        assert(num1 <= num3);
        assert(num2 <= num1);

        assert(num1 >= num3);
        assert(num1 >= num2);

        const int NUM1_OPS_COUNT = 8; // These tests made comparisons only
        assert(num1.GetComparisonsCount() == NUM1_OPS_COUNT);
        assert(num1.GetOperationsCount() == NUM1_OPS_COUNT);
    }

    // Unary arithmetic and shifts tests
    {
        StatisticsInt num1(1);
        StatisticsInt num2(0);

        // += test
        num2 += num1;
        assert(static_cast<int>(num2) == 1);
        
        // -= test
        num2 -= num1;
        assert(static_cast<int>(num2) == 0);

        // *= tests
        num2 *= num1;
        assert(static_cast<int>(num2) == 0);
        num2 = 3;
        num2 *= num1;
        assert(static_cast<int>(num2) == 3);

        // /= test
        num1 = 2;
        num2 /= num1;
        assert(static_cast<int>(num2) == 1);

        // %= tests
        num2 = 80;
        num1 = 3;
        num2 %= num1;
        assert(static_cast<int>(num2) == 2);

        // >>= test
        num2 = 64;
        num1 = 2;
        num2 >>= num1;
        assert(static_cast<int>(num2) == 16);

        // <<= test
        num1 = 3;
        num2 <<= num1;
        assert(static_cast<int>(num2) == 128);

        // Increments and decrements tests
        num1++;
        assert(static_cast<int>(num1) == 4);
        
        ++num1;
        assert(static_cast<int>(num1) == 5);

        num1--;
        assert(static_cast<int>(num1) == 4);

        --num1;
        assert(static_cast<int>(num1) == 3);

        // Unary arithmetic and shifts counters' tests
        const int NUM1_ARITHM_COUNT = 10;
        const int NUM1_SHIFTS_COUNT = 2;
        assert(num1.GetArithmeticsCount() == NUM1_ARITHM_COUNT);
        assert(num1.GetBinsCount() == NUM1_SHIFTS_COUNT);
    }

    // Two operands arithmetic tests
    {
        StatisticsInt num1(2);
        StatisticsInt num2(3);
        StatisticsInt test_num;

        test_num = num1 + num2;
        assert(static_cast<int>(test_num) == 5);

        test_num = num2 - num1;
        assert(static_cast<int>(test_num) == 1);

        test_num = num2 * num1;
        assert(static_cast<int>(test_num) == 6);

        num2 = 7;
        num1 = 3;
        test_num = num2 / num1;
        assert(static_cast<int>(test_num) == 2);

        test_num = num2 % num1;
        assert(static_cast<int>(test_num) == 1);

        num2 = 64;
        num1 = 2;
        test_num = num2 >> num1;
        assert(static_cast<int>(test_num) == 16);

        num2 = 1;
        num1 = 2;
        test_num = num2 << num1;
        assert(static_cast<int>(test_num) == 4);

        const int NUM1_ARITHM_COUNT = 5;
        const int NUM1_SHIFTS_COUNT = 2;
        assert(num1.GetArithmeticsCount() == NUM1_ARITHM_COUNT);
        assert(num1.GetBinsCount() == NUM1_SHIFTS_COUNT);
    }

    std::cout << "OK: ALL TESTS PASSED" << std::endl;
}