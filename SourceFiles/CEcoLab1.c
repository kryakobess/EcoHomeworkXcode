/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab1
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
#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorC.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"
#include "CEcoLab1.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoLab1
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1_QueryInterface(/* in */ struct IEcoLab1* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoLab1) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoCalculatorX) ) {
        // При запросе интерфейса IEcoCalculatorX отдаем агрегированный компонент EcoCalculatorA
        if (pCMe->m_pInnerUnknownA != 0) {
            result = pCMe->m_pInnerUnknownA->pVTbl->QueryInterface(pCMe->m_pInnerUnknownA, riid, ppv);
        }
        return result;
    } else if (IsEqualUGUID(riid, &IID_IEcoCalculatorY)) {
        if (pCMe->m_pInnerUnknownE != 0) {
            result = pCMe->m_pInnerUnknownE->pVTbl->QueryInterface(pCMe->m_pInnerUnknownE, riid, ppv);
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
 *   Функция AddRef для интерфейса IEcoLab1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1_AddRef(/* in */ struct IEcoLab1* me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

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
 *   Функция Release для интерфейса IEcoLab1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1_Release(/* in */ struct IEcoLab1* me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab1((IEcoLab1*)pCMe);
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

int16_t ECOCALLMETHOD CEcoLab1_gnome_sort_opt(struct IEcoLab1* me, void* arr, size_t count, size_t size, int (*comp)(const void*, const void*)) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
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

int16_t ECOCALLMETHOD CEcoLab1_gnome_sort(struct IEcoLab1* me, void* arr, size_t count, size_t size, int (*comp)(const void*, const void*)) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
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


int32_t ECOCALLMETHOD Addition(/* in */ struct CEcoLab1* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    int32_t result = 0;

    if (me == 0 ) {
        return -1;
    }

    if (pCMe->m_pIXCalculatorB != 0) {
        printf("Using EcoCalculatorB for addition method in EcoLab1\n");
        result = pCMe->m_pIXCalculatorB->pVTbl->Addition(pCMe->m_pIXCalculatorB, a, b);
    }

    return result;
}

int16_t ECOCALLMETHOD Subtraction(/* in */ struct CEcoLab1* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    int16_t result = 0;

    if (me == 0 ) {
        return -1;
    }

    if (pCMe->m_pIXCalculatorC != 0) {
        printf("Using EcoCalculatorC for substraction method in EcoLab1\n");
        result = pCMe->m_pIXCalculatorC->pVTbl->Subtraction(pCMe->m_pIXCalculatorC, a, b);
    }

    return result;
}

int32_t ECOCALLMETHOD Multiplication(/* in */ struct CEcoLab1* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    int32_t result = 0;

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }

    if (pCMe->m_pIYCalculatorD != 0) {
        printf("Using EcoCalculatorD for Multiplication method in EcoLab1\n");
        result = pCMe->m_pIYCalculatorD->pVTbl->Multiplication(pCMe->m_pIYCalculatorD, a, b);
    }

    return result;
}

int16_t ECOCALLMETHOD Division(/* in */ struct CEcoLab1* me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    int16_t result = 0;

    /* Проверка указателей */
    if (me == 0 ) {
        return -1;
    }

    if (pCMe->m_pIYCalculatorE != 0) {
        printf("Using EcoCalculatorE for Division method in EcoLab1\n");
        result = pCMe->m_pIYCalculatorE->pVTbl->Division(pCMe->m_pIYCalculatorE, a, b);
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
int16_t ECOCALLMETHOD initCEcoLab1(/*in*/ struct IEcoLab1* me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
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
    
    /* Создание внутреннего компонента "EcoCalculatorA" c поддержкой агрегирования */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorA, pOuterUnknown, &IID_IEcoUnknown, (void**) &pCMe->m_pInnerUnknownA);
    
    if (result != 0 || pCMe->m_pInnerUnknownA == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorB, pOuterUnknown, &IID_IEcoUnknown, (void**) &pCMe->m_pInnerUnknownA);
    }
    
    if (result != 0 || pCMe->m_pInnerUnknownA == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorC, pOuterUnknown, &IID_IEcoUnknown, (void**) &pCMe->m_pInnerUnknownA);
    }
    
    /* Создание внутреннего компонента "EcoCalculatorE" c поддержкой агрегирования */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorE, pOuterUnknown, &IID_IEcoUnknown, (void**) &pCMe->m_pInnerUnknownE);
    
    if (result != 0 || pCMe->m_pInnerUnknownE == 0) {
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorD, pOuterUnknown, &IID_IEcoUnknown, (void**) &pCMe->m_pInnerUnknownE);
    }
    
    /* ВКЛЮЧЕНИЕ */
    
    /* Получение интерфейса EcoCalculatorX внутреннего компонента "EcoCalculatorB" */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorB, 0, &IID_IEcoCalculatorX, (void**) &pCMe->m_pIXCalculatorB);
    /* Получение интерфейса EcoCalculatorX внутреннего компонента "EcoCalculatorC" */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorC, 0, &IID_IEcoCalculatorX, (void**) &pCMe->m_pIXCalculatorC);
    
    /* Получение интерфейса EcoCalculatorY внутреннего компонента "EcoCalculatorE" */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorE, 0, &IID_IEcoCalculatorY, (void**) &pCMe->m_pIYCalculatorE);
    
    /* Получение интерфейса EcoCalculatorY внутреннего компонента "EcoCalculatorD" */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorD, 0, &IID_IEcoCalculatorY, (void**) &pCMe->m_pIYCalculatorD);
    

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

/* Create Virtual Table IEcoLab1 */
IEcoLab1VTbl g_x277FC00C35624096AFCFC125B94EEC90VTbl = {
    CEcoLab1_QueryInterface,
    CEcoLab1_AddRef,
    CEcoLab1_Release,
    CEcoLab1_gnome_sort,
    CEcoLab1_gnome_sort_opt,
    Addition,
    Subtraction,
    Multiplication,
    Division
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
int16_t ECOCALLMETHOD createCEcoLab1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab1** ppIEcoLab1) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoLab1* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;
	
    /* Проверка указателей */
    if (ppIEcoLab1 == 0 || pIUnkSystem == 0) {
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
    pCMe = (CEcoLab1*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoLab1 */
    pCMe->m_pVTblIEcoLab1 = &g_x277FC00C35624096AFCFC125B94EEC90VTbl;

    /* Инициализация данных */
    pCMe->m_Name = 0;
    
    pCMe->m_pInnerUnknownA = 0;
    
    pCMe->m_pInnerUnknownE = 0;

    /* Возврат указателя на интерфейс */
    *ppIEcoLab1 = (IEcoLab1*)pCMe;

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
void ECOCALLMETHOD deleteCEcoLab1(/* in */ IEcoLab1* pIEcoLab1) {
    CEcoLab1* pCMe = (CEcoLab1*)pIEcoLab1;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab1 != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if (pCMe->m_pIYCalculatorE != 0) {
            pCMe->m_pIYCalculatorE->pVTbl->Release(pCMe->m_pIYCalculatorE);
        }
        if (pCMe->m_pIXCalculatorB != 0) {
            pCMe->m_pIXCalculatorB->pVTbl->Release(pCMe->m_pIXCalculatorB);
        }
        if (pCMe->m_pIXCalculatorC != 0) {
            pCMe->m_pIXCalculatorC->pVTbl->Release(pCMe->m_pIXCalculatorC);
        }
        if (pCMe->m_pIYCalculatorD != 0) {
            pCMe->m_pIYCalculatorD->pVTbl->Release(pCMe->m_pIYCalculatorD);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
