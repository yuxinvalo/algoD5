#include <stdio.h>
#include <math.h>
# define MtabX_COLUMN 80
#include <stdint.h>
#include <assert.h> 
#include <time.h>
#include <string.h> 
uintmax_t cmp_count;


unsigned partition_cmp(int* tab, unsigned b, unsigned e, unsigned p, int (*cmp)(int a, int b));

//------------------print_int_array----------------------------------------
unsigned int_width(double i)
{
        unsigned nb = 0;
        if (i > 0)
        { 
                nb = log10(i) + 1;
        } 
        else if (i < 0)
        { 
                i = i * (-1); 
                nb = log10((double)i) + 2;
        }     
        else
        {
                nb = 1;
        }
        return nb;
}

unsigned ints_width(const int* tab, unsigned count)
{
        unsigned nb[count];
        unsigned max_nb = 0;

        if(tab != NULL)
        {
                for (unsigned i = 0; i < count; ++i)
                {
                        nb[i] = int_width(tab[i]);
                }

                for(unsigned i = 0; i < count; ++i)
                {
                        if(max_nb < nb[i])
                        {
                                max_nb = nb[i];
                        }
                }
                return max_nb;
        }
        return -1;
}

void printWhiteSpace(FILE* out, unsigned int count)
{
        for (unsigned int i = 0; i < count ; ++i)
        {
                fprintf(out, " ");
        }
}

void printOneInt(FILE*out, const int num, const unsigned int int_width, const unsigned int max_width)
{
        printWhiteSpace(out, max_width - int_width);
        fprintf(out, "%d", num);
}

void print_int_array(FILE* out, const int* tab, unsigned count)
{
        unsigned int max_width = ints_width(tab, count);
        // unsigned int leadingIndex = 0;
        unsigned int numOfIntsInTheRow;
        unsigned int indexWidth = int_width(count - 1);
        for (unsigned int i = 0; i < count;)
        {
                numOfIntsInTheRow = (MtabX_COLUMN - int_width(count - 1) - 2) / (max_width + 1);
                printWhiteSpace(out, indexWidth - int_width(i));
                fprintf(out, "[");
                fprintf(out, "%d", i);
                fprintf(out, "]");
                for (unsigned int j = i; j < i + numOfIntsInTheRow && j < count; ++j)
                {
                        fprintf(out, " ");
                        printOneInt(out, tab[j], int_width(tab[j]), max_width);
                }
                fprintf(out, "\n");
                i += numOfIntsInTheRow;
        }
}
//--------------------print_int_array--------------------------------


//--------------------partition_cmp--------------------------------
int increasing(int a, int b)
{
         ++cmp_count;
        if (a < b)
                return -1;
        return a > b; //superieur à  0
}

void swap(unsigned* a, unsigned *b)
{
        unsigned temp = *a;
        *a = *b;
        *b = temp;
				return ;
}

//----b==>beginIndex e==>endIndex-----p==>pivotIndex---------
unsigned partition_cmp(int* tab, unsigned b, unsigned e,
                unsigned p, int (*cmp)(int a, int b))
{
        int x =  tab[p];
        unsigned i = b - 1;
        unsigned j = e;


        while(1)
        {
                //move start with endIndex
                do
                {	i = i + 1;}
                while(cmp(x, tab[i]) > 0);

                do
                {j = j - 1;}
                while(cmp(x,tab[j]) < 0);

                /*		while((*cmp)(e, b) == -1 && (*cmp)(tab[j],tab[x]) < 0)
                      i++;	
                      if((*cmp)(e, b) <= 0)
                      break;
                //move start with beginIndex
                while((*cmp)(b, e) == -1 && (*cmp)(tab[b],tab[p]) < 0)
                b++;	
                if((*cmp)(e, b) <= 0)
                break;
                tab[e--] = tab[b];*/
                if(i < j)
                {
                        int temp = 0;
                        temp =	tab[i];
                        tab[i] = tab[j];
                        tab[j] = temp; 
                } else
								{
								printf("i is %i, and that is%i, b is %i\n ",i, i+(i==b),b);
                return i + (i == b);	
								}
								
        }
}
//-------------------partition _cmp-------------------------------

//------------------pivot_first---------------------------------
unsigned pivot_first(const int* tab, unsigned l, unsigned r,
                     int (*cmp)(int a, int b))
{
	(void) tab;
  (void) r;
  (void) cmp;
  return l;
}

unsigned pivot_rand(const int* tab, unsigned l, unsigned r,
                    int (*cmp)(int a, int b))
{
  (void) tab;
  return l + (rand() % (r - l));
}
//----------------faux!!!!------------------------------
unsigned pivot_median3(const int* tab, unsigned l, unsigned r,
                       int (*cmp)(int a, int b))
{
	int middle = (l + r)/2;
	if(cmp(tab[middle], tab[l]) == -1 )
		swap(&tab[l], &tab[middle]);
	if(cmp(tab[r],tab[l]) == -1)
		swap(&tab[l], &tab[r]);
	if(cmp(tab[r], tab[middle]) == -1)
		swap(&tab[middle], &tab[r]);

	swap(&tab[middle], &tab[r - 1]);
	return r - 1;
}

//------------------pivot_first---------------------------------

//------------------quick_sort_cmp------------------------------


void quick_sort_cmp_loop(int* tab, unsigned count, unsigned (*pivot)(const int* tab, unsigned l, unsigned r,int (*cmp)(int a, int b)),
                         int (*cmp)(int a, int b))
{


}


//------------------quick_sort_cmp------------------------------

#define mycheck(fun, tab)                                  \
  {                                                        \
    cmp_count = 0;                                         \
    clock_t before = clock();                              \
    fun(tab, tsize, pivot_median3, my_increasing);         \
    clock_t after = clock();                               \
    printf(#fun " used %ju comparisons and %ju ticks\n",   \
           cmp_count, (uintmax_t) (after - before));       \
  }




int main(void)
{
        //test for partition_cmp-----------------------------
/*   for (unsigned p = 0; p <= 10; p += 5)
  {
                int tab[11] = { 2, 8, 42, 9, 13, 5, 3, 23, 40, -3, 55 };
                printf("p = %u  =>  m = %u\n", p, partition_cmp(tab, 0, 11, p, increasing));
                print_int_array(stdout, tab, 11);
        }

        //test for partition_cmp-------------------------------------*/

/*test for pivot_first----------------------------------------

int tab[10] = { 30, 8, 42, 9, 13, -3, 3, 23, 40, 5 };
printf("p = %u\n", pivot_median3(tab, 0, 10, increasing));*/

//test for pivot_first----------------------------------------


//test quick_sort------------------------------------------------
  srand(0);
  const unsigned tsize = 500000;
  int* tab1 = malloc(tsize * sizeof(int));
  int* tab2 = malloc(tsize * sizeof(int));
  for (unsigned i = 0; i < tsize; ++i)
    tab2[i] = tab1[i] = rand(); // = i;

  mycheck(quick_sort_cmp, tab1);
  mycheck(quick_sort_cmp_loop, tab2);
  return 0;

//test quick_sort------------------------------------------------

return 0; 
}
