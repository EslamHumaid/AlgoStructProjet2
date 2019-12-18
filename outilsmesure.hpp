/**
 * @file outilsmesure.hpp
 * @author C. Jermann
 * @date 21/09/2015 Création (tp2.cpp)
 * @date 19/07/2016 Actualisation des commentaires & retrait du comptage temporel
 * @date 3/10/2017 transformation en un bibliothèque
 * @date 12/10/2018 version allégée de la bibliothèque (entête uniquement)
 * @brief test de performance par chronométrage
**/
#ifndef __OUTILSMESURE_HPP__
#define __OUTILSMESURE_HPP__

#include <ctime>     // time(), clock_t, clock(), CLOCKS_PER_SEC
using namespace std;

//--------------------------------------------------------------------
// Éléments de mesure de performance

/**
 * @var monChrono
 * @brief Chronomètre du programme
**/
clock_t monChrono;

/**
 * @def START
 * @brief démarre le Chronomètre
**/
#define START monChrono=clock();

/**
 * @def STOP
 * @brief arrête le Chronomètre
**/
#define STOP monChrono=clock()-monChrono;

/**
 * @def TEMPS
 * @brief donne le temps du Chronomètre (après arrêt)
**/
#define TEMPS double(monChrono)

/**
 * @def TEMPS
 * @brief donne le temps du Chronomètre (après arrêt)
**/
#define PRECISION CLOCKS_PER_SEC

/**
 * @def MAX(a,b)
 * @brief donne le maximum de a et b
**/
#define MAX(a,b) ((a<b)?b:a)

/**
 * @def MIN(a,b)
 * @brief donne le minimum de a et b
**/
#define MIN(a,b) ((a<b)?a:b)

/**
 * @def TAB
 * @brief caractère de tabulation (code ASCII 9)
**/
#define TAB '\t'

#endif // __OUTILSMESURE_HPP__
