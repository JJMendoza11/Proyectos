/*
 * @file Timer.h
 *
 *  Created on: Jul 26, 2021
 * @Author: lucky
 */

#ifndef SRC_TIMER_TIMER_H_
#define SRC_TIMER_TIMER_H_

/*
 * @fn MX_TIM6_Init
 * @brief Función generada por el IDE para la
 * inicializacion del Timer6.
 * @param void.
 * @return void.
 */
extern void MX_TIM6_Init(void);


/*
 * @fn Timer_vStarTimer
 * @brief El contador empieza a contar.
 * @param void.
 * @return void.
 */
extern void Timer_vStarTimer(void);

/*
 * @fn Timer_vDelayUs
 * @brief Se espera los us establesidos.
 * @param us Inidica los us que se tiene que
 * esperar. Rango [0, 0xFFFFFFFF].
 * @return void.
 */
extern void Timer_vDelayUs(uint32_t us);

#endif /* SRC_TIMER_TIMER_H_ */
