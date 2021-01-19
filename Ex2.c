
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define ull unsigned long long int

struct Object
{
    int weight;
    int value;
    int quanity;
    float unitVal;
    char name;
};

/*
   Anonymous function to compare two objects by unit value 
*/
int comparator(const void *ptr1, const void *ptr2)
{
    struct Object obj1 = *(struct Object *)ptr1;
    struct Object obj2 = *(struct Object *)ptr2;
    return (obj1.unitVal < obj2.unitVal) - (obj1.unitVal > obj2.unitVal);
}

/*
    Dynamic allocate array of objects
*/
struct Object *mallocObjects(int size)
{
    return (struct Object *)malloc(size * sizeof(struct Object));
}

/*
    Helper function to debug
*/
void printObject(struct Object obj)
{
    printf("%c(%d,%d) : %d \n", obj.name, obj.weight, obj.value, obj.quanity);
}

int main()
{
    int N, T;
    FILE *input_file = NULL;

    input_file = fopen("./BAG.INP", "r");

    assert(input_file != NULL);

    fscanf(input_file, "%d %d", &N, &T);

    struct Object *objects = mallocObjects(N);

    for (int i = 0; i < N; i++)
    {
        struct Object tmp;
        fscanf(input_file, "%d %d %c", &tmp.weight, &tmp.value, &tmp.name);
        tmp.unitVal = (float)(tmp.value) / (float)(tmp.weight);

        objects[i] = tmp;
    }

    qsort(objects, N, sizeof(struct Object), comparator);

    int cur_weight = T;
    int cur_var = 0;

    for (int i = 0; i < N; i++)
    {
        // https://www.tutorialspoint.com/c_standard_library/c_function_div.htm
        div_t divRet = div(cur_weight, objects[i].weight);
        int quanitity = divRet.quot;

        cur_var += quanitity * objects[i].value;
        cur_weight = divRet.rem;

        objects[i].quanity = quanitity;

        printObject(objects[i]);
    }

    printf("%d \n", cur_var);

    for (int i = 0; i < N; i++)
    {
        if (!objects[i].quanity)
            continue;
        printf("%c %d \n", objects[i].name, objects[i].quanity);
    }

    fclose(input_file);
    free(objects);
    return 0;
}