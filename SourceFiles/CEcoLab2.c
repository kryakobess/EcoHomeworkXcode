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

void swap(void* el1, void* el2, size_t size) {
    char buffer[size];
    char* p_el1 = (char*) el1;
    char* p_el2 = (char*) el2;
    
    for (size_t i = 0; i < size; ++i) {
        buffer[i] = p_el1[i];
        p_el1[i] = p_el2[i];
        p_el2[i] = buffer[i];
    }
}

int16_t ECOCALLMETHOD CEcoLab2_gnome_sort_opt(struct IEcoLab2* me, void* arr, size_t count, size_t size, int (*comp)(const void*, const void*)) {
    CEcoLab2* pCMe = (CEcoLab2*)me;
    size_t i = 1;
    size_t j = 2;
    
    if (arr == 0 || comp == 0 || size == 0) {
        return -1;
    }
    
    if (count <= 1) {
        return 0;
    }
    
    while(i < count) {
        if ((*comp)(arr + ((i - 1) * size), arr + (i * size)) >= 0) {
            i = j;
            j++;
        } else {
            swap(arr + ((i - 1) * size), arr + (i * size), size);
            i--;
            if (i == 0) {
                i = j;
                j++;
            }
        }
    }
    
    return 0;
}

int16_t ECOCALLMETHOD CEcoLab2_gnome_sort(struct IEcoLab2* me, void* arr, size_t count, size_t size, int (*comp)(const void*, const void*)) {
    CEcoLab2* pCMe = (CEcoLab2*)me;
    size_t i = 0;
    if (arr == 0 || comp == 0 || size == 0) {
        return -1;
    }
    
    if (count <= 1) {
        return 0;
    }
    
    while(i < count) {
        if (i == 0) {
            i++;
        }
        if ((*comp)(arr + ((i - 1) * size), arr + (i * size)) >= 0) {
            i++;
        } else {
            swap(arr + ((i - 1) * size), arr + (i * size), size);
            i--;
        }
    }
    return 0;
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
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pCMe->m_pIEcoLab1);
    
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
        if (pCMe->m_pIEcoLab1 != 0) {
            pCMe->m_pIEcoLab1->pVTbl->Release(pCMe->m_pIEcoLab1);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
