# Summary of the implementations of set.h #
## Overview ##
**How to test:** the command is

`$ make test set=test_set_o`

*test_set_o* is the file the test is about running on. **Overview performance**
Implementation | set.o | set1.o | set2.o | set3.o | set4.o | set5.o |
Fail tests              | 2/32  | 2/32    | 6/32   | 6/32    | 2/32    | 16/32  |

**Test cases** ?! is undefined result of the test.

Test case: ValidateMemUse with newSet and deleteSet
Test: No set has been created, validateMemUse should return true: ?!
Create a set: firstSet
Test: The firstSet should be not null: ?!
Test: One set was created, validateMemUse should return false: ?!
Test: Delete the first set, the returned set from function deleteSet should be null: ?!
Test: There is no set now, validateMemUse should return true: ?!
End test case!

Test case: insertItem with removeItem
Test insert and remove 1 item
Insert: 1 
Test: Insert 1 item should return true: ?!
Remove: 2 
Test: Remove wrong items should return false: ?!
Remove: 1 
Test: Remove 1 item should return true: ?!
Remove: 1 
Test: Remove same item second time (confirm removal) should return false: ?!
Reconstruct set
Test insert and remove 2 items width duplicate
Insert: 1 2 
Test: Insert 2 different items should return true: ?!
Insert: 1 
Test: Insert 1 item that duplicate a item in set should return false: ?!
Remove: 1 2 
Test: Remove first two item should return true: ?!
Remove: 1 
Test: Remove the item that tried to insert duplicate (to confirm no duplicate) should return false: ?!
Reconstruct set
Test insert and remove multiple items
Insert: 1 2 3 4 5 6 7 8 9 10 
Test: Insert multiple items should return true: ?!
Remove: 1 2 3 4 5 6 7 8 9 10 
Test: Remove multiple items (same items) should return true: ?!
End test case!

Test case: areEqual function
Test multiple-item sets
Insert set1, Insert: 1 2 3 4 5 6 7 8 9 10 1 2 3 4 5 6 7 8 9 10 
Insert set2, Insert: 1 2 3 4 5 6 7 8 9 10 1 2 3 4 5 6 7 8 9 10 
Test: Set1 should equal set2: ?!
Reconstruct set
Test 2 empty
Set 1: empty
Set 2: empty
Test: Set1 empty should equal set2 empty: ?!
Reconstruct set
Test empty set with non-empty set
Insert set1, Insert: 1 2 3 4 5 6 7 8 9 10 1 2 3 4 5 6 7 8 9 10 
Set 2: empty
Test: Set1 should NOT equal set2 empty: ?!
Reconstruct set
Test multiple-item same-length sets
Insert set1, Insert: 1 2 3 4 5 6 7 8 9 10 1 2 3 4 5 6 7 8 9 10 
Insert set2, Insert: 1 2 3 4 5 6 7 8 9 11 
Test: Set1 should NOT equal set2: ?!
End test case!

Test case: areDisjoint function
Test multiple-item length sets
Insert set1, Insert: 1 2 3 4 5 6 7 8 9 
Insert set2, Insert: 1 2 3 4 5 6 7 8 9 
Test: Set1 should NOT disjoint set2: ?!
Reconstruct set
Test multiple-item sets
Insert set1, Insert: 1 2 3 4 5 6 7 8 9 10 
Insert set2, Insert: 11 12 13 14 15 16 17 18 19 20 
Test: Set1 should disjoint set2: ?!
Reconstruct set
Test empty set with non-empty set
Insert set1, Insert: 1 2 3 4 5 6 7 8 9 
Test: Set1 non-empty should disjoint set2 empty: ?!
Reconstruct set
Test 2 empty sets
Test: Set1 empty should disjoint set2 empty: ?!
End test case!

Test case: unionOf function
Test 2 disjoint set
Set 1 Insert: 1 
Set 2 Insert: 2 
Set 3 Insert: 1 2 
Union set 1 and set 2
Test: Union set 1 and set 2 should equal set 3: ?!
Reconstruct sets
Test 2 non-disjoint set
Set 1 Insert: 1 2 3 4 5 6 7 8 9 10 
Set 2 Insert: 1 2 3 4 5 6 7 8 9 11 
Set 3 Insert: 1 2 3 4 5 6 7 8 9 10 11 
Union set 1 and set 2
Test: Union set 1 and set 2 should equal set 3: ?!
Reconstruct setsTest empty set and non-empty set
Set 1 Insert: 1 
Set 3 Insert: 1 
Union set 1 and set 2
Test: Union set 1 and set 2 empty should equal set 3: ?!
Reconstruct sets
Test 2 empty set
Union set 1 empty and set 2 empty
Test: Union set 1 and set 2 should equal set 3 empty: ?!
End test case!

Test case: symmetricDifferenceOf
Test 2 joint sets
Set 1 :Insert: 1 2 3 4 
Set 2 :Insert: 2 4 5 6 
Set 3:Insert: 1 3 5 6 
Test: Symmetric Difference of set 1 and set 2 should equal set 3: ?!
Reconstruct sets
Test 2 disjoint sets
Set 1 :Insert: 1 2 3 4 
Set 2 :Insert: 5 6 7 8 9 10 
Set 3:Insert: 1 2 3 4 5 6 7 8 9 10 
Test: Symmetric Difference of set 1 and set 2 should equal set 3: ?!
Reconstruct sets
Test 2 same sets
Set 1 :Insert: 1 2 3 4 5 6 7 8 9 10 
Set 2 :Insert: 1 2 3 4 5 6 7 8 9 10 
Set 3: empty
Test: Symmetric Difference of set 1 and set 2 should equal set 3: ?!
Reconstruct sets
Test non-empty set with empty set
Set 1 :Insert: 1 2 3 4 5 6 7 8 9 10 
Set 2 : empty
Set 3:Insert: 1 2 3 4 5 6 7 8 9 10 
Test: Symmetric Difference of set 1 and set 2 should equal set 3: ?!
Reconstruct sets
Test 2 empty sets
Set 1 : empty
Set 2 : empty
Set 3 : empty
Test: Symmetric Difference of set 1 and set 2 should equal set 3: ?!
End test case!

Test case: repeating construct and deconstruct set to test memory leak
Insert and remove 20 times
Insert and remove #1
Insert: 0 
Remove: 0 
Insert and remove #2
Insert: 0 1 
Remove: 0 1 
Insert and remove #3
Insert: 0 1 2 
Remove: 0 1 2 
Insert and remove #4
Insert: 0 1 2 3 
Remove: 0 1 2 3 
Insert and remove #5
Insert: 0 1 2 3 4 
Remove: 0 1 2 3 4 
Insert and remove #6
Insert: 0 1 2 3 4 5 
Remove: 0 1 2 3 4 5 
Insert and remove #7
Insert: 0 1 2 3 4 5 6 
Remove: 0 1 2 3 4 5 6 
Insert and remove #8
Insert: 0 1 2 3 4 5 6 7 
Remove: 0 1 2 3 4 5 6 7 
Insert and remove #9
Insert: 0 1 2 3 4 5 6 7 8 
Remove: 0 1 2 3 4 5 6 7 8 
Insert and remove #10
Insert: 0 1 2 3 4 5 6 7 8 9 
Remove: 0 1 2 3 4 5 6 7 8 9 
Insert and remove #11
Insert: 0 1 2 3 4 5 6 7 8 9 10 
Remove: 0 1 2 3 4 5 6 7 8 9 10 
Insert and remove #12
Insert: 0 1 2 3 4 5 6 7 8 9 10 11 
Remove: 0 1 2 3 4 5 6 7 8 9 10 11 
Insert and remove #13
Insert: 0 1 2 3 4 5 6 7 8 9 10 11 12 
Remove: 0 1 2 3 4 5 6 7 8 9 10 11 12 
Insert and remove #14
Insert: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 
Remove: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 
Insert and remove #15
Insert: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 
Remove: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 
Insert and remove #16
Insert: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 
Remove: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 
Insert and remove #17
Insert: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 
Remove: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 
Insert and remove #18
Insert: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 
Remove: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 
Insert and remove #19
Insert: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Remove: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Insert and remove #20
Insert: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 
Remove: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 
Construct, insert and deleteSet 20 times
Construct, insert and deleteSet #1
Insert: 0 
Remove: 0 
Construct, insert and deleteSet #2
Insert: 0 1 
Remove: 0 1 
Construct, insert and deleteSet #3
Insert: 0 1 2 
Remove: 0 1 2 
Construct, insert and deleteSet #4
Insert: 0 1 2 3 
Remove: 0 1 2 3 
Construct, insert and deleteSet #5
Insert: 0 1 2 3 4 
Remove: 0 1 2 3 4 
Construct, insert and deleteSet #6
Insert: 0 1 2 3 4 5 
Remove: 0 1 2 3 4 5 
Construct, insert and deleteSet #7
Insert: 0 1 2 3 4 5 6 
Remove: 0 1 2 3 4 5 6 
Construct, insert and deleteSet #8
Insert: 0 1 2 3 4 5 6 7 
Remove: 0 1 2 3 4 5 6 7 
Construct, insert and deleteSet #9
Insert: 0 1 2 3 4 5 6 7 8 
Remove: 0 1 2 3 4 5 6 7 8 
Construct, insert and deleteSet #10
Insert: 0 1 2 3 4 5 6 7 8 9 
Remove: 0 1 2 3 4 5 6 7 8 9 
Construct, insert and deleteSet #11
Insert: 0 1 2 3 4 5 6 7 8 9 10 
Remove: 0 1 2 3 4 5 6 7 8 9 10 
Construct, insert and deleteSet #12
Insert: 0 1 2 3 4 5 6 7 8 9 10 11 
Remove: 0 1 2 3 4 5 6 7 8 9 10 11 
Construct, insert and deleteSet #13
Insert: 0 1 2 3 4 5 6 7 8 9 10 11 12 
Remove: 0 1 2 3 4 5 6 7 8 9 10 11 12 
Construct, insert and deleteSet #14
Insert: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 
Remove: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 
Construct, insert and deleteSet #15
Insert: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 
Remove: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 
Construct, insert and deleteSet #16
Insert: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 
Remove: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 
Construct, insert and deleteSet #17
Insert: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 
Remove: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 
Construct, insert and deleteSet #18
Insert: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 
Remove: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 
Construct, insert and deleteSet #19
Insert: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Remove: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 
Construct, insert and deleteSet #20
Insert: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 
Remove: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 
End test case! 

## Detail
**Notes:**

- If functions is not mentioned in the detail below, it meant the function succeeded all the test cases. 
- Because the command "top" is not working in the remote machine. I have no way to actually test memory leak. "Top" command should be used to check the memory before and after run the test. 

**Detail test cases**

0. Set.o

- Function removeItem:
  - *Case:* removing item not existing in the set. *Expect:* return false. *Actual:* return true.
- Other functions run as expected.
- Memory leak: 

1. Set1.o

- Function removeItem:
  - *Case:* removing item not existing in the set. *Expect:* return false. *Actual:* return true.
- Other functions run as expected.
- Memory leak: 

2. Set2.o

- Inserting duplicate element return unexpected value. Expect returning false and not inserting, actual returning true. 
- Remove function does not return right value. Expect returning true and removing elements from set when removing elements in sets, actual return false. Expect return false when removing elements that do not exist in sets, actual return true.
- Set includes duplicating elements. Expect: no duplicate elements in sets. 
- Other functions run as expected.
- Memory leak: 

3. Set3.o

- Function removeItem:
  - *Case:* removing item not existing in the set. *Expect:* return false. *Actual:* return true.
- areDisjoint function failed some cases. 
  - *Case*: Non empty set and empty set. *Expect*: return true. *Actual:* return false.
  - *Case:* 2 non-empty sets are expected to be disjoint. *Expect:* return true. *Actual:* return false.
- Function symmetricDifferenceOf:
  - *Case:* the symmetric difference set of 2 non-empty sets is expected to be equal the expected set. *Expect:* return the expected results. *Actual:* return the result not equal the expected results.
  - *Case:* the symmetric difference set of empty set and non-empty set should be equal the non-empty set. *Expect:* return the set that are equal the non-empty set. *Actual:* the result is not equal the non-empty set.
- Memory leak: 

4. Set4.o

- Function removeItem:
  - *Case:* removing item not existing in the set. *Expect:* return false. *Actual:* return true. 

5. Set5.o

- Function removeItem:
  - *Case:* removing item not existing in the set. *Expect:* return false. *Actual:* return true.
- Function areEqual:
  - *Case:* Insert same elements into 2 sets. Comparing 2 sets should be equal. *Expect:* return true. *Actual:* return false.
  - Case: Comparing non-empty set and empty set should be unequal. *Expect:* return false. *Actual:* return true.
- There were failed cases in functions areDisjoint, unionOf, symmetricDifference but it is impossible to clarify due to the dependency of function areEqual for testing other functions.