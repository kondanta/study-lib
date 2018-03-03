## TODO

- Change from `transparent` to `safe`
- Add iterator for traversing.
- Add delete routine[memory leaks!!]

---
*Valgrind output before editing the existing code*

```
==18572== HEAP SUMMARY:
==18572==     in use at exit: 488 bytes in 11 blocks
==18572==   total heap usage: 17 allocs, 6 frees, 74,280 bytes allocated
==18572== 
==18572== Searching for pointers to 11 not-freed blocks
==18572== Checked 101,608 bytes
==18572== 
==18572== 16 bytes in 1 blocks are indirectly lost in loss record 1 of 11
==18572==    at 0x4C2D54F: operator new(unsigned long) (vg_replace_malloc.c:334)
==18572==    by 0x109BE1: allocate (new_allocator.h:111)
==18572==    by 0x109BE1: allocate (alloc_traits.h:436)
==18572==    by 0x109BE1: _M_allocate (stl_vector.h:172)
==18572==    by 0x109BE1: _M_realloc_insert<DrawingElement *const &> (vector.tcc:406)
==18572==    by 0x109BE1: push_back (stl_vector.h:948)
==18572==    by 0x109BE1: CompositeElement::Add(DrawingElement*) (main.cpp:71)
==18572==    by 0x109541: main (main.cpp:106)
==18572== 
==18572== 40 bytes in 1 blocks are indirectly lost in loss record 2 of 11
==18572==    at 0x4C2D54F: operator new(unsigned long) (vg_replace_malloc.c:334)
==18572==    by 0x1092AF: main (main.cpp:100)
==18572== 
==18572== 40 bytes in 1 blocks are indirectly lost in loss record 3 of 11
==18572==    at 0x4C2D54F: operator new(unsigned long) (vg_replace_malloc.c:334)
==18572==    by 0x10931A: main (main.cpp:101)
==18572== 
==18572== 40 bytes in 1 blocks are indirectly lost in loss record 4 of 11
==18572==    at 0x4C2D54F: operator new(unsigned long) (vg_replace_malloc.c:334)
==18572==    by 0x109397: main (main.cpp:102)
==18572== 
==18572== 40 bytes in 1 blocks are indirectly lost in loss record 5 of 11
==18572==    at 0x4C2D54F: operator new(unsigned long) (vg_replace_malloc.c:334)
==18572==    by 0x10947B: main (main.cpp:105)
==18572== 
==18572== 40 bytes in 1 blocks are indirectly lost in loss record 6 of 11
==18572==    at 0x4C2D54F: operator new(unsigned long) (vg_replace_malloc.c:334)
==18572==    by 0x1094F4: main (main.cpp:106)
==18572== 
==18572== 40 bytes in 1 blocks are indirectly lost in loss record 7 of 11
==18572==    at 0x4C2D54F: operator new(unsigned long) (vg_replace_malloc.c:334)
==18572==    by 0x109566: main (main.cpp:110)
==18572== 
==18572== 40 bytes in 1 blocks are definitely lost in loss record 8 of 11
==18572==    at 0x4C2D54F: operator new(unsigned long) (vg_replace_malloc.c:334)
==18572==    by 0x1095C0: main (main.cpp:111)
==18572== 
==18572== 64 bytes in 1 blocks are indirectly lost in loss record 9 of 11
==18572==    at 0x4C2D54F: operator new(unsigned long) (vg_replace_malloc.c:334)
==18572==    by 0x10940C: main (main.cpp:104)
==18572== 
==18572== 64 bytes in 1 blocks are indirectly lost in loss record 10 of 11
==18572==    at 0x4C2D54F: operator new(unsigned long) (vg_replace_malloc.c:334)
==18572==    by 0x109BE1: allocate (new_allocator.h:111)
==18572==    by 0x109BE1: allocate (alloc_traits.h:436)
==18572==    by 0x109BE1: _M_allocate (stl_vector.h:172)
==18572==    by 0x109BE1: _M_realloc_insert<DrawingElement *const &> (vector.tcc:406)
==18572==    by 0x109BE1: push_back (stl_vector.h:948)
==18572==    by 0x109BE1: CompositeElement::Add(DrawingElement*) (main.cpp:71)
==18572==    by 0x109614: main (main.cpp:112)
==18572== 
==18572== 448 (64 direct, 384 indirect) bytes in 1 blocks are definitely lost in loss record 11 of 11
==18572==    at 0x4C2D54F: operator new(unsigned long) (vg_replace_malloc.c:334)
==18572==    by 0x10924B: main (main.cpp:99)
==18572== 
==18572== LEAK SUMMARY:
==18572==    definitely lost: 104 bytes in 2 blocks
==18572==    indirectly lost: 384 bytes in 9 blocks
==18572==      possibly lost: 0 bytes in 0 blocks
==18572==    still reachable: 0 bytes in 0 blocks
==18572==         suppressed: 0 bytes in 0 blocks

```
