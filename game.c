#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define n 4

int printBoard(int array[n][n]);
int calculateScore(int array[n][n]);
void addRandom(int array[n][n]);
void initializeBoard(int array[n][n]);
int get_work(int array[n][n] , int save_array[n][n]);
int FindTarget(int array[n][n], int coulmn, int row, int stop);
void rotate_array(int array[n][n]);
int moveLefting(int array[n][n]);
int moveLeft(int array[n][n] , int save_array[n][n]);
int moveRight(int array[n][n] , int save_array[n][n]);
int moveUp(int array[n][n] , int save_array[n][n]);
int moveDown(int array[n][n] , int save_array[n][n]);
int win_or_not(int array[n][n]);
int lose_or_not(int array[n][n]);
int new_game();
int back(int array[n][n]);
int saving_array(int array[n][n], int save_array[n][n]);
int check_change (int array[n][n] , int save_array[n][n]);
int have_zero(int array[n][n]);

//تابع بازی اصلی
int main()
{
    srand(time(0));
    int array[n][n]; //صفحه بازی
    int save_array[n][n]; //تابعی برای ذخیره کردن صفحه بازی
    initializeBoard(array);
    printBoard(array);
    while (1)
    {
        if (win_or_not(array) == 1)
        {
            printf("YOU WIN");
            return 1;
        }
        else if (lose_or_not(array) == 1)
        {
            printf("\nYOU LOSE");
            printBoard(array);
            return 0;
        }
        else
        {
            if (get_work(array , save_array) == 0 )
            {
                return 0 ;
            }
        }
    }
    return 0;
}

// تابع چاپ کننده ی محیط بازی
int printBoard(int array[n][n])
{
    printf("\n*************************************\nYour Score: %d\n-----------------------\n", calculateScore(array));
    for (int row = 0; row < n; row++)
    {
        for (int coulmn = 0; coulmn < n; coulmn++)
        {
            if (array[row][coulmn])
            {
                printf("|%4d", array[row][coulmn]);
            }
            else
            {
                printf("|    ");
            }
        }
        printf("|\n");
    }
    printf("-----------------------");
    if ((win_or_not(array) == 0) && (lose_or_not(array) == 0))
    {
        printf("\nMove (L/R/U/D) or Quit, Back, New Start(Q, B, N):");
    }
}

// تابع محاسبه امتیاز
int calculateScore(int array[n][n])
{
    int score = 0;
    for (int row = 0; row < n; row++)
    {
        for (int coulmn = 0; coulmn < n; coulmn++)
        {
            score += array[row][coulmn];
        }
    }
    return score;
}

// تابع تولیدکننده ی مقدار تصادفی
void addRandom(int array[n][n])
{
    while (have_zero(array) == 1)
    {
        int row = rand() % 4, coulmn = rand() % 4; // انتخاب ستون و ردیف ارایه
        if (array[row][coulmn] == 0)
        {
            int x = rand() % 2;
            if (x == 0)
            {
                array[row][coulmn] = 2;
            }
            else
            {
                array[row][coulmn] = 4;
            }
            break;
        }
    }
}

// تابع مقداردهی اولیه بازی
void initializeBoard(int array[n][n])
{
    for (int row = 0; row < n; row++)
    {
        for (int coulmn = 0; coulmn < n; coulmn++)
        {
            array[row][coulmn] = 0; // تمام ارایه ها را صفر میکنیم
        }
    }
    // به دو تا از ارایه ها مقدار میدهیم
    addRandom(array);
    addRandom(array);
}

//تابع گرفتن ورودی و انجام عملیات ها
int get_work(int array[n][n] , int save_array[n][n]){
    char work = getche(); // گرفتن ورودی از کاربر
        switch (work)
        {
        case 'L': // رفتن به چپ
            moveLeft(array , save_array);
            break;
        case 'R': // رفتن به راست
            moveRight(array , save_array);
            break;
        case 'U': // رفتن به بالا
            moveUp(array , save_array);
            break;
        case 'D': // رفتن به پایین
            moveDown(array , save_array);
            break;
        case 'B': // به مرحله قبلی برگشتن
            back(save_array);
            break;
        case 'N': // بازی جدید
            new_game();
            return 0;
        case 'Q': //پایان بازی
            return 0;
        default: //ورودی های تعریف نشده
            printf("\ninvalid move");
            printBoard(array);
        }
}

// تابع حرکت کردن صفحه بازی به سمت چپ
int moveLefting(int array[n][n])
{
    for (int row = 0; row < n; row++)
    {
        int stop = 0;
        for (int coulmn = 0; coulmn < n; coulmn++)
        {   
            if(array[row][coulmn] == 0)
            {
                continue;
            }
            // اگر مقدار ارایه برابر با صفر بود کاری نمیکنیم
            if (array[row][coulmn] != 0)
            {
                int target = FindTarget(array, coulmn, row, stop);
                // اگر تارگت با کالمن مساوی بود کاری نمیکنیم
                if (target != coulmn)
                {
                    if (array[row][target] == 0)
                    {
                        array[row][target] = array[row][coulmn];
                    }
                    else if (array[row][target] == array[row][coulmn])
                    {
                        array[row][target] *= 2;
                        stop++;
                        if(coulmn==2){
                        stop ++ ;
                    }
                    }
                    array[row][coulmn] = 0;
                }
            }
        }
    }
}

// تابع پیدا کردن تارگت برای کمک به تابع حرکت به چپ
int FindTarget(int array[n][n], int coulmn, int row, int stop)
{
    if (coulmn == 0)
    {
        return 0;
    }
    for (int target = coulmn - 1; target >= 0; target--)
    {
        if (array[row][target] != 0)
        {
            if (array[row][target] == array[row][coulmn])
            {
                return target;
            }
            else
            {
                return target + 1;
            }
        }
        else
        {
            if (stop == target)
            {
                return target;
            }
        }
        
    }
}

//مشخص کردن برد
int win_or_not(int array[n][n])
{
    for (int row = 0; row < n; row++)
    {
        for (int coulmn = 0; coulmn < n; coulmn++)
        {
            if (array[row][coulmn] == 2048)
            {
                return 1; //بردن
            }
        }
    }
    return 0; //هنوز نبردن
}

//مشخص کردن باخت
int lose_or_not(int array[n][n])
{
    for (int i = 0; i < n; i++)
    { 
        for (int j = 0; j < n; j++)
        {
            if(array[i][j] == 0)
            {
                return 0 ;
            }
            if ((i < n-1) && (array[i][j]==array[i+1][j])){
                return 0 ;
            }
            if ((j < n-1) && (array[i][j] == array[i][j+1]))
            {
                return 0 ;
            }
        }
    }
    return 1;
}

//چرخاندن صفحه بازی
void rotate_array(int array[n][n])
{
    int tmp;
    for (int row = 0; row < n / 2; row++)
    {
        for (int coulmn = row; coulmn < n - row - 1; coulmn++)
        {
            tmp = array[row][coulmn];
            array[row][coulmn] = array[coulmn][n - row - 1];
            array[coulmn][n - row - 1] = array[n - row - 1][n - coulmn - 1];
            array[n - row - 1][n - coulmn - 1] = array[n - coulmn - 1][row];
            array[n - coulmn - 1][row] = tmp;
        }
    }
}

//حرکت به چپ
int moveLeft(int array[n][n] , int save_array[n][n])
{
    saving_array(array, save_array);
    moveLefting(array);
    if (check_change(array , save_array) == 1)
    {
    addRandom(array);
    }
    if (lose_or_not(array) == 0)
    {
        printBoard(array);
    }
}

//حرکت به راست
int moveRight(int array[n][n] , int save_array[n][n])
{
    saving_array(array, save_array);
    rotate_array(array);
    rotate_array(array);
    moveLefting(array);
    rotate_array(array);
    rotate_array(array);
    if (check_change(array , save_array) == 1)
    {
    addRandom(array);
    }
    if (lose_or_not(array) == 0)
    {
        printBoard(array);
    }
}

//حرکت به بالا
int moveUp(int array[n][n] , int save_array[n][n])
{
    saving_array(array, save_array);
    rotate_array(array);
    moveLefting(array);
    rotate_array(array);
    rotate_array(array);
    rotate_array(array);
    if (check_change(array , save_array) == 1)
    {
    addRandom(array);
    }
    if (lose_or_not(array) == 0)
    {
        printBoard(array);
    }
}

//حرکت به پایین
int moveDown(int array[n][n] , int save_array[n][n])
{
    saving_array(array, save_array);
    rotate_array(array);
    rotate_array(array);
    rotate_array(array);
    moveLefting(array);
    rotate_array(array);
    if (check_change(array , save_array) == 1)
    {
    addRandom(array);
    }
    if (lose_or_not(array) == 0)
    {
        printBoard(array);
    }
}

//شروع بازی جدید
int new_game()
{
    main();
}

//ذخیره کردن صفحه بازی
int saving_array(int array[n][n], int save_array[n][n])
{   
        if (check_change ( array , save_array) ==1){
        for (int row = 0; row < n; row++)
        {
            for (int coulmn = 0; coulmn < n; coulmn++)
            {
                save_array[row][coulmn] = array[row][coulmn];
            }
        }
        }
    
}

//برگشنن به مرحله قبلی
int back(int save_array[n][n])
{
    printBoard(save_array);
}

//تابعی که چک کند ترتیه تغیر کرده است یا نه
int check_change (int array[n][n] , int save_array[n][n]){
    int number_of_equals = 0 ;
    for (int row = 0; row < n; row++)
    {
        for (int coulmn = 0; coulmn < n; coulmn++)
        {
            if(save_array[row][coulmn] == array[row][coulmn])
            {
                number_of_equals ++ ;
            }
        }
    }
    if (number_of_equals==16)
    {
        return 0 ;
    }
    else 
    {
        return 1 ;
    }
}

//تابعی که چک کند ارایه ی صفر وجود دارد یا نه
int have_zero(int array[n][n]){
    for (int row = 0; row < n; row++)
    {
        for (int coulmn = 0; coulmn < n; coulmn++)
        {
            if (array[row][coulmn] == 0)
            {
                return 1 ;
            }
        }
    }
    return 0 ;
}
