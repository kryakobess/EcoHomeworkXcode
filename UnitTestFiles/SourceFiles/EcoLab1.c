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
#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"
#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorC.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"


IEcoLab1* back(IEcoLab1* pILab1) {
    /* Вы всегда можете вернуться туда, откуда начали. */
    IEcoCalculatorX* p_x = 0;
    IEcoLab1* p_lab1 = 0;
    if (pILab1->pVTbl->QueryInterface(pILab1, &IID_IEcoCalculatorX, (void**)&p_x) == 0) {
        p_x->pVTbl->QueryInterface(p_x, &IID_IEcoLab1, (void**)&p_lab1);
    }
    return p_lab1;
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
    
    /* ПРИМЕРЫ ВКЛЮЧЕНИЯ/АГРЕГИРОВАНИЯ */

    //Получаю агрегированный компонент EcoCalculatorA по интерфейсу IEcoCalculatorX
    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**) &pIEcoCalculatorX);
    
    //Получаю агрегированный компонент EcoCalculatorE по интерфейсу IEcoCalculatorY
    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void**) &pIEcoCalculatorY);
    
    printf("Examples of inclusion method execution:\n");
    
    //Вызываю метод с включенным компонентом EcoCalculatorB
    res = pIEcoLab1->pVTbl->Addition(pIEcoLab1, 8, 4);
    printf("Addition: %d\n", res);
    
    //Вызываю метод с включенным компонентом EcoCalculatorC
    res = pIEcoLab1->pVTbl->Subtraction(pIEcoLab1, 8, 4);
    printf("Addition: %d\n", res);
    
    //Вызываю метод с включенным компонентом EcoCalculatorD
    res = pIEcoLab1->pVTbl->Multiplication(pIEcoLab1, 8, 4);
    printf("Multiplication: %d\n", res);
    
    //Вызываю метод с включенным компонентом EcoCalculatorE
    res = pIEcoLab1->pVTbl->Division(pIEcoLab1, 8, 4);
    printf("Division: %d\n", res);
    
    printf("Examples of aggregation method execution:\n");
    
    //Вызываю метод Addition агрегированного компонента EcoCalculatorA
    res = pIEcoCalculatorX->pVTbl->Addition(pIEcoCalculatorX,8,4);
    printf("Addition with aggregation of Component A: %d\n", res);
    
    //Вызываю метод Subtraction агрегированного компонента EcoCalculatorA
    res = pIEcoCalculatorX->pVTbl->Subtraction(pIEcoCalculatorX,8,4);
    printf("Subtraction with aggregation of Component A: %d\n", res);
    
    //Вызываю метод Multiplication агрегированного компонента EcoCalculatorE
    res = pIEcoCalculatorY->pVTbl->Multiplication(pIEcoCalculatorY,8,4);
    printf("Multiplication with aggregation of Component E: %d\n", res);
    
    //Вызываю метод Division агрегированного компонента EcoCalculatorE
    res = pIEcoCalculatorY->pVTbl->Division(pIEcoCalculatorY,8,4);
    printf("Addition with aggregation of Component E: %d\n", res);
    
    /* СВОЙСТВА ИНТЕРФЕЙСОВ */
    IEcoCalculatorX* p_xB = 0;
    pIEcoCalculatorY->pVTbl->QueryInterface(pIEcoCalculatorY, &IID_IEcoCalculatorX, (void**)&p_xB);
    
    res = p_xB->pVTbl->Addition(p_xB, 8, 4);
    printf("Addition with EcoCalculatorX from aggreagated component E: %d\n", res);

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

