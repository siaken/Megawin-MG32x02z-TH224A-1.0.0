/*
  Copyright (c) 2022 megawin Technology Co., Ltd. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef _WIRING_ANALOG_
#define _WIRING_ANALOG_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * \brief SAM3 products have only one reference for ADC
 */
typedef enum _eAnalogReference
{
#ifdef  MG32F02U128
    AR_DEFAULT,              //EXTERNAL
    AR_INTERNAL,             //2.4V 
    AR_EXTERNAL,             //VREF+
#endif
} eAnalogReference;



extern  eAnalogReference  g_AnalogReference;

/*
 * \brief Set the analog read.
 * And set the resolution of analogRead return values. Default is ADC_RESOLUTION in variant.h.
 *
 * \param res
 */
extern void analogReadInit();


/*
 * \brief Configures the reference voltage used for analog input (i.e. the value used as the top of the input range).
 * This function is kept only for compatibility with existing AVR based API.
 *
 * \param ulMmode Should be set to AR_DEFAULT.
 */
extern void analogReference( eAnalogReference ulMode ) ;

/*
 * \brief Writes an analog value (PWM wave) to a pin.
 *
 * \param ulPin
 * \param ulValue
 */
extern void analogWrite( uint32_t ulPin, uint32_t ulValue ) ;

/*
 * \brief Reads the value from the specified analog pin.
 *
 * \param ulPin : the gpio pin to use
 *
 * \return Read value from selected pin, if no error.
 */
extern uint32_t analogRead( uint32_t ulPin ) ;



/*
 * \brief Set the analog PWM output frequency.
 *
 * \param ulPin
 * 3: Set the PWM frequency of pin D3. (The frequency of D6 pin will be modified synchronously)
 * 5: Set the PWM frequency of pin D5. (The frequency of D8 and D9 pins will be modified synchronously)
 * 6: Set the PWM frequency of pin D6. (The frequency of D6 pin will be modified synchronously)
 * 8: Set the PWM frequency of pin D8. (The frequency of D5 and D9 pins will be modified synchronously)
 * 9: Set the PWM frequency of pin D9. (The frequency of D5 and D8 pins will be modified synchronously)
 * 10: Set the PWM frequency of pin D10. (The frequency of D11 pin will be modified synchronously)
 * 11: Set the PWM frequency of pin D11. (The frequency of D10 pin will be modified synchronously)
 * Or use optional macros:
 * PWM_FRQ_D3_D6: Set the PWM frequency of pin D3 and pin D6 at the same time. (same as setting pin D3 or pin D6 separately)
 * PWM_FRQ_D5_D8_D9: Set the PWM frequency of pin D5, pin D8 and pin D9 at the same time. (Same effect as setting pin D5, pin D8 or pin D9 separately)
 * PWM_FRQ_D10_D11: Set the PWM frequency of pin D10 and pin D1 at the same time (same as setting pin D10 or pin D11 separately).
 * PWM_FRQ_ALL: Set the PWM frequency of all pins simultaneously.
 *
 * \param freq£ºthe frequency 300~5000(Hz)
 */
void analogWriteFrequency(uint32_t ulPin,  uint32_t freq);

/*
 * \brief Set the resolution of analogRead return values. Default is ADC_RESOLUTION in variant.h.
 *
 * \param res
 */
extern void analogReadResolution(int res);

/*
 * \brief Set the resolution of analogWrite parameters. Default is DACC_RESOLUTION in variant.h.
 *
 * \param res
 */
extern void analogWriteResolution(int res);

/*
 * \brief initialize analog set the default value.
 *
 */
extern void analogOutputInit( void ) ;



#ifdef __cplusplus
}
#endif

#endif /* _WIRING_ANALOG_ */
