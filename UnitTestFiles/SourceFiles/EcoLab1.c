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
#include "IdEcoLab2.h"
#include "IEcoLab1.h"
#include "IEcoLab2.h"
#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"
#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorC.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"


void examplesOnX(IEcoCalculatorX* pIEcoCalculatorX) {
    int res = 0;
    
    res = pIEcoCalculatorX->pVTbl->Addition(pIEcoCalculatorX,8,4);
    printf("Addition result: %d\n", res);
    
    res = pIEcoCalculatorX->pVTbl->Subtraction(pIEcoCalculatorX,8,4);
    printf("Subtraction result: %d\n", res);
}

void examplesOnY(IEcoCalculatorY* pIEcoCalculatorY) {
    int res = 0;
    
    res = pIEcoCalculatorY->pVTbl->Multiplication(pIEcoCalculatorY,8,4);
    printf("Multiplication result: %d\n", res);
    
    res = pIEcoCalculatorY->pVTbl->Division(pIEcoCalculatorY,8,4);
    printf("Division result: %d\n", res);
}

void examplesOfEcoLab1Inclusion(IEcoLab1* pIEcoLab1) {
    int res = 0;
    
    //Вызываю метод с включенным компонентом EcoCalculatorB
    res = pIEcoLab1->pVTbl->Addition(pIEcoLab1, 8, 4);
    printf("Addition from IEcoLab1 with inclusion, result: %d\n", res);
    
    //Вызываю метод с включенным компонентом EcoCalculatorC
    res = pIEcoLab1->pVTbl->Subtraction(pIEcoLab1, 8, 4);
    printf("Substraction from IEcoLab1 with inclusion, result: %d\n", res);
    
    //Вызываю метод с включенным компонентом EcoCalculatorD
    res = pIEcoLab1->pVTbl->Multiplication(pIEcoLab1, 8, 4);
    printf("Multiplication from IEcoLab1 with inclusion, result: %d\n", res);
    
    //Вызываю метод с включенным компонентом EcoCalculatorE
    res = pIEcoLab1->pVTbl->Division(pIEcoLab1, 8, 4);
    printf("Division from IEcoLab1 with inclusion, result: %d\n", res);
}

IEcoLab2* intersfaceBack(IEcoLab2* pEcoLab2) {
    IEcoCalculatorX* pX = 0;
    IEcoLab2* pl2 = 0;
    
    if (pEcoLab2->pVTbl->QueryInterface(pEcoLab2, &IID_IEcoCalculatorX, (void**)&pX) == 0) {
        pX->pVTbl->QueryInterface(pX, &IID_IEcoLab2, (void**)&pl2);
    }
    
    return pl2;
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

    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1 = 0;
    IEcoCalculatorX* pIEcoCalculatorX = 0;
    IEcoCalculatorY* pIEcoCalculatorY = 0;
    IEcoLab2* pIEcoLab2 = 0;
    IEcoLab1* pILab1 = 0;
    int res = 0;

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
    /* Регистрация статического компонента для работы со списком */
    //result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab2, (IEcoUnknown *)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3B);
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
    
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab2, 0, &IID_IEcoLab2, (void**) &pIEcoLab2);
    
    if (result != 0 || pIEcoLab2 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    
    /* ПРИМЕРЫ ВКЛЮЧЕНИЯ/АГРЕГИРОВАНИЯ */
    
    //Получаю агрегированный компонент EcoLab1 по интерфейсу IEcoLab1
    result = pIEcoLab2->pVTbl->QueryInterface(pIEcoLab2, &IID_IEcoLab1, (void**) &pIEcoLab1);

    
    //ИСПОЛЬЗУЮ ВКЛЮЧЕНИЕ В МЕТОДАХ ИНТЕРФЕЙСА ECOLAB1 (1 способ включения)
    
    printf("Examples of inclusion in custom method in IEcoLab1:\n");
    examplesOfEcoLab1Inclusion(pIEcoLab1);
    
    //ИСПОЛЬЗУЮ ВКЛЮЧЕНИЕ В РЕАЛИЗОВАННЫХ МЕТОДАХ ИНТЕРФЕЙСА IEcoCalculatorX и IEcoCalculatorY внутри EcoLab2 (2й способ включения)
    
    //Получаю включенный компонент по интерфейсу IEcoCalculatorX из EcoLab2
    result = pIEcoLab2->pVTbl->QueryInterface(pIEcoLab2, &IID_IEcoCalculatorX, (void**) &pIEcoCalculatorX);
    
    //Получаю включенный компонент по интерфейсу IEcoCalculatorY из EcoLab2
    result = pIEcoLab2->pVTbl->QueryInterface(pIEcoLab2, &IID_IEcoCalculatorY, (void**) &pIEcoCalculatorY);
    
    printf("Examples of inclusion in overwriten method of IEcoCalculatorX:\n");
    examplesOnX(pIEcoCalculatorX);
    
    printf("Examples of inclusion in overwriten method of IEcoCalculatorY:\n");
    examplesOnY(pIEcoCalculatorY);
    
    //АГРЕГАЦИЯ
    //ДАЛЕЕ ПРИ ИСПОЛЬЗОВАНИИ АГРЕГИРОВАННЫХ В IEcoLab1 КОМПОНЕНТОВ ПРОДЕМОНСТРИРОВАНО СВОЙСТВО ВЛОЖЕННОСТИ ИНТЕРФЕЙСОВ
    
    //Получаю агрегированный компонент по интерфейсу IEcoCalculatorX из EcoLab1
    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**) &pIEcoCalculatorX);
    
    //Получаю агрегированный компонент по интерфейсу IEcoCalculatorY из EcoLab1
    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void**) &pIEcoCalculatorY);
    
    printf("Examples of aggregation of EcoCalculatorX:\n");
    examplesOnX(pIEcoCalculatorX);
    
    printf("Examples of aggregation of EcoCalculatorY:\n");
    examplesOnY(pIEcoCalculatorY);
    
    //ВОЗВРАТНОЕ СВОЙСТВО ИНТЕРФЕЙСА
    printf("Returning interface from another interface:\n");
    printf("interfaces are equal: %s\n", pIEcoLab2 == intersfaceBack(pIEcoLab2) ? "true" : "false");
    

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

