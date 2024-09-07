#include "libmin.h"

typedef struct testcase_t
{
  const char *input_str;
  unsigned long expected_value;
  int base;
  const char *expected_endptr;
  int expect_endptr_set_correctly;
} testcase_t;

testcase_t test_cases[] = {
    {
      .input_str = "12345",
      .expected_value = 12345UL,
      .base = 10,
      .expected_endptr = NULL,
      .expect_endptr_set_correctly = 0
    },                  // Base 10 by default
    {
      .input_str = "0x1A3F",
      .expected_value = 0x1A3FUL,
      .base = 0,
      .expected_endptr = NULL,
      .expect_endptr_set_correctly = 0
    },                 // Base 16 with 0x prefix
    {
      .input_str = "0123",
      .expected_value = 83UL,
      .base = 0,
      .expected_endptr = NULL,
      .expect_endptr_set_correctly = 0
    },                       // Base 8 with leading 0
    {
      .input_str = "123",
      .expected_value = 123UL,
      .base = 0,
      .expected_endptr = NULL,
      .expect_endptr_set_correctly = 0
    },                       // Base 10 without leading 0
    {
      .input_str = "0x123abc",
      .expected_value = 0x123abcUL,
      .base = 16,
      .expected_endptr = NULL,
      .expect_endptr_set_correctly = 0
    },            // Explicit base 16
    {
      .input_str = "0b1101",
      .expected_value = 0UL,
      .base = 0,
      .expected_endptr = "b1101",
      .expect_endptr_set_correctly = 1
    },                   // Invalid binary (should stop at 'b')
    {
      .input_str = "abc",
      .expected_value = 0UL,
      .base = 0,
      .expected_endptr = "abc",
      .expect_endptr_set_correctly = 1
    },                        // Invalid input (not a number)
    {
      .input_str = "12345",
      .expected_value = 12345UL,
      .base = 10,
      .expected_endptr = NULL,
      .expect_endptr_set_correctly = 0
    },                  // Base 10 again
    {
      .input_str = "1A3F",
      .expected_value = 0x1A3FUL,
      .base = 16,
      .expected_endptr = NULL,
      .expect_endptr_set_correctly = 0
    },                  // Base 16 without 0x prefix
    {
      .input_str = "177",
      .expected_value = 127UL,
      .base = 8,
      .expected_endptr = NULL,
      .expect_endptr_set_correctly = 0
    },                       // Base 8
    {
      .input_str = "abc",
      .expected_value = 0UL,
      .base = 10,
      .expected_endptr = "abc",
      .expect_endptr_set_correctly = 1
    },                       // Invalid input for base 10
    {
      .input_str = "18446744073709551616",
      .expected_value = ULONG_MAX,
      .base = 10,
      .expected_endptr = NULL,
      .expect_endptr_set_correctly = 0
    }, // Overflow case
    {
      .input_str = "100abc",
      .expected_value = 100UL,
      .base = 10,
      .expected_endptr = "abc",
      .expect_endptr_set_correctly = 1
    },                  // Mixed valid and invalid input
};

int main()
{

  int num_tests = sizeof(test_cases) / sizeof(testcase_t);
  int all_tests_passed = 1;

  for (int i = 0; i < num_tests; i++)
  {
    char *endptr = NULL;
    unsigned long result = strtoul(test_cases[i].input_str, test_cases[i].expect_endptr_set_correctly ? &endptr : NULL, test_cases[i].base);

    // Check if the conversion result matches the expected value
    if (result != test_cases[i].expected_value)
    {
      fprintf(stderr, "Test case %d failed: expected %lu, got %lu\n", i + 1, test_cases[i].expected_value, result);
      all_tests_passed = 0;
    }

    // If we expect to check endptr, verify that it is set correctly
    if (test_cases[i].expect_endptr_set_correctly && strcmp(endptr, test_cases[i].expected_endptr) != 0)
    {
      fprintf(stderr, "Test case %d failed: expected endptr to point to '%s', got '%s'\n", i + 1, test_cases[i].expected_endptr, endptr);
      all_tests_passed = 0;
    }
  }

  // Print final result
  if (all_tests_passed)
  {
    printf("All tests passed.\n");
  }
  else
  {
    printf("Some tests failed.\n");
  }

  return 0;
}
