//
// Created by Christian W. Aranibar Solaligue.
// UCSP - ADS
//

#ifndef SEQUENTIAL_CONCURRENT_SKIPLIST_ARGSMAIN_H
#define SEQUENTIAL_CONCURRENT_SKIPLIST_ARGSMAIN_H

#include <iostream>
#include <thread>
#include <ctime>
#include <fstream>
#include "./testStruct.h"

void help() {
    std::cout << "[--th]                    -> Testeo secuencial contra concurrente con la cantidad maxima de threads [Threads=default, Elementos=default]." << std::endl;
    std::cout << "[--th] [n]                -> Testeo secuencial contra concurrente con una cantidad n de threads [Elementos=default]." << std::endl;
    std::cout << "[--th] [n] [m]            -> Testeo secuencial contra concurrente con una cantidad n de threads y una cantidad m de elementos." << std::endl;
    std::cout << "[--th] [n] [m] [m] ...    -> Testeo secuencial contra concurrente con una cantidad n de threads y m casos de x de elementos." << std::endl << std::endl;

    std::cout << "[--thU]                       -> Testeo concurrente con la cantidad maxima de threads." << std::endl;
    std::cout << "[--thU] [n]                   -> Testeo concurrente con una cantidad n de threads." << std::endl;
    std::cout << "[--thU] [n] [m]               -> Testeo concurrente con una cantidad n de threads y una cantidad m de elementos." << std::endl;
    std::cout << "[--thU] [n] [m] [m] [m] ...   -> Testeo concurrente con una cantidad n de threads y una cantidad de m casos de x elementos." << std::endl << std::endl;

    std::cout << "[--thCsv] [n] [m] [s] -> Testeo secuencial contra concurrente con una cantidad n de threads, m elementos con s pruebas del mismo caso. [Promedio]" << std::endl << std::endl;

    std::cout << "[--s]             -> Testeo secuencial [Elementos=default]." << std::endl;
    std::cout << "[--s] [m]         -> Testeo secuencial con m elementos." << std::endl;
    std::cout << "[--s] [m] [m] ... -> Testeo secuencial con n casos de m elementos." << std::endl;

}

void helpC() {
    std::cout << "Cantidad de threads: MAX" << std::endl;
    std::cout << "Testeo Secuencial: True" << std::endl;
    std::cout << "Testeo Concurrente: True" << std::endl;
    std::cout << "Cantidad de elementos: 1000000" << std::endl;
}

void th(unsigned int elementos = 1000000, unsigned int threads = std::thread::hardware_concurrency()) {
    int min = 0;
    unsigned int max = elementos;
    std::vector<std::thread> insert_th;
    std::vector<std::thread> find_th;
    std::vector<std::thread> rem_th;
    std::vector<int> data;
    randomData<int> rData(min, max, elementos);

    //
    cSkipList<int> cSl(elementos);
    sSkipList<int> sSl(elementos);
    //

    //
    double t1Ic, t2Ic, tcInsert, t1Is, t2Is, tsInsert;
    double t1Fc, t2Fc, tcFind, t1Fs, t2Fs, tsFind;
    double t1Rc, t2Rc, tcRemove, t1Rs, t2Rs, tsRemove;
    //
    std::cout << "> Iniciando test concurrente contra secuencial" << std::endl;
    std::cout << "> Cantidad de Threads: " << threads << std::endl;
    std::cout << "> Cantidad de Elementos: " << elementos << std::endl;
    std::cout << "> ---------------------------" << std::endl;
    std::cout << "> Generando datos ..." << std::endl;
    rData.generate(data);
    std::cout << "> Datos generados con exito." << std::endl;
    std::cout << "> ---------------------------" << std::endl;


    // Insert ############################################################################
    // -----------------------------------------------------------------------------------
    std::cout << "> Test de insertado iniciado" << std::endl;
    t1Ic = clock();
    for (int i = 0; i < threads; i++) {
        insert_th.emplace_back(TestInsertConcurrent<int>(cSl, data), elementos);
    }
    for (int i = 0; i < threads; i++) {
        insert_th[i].join();
    }
    t2Ic = clock();
    tcInsert = (t2Ic - t1Ic) / CLOCKS_PER_SEC;
    // -----------------------------------------------------------------------------------


    // -----------------------------------------------------------------------------------
    t1Is = clock();
    TestInsertSequential<int>(sSl, data).operator()(elementos);
    t2Is = clock();
    tsInsert = (t2Is - t1Is) / CLOCKS_PER_SEC;
    // -----------------------------------------------------------------------------------
    std::cout << "> Insertado Concurrente: " << tcInsert << std::endl;
    std::cout << "> Insertado Secuencial: " << tsInsert << std::endl;
    std::cout << "> Test de insertado finalizado." << std::endl;
    // FinInsert -------------------------------------------------------------------------


    std::cout << "> ---------------------------" << std::endl;


    // Find ##############################################################################
    // -----------------------------------------------------------------------------------
    std::cout << "> Test de busqueda iniciado." << std::endl;
    t1Fc = clock();
    for (int i = 0; i < threads; i++) {
        find_th.emplace_back(TestBusquedaConcurrent<int>(cSl, data), elementos);
    }
    for (int i = 0; i < threads; i++) {
        find_th[i].join();
    }
    t2Fc = clock();
    tcFind = (t2Fc - t1Fc) / CLOCKS_PER_SEC;
    // -----------------------------------------------------------------------------------


    // -----------------------------------------------------------------------------------
    t1Fs = clock();
    TestBusquedaSequential<int>(sSl, data).operator()(elementos);
    t2Fs = clock();
    tsFind = (t2Fs - t1Fs) / CLOCKS_PER_SEC;
    // -----------------------------------------------------------------------------------
    std::cout << "> Busqueda Concurrente: " << tcFind << std::endl;
    std::cout << "> Busqueda Secuencial: " << tsFind << std::endl;
    std::cout << "> Test de busqueda finalizado." << std::endl;
    // FinFind ---------------------------------------------------------------------------


    std::cout << "> ---------------------------" << std::endl;


    // Remove ############################################################################
    // -----------------------------------------------------------------------------------
    std::cout << "> Test de borrado iniciado." << std::endl;
    t1Rc = clock();
    for (int i = 0; i < threads; i++) {
        rem_th.emplace_back(TestBorradoConcurrent<int>(cSl, data), elementos);
    }
    for (int i = 0; i < threads; i++) {
        rem_th[i].join();
    }
    t2Rc = clock();
    tcRemove = (t2Rc - t1Rc) / CLOCKS_PER_SEC;
    // -----------------------------------------------------------------------------------


    // -----------------------------------------------------------------------------------
    t1Rs = clock();
    TestBorradoSequential<int>(sSl, data).operator()(elementos);
    t2Rs = clock();
    tsRemove = (t2Rs - t1Rs) / CLOCKS_PER_SEC;
    // -----------------------------------------------------------------------------------
    std::cout << "> Borrado Concurrente: " << tcRemove << std::endl;
    std::cout << "> Borrado Secuencial: " << tsRemove << std::endl;
    std::cout << "> Test de borrado finalizado." << std::endl;
    // FinRemove -------------------------------------------------------------------------


    std::cout << "> ---------------------------" << std::endl;


    std::cout << "> Finalizado test concurrente contra secuencial" << std::endl;
}

void thU(unsigned int elementos = 1000000, unsigned int threads = std::thread::hardware_concurrency()) {
    int min = 0;
    unsigned int max = elementos;
    std::vector<std::thread> insert_th;
    std::vector<std::thread> find_th;
    std::vector<std::thread> rem_th;
    std::vector<int> data;
    randomData<int> rData(min, max, elementos);

    //
    cSkipList<int> cSl(elementos);
    //

    //
    double t1Ic, t2Ic, tcInsert;
    double t1Fc, t2Fc, tcFind;
    double t1Rc, t2Rc, tcRemove;
    //
    std::cout << "> Iniciando test unitario: Concurrente" << std::endl;
    std::cout << "> Cantidad de Threads: " << threads << std::endl;
    std::cout << "> Cantidad de Elementos: " << elementos << std::endl;
    std::cout << "> ---------------------------" << std::endl;
    std::cout << "> Generando datos ..." << std::endl;
    rData.generate(data);
    std::cout << "> Datos generados con exito." << std::endl;
    std::cout << "> ---------------------------" << std::endl;


    // Insert ############################################################################
    // -----------------------------------------------------------------------------------
    std::cout << "> Test de insertado iniciado" << std::endl;
    t1Ic = clock();
    for (int i = 0; i < threads; i++) {
        insert_th.emplace_back(TestInsertConcurrent<int>(cSl, data), elementos);
    }
    for (int i = 0; i < threads; i++) {
        insert_th[i].join();
    }
    t2Ic = clock();
    tcInsert = (t2Ic - t1Ic) / CLOCKS_PER_SEC;
    // -----------------------------------------------------------------------------------
    std::cout << "> Insertado concurrente: " << tcInsert << std::endl;
    std::cout << "> Test de insertado finalizado." << std::endl;
    // FinInsert -------------------------------------------------------------------------


    std::cout << "> ---------------------------" << std::endl;


    // Find ##############################################################################
    // -----------------------------------------------------------------------------------
    std::cout << "> Test de busqueda iniciado." << std::endl;
    t1Fc = clock();
    for (int i = 0; i < threads; i++) {
        find_th.emplace_back(TestBusquedaConcurrent<int>(cSl, data), elementos);
    }
    for (int i = 0; i < threads; i++) {
        find_th[i].join();
    }
    t2Fc = clock();
    tcFind = (t2Fc - t1Fc) / CLOCKS_PER_SEC;
    // -----------------------------------------------------------------------------------
    std::cout << "> Busqueda concurrente: " << tcFind << std::endl;
    std::cout << "> Test de busqueda finalizado." << std::endl;
    // FinFind ---------------------------------------------------------------------------


    std::cout << "> ---------------------------" << std::endl;


    // Remove ############################################################################
    // -----------------------------------------------------------------------------------
    std::cout << "> Test de borrado iniciado." << std::endl;
    t1Rc = clock();
    for (int i = 0; i < threads; i++) {
        rem_th.emplace_back(TestBorradoConcurrent<int>(cSl, data), elementos);
    }
    for (int i = 0; i < threads; i++) {
        rem_th[i].join();
    }
    t2Rc = clock();
    tcRemove = (t2Rc - t1Rc) / CLOCKS_PER_SEC;
    // -----------------------------------------------------------------------------------
    std::cout << "> Borrado concurrente: " << tcRemove << std::endl;
    std::cout << "> Test de borrado finalizado." << std::endl;
    // FinRemove -------------------------------------------------------------------------


    std::cout << "> ---------------------------" << std::endl;


    std::cout << "> Finalizado test unitario: Concurrente" << std::endl;
}

void s(unsigned  int elementos = 1000000) {
    int min = 0;
    unsigned int max = elementos;
    std::vector<int> data;
    randomData<int> rData(min, max, elementos);

    //
    sSkipList<int> sSl(elementos);
    //

    //
    double t1Is, t2Is, tsInsert;
    double t1Fs, t2Fs, tsFind;
    double t1Rs, t2Rs, tsRemove;
    //

    std::cout << "> Iniciando test unitario: Secuencial" << std::endl;
    std::cout << "> Cantidad de Elementos: " << elementos << std::endl;
    std::cout << "> ---------------------------" << std::endl;
    std::cout << "> Generando datos ..." << std::endl;
    rData.generate(data);
    std::cout << "> Datos generados con exito." << std::endl;
    std::cout << "> ---------------------------" << std::endl;


    // Insert ############################################################################
    // -----------------------------------------------------------------------------------
    t1Is = clock();
    TestInsertSequential<int>(sSl, data).operator()(elementos);
    t2Is = clock();
    tsInsert = (t2Is - t1Is) / CLOCKS_PER_SEC;
    // -----------------------------------------------------------------------------------
    std::cout << "> Insertado Secuencial: " << tsInsert << std::endl;
    std::cout << "> Test de insertado finalizado." << std::endl;
    // FinInsert -------------------------------------------------------------------------


    std::cout << "> ---------------------------" << std::endl;


    // Find ##############################################################################
    // -----------------------------------------------------------------------------------
    t1Fs = clock();
    TestBusquedaSequential<int>(sSl, data).operator()(elementos);
    t2Fs = clock();
    tsFind = (t2Fs - t1Fs) / CLOCKS_PER_SEC;
    // -----------------------------------------------------------------------------------
    std::cout << "> Busqueda Secuencial: " << tsFind << std::endl;
    std::cout << "> Test de busqueda finalizado." << std::endl;
    // FinFind ---------------------------------------------------------------------------


    std::cout << "> ---------------------------" << std::endl;


    // Remove ############################################################################
    // -----------------------------------------------------------------------------------
    t1Rs = clock();
    TestBorradoSequential<int>(sSl, data).operator()(elementos);
    t2Rs = clock();
    tsRemove = (t2Rs - t1Rs) / CLOCKS_PER_SEC;
    // -----------------------------------------------------------------------------------
    std::cout << "> Borrado Secuencial: " << tsRemove << std::endl;
    std::cout << "> Test de borrado finalizado." << std::endl;
    // FinRemove -------------------------------------------------------------------------


    std::cout << "> ---------------------------" << std::endl;


    std::cout << "> Finalizado test unitario: Secuencial" << std::endl;
}

void sm (const std::vector<int>& elementos) {
    std::cout << "> Inciando test secuencial de n elementos" << std::endl;
    std::cout << "> Cantidad de casos [n]: " << elementos.size() << std::endl << std::endl;
    int min = 0;
    for (int elemento : elementos) {
        unsigned int max = elemento;
        std::vector<int> data;
        randomData<int> rData(min, max, elemento);

        //
        sSkipList<int> sSl(elemento);
        //

        //
        double t1Is, t2Is, tsInsert;
        double t1Fs, t2Fs, tsFind;
        double t1Rs, t2Rs, tsRemove;
        //
        std::cout << "> ###########################################" << std::endl;
        std::cout << "> Iniciando test unitario: Secuencial" << std::endl;
        std::cout << "> Cantidad de Elementos: " << elemento << std::endl;
        std::cout << "> ---------------------------" << std::endl;
        std::cout << "> Generando datos ..." << std::endl;
        rData.generate(data);
        std::cout << "> Datos generados con exito." << std::endl;
        std::cout << "> ---------------------------" << std::endl;
        // Insert ############################################################################
        // -----------------------------------------------------------------------------------
        t1Is = clock();
        TestInsertSequential<int>(sSl, data).operator()(elemento);
        t2Is = clock();
        tsInsert = (t2Is - t1Is) / CLOCKS_PER_SEC;
        // -----------------------------------------------------------------------------------
        std::cout << "> Insertado Secuencial: " << tsInsert << std::endl;
        std::cout << "> Test de insertado finalizado." << std::endl;
        // FinInsert -------------------------------------------------------------------------
        std::cout << "> ---------------------------" << std::endl;
        // Find ##############################################################################
        // -----------------------------------------------------------------------------------
        t1Fs = clock();
        TestBusquedaSequential<int>(sSl, data).operator()(elemento);
        t2Fs = clock();
        tsFind = (t2Fs - t1Fs) / CLOCKS_PER_SEC;
        // -----------------------------------------------------------------------------------
        std::cout << "> Busqueda Secuencial: " << tsFind << std::endl;
        std::cout << "> Test de busqueda finalizado." << std::endl;
        // FinFind ---------------------------------------------------------------------------
        std::cout << "> ---------------------------" << std::endl;
        // Remove ############################################################################
        // -----------------------------------------------------------------------------------
        t1Rs = clock();
        TestBorradoSequential<int>(sSl, data).operator()(elemento);
        t2Rs = clock();
        tsRemove = (t2Rs - t1Rs) / CLOCKS_PER_SEC;
        // -----------------------------------------------------------------------------------
        std::cout << "> Borrado Secuencial: " << tsRemove << std::endl;
        std::cout << "> Test de borrado finalizado." << std::endl;
        // FinRemove -------------------------------------------------------------------------
        std::cout << "> ---------------------------" << std::endl;
        std::cout << "> Finalizado test unitario: Secuencial" << std::endl;
        std::cout << "> ###########################################" << std::endl << std::endl;
    }
}

void thm (const std::vector<int> &elementos, unsigned int threads) {
    std::cout << "Cantidad de casos [m]: " << elementos.size() << std::endl;
    for (int elemento : elementos) {
        std::cout << "> ###########################################" << std::endl;
        th(elemento, threads);
        std::cout << "> ###########################################" << std::endl << std::endl;
    }
}

void thUm (const std::vector<int> &elementos, unsigned int threads) {
    std::cout << "Cantidad de casos [m]: " << elementos.size() << std::endl;
    for (int elemento : elementos) {
        std::cout << "> ###########################################" << std::endl;
        thU(elemento, threads);
        std::cout << "> ###########################################" << std::endl << std::endl;
    }
}

void thCsv(unsigned int elementos, unsigned int threads, unsigned int casos) {

    std::fstream testsTime;
    testsTime.open("./TestTimes/times.csv", std::ios::out);
    testsTime << "insert_concurrente,insert_secuencial,find_concurrente,find_secuencial,remove_concurrente,remove_secuencial," << elementos << "," << threads << std::endl;
    int min = 0;
    unsigned int max = elementos;

    std::vector<int> data;
    randomData<int> rData(min, max, elementos);
    std::cout << "> ---------------------------" << std::endl;
    std::cout << "> Cantidad de casos: " << casos << std::endl;
    std::cout << "> Iniciando test concurrente contra secuencial" << std::endl;
    std::cout << "> Cantidad de Threads: " << threads << std::endl;
    std::cout << "> Cantidad de Elementos: " << elementos << std::endl;
    std::cout << "> ---------------------------" << std::endl;
    std::cout << "> Generando datos ..." << std::endl;
    rData.generate(data);
    std::cout << "> Datos generados con exito." << std::endl;
    std::cout << "> ---------------------------" << std::endl << std::endl;

    for (unsigned int j = 0; j < casos; j++) {
        std::vector<std::thread> insert_th;
        std::vector<std::thread> find_th;
        std::vector<std::thread> rem_th;
        //
        cSkipList<int> cSl(elementos);
        sSkipList<int> sSl(elementos);
        //

        //
        double t1Ic, t2Ic, tcInsert, t1Is, t2Is, tsInsert;
        double t1Fc, t2Fc, tcFind, t1Fs, t2Fs, tsFind;
        double t1Rc, t2Rc, tcRemove, t1Rs, t2Rs, tsRemove;
        //
        std::cout << "> ###########################################" << std::endl;

        // Insert ############################################################################
        // -----------------------------------------------------------------------------------
        std::cout << "> Test de insertado iniciado" << std::endl;
        t1Ic = clock();
        for (int i = 0; i < threads; i++) {
            insert_th.emplace_back(TestInsertConcurrent<int>(cSl, data), elementos);
        }
        for (int i = 0; i < threads; i++) {
            insert_th[i].join();
        }
        t2Ic = clock();
        tcInsert = (t2Ic - t1Ic) / CLOCKS_PER_SEC;
        // -----------------------------------------------------------------------------------


        // -----------------------------------------------------------------------------------
        t1Is = clock();
        TestInsertSequential<int>(sSl, data).operator()(elementos);
        t2Is = clock();
        tsInsert = (t2Is - t1Is) / CLOCKS_PER_SEC;
        // -----------------------------------------------------------------------------------
        std::cout << "> Insertado Concurrente: " << tcInsert << std::endl;
        std::cout << "> Insertado Secuencial: " << tsInsert << std::endl;
        std::cout << "> Test de insertado finalizado." << std::endl;
        // FinInsert -------------------------------------------------------------------------


        std::cout << "> ---------------------------" << std::endl;


        // Find ##############################################################################
        // -----------------------------------------------------------------------------------
        std::cout << "> Test de busqueda iniciado." << std::endl;
        t1Fc = clock();
        for (int i = 0; i < threads; i++) {
            find_th.emplace_back(TestBusquedaConcurrent<int>(cSl, data), elementos);
        }
        for (int i = 0; i < threads; i++) {
            find_th[i].join();
        }
        t2Fc = clock();
        tcFind = (t2Fc - t1Fc) / CLOCKS_PER_SEC;
        // -----------------------------------------------------------------------------------


        // -----------------------------------------------------------------------------------
        t1Fs = clock();
        TestBusquedaSequential<int>(sSl, data).operator()(elementos);
        t2Fs = clock();
        tsFind = (t2Fs - t1Fs) / CLOCKS_PER_SEC;
        // -----------------------------------------------------------------------------------
        std::cout << "> Busqueda Concurrente: " << tcFind << std::endl;
        std::cout << "> Busqueda Secuencial: " << tsFind << std::endl;
        std::cout << "> Test de busqueda finalizado." << std::endl;
        // FinFind ---------------------------------------------------------------------------


        std::cout << "> ---------------------------" << std::endl;


        // Remove ############################################################################
        // -----------------------------------------------------------------------------------
        std::cout << "> Test de borrado iniciado." << std::endl;
        t1Rc = clock();
        for (int i = 0; i < threads; i++) {
            rem_th.emplace_back(TestBorradoConcurrent<int>(cSl, data), elementos);
        }
        for (int i = 0; i < threads; i++) {
            rem_th[i].join();
        }
        t2Rc = clock();
        tcRemove = (t2Rc - t1Rc) / CLOCKS_PER_SEC;
        // -----------------------------------------------------------------------------------


        // -----------------------------------------------------------------------------------
        t1Rs = clock();
        TestBorradoSequential<int>(sSl, data).operator()(elementos);
        t2Rs = clock();
        tsRemove = (t2Rs - t1Rs) / CLOCKS_PER_SEC;
        // -----------------------------------------------------------------------------------
        std::cout << "> Borrado Concurrente: " << tcRemove << std::endl;
        std::cout << "> Borrado Secuencial: " << tsRemove << std::endl;
        std::cout << "> Test de borrado finalizado." << std::endl;
        // FinRemove -------------------------------------------------------------------------


        std::cout << "> ---------------------------" << std::endl;
        std::cout << "> Finalizado test concurrente contra secuencial" << std::endl;

        testsTime << tcInsert << "," << tsInsert << "," << tcFind << "," << tsFind << "," << tcRemove << "," << tsRemove << std::endl;

        std::cout << "> ###########################################" << std::endl << std::endl;
    }
    testsTime.close();

}

#endif //SEQUENTIAL_CONCURRENT_SKIPLIST_ARGSMAIN_H
