/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab2
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab2
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLab2.h"
#include "IEcoLab1.h"
#include "IdEcoLab1.h"
#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorC.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoLab2
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab2_QueryInterface(/* in */ struct IEcoLab2* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab2* pCMe = (CEcoLab2*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoLab2) ) {
        *ppv = &pCMe->m_pVTblIEcoLab2;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorX)) {
        *ppv = &pCMe->m_pVTblIX;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*) pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorY)) {
        *ppv = &pCMe->m_pVTblIY;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*) pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoLab2;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoLab1) ) {
        // При запросе интерфейса IEcoCalculatorX отдаем агрегированный компонент EcoCalculatorA
        if (pCMe->m_pInnerUnknownLab1 != 0) {
            result = pCMe->m_pInnerUnknownLab1->pVTbl->QueryInterface(pCMe->m_pInnerUnknownLab1, riid, ppv);
        }
        return result;
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

int16_t ECOCALLMETHOD X_QueryInterface(/* in */ struct IEcoCalculatorX* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoLab2*));
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoLab2) ) {
        *ppv = &pCMe->m_pVTblIEcoLab2;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorX)) {
        *ppv = &pCMe->m_pVTblIX;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*) pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorY)) {
        *ppv = &pCMe->m_pVTblIY;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*) pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoLab2;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoLab1) ) {
        // При запросе интерфейса IEcoCalculatorX отдаем агрегированный компонент EcoCalculatorA
        if (pCMe->m_pInnerUnknownLab1 != 0) {
            result = pCMe->m_pInnerUnknownLab1->pVTbl->QueryInterface(pCMe->m_pInnerUnknownLab1, riid, ppv);
        }
        return result;
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

int16_t ECOCALLMETHOD Y_QueryInterface(/* in */ struct IEcoCalculatorY* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct CEcoLab2*) - sizeof(struct IEcoCalculatorX*));
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoLab2) ) {
        *ppv = &pCMe->m_pVTblIEcoLab2;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*)pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorX)) {
        *ppv = &pCMe->m_pVTblIX;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*) pCMe);
    }
    else if (IsEqualUGUID(riid, &IID_IEcoCalculatorY)) {
        *ppv = &pCMe->m_pVTblIY;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*) pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoLab2;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoLab1) ) {
        // При запросе интерфейса IEcoCalculatorX отдаем агрегированный компонент EcoCalculatorA
        if (pCMe->m_pInnerUnknownLab1 != 0) {
            result = pCMe->m_pInnerUnknownLab1->pVTbl->QueryInterface(pCMe->m_pInnerUnknownLab1, riid, ppv);
        }
        return result;
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoLab2
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab2_AddRef(/* in */ struct IEcoLab2* me) {
    CEcoLab2* pCMe = (CEcoLab2*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

uint32_t ECOCALLMETHOD X_AddRef(/* in */ struct IEcoCalculatorX* me) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoLab2*));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

uint32_t ECOCALLMETHOD Y_AddRef(/* in */ struct IEcoCalculatorY* me) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct CEcoLab2*) - sizeof(struct IEcoCalculatorX*));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoLab2
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab2_Release(/* in */ struct IEcoLab2* me) {
    CEcoLab2* pCMe = (CEcoLab2*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab2((IEcoLab2*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

uint32_t ECOCALLMETHOD X_Release(/* in */ struct IEcoCalculatorX* me) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoLab2*));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab2((IEcoLab2*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

uint32_t ECOCALLMETHOD Y_Release(/* in */ struct IEcoCalculatorX* me) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct CEcoLab2*) - sizeof(struct IEcoCalculatorX*));

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab2((IEcoLab2*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

int32_t ECOCALLMETHOD X_Addition(/* in */ struct IEcoCalculatorX* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(IEcoLab2*));
    int32_t result = 0;

    if (me == 0 ) {
        return -1;
    }

    if (pCMe->m_pIEcoCalculatorX != 0) {
        printf("Using included EcoCalculatorX for addition method in EcoLab2\n");
        result = pCMe->m_pIEcoCalculatorX->pVTbl->Addition(pCMe->m_pIEcoCalculatorX, a, b);
    }

    return result;
}

int16_t ECOCALLMETHOD X_Subtraction(/* in */ struct IEcoCalculatorX* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct IEcoLab2*));
    int16_t result = 0;

    if (me == 0 ) {
        return -1;
    }

    if (pCMe->m_pIEcoCalculatorX != 0) {
        printf("Using included EcoCalculatorX for substraction method in EcoLab2\n");
        result = pCMe->m_pIEcoCalculatorX->pVTbl->Subtraction(pCMe->m_pIEcoCalculatorX, a, b);
    }

    return result;
}

int32_t ECOCALLMETHOD Y_Multiplication(/* in */ struct IEcoCalculatorY* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct CEcoLab2*) - sizeof(struct IEcoCalculatorX*));
    int32_t result = 0;

    if (me == 0 ) {
        return -1;
    }

    if (pCMe->m_pIEcoCalculatorY != 0) {
        printf("Using included EcoCalculatorY for addition method in EcoLab2\n");
        result = pCMe->m_pIEcoCalculatorY->pVTbl->Multiplication(pCMe->m_pIEcoCalculatorY, a, b);
    }

    return result;
}

int16_t ECOCALLMETHOD Y_Division(/* in */ struct IEcoCalculatorY* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab2* pCMe = (CEcoLab2*)((uint64_t)me - sizeof(struct CEcoLab2*) - sizeof(struct IEcoCalculatorX*));
    int16_t result = 0;

    if (me == 0 ) {
        return -1;
    }

    if (pCMe->m_pIEcoCalculatorY != 0) {
        printf("Using included EcoCalculatorY for substraction method in EcoLab2\n");
        result = pCMe->m_pIEcoCalculatorY->pVTbl->Division(pCMe->m_pIEcoCalculatorY, a, b);
    }

    return result;
}

/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD initCEcoLab2(/*in*/ struct IEcoLab2* me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoLab2* pCMe = (CEcoLab2*)me;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoUnknown* pOuterUnknown = (IEcoUnknown*)me; // агрегация
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    
    /* АГРЕГИРОВАНИЕ */
    
    /* Создание внутреннего компонента "EcoLab1" c поддержкой агрегирования */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, pOuterUnknown, &IID_IEcoUnknown, (void**) &pCMe->m_pInnerUnknownLab1);
    
    /* ВКЛЮЧЕНИЕ */
    
    /* Получение интерфейса IEcoLab1 внутреннего компонента "EcoLab1" */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorA, 0, &IID_IEcoCalculatorX, (void**) &pCMe->m_pIEcoCalculatorX);
    
    if (result != 0 || pCMe->m_pIEcoCalculatorX == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorB, 0, &IID_IEcoCalculatorX, (void**) &pCMe->m_pIEcoCalculatorX);
    }
    
    if (result != 0 || pCMe->m_pIEcoCalculatorX == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorC, 0, &IID_IEcoCalculatorX, (void**) &pCMe->m_pIEcoCalculatorX);
    }
    if (result!=0) {
        return result;
    }
    
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorD, 0, &IID_IEcoCalculatorY, (void**) &pCMe->m_pIEcoCalculatorY);
    
    if (result != 0 || pCMe->m_pIEcoCalculatorX == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorE, 0, &IID_IEcoCalculatorY, (void**) &pCMe->m_pIEcoCalculatorY);
    }

    
    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;



    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);
    
    return result;
}

/* Create Virtual Table IEcoLab2 */
IEcoLab2VTbl g_x277FC00C35624096AFCFC125B94EEC90VTbl = {
    CEcoLab2_QueryInterface,
    CEcoLab2_AddRef,
    CEcoLab2_Release
};

/* Create Virtual Table */
IEcoCalculatorXVTbl g_x9322111622484742AE0682819447843DVTbl = {
    X_QueryInterface,
    X_AddRef,
    X_Release,
    X_Addition,
    X_Subtraction
};

IEcoCalculatorYVTbl g_xBD6414C29096423EA90C04D77AFD1CADVTbl = {
    Y_QueryInterface,
    Y_AddRef,
    Y_Release,
    Y_Multiplication,
    Y_Division
};

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD createCEcoLab2(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab2** ppIEcoLab2) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoLab2* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;
    
    /* Проверка указателей */
    if (ppIEcoLab2 == 0 || pIUnkSystem == 0) {
        return result;
    }

    /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem1, (void **)&pISys);

    /* Проверка */
    if (result != 0 && pISys == 0) {
        return result;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Получение идентификатора компонента для работы с памятью */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получение интерфейса распределителя памяти */
    pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 && pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLab2*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab2));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoLab2 */
    pCMe->m_pVTblIEcoLab2 = &g_x277FC00C35624096AFCFC125B94EEC90VTbl;
    pCMe->m_pVTblIX = &g_x9322111622484742AE0682819447843DVTbl;
    pCMe->m_pVTblIY = &g_xBD6414C29096423EA90C04D77AFD1CADVTbl;

    /* Инициализация данных */
    pCMe->m_Name = 0;
    
    pCMe->m_pInnerUnknownLab1 = 0;

    /* Возврат указателя на интерфейс */
    *ppIEcoLab2 = (IEcoLab2*)pCMe;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void ECOCALLMETHOD deleteCEcoLab2(/* in */ IEcoLab2* pIEcoLab2) {
    CEcoLab2* pCMe = (CEcoLab2*)pIEcoLab2;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab2 != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if (pCMe->m_pIEcoCalculatorX != 0) {
            pCMe->m_pIEcoCalculatorX->pVTbl->Release(pCMe->m_pIEcoCalculatorX);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
