/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"

#define ARRAY_SIZE 8
#define STRING_MAX_SIZE 10

int intComp(const void* p, const void* q) {
    // Get the values at given addresses
    int l = *(const int*)p;
    int r = *(const int*)q;

    return (l > r) - (l < r);
}

int intDescComp(const void* p, const void* q) {
    // Get the values at given addresses
    int l = *(const int*)p;
    int r = *(const int*)q;

    return (l < r) - (l > r);
}

int stringComp(const void* p, const void* q) {
    char* l = *(char* const*) p;
    char* r = *(char* const*) q;
    return strcmp(l, r);
}

int doubleComp(const void* p, const void* q) {
    double l = *(const double*)p;
    double r = *(const double*)q;
    return l > r ? 1 : l < r ? -1 : 0;
}

char* rand_string(char *str, size_t size) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    if (size) {
        --size;
        for (size_t n = 0; n < size; n++) {
            int key = rand() % (int) (sizeof charset - 1);
            str[n] = charset[key];
        }
        str[size] = '\0';
    }
    return str;
}

void printArr(int* arr, size_t count) {
    for (size_t i = 0; i < count; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void doBenchmark(IEcoLab1* pIEcoLab1, void* arr, size_t size, size_t count, int (*comp)(const void *, const void*)) {
    double start = (double)(clock()) * 1000 / (CLOCKS_PER_SEC);
    //pIEcoLab1->pVTbl->gnome_sort(pIEcoLab1, arr, count, size, comp);
    qsort(arr, size, count, comp);
    double end = (double)(clock()) * 1000 / (CLOCKS_PER_SEC);
    double diff = end - start;
    printf("%f\n", diff);
}

void doBenchmarkOnIntArray(IEcoLab1* pIEcoLab1) {
    for (size_t count = 1e3; count <= 2e4; count+=1e3) {
        int arr[count];
        srand(1000);
        for (size_t i = 0; i < count; ++i) {
            arr[i] = rand();
        }
        doBenchmark(pIEcoLab1, arr, sizeof(arr[0]), count, intComp);
    }
}

void doBenchmarkOnStringArray(IEcoLab1* pIEcoLab1, IEcoMemoryAllocator1* pIMem) {
    for (size_t count = 1e3; count <= 2e4; count+=1e3) {
        char* arr[count];
        srand(time(NULL));
        for (size_t i = 0; i < count; ++i) {
            char* line = pIMem->pVTbl->Alloc(pIMem, STRING_MAX_SIZE);
            arr[i] = rand_string(line, STRING_MAX_SIZE);
        }
        doBenchmark(pIEcoLab1, arr, sizeof(arr[0]), count, stringComp);
        for (int i = 0; i < count; ++i) {
            pIMem->pVTbl->Free(pIMem, arr[i]);
        }
    }
}

void doBenchmarkOnDoubleArray(IEcoLab1* pIEcoLab1) {
    double maxRange = 100.0; double minRange = -100.0;
    double range = maxRange - minRange;
    double div = RAND_MAX / range;
    for (size_t count = 2e3; count <= 2e4; count+=1e3) {
        double arr[count];
        srand(time(NULL));
        for (size_t i = 0; i < count; ++i) {
            arr[i] = minRange + (rand() / div);
        }
        doBenchmark(pIEcoLab1, arr, sizeof(arr[0]), count, doubleComp);
    }
}

void doBenchmarkOnIncreasingInt(IEcoLab1* pIEcoLab1, int (*comp)(const void *, const void*)) {
    for (size_t count = 1e3; count <= 2e4; count += 1e3) {
        int arr[count];

        for (size_t i = 0; i < count; ++i) {
            arr[i] = i;
        }
        doBenchmark(pIEcoLab1, arr, sizeof(arr[0]), count, comp);
    }
}

/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    //char* arr[ARRAY_SIZE] = {"qqqq", "bbbb", "gggg", "dddd", "aaaa", "eeee", "uuuu", "zzzz"};
    int arr[ARRAY_SIZE] = {1, 5,9, 2, 7, 8,1, 4};
    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1 = 0;

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#ifdef ECO_LIB
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif
    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Выделение блока памяти */
    //name = (char_t *)pIMem->pVTbl->Alloc(pIMem, 10);

    /* Заполнение блока памяти */
    //pIMem->pVTbl->Fill(pIMem, name, 'a', 9);


    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    
    //doBenchmarkOnIntArray(pIEcoLab1);
    //doBenchmarkOnStringArray(pIEcoLab1, pIMem);
    //doBenchmarkOnDoubleArray(pIEcoLab1);
    doBenchmarkOnIncreasingInt(pIEcoLab1, intComp);
    //result = pIEcoLab1->pVTbl->gnome_sort(pIEcoLab1, arr, ARRAY_SIZE, sizeof(arr[0]), intComp);
    //for (int i = 0; i < ARRAY_SIZE; ++i) {
    //    printf("%s ", arr[i]);
    //}
    //printArr(arr, ARRAY_SIZE);
    /* Освлбождение блока памяти */
    //pIMem->pVTbl->Free(pIMem, name);

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab1 != 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

