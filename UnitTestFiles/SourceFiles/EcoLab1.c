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
#include "IEcoLab1.h"
#include "IdEcoList1.h"


void printProcessSeq(IEcoList1* list) {
    int count = list->pVTbl->Count(list);
    printf("Time:    ");
    for (int i = 0; i < count; ++i) {
        printf("%3d ", i+1);
    }
    printf("\n");
    printf("Process: ");
    for (int i = 0; i < count; ++i) {
        size_t el = (size_t) list->pVTbl->Item(list, i);
        printf("%3zu ", el);
    }
    printf("\n");
}

void printProcessSeq_NonPreemptive(IEcoList1* list) {
    int count = list->pVTbl->Count(list);
    printf("Process: ");
    for (int i = 0; i < count; ++i) {
        size_t el = (size_t) list->pVTbl->Item(list, i);
        printf("%3zu ->", el);
    }
    printf(" end\n");
}

void printProcessesStatistic(Process processes[], size_t count) {
    printf("pid\t\t burstTime\t\t arrivingTime\t\t turnAroundTime\t\t waitingTime\t\t completeTime\n");
    
    for (size_t i = 0; i < count; ++i) {
        Process p = processes[i];
        printf("%zu\t\t\t\t %zu\t\t\t\t %zu\t\t\t\t %zu\t\t\t\t\t\t %zu\t\t\t\t %zu\n", p.pid, p.burstTime, p.arrivalTime, p.turnAroundTime, p.waitingTime, p.completeTime);
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
    IEcoList1* seq = 0;
    char_t* name = 0;
    char_t* copyName = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1 = 0;
    uint32_t cAdvise = 0;

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
    /* Регистрация статического компонента для работы с CEcoLab1 */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoList1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_53884AFC93C448ECAA929C8D3A562281);
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

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0, &IID_IEcoList1, (void**) &seq);
    
    Process arr[] = {{1, 7, 2}, {2, 2, 6}, {3, 8, 0}, {4,5,1}, {5,5,4}};
    int count = sizeof(arr) / sizeof(Process);
    
    pIEcoLab1->pVTbl->sjf(pIEcoLab1, arr, count, seq);
    
    printf("\nPreemptive:\n");
    
    printProcessSeq(seq);
    
    printProcessesStatistic(arr, count);
    
    seq->pVTbl->Clear(seq);
    Process arr2[] = {{1, 7, 2}, {2, 2, 6}, {3, 8, 0}, {4,5,1}, {5,5,4}};
    pIEcoLab1->pVTbl->sjfNonPreemptive(pIEcoLab1, arr2, count, seq);
    
    printf("\nNon-preemptive:\n");
    
    printProcessSeq_NonPreemptive(seq);
    
    printProcessesStatistic(arr2, count);
    
    
    /* Освлбождение блока памяти */
    pIMem->pVTbl->Free(pIMem, name);

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

