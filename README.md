# Втрата пам'яті при копіюванні у heap

## Умова:

Напишіть код, в якому неправильне приведення типів призводить до втрати частини даних при копіюванні у динамічну пам’ять.

## [Програмний код](1.c)

## Опис:

Написано програму, у якій створена зміна типу long long (ll_var) копіюється у пам'ять, адреса якої збережена 
у вказівнику типу int (int_ptr). Копіювання виходить з втратою частини початкового значення типу long long, 
оскільки копіюються тільки молодші sizeof(int) (тут - 4) байтів з ll_val в int_ptr. Замість long long 
неправильно приведено тип int при копіюванні в heap (тип long long займає більше місця ніж ціле число), 
в який перший тип не вміщається. В результаті цього відбувається втрата даних, тобто з початкового long long 
0x11221122aabbaabb тільки молодші половина байтів aabbaabb зберіжуться, а старші 11221122 - 
втратяться, тому що int тут = 4B, а long long = 8B, що видно у результаті виконання.

## Результат виконання:

```bash
max@aspz:~/c/5 $ gcc -g 1.c -o 1
max@aspz:~/c/5 $ valgrind --leak-check=full ./1
==1143== Memcheck, a memory error detector
==1143== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==1143== Using Valgrind-3.24.0 and LibVEX; rerun with -h for copyright info
==1143== Command: ./1
==1143==
Long long (8B): 0x11221122aabbaabb
Allocated long long as int (4B) at: 0x5562080
Allocated int: 0xaabbaabb
==1143==
==1143== HEAP SUMMARY:
==1143==     in use at exit: 4,096 bytes in 1 blocks
==1143==   total heap usage: 2 allocs, 1 frees, 4,100 bytes allocated
==1143==
==1143== LEAK SUMMARY:
==1143==    definitely lost: 0 bytes in 0 blocks
==1143==    indirectly lost: 0 bytes in 0 blocks
==1143==      possibly lost: 0 bytes in 0 blocks
==1143==    still reachable: 0 bytes in 0 blocks
==1143==         suppressed: 4,096 bytes in 1 blocks
==1143==
==1143== For lists of detected and suppressed errors, rerun with: -s
==1143== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
